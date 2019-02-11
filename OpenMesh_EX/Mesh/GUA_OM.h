#pragma once
#ifndef _GUA_OM_H_
#define _GUA_OM_H_
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <deque>
#include <queue>
#include <stack>
#include <windows.h>
// OpenGL
#include "vgl.h"
// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
// OpenMesh
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>
#include <OpenMesh/Tools/Utils/getopt.h>
// Eigen
#include <../../OpenMesh-5.2/src/Eigen/Sparse>

enum CurrentPicking { PICK_POINT, PICK_FACE, PICK_FACE_FAST_ADD, PICK_NONE };
enum BoundaryStyle { BOUNDARY_STYLE_SQUARE, BOUNDARY_STYLE_CIRCLE };
enum WeightCalculatingMethod { WEIGHT_CALC_UNIFORM, WEIGHT_CALC_COTANGENT, WEIGHT_CALC_MEAN_VALUE };

//#define Quad
//#define TEST

struct Face_InnerAngle
{
	double Vertex_Angle[3];
};

class AllPairHarVal_class
{
public:  
	std::vector<double> Har_val;
};

namespace OMT//OpenMesh Triangle mesh
{
	using namespace std;
	/*----------------------------------------------------------------------*/

	/*�w�q�ϥΪ���ǫשM���ݩ�*/
	struct MyTraits : OpenMesh::DefaultTraits
	{
		// let Point and Normal be a vector made from doubles
		typedef OpenMesh::Vec3d Point;
		typedef OpenMesh::Vec3d Normal;

		// add normal property to vertices and faces
		VertexAttributes(OpenMesh::Attributes::Normal);
		FaceAttributes  (OpenMesh::Attributes::Normal);

		// Already defined in OpenMesh::DefaultTraits
		// HalfedgeAttributes( OpenMesh::Attributes::PrevHalfedge );

		// Uncomment next line to disable attribute PrevHalfedge
		// HalfedgeAttributes( OpenMesh::Attributes::None );
		//
		// or
		//
		// HalfedgeAttributes( 0 );
	};
	/*----------------------------------------------------------------------*/

	/*�w�q�`��type*/
	typedef OpenMesh::TriMesh_ArrayKernelT<MyTraits>	    MyMesh	;
	typedef OpenMesh::Vec3d									Vector3d;	//Vec3D type
	typedef MyMesh::Scalar									Scalar	;	//Scalar type
	typedef MyMesh::Point									Point	;	//Point type
	typedef MyMesh::Normal									Normal	;	//Normal type
	typedef MyMesh::VertexHandle							VHandle	;	//VertexHandle type
	typedef MyMesh::HalfedgeHandle							HEHandle;	//HalfedgeHandle type
	typedef MyMesh::EdgeHandle							    EHandle ;	//edgeHandle type
	typedef MyMesh::FaceHandle								FHandle	;	//FaceHandle type
	//-------------Vertex iterators & circulators-------------
	typedef MyMesh::VertexIter								VIter	;	//VertexIter type
	typedef MyMesh::VertexVertexIter						VVIter	;	//VertexVertexIter type
	typedef MyMesh::VertexEdgeIter							VEIter	;	//VertexEdgeIter type
	typedef MyMesh::VertexFaceIter							VFIter	;	//VertexFaceIter type
	typedef MyMesh::EdgeIter								EIter	;	//EdgeIterT	type
	typedef MyMesh::FaceIter								FIter	;	//FaceIter type
	typedef MyMesh::FaceVertexIter							FVIter	;	//FaceVertexIter type
	typedef MyMesh::FaceEdgeIter							FEIter	;	//FaceEdgeIter type
	typedef MyMesh::FaceFaceIter							FFIter	;	//FaceFaceIter type
	typedef MyMesh::VertexOHalfedgeIter						VOHEIter;	//VertexOutHalfEdge type
	typedef MyMesh::ConstVertexVertexIter					CVVIter	;	//ConstVertexVertexIter type
	/*----------------------------------------------------------------------*/

	/*�w�q�B�~��Ƶ��c*/
	using namespace OpenMesh;
	/*----------------------------------------------------------------------*/

	/*�w�q���O*/
	class Model:public MyMesh
	{
	public:
		Model();//constructor
		~Model();//de-constructor
	};
}
/*======================================================================*/

namespace OMP//OpenMesh Polygonal mesh
{
	using namespace std;
	/*----------------------------------------------------------------------*/

