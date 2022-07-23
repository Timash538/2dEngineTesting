#include "render_component.h"

RenderComponent::RenderComponent(Shader &_shader, Scene &_scene, SimpleModel &_vao) {
	pShader = &_shader;
	pScene = &_scene;
	pSimpleModel = &_vao;
	num_elements = pSimpleModel->numOfElements();
}

void RenderComponent::Draw(vec3 position, float size) {
	pShader->use();
	pShader->setVec3("Pos", position);
	pShader->setFloat("Size", size);
	pShader->setVec3("res", pScene->resolution);
	pShader->setVec3("cam", pScene->cam);
	pShader->setVec3("spc", pScene->space);
	glBindVertexArray(pSimpleModel->getVAO());
	glDrawElements(GL_TRIANGLES, pSimpleModel->numOfElements(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}