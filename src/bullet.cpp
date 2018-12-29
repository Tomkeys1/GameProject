//EXTERNAL INCLUDES
//INTERNAL INCLUDES
#include "components/bullet.h"
#include "typedefs/utils.h"
#include "scene/gameobject.h"

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

	if (this->time > 0.0f)
	{
		this->GetGameObject()->GetTransform().position += this->dir * this->speed;
		this->time -= 0.0008f;
	}
	else
	{
		this->GetGameObject()->Cleanup();
	}
}

void Bullet::Cleanup(void)
{
	Component::Cleanup();
}

void Bullet::SetBulletValues(real speed, real time, Math::Vec3 direction)
{
	this->time = time;
	this->speed = speed;
	this->dir = direction;
}
