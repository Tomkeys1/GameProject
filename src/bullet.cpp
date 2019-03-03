//EXTERNAL INCLUDES
#include <chrono>
//INTERNAL INCLUDES
#include "components/bullet.h"
#include "components/health.h"
#include "physics/rigidbody.h"
#include "typedefs/utils.h"
#include "scene/gameobject.h"
#include "scene/scene.h"
#include "application.h"
#include "math/vector3.h"

Bullet::Bullet()
{
	Component::Initialize("bullet", ComponentType::Bullet);
}

//Void Initialize
void Bullet::Initialize(Gameobject* gb)
{
	//Initialize the base.
	Component::SetGameObject(gb);
}

void Bullet::Update(void)
{
	if (!this->bullet.activated)
		return;
	//Execute the components Update function.
	Component::Update();

	if (this->bullet.time > 0.0f)
	{
		this->GetGameObject()->GetRigidbody()->GetRigidbodyValues().movementDir = this->bullet.dir;
		if (this->GetGameObject()->isColliding())
		{
			if (this->GetGameObject()->GetHitObject() != nullptr)
			{
				if (this->GetGameObject()->GetHitObject() == reinterpret_cast<Gameobject*>(this->GetGameObject()->GetParent()) || this->GetGameObject()->GetHitObject()->GetComponent(ComponentType::Bullet) != nullptr || this->GetGameObject()->GetHitObject()->GetTag() == reinterpret_cast<Gameobject*>(this->GetGameObject()->GetParent())->GetTag())
					this->GetGameObject()->GetRigidbody()->GetRigidbodyValues().velocity = this->bullet.speed;
				else
				{
					if (this->GetGameObject()->GetHitObject()->IsMirror() && !this->deflecting)
					{
						if (this->mirrorThread.joinable())
							this->mirrorThread.join();
						this->mirrorThread = std::thread(&Bullet::Deflect, this);
					}
					else if (!this->GetGameObject()->GetHitObject()->IsMirror())
					{
						if (this->GetGameObject()->GetHitObject()->GetComponent(ComponentType::Health) != nullptr)
						{
							reinterpret_cast<Health*>(this->GetGameObject()->GetHitObject()->GetComponent(ComponentType::Health))->GetHealthValues().health -= reinterpret_cast<Health*>(this->GetGameObject()->GetHitObject()->GetComponent(ComponentType::Health))->GetHealthValues().damage;
						}
						Application::GetInstancePtr()->GetScene()->DeleteGameobject(this->GetGameObject(), true);
					}
				}
			}
		}
 		else
		{
			this->GetGameObject()->GetRigidbody()->GetRigidbodyValues().velocity = this->bullet.speed;
		}

		this->bullet.time -= 1.0f * Time::deltaTime;
	}
	else
	{
		Application::GetInstancePtr()->GetScene()->DeleteGameobject(this->GetGameObject(), true);
	}

}

void Bullet::Cleanup(void)
{
	Component::Cleanup();
}

BulletValues& Bullet::GetBulletValues(void)
{
	return this->bullet;
}

void Bullet::Deflect(void)
{
	this->deflecting = true;

	Math::Vec3 normal = this->GetGameObject()->GetRigidbody()->GetImpactNormal();
	real dot = Math::Dot(this->bullet.dir, normal);
	this->bullet.dir = this->bullet.dir - (normal * 2.0f) * dot;

	Math::Vec3 vec1 = Math::GetForwardVector(this->GetGameObject()->GetEulerRotation());
	Math::Vec3 vec2 = this->bullet.dir;
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
