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

#define GLUT_ROLL_FORWARD 3
#define GLUT_ROLL_BACKWARD 4
#define pointInSpace(res,space) vec3((x/res.x-0.5f)*space.x, ( - y / res.y+0.5f)*space.y,0.0f)

clock_t c = clock();

Scene scene;
bool rightButtonPressed = false;
bool middleButtonPressed = false;
bool isSimulationRunning = true;
vec3 massCenter = vec3(0.0f);
Shader shader;
auto lastUpdate = std::chrono::system_clock::now();
std::chrono::duration<double>  timeStamp;

VisualEngine::VisualEngine(int argc, char* argv[]) {
	glutInit(&argc, argv);
}

void CreatePoints(int count);

int VisualEngine::Init(int width, int height) {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(0, 0);

	int window = glutCreateWindow("Space simulation v0.1");

	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return 1;
	}
	glEnable(GL_BLEND);

	glClearColor(0.3f, 0.3f, 1.0f, 1.0f);

	srand(std::time(0));

	scene = Scene();
	scene.resolution.x = width;
	scene.resolution.y = height;
	scene.aspectRatio = width / height;
	scene.space = vec2(2000, 2000);
	shader = Shader("shader.vs", "shader.fs");
	CreatePoints(50);

	lastUpdate = std::chrono::system_clock::now();
}

void VisualEngine::Start() {
	glutMainLoop();
}

// Callbacks Declaration
void RenderSceneCB();
void ReshapeCB(int x, int y);
void Idle();
void MousePassiveMotionCB(int x, int y);
void MouseButtonPressedCB(int b, int s, int x, int y);
void MousePressedMotionCB(int x, int y);
void KeyCB(unsigned char ch, int x, int y);

void VisualEngine::RegisterCallbacks() {
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glutIdleFunc(glutPostRedisplay);
	glutDisplayFunc(RenderSceneCB);
	glutPassiveMotionFunc(MousePassiveMotionCB);
	glutMotionFunc(MousePressedMotionCB);
	glutMouseFunc(MouseButtonPressedCB);
	glutIdleFunc(Idle);
	glutReshapeFunc(ReshapeCB);
	glutKeyboardFunc(KeyCB);
}

/////////////////////////////Auxiliary Functions///////////////////

// Bad collision detection
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
			if (d < b->getSize() + a->getSize()) {
				a->setVelocity(a->getVelocity() + (aPos - scene.agents[j].getPosition()) * std::max(b->getSize() - a->getSize(), 5.0f) / 10.0f);
				b->setVelocity(b->getVelocity() + (bPos - scene.agents[i].getPosition()) * std::max(a->getSize() - b->getSize(), 5.0f) / 10.0f);
			}
		}
	}
}

void CreatePoints(int count) {

	for (int i = 0; i < count; i++) {

		float x = RandomFloat(-1000.0f, 1000.0f);
		float y = RandomFloat(-1000.0f, 1000.0f);
		float size = RandomFloat(1.0f, 100.0f);

		vec3 randPos = vec3(x, y, 0.0f);

		scene.agents.push_back(Agent(randPos, vec3(0.0f), vec3(0.0f), size));
	}
}



/////////////////////////////Callbacks/////////////////////////////

void Idle() {

	//Timestamp
	auto now = std::chrono::system_clock::now();
	timeStamp = (now - lastUpdate);
	lastUpdate = std::chrono::system_clock::now();

	if (isSimulationRunning) {
		for (int i = 0; i < scene.agents.size();i++) {

			Agent* agent = &scene.agents[i];
			vec3 acceleration = (massCenter - agent->getPosition());
			float aMagnitude = sqrt(pow(acceleration.x,2) + pow(acceleration.y,2));
			vec3 accUnit = acceleration / aMagnitude;

			agent->setAcceleration(accUnit*3000.0f);

			doCollisionDetection(i);

			float x = agent->getVelocity().x;
			float y = agent->getVelocity().y;
			float d = sqrt(pow(x, 2) + pow(y, 2));

			if (abs(x) > 300.0f || abs(y) > 300.0f)
				scene.agents[i].setVelocity(agent->getVelocity()*0.99f);
			scene.agents[i].Update(timeStamp.count());
		}
	}
		glutPostRedisplay();
}

void RenderSceneCB() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (int i = 0; i < scene.agents.size();i++) {
		scene.agents[i].Draw(shader, scene.resolution, scene.space, scene.cam);
	}

	glutSwapBuffers();
}

void ReshapeCB(int x, int y) {

	vec2 oldSceneResolution = scene.resolution;
	scene.resolution = vec2(x, y);
	scene.aspectRatio = scene.resolution.x / scene.resolution.y;
	scene.space *= scene.resolution / oldSceneResolution;

	glutReshapeWindow(x, y);
	glViewport(0, 0, x, y);
}

void KeyCB(unsigned char ch, int x, int y) {

	if (ch == 'p') {
		isSimulationRunning = !isSimulationRunning;
	}
}

void MousePassiveMotionCB(int x, int y) {
	scene.mousePos = scene.cam + pointInSpace(scene.resolution, scene.space);
}

void MouseButtonPressedCB(int button, int status, int x, int y) {

	switch (button) {
	case GLUT_MIDDLE_BUTTON:
		scene.cam = vec3(0.0f);
		massCenter = vec3(0.0f);
		middleButtonPressed = !middleButtonPressed;
		break;
	case GLUT_ROLL_FORWARD:
		if (scene.space.x > 100.0f && scene.space.y > 100.0f) {
			scene.space.x -= 100.0f * scene.aspectRatio;
			scene.space.y -= 100.0f;
		}
		break;
	case GLUT_ROLL_BACKWARD:
		scene.space.x += 100.0f * scene.aspectRatio;
		scene.space.y += 100.0f;
		break;
	case GLUT_LEFT_BUTTON:
		if (status == GLUT_DOWN) {
			rightButtonPressed = true;
			massCenter = scene.mousePos;
		}
		else {
			rightButtonPressed = false;
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (status == GLUT_DOWN)
			scene.mousePos = scene.cam + pointInSpace(scene.resolution, scene.space);
		break;
	}
}

void MousePressedMotionCB(int x, int y) {
	if (!rightButtonPressed && !middleButtonPressed) {
		scene.cam = scene.mousePos - pointInSpace(scene.resolution, scene.space);
	}
	else {
		massCenter = scene.cam + pointInSpace(scene.resolution, scene.space);
	}
}
