
//EXTERNAL INCLUDES
//INTERNAL INCLUDES
#include "systems/inputhandler.h"
#include "components/movement.h"
#include "typedefs/utils.h"
#include "math/vector3.h"
#include "math/mathfunctions.h"

Movement::Movement()
{
	Component::Initialize("movement", ComponentType::Movement);
}

//Void Initialize
void Movement::Initialize(Gameobject* gb)
{
	//Initialize the base.
	Component::SetGameObject(gb);
}

void Movement::Update(void)
{
	//Execute the components Update function.
	Component::Update();

	Rotate();

	if (!this->GetGameObject()->isColliding() || this->GetGameObject()->GetHitObject()->isTrigger())
		Move();
	
}

void Movement::Cleanup(void)
{
	Component::Cleanup();

}

void Movement::Move()
{
	if (Input::GetInstancePtr()->GetKey(KeyCode::W))
	{
		this->direction = Math::GetForwardVector(this->GetGameObject()->GetEulerRotation());
		this->speed += this->velocity;
	}
	else if (Input::GetInstancePtr()->GetKey(KeyCode::S))
	{
		this->direction = Math::Negate(Math::GetForwardVector(this->GetGameObject()->GetEulerRotation()));
		this->speed += this->velocity;
	}
	else if (Input::GetInstancePtr()->GetKey(KeyCode::D))
	{
		this->direction = Math::GetRightVector(this->GetGameObject()->GetEulerRotation());
		this->speed += this->velocity;
	}
	else if (Input::GetInstancePtr()->GetKey(KeyCode::A))
	{
		this->direction = Math::Negate(Math::GetRightVector(this->GetGameObject()->GetEulerRotation()));
		this->speed += this->velocity;
	}
	else
	{
		this->speed = 0.0f;
	}
	
	this->GetGameObject()->GetTransform().position += this->direction * Math::Clamp(this->speed, -this->maxSpeed, this->maxSpeed);
}

void Movement::Rotate(void)
{
	if (Input::GetInstancePtr()->GetKey(KeyCode::E))
	{
		this->GetGameObject()->GetEulerRotation().z -= 0.01f;
	}
	else if (Input::GetInstancePtr()->GetKey(KeyCode::Q))
	{
		this->GetGameObject()->GetEulerRotation().z += 0.01f;
	}
}
