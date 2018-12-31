
//EXTERNAL INCLUDES
//INTERNAL INCLUDES
#include "physics\rigidbody.h"
#include "scene/gameobject.h"
#include "typedefs/time.h"

Rigidbody::Rigidbody(Gameobject* gb)
{
	this->gameobject = gb;
	this->gravityGb = nullptr;
}

void Rigidbody::Update(void)
{
	//Area of Object
	real radius1 = Math::Distance(this->gameobject->GetWorldCorner(fColorRGBA{ -1, 1, 0, 1.0f }, this->gameobject->GetModelMatrixNoRotation()), this->gameobject->GetWorldCorner(fColorRGBA{ 1, 1, 0, 1.0f }, this->gameobject->GetModelMatrixNoRotation()));
	radius1 = radius1 * 0.5f;
	real radius2 = Math::Distance(this->gameobject->GetWorldCorner(fColorRGBA{ 1, -1, 0, 1.0f }, this->gameobject->GetModelMatrixNoRotation()), this->gameobject->GetWorldCorner(fColorRGBA{ 1, 1, 0, 1.0f }, this->gameobject->GetModelMatrixNoRotation()));
	radius2 = radius2 * 0.5f;
	this->rigidBody.areaOfObject = radius1 * radius2;

	//Gravity
	if (this->rigidBody.isEnabled && !this->rigidBody.isKinematic && this->rigidBody.gravityEnabled)
	{
		if (this->gameobject->GetHitObject() == nullptr)
		{
			Gravity();
		}
		else
		{
			if (this->gameobject->GetHitObject()->isTrigger())
			{
				Gravity();
			}
		}
	}
}

void Rigidbody::Cleanup(void)
{
}

void Rigidbody::SetGravityCenter(Gameobject* gb)
{
	this->gravityGb = gb;
}

void Rigidbody::AddForce(Math::Vec3 direction, real force)
{
	this->gameobject->GetTransform().position += direction * CalculateVelocity((Time::deltaTime * (force / this->rigidBody.mass)));
}

RigidbodyValues& Rigidbody::GetRigidbodyValues()
{
	return this->rigidBody;
}

void Rigidbody::Gravity(void)
{
	if (this->gravityGb != nullptr)
	{
		this->gravityCenter = this->gravityGb->GetTransform().position;
		this->massOfCenter = this->gravityGb->GetRigidbody()->GetRigidbodyValues().mass;
		this->rigidBody.gravityDir =  Math::Negate(this->gameobject->GetTransform().position - this->gravityGb->GetTransform().position);
	}
	else
	{
		this->gravityCenter = { this->gameobject->GetTransform().position.x, FLT_MIN , this->gameobject->GetTransform().position.z };
		this->massOfCenter = 96500000000.0f;
		this->rigidBody.gravityDir = Math::Vec3::neg_unit_y;
	}

	this->gravity = this->gravityConstant * ((this->rigidBody.mass * this->massOfCenter) / (Math::Distance(this->gameobject->GetTransform().position, this->gravityCenter)) * Math::Distance(this->gameobject->GetTransform().position, this->gravityCenter));
	
	this->gameobject->GetTransform().position += this->rigidBody.gravityDir * CalculateVelocity(gravity) * Time::deltaTime;
}

real Rigidbody::CalculateVelocity(real force)
{
	return sqrt((2.0f * abs(force)) / (this->rigidBody.airDensity * this->rigidBody.dragCoefficient * this->rigidBody.areaOfObject));
}