	/*�w�q�ϥΪ���ǫשM���ݩ�*/
	struct MyTraits : OpenMesh::DefaultTraits
	{
		// let Point and Normal be a vector made from doubles
		typedef OpenMesh::Vec3d Point;
		typedef OpenMesh::Vec3d Normal;

		// add normal property to vertices and faces
		VertexAttributes(OpenMesh::Attributes::Normal);
		FaceAttributes  (OpenMesh::Attributes::Normal);

		// Already defined in OpenMesh::DefaultTraits
		// HalfedgeAttributes( OpenMesh::Attributes::PrevHalfedge );

		// Uncomment next line to disable attribute PrevHalfedge
		// HalfedgeAttributes( OpenMesh::Attributes::None );
		//
		// or
		//
		// HalfedgeAttributes( 0 );
	};
	/*----------------------------------------------------------------------*/

	/*�w�q�`��type*/
	typedef OpenMesh::PolyMesh_ArrayKernelT<MyTraits>	    MyMesh	;
	typedef OpenMesh::Vec3d									Vector3d;	//Vec3D type
	typedef MyMesh::Scalar									Scalar	;	//Scalar type
	typedef MyMesh::Point									Point	;	//Point type
	typedef MyMesh::Normal									Normal	;	//Normal type
	typedef MyMesh::VertexHandle							VHandle	;	//VertexHandle type
	typedef MyMesh::HalfedgeHandle							HEHandle;	//HalfedgeHandle type
	typedef MyMesh::EdgeHandle							    EHandle ;	//edgeHandle type
	typedef MyMesh::FaceHandle								FHandle	;	//FaceHandle type
	//-------------Vertex iterators & circulators-------------
	typedef MyMesh::VertexIter								VIter	;	//VertexIter type
	typedef MyMesh::VertexVertexIter						VVIter	;	//VertexVertexIter type
	typedef MyMesh::VertexEdgeIter							VEIter	;	//VertexEdgeIter type
	typedef MyMesh::VertexFaceIter							VFIter	;	//VertexFaceIter type
	typedef MyMesh::EdgeIter								EIter	;	//EdgeIterT	type
	typedef MyMesh::FaceIter								FIter	;	//FaceIter type
	typedef MyMesh::FaceVertexIter							FVIter	;	//FaceVertexIter type
	typedef MyMesh::FaceEdgeIter							FEIter	;	//FaceEdgeIter type
	typedef MyMesh::FaceFaceIter							FFIter	;	//FaceFaceIter type
	typedef MyMesh::VertexOHalfedgeIter						VOHEIter;	//VertexOutHalfEdge type
	typedef MyMesh::ConstVertexVertexIter					CVVIter	;	//ConstVertexVertexIter type
	/*----------------------------------------------------------------------*/

	/*�w�q�B�~��Ƶ��c*/
	using namespace OpenMesh;
	//���w�S�O�e�X������Ƶ��c
	struct sp_f 
	{
		FHandle fh;
		float r, g, b;
	};
	//���w�S�O�e�X���I����Ƶ��c
	struct sp_v 
	{
		VHandle vh;
		float r, g, b;
	};
	//���w�t�~�e�X��m����Ƶ��c
	struct sp_p
	{
		Point pt;
		float r, g, b;
	};
	/*----------------------------------------------------------------------*/
	struct srtPath
	{
		std::vector<OMP::VHandle> path;
	};

	/*�w�q���O*/
	class Model:public MyMesh
	{
		//��Ʀ���
	public:
		MyMesh Mesh;													//OpenMesh instance
	private:
		vector< sp_p > sp_p_list;
		vector< sp_v > sp_v_list;
		vector< sp_f > sp_f_list;
		//�禡����
	public:
		Model();//constructor
		~Model();//de-constructor

		bool ReadFile(std::string _fileName);//Ū��mesh���

		bool SaveFile(std::string _fileName);//�x�smesh���

		void Render_solid();			//solid rendering
		void Render_wireframe();		//wireframe rendering

		void RenderSpecifiedPoint();	//�e�X���w��m���I
		void RenderSpecifiedVertex();	//�e�X���w�����I
		void RenderSpecifiedFace();		//�e�X���w����

		void add_sp_p(Point   _p, float _r, float _g, float _b);//���w�B�~�e�X���I
		void add_sp_v(VHandle _v, float _r, float _g, float _b);//���w�B�~�e�X�����I
		void add_sp_f(FHandle _f, float _r, float _g, float _b);//���w�B�~�e�X����
		void clear_sp_p();//�M���B�~�e�X���I
		void clear_sp_v();//�M���B�~�e�X�����I
		void clear_sp_f();//�M���B�~�e�X����

		VHandle addVertex(Point _p);										//�bmodel�W�W�[�s�����I
		FHandle addFace(VHandle _v0, VHandle _v1, VHandle _v2, VHandle _v3);//�bmodel�W�W�[�s����
		void deleteFace(FHandle _f);										//�bmodel�W�R����
		void deleteFace(VHandle _v0, VHandle _v1, VHandle _v2, VHandle _v3);//�bmodel�W�R����

		bool IsVertexVertex( VHandle _vj, VHandle _vi);	//�ˬd�⳻�I�O�_�۾F

		int quad_subdivision1(int _face_id);//1to4 quadrilateral subdivision
		int quad_subdivision2(int _face_id);//1to9 quadrilateral subdivision

	private:
		int findVertex(Point _p);//��X��m_p�O�_�w�g�����I�s�b
	};
}
/*======================================================================*/
class Tri_Mesh:public OMT::Model
{
public:
	Tri_Mesh()
	{
	
	
	}
	//-------Edit Flag-------//
    bool                                       Delete_Flag;
	
	int                                        Constrain_num;
	int                                        Boundary_num ;
	OMT::VHandle                               start_vh,end_vh;
	OMT::VHandle                               ExtremeVh[2];
	int                                        PatchType;

	std::vector<OMT::VHandle>                  Pluspt      ;
	std::vector<OMT::VHandle>                  Minuspt     ;
	std::vector<OMT::VHandle>                  Extrme_Pt   ;

	static GLuint loadShader(char*, char*);

	void init(void);
	void initPatch(void);
	void load2Buffer();
	void setShader(char*, char*);
	void Render_Solid(mat4, mat4, OMT::FIter, CurrentPicking);
	void Render_SolidWireframe(mat4, mat4);
	void Render_Wireframe(mat4, mat4);
	void Render_Point(mat4, mat4, OMT::VIter, CurrentPicking);
	void Render_Point(mat4, mat4);
	void Render_Texture(mat4, mat4);
	void load2BufferPatch(void);
	void Render_PatchWire(mat4, mat4);
	void Render_PatchPoint(mat4, mat4);
	void Parameterization(float, BoundaryStyle, WeightCalculatingMethod);
	void LoadTextures(const char*);
	void LoadTexCoordToShader();

	std::vector<unsigned int> selectedFace;
	std::set<unsigned int> selectedFaceSet;
	std::vector<TexCoord2D> texCoords;
	std::vector<glm::vec2> edgeConnectivity;

private:
	// Vertex
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> verticesIdx;
	std::vector<GLuint> faceVertexIndex;
	std::vector<glm::vec3> faceIndex;
	GLfloat* faceIndices;
	std::vector<GLuint> edgeVertexIndex;
	// UV
	std::vector<glm::vec2> uvs;
	// Normal
	std::vector<glm::vec3> normals; // Won't be used at the moment.

	// VAO
	GLuint VAO;
	GLuint VAOpatch;
	// VBO
	GLuint pointVBO;
	GLuint pointIdxVBO;
	GLuint faceIdxVBO;
	GLuint uvVBO;
	GLuint normalVBO;
	GLuint texCoordVBO;
	GLuint patchPointVBO;
	GLuint patchEdgeVBO;
	// EBO
	GLuint pointEBO;
	GLuint edgeEBO;
	// Program
	GLuint shaderProgram;
	GLuint texProgram;
	GLuint patchProgram;
	// Texture
	GLuint textureID;

	std::vector<unsigned int*> fvIDsPtr;
	std::vector<int> elemCount;

	int verticesSize = 0;
	int verticesIdxSize = 0;
	int faceVertexSize = 0;
	int edgeVertexSize = 0;
	int uvsSize = 0;
	int normalsSize = 0;
	int patchVerticesSize = 0;
	int patchEdgesSize = 0;

	GLuint M_KaID;
	GLuint M_KdID;
	GLuint M_KsID;

	GLuint nVBO;
	GLuint mVBO;
	GLuint UBO;
	GLuint VBOs;
	GLuint uVBOs;
	GLuint nVBOs;

	GLint MatricesIdx;
	GLuint ModelID;
};

///*======================================================================*/
/*======================================================================*/
bool ReadFile(std::string _fileName, Tri_Mesh *_mesh); //Ū��mesh���
bool SaveFile(std::string _fileName, Tri_Mesh *_mesh); //�x�smesh���
/*��l��view port�]�w�禡*/

#endif

