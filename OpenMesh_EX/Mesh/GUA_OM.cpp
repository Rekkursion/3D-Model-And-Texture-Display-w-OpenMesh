#include "GUA_OM.h"
// Shader
#include "LoadShaders.h"
// STB
#define STB_IMAGE_IMPLEMENTATION
#include <../../OpenMesh-5.2/src/STB/stb_image.h>#define MODEL 0


typedef struct _TextureData {
	_TextureData() : width(0), height(0), data(0) {}
	int width;
	int height;
	unsigned char* data;
} TextureData;

static TextureData Load_png(const char* path) {
	TextureData texture;
	int n;
	stbi_uc *data = stbi_load(path, &texture.width, &texture.height, &n, 4);
	if (data != NULL) {
		texture.data = new unsigned char[texture.width * texture.height * 4 * sizeof(unsigned char)];
		memcpy(texture.data, data, texture.width * texture.height * 4 * sizeof(unsigned char));
		// vertical-mirror image data
		for (size_t i = 0; i < texture.width; i++) {
			for (size_t j = 0; j < texture.height / 2; j++) {
				for (size_t k = 0; k < 4; k++) {
					std::swap(texture.data[(j * texture.width + i) * 4 + k], texture.data[((texture.height - j - 1) * texture.width + i) * 4 + k]);
				}
			}
		}
		stbi_image_free(data);
	}
	return texture;
}


namespace OMT
{
	/*======================================================================*/
	Model::Model()
	{
		request_vertex_status();
		request_edge_status();
		request_face_status();
	}
	Model::~Model()
	{
		release_vertex_status();
		release_edge_status();
		release_face_status();
	}
}
/*======================================================================*/
namespace OMP
{
	Model::Model()
	{
		Mesh.request_vertex_status();
		Mesh.request_edge_status();
		Mesh.request_face_status();
	}
	Model::~Model()
	{
		Mesh.release_vertex_status();
		Mesh.release_edge_status();
		Mesh.release_face_status();
	}
	/*======================================================================*/
	// Read file
	bool Model::ReadFile(std::string _fileName)
	{
		bool isRead = false;
		OpenMesh::IO::Options opt;
		if ( OpenMesh::IO::read_mesh(Mesh, _fileName, opt) )
		{
			//read mesh from filename OK!
			isRead = true;
		}
		if(isRead)
		{
			// If the file did not provide vertex normals and mesh has vertex normal ,then calculate them
			if (!opt.check( OpenMesh::IO::Options::VertexNormal ) && Mesh.has_vertex_normals())
			{
				Mesh.update_normals();
			}
		}
		return isRead;
	}
	// Save file
	bool Model::SaveFile(std::string _fileName)
	{
		bool isSave = false;
		OpenMesh::IO::Options opt;
		if ( OpenMesh::IO::write_mesh(Mesh, _fileName, opt) )
		{
			//read mesh from filename OK!
			isSave = true;
		}
		return isSave;
	}
	/*======================================================================*/
	void Model::Render_solid()
	{
		FIter f_it;
		FVIter	fv_it;
		glPushAttrib(GL_LIGHTING_BIT);
		glEnable(GL_POLYGON_OFFSET_FILL);
		glEnable(GL_DEPTH_TEST);
		glPolygonOffset(2.0, 2.0);
		glBegin(GL_POLYGON);
		//glColor4f(1.0, 0.5, 1.0, 0.5);
		for (f_it = Mesh.faces_begin(); f_it != Mesh.faces_end(); ++f_it) 
		{
			for (fv_it = Mesh.fv_iter( f_it ); fv_it; ++fv_it)
			{						
				glNormal3dv(Mesh.normal(fv_it.handle()).data());
				glVertex3dv(Mesh.point(fv_it.handle()).data());
			}
		}
		glEnd();		
		glDisable(GL_POLYGON_OFFSET_FILL);
	}
	void Model::Render_wireframe()
	{
		MyMesh::HalfedgeHandle _hedge;
		EIter e_it=Mesh.edges_begin();

		glDisable(GL_LIGHTING);
		glEnable(GL_DEPTH_TEST);
		glColor3f(0.0, 0.0, 0.0);
		glLineWidth(1);
		glBegin(GL_LINES);
		for(e_it=Mesh.edges_begin(); e_it != Mesh.edges_end(); ++e_it)
		{
			_hedge = Mesh.halfedge_handle(e_it.handle(),1);

			glVertex3dv(Mesh.point(Mesh.from_vertex_handle(_hedge)).data());
			glVertex3dv(Mesh.point(Mesh.to_vertex_handle(_hedge)).data());			
		}
		glEnd();
		glEnable(GL_LIGHTING);
	}
	/*======================================================================*/
	void Model::RenderSpecifiedPoint()
	{
		glPushAttrib(GL_LIGHTING_BIT);
		glDisable(GL_LIGHTING);
		glEnable(GL_DEPTH_TEST);
		glPointSize(5.0f);
		glBegin(GL_POINTS);
		vector<sp_p>::iterator p_itr = sp_p_list.begin();
		for (p_itr; p_itr != sp_p_list.end(); ++p_itr)
		{
			glColor3f(p_itr->r, p_itr->g, p_itr->b);
			glVertex3dv(p_itr->pt.data());
		}
		glEnd();
		glEnable(GL_LIGHTING);
		glDisable(GL_POLYGON_OFFSET_FILL);
	}
	void Model::RenderSpecifiedVertex()
	{
		glPushAttrib(GL_LIGHTING_BIT);
		glDisable(GL_LIGHTING);
		glEnable(GL_DEPTH_TEST);
		glPointSize(5.0f);
		glBegin(GL_POINTS);
		vector< sp_v >::iterator v_itr = sp_v_list.begin();
		for (v_itr; v_itr != sp_v_list.end(); ++v_itr)
		{
			glColor3f(v_itr->r, v_itr->g, v_itr->b);
			glVertex3dv(Mesh.point(v_itr->vh).data());
		}
		glEnd();
		glEnable(GL_LIGHTING);
		glDisable(GL_POLYGON_OFFSET_FILL);
	}
	void Model::RenderSpecifiedFace()
	{
		glDisable(GL_CULL_FACE);
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		glPushAttrib(GL_LIGHTING_BIT);
		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonOffset(0.5, 1.0);
		glDisable(GL_LIGHTING);
		glEnable(GL_DEPTH_TEST);
		glBegin(GL_QUADS);
		FVIter fv_itr;
		vector< sp_f >::iterator f_itr;
		for (f_itr = sp_f_list.begin(); f_itr != sp_f_list.end(); ++f_itr)
		{
			glColor3f(f_itr->r, f_itr->g, f_itr->b);
			for (fv_itr=Mesh.fv_iter(f_itr->fh); fv_itr; ++fv_itr)
			{						
				glNormal3dv(Mesh.normal(fv_itr.handle()).data());
				glVertex3dv(Mesh.point(fv_itr.handle()).data());
			}
		}
		glEnd();		
		glEnable(GL_LIGHTING);
		glDisable(GL_POLYGON_OFFSET_FILL);
		glPolygonMode(GL_FRONT,GL_FILL);
		glEnable(GL_CULL_FACE);
	}

