//EXTERNAL INCLUDES
//INTERNAL INCLUDES
#include "components/bullet.h"
#include "typedefs/utils.h"
#include "scene/gameobject.h"

void Bullet::Initialize(char* comName, ComponentType comType, Gameobject* gb)
{
	//Initialize the base.
	Component::Initialize(comName, comType, gb);
	
}

void Bullet::Update(void)
{
	//Execute the components Update function.
	Component::Update();

	if (this->time > 0.0f)
	{
		this->GetGameObject()->GetTransform().position.y += speed;
		this->time -= 0.00008f;
	}
	else
		this->GetGameObject()->Cleanup();
}

void Bullet::Cleanup(void)
{
	Component::Cleanup();
}

void Bullet::SetBulletValues(real speed, real time)
{
	this->time = time;
	this->speed = speed;
}
