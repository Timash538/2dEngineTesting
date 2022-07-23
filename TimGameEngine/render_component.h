#pragma once
#include "component.h"
#include "glew.h"
#include "freeglut.h"
#include "glm/vec3.hpp"
#include "scene.h"
#include "simple_model.h"
#include "shader.h"

class RenderComponent : public Component {
	unsigned int num_elements;
	
	Shader* pShader;
	Scene* pScene;

public:
	SimpleModel* pSimpleModel;
	RenderComponent(Shader& _shader, Scene& _scene, SimpleModel &_simpleModel);

	void Draw(vec3 position, float size);
};