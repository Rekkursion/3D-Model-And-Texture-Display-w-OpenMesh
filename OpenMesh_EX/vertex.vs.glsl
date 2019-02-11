// ADS Point lighting Shader
// Vertex Shader
// Richard S. Wright Jr.
// OpenGL SuperBible
#version 430

layout(location = 0) in vec3 Position;
layout(location = 1) in vec3 Index;
layout(location = 2) in vec2 vertexUV;

//layout(location = 2) in vec3 vertexNormal;

vec3 vLightPosition = vec3(0,10,50);

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
uniform int Part;
uniform mat4 UvRotateMatrix;

// Color to fragment program
out vec3 vVaryingNormal;
out vec3 vVaryingLightDir;
out vec2 UV;
flat out int PartInfo;
flat out vec3 Pos;
flat out vec3 Idx;

void main(void)
{
	mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
	mat4 MV = ViewMatrix * ModelMatrix;
	PartInfo = Part;
	Pos = Position;
	Idx = Index;
	
    // Get surface normal in eye coordinates
	//mat3 normalMatrix = mat3(MV);//normal matrix is MV matrix's 3*3 excluding 'w' 
    //vVaryingNormal = normalMatrix * vertexNormal;
	//vVaryingNormal = normalMatrix;

    // Get vertex position in eye coordinates
    //vec4 vPosition4 = MV * vec4(Position, 1);
    //vec3 vPosition3 = vPosition4.xyz / vPosition4.w;

    // Get vector to light source
    //vVaryingLightDir = normalize(vLightPosition - vPosition3);

	//UV = (UvRotateMatrix * vec4(vertexUV, 0.0, 1.0)).xy;
	UV = vertexUV;
    // Don't forget to transform the geometry!
	if(PartInfo == 6) {
		gl_Position = MVP * vec4(UV, 1.0, 1.0);
	}
	else
		gl_Position = MVP * vec4(Position, 1.0);
}
