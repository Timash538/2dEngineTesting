#include "tim_utils.h"
#include "glm/mat4x4.hpp"
#include "glm/gtx/transform.hpp"
#include <fstream>
using namespace std;
using namespace glm;
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

mat4 InitRotationTransform(glm::vec3 rot) {
	mat4 rotationX, rotationY, rotationZ;
	rotationX = rotate(rot.x, vec3(1.0f, 0.0f, 0.0f));
	rotationY = rotate(rot.y, vec3(0.0f, 1.0f, 0.0f));
	rotationZ = rotate(rot.z, vec3(0.0f, 0.0f, 1.0f));
	return rotationX * rotationY * rotationZ;
}