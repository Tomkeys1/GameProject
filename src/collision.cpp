
//EXTERNAL INCLUDES
//INTERNAL INCLUDES
#include "application.h"
#include "scene/gameobject.h"
#include "scene/scene.h"
#include "systems/inputhandler.h"
#include "components/collision.h"
#include "typedefs/utils.h"
#include "rendering/camera.h"
#include "rendering/renderer.h"


Collision::Collision()
{
	Component::Initialize("collision", ComponentType::Collision);
}

//Void Initialize
void Collision::Initialize(Gameobject* gb)
{
	//Initialize the base.
	Component::SetGameObject(gb);
}

void Collision::Update(void)
{
	//Execute the components Update function.
	Component::Update();

	for (Node* gb : Application::GetInstancePtr()->GetScene()->GetGameobject()->GetAllChildren())
	{
		Gameobject* temp = reinterpret_cast<Gameobject*>(gb);

		if (temp->hasCollision())
		{
			if (temp != this->GetGameObject())
			{
				if (Math::Distance(this->GetGameObject()->GetTransform().position, temp->GetTransform().position) < this->collisionRange)
				{
					if (CheckCollision(temp) == true)
					{
						if (this->GetGameObject()->GetHitObject() == nullptr)
						{
							this->GetGameObject()->SetHitObject(temp);
							temp->SetHitObject(this->GetGameObject());
							temp->SetIsColliding(true);
						}

						this->GetGameObject()->SetIsColliding(true);
					}
					else
					{
						if (this->GetGameObject()->GetHitObject() == temp)
						{
							this->GetGameObject()->SetHitObject(nullptr);
							this->GetGameObject()->SetIsColliding(false);
							temp->SetHitObject(nullptr);
							temp->SetIsColliding(true);
						}
					}
				}
				else
				{
					if (this->GetGameObject()->GetHitObject() == temp)
					{
						this->GetGameObject()->SetHitObject(nullptr);
						this->GetGameObject()->SetIsColliding(false);
						temp->SetHitObject(nullptr);
						temp->SetIsColliding(false);
					}
				}
			}
		}
	};
}

void Collision::Cleanup(void)
{
	Component::Cleanup();

}

bool Collision::CheckCollision(Gameobject* gb)
{
	Math::Vec3 A_minPosition = GetBoxPosition(this->GetGameObject(), fColorRGBA{ -1, -1, 0, 1.0f });
	Math::Vec3 A_maxPosition = GetBoxPosition(this->GetGameObject(), fColorRGBA{ 1, 1, 0, 1.0f });

	Math::Vec3 B_minPosition = GetBoxPosition(gb, fColorRGBA{ -1, -1, 0, 1.0f });
	Math::Vec3 B_maxPosition = GetBoxPosition(gb, fColorRGBA{ 1, 1, 0, 1.0f });

	if (B_minPosition.x - A_maxPosition.x > 0) return false;
	if (A_minPosition.x - B_maxPosition.x > 0) return false;
	if (B_minPosition.y - A_maxPosition.y > 0) return false;
	if (A_minPosition.y - B_maxPosition.y > 0) return false;

	return true;
}

Math::Vec3 Collision::GetBoxPosition(Gameobject* gb, fColorRGBA pos)
{
	Math::Mat4x4 mvp = Application::GetInstancePtr()->GetRenderer()->GetCamera()->GetVP() * gb->GetModelMatrix();

	fColorRGBA temp2 =
	{
		mvp.m11 * pos.r + mvp.m12 * pos.g + mvp.m13 * pos.b + mvp.m14 * pos.a,
		mvp.m21 * pos.r + mvp.m22 * pos.g + mvp.m23 * pos.b + mvp.m24 * pos.a,
		mvp.m31 * pos.r + mvp.m32 * pos.g + mvp.m33 * pos.b + mvp.m34 * pos.a,
		mvp.m41 * pos.r + mvp.m42 * pos.g + mvp.m43 * pos.b + mvp.m44 * pos.a,
	};

	return Math::Vec3
	{
		gb->GetTransform().position.x + temp2.r * 100.0f,
		gb->GetTransform().position.y + temp2.g * 100.0f,
		0.0f,
	};
}


