#include "visual_engine.h"

#include "glew.h"
#include "freeglut.h"
#include "tim_utils.h"
#include "glm/vec3.hpp"
#include <ctime>
#include "agent.h"
#include "shader.h"
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <string>


clock_t c = clock();

Scene scene;
bool prsd = false;
bool mdlprsd = false;
bool flag = false;
bool flagTime = false;
vec2 spd1 = vec2(0.0f, 0.0f);
float aspectRatio = 800.0f/800.0f;
vec2 center = vec2(0.0f, 0.0f);
vec2 center1 = vec2(0.0f, 0.0f);
vec2 center2 = vec2(0.0f, 0.0f);
vec2 cam = vec2(0.0f, 0.0f);
Shader shader;

VisualEngine::VisualEngine(int argc, char* argv[]) {
	glutInit(&argc, argv);
}

void dowork(int i) {
	for (int j = 0; j < scene.agents.size();j++) {
		if (i != j) {
			float x1 = scene.agents[i].getPosition().x;
			float y1 = scene.agents[i].getPosition().y;
			float x2 = scene.agents[j].getPosition().x;
			float y2 = scene.agents[j].getPosition().y;
			float d = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
			if (d < scene.agents[j].getSize()+ scene.agents[i].getSize()) {
				//std::cout << d << std::endl;
				scene.agents[i].setVelocity(((scene.agents[i].getPosition() - scene.agents[j].getPosition()))*0.1f);
				//scene.agents[j].setVelocity((scene.agents[j].getVelocity() - scene.agents[i].getVelocity())/10.0f);
			}
		}
	}
}



void createPoints(int howMuch) {
	vec3 spd = vec3(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < howMuch; i++) {
		float x = RandomFloat(-1000.0f, 1000.0f);
		float y = RandomFloat(-1000.0f, 1000.0f);
		float s = RandomFloat(1.0f, 100.0f);
		vec3 randPos = vec3(x, y, 0.0f);
		scene.agents.push_back(Agent(randPos, vec3(0.0f), vec3(0.0f), s));
	}
}

int VisualEngine::Init(int width, int height) {
	c = clock();
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
	glEnable(GL_BLEND);
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_MULTISAMPLE);
	glHint(GL_MULTISAMPLE_FILTER_HINT_NV, GL_FASTEST);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	//glutSetCursor(GLUT_CURSOR_NONE);
	//glutFullScreen();
	glClearColor(0.3f, 0.3f, 1.0f, 1.0f);

	srand(std::time(0));

	scene = Scene();
	scene.resolution.x = width;
	scene.resolution.y = height;
	scene.space = vec2(2000, 2000);
	shader = Shader("shader.vs", "shader.fs");
	createPoints(500);
	cout << (float)(clock() - c)/CLOCKS_PER_SEC << "s for Init" << endl;
}

void VisualEngine::Start() {
	glutMainLoop();
}

void RenderSceneCB();
void Idle();
void MouseCB(int x, int y);
void MouseCB1(int b, int s, int x, int y);
void MouseCB2(int x, int y);
void KeyCB(unsigned char ch, int x, int y);

void ReshapeCB(int x, int y) {



	vec2 oldSc = scene.resolution;

	scene.resolution = vec2(x, y);
	cout << x << " : " << y << endl;
	cout << oldSc.x << " : " << oldSc.y << endl;

	aspectRatio = scene.resolution.x / scene.resolution.y;
	scene.space *= scene.resolution / oldSc;
	glutReshapeWindow(x, y);
	glViewport(0, 0, x, y);
}

void VisualEngine::RegisterCallbacks() {
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glutIdleFunc(glutPostRedisplay);
	glutDisplayFunc(RenderSceneCB);
	glutPassiveMotionFunc(MouseCB);
	glutMotionFunc(MouseCB2);
	glutMouseFunc(MouseCB1);
	glutIdleFunc(Idle);
	glutReshapeFunc(ReshapeCB);
	glutKeyboardFunc(KeyCB);
}

