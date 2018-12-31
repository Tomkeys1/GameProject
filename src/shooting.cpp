//EXTERNAL INCLUDES
#include <chrono>
#include <iostream>
//INTERNAL INCLUDES
#include "systems/inputhandler.h"
#include "typedefs/color.h"
#include "components/shooting.h"
#include "components/collision.h"
#include "components/bullet.h"
#include "typedefs/utils.h"
#include "scene/gameobject.h"
#include "application.h"
#include "scene/scene.h"
#include "physics/rigidbody.h"

Shooting::Shooting()
{
	Component::Initialize("shooting", ComponentType::Shoot);
	this->shoot.available = true;
	this->shoot.timer = 1.0f;
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
			this->shoot.timer -= 2.0f * Time::deltaTime;
		else
			this->shoot.available = true;

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
		this->shoot.timer = 1.7f;

		if (this->GetGameObject()->isVisisble())
		{
			using namespace std;
			auto start = chrono::steady_clock::now();

 			std::string tempStr = this->GetGameObject()->GetName();
			tempStr += " shot";
			Application::GetInstancePtr()->GetScene()->AddGameobject(tempStr.c_str(), CreateMode::NORMAL, this->GetGameObject(), Color::GetColor(ColorCode::BLUE));
			Gameobject* temp = Application::GetInstancePtr()->GetScene()->GetGameobject(tempStr.c_str());
			temp->GetTransform().scaling = { 0.05f, 0.15f, 0 };
			temp->GetTransform().position = GetPos(temp);
			temp->GetEulerRotation() = this->GetGameObject()->GetEulerRotation();
			temp->GetRigidbody()->GetRigidbodyValues().isEnabled = true;
			temp->GetRigidbody()->GetRigidbodyValues().gravityEnabled = false;
			temp->GetRigidbody()->GetRigidbodyValues().dragCoefficient = 0.001f;
			temp->GetRigidbody()->GetRigidbodyValues().mass = 100.0f;
			temp->SetTag("bullet");

			Bullet* bullet = new Bullet;
			Application::GetInstancePtr()->GetScene()->AddComponent(temp, bullet);
			bullet->GetBulletValues().dir = Math::GetForwardVector(this->GetGameObject()->GetEulerRotation());
			bullet->GetBulletValues().speed = this->shoot.speed;
			bullet->GetBulletValues().time = this->shoot.time;

			this->shoot.speed = 20.0f;

			Collision* col = new Collision;
			Application::GetInstancePtr()->GetScene()->AddComponent(temp, col);


			auto end = chrono::steady_clock::now();

			cout << "Elapsed time in milliseconds : "
				<< chrono::duration_cast<chrono::milliseconds>(end - start).count()
				<< " ms" << endl;
		}
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

Math::Vec3 Shooting::GetPos(Gameobject* gb)
{
	Math::Vec3 temp = Math::Vec3{ this->GetGameObject()->GetWorldCorner(fColorRGBA{0, 1, 0, 1.0f})};

	return temp;
}
