
//EXTERNAL INCLUDES
//INTERNAL INCLUDES
#include "components/component.h"
#include "typedefs/utils.h"

//Void Initialize
void Component::Initialize(const char* comName, ComponentType comType)
{
	//Set name and type.
	this->name = comName;
	this->type = comType;
}

//Void Update
void Component::Update(void)
{
	
}

//Void Update
void Component::Cleanup(void)
{
	this->name = "";
}

void Component::SetGameObject(Gameobject* gb)
{
	this->gameObject = gb;
}

//GetType.
ComponentType Component::GetType(void) const
{
	//Returns this components component type.
	return this->type;
}

Gameobject* Component::GetGameObject(void) const
{
	return this->gameObject;
}

//Compare two Components.
bool Component::operator==(const Component & other)
{
	//Return true if the bytes between this component and the inputed component are the size of the class Component.
	return memcmp(this, &other, sizeof(Component)) == 0;
}
