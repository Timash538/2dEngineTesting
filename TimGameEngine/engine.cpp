#include "engine.h"
#include "freeglut.h"
#include "tim_utils.h"
#include "glm/vec3.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "texture.h"
#include "shader.h"
#include "model.h"
#include "camera.h"
#include "agent.h"
#include <ctime>

#include "world_transform.h"

#define GLM_FORCE_DEPTH_ZERO_TO_ONE


using namespace glm;

Shader shader,shader2;
GLuint cubeVAO, lightVAO;
GLuint VBO;
vec3 lightColor(1.0f);
vec3 objectColor(1.0f, 0.0f, 0.0f);
vector<Agent> agents;

//float vertices[] = {
//	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//
//	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//
//	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//
//
//	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//
//	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//
//	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
//	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
//	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
//};

Camera cam;
float currentFrame, lastFrame, deltaTime;
int mX, mY;
bool passiveMotionOn = true;


Engine::Engine(int argc, char* argv[]) {
	glutInit(&argc,argv);
};

Engine::~Engine() {};

//void CreateCubes();

int Engine::Init(int width, int height) {
	glutSetOption(GLUT_MULTISAMPLE, 8);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(0,0);

	window = glutCreateWindow("kek");

	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return 1;
	}

	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_MULTISAMPLE);
	glHint(GL_MULTISAMPLE_FILTER_HINT_NV, GL_FASTEST);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	shader = Shader("shader.vs", "shader.fs");
	shader2 = Shader("shader.vs", "light.fs");

	//CreateCubes();
	string path = "D:/repos/TimGameEngine/TimGameEngine/obj_Neck_Mech_Walker_by_3DHaupt/Neck_Mech_Walker_by_3DHaupt-(Wavefront OBJ).obj";
	string path2 = "C:/Users/Timash/Desktop/99d2906d822406ddb52a099cdc3d08b5/Gato.obj";
	agents.push_back(Agent(path2));
	agents.push_back(Agent(path));
	agents.push_back(Agent(path));
	//agents[0].GetWT().SetScale(0.25f, 0.25f, 0.25f);
	agents.at(1).GetWT().SetPosition(2.0f, 1.0f, 3.0f);
	agents.at(2).GetWT().SetPosition(8.0f, -5.0f, 3.0f);
	agents.at(1).GetWT().SetRotation(2.0f, 1.0f, 3.0f);
	agents.at(2).GetWT().SetRotation(8.0f, -5.0f, 3.0f);
	//agents.at(1).SetSpeed(vec3(1.0f,0.0f,0.0f));
	

	currentFrame = clock();
	lastFrame = currentFrame;

	glutSetCursor(GLUT_CURSOR_NONE);
	glutFullScreen();
	glClearColor(0.3f, 0.3f, 1.0f, 1.0f);

}

//void RenderSceneCB() {
//	
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	mat4 PersProjTrans = perspectiveFov(1.57f, 1920.0f, 1080.0f, 0.001f, 100.0f);
//	mat4 CameraTrans = cam.GetMatrix();
//	mat4 WVP;
//	WorldTransform wT;
//	mat4 WorldTrans;
//	Agent& agent = agents.at(0);
//	agent.GetWT().SetPosition(cam.GetPosition() + cam.direction + vec3(0.0f,-1.0f,0.0f));
//	cam.Update();
//	shader.use();
//	
//	for (unsigned int i = 0; i < agents.size(); i++) {
//		agents.at(i).Update();
//		WVP = PersProjTrans * CameraTrans * agents.at(i).GetWT().GetMatrix();
//		agents.at(i).Draw(shader, WVP);
//	}
//
//	
//	static float scale = 0.0f;
//	scale += 0.01f;
//	vec3 lightPos(cosf(scale)*5.0f, 0.0f, sinf(scale)*5.0f);
//	
//
//	shader.use();
//	shader.setVec3("objectColor", objectColor);
//	shader.setVec3("lightColor", lightColor);
//	shader.setVec3("lightPos", lightPos.x,lightPos.y,lightPos.z);
//	vec3 camPos = cam.GetPosition();
//	shader.setVec3("viewPos", camPos.x,camPos.y,camPos.z);
//	mat4 rotation = wT.GetRotMatrix();
//	mat4 model(1.0f);
//	WorldTrans = wT.GetMatrix();
//	WVP = PersProjTrans * CameraTrans * WorldTrans;
//	shader.setMat4("rotation", rotation);
//	shader.setMat4("model", model);
//	shader.setMat4("WVP", WVP);
//
//	glBindVertexArray(cubeVAO);
//	glDrawArrays(GL_TRIANGLES, 0, 36);
//
//	//lightCube
//	wT.SetPosition(0.0f, 0.0f, 5.0f);
//
//	wT.Translate(lightPos);
//	wT.SetRotation(0.0f, 0.0f, 0.0f);
//	wT.SetScale(0.1, 0.1f, 0.1f);
//
//	shader2.use();
//	WorldTrans = wT.GetMatrix();
//	WVP = PersProjTrans * CameraTrans * WorldTrans;
//
//	shader2.setMat4("WVP", WVP);
//
//	glBindVertexArray(lightVAO);
//	glDrawArrays(GL_TRIANGLES, 0, 36);
//
//	glutPostRedisplay();
//	glutSwapBuffers();
//}

void KeysCB(unsigned char key, int x, int y) {
	if (key == 27) {
		glutLeaveMainLoop();
	}
	cam.OnKeyboard(key);
}

void KeysUpCB(unsigned char key, int x, int y) {
	cam.OnKeyboardUp(key);
}

void PassiveMouseCB(int x, int y) {
	if (passiveMotionOn) {
		mX = 1200 / 2 - x;
		mY = 720 / 2 - y;
		cam.OnMouse(mX, mY);
		agents[0].OnMouse(mX,mY);
		glutWarpPointer(1200 / 2, 720 / 2);
	}
}

//void Engine::RegisterCallbacks() {
//	glutDisplayFunc(RenderSceneCB);
//	glutKeyboardFunc(KeysCB);
//	glutKeyboardUpFunc(KeysUpCB);
//	glutPassiveMotionFunc(PassiveMouseCB);
//}

void Engine::Start() {

	//Vertex vecs[3];
	//vecs[0].Position = vec3(-1.0f, -1.0f, 0.0f);
	//vecs[1].Position = vec3(0.0f, 1.0f, 0.0f);
	//vecs[2].Position = vec3(1.0f, -1.0f, 0.0f);

	//vecs[0].TexCoords = vec2(0.0f,0.0f);
	//vecs[1].TexCoords = vec2(0.5f,1.0f);
	//vecs[2].TexCoords = vec2(1.0f, 0.0f);
	//glGenBuffers(1, &VBO);

	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vecs), vecs, GL_STATIC_DRAW);
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

	glutMainLoop();
}

//void CreateCubes() {
//	
//	glGenBuffers(1, &VBO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//
//	//glGenVertexArrays(1, &cubeVAO);
//	//glBindVertexArray(cubeVAO);
//	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	//glEnableVertexAttribArray(0);
//	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*6,(void*)0);
//	//glEnableVertexAttribArray(1);
//	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(sizeof(float) * 3));
//
//	glGenVertexArrays(1, &lightVAO);
//	glBindVertexArray(lightVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);
//}