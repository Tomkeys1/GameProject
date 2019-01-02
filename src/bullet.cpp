//EXTERNAL INCLUDES
#include <chrono>
#include <iostream>
//INTERNAL INCLUDES
#include "components/bullet.h"
#include "physics/rigidbody.h"
#include "typedefs/utils.h"
#include "scene/gameobject.h"
#include "scene/scene.h"
#include "application.h"
#include "math/vector3.h"

Bullet::Bullet()
{
	Component::Initialize("bullet", ComponentType::Bullet);
}

//Void Initialize
void Bullet::Initialize(Gameobject* gb)
{
	//Initialize the base.
	Component::SetGameObject(gb);
}

void Bullet::Update(void)
{
	//Execute the components Update function.
	Component::Update();

	if (this->bullet.time > 0.0f)
	{
		this->GetGameObject()->GetRigidbody()->GetRigidbodyValues().movementDir = this->bullet.dir;
		if (this->GetGameObject()->isColliding())
		{
			if (this->GetGameObject()->GetHitObject() == reinterpret_cast<Gameobject*>(this->GetGameObject()->GetParent()))
				this->GetGameObject()->GetRigidbody()->GetRigidbodyValues().velocity = this->bullet.speed;
			else
			{
				this->GetGameObject()->SetCollision(false);
				this->GetGameObject()->SetVisi(false);
				this->GetGameObject()->SetIsColliding(false);
			}
		}
		else
		{
			this->GetGameObject()->GetRigidbody()->GetRigidbodyValues().velocity = this->bullet.speed;
		}
		this->bullet.time -= 2.0f * Time::deltaTime;
	}
	else
	{
		Application::GetInstancePtr()->GetScene()->DeleteGameobject(this->GetGameObject());
	}

}

void Bullet::Cleanup(void)
{
	Component::Cleanup();
}

BulletValues& Bullet::GetBulletValues(void)
{
	return this->bullet;
}
