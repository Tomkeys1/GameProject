
//EXTERNAL INCLUDES
//INTERNAL INCLUDES
#include "systems/inputhandler.h"
#include "components/movement.h"
#include "typedefs/utils.h"
#include "typedefs/time.h"
#include "math/vector3.h"
#include "physics/rigidbody.h"

Movement::Movement()
{
	Component::Initialize("movement", ComponentType::Movement);
	this->movement.velocity = 0.0f;
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

	if (!this->GetGameObject()->inViewport())
	{
		if(this->movement.direction.x > 0.0f)
			this->GetGameObject()->GetTransform().position.x -= 200.0f;
		else
			this->GetGameObject()->GetTransform().position.x += 200.0f;
	}

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
		this->movement.velocity += this->movement.speed;
	}
	else if (Input::GetInstancePtr()->GetKey(KeyCode::A))
	{
		this->movement.direction = Math::Negate(Math::GetRightVector(this->GetGameObject()->GetEulerRotation()));
		this->movement.velocity += this->movement.speed;
	}
	else
	{
		if (this->movement.velocity > 0.0f)
		{
			this->movement.velocity += (0 - this->movement.velocity) / this->movement.stoppingCoefficient;
		}
	}

	this->GetGameObject()->GetRigidbody()->GetRigidbodyValues().movementDir = this->movement.direction;
	this->GetGameObject()->GetRigidbody()->GetRigidbodyValues().velocity = Math::Clamp(this->movement.velocity, -this->movement.maxSpeed, this->movement.maxSpeed);
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