	/*======================================================================*/
	void Model::add_sp_p(Point   _p, float _r, float _g, float _b)
	{
		sp_p input_data;
		input_data.pt = _p;
		input_data.r = _r;
		input_data.g = _g;
		input_data.b = _b;
		sp_p_list.push_back(input_data);
	}
	void Model::add_sp_v(VHandle _v, float _r, float _g, float _b)
	{
		sp_v input_data;
		input_data.vh = _v;
		input_data.r = _r;
		input_data.g = _g;
		input_data.b = _b;
		sp_v_list.push_back(input_data);
	}
	void Model::add_sp_f(FHandle _f, float _r, float _g, float _b)
	{
		sp_f input_data;
		input_data.fh = _f;
		input_data.r = _r;
		input_data.g = _g;
		input_data.b = _b;
		sp_f_list.push_back(input_data);
	}
	void Model::clear_sp_p()
	{
		sp_p_list.clear();
	}
	void Model::clear_sp_v()
	{
		sp_v_list.clear();
	}
	void Model::clear_sp_f()
	{
		sp_f_list.clear();
	}
	/*======================================================================*/
	VHandle Model::addVertex(Point _p)
	{
		int find_result = findVertex(_p);
		if (find_result != -1)
		{
			return Mesh.vertex_handle(find_result);
		}
		else
		{
			return Mesh.add_vertex(_p);
		}
	}
	FHandle Model::addFace(VHandle _v0, VHandle _v1, VHandle _v2, VHandle _v3)
	{
		vector<VHandle> face_vhandles;

		face_vhandles.clear();
		face_vhandles.push_back(_v0);
		face_vhandles.push_back(_v1);
		face_vhandles.push_back(_v2);
		face_vhandles.push_back(_v3);
		return Mesh.add_face(face_vhandles);
	}
	void Model::deleteFace(FHandle _f)
	{
		Mesh.delete_face(_f);
		Mesh.garbage_collection();
	}
	void Model::deleteFace(VHandle _v0, VHandle _v1, VHandle _v2, VHandle _v3)
	{
		/* 
		v1				v0
		*<--------------*
		|				|
		|				|
		|				|
		|		f		|
		|				|
		|				|
		|				|
		* --------------*
		v2				v3
		*/

		HEHandle v0v1 = Mesh.find_halfedge(_v0, _v1);
		if (v0v1.is_valid())
		{
			FHandle fh = Mesh.face_handle(v0v1);
			if (fh.is_valid())
			{
				Mesh.delete_face(fh);
				Mesh.garbage_collection();
			}
		}
	}
	/*======================================================================*/
	bool Model::IsVertexVertex( VHandle _vj, VHandle _vi)
	{
		for( VVIter vvit = Mesh.vv_iter(_vi) ; vvit ; ++vvit )
			if( vvit.handle() == _vj )
				return true;
		return false;
	}
	/*======================================================================*/
	int Model::quad_subdivision1(int _face_id)
	{
		/*----------------------------------------------------------------------*/
		//�o�q�O���F�ѨMindex���D
		VHandle vq, vw, vt, vr;
		vq	 = addVertex(Point(0, 0, 100));
		vw	 = addVertex(Point(1, 0, 100));
		vt	 = addVertex(Point(1, 1, 100));
		vr	 = addVertex(Point(0, 1, 100));
		addFace(vq, vw, vt, vr);
		/*----------------------------------------------------------------------*/
		/*�����ݭnsubdivision��face*/
		//��ltable
		bool *table = new bool[Mesh.n_faces()];
		for (unsigned i = 0; i < Mesh.n_faces(); i++)
		{
			table[i] = false;
		}

		vector< FHandle > candidate_faces, last_found_face;
		last_found_face.push_back(Mesh.face_handle(_face_id));
		table[_face_id] = true;

		while(last_found_face.size() != 0)
		{
			vector< FHandle > new_found_faces;
			for (vector< FHandle >::iterator crnt_f = last_found_face.begin(); crnt_f != last_found_face.end(); ++crnt_f)
			{
				for (FFIter ff_itr = Mesh.ff_iter(*crnt_f); ff_itr; ++ff_itr)
				{
					if (table[ff_itr.handle().idx()] != true)
					{
						new_found_faces.push_back(ff_itr.handle());
						table[ff_itr.handle().idx()] = true;
					}
				}
			}
			for (vector< FHandle >::iterator f_itr = last_found_face.begin(); f_itr != last_found_face.end(); ++f_itr)
			{
				candidate_faces.push_back(*f_itr);
			}
			last_found_face.assign(new_found_faces.begin(), new_found_faces.end());
		}
		delete table;
		/*----------------------------------------------------------------------*/
		/*��candidate faces��subdivision*/
		/*
			v0		vd		v3
			*-------*-------*
			|		|		|	 
			|		|		|
			|	  ve|		|
		  va*-------*-------*vc
			|		|		|
			|		|		|
			|		|		|
			*-------*-------*
			v1		vb		v2		
		*/
		for (vector< FHandle >::iterator face_itr = candidate_faces.begin(); face_itr != candidate_faces.end(); ++face_itr)
		{
			VHandle v[4], va, vb, vc, vd, ve;
			FVIter fv_itr = Mesh.fv_iter(*face_itr);
			for (int i = 0; fv_itr; ++fv_itr)
			{
				v[i++] = fv_itr.handle();
			}

			deleteFace(v[0], v[1], v[2], v[3]);
			va	 = addVertex((Mesh.point(v[0])+Mesh.point(v[1]))/2);
			vb	 = addVertex((Mesh.point(v[1])+Mesh.point(v[2]))/2);
			vc	 = addVertex((Mesh.point(v[2])+Mesh.point(v[3]))/2);
			vd	 = addVertex((Mesh.point(v[3])+Mesh.point(v[0]))/2);
			ve	 = addVertex((Mesh.point(v[0])+Mesh.point(v[1])+Mesh.point(v[2])+Mesh.point(v[3]))/4);
			addFace(vd, v[0], va, ve);
			addFace(va, v[1], vb, ve);
			addFace(vb, v[2], vc, ve);
			addFace(vc, v[3], vd, ve);
		}
		/*----------------------------------------------------------------------*/
		deleteFace(vq, vw, vt, vr);//�o��u�O���F�ѨMindex���D
		/*----------------------------------------------------------------------*/
		return 0;
	}
	int Model::quad_subdivision2(int _face_id)
	{
		/*----------------------------------------------------------------------*/
		//�o�q�O���F�ѨMindex���D
		VHandle vq, vw, vt, vr;
		vq	 = addVertex(Point(0, 0, 100));
		vw	 = addVertex(Point(1, 0, 100));
		vt	 = addVertex(Point(1, 1, 100));
		vr	 = addVertex(Point(0, 1, 100));
		addFace(vq, vw, vt, vr);
		/*----------------------------------------------------------------------*/
		/*�����ݭnsubdivision��face*/
		//��ltable
		bool *table = new bool[Mesh.n_faces()];
		for (unsigned i = 0; i < Mesh.n_faces(); i++)
		{
			table[i] = false;
		}

		vector< FHandle > candidate_faces, last_found_face;
		last_found_face.push_back(Mesh.face_handle(_face_id));
		table[_face_id] = true;

		while(last_found_face.size() != 0)
		{
			vector< FHandle > new_found_faces;
			for (vector< FHandle >::iterator crnt_f = last_found_face.begin(); crnt_f != last_found_face.end(); ++crnt_f)
			{
				for (FFIter ff_itr = Mesh.ff_iter(*crnt_f); ff_itr; ++ff_itr)
				{
					if (table[ff_itr.handle().idx()] != true)
					{
						new_found_faces.push_back(ff_itr.handle());
						table[ff_itr.handle().idx()] = true;
					}
				}
			}
			for (vector< FHandle >::iterator f_itr = last_found_face.begin(); f_itr != last_found_face.end(); ++f_itr)
			{
				candidate_faces.push_back(*f_itr);
			}
			last_found_face.assign(new_found_faces.begin(), new_found_faces.end());
		}
		delete table;
		/*----------------------------------------------------------------------*/
		/*��candidate faces��subdivision*/
		/*
			v0		vh		vg		v3
			*-------*-------*-------*
			|		|		|		|
			|		|		|		|
			|	  vi|	  vl|		|
		 va *-------*-------*-------*vf
			|		|		|		|
			|		|		|		|
			|	  vj|	  vk|		|
		 vb *-------*-------*-------*ve
			|		|		|		|
			|		|		|		|
			|		|		|		|
			*-------*-------*-------*
			v1		vc		vd		v2		
		*/
		for (vector< FHandle >::iterator face_itr = candidate_faces.begin(); face_itr != candidate_faces.end(); ++face_itr)
		{
			VHandle v[4], va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl;
			FVIter fv_itr = Mesh.fv_iter(*face_itr);
			for (int i = 0; fv_itr; ++fv_itr)
			{
				v[i++] = fv_itr.handle();
			}

			deleteFace(v[0], v[1], v[2], v[3]);
			va	 = addVertex((Mesh.point(v[0])*2+Mesh.point(v[1])  )/3);
			vb	 = addVertex((Mesh.point(v[0])  +Mesh.point(v[1])*2)/3);
			vc	 = addVertex((Mesh.point(v[1])*2+Mesh.point(v[2])  )/3);
			vd	 = addVertex((Mesh.point(v[1])  +Mesh.point(v[2])*2)/3);
			ve	 = addVertex((Mesh.point(v[2])*2+Mesh.point(v[3])  )/3);
			vf	 = addVertex((Mesh.point(v[2])  +Mesh.point(v[3])*2)/3);
			vg	 = addVertex((Mesh.point(v[3])*2+Mesh.point(v[0])  )/3);
			vh	 = addVertex((Mesh.point(v[3])  +Mesh.point(v[0])*2)/3);

			vi	 = addVertex((Mesh.point(vh)*2+Mesh.point(vc)  )/3);
			vj	 = addVertex((Mesh.point(vh)  +Mesh.point(vc)*2)/3);
			vk	 = addVertex((Mesh.point(vd)*2+Mesh.point(vg)  )/3);
			vl	 = addVertex((Mesh.point(vd)  +Mesh.point(vg)*2)/3);
			addFace(v[0], va, vi, vh);
			addFace(va, vb, vj, vi);
			addFace(vb, v[1], vc, vj);
			addFace(vc, vd, vk, vj);
			addFace(vd, v[2], ve, vk);
			addFace(ve, vf, vl, vk);
			addFace(vf, v[3], vg, vl);
			addFace(vg, vh, vi, vl);
			addFace(vi, vj, vk, vl);
		}
		/*----------------------------------------------------------------------*/
		deleteFace(vq, vw, vt, vr);//�o��u�O���F�ѨMindex���D
		/*----------------------------------------------------------------------*/
		return 0;
	}
	/*======================================================================*/
	int Model::findVertex(Point _p)
	{
		for( VIter v_itr = Mesh.vertices_begin(); v_itr != Mesh.vertices_end(); ++v_itr)
			if( Mesh.point(v_itr) == _p )
				return v_itr.handle().idx();
		return -1;
	}
	/*======================================================================*/
};
/*======================================================================*/
// Initial function
void Tri_Mesh::init()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// VAO
	glDeleteVertexArrays(1, &VAO);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Load shader
	setShader("vertex.vs.glsl", "fragment.fs.glsl");

	glUseProgram(shaderProgram);
	MatricesIdx = glGetUniformBlockIndex(shaderProgram, "MatVP");
	ModelID = glGetUniformLocation(shaderProgram, "Model");
	M_KaID = glGetUniformLocation(shaderProgram, "Material.Ka");
	M_KdID = glGetUniformLocation(shaderProgram, "Material.Kd");
	M_KsID = glGetUniformLocation(shaderProgram, "Material.Ks");
	// VBO
	load2Buffer();
	// Set background color
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glUseProgram(0);
}

