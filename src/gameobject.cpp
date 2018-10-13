
//EXTERNAL INCLUDES
//INTERNAL INCLUDES
#include "scene/gameobject.h"
#include "components/movement.h"

//Gameobject Constructor.
Gameobject::Gameobject()
{
	//Set this gameobjects position, scaling and rotation to 0;
	this->transform.position = { 0, 0, 0 };
	this->transform.scaling = { 0, 0, 0 };
	this->transform.rotation = { 1, 0, 0, 0 };
}

//Void Update
void Gameobject::Update(void)
{
	//Execute the bases Update.
	Node::Update();

	//For all component pointers in the components list of this gameobject.
	for (Component* component : this->components) 
	{
		//Check for the component type.
		//Update the casted components.
		switch (component->GetType()) 
		{
			case ComponentType::Movement :
				(static_cast<Movement*>(component))->Update();
				break;
			case ComponentType::Shoot:
				(static_cast<Movement*>(component))->Update();
				break;
			case ComponentType::Material:
				(static_cast<Movement*>(component))->Update();
				break;
			case ComponentType::Collision:
				(static_cast<Movement*>(component))->Update();
				break;
		}
	}
}

//Void Cleanup
void Gameobject::Cleanup(void)
{
	//Empty this gameobjects name.
	this->name = "";
}

//Void AddComponent
void Gameobject::AddComponent(Component* component)
{
	//Store the inputed component pointer into this gameobjects components list.
	this->components.push_back(component);
}

//Void DeleteComponent
void Gameobject::DeleteComponent(Component* component)
{
	//Get the id of the inputed component pointer in this gameobjects components list.
	std::ptrdiff_t id = std::find(this->components.begin(), this->components.end(), component) - this->components.begin();

	//If the id is in this gameobjects components list.
	if (id >= this->components.size())
	{
		//Delete the component.
		this->components.erase(this->components.begin() + id);
	}
	else
	{
		//Component wasnt found.
		LOG("The Component wasnt found.");
	}
}

//GetTransform
Transform& Gameobject::GetTransform(void)
{
	//Return this gameobjects transform.
	return this->transform;
}

//Set name
void Gameobject::SetName(char* gameobjectName)
{
	//Set this gameobjects name.
	this->name = gameobjectName;
}
