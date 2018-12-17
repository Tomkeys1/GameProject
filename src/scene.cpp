
//EXTERNAL INCLUDES
//INTERNAL INCLUDES
#include "scene/scene.h"
#include "application.h"
#include "rendering/renderer.h"
#include "typedefs/color.h"
#include "components/component.h"
#include "components/movement.h"
#include "components/shooting.h"
#include "components/bullet.h"


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
	AddGameobject("player2", CreateMode::EMPTY, this->GetGameobject("player1"));

	Vertex* v = new Vertex[4];
	ui32* i = new ui32[6];

	v[0].position = fColorRGBA{ -1, 1, 0, 1.0f };
	v[0].color = Color::GetColor(ColorCode::BLUE);

	v[1].position = fColorRGBA{ 1, 1, 0, 1.0f };
	v[1].color = Color::GetColor(ColorCode::BLUE);

	v[2].position = fColorRGBA{ 1, -1, 0, 1.0f };
	v[2].color = Color::GetColor(ColorCode::BLUE);

	v[3].position = fColorRGBA{ -1, -1, 0, 1.0f };
	v[3].color = Color::GetColor(ColorCode::BLUE);

	i[0] = 3;
	i[1] = 0;
	i[2] = 1;
	i[3] = 3;
	i[4] = 1;
	i[5] = 2;

	AddMesh(this->gameObjects["player2"], v, i, 4, 6);

	Movement* mov = new Movement;
	Shooting* shot = new Shooting;
	AddComponent(this->gameObjects["player1"], mov);
	AddComponent(this->gameObjects["player1"], shot);

	this->gameObjects["player1"]->GetTransform().position = { 0, -0.7f, 0.0f };
	this->gameObjects["player1"]->GetTransform().scaling = { 20, 40, 0 };
}

void Scene::AddGameobject(const char* name, CreateMode mode, Gameobject* parent, fColorRGBA color)
{
	if (mode == CreateMode::EMPTY)
	{
		this->gameObjects[name] = new Gameobject(false, false, false, parent);
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
		this->gameObjects[name] = new Gameobject(true, false, false, parent, color);
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
	}

	gb->AddComponent(com);
}

Gameobject* Scene::GetGameobject(std::string name)
{
	return this->gameObjects[name];
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
