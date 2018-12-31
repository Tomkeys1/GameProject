
//EXTERNAL INCLUDES
//INTERNAL INCLUDES
#include "systems/inputhandler.h"
#include "components/movement.h"
#include "typedefs/utils.h"
#include "typedefs/time.h"
#include "math/vector3.h"
#include "math/mathfunctions.h"
#include "physics/rigidbody.h"

Movement::Movement()
{
	Component::Initialize("movement", ComponentType::Movement);
	this->movement.speed = 0.0f;
	this->movement.stoppingCoefficient = 50.0f;
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
	Move();

}

void Movement::Cleanup(void)
{
	Component::Cleanup();

}

MovementValues& Movement::GetMovementValues(void)
{
	return this->movement;
}

void Movement::Move()
{
	if (Input::GetInstancePtr()->GetKey(KeyCode::D))
	{
		this->movement.direction = Math::GetRightVector(this->GetGameObject()->GetEulerRotation());
		this->movement.speed += this->movement.velocity;
	}
	else if (Input::GetInstancePtr()->GetKey(KeyCode::A))
	{
		this->movement.direction = Math::Negate(Math::GetRightVector(this->GetGameObject()->GetEulerRotation()));
		this->movement.speed += this->movement.velocity;
	}
	else
	{
		if (this->movement.speed > 0.0f)
		{
			this->movement.speed += (0 - this->movement.speed) / this->movement.stoppingCoefficient;
		}
	}

	this->GetGameObject()->GetRigidbody()->AddForce(this->movement.direction, Math::Clamp(this->movement.speed, 0.0f, this->movement.maxSpeed));
}

void Movement::Rotate(void)
{
	if (Input::GetInstancePtr()->GetKey(KeyCode::E))
	{
		this->GetGameObject()->GetEulerRotation().z -= this->movement.rotationSpeed * Time::deltaTime;
	}
	else if (Input::GetInstancePtr()->GetKey(KeyCode::Q))
	{
		this->GetGameObject()->GetEulerRotation().z += this->movement.rotationSpeed * Time::deltaTime;
	}
}
