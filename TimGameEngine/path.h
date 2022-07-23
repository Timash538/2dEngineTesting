#pragma once
#include <vector>
#include "glm/vec2.hpp"
#include "object.h"

using namespace std;
using namespace glm;
class Waypoint;
class Path {
	vector<Waypoint> waypoints;

public:
	Path(const vector<Waypoint> &waypoints);
};

class Waypoint {
	Object agent;
	vector<Waypoint> waypoints;
	vec2 pos;

public:
	Waypoint(vec2 _pos);

	Waypoint(vec2 pos, Waypoint& waypoint);
	vec2& getPosition();
	void addWaypoint(Waypoint &wp);
	Object& getAgent();
	vector<Waypoint>& getWPs();
};

class RoadMap {
	vector<GLuint> VAOs;
	vector<GLuint> VBOs;
	vector<Waypoint> waypoints;
	vector<vec2> lines;

public:
	RoadMap();
	RoadMap(float x, float y, int count);
	RoadMap(vector<Waypoint> waypoints);
	void ConnectWaypoints(Waypoint &start,Waypoint &end);
	void Draw(Shader shader, vec2 res, vec2 scene, vec2 cam);
};