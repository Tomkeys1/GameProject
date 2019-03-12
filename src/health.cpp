//EXTERNAL INCLUDES
#include <chrono>
//INTERNAL INCLUDES
#include "typedefs/color.h"
#include "rendering/geometry.h"
#include "components/enemies/espawnbehaviour.h"
#include "components/health.h"
#include "components/bullet.h"
#include "scene/scene.h"
#include "application.h"

Health::Health()
{
	Component::Initialize("health", ComponentType::Health);
	this->health.damage = 25.0f;
	this->health.health = 100.0f;
	this->health.resistance = 1.0f;
	this->health.shield = 0.0f;
	this->damaging = false;
}

void Health::Initialize(Gameobject* gb)
{
	Component::SetGameObject(gb);
}

void Health::Update(void)
{
	Component::Update();

	if (this->health.health <= 0)
	{
		//this->GetGameObject()->GetMesh()->SetColor(Color::GetColor(ColorCode::GREEN));
		Application::GetInstancePtr()->GetScene()->GetEnemySpawner()->GetDeadEnemies()++;
		Application::GetInstancePtr()->GetScene()->DeleteGameobject(this->GetGameObject(), true);
	}
}

void Health::Cleanup(void)
{
	Component::Cleanup();
}

HealthValues& Health::GetHealthValues(void)
{
	return this->health;
}