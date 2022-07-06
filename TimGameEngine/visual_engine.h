#pragma once
#include "shader.h"
#include <vector>
#include <math.h>
#include "scene.h"

class VisualEngine {
private: 

public:
	VisualEngine(int argc, char* argv[]);

	int Init(int width, int height);
	void Start();
	void RegisterCallbacks();

};