
//EXTERNAL INCLUDES
//INTERNAL INCLUDES
#include "application.h"
#include "rendering/renderer.h"
#include "scene/gameobject.h"
#include "components/movement.h"
#include "components/shooting.h"
#include "components/bullet.h"
#include "rendering/geometry.h"
#include "rendering/shader.h"

//Gameobject Constructor.
Gameobject::Gameobject(bool render, bool isRoot, bool cam, fColorRGBA col, Gameobject* parent)
{
	//Set this gameobjects position, scaling and rotation to 0;
	this->transform.position = { 0.0f, 0, 0 };
	this->transform.scaling = { 30, 60, 0 };
	this->transform.rotation = { 1, 0, 0, 0 };

	if (cam)
		return;

	Application::GetInstancePtr()->AddGameobject(this);
	if (render)
	{
		this->material = new Shader();
		this->mesh = new Geometry(this, col);
		this->bMesh = true;
		Application::GetInstancePtr()->GetRenderer()->InitializeGameobject(this);
	}
	else
	{
		this->bMesh = false;
	}

	if (!isRoot && parent == nullptr)
	{
		this->SetParent(Application::GetInstancePtr()->GetRoot());
		Application::GetInstancePtr()->GetRoot()->AddChild(this);
	}
	else if (parent != nullptr)
	{
		this->SetParent(parent);
		parent->AddChild(this);
	}
}

Gameobject::Gameobject(Vertex* vertices, ui32* indicies, ui32 vLength, ui32 iLength, fColorRGBA col, bool render, bool isRoot)
{

}

Gameobject::~Gameobject()
{
	this->Cleanup();
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
				(static_cast<Shooting*>(component))->Update();
				break;
			case ComponentType::Bullet:
				(static_cast<Bullet*>(component))->Update();
				break;
		}
	}
}

//Void Cleanup
void Gameobject::Cleanup(void)
{

	//Empty this gameobjects name.
	this->name = "";

	for (Component* component : this->components)
	{
		//Check for the component type.
		//Update the casted components.
		switch (component->GetType())
		{
		case ComponentType::Movement:
			(static_cast<Movement*>(component))->Cleanup();
			break;
		case ComponentType::Shoot:
			(static_cast<Shooting*>(component))->Cleanup();
			break;
		case ComponentType::Bullet:
			(static_cast<Bullet*>(component))->Cleanup();
			break;
		}

		delete component;
	}
	this->components.clear();

	Node::Cleanup();
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
	this->material = new Shader();
	this->mesh = new Geometry(vertices, indicies, vLength, iLength, this);
	this->bMesh = true;
}

void Gameobject::SetMeshData(fColorRGBA col)
{
	this->mesh = new Geometry(this, col);
	this->bMesh = true;
}

Math::Mat4x4 Gameobject::GetModelMatrix(void)
{
	this->modelMatrix = Math::Mat4x4::identity;
	modelMatrix = modelMatrix * Math::CreateScalingMatrix(this->transform.scaling);
	modelMatrix = modelMatrix * Math::CreateRotationMatrix(Math::Vec3{ this->transform.rotation.x, this->transform.rotation.y, this->transform.rotation.z});
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

void Gameobject::SetVisiblity(bool b)
{
	this->isRendering = b;

	std::list<Node*> temp; 
	this->GetAllChildren(temp);

	for (Node* child : temp)
	{
		reinterpret_cast<Gameobject*>(child)->SetVisi(b);
	}
}

void Gameobject::SetVisi(bool b)
{
	this->isRendering = b;
}

bool Gameobject::hasMesh()
{
	if (this->bMesh == true)
		return true;
	return false;
}

bool Gameobject::isVisisble(void)
{
	if (this->isRendering == true)
		return true;
	return false;
}
