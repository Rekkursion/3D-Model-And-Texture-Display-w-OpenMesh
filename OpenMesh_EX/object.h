#pragma once
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

class object
{

public:
	object();
	void initialize();
	void setShader(char* vert, char* frag);

	void setPoint(glm::vec3 point);
	void setColor(glm::vec3 color);

	mat4 setTranslate(float x, float y, float z); //移動
	mat4 setRotate(float angle, float x, float y, float z); //旋轉
	mat4 setScale(float x, float y, float z); //縮放
	//T[]*R[]*S[]*M[]
	void render(GLenum type,mat4 modelMatrix,mat4 projectionMatrix, mat4 viewMatrix);
private:
	std::vector<glm::vec3> Points;
	std::vector<glm::vec3> PColors;
	GLuint shaderProgram;
	GLuint VAO;
	GLuint pVBOs; //點座標 buffer
	GLuint pcVBOs; //顏色 buffer

};
