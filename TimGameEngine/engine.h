#pragma once

#include "glew.h"
#include "shader.h"

class Engine {
public:
	Engine(int argc, char* argv[]);

	~Engine();

	int Init(int width, int height);

	void RegisterCallbacks();

	void Start();

private:
	GLuint VBO;

	int window;
	int width, height;
};