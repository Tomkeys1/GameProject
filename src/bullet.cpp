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
		if (this->GetGameObject()->GetHitObject() != nullptr)
		{
			if (this->GetGameObject()->GetHitObject() == reinterpret_cast<Gameobject*>(this->GetGameObject()->GetParent()))
				this->GetGameObject()->GetRigidbody()->AddForce(this->bullet.dir, this->bullet.speed);
		}
		else
		{
			this->GetGameObject()->GetRigidbody()->AddForce(this->bullet.dir, this->bullet.speed);
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
