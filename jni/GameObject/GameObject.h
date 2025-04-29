#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <jni.h>

struct Object_t {
    void *object;
};

class GameObject {
public:

    void* MyObject = NULL;

    std::vector<Object_t *> *objects;
	
    GameObject() {
        objects = new std::vector<Object_t *>();
    }
	
    bool isObjectPresent(void *Object) {
        for (std::vector<Object_t *>::iterator it = objects->begin(); it != objects->end(); it++) {
            if ((*it)->object == Object) {
                return true;
            }
        }
        return false;
    }
    void removeObject(Object_t *Object) {
        for (int i = 0; i < objects->size(); i++) {
            if ((*objects)[i] == Object) {
                objects->erase(objects->begin() + i);
                return;
            }
        }
    }
    void tryAddObject(void *Object) {
        if (isObjectPresent(Object)) {
            return;
        }
        Object_t *newObject = new Object_t();

        newObject->object = Object;
		
        objects->push_back(newObject);
    }
	
	void tryAddMyObject(void *Object) {
		if (MyObject==NULL)
		    MyObject = Object;
    }
    
    void removeObjectGivenObject(void *Object) {
        for (int i = 0; i < objects->size(); i++) {
            if ((*objects)[i]->object == Object) {
                objects->erase(objects->begin() + i);
                return;
            }
        }
    }
	
	void removeAllObjectGivenObject() {
		MyObject = NULL;
        for (int i = 0; i < objects->size(); i++) {
            objects->erase(objects->begin() + i);
        }
    }

};

#endif
