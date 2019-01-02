#include "components\abilities\gravityshot.h"
#include "typedefs/utils.h"
#include "scene/gameobject.h"
#include "application.h"
#include "scene/scene.h"
#include "physics/rigidbody.h"
#include "systems/inputhandler.h"
#include "typedefs/color.h"

GravityShot::GravityShot()
{
	Component::Initialize("gravityShot", ComponentType::GravityShot);
}

void GravityShot::Initialize(Gameobject * gb)
{
	Component::SetGameObject(gb);
}

void GravityShot::Update(void)
{
	if (Input::GetInstancePtr()->GetKeyUp(KeyCode::Q))
	{

	}
}

void GravityShot::Cleanup(void)
{

}

GravityShotValues& GravityShot::GetBulletValues(void)
{
	return this->gravityShot;
}
