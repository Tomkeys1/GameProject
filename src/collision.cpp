
//EXTERNAL INCLUDES
//INTERNAL INCLUDES
#include "application.h"
#include "math/vector3.h"
#include "math/vector2.h"
#include "scene/gameobject.h"
#include "scene/scene.h"
#include "systems/inputhandler.h"
#include "components/collision.h"
#include "typedefs/utils.h"

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
					this->GetGameObject()->SetIsColliding(CheckCollision(temp));
				}
				else
				{
					this->GetGameObject()->SetIsColliding(false);
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
	Math::Vec2 A = { this->GetGameObject()->GetTransform().position.x, this->GetGameObject()->GetTransform().position.y };
	Math::Vec2 B = { gb->GetTransform().position.x, gb->GetTransform().position.y };

	real aWidth = (this->GetGameObject()->GetTransform().scaling.x * 16.25f);
	real aHeight = (this->GetGameObject()->GetTransform().scaling.y * 25.15f);

	real bWidth = (gb->GetTransform().scaling.x * 16.25f);
	real bHeight = (gb->GetTransform().scaling.y * 25.15f);

	if ((A.x + aWidth) <= (B.x - bWidth)) return false;
	if ((A.x - aWidth) >= (B.x + bWidth)) return false;
	if ((A.y + aHeight) <= (B.y - bHeight)) return false;
	if ((A.y - aHeight) >= (B.y + bHeight)) return false;

	return true;
}
