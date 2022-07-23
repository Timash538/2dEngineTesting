#include "visual_engine.h"

#include "glew.h"
#include "freeglut.h"
#include "tim_utils.h"
#include "glm/vec3.hpp"
#include <ctime>
#include "shader.h"
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <time.h>
#include <string>
#include <thread>
#include <chrono>
#include "enum.h"
#include "game_object.h"

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
//RoadMap roadMap;
GameObject object;
SimpleModel model;\
vector<GameObject> objs;

Program p = Program::physics_demo;

GLuint VAO, VBO, IBO;

VisualEngine::VisualEngine(int argc, char* argv[]) {
	glutInit(&argc, argv);
}

//void CreatePoints(vector<PhysicsObject> &agents, int count);
void ChooseProgram(Program program) {
	switch (program) {
	case Program::path_demo:
		//roadMap = RoadMap(1000.0f, 1000.0f, 6);
		break;
	case Program::physics_demo:
		//CreatePoints(scene.agents, 50);
		break;
	}
}

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

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//glClearColor(0.3f, 0.3f, 1.0f, 1.0f);

	srand(std::time(0));
	vector<vec3> vertices;

	vertices.push_back(vec3(-1.0f, -1.0f, 0.0f));
	vertices.push_back(vec3(-1.0f, 1.0f, 0.0f));
	vertices.push_back(vec3(1.0f, 1.0f, 0.0f));
	vertices.push_back(vec3(1.0f, -1.0f, 0.0f));

	vector<unsigned int> indices = {0,1,2,0,2,3};


	scene = Scene();
	for (vec3 v : vertices) {
		showVec(v);
	}
	scene.resolution.x = width;
	scene.resolution.y = height;
	scene.aspectRatio = width / height;
	scene.space = vec3(2000, 2000,0.0f);
	shader = Shader("shader.vs", "light.fs");
	model = SimpleModel(vertices, indices);
	//std::cout << sizeof(vertices) << endl;
	//std::cout << sizeof(indices) << endl;
	for (int i = 0; i < 30; i++) {
		GameObject nObj = GameObject(vec3(RandomFloat(-1000.0f, 1000.0f), RandomFloat(-1000.0f, 1000.0f), 0.0f), RandomFloat(30.0f, 200.0f));
		nObj.physC.push_back(new PhysicsComponent());
		nObj.physC[0]->setVelocity(vec3(10.0f, 0.0f, 0.0f));
		nObj.renderC.push_back(new RenderComponent(shader, scene, model));
		objs.push_back(nObj);
		
	}
	object.physC.push_back(new PhysicsComponent());
	object.physC[0]->setVelocity(vec3(1.0f, 0.0f, 0.0f));
	object.renderC.push_back(new RenderComponent(shader, scene, model));
	object.size = 30.0f;
	ChooseProgram(p);
	lastUpdate = std::chrono::system_clock::now();
}

void VisualEngine::Start() {
	glutMainLoop();
}

// Callbacks Declaration
void RenderSceneCB();
void ReshapeCB(int x, int y);
void Idle();
void PhysicsIdle();
void MousePassiveMotionCB(int x, int y);
void MouseButtonPressedCB(int b, int s, int x, int y);
void MousePressedMotionCB(int x, int y);
void KeyCB(unsigned char ch, int x, int y);

auto ChoosenIdle(Program program) {
	switch (program) {
	case Program::path_demo:
		return Idle;
		break;
	case Program::physics_demo:
		return PhysicsIdle;
		break;
	default:
		return Idle;
		break;
	}
}

void VisualEngine::RegisterCallbacks() {
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glutIdleFunc(glutPostRedisplay);
	glutDisplayFunc(RenderSceneCB);
	glutPassiveMotionFunc(MousePassiveMotionCB);
	glutMotionFunc(MousePressedMotionCB);
	glutMouseFunc(MouseButtonPressedCB);
	glutIdleFunc(ChoosenIdle(p));
	glutReshapeFunc(ReshapeCB);
	glutKeyboardFunc(KeyCB);
}

/////////////////////////////Auxiliary Functions///////////////////

 //Bad collision detection
void doCollisionDetection(int i) {
	GameObject* a = &objs[i];
	vec3 aPos = a->position;
	for (int j = 0; j < objs.size();j++) {
		if (i != j) {
			GameObject* b = &objs[j];
			vec3 bPos = b->position;

			float x1 = aPos.x;
			float y1 = aPos.y;

			float x2 = bPos.x;
			float y2 = bPos.y;

			float d = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
			if (d < b->size + a->size) {
				a->physC[0]->setVelocity(a->physC[0]->getVelocity() + ((aPos - bPos) * (std::max(std::abs(b->size - a->size), 5.0f))) / 100.0f);
				b->physC[0]->setVelocity(b->physC[0]->getVelocity() + ((bPos - aPos) * (std::max(std::abs(a->size - b->size), 5.0f))) / 100.0f);
			}
		}
	}
}

//void CreatePoints(vector<PhysicsObject>& agents, int count) {
//	for (int i = 0; i < count; i++) {
//
//		float x = RandomFloat(-1000.0f, 1000.0f);
//		float y = RandomFloat(-1000.0f, 1000.0f);
//		float size = RandomFloat(1.0f, 100.0f);
//
//		vec3 randPos = vec3(x, y, 0.0f);
//
//		//agents.push_back(PhysicsObject(randPos, vec3(0.0f), vec3(0.0f), size));
//	}
//}



/////////////////////////////Callbacks/////////////////////////////

void PhysicsIdle() {
	
	//Timestamp
	auto now = std::chrono::system_clock::now();
	timeStamp = (now - lastUpdate);
	lastUpdate = std::chrono::system_clock::now();

	if (isSimulationRunning) {
		for (int i = 0; i < 30; i++) {
			objs[i].physC[0]->setAcceleration(1000.0f*(massCenter - objs[i].position)/(float)sqrt(pow(massCenter.x-objs[i].position.x,2)+pow(massCenter.y - objs[i].position.y, 2)));
			//showVec(objs[i].physC[0]->getAcceleration());
			doCollisionDetection(i);
			float x = objs[i].physC[0]->getVelocity().x;
			float y = objs[i].physC[0]->getVelocity().y;
			float d = sqrt(pow(x, 2) + pow(y, 2));

			if (abs(x) > 300.0f || abs(y) > 300.0f)
				objs[i].physC[0]->setVelocity(objs[i].physC[0]->getVelocity() * 0.99f);
			objs[i].Update(timeStamp.count());
		}
		//std::cout << object.position.x << endl;
		/*for (int i = 0; i < scene.agents.size();i++) {

			PhysicsObject* agent = &scene.agents[i];
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
		}*/
	}
	glutPostRedisplay();
}

void Idle() {
	
	//Timestamp
	auto now = std::chrono::system_clock::now();
	timeStamp = (now - lastUpdate);
	lastUpdate = std::chrono::system_clock::now();
	std::cout << timeStamp.count() << endl;
	glutPostRedisplay();
}

void RenderSceneCB() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (GameObject obj : objs) {
		obj.Draw();
	}
	//std::cout << object.renderC[0]->pSimpleModel->numOfElements() << endl;
	glutSwapBuffers();
}

void ReshapeCB(int x, int y) {

	vec3 oldSceneResolution = scene.resolution;
	scene.resolution = vec3(x, y,1.0f);
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
