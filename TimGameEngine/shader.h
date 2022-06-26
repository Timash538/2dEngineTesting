#pragma once
#include "tim_utils.h"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"

using namespace glm;

class Shader {
public:
	unsigned int ID;
	Shader();
	Shader(const char* vertexPath, const char* fragmentPath);

	void use();

	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setVec3(const std::string& name, float value1, float value2, float value3) const;
	void setVec3(const std::string& name, vec3 vec) const;
	void setMat4(const std::string& name, const mat4& mat) const;
};