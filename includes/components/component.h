
#pragma once
//EXTERNAL INCLUDES
//INTERNAL INCLUDES
#include "scene/gameobject.h"

enum class ComponentType
{
	Movement = 0,
	Shoot = 1,
	Material = 2,
	Collision = 3
};


class Component 
{

public:
	/**
	* @brief    This method calculates the distance between two vectors.\n
	*			It does not calculate the square root thus it is more performant than \link Engine::Math::Distance \endlink\n
	*			This method can be used to compare two distances relative to each other without taking the actual value\n
	*			into account. This can be helpful if you want to know which one is closer or further away than the other.
	* @param	comName 
	* @param	comType 
	*/
	virtual void Initialize(char* comName, ComponentType comType, Gameobject* gb);
	virtual void Update(void);
	virtual void Cleanup(void);

	ComponentType GetType(void) const;
	Gameobject* GetGameObject(void) const;

	bool operator==(const Component& other);

private:
	Gameobject* gameObject;
	char* name;
	ComponentType type;

};
