//EXTERNAL INCLUDES
//INTERNAL INCLUDES
#include "systems/inputhandler.h"
#include "components/shooting.h"
#include "components/bullet.h"
#include "typedefs/utils.h"
#include "scene/gameobject.h"

void Shooting::Initialize(char* comName, ComponentType comType, Gameobject* gb)
{
	//Initialize the base.
	Component::Initialize(comName, comType, gb);

	this->growth = 0.00000001f;
	this->time = 2.0f;
	this->speed = 0.00004f;

}

void Shooting::Update(void)
{
	//Execute the components Update function.
	Component::Update();

	if (Input::GetInstancePtr()->GetKey(KeyCode::Space))
	{
		this->speed += this->growth;
	}

	if (Input::GetInstancePtr()->GetKeyUp(KeyCode::Space))
	{
		Gameobject* shot = new Gameobject(true, false, false, fColorRGBA{ 0.972f, 0.125f, 0.125f, 1.0f }, this->GetGameObject());
		shot->GetTransform().scaling = {5, 15, 0};
		shot->GetTransform().position = this->GetGameObject()->GetTransform().position + Math::Vec3{0, 0.25f, 0};
		Bullet* bullet = new Bullet;
		bullet->Initialize("bullet", ComponentType::Bullet, shot);
		shot->AddComponent(bullet);
		bullet->SetBulletValues(this->speed, this->time);
		shot->SetName("Shot1");
		this->speed = 0.00004f;
	}
}

void Shooting::Cleanup(void)
{
	Component::Cleanup();

}
