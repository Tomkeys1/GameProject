//EXTERNAL INCLUDES
#include <chrono>
#include <iostream>
//INTERNAL INCLUDES
#include "systems/inputhandler.h"
#include "typedefs/color.h"
#include "components/shooting.h"
#include "components/bullet.h"
#include "typedefs/utils.h"
#include "scene/gameobject.h"
#include "application.h"
#include "scene/scene.h"
#include "physics/rigidbody.h"

Shooting::Shooting()
{
	Component::Initialize("shooting", ComponentType::Shoot);
	this->shoot.available = false;
	this->shoot.timer = 0.0f;
	this->shoot.cooldown = 0.1f;
	this->shoot.shotID = 0;
	this->shoot.speed = 200.0f;
	this->shoot.bulletSpeed = this->shoot.speed;
}

//Void Initialize
void Shooting::Initialize(Gameobject* gb)
{
	//Initialize the base.
	Component::SetGameObject(gb);
}

void Shooting::Update(void)
{
	//Execute the components Update function.
	Component::Update();

		if (this->shoot.timer > 0.0f)
			this->shoot.timer -= 1.0f * Time::deltaTime;
		else
			this->shoot.available = true;

		if (this->GetGameObject()->GetTag() == "player")
		{
			PlayerShooting();
		}
		else if (this->GetGameObject()->GetTag() == "enemy")
		{
			NEnemyShooting();
		}

}

void Shooting::Cleanup(void)
{
	Component::Cleanup();

}

ShootingValues& Shooting::GetShootingValues(void)
{
	return this->shoot;
}

void Shooting::PlayerShooting(void)
{
	if (Input::GetInstancePtr()->GetKey(KeyCode::Space))
	{
		if (this->GetGameObject()->isVisisble())
		{
			this->shoot.speed += this->shoot.growth;
		}
	}

	if (Input::GetInstancePtr()->GetKeyUp(KeyCode::Space) && this->shoot.available)
	{
		this->shoot.available = false;
		this->shoot.timer = this->shoot.cooldown;
		this->shoot.bulletSpeed = this->shoot.speed;

		if (this->GetGameObject()->isVisisble())
		{
			Gameobject* temp = Application::GetInstancePtr()->GetScene()->GetObjectItem("bullets", false);
			temp->GetTransform().position = GetPos(temp);
			temp->GetEulerRotation() = this->GetGameObject()->GetEulerRotation();
			temp->SetVisi(true);
			temp->SetActive(true, this->GetGameObject());

			reinterpret_cast<Bullet*>(temp->GetComponent(ComponentType::Bullet))->GetBulletValues().dir = Math::GetForwardVector(this->GetGameObject()->GetEulerRotation());
			reinterpret_cast<Bullet*>(temp->GetComponent(ComponentType::Bullet))->GetBulletValues().speed = this->shoot.bulletSpeed;
			reinterpret_cast<Bullet*>(temp->GetComponent(ComponentType::Bullet))->GetBulletValues().time = this->shoot.time;

			this->shoot.shotID++;
		}
	}

	if (Input::GetInstancePtr()->GetKeyUp(KeyCode::Q))
	{

	}

}

void Shooting::NEnemyShooting(void)
{
	if (this->shoot.available)
	{
		this->shoot.available = false;
		this->shoot.timer = rand() % static_cast<ui32>(this->shoot.cooldown) + 5;

		if (this->GetGameObject()->isVisisble())
		{
			Gameobject* temp = Application::GetInstancePtr()->GetScene()->GetObjectItem("bullets", false);
			temp->GetTransform().position = GetPos(temp);
			temp->GetEulerRotation() = this->GetGameObject()->GetEulerRotation();
			temp->SetVisi(true);
			temp->SetActive(true, this->GetGameObject());

			reinterpret_cast<Bullet*>(temp->GetComponent(ComponentType::Bullet))->GetBulletValues().dir = Math::GetForwardVector(this->GetGameObject()->GetEulerRotation());
			reinterpret_cast<Bullet*>(temp->GetComponent(ComponentType::Bullet))->GetBulletValues().speed = this->shoot.bulletSpeed;
			reinterpret_cast<Bullet*>(temp->GetComponent(ComponentType::Bullet))->GetBulletValues().time = this->shoot.time;

			this->shoot.shotID++;
		}
	}
}

Math::Vec3 Shooting::GetPos(Gameobject* gb)
{
	Math::Vec3 temp = Math::Vec3{ this->GetGameObject()->GetWorldCorner(fColorRGBA{0, 1.5F, 0, 1.0f})};

	return temp;
}
