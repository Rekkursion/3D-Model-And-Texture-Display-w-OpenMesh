// ADS Point lighting Shader
// Fragment Shader
// Richard S. Wright Jr.
// OpenGL SuperBible

// Normal

#version 430

uniform sampler2D tex;

#define MAX_ONE_RING_SIZE	150

/*struct MaterialInfo{
	vec3 Ka;
	vec3 Kd;
	vec3 Ks;
};*/

out vec4 vFragColor;

//lighting color
vec4    ambientColor = vec4(0.941,0.901,0.509,1);
vec4    diffuseColor = vec4(0.8,0.8,0.8,1);   
vec4    specularColor = vec4(1,1,1,1);

uniform float ChosenPointIdx;
uniform int OneRingSize;
uniform float OneRingIndices[MAX_ONE_RING_SIZE];
uniform float ChosenFaceIdx;
uniform vec3 ChosenFacePoint1;
uniform vec3 ChosenFacePoint2;
uniform vec3 ChosenFacePoint3;

in vec3 vVaryingNormal;
in vec3 vVaryingLightDir;
in vec2 UV;
flat in int PartInfo;
flat in vec3 Pos;
flat in vec3 Idx;
flat in vec3 OneRingIdx;
float Shininess = 128.0;//for material specular

void main(void)
{ 
    // Dot product gives us diffuse intensity
    float diff = max(0.0, dot(normalize(vVaryingNormal),
					normalize(vVaryingLightDir)));

    // Multiply intensity by diffuse color, force alpha to 1.0
    //vFragColor = diff * diffuseColor*vec4(Material.Kd,1);
	vFragColor = diff * diffuseColor;

    // Add in ambient light
    vFragColor += ambientColor;


    // Specular Light
    vec3 vReflection = normalize(reflect(-normalize(vVaryingLightDir),
								normalize(vVaryingNormal)));//反射角
    float spec = max(0.0, dot(normalize(vVaryingNormal), vReflection));
    if(diff != 0) {
		spec = pow(spec, Shininess);
		//vFragColor += specularColor*vec4(Material.Ka,1)*spec;
		vFragColor += specularColor * spec;
    }
	
	
	// Faces
	if(PartInfo == 0 || PartInfo == 4) {
		float dis1 = ((ChosenFacePoint1.x - Pos.x) * (ChosenFacePoint1.x - Pos.x)) + ((ChosenFacePoint1.y - Pos.y) * (ChosenFacePoint1.y - Pos.y)) + ((ChosenFacePoint1.z - Pos.z) * (ChosenFacePoint1.z - Pos.z));
		float dis2 = ((ChosenFacePoint2.x - Pos.x) * (ChosenFacePoint2.x - Pos.x)) + ((ChosenFacePoint2.y - Pos.y) * (ChosenFacePoint2.y - Pos.y)) + ((ChosenFacePoint2.z - Pos.z) * (ChosenFacePoint2.z - Pos.z));
		float dis3 = ((ChosenFacePoint3.x - Pos.x) * (ChosenFacePoint3.x - Pos.x)) + ((ChosenFacePoint3.y - Pos.y) * (ChosenFacePoint3.y - Pos.y)) + ((ChosenFacePoint3.z - Pos.z) * (ChosenFacePoint3.z - Pos.z));
		//if(dis1 <= 0.0001 || dis2 <= 0.0001 || dis3 <= 0.0001)
		/*
		if(dis1 <= 0.0001)
			vFragColor = vec4(0.941, 0.901, 0.509, 1);
		else
			vFragColor = vec4(0.8, 0.8, 0.8, 1);
		*/
			
		if(PartInfo == 0)
			vFragColor = vec4(0.941, 0.901, 0.509, 1);
		else
			vFragColor = vec4(0.8, 0.8, 0.8, 1);
		
		/*
		if(abs(ChosenFaceIdx - Idx.x) <= 0.001)
			vFragColor = vec4(0.941, 0.901, 0.509, 1);
		else
			vFragColor = vec4(0.8, 0.8, 0.8, 1);
		*/
	}
	
	// Points
	else if(PartInfo == 1) {
		if(abs(ChosenPointIdx - Idx.x) <= 0.001)
			vFragColor = vec4(1.0, 0.7, 0.2, 1);
		else {
			bool found = false;
			int k;
			for(k = 0; k < OneRingSize; k++) {
				if(abs(OneRingIndices[k] - Idx.x) <= 0.001) {
					vFragColor = vec4(0.4, 0.3, 0.7, 1);
					found = true;
					break;
				}
			}
			
			if(found == false)
				vFragColor = vec4(0.0, 1.0, 0.0, 1);
		}
	}
	
	// Wires
	else if(PartInfo == 2)
		vFragColor = vec4(0.0,0.0,0.0,1);
	
	// Texture
	else if(PartInfo == 5) {
		vFragColor = texture(tex, UV).rgba;
	}
	
	else if(PartInfo == 6) {
		vFragColor = vec4(0.0, 0.0, 0.0, 1);
	}
}
	
    