
//EXTERNAL INCLUDES
//INTERNAL INCLUDES
#include "application.h"
#include "scene/scene.h"
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
	this->movement.direction = Math::Vec3::zero;
	this->movement.stoppingCoefficient = 25.0f;
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

	if (this->GetGameObject()->GetTag() == "enemy")
	{
		if (!this->GetGameObject()->inViewport())
		{
			if (this->movement.direction.x > 0.0f)
			{
				this->GetGameObject()->GetTransform().position.x -= 200.0f;
				this->GetGameObject()->GetTransform().position.y -= 20;
			}
			else if (this->movement.direction.x < 0.0f)
			{
				this->GetGameObject()->GetTransform().position.x += 200.0f;
				this->GetGameObject()->GetTransform().position.y -= 20;
			}
			else
				Application::GetInstancePtr()->GetScene()->GetEnd() = true;
		}

		this->movement.direction = Math::Negate(Math::GetRightVector(this->GetGameObject()->GetEulerRotation()));
		this->movement.velocity += this->movement.speed;

		this->GetGameObject()->GetRigidbody()->GetRigidbodyValues().movementDir = this->movement.direction;
		this->GetGameObject()->GetRigidbody()->GetRigidbodyValues().velocity = Math::Clamp(this->movement.velocity, -this->movement.maxSpeed, this->movement.maxSpeed);
	}
	else
	{
		if (!this->GetGameObject()->inViewport())
		{
			if (this->movement.direction.x > 0.0f)
				this->GetGameObject()->GetTransform().position.x -= 200.0f;
			else
				this->GetGameObject()->GetTransform().position.x += 200.0f;
		}

		Move();
	}
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
	else if (Input::GetInstancePtr()->GetKey(KeyCode::S))
	{
		this->movement.direction = this->movement.direction;
		this->movement.velocity = 0.0f;
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
