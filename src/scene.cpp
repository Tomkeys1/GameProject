
//EXTERNAL INCLUDES
//INTERNAL INCLUDES
#include "scene/scene.h"
#include "components/health.h"
#include "application.h"
#include "rendering/renderer.h"
#include "typedefs/color.h"
#include "typedefs/time.h"
#include "components/component.h"
#include "components/abilities/gravityshot.h"
#include "components/movement.h"
#include "components/shooting.h"
#include "components/bullet.h"
#include "rendering/camera.h"
#include "physics/rigidbody.h"

Scene::Scene()
{
	this->root = new Gameobject(false, true);
	this->root->SetName("scene");
	this->root->MakeRoot();
	Application::GetInstancePtr()->AddGameobject(this->root);
}

void Scene::Initialize(void)
{
	AddGameobject("player1", CreateMode::NORMAL, nullptr, Color::GetColor(ColorCode::YELLOW), true);

	Movement* mov = new Movement;
	Shooting* shot = new Shooting;

	AddComponent(this->gameObjects["player1"], mov);
	AddComponent(this->gameObjects["player1"], shot);

	mov->GetMovementValues().speed = 10.0f;
	mov->GetMovementValues().maxSpeed = 10000.0f;
	mov->GetMovementValues().rotationSpeed = 80.0f;

	shot->GetShootingValues().growth = 0.4f;
	shot->GetShootingValues().time = 3.0f;
	shot->GetShootingValues().speed = 0.0f;

	this->gameObjects["player1"]->GetTransform().position = { 0, -70.0f, 0.0f };
	this->gameObjects["player1"]->GetTransform().scaling = { 0.2f, 0.4f, 0 };
	this->gameObjects["player1"]->GetRigidbody()->GetRigidbodyValues().isEnabled = true;
	this->gameObjects["player1"]->GetRigidbody()->GetRigidbodyValues().mass = 100.0f;


	AddGameobject("object1", CreateMode::NORMAL, this->GetGameobject("player1"), Color::GetColor(ColorCode::RED), true, true);

	this->gameObjects["object1"]->GetTransform().position = { 30, 70.0f, 0.0f };
	this->gameObjects["object1"]->GetTransform().scaling = { 1.0f, 1.0f, 0 };


	AddGameobject("ground", CreateMode::NORMAL, nullptr, Color::GetColor(ColorCode::GREEN), true, true);
	this->gameObjects["ground"]->GetTransform().position = { 0, -100, 0.0f };
	this->gameObjects["ground"]->GetTransform().scaling = { 100.0f, 0.50f, 0 };

	AddGameobject("test", CreateMode::NORMAL, nullptr, Color::GetColor(ColorCode::BLUE));
	this->gameObjects["test"]->GetTransform().position = { 100, 100, 0.0f };
	this->gameObjects["test"]->GetTransform().scaling = { 0.01f, 0.01f, 0 };

}


void Scene::AddGameobject(const char* name, CreateMode mode, Gameobject* parent, fColorRGBA color, bool hasCollision, bool isMirror)
{
	if (mode == CreateMode::EMPTY)
	{
		this->gameObjects[name] = new Gameobject(false, false, false, parent, color, hasCollision, isMirror);
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
		this->gameObjects[name] = new Gameobject(true, false, false, parent, color, hasCollision, isMirror);
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
		(reinterpret_cast<Shooting*>(com))->Initialize(gb);
		break;
	case ComponentType::Bullet:
		(reinterpret_cast<Bullet*>(com))->Initialize(gb);
		break;
	case ComponentType::Health:
		(reinterpret_cast<Health*>(com))->Initialize(gb);
		break;
	case ComponentType::GravityShot:
		(reinterpret_cast<GravityShot*>(com))->Cleanup();
		break;
	}

	gb->AddComponent(com);
}

void Scene::DeleteGameobject(Gameobject* gb)
{
	this->deleteGb.push_back(gb);
}

void Scene::DeleteGameobjects(void)
{
	if (this->deleteGb.size() != 0)
	{
		for (Gameobject* gb : this->deleteGb)
		{
			this->gameObjects[gb->GetName()]->GetParent()->GetChildren().remove(gb);
			this->gameObjects.erase(gb->GetName());
			gb->Cleanup();
		}
		this->deleteGb.clear();
	}
}

Gameobject* Scene::GetGameobject(std::string name)
{
	return this->gameObjects[name];
}

Gameobject* Scene::GetGameobject()
{
	return this->root;
}

void Scene::Update(real deltaTime)
{
	Time::deltaTime = deltaTime / 1000.0f;
	this->root->Update();
}

void Scene::Cleanup(void)
{
	this->gameObjects.clear();
	this->root->Cleanup();
}
