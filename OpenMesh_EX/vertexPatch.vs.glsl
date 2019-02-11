// Patch
#version 430

layout(location = 0) in vec3 Position;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
//uniform int Part;

//flat out int PartInfo;
	const vec4 vertices[3] = vec4[3] (
			vec4(0.25, -0.25, 0.5, 1.0),
			vec4(-0.25, -0.25, 0.5, 1.0),
			vec4(0.25, 0.25, 0.5, 1.0)
		);
void main(void) 
{ 
	mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
	mat4 MV = ViewMatrix * ModelMatrix;
	//PartInfo = Part;
	//gl_Position = MVP * vertices[gl_VertexID];
	gl_Position = MVP * vec4(Position, 1.0);
}
