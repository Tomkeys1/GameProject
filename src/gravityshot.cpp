//EXTERNAL INCLUDES
#include <chrono>
//INTERNAL INCLUDES
#include "components/abilities/gravityshot.h"
#include "components/health.h"
#include "physics/rigidbody.h"
#include "typedefs/utils.h"
#include "scene/gameobject.h"
#include "scene/scene.h"
#include "application.h"
#include "math/vector3.h"

GravityShot::GravityShot()
{
	Component::Initialize("gravityBullet", ComponentType::GravityShot);
	this->origin = this->GetGameObject();
}

//Void Initialize
void GravityShot::Initialize(Gameobject* gb)
{
	//Initialize the base.
	Component::SetGameObject(gb);
}

void GravityShot::Update(void)
{
	if (!this->gravityShot.activated)
		return;
	//Execute the components Update function.
	Component::Update();

	if (this->gravityShot.time > 0.0f)
	{
		this->GetGameObject()->GetRigidbody()->GetRigidbodyValues().movementDir = Math::Vec3::zero;

		if (this->gravityShot.timeInAir > 0.0f)
		{
			this->GetGameObject()->GetRigidbody()->GetRigidbodyValues().movementDir = this->gravityShot.dir;
			if (this->GetGameObject()->isColliding())
			{
				if (this->GetGameObject()->GetHitObject() != nullptr)
				{
					if (this->GetGameObject()->GetHitObject() == reinterpret_cast<Gameobject*>(this->GetGameObject()->GetParent()) || this->GetGameObject()->GetHitObject()->GetComponent(ComponentType::Bullet) != nullptr || this->GetGameObject()->GetHitObject()->GetTag() == reinterpret_cast<Gameobject*>(this->GetGameObject()->GetParent())->GetTag())
						this->GetGameObject()->GetRigidbody()->GetRigidbodyValues().velocity = this->gravityShot.speed;
					else
					{
						if (this->GetGameObject()->GetHitObject()->IsMirror() && !this->deflecting)
						{
							if (this->mirrorThread.joinable())
								this->mirrorThread.join();
							this->mirrorThread = std::thread(&GravityShot::Deflect, this);
						}
						else if (!this->GetGameObject()->GetHitObject()->IsMirror())
						{
							if (this->gravityShot.timeInAir > 0.0f)
							{
								this->origin = this->GetGameObject()->GetHitObject();
							}

							if (this->GetGameObject()->GetHitObject()->GetComponent(ComponentType::Health) != nullptr)
							{
								reinterpret_cast<Health*>(this->GetGameObject()->GetHitObject()->GetComponent(ComponentType::Health))->GetHealthValues().health -= (reinterpret_cast<Health*>(this->GetGameObject()->GetHitObject()->GetComponent(ComponentType::Health))->GetHealthValues().damage * 0.3f);
							}

							this->GetGameObject()->GetTransform().position = Math::Vec3{ 1000, 1000, 1000 };
						}
					}
				}
			}
			else
			{
				this->GetGameObject()->GetRigidbody()->GetRigidbodyValues().velocity = this->gravityShot.speed;
			}
		}
		else
		{
			if (this->gravityShot.timeToExplode > 0.0f)
			{
				this->origin->GetRigidbody()->GetRigidbodyValues().isEnabled = true;
				this->origin->GetRigidbody()->GetRigidbodyValues().movementDir = Math::Vec3::zero;
				this->GetGameObject()->GetRigidbody()->GetRigidbodyValues().velocity = 0.0f;

				for (Node* gb : Application::GetInstancePtr()->GetScene()->GetGameobject()->GetAllChildren())
				{
					Gameobject* temp = reinterpret_cast<Gameobject*>(gb);

					if (temp->hasCollision() && temp->GetRigidbody()->GetRigidbodyValues().isEnabled)
					{
						if (temp != this->GetGameObject())
						{
							if (Math::Distance(this->GetGameObject()->GetTransform().position, temp->GetTransform().position) < this->GetBulletValues().gravityRadius)
							{
								temp->GetRigidbody()->SetGravityCenter(this->origin);
							}
						}
					}
				}
			}
			else
			{
				this->origin = this->GetGameObject();
				for (Node* gb : Application::GetInstancePtr()->GetScene()->GetGameobject()->GetAllChildren())
				{
					Gameobject* temp = reinterpret_cast<Gameobject*>(gb);

					if (temp->hasCollision() && temp->GetRigidbody()->GetRigidbodyValues().isEnabled)
					{
						if (temp != this->GetGameObject())
						{
							if (Math::Distance(this->GetGameObject()->GetTransform().position, temp->GetTransform().position) < this->GetBulletValues().gravityRadius)
							{
								Application::GetInstancePtr()->GetScene()->DeleteGameobject(temp, true);
							}
						}
					}
				}
				Application::GetInstancePtr()->GetScene()->DeleteGameobject(this->GetGameObject(), true);
			}

			this->gravityShot.timeToExplode -= 1.0f * Time::deltaTime;
		}

		this->gravityShot.timeInAir -= 1.0f * Time::deltaTime;
		this->gravityShot.time -= 1.0f * Time::deltaTime;
	}
	else
	{
		if (this->origin == this->GetGameObject())
			Application::GetInstancePtr()->GetScene()->DeleteGameobject(this->origin, true);
		else
		{
			Application::GetInstancePtr()->GetScene()->DeleteGameobject(this->origin, true);
			Application::GetInstancePtr()->GetScene()->DeleteGameobject(this->GetGameObject(), true);
		}
	}

}

void GravityShot::Cleanup(void)
{
	Component::Cleanup();
	this->origin = nullptr;
	delete this->origin;
}

GravityShotValues& GravityShot::GetBulletValues(void)
{
	return this->gravityShot;
}

void GravityShot::Deflect(void)
{
	this->deflecting = true;

	Math::Vec3 normal = this->GetGameObject()->GetRigidbody()->GetImpactNormal();
	real dot = Math::Dot(this->gravityShot.dir, normal);
	this->gravityShot.dir = this->gravityShot.dir - (normal * 2.0f) * dot;

	Math::Vec3 vec1 = Math::GetForwardVector(this->GetGameObject()->GetEulerRotation());
	Math::Vec3 vec2 = this->gravityShot.dir;
	dot = Math::Dot(vec1, vec2);
	// Divide the dot by the product of the magnitudes of the vectors
	dot = dot / (Math::Length(vec1) * Math::Length(vec2));
	//Get the arc cosin of the angle, you now have your angle in radians 
	real arccos = acos(dot);
	//Multiply by 180/Mathf.PI to convert to degrees
	real angle = arccos * 180 / M_PI;
	this->GetGameObject()->GetEulerRotation().z += angle;

	std::this_thread::sleep_for(std::chrono::milliseconds(int(1 * 100)));
	this->deflecting = false;
}