void Tri_Mesh::initPatch(void) {

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Load shader
	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER,		"vertexPatch.vs.glsl" },
		{ GL_FRAGMENT_SHADER,	"fragmentPatch.fs.glsl" },
		{ GL_NONE,				NULL }
	};
	patchProgram = LoadShaders(shaders);

	// VAO
	glDeleteVertexArrays(1, &VAOpatch);
	glGenVertexArrays(1, &VAOpatch);
	glBindVertexArray(VAOpatch);

	// VBO
	load2BufferPatch();
	// Set background color
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glUseProgram(0);
}

GLuint Tri_Mesh::loadShader(char* vs, char* fs) {
	ShaderInfo shaders[] =
	{
		{ GL_VERTEX_SHADER,		vs },
		{ GL_FRAGMENT_SHADER,	fs },
		{ GL_NONE, NULL }
	};

	return LoadShaders(shaders);
}

// Set shader
void Tri_Mesh::setShader(char* vert, char* frag)
{
	ShaderInfo shaders[] =
	{
		{ GL_VERTEX_SHADER,		vert },
		{ GL_FRAGMENT_SHADER,	frag },
		{ GL_NONE, NULL }
	};
	shaderProgram = LoadShaders(shaders);
}

// Load Obj to buffer
void Tri_Mesh::load2Buffer()
{
	// Get vertices form mesh
	vertices.clear();
	verticesIdx.clear();
	for (OMT::VIter v_it = vertices_begin(); v_it != vertices_end(); ++v_it)
	{
#ifdef TEST
		std::cout << "Vertex" << *v_it << ": ";
#endif // TEST
		double *vertexMesh = point(v_it).data();
#ifdef TEST
		std::cout << vertexMesh[0] << ", " << vertexMesh[1] << ", " << vertexMesh[2] << std::endl;
#endif // TEST
		vec3 vertexGLM(vertexMesh[0], vertexMesh[1], vertexMesh[2]);
		vertices.push_back(vertexGLM);

		verticesIdx.push_back(vec3((float)v_it->idx()));
	}
	verticesIdxSize = verticesIdx.size();
	std::cout << "Vertex Number: " << vertices.size() << std::endl;

	// Set mesh's face vertex indices
	std::vector<GLfloat> faceIndicesVec;
	faceIndicesVec.clear();
	faceIndex.clear();
	faceVertexIndex.clear();
	for (OMT::FIter f_it = faces_begin(); f_it != faces_end(); ++f_it)
	{
		faceIndicesVec.push_back((float)(f_it->idx()));
#ifdef TEST
		std::cout << "Face" << *f_it << ": ";
#endif // TEST
		for (OMT::FVIter fv_it = fv_begin(f_it); fv_it != fv_end(f_it); ++fv_it) 
		{
#ifdef TEST
			std::cout << *fv_it << " ";
#endif // TEST
			faceVertexIndex.push_back(fv_it->idx());
			faceIndex.push_back(vec3((float)(f_it->idx())));
		}
#ifdef TEST
		std::cout << std::endl;
#endif // TEST
	}
	faceIndices = new GLfloat[faceIndicesVec.size()];
	for (int u = 0; u < faceIndicesVec.size(); u++)
		faceIndices[u] = faceIndicesVec[u];
	faceVertexSize = faceVertexIndex.size();
	std::cout << "Face Number: " << faceIndicesVec.size() << "\n\n";

	// Set mesh's edge vertex indices
	edgeVertexIndex.clear();
	for (OMT::EIter e_it = edges_begin(); e_it != edges_end(); ++e_it)
	{
#ifdef TEST
		std::cout << "Edge" << *e_it << ": ";
#endif // TEST	
		GLuint from;
		from = from_vertex_handle(halfedge_handle(e_it, 0)).idx();
		GLuint to;
		to = to_vertex_handle(halfedge_handle(e_it, 0)).idx();
#ifdef TEST
		std::cout << from << " -> " << to << std::endl;
#endif // TEST
		edgeVertexIndex.push_back(to);
		edgeVertexIndex.push_back(from);
	}
	edgeVertexSize = edgeVertexIndex.size();
	
	if (vertices.size() <= 0 || verticesIdx.size() <= 0 || faceIndex.size() <= 0 || faceVertexIndex.size() <= 0 || edgeVertexIndex.size() <= 0)
		return;

	// Point VBO
	glGenBuffers(1, &pointVBO);
	glBindBuffer(GL_ARRAY_BUFFER, pointVBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3), &vertices[0], GL_STATIC_DRAW);
	verticesSize = vertices.size();

	// Point ID VBO
	glGenBuffers(1, &pointIdxVBO);
	glBindBuffer(GL_ARRAY_BUFFER, pointIdxVBO);
	glBufferData(GL_ARRAY_BUFFER, verticesIdx.size() * sizeof(vec3), &verticesIdx[0], GL_STATIC_DRAW);
	
	// Face ID VBO
	glGenBuffers(1, &faceIdxVBO);
	glBindBuffer(GL_ARRAY_BUFFER, faceIdxVBO);
	glBufferData(GL_ARRAY_BUFFER, faceIndex.size() * sizeof(vec3), &faceIndex[0], GL_STATIC_DRAW);

	// UV VBO
	glGenBuffers(1, &texCoordVBO);
	glBindBuffer(GL_ARRAY_BUFFER, texCoordVBO);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(vec2), NULL, GL_STATIC_DRAW);
	uvsSize = uvs.size();

	// Normal VBO
	glGenBuffers(1, &normalVBO);
	glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(vec3), NULL, GL_STATIC_DRAW);
	normalsSize = normals.size();

	// Point EBO
	glGenBuffers(1, &pointEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pointEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, faceVertexIndex.size() * sizeof(GLint), &faceVertexIndex[0], GL_STATIC_DRAW);
	
	// Edge EBO
	glGenBuffers(1, &edgeEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, edgeEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, edgeVertexIndex.size() * sizeof(GLint), &edgeVertexIndex[0], GL_STATIC_DRAW);

	std::vector<Tri_Mesh::Normal> normals;
	normals.reserve(n_vertices());
	for (Tri_Mesh::VertexIter v_it = vertices_begin(); v_it != vertices_end(); ++v_it) {
		normals.push_back(normal(*v_it));
	}
}

