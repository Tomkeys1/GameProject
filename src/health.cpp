#include "components\health.h"
#include "components\bullet.h"
#include "scene/scene.h"
#include "application.h"

Health::Health()
{
	Component::Initialize("health", ComponentType::Health);
	this->health.damage = 25.0f;
	this->health.health = 100.0f;
	this->health.resistance = 1.0f;
}

void Health::Initialize(Gameobject* gb)
{
	Component::SetGameObject(gb);
}

void Health::Update(void)
{

	if (this->health.health <= 0.0f)
	{
		Application::GetInstancePtr()->GetScene()->DeleteGameobject(this->GetGameObject());
	}

	if (this->GetGameObject()->isColliding())
	{
		if (this->GetGameObject()->GetHitObject()->GetTag() == "bullet")
		{
			this->health.health -= this->health.damage / this->health.resistance;
			return;
		}
	}
}

void Health::Cleanup(void)
{
}

HealthValues& Health::GetHealthValues(void)
{
	return this->health;
}
