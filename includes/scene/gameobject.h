
#pragma once
//EXTERNAL INCLUDES
#include <vector>
//INTERNAL INCLUDES
#include "node.h"
#include "typedefs/transform.h"
#include "typedefs/utils.h"

//Forward declaration.
class Component;

//Class Gameobject derived from class Node. This is class cant be inherited.
class Gameobject final : public Node
{
//Declare public functions. And override some functions of class Node.
public:
	Gameobject();

	virtual void Update(void) override;
	void Cleanup(void);

	void AddComponent(Component* component);
	void DeleteComponent(Component* component);
	Transform& GetTransform(void);

	void SetName(char* gameobjectName);

//Declare private variables.
private:
	Transform transform;
	char* name;
	std::vector<Component*> components;
};
