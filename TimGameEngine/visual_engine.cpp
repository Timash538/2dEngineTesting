#include "visual_engine.h"

#include "glew.h"
#include "freeglut.h"
#include "tim_utils.h"
#include "glm/vec3.hpp"
#include <ctime>
#include "object.h"
#include "shader.h"
#include <stdio.h>
#include <iostream>
#include <string>

#include "world_transform.h"


const float HI = 1.0f;
const float LO = -1.0f;
vec3 spd1 = vec3(0.0f, 0.0f, 0.0f);
Agent object;

Shader shader;

VisualEngine::VisualEngine(int argc, char* argv[]) {
	glutInit(&argc, argv);
}

float RandomFloat(float min, float max)
{
	float r = (float)rand() / (float)RAND_MAX;
	return min + r * (max - min);
}

int VisualEngine::Init(int width, int height) {
	//glutSetOption(GLUT_MULTISAMPLE, 8);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(0, 0);

	int window = glutCreateWindow("kek");

	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return 1;
	}

	/*glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_MULTISAMPLE);
	glHint(GL_MULTISAMPLE_FILTER_HINT_NV, GL_FASTEST);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);*/

	//glutSetCursor(GLUT_CURSOR_NONE);
	//glutFullScreen();
	glClearColor(0.3f, 0.3f, 1.0f, 1.0f);

	srand(std::time(0));

	vec3 spd = vec3(0.0f, 0.0f,0.0f);
	vec3 setvec[6] = {vec3(-1.0f,1.0f,0.0f),
					vec3(1.0f,-1.0f,0.0f),
					vec3(1.0f,1.0f,0.0f),
					vec3(-1.0f,1.0f,0.0f),
					vec3(-1.0f,-1.0f,0.0f),
					vec3(1.0f,-1.0f,0.0f)
					 };


	object = Agent(spd1, spd, spd);
	shader = Shader("shader.vs", "shader.fs");
	
	vec3 position = object.getPosition();
	std::cout << position.x;
	std::string pos = "Pos";
	
	glPointSize(30.0f);
	glEnable(GL_POINT_SMOOTH);

}

void VisualEngine::Start() {
	glutMainLoop();
}

void RenderSceneCB();
void MouseCB(int x, int y);

void VisualEngine::RegisterCallbacks() {
	glutIdleFunc(glutPostRedisplay);
	glutDisplayFunc(RenderSceneCB);
	glutPassiveMotionFunc(MouseCB);
}

/////////////////////////////Callbacks/////////////////////////////

void RenderSceneCB() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//object.setVelocity(spd1-object.getPosition());
	object.setAcceleration(spd1-object.getPosition());
	object.Update();
	object.Draw(shader);
	std::cout << object.getPosition().x << " " << object.getPosition().y << std::endl;
	glutPostRedisplay();
	glutSwapBuffers();
}

void MouseCB(int x, int y) {
	spd1 = vec3(((float)-1.0f+(float)x/400), ((float)1.0f-(float)y/400), 0.0f);
}