void Tri_Mesh::load2BufferPatch(void) {
	if (edgeConnectivity.size() <= 0)
		return;

	// Get edge from patch
	std::vector<vec3> edges;
	for (int e = 0; e < edgeConnectivity.size(); e++)
		edges.push_back(vec3(edgeConnectivity[e][0] * 2 - 1, edgeConnectivity[e][1] * 2 - 1, -2.0));
	edges.push_back(vec3(edgeConnectivity[0][0] * 2 - 1, edgeConnectivity[0][1] * 2 - 1, -2.0));

	// Get vertices from patch
	vertices.clear();
	for (std::vector<Tri_Mesh::TexCoord2D>::iterator it_v = texCoords.begin(); it_v != texCoords.end(); ++it_v) {
		vertices.push_back(vec3(((*it_v)[0] * 2.0) - 1.0, ((*it_v)[1] * 2.0) - 1.0, -2.0));
		//std::cout << "Original on text: " << (*it_v)[0] << " " << (*it_v)[1] << std::endl;
		//std::cout << "Coordinate on shader: " << ((*it_v)[0] * 2.0) - 1.0 << " " << ((*it_v)[1] * 2.0) - 1.0 << std::endl;
	}

	if (vertices.size() <= 0 || edges.size() <= 0)
		return;

	// Point VBO
	glGenBuffers(1, &patchPointVBO);
	glBindBuffer(GL_ARRAY_BUFFER, patchPointVBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	patchVerticesSize = vertices.size();
	//std::cout << "Patch point number: " << vertices.size() << std::endl;

	// Edge VBO
	glGenBuffers(1, &patchEdgeVBO);
	glBindBuffer(GL_ARRAY_BUFFER, patchEdgeVBO);
	glBufferData(GL_ARRAY_BUFFER, edges.size() * sizeof(vec3), &edges[0], GL_STATIC_DRAW);
	patchEdgesSize = edges.size();
	//std::cout << "Patch edge number: " << edges.size() << std::endl;
}

// Draw solid face
void Tri_Mesh::Render_Solid(mat4 projection, mat4 view, OMT::FIter chosenFace_iter, CurrentPicking picking) {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	// VAO
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pointEBO);
	glBindTexture(GL_TEXTURE_2D, textureID);
	// Set model matrix
	mat4 model = mat4(1.0f);

	GLuint offset[3] = { 0,0,0 };//offset for vertices , uvs , normals

	//update data to pointVBO for MVP
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "ModelMatrix"), 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "ViewMatrix"), 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "ProjectionMatrix"), 1, GL_FALSE, &projection[0][0]);
	if(picking == CurrentPicking::PICK_POINT)
		glUniform1i(glGetUniformLocation(shaderProgram, "Part"), 4);
	else
		glUniform1i(glGetUniformLocation(shaderProgram, "Part"), 0);
	if (picking == CurrentPicking::PICK_FACE) {
		//for (OMT::FVIter fv_it = fv_begin(chosenFace_iter); fv_it != fv_end(chosenFace_iter); ++fv_it) {
		//	glUniform3f(glGetUniformLocation(shaderProgram, "ChosenFacePoint1"), point(fv_it)[0], point(fv_it)[1], point(fv_it)[2]);
		//	glUniform1f(glGetUniformLocation(shaderProgram, "ChosenFaceIdx"), (float)(chosenFace_iter->idx()));
		//}
	}
	else {
		glUniform3f(glGetUniformLocation(shaderProgram, "ChosenFacePoint1"), -10.0, -10.0, -10.0);
		glUniform3f(glGetUniformLocation(shaderProgram, "ChosenFacePoint2"), -10.0, -10.0, -10.0);
		glUniform3f(glGetUniformLocation(shaderProgram, "ChosenFacePoint3"), -10.0, -10.0, -10.0);
		glUniform1f(glGetUniformLocation(shaderProgram, "ChosenFaceIdx"), -10.0);
	}

	// 1rst attribute buffer : vertices
	//glBindBuffer(GL_ARRAY_BUFFER, pointVBO);
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0,				//location
	//	3,				//vec3
	//	GL_FLOAT,			//type
	//	GL_FALSE,			//not normalized
	//	0,				//strip
	//	(void*)offset[0]);//buffer offset
	//offset[0] += verticesSize * sizeof(vec3);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);//location 1 :vec2 UV
	glBindBuffer(GL_ARRAY_BUFFER, faceIdxVBO);
	glVertexAttribPointer(1,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)offset[1]);
	offset[1] += faceIndex.size() * sizeof(vec3);

	// 2nd attribute buffer : UVs
	
	if (texCoords.size() > 0) {
		glDeleteBuffers(1, &texCoordVBO);
		glGenBuffers(1, &texCoordVBO);
		glBindBuffer(GL_ARRAY_BUFFER, texCoordVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Tri_Mesh::TexCoord2D) * texCoords.size(), &texCoords[0], GL_STATIC_DRAW);
		//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
		//glEnableVertexAttribArray(2);

		glEnableVertexAttribArray(2);//location 1 :vec2 UV
		glBindBuffer(GL_ARRAY_BUFFER, texCoordVBO);
		glVertexAttribPointer(2,
			2,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)offset[2]);
		offset[2] += uvsSize * sizeof(vec2);
	}

	// 3rd attribute buffer : normals
	/*glEnableVertexAttribArray(2);//location 2 :vec3 Normal
	glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
	glVertexAttribPointer(2,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)offset[2]);
	offset[2] += normalsSize * sizeof(vec3);*/
	glDrawElements(GL_TRIANGLES, faceVertexIndex.size(), GL_UNSIGNED_INT, 0);

	/*int vertexIDoffset = 0;//glVertexID's offset

	vec3 Ks = vec3(1, 1, 1);//because .mtl excluding specular , so give it here.
	for (int j = 0; j < mtls[i].size(); j++)
	{//
		mtlname = mtls[i][j];
		//find the material diffuse color in map:KDs by material name.
		glUniform3fv(M_KdID, 1, &KDs[mtlname][0]);
		glUniform3fv(M_KsID, 1, &Ks[0]);
		//          (primitive   , glVertexID base , vertex count    )
		glDrawArrays(GL_TRIANGLES, vertexIDoffset, triangleFaces[i][j + 1] * 3);
		//we draw triangles by giving the glVertexID base and vertex count is face count*3
		vertexIDoffset += triangleFaces[i][j + 1] * 3;//glVertexID's base offset is face count*3
	}//end for loop for draw one part of the robot	*/
}

