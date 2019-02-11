#version 410

layout(location = 0) in vec2 position;
//layout(location = 1) in vec2 texcoord;
//out vec2 coord;

uniform mat4 ModelMat;
uniform mat4 ViewMat;
uniform mat4 ProjectionMat;

const vec3[] points = vec3[5](vec3(-0.5, -0.5, -0.5), vec3(0.5, -0.5, -0.5), vec3(-0.5, -0.5, 0.5), vec3(0.5, -0.5, 0.5), vec3(0.0, 0.5, 0.0));

void main()
{
	mat4 MVP = ProjectionMat * ViewMat * ModelMat;
	//gl_Position = MVP * vec4(position, 0.0, 1.0);
	gl_Position = MVP * vec4(points[gl_VertexID], 1.0);
	//coord = texcoord;
}