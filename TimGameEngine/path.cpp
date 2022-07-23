#include "path.h"
#include "tim_utils.h"

Waypoint::Waypoint(vec2 _pos,Waypoint &wp) { 
	pos = _pos;
	addWaypoint(wp);
	wp.addWaypoint(*this);
}

Waypoint::Waypoint(vec2 _pos) {
	pos = _pos;
}

vec2& Waypoint::getPosition() {
	return pos;
}

void Waypoint::addWaypoint(Waypoint& wp) {
	waypoints.push_back(wp);
}

//PhysicsObject& Waypoint::getAgent() {
//	return agent;
//}

vector<Waypoint>& Waypoint::getWPs() {
	return waypoints;
}

RoadMap::RoadMap(){}

RoadMap::RoadMap(float maxX, float maxY, int count) {
	for (int i = 0; i < count; i++) {
		float x = RandomFloat(-maxX, maxX);
		float y = RandomFloat(-maxY, maxY);
		Waypoint wp = Waypoint(vec2(x, y));
		waypoints.push_back(wp);
	}

	for (Waypoint& waypoint : waypoints) {
		int countr = (int)RandomFloat(1.0f,3.0f);
		for (int i = 0; i < countr; i++) {
			int index = RandomFloat(0.0f, 1.0f) * waypoints.size()-1;
			Waypoint& _wp = waypoints.at(index);
			bool flag = false;
			for (Waypoint& w : waypoint.getWPs()) {
				if (w.getPosition() == _wp.getPosition()) {
					flag = true;
					i--;
					break;
				}
			}
			if (!flag) {
				lines.push_back(waypoint.getPosition());
				lines.push_back(_wp.getPosition());
				vec3 vertices[2];
				vertices[0] = vec3(waypoint.getPosition(),0.0f);
				vertices[1] = vec3(_wp.getPosition(),0.0f);
				GLuint VAO, VBO;
				
				glGenVertexArrays(1, &VAO);
				glBindVertexArray(VAO);
				glGenBuffers(1, &VBO);
				glBindBuffer(GL_ARRAY_BUFFER, VBO);
				glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(0);

				glBindBuffer(GL_ARRAY_BUFFER, 0);

				glBindVertexArray(0);
				VAOs.push_back(VAO);
				VBOs.push_back(VBO);
				waypoint.addWaypoint(_wp);
				_wp.addWaypoint(waypoint);
			}
		}
	}
	/*int k = 1;
	for (Waypoint& waypoint : waypoints) {
		std::cout << k << " wX: " << waypoint.getPosition().x << " wY: " << waypoint.getPosition().y << endl;
		std::cout << "  aX: " << waypoint.getAgent().getPosition().x << " aY: " << waypoint.getAgent().getPosition().y << endl;
		std::cout << "  aSize: " << waypoint.getAgent().getSize() << endl;
		k++;
	}
	k = 1;
	for (vec2 line : lines) {
		std::cout << k << " X1: " << line.x << " Y1: " << line.y << endl;
		k++;
	}*/
}

void RoadMap::Draw(Shader shader, vec2 resolution, vec2 scene, vec2 cam) {
	for (Waypoint& wp : waypoints) {
		wp.getAgent().Draw(shader, resolution, scene, cam);
	}
	for (int i = 0; i < VAOs.size();i++) {
		vec2 line1 = lines[i];
		vec2 line2 = lines[i+1];
		shader.use();
		shader.setVec3("Pos", vec3(0.0f));
		shader.setFloat("Size", 1.0f);
		shader.setVec3("bColor", vec3(0.3f, 0.3f, 1.0f));
		shader.setVec3("scene", vec3(scene.x, scene.y, 0.0f));
		shader.setVec3("res", vec3(resolution.x, resolution.y, 0.0f));
		shader.setVec3("cam", vec3(cam.x, cam.y, 0.0f));
		glBindVertexArray(VAOs.at(i));
		glDrawArrays(GL_LINES, 0, 2);
		glBindVertexArray(0);
	}
}