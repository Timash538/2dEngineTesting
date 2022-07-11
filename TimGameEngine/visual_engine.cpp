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
#include <time.h>
#include <string>
#include <thread>
#include <chrono>


clock_t c = clock();

Scene scene;
bool prsd = false;
bool mdlprsd = false;
bool flag = true;
bool flagTime = false;
vec3 massCenter = vec3(0.0f);
float aspectRatio = 800.0f/800.0f;
vec3 center = vec3(0.0f);
vec3 center1 = vec3(0.0f);
vec3 center2 = vec3(0.0f);
vec3 cam = vec3(0.0f);
Shader shader;
auto lastUpdate = std::chrono::system_clock::now();
std::chrono::duration<double>  ts;
std::chrono::duration<double> t;

VisualEngine::VisualEngine(int argc, char* argv[]) {
	glutInit(&argc, argv);
}

void doCollisionDetection(int i) {
	Agent* a = &scene.agents[i];
	vec3 aPos = a->getPosition();
	for (int j = 0; j < scene.agents.size();j++) {
		if (i != j) {
			Agent* b = &scene.agents[j];
			vec3 bPos = b->getPosition();

			float x1 = aPos.x;
			float y1 = aPos.y;

			float x2 = bPos.x;
			float y2 = bPos.y;

			float d = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
			if (d < b->getSize()+ a->getSize()) {
				//std::cout << d << std::endl;
				a->setVelocity(a->getVelocity() + (aPos - scene.agents[j].getPosition()) * std::max(b->getSize() - a->getSize(), 5.0f) / 10.0f);
				b->setVelocity(b->getVelocity() + (bPos - scene.agents[i].getPosition()) * std::max(a->getSize() - b->getSize(), 5.0f) / 10.0f);
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
	createPoints(30);
	scene.agents[0].setPosition(vec3(-1000.0f, 0.0f, 0.0f));
	//cout << (float)(lastUpdate-std::chrono::system_clock::now()) << "s for Init" << endl;
	lastUpdate = std::chrono::system_clock::now();
}



void VisualEngine::Start() {
	glutMainLoop();
}

void RenderSceneCB();
void Idle();
void MouseCB(int x, int y);
void MouseCB1(int b, int s, int x, int y);
void MouseCB2(int x, int y);
void TimerCB(int value);
void KeyCB(unsigned char ch, int x, int y);
auto lU = std::chrono::system_clock::now();

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

	auto now = std::chrono::system_clock::now();
	ts = (now - lastUpdate);
	lastUpdate = std::chrono::system_clock::now();

	if (flag) {
		for (int i = 0; i < scene.agents.size();i++) {
			Agent* agent = &scene.agents[i];
			vec3 acceleration = (massCenter - agent->getPosition());
			float magnitude = sqrt(pow(acceleration.x,2) + pow(acceleration.y,2));
			vec3 accUnit = acceleration / magnitude;
			agent->setAcceleration(accUnit*1000.0f);
			doCollisionDetection(i);
			float x = agent->getVelocity().x;
			float y = agent->getVelocity().y;
			float d = sqrt(pow(x, 2) + pow(y, 2));
			if (abs(x) > 300.0f || abs(y) > 300.0f)
				scene.agents[i].setVelocity(agent->getVelocity()*0.99f);
			scene.agents[i].Update(ts.count());
		}
	}
		glutPostRedisplay();
	
}

void RenderSceneCB() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (int i = 0; i < scene.agents.size();i++) {
		scene.agents[i].Draw(shader, scene.resolution, scene.space, cam);
	}
	//std::cout << scene.agents[0].getPosition().x << " " << scene.agents[0].getPosition().y << std::endl;
	
	glutSwapBuffers();
}

void KeyCB(unsigned char ch, int x, int y) {
	if (ch == 'p') {
		flag = !flag;
	}
}

void MouseCB(int x, int y) {
	scene.mousePos = center+vec3((x-scene.resolution.x/2)*scene.space.x/scene.resolution.x, ( - y + scene.resolution.y / 2)*scene.space.y/scene.resolution.y,0.0f);
	//std::cout << scene.mousePos.x << ":" << scene.mousePos.y << endl;
}

void MouseCB1(int b, int s, int x, int y) {
	if (b == GLUT_MIDDLE_BUTTON) {
		center = vec3(0.0f);
		cam = center;
		massCenter = vec3(0.0f);
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
					massCenter = scene.mousePos;
				} else
					if (b == GLUT_LEFT_BUTTON && s == GLUT_UP) {
						prsd = false;
					}
				if (s == GLUT_DOWN && b != GLUT_LEFT_BUTTON) {
					center1 = center+ vec3((x - scene.resolution.x / 2) * scene.space.x / scene.resolution.x, (-y + scene.resolution.y / 2) * scene.space.y / scene.resolution.y,0.0f);
				}
				if (s == GLUT_UP != GLUT_LEFT_BUTTON)
					center = cam;
	//std::cout << cam.x << endl;
	
}
std::chrono::duration<double> a;

void TimerCB(int value) {
	auto noww = std::chrono::system_clock::now();
	a = noww - lU;
	cout << a.count() << endl;
	cout << "Pos: " << scene.agents[0].getPosition().x << endl;
	cout << "Vel: " << scene.agents[0].getVelocity().x << endl;
	cout << "Acc: " << scene.agents[0].getAcceleration().x << endl;
	flag = !flag;
}

void MouseCB2(int x, int y) {
	if (!prsd && !mdlprsd) {
		center2 = vec3((x - scene.resolution.x / 2) * scene.space.x / scene.resolution.x, (-y + scene.resolution.y / 2) * scene.space.y / scene.resolution.y,0.0f);
		cam = center1 - center2;
	}
	else if (!mdlprsd) {
		massCenter = center + vec3((x - scene.resolution.x / 2) * scene.space.x / scene.resolution.x, (-y + scene.resolution.y / 2) * scene.space.y / scene.resolution.y,0.0f);
	}
}
