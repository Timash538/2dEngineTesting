#pragma once
#include <string>
#include "core_object.h"
#include "glm\vec2.hpp"
class ObjectManager {
private:
	vector<CoreObject*> objects;
public:
	ObjectManager(){}
	template <class T> ObjectManager(vector<T> _objects) {
		for (T &obj : _objects) {
			//std::cout << typeid(obj).name() << endl;
			objects.push_back(&obj);
		}
	}
	template <class T> void AddObject(T obj) {
		objects.push_back(&obj);
		for (int i = 0; i < objects.size();i++) {
			std::cout << typeid(objects[i]).name() << endl;
		}
	}
		


};