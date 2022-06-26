#pragma once
#include "model.h"
#include "tim_utils.h"
#include "world_transform.h"

class Agent {
private:
	Model model;
	vec3 speed = vec3(0.0f);
	vec3 acceleration = vec3(0.0f);
	WorldTransform wT;
public:
	Agent(string path) {
		model = Model(path);
	}
	void Draw(Shader shader, mat4 wvp) {
		shader.setMat4("WVP", wvp);
		model.Draw(shader);
	}
	void SetSpeed(vec3 vec) {
		speed = vec;
	};
	void SetAcceleration(vec3 acc) {
		acceleration = acc;
	};
	WorldTransform& GetWT() {
		return wT;
	}

	void OnMouse(int x, int y) {
		
		//wT.rot.x += toRadian(y * -0.1f);
		wT.rot.y -= toRadian(x * -0.1f);
		if (wT.rot.x > toRadian(89.9f))
			wT.rot.x = toRadian(89.9f);
		if (wT.rot.x < toRadian(-89.9f))
			wT.rot.x = toRadian(-89.9f);
	}

	void Update() {
		wT.Translate(speed);
		speed += acceleration;
	}

};