// Draw solid face and wire
void Tri_Mesh::Render_SolidWireframe(mat4 projection, mat4 view)
{
	// VAO
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	if (textureID)
		glBindTexture(GL_TEXTURE_2D, textureID);

	// Set model matrix
	mat4 model = mat4(1.0f);

	GLuint offset[3] = { 0,0,0 };//offset for vertices , uvs , normals

	//update data to pointVBO for MVP
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "ModelMatrix"), 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "ViewMatrix"), 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "ProjectionMatrix"), 1, GL_FALSE, &projection[0][0]);

	// 1rst attribute buffer : vertices
	glBindBuffer(GL_ARRAY_BUFFER, pointVBO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,				//location
		3,				//vec3
		GL_FLOAT,			//type
		GL_FALSE,			//not normalized
		0,				//strip
		(void*)offset[0]);//buffer offset
	offset[0] += verticesSize * sizeof(vec3);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(2);//location 1 :vec2 UV
	glBindBuffer(GL_ARRAY_BUFFER, texCoordVBO);
	glVertexAttribPointer(2,
		2,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)offset[2]);
	offset[2] += uvsSize * sizeof(vec2);

	// 3rd attribute buffer : normals
	/*glEnableVertexAttribArray(2);//location 2 :vec3 Normal
	glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
	glVertexAttribPointer(2,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)offset[2]);
	offset[2] += normalsSize * sizeof(vec3);*/
	glDrawElements(GL_TRIANGLES, faceVertexIndex.size(), GL_UNSIGNED_INT, &faceVertexIndex[0]);

	/*int vertexIDoffset = 0;//glVertexID's offset 

	vec3 Ks = vec3(1, 1, 1);//because .mtl excluding specular , so give it here.
	for (int j = 0; j < mtls[i].size(); j++) 
	{//
		mtlname = mtls[i][j];
		//find the material diffuse color in map:KDs by material name.
		glUniform3fv(M_KdID, 1, &KDs[mtlname][0]);
		glUniform3fv(M_KsID, 1, &Ks[0]);
		//          (primitive   , glVertexID base , vertex count    )
		glDrawArrays(GL_TRIANGLES, vertexIDoffset, triangleFaces[i][j + 1] * 3);
		//we draw triangles by giving the glVertexID base and vertex count is face count*3
		vertexIDoffset += triangleFaces[i][j + 1] * 3;//glVertexID's base offset is face count*3
	}//end for loop for draw one part of the robot	*/
}

// Draw wire
void Tri_Mesh::Render_Wireframe(mat4 projection, mat4 view)
{
	// VAO
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, edgeEBO);
	if (textureID)
		glBindTexture(GL_TEXTURE_2D, textureID);
	// Set model matrix
	mat4 model = mat4(1.0f);

	GLuint offset[3] = { 0,0,0 };//offset for vertices , uvs , normals

	//update data to pointVBO for MVP
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "ModelMatrix"), 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "ViewMatrix"), 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "ProjectionMatrix"), 1, GL_FALSE, &projection[0][0]);
	glUniform1i(glGetUniformLocation(shaderProgram, "Part"), 2);

	// 1rst attribute buffer : vertices
	glBindBuffer(GL_ARRAY_BUFFER, pointVBO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,				//location
		3,				//vec3
		GL_FLOAT,			//type
		GL_FALSE,			//not normalized
		0,				//strip
		(void*)offset[0]);//buffer offset
	offset[0] += verticesSize * sizeof(vec3);

	// 2nd attribute buffer : UVs
	/*
	glEnableVertexAttribArray(2);//location 1 :vec2 UV
	glBindBuffer(GL_ARRAY_BUFFER, texCoordVBO);
	glVertexAttribPointer(2,
		2,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)offset[2]);
	offset[2] += uvsSize * sizeof(vec2);
	*/

	// 3rd attribute buffer : normals
	/*glEnableVertexAttribArray(2);//location 2 :vec3 Normal
	glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
	glVertexAttribPointer(2,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)offset[2]);
	offset[2] += normalsSize * sizeof(vec3);*/
	glLineWidth(3.2);
	glDrawElements(GL_LINES, edgeVertexIndex.size() , GL_UNSIGNED_INT, 0);
	/*int vertexIDoffset = 0;//glVertexID's offset

	vec3 Ks = vec3(1, 1, 1);//because .mtl excluding specular , so give it here.
	for (int j = 0; j < mtls[i].size(); j++)
	{//
		mtlname = mtls[i][j];
		//find the material diffuse color in map:KDs by material name.
		glUniform3fv(M_KdID, 1, &KDs[mtlname][0]);
		glUniform3fv(M_KsID, 1, &Ks[0]);
		//          (primitive   , glVertexID base , vertex count    )
		glDrawArrays(GL_TRIANGLES, vertexIDoffset, triangleFaces[i][j + 1] * 3);
		//we draw triangles by giving the glVertexID base and vertex count is face count*3
		vertexIDoffset += triangleFaces[i][j + 1] * 3;//glVertexID's base offset is face count*3
	}//end for loop for draw one part of the robot	*/
}

void Tri_Mesh::Render_Point(mat4 projection, mat4 view) {
	std::vector<float> boundaryIdcsVec;
	GLfloat* boundaryIdcs = NULL;

	// find the boundary points
	for (OMT::VIter v_it = vertices_begin(); v_it != vertices_end(); ++v_it) {
		if (is_boundary(v_it.handle())) {
			boundaryIdcsVec.push_back(v_it->idx());
		}
	}

	boundaryIdcs = new GLfloat[boundaryIdcsVec.size()];
	for (int k = 0; k < boundaryIdcsVec.size(); k++)
		boundaryIdcs[k] = boundaryIdcsVec[k];

	// VAO
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	if (textureID)
		glBindTexture(GL_TEXTURE_2D, textureID);

	// Set model matrix
	mat4 model = mat4(1.0f);

	GLuint offset[3] = { 0,0,0 };//offset for vertices , uvs , normals

	//update data to pointVBO for MVP
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "ModelMatrix"), 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "ViewMatrix"), 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "ProjectionMatrix"), 1, GL_FALSE, &projection[0][0]);
	glUniform1i(glGetUniformLocation(shaderProgram, "Part"), 1);
	glUniform1f(glGetUniformLocation(shaderProgram, "ChosenPointIdx"), -10.0);
	glUniform1i(glGetUniformLocation(shaderProgram, "OneRingSize"), boundaryIdcsVec.size());
	glUniform1fv(glGetUniformLocation(shaderProgram, "OneRingIndices"), boundaryIdcsVec.size(), boundaryIdcs);

	// 1rst attribute buffer : vertices
	glBindBuffer(GL_ARRAY_BUFFER, pointVBO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,				//location
		3,				//vec3
		GL_FLOAT,			//type
		GL_FALSE,			//not normalized
		0,				//strip
		(void*)offset[0]);//buffer offset
	offset[0] += verticesSize * sizeof(vec3);

	glBindBuffer(GL_ARRAY_BUFFER, pointIdxVBO);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1,				//location
		3,				//vec3
		GL_FLOAT,			//type
		GL_FALSE,			//not normalized
		0,				//strip
		(void*)offset[1]);//buffer offset
	offset[1] += verticesIdx.size() * sizeof(vec3);

	/*
	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(2);//location 1 :vec2 UV
	glBindBuffer(GL_ARRAY_BUFFER, texCoordVBO);
	glVertexAttribPointer(2,
		2,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)offset[2]);
	offset[2] += uvsSize * sizeof(vec2);
	*/

	// 3rd attribute buffer : normals
	/*glEnableVertexAttribArray(2);//location 2 :vec3 Normal
	glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
	glVertexAttribPointer(2,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)offset[2]);
	offset[2] += normalsSize * sizeof(vec3);*/

	glPointSize(14);
	glDrawArrays(GL_POINTS, 0, n_vertices());
}

