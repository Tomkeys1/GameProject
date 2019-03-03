
//EXTERNAL INCLUDES
#include <thread>
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
#include "components/enemies/espawnbehaviour.h"

Scene::Scene()
{
	this->root = new Gameobject("scene", false, true);
	this->root->MakeRoot();
}

void Scene::Initialize(void)
{
	//Player
	AddGameobject("player1", CreateMode::NORMAL, nullptr, Color::GetColor(ColorCode::YELLOW), true);
	this->gameObjects["player1"]->GetTransform().position = { 0, -70.0f, 0.0f };
	this->gameObjects["player1"]->GetTransform().scaling = { 0.2f, 0.4f, 0 };
	this->gameObjects["player1"]->GetRigidbody()->GetRigidbodyValues().isEnabled = true;
	this->gameObjects["player1"]->GetRigidbody()->GetRigidbodyValues().mass = 100.0f;
	this->gameObjects["player1"]->SetTag("player");

	Movement* mov = new Movement;
	mov->GetMovementValues().speed = 10000.0f;
	mov->GetMovementValues().maxSpeed = 220000.0f;
	AddComponent(this->gameObjects["player1"], mov);

	Shooting* shot = new Shooting;
	shot->GetShootingValues().growth = 2.0f;
	shot->GetShootingValues().time = 2.0f;
	shot->GetShootingValues().speed = 5000.0f;
	AddComponent(this->gameObjects["player1"], shot);

	Health* playerHealth = new Health;
	playerHealth->GetHealthValues().health = 200;
	playerHealth->GetHealthValues().damage = 10;
	AddComponent(this->gameObjects["player1"], playerHealth);

	//Ground
	AddGameobject("ground", CreateMode::NORMAL, nullptr, Color::GetColor(ColorCode::BLACK), true, Meshes::BOX, false);
	this->gameObjects["ground"]->GetTransform().position = { 0, -100, 0.0f };
	this->gameObjects["ground"]->GetTransform().scaling = { 100.0f, 0.50f, 0 };

	//Prefab Bullet
	AddGameobject("bullet", CreateMode::NORMAL, nullptr, Color::GetColor(ColorCode::BLUE), true, Meshes::TRIANGLE, false);
	this->gameObjects["bullet"]->GetTransform().position = { 1000, 1000, 1000 };
	this->gameObjects["bullet"]->GetTransform().scaling = { 0.07f, 0.20f, 0 };
	this->gameObjects["bullet"]->GetRigidbody()->GetRigidbodyValues().isEnabled = true;
	this->gameObjects["bullet"]->GetRigidbody()->GetRigidbodyValues().gravityEnabled = false;
	this->gameObjects["bullet"]->GetRigidbody()->GetRigidbodyValues().dragCoefficient = 0.001f;
	this->gameObjects["bullet"]->GetRigidbody()->GetRigidbodyValues().mass = 100.0f;
	this->gameObjects["bullet"]->SetTag("bullet");
	this->gameObjects["bullet"]->SetActive(false);
	this->gameObjects["bullet"]->SetVisiblity(false);

	Bullet* bullet = new Bullet;
	AddComponent(this->gameObjects["bullet"], bullet);

	//Prefab normal enemy
	AddGameobject("normalEnemy", CreateMode::NORMAL, nullptr, Color::GetColor(ColorCode::RED), true, Meshes::BOX, false);
	this->gameObjects["normalEnemy"]->GetTransform().position = { 0, 0, 0 };
	this->gameObjects["normalEnemy"]->GetTransform().scaling = { 0.3f, 0.3f, 0 };
	this->gameObjects["normalEnemy"]->GetRigidbody()->GetRigidbodyValues().isEnabled = true;
	this->gameObjects["normalEnemy"]->GetRigidbody()->GetRigidbodyValues().gravityEnabled = false;
	this->gameObjects["normalEnemy"]->GetRigidbody()->GetRigidbodyValues().mass = 100.0f;
	this->gameObjects["normalEnemy"]->SetTag("enemy");
	this->gameObjects["normalEnemy"]->SetActive(false);
	this->gameObjects["normalEnemy"]->SetVisiblity(false);

	Shooting* nEShot = new Shooting;
	nEShot->GetShootingValues().bulletSpeed = 1500;
	nEShot->GetShootingValues().time = 3.0f;
	AddComponent(this->gameObjects["normalEnemy"], nEShot);

	Health* nEHealth = new Health;
	AddComponent(this->gameObjects["normalEnemy"], nEHealth);

	Movement* nEMov = new Movement;
	nEMov->GetMovementValues().speed = 100;
	nEMov->GetMovementValues().maxSpeed = 10000.0f;
	AddComponent(this->gameObjects["normalEnemy"], nEMov);

	//Object Pools
	this->CreateObjectPool("bullets", 2000, this->gameObjects["bullet"]);
	this->CreateObjectPool("normalEnemies", 100, this->gameObjects["normalEnemy"]);


	//Enemies

	this->eSpawner = new EnemySpawner;
	this->eSpawner->Initialize();
} 


void Scene::CreateObjectPool(std::string name, ui32 amount, Gameobject* type)
{
	std::vector<Gameobject*> temp;

	for (int i = 0; i < amount; i++)
	{
		if (i == 0)
			temp.push_back(type);
		else
		{
			Gameobject* bullet = type->CreateCopy(true);
			temp.push_back(bullet);
		}
	}

	this->objectPools[name] = temp;
}

void Scene::AddGameobject(const char* name, CreateMode mode, Gameobject* parent, fColorRGBA color, bool hasCollision, Meshes mesh, bool isMirror)
{
	if (mode == CreateMode::EMPTY)
	{
		this->gameObjects[name] = new Gameobject(name, false, false, false, parent, color, hasCollision, mesh, isMirror);
	}
	else if (mode == CreateMode::NORMAL)
	{
		this->gameObjects[name] = new Gameobject(name, true, false, false, parent, color, hasCollision, mesh, isMirror);

		Application::GetInstancePtr()->GetRenderer()->InitializeGameobject(this->gameObjects[name]);
	}
}

void Scene::AddGameobject(Gameobject* gb)
{
	this->gameObjects[gb->GetName()] = gb;
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

void Scene::DeleteGameobject(Gameobject* gb, bool deactivate)
{
	gb->SetDeactivate(deactivate);
	this->deleteGb.push_back(gb);
}

void Scene::SetActivity(Gameobject* gb, Gameobject* parent, bool active)
{
	if (active)
	{
		if (parent == nullptr)
			this->root->AddChild(gb);
		else
			if (gb->GetParent() == nullptr)
				parent->AddChild(gb);
	}
	else
	{
		this->root->DeleteChild(gb, nullptr);
	}
}

void Scene::DeleteGameobjects(void)
{
	if (this->deleteGb.size() != 0)
	{
		for (Gameobject* gb : this->deleteGb)
		{
			if (gb->isDeactivate())
			{
				if (gb->GetTag() == "enemy")
					LOG("er");
				gb->SetActive(false);
			}
			else
			{

				Node* g = this->gameObjects[gb->GetName()]->GetParent();

				this->gameObjects[gb->GetName()]->GetParent()->GetChildren().remove(gb);
				this->gameObjects.erase(gb->GetName());
				this->root->GetAllChildren().remove(gb);
				gb->Cleanup();
			}
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

Gameobject* Scene::GetObjectItem(std::string objectPool, bool deleteObject)
{
	Gameobject* temp = this->objectPools[objectPool][this->objectPools[objectPool].size() - 1];

	if (deleteObject)
	{
		if (this->objectPools[objectPool].size() != 0)
		{
			this->objectPools[objectPool].pop_back();
			return temp;
		}
		else
			LOG("objectPool has no elements!")
	}
	else
	{
		this->objectPools[objectPool].pop_back();
		this->objectPools[objectPool].insert(this->objectPools[objectPool].begin(), temp);
		return temp;
	}

	LOG("Error")

	return nullptr;
}

EnemySpawner* Scene::GetEnemySpawner(void)
{
	return this->eSpawner;
}

bool & Scene::GetPaused()
{
	return this->paused;
}

bool & Scene::GetEnd()
{
	return this->end;
}

void Scene::Update(real deltaTime)
{
	Time::deltaTime = deltaTime;

	if (!this->paused && !this->end)
	{
		std::thread enemyThread(&EnemySpawner::Update, this->eSpawner);
		std::thread gameobjectThread(&Gameobject::Update, this->root);
		gameobjectThread.join();
		enemyThread.join();
	}
}

void Scene::Cleanup(void)
{
	std::map<std::string, Gameobject*>::iterator it;

	for (it = this->gameObjects.begin(); it != this->gameObjects.end(); it++)
	{
		it->second->Cleanup();
	}

	this->gameObjects.clear();
	this->root->Cleanup();
	this->eSpawner->Cleanup();
	delete this->eSpawner;
}
