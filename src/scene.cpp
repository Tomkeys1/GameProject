
//EXTERNAL INCLUDES
//INTERNAL INCLUDES
#include "scene/scene.h"
#include "application.h"
#include "rendering/renderer.h"
#include "typedefs/color.h"
#include "components/component.h"
#include "components/movement.h"
#include "components/collision.h"
#include "components/shooting.h"
#include "components/bullet.h"
#include "rendering/camera.h"

Scene::Scene()
{
	this->root = new Gameobject(false, true);
	this->root->SetName("scene");
	this->root->MakeRoot();
	Application::GetInstancePtr()->AddGameobject(this->root);
}

void Scene::Initialize(void)
{
	AddGameobject("player1", CreateMode::NORMAL, nullptr, Color::GetColor(ColorCode::YELLOW));

	Movement* mov = new Movement;
	Shooting* shot = new Shooting;
	Collision* col = new Collision;

	AddComponent(this->gameObjects["player1"], mov);
	AddComponent(this->gameObjects["player1"], shot);
	AddComponent(this->gameObjects["player1"], col);

	mov->velocity = 0.00001f;
	mov->maxSpeed = 0.01f;

	this->gameObjects["player1"]->GetTransform().position = { 0, -70.0f, 0.0f };
	this->gameObjects["player1"]->GetTransform().scaling = { 0.2f, 0.4f, 0 };


	AddGameobject("object1", CreateMode::NORMAL, nullptr, Color::GetColor(ColorCode::RED));

	this->gameObjects["object1"]->GetTransform().position = { 0, 0.0f, 0.0f };


}

void Scene::AddGameobject(const char* name, CreateMode mode, Gameobject* parent, fColorRGBA color)
{
	if (mode == CreateMode::EMPTY)
	{
		this->gameObjects[name] = new Gameobject(false, false, false, parent, color, false);
		this->gameObjects[name]->SetName(name);

		Application::GetInstancePtr()->AddGameobject(this->gameObjects[name]);

		if (parent == nullptr)
		{
			this->gameObjects[name]->SetParent(this->root);
			this->root->AddChild(this->gameObjects[name]);
		}
	}
	else if (mode == CreateMode::NORMAL)
	{
		this->gameObjects[name] = new Gameobject(true, false, false, parent, color, true);
		this->gameObjects[name]->SetName(name);

		Application::GetInstancePtr()->AddGameobject(this->gameObjects[name]);

		if (parent == nullptr)
		{
			this->gameObjects[name]->SetParent(this->root);
			this->root->AddChild(this->gameObjects[name]);
		}

		Application::GetInstancePtr()->GetRenderer()->InitializeGameobject(this->gameObjects[name]);
	}
}

void Scene::AddMesh(Gameobject* gb, Vertex* vertices, ui32* indicies, ui32 vLength, ui32 iLength)
{
	gb->SetMeshData(vertices, indicies, vLength, iLength);
	Application::GetInstancePtr()->GetRenderer()->InitializeGameobject(gb);
}

void Scene::AddComponent(Gameobject* gb, Component* com)
{
	switch (com->GetType())
	{
	case ComponentType::Movement:
		(reinterpret_cast<Movement*>(com))->Initialize(gb);
		break;
	case ComponentType::Shoot:
		(reinterpret_cast<Movement*>(com))->Initialize(gb);
		break;
	case ComponentType::Bullet:
		(reinterpret_cast<Bullet*>(com))->Initialize(gb);
		break;
	case ComponentType::Collision:
		(reinterpret_cast<Collision*>(com))->Initialize(gb);
		break;
	}

	gb->AddComponent(com);
}

Gameobject* Scene::GetGameobject(std::string name)
{
	return this->gameObjects[name];
}

Gameobject* Scene::GetGameobject()
{
	return this->root;
}

void Scene::Update(void)
{
	this->root->Update();
}

void Scene::Cleanup(void)
{
	this->gameObjects.clear();
	this->root->Cleanup();
}