void Tri_Mesh::Render_Point(mat4 projection, mat4 view, OMT::VIter chosenPoint_iter, CurrentPicking picking) {
	std::vector<float> oneRingIdcsVec;
	GLfloat* oneRingIdcs = NULL;

	if (picking == CurrentPicking::PICK_POINT) {
		// find the one ring
		for (OMT::VVIter vv_it = vv_iter(chosenPoint_iter); vv_it; ++vv_it)
			oneRingIdcsVec.push_back((float)(vv_it->idx()));

		oneRingIdcs = new GLfloat[oneRingIdcsVec.size()];
		for (int k = 0; k < oneRingIdcsVec.size(); k++)
			oneRingIdcs[k] = oneRingIdcsVec[k];
	}
	

	// VAO
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	if (textureID)
		glBindTexture(GL_TEXTURE_2D, textureID);

	// Set model matrix
	mat4 model = mat4(1.0f);

	GLuint offset[3] = { 0,0,0 };//offset for vertices , uvs , normals

	//update data to pointVBO for MVP
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "ModelMatrix"), 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "ViewMatrix"), 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "ProjectionMatrix"), 1, GL_FALSE, &projection[0][0]);
	glUniform1i(glGetUniformLocation(shaderProgram, "Part"), 1);
	if (picking == CurrentPicking::PICK_POINT && oneRingIdcs != NULL) {
		glUniform1f(glGetUniformLocation(shaderProgram, "ChosenPointIdx"), (float)(chosenPoint_iter->idx()));
		glUniform1i(glGetUniformLocation(shaderProgram, "OneRingSize"), oneRingIdcsVec.size());
		glUniform1fv(glGetUniformLocation(shaderProgram, "OneRingIndices"), oneRingIdcsVec.size(), oneRingIdcs);
	}
	else {
		glUniform1f(glGetUniformLocation(shaderProgram, "ChosenPointIdx"), -10.0);
		glUniform1i(glGetUniformLocation(shaderProgram, "OneRingSize"), 0);
	}

	// 1rst attribute buffer : vertices
	glBindBuffer(GL_ARRAY_BUFFER, pointVBO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,				//location
		3,				//vec3
		GL_FLOAT,			//type
		GL_FALSE,			//not normalized
		0,				//strip
		(void*)offset[0]);//buffer offset
	offset[0] += verticesSize * sizeof(vec3);

	glBindBuffer(GL_ARRAY_BUFFER, pointIdxVBO);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1,				//location
		3,				//vec3
		GL_FLOAT,			//type
		GL_FALSE,			//not normalized
		0,				//strip
		(void*)offset[1]);//buffer offset
	offset[1] += verticesIdx.size() * sizeof(vec3);

	/*
	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(2);//location 1 :vec2 UV
	glBindBuffer(GL_ARRAY_BUFFER, texCoordVBO);
	glVertexAttribPointer(2,
		2,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)offset[2]);
	offset[2] += uvsSize * sizeof(vec2);
	*/

	// 3rd attribute buffer : normals
	/*glEnableVertexAttribArray(2);//location 2 :vec3 Normal
	glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
	glVertexAttribPointer(2,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)offset[2]);
	offset[2] += normalsSize * sizeof(vec3);*/

	glPointSize(14);
	glDrawArrays(GL_POINTS, 0, n_vertices());
}

void Tri_Mesh::Render_Texture(mat4 projection, mat4 view) {

	if (has_vertex_texcoords2D()) {
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		if (textureID)
			glBindTexture(GL_TEXTURE_2D, textureID);

		// Set model matrix
		mat4 model = mat4(1.0f);

		GLuint offset[3] = { 0,0,0 };//offset for vertices , uvs , normals

		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "ModelMatrix"), 1, GL_FALSE, &model[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "ViewMatrix"), 1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "ProjectionMatrix"), 1, GL_FALSE, &projection[0][0]);
		glUniform1i(glGetUniformLocation(shaderProgram, "Part"), 5);

		glBindBuffer(GL_ARRAY_BUFFER, pointVBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, pointIdxVBO);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1,				//location
			3,				//vec3
			GL_FLOAT,			//type
			GL_FALSE,			//not normalized
			0,				//strip
			(void*)offset[1]);//buffer offset

		glBindBuffer(GL_ARRAY_BUFFER, texCoordVBO);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(2);

		glMultiDrawElements(GL_TRIANGLES, &elemCount[0], GL_UNSIGNED_INT, (const GLvoid **)&fvIDsPtr[0], elemCount.size());

		glUseProgram(0);
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	return;
}

void Tri_Mesh::Render_PatchWire(mat4 projection, mat4 view) {
	// VAO
	glUseProgram(patchProgram);
	glBindVertexArray(VAOpatch);

	// Set model matrix
	mat4 model = mat4(1.0f);

	GLuint offset[3] = { 0,0,0 };//offset for vertices , uvs , normals

	//update data to pointVBO for MVP
	glUniformMatrix4fv(glGetUniformLocation(patchProgram, "ModelMatrix"), 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(patchProgram, "ViewMatrix"), 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(patchProgram, "ProjectionMatrix"), 1, GL_FALSE, &projection[0][0]);
	//glUniform1i(glGetUniformLocation(patchProgram, "Part"), 2);

	// 1rst attribute buffer : vertices
	glBindBuffer(GL_ARRAY_BUFFER, patchEdgeVBO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,				//location
		3,				//vec3
		GL_FLOAT,			//type
		GL_FALSE,			//not normalized
		0,				//strip
		(void*)offset[0]);//buffer offset
	offset[0] += verticesSize * sizeof(vec3);

	glLineWidth(1.5);
	//glDrawElements(GL_LINES, edgeVertexIndex.size(), GL_UNSIGNED_INT, 0);
	glDrawArrays(GL_LINES, 0, patchEdgesSize);
}

void Tri_Mesh::Render_PatchPoint(mat4 projection, mat4 view) {
	//std::cout << to_string(projection) << std::endl << to_string(view) << std::endl;
	// VAO
	glUseProgram(patchProgram);
	glBindVertexArray(VAOpatch);

	// Set model matrix
	mat4 model = mat4(1.0f);

	GLuint offset[3] = { 0,0,0 };//offset for vertices , uvs , normals

	//update data to pointVBO for MVP
	glUniformMatrix4fv(glGetUniformLocation(patchProgram, "ModelMatrix"), 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(patchProgram, "ViewMatrix"), 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(patchProgram, "ProjectionMatrix"), 1, GL_FALSE, &projection[0][0]);
	//glUniform1i(glGetUniformLocation(shaderProgram, "Part"), 1);

	// 1rst attribute buffer : vertices
	glBindBuffer(GL_ARRAY_BUFFER, patchPointVBO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,				//location
		3,				//vec3
		GL_FLOAT,			//type
		GL_FALSE,			//not normalized
		0,				//strip
		(void*)offset[0]);//buffer offset
	offset[0] += verticesSize * sizeof(vec3);

	glPointSize(10);
	glDrawArrays(GL_POINTS, 0, patchVerticesSize);
}

// Read file
bool ReadFile(std::string _fileName,Tri_Mesh *_mesh)
{
	bool isRead = false;
	OpenMesh::IO::Options opt;
	if ( OpenMesh::IO::read_mesh(*_mesh, _fileName, opt) )
	{
		//read mesh from filename OK!
		isRead = true;
	}
	if(isRead)
	{
		// If the file did not provide vertex normals and mesh has vertex normal ,then calculate them
		if (!opt.check( OpenMesh::IO::Options::VertexNormal ) && _mesh->has_vertex_normals())
		{
			_mesh->update_normals();
		}
	}
	return isRead;
}
// Save file
bool SaveFile(std::string _fileName, Tri_Mesh *_mesh)
{
	bool isSave = false;
	if (OpenMesh::IO::write_mesh(*_mesh, _fileName))
	{
		isSave = true;
	}
	return isSave;
}

void Tri_Mesh::Parameterization(float uvRotateAngle, BoundaryStyle bs, WeightCalculatingMethod weightCalcMethod) {
	texCoords.clear();
	edgeConnectivity.clear();

	if (selectedFace.size() <= 0)
		return;

	std::sort(selectedFace.begin(), selectedFace.end());

	OpenMesh::HPropHandleT<double> heWeight;
	OpenMesh::VPropHandleT<int> row;

	add_property(heWeight, "heWeight");
	add_property(row, "row");
	request_vertex_texcoords2D();

	// Calculate weight
	Tri_Mesh::HalfedgeHandle heh;
	for (Tri_Mesh::EdgeIter e_it = edges_begin(); e_it != edges_end(); ++e_it) {
		if (!is_boundary(*e_it)) {
			GLdouble angle1, angle2, w;
			
			Tri_Mesh::HalfedgeHandle _heh = halfedge_handle(*e_it, 1);
			Tri_Mesh::Point pFrom = point(from_vertex_handle(_heh));
			Tri_Mesh::Point pTo = point(to_vertex_handle(_heh));
			//Tri_Mesh::Point p1 = point(mesh.opposite_vh(_heh));
			//Tri_Mesh::Point p2 = point(mesh.opposite_he_opposite_vh(_heh));
			Tri_Mesh::Point p1 = point(to_vertex_handle(next_halfedge_handle(_heh)));
			Tri_Mesh::Point p2 = point(to_vertex_handle(next_halfedge_handle(opposite_halfedge_handle(_heh))));

			double edgeLen = (pFrom - pTo).length();

			if (weightCalcMethod == WeightCalculatingMethod::WEIGHT_CALC_MEAN_VALUE) {
				// weight from to
				OpenMesh::Vec3d v1 = (OpenMesh::Vec3d)(pTo - pFrom);
				v1.normalize();

				OpenMesh::Vec3d v2 = (OpenMesh::Vec3d)(p1 - pFrom);
				v2.normalize();

				angle1 = std::acos(OpenMesh::dot(v1, v2));

				v2 = (OpenMesh::Vec3d)(p2 - pFrom);
				v2.normalize();

				angle2 = std::acos(OpenMesh::dot(v1, v2));

				w = (std::tan(angle1 / 2.0f) + std::tan(angle2 / 2.0f)) / edgeLen;

				property(heWeight, _heh) = w;

				// weight to from
				v1 = -v1;

				v2 = (OpenMesh::Vec3d)(p1 - pTo);
				v2.normalize();

				angle1 = std::acos(OpenMesh::dot(v1, v2));

				v2 = (OpenMesh::Vec3d)(p2 - pTo);
				v2.normalize();

				angle2 = std::acos(OpenMesh::dot(v1, v2));

				w = (std::tan(angle1 / 2.0f) + std::tan(angle2 / 2.0f)) / edgeLen;

				property(heWeight, opposite_halfedge_handle(_heh)) = w;
			}

			else if (weightCalcMethod == WeightCalculatingMethod::WEIGHT_CALC_COTANGENT) {
				OpenMesh::Vec3d v1 = (OpenMesh::Vec3d)(pTo - p1);
				v1.normalize();

				OpenMesh::Vec3d v2 = (OpenMesh::Vec3d)(pFrom - p1);
				v2.normalize();

				angle1 = std::acos(OpenMesh::dot(v1, v2));

				v1 = (OpenMesh::Vec3d)(pTo - p2);
				v1.normalize();

				v2 = (OpenMesh::Vec3d)(pFrom - p2);
				v2.normalize();

				angle2 = std::acos(OpenMesh::dot(v1, v2));

				double sinVal1 = std::sin(angle1);
				if (sinVal1 == 0.0)
					sinVal1 = 0.00000001;
				double sinVal2 = std::sin(angle2);
				if (sinVal2 == 0.0)
					sinVal2 = 0.00000001;

				w = (std::cos(angle1) / sinVal1) + (std::cos(angle2) / sinVal2);

				property(heWeight, _heh) = w;
				property(heWeight, opposite_halfedge_handle(_heh)) = w;
			}

			else if (weightCalcMethod == WeightCalculatingMethod::WEIGHT_CALC_UNIFORM) {
				property(heWeight, _heh) = 1;
				property(heWeight, opposite_halfedge_handle(_heh)) = 1;
			}
		}

		else {
			if (!heh.is_valid())
				heh = halfedge_handle(e_it.handle(), 1);
		}
	}

	// calculate matrix size
	int count = 0;
	for (Tri_Mesh::VertexIter v_it = vertices_begin(); v_it != vertices_end(); ++v_it) {
		if (is_boundary(*v_it)) {
			property(row, *v_it) = -1;
		}
		else {
			property(row, *v_it) = count++;
		}
	}

	// calculate perimeter
	double perimeter = 0;
	std::vector<double> segLength;
	std::vector<Tri_Mesh::VertexHandle> vhs;
	Tri_Mesh::HalfedgeHandle hehNext = heh;
	do {
		Tri_Mesh::Point from = point(from_vertex_handle(hehNext));
		Tri_Mesh::Point to = point(to_vertex_handle(hehNext));
		perimeter += (from - to).length();

		segLength.push_back(perimeter);
		vhs.push_back(from_vertex_handle(hehNext));

		hehNext = next_halfedge_handle(hehNext);
	} while (heh != hehNext);

	#ifdef Quad

	if (bs == BoundaryStyle::BOUNDARY_STYLE_SQUARE) {
		float rd = ((0 * M_PI / 180.0) + uvRotateAngle);
		float initDist = 0.0;
		Tri_Mesh::TexCoord2D st(0, 0);
		float R = std::sqrt(2.0) / 2.0;
		st[0] = R * cos(rd) + 0.5;
		st[1] = R * sin(rd) + 0.5;

		if (st[0] > 1) {
			st[0] = 1;
			st[1] = tan(rd) / 2 + 0.5;
		}

		if (st[0] < 0) {
			st[0] = 0;
			st[1] = 0.5 - tan(rd) / 2;
		}

		if (st[1] > 1) {
			st[0] = tan(M_PI_2 - rd) / 2 + 0.5;
			st[1] = 1;
		}

		if (st[1] < 0) {
			st[0] = 0.5 - tan(M_PI_2 - rd) / 2;
			st[1] = 0;
		}


		if (uvRotateAngle <= 90)
			initDist = st.length();

		else if (uvRotateAngle <= 180)
			initDist = 1 + st[1];

		else if (uvRotateAngle <= 270)
			initDist = 3 - st[0];

		else
			initDist = 4 - st[1];

		set_texcoord2D(vhs[0], st);
		perimeter /= 4.0;

		for (int i = 1; i < vhs.size(); ++i) {
			double curLen = segLength[i - 1] / perimeter + initDist;

			if (curLen > 4)
				curLen -= 4;

			if (curLen <= 1) {
				st[0] = curLen;
				st[1] = 0;
			}
			else if (curLen <= 2) {
				st[0] = 1;
				st[1] = curLen - 1;
			}
			else if (curLen <= 3) {
				st[0] = 3 - curLen;
				st[1] = 1;
			}
			else {
				st[0] = 0;
				st[1] = 4 - curLen;
			}

			set_texcoord2D(vhs[i], st);
		}
	}

	else if (bs == BoundaryStyle::BOUNDARY_STYLE_CIRCLE) {
		Tri_Mesh::TexCoord2D st(0.0, 0.0);
		set_texcoord2D(vhs[0], Tri_Mesh::TexCoord2D(1.0, 0.5));

		for (int i = 1; i < vhs.size(); ++i) {
			double angle = 2 * M_PI * segLength[i - 1] / perimeter;

			st[0] = (std::cos(angle) + 1) / 2;
			st[1] = (std::sin(angle) + 1) / 2;

			set_texcoord2D(vhs[i], st);
		}
	}

	#else

	Tri_Mesh::TexCoord2D st(0.0, 0.0);

	if (bs == BoundaryStyle::BOUNDARY_STYLE_CIRCLE) {
		st[0] = (std::cos(uvRotateAngle + ((225.0 * M_PI) / 180.0)) + 1) / 2;
		st[1] = (std::sin(uvRotateAngle + ((225.0 * M_PI) / 180.0)) + 1) / 2;
		set_texcoord2D(vhs[0], st);
	}

	else if (bs == BoundaryStyle::BOUNDARY_STYLE_SQUARE) {
		double r = (((uvRotateAngle * 180.0) / M_PI) * 4.0) / 360.0;

		if (r <= 1.0)
			set_texcoord2D(vhs[0], Tri_Mesh::TexCoord2D(r, 0.0));
		else if (r <= 2.0)
			set_texcoord2D(vhs[0], Tri_Mesh::TexCoord2D(1.0, r - 1.0));
		else if (r <= 3.0)
			set_texcoord2D(vhs[0], Tri_Mesh::TexCoord2D(1.0 - (r - 2.0), 1.0));
		else if (r <= 4.0)
			set_texcoord2D(vhs[0], Tri_Mesh::TexCoord2D(0.0, 1.0 - (r - 3.0)));
	}

	for (int i = 1; i < vhs.size(); ++i) {
		if (bs == BoundaryStyle::BOUNDARY_STYLE_CIRCLE) {
			double angle = (2 * M_PI * segLength[i - 1] / perimeter) + uvRotateAngle + ((225.0 * M_PI) / 180.0);

			st[0] = (std::cos(angle) + 1) / 2;
			st[1] = (std::sin(angle) + 1) / 2;
		}

		else if (bs == BoundaryStyle::BOUNDARY_STYLE_SQUARE) {
			double r = (((uvRotateAngle * 180.0) / M_PI) * 4.0) / 360.0;
			double scale = segLength[i - 1] / (perimeter / 4.0) + r;

			if (scale >= 4.0)
				scale -= 4.0;


			if (scale <= 1.0) {
				st[0] = scale;
				st[1] = 0.0;
			}

			else if (scale <= 2.0) {
				st[0] = 1.0;
				st[1] = (scale - 1.0);
			}

			else if (scale <= 3.0) {
				st[0] = 1.0 - (scale - 2.0);
				st[1] = 1.0;
			}

			else {
				st[0] = 0.0;
				st[1] = 1.0 - (scale - 3.0);
			}
		}

		set_texcoord2D(vhs[i], st);
	}

	#endif

	typedef Eigen::SparseMatrix<double> SpMat;

	SpMat A(count, count);
	Eigen::VectorXd BX(count);
	Eigen::VectorXd BY(count);
	Eigen::SimplicialLDLT<Eigen::SparseMatrix<double> > linearSolver;

	BX.setZero();
	BY.setZero();

	// fill matrix
	for (Tri_Mesh::VertexIter v_it = vertices_begin(); v_it != vertices_end(); ++v_it) {
		if (!is_boundary(*v_it)) {
			int i = property(row, *v_it);
			double totalWeight = 0;

			for (Tri_Mesh::VertexVertexIter vv_it = vv_iter(*v_it); vv_it.is_valid(); ++vv_it) {
				Tri_Mesh::HalfedgeHandle _heh = find_halfedge(*v_it, *vv_it);
				double w = property(heWeight, _heh);

				if (is_boundary(*vv_it)) {
					Tri_Mesh::TexCoord2D texCoord = texcoord2D(*vv_it);
					BX[i] += w * texCoord[0];
					BY[i] += w * texCoord[1];
				}
				
				else {
					int j = property(row, *vv_it);
					A.insert(i, j) = -w;
				}

				totalWeight += w;
			}

			A.insert(i, i) = totalWeight;
		}
	}

	A.makeCompressed();

	// solve linear system
	SpMat At = A.transpose();
	linearSolver.compute(At * A);

	Eigen::VectorXd TX = linearSolver.solve(At * BX);
	Eigen::VectorXd TY = linearSolver.solve(At * BY);

	// set texcoord
	for (Tri_Mesh::VertexIter v_it = vertices_begin(); v_it != vertices_end(); ++v_it) {
		if (!is_boundary(*v_it)) {
			int i = property(row, *v_it);
			set_texcoord2D(*v_it, Tri_Mesh::TexCoord2D(TX[i], TY[i]));
		}
	}

	// request vertex texcoord, if not exist
	if (!has_vertex_texcoords2D()) {
		request_vertex_texcoords2D();
		for (Tri_Mesh::VertexIter v_it = vertices_begin(); v_it != vertices_end(); ++v_it) {
			set_texcoord2D(*v_it, Tri_Mesh::TexCoord2D(-1, -1));
		}
	}

	// map texcoord back to origin mesh
	int index = 0;
	for (Tri_Mesh::FaceIter f_it = faces_begin(); f_it != faces_end(); ++f_it) {
		Tri_Mesh::FaceHandle fh = *f_it;
		Tri_Mesh::FaceHandle selectedFace_h = face_handle(selectedFace[index++]);

		Tri_Mesh::FaceVertexIter fv_it = fv_iter(fh);
		Tri_Mesh::FaceVertexIter selectedfv_it = fv_iter(selectedFace_h);

		for (; fv_it.is_valid() && selectedfv_it.is_valid(); ++fv_it, ++selectedfv_it) {
			Tri_Mesh::TexCoord2D texCoord = texcoord2D(*fv_it);
			set_texcoord2D(*selectedfv_it, texCoord);
		}
	}

	LoadTexCoordToShader();

	fvIDsPtr.swap(std::vector<unsigned int*>(selectedFace.size()));
	for (int i = 0; i < fvIDsPtr.size(); ++i) {
		fvIDsPtr[i] = (GLuint*)(selectedFace[i] * 3 * sizeof(GLuint));
	}
	elemCount.swap(std::vector<int>(selectedFace.size(), 3));

	//puts("selectedFace: ");
	//for (std::vector<unsigned int>::iterator it = selectedFace.begin(); it != selectedFace.end(); it++) {
	//	printf("%u, ", *it);
	//}
	//puts("");

	return;
}

