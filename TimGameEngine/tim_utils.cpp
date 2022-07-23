#include "tim_utils.h"
#include "glm/mat4x4.hpp"
#include "glm/gtx/transform.hpp"
#include <fstream>


bool ReadFile(const char* FileName, string& outFile) {
	ifstream f(FileName);
	
	bool ret = false;
	
	if (f.is_open()) {
		string line;
		while (getline(f, line)) {
			outFile.append(line);
			outFile.append("\n");
		}
		ret = true;
	}
	else {
		fprintf(stderr, "Error reading shader file %s", FileName);
	}
	return ret;
}

float RandomFloat(float min, float max)
{
	float r = (float)rand() / (float)RAND_MAX;
	return min + r * (max - min);
}

float getMagnitude(vec2& start, vec2& end) {
	return (float)sqrt(pow(start.x + end.x, 2) + pow(start.y + end.y, 2));
}

void showVec(vec3 v) {
	cout << "x: " << v.x << " y: " << v.y << " z: " << v.z << endl;
}