/////////////////////////////Callbacks/////////////////////////////

void Idle() {
	c = clock();
	if (flag) {
		for (int i = 0; i < scene.agents.size();i++) {
			scene.agents[i].setAcceleration(vec3(spd1, 0.0f) - scene.agents[i].getPosition());
			//scene.agents[i].setVelocity((vec3(spd1, 0.0f) - scene.agents[i].getPosition())*0.01f);
			dowork(i);
			float x = scene.agents[i].getVelocity().x;
			float y = scene.agents[i].getVelocity().y;
			float d = sqrt(pow(x, 2) + pow(y, 2));
			if (abs(x) > 0.01f || abs(y) > 0.01f)
				scene.agents[i].setVelocity(scene.agents[i].getVelocity() * 0.70f);
			scene.agents[i].Update();
			
		}
		//std::cout << scene.agents[0].getVelocity().x << " " << scene.agents[0].getVelocity().y << endl;
	}
	cout << (float)(clock() - c) / CLOCKS_PER_SEC << "s for physics" << endl;
		glutPostRedisplay();
	
}

void RenderSceneCB() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (int i = 0; i < scene.agents.size();i++) {
		scene.agents[i].Draw(shader, scene.resolution, scene.space, cam);
	}
	//std::cout << scene.agents[0].getPosition().x << " " << scene.agents[0].getPosition().y << std::endl;
	cout << (float)(clock() - c) / CLOCKS_PER_SEC << "s for render" << endl;
	glutSwapBuffers();
}

void KeyCB(unsigned char ch, int x, int y) {
	if (ch == 'p') {
		flag = !flag;
	}
}

void MouseCB(int x, int y) {
	scene.mousePos = center+vec2((x-scene.resolution.x/2)*scene.space.x/scene.resolution.x, ( - y + scene.resolution.y / 2)*scene.space.y/scene.resolution.y);
	//std::cout << scene.mousePos.x << ":" << scene.mousePos.y << endl;
}

void MouseCB1(int b, int s, int x, int y) {
	if (b == GLUT_MIDDLE_BUTTON) {
		center = vec2(0.0f);
		cam = center;
		spd1 = vec2(0.0f);
		mdlprsd = !mdlprsd;
	}
	else
		if (b == 3) {
			if (scene.space.x > 100.0f && scene.space.y > 100.0f) {
				scene.space.x -= 100.0f*aspectRatio;
				scene.space.y -= 100.0f;
			}
		}
		else
			if (b == 4) {
				scene.space.x += 100.0f*aspectRatio;
				scene.space.y += 100.0f;
			}
			else
				if (b == GLUT_LEFT_BUTTON && s == GLUT_DOWN) {
					prsd = true;
					spd1 = scene.mousePos;
				} else
					if (b == GLUT_LEFT_BUTTON && s == GLUT_UP) {
						prsd = false;
					}
				if (s == GLUT_DOWN && b != GLUT_LEFT_BUTTON) {
					center1 = center+ vec2((x - scene.resolution.x / 2) * scene.space.x / scene.resolution.x, (-y + scene.resolution.y / 2) * scene.space.y / scene.resolution.y);
				}
				if (s == GLUT_UP != GLUT_LEFT_BUTTON)
					center = cam;
	//std::cout << cam.x << endl;
	
}

void MouseCB2(int x, int y) {
	if (!prsd && !mdlprsd) {
		center2 = vec2((x - scene.resolution.x / 2) * scene.space.x / scene.resolution.x, (-y + scene.resolution.y / 2) * scene.space.y / scene.resolution.y);
		cam = center1 - center2;
	}
	else if (!mdlprsd) {
		spd1 = center + vec2((x - scene.resolution.x / 2) * scene.space.x / scene.resolution.x, (-y + scene.resolution.y / 2) * scene.space.y / scene.resolution.y);
	}
}
