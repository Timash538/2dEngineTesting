#pragma once
#include "shader.h"
#include <vector>
#include <math.h>

class VisualEngine {
private: 
	//const char* shaders[2] = {"shader.vs","shader.fs"};



	//Shader shader = Shader("shader.vs", "shader.fs");

public:
	VisualEngine(int argc, char* argv[]);

	int Init(int width, int height);
	void Start();
	void RegisterCallbacks();

};