void Tri_Mesh::LoadTextures(const char* texPath) {
	// Texture setting
	// /////////////////////////
	// Load texture data from file
	TextureData tdata = Load_png(texPath);

	// Generate empty texture
	glDeleteTextures(1, &textureID);
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Do texture setting
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, tdata.width, tdata.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tdata.data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	///////////////////////////

	return;
}

void Tri_Mesh::LoadTexCoordToShader() {
	if (has_vertex_texcoords2D()) {
		texCoords.clear();
		edgeConnectivity.clear();
		for (Tri_Mesh::VertexIter v_it = vertices_begin(); v_it != vertices_end(); ++v_it) {
			Tri_Mesh::TexCoord2D texCoord = texcoord2D(*v_it);
			// Get Point
			texCoords.push_back(texCoord);

			// Get Edge
			for (Tri_Mesh::VVIter vv_it = vv_iter(*v_it); vv_it.is_valid(); ++vv_it) {
				// from
				edgeConnectivity.push_back(vec2(texCoord[0], texCoord[1]));

				// to
				Tri_Mesh::TexCoord2D thenTexCoord = texcoord2D(*vv_it);
				edgeConnectivity.push_back(vec2(thenTexCoord[0], thenTexCoord[1]));
			}
		}

		glUseProgram(texProgram);
		glBindVertexArray(VAO);

		glGenBuffers(1, &texCoordVBO);
		glBindBuffer(GL_ARRAY_BUFFER, texCoordVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Tri_Mesh::TexCoord2D) * texCoords.size(), &texCoords[0], GL_STATIC_DRAW);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glUseProgram(0);
	}

	return;
}