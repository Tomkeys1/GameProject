
//EXTERNAL INCLUDES
//INTERNAL INCLUDES
#include "scene/gameobject.h"
#include "components/movement.h"
#include "rendering/geometry.h"
#include "rendering/shader.h"

//Gameobject Constructor.
Gameobject::Gameobject(const char* vsFilename, const char* psFilename)
{
	//Set this gameobjects position, scaling and rotation to 0;
	this->transform.position = { 0, 0, 0 };
	this->transform.scaling = { 0, 0, 0 };
	this->transform.rotation = { 1, 0, 0, 0 };

	this->material = new Shader(vsFilename, psFilename);
	this->bMesh = false;
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

void Gameobject::SetMeshData(Vertex* vertices, ui32* indicies, ui32 vLength, ui32 iLength)
{
	this->mesh = new Geometry(vertices, indicies, vLength, iLength, this);
	this->bMesh = true;
}

Math::Mat4x4 Gameobject::GetModelMatrix(void)
{
	this->modelMatrix = Math::Mat4x4::identity;
	modelMatrix = modelMatrix * Math::CreateScalingMatrix(this->transform.scaling);
	modelMatrix = modelMatrix * Math::CreateRotationMatrix2(this->transform.rotation);
	modelMatrix = modelMatrix * Math::CreateTranslationMatrix(this->transform.position);

	return this->modelMatrix;
}

//GetTransform
Transform& Gameobject::GetTransform(void)
{
	//Return this gameobjects transform.
	return this->transform;
}

Geometry* Gameobject::GetMesh(void)
{
	return this->mesh;
}

Shader* Gameobject::GetMaterial(void)
{
	return this->material;
}

//Set name
void Gameobject::SetName(char* gameobjectName)
{
	//Set this gameobjects name.
	this->name = gameobjectName;
}

bool Gameobject::hasMesh()
{
	if (this->bMesh == true)
		return true;
	return false;
}
