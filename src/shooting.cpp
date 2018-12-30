//EXTERNAL INCLUDES
//INTERNAL INCLUDES
#include "systems/inputhandler.h"
#include "typedefs/color.h"
#include "components/shooting.h"
#include "components/bullet.h"
#include "typedefs/utils.h"
#include "scene/gameobject.h"
#include "application.h"
#include "scene/scene.h"

Shooting::Shooting()
{
	Component::Initialize("shooting", ComponentType::Shoot);
	this->growth = 0.000006f;
	this->time = 2.0f;
	this->speed = 0.04f;
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

	if (Input::GetInstancePtr()->GetKey(KeyCode::Space))
	{
		if (this->GetGameObject()->isVisisble())
		{
			this->speed += this->growth;
		}
	}

	if (Input::GetInstancePtr()->GetKeyUp(KeyCode::Space))
	{
		if (this->GetGameObject()->isVisisble())
		{
			std::string tempStr = this->GetGameObject()->GetName();
			tempStr += " shot";
			Application::GetInstancePtr()->GetScene()->AddGameobject(tempStr.c_str(), CreateMode::NORMAL, this->GetGameObject(), Color::GetColor(ColorCode::RED));
			Gameobject* temp = Application::GetInstancePtr()->GetScene()->GetGameobject(tempStr.c_str());
			temp->GetTransform().scaling = { 0.05f, 0.15f, 0 };
			temp->GetTransform().position = GetPos(temp);
			temp->GetEulerRotation() = this->GetGameObject()->GetEulerRotation();
			
			Bullet* bullet = new Bullet;
			Application::GetInstancePtr()->GetScene()->AddComponent(temp, bullet);
			bullet->SetBulletValues(this->speed, this->time, Math::GetForwardVector(this->GetGameObject()->GetEulerRotation()));
			this->speed = 0.04f;
		}
	}
}

void Shooting::Cleanup(void)
{
	Component::Cleanup();

}

Math::Vec3 Shooting::GetPos(Gameobject* gb)
{
	Math::Vec3 temp = Math::Vec3{ this->GetGameObject()->GetWorldCorner(fColorRGBA{ -1, -1, 0, 1.0f }).x, this->GetGameObject()->GetWorldCorner(fColorRGBA{ 1, 1, 0, 1.0f }).y, 0.0f };

	real middle = Math::Distance(this->GetGameObject()->GetWorldCorner(fColorRGBA{ 1, 1, 0, 1.0f }), temp);
	middle = middle * 0.5f;
	temp.x += middle;

	return temp;
}
