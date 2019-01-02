
//EXTERNAL INCLUDES
//INTERNAL INCLUDES
#include "application.h"
#include "scene/gameobject.h"
#include "scene/scene.h"
#include "systems/inputhandler.h"
#include "physics/collision.h"
#include "physics/rigidbody.h"
#include "typedefs/utils.h"
#include "rendering/camera.h"
#include "rendering/renderer.h"


Collision::Collision(Gameobject* gb)
{
	this->gameobject = gb;
}

void Collision::Update(void)
{
	//Execute the components Update function.

	if (Input::GetInstancePtr()->GetKey(KeyCode::B))
	{
		real f = 0.01f;
	}

	if (this->gameobject->hasCollision())
	{
		for (Node* gb : Application::GetInstancePtr()->GetScene()->GetGameobject()->GetAllChildren())
		{
			Gameobject* temp = reinterpret_cast<Gameobject*>(gb);

			if (temp->hasCollision())
			{
				if (temp != this->gameobject)
				{
					if (Math::Distance(this->gameobject->GetTransform().position, temp->GetTransform().position) < GetRadius(temp))
					{
						if (CheckCollision(temp) == true)
						{
							if (this->gameobject->GetHitObject() == nullptr)
							{
								this->impactDir = Math::Negate(this->gameobject->GetRigidbody()->GetRigidbodyValues().movementDir);
								this->gameobject->SetHitObject(temp);
							}

							this->gameobject->SetIsColliding(true);
						}
						else
						{
							if (this->gameobject->GetHitObject() == temp)
							{
								this->gameobject->SetHitObject(nullptr);
								this->gameobject->SetIsColliding(false);
							}
						}
					}
					else
					{
						if (this->gameobject->GetHitObject() == temp)
						{
							this->gameobject->SetHitObject(nullptr);
							this->gameobject->SetIsColliding(false);
						}
					}
				}
			}
			else
			{
				if (this->gameobject->GetHitObject() == temp)
				{
					this->gameobject->SetHitObject(nullptr);
					this->gameobject->SetIsColliding(false);
				}
			}
		}
	}
}

void Collision::Cleanup(void)
{

}

Math::Vec3 Collision::GetImpactDirection()
{
	return this->impactDir;
}

real Collision::GetRadius(Gameobject* gb)
{
	real aradius1 = Math::Distance(this->gameobject->GetWorldCorner(fColorRGBA{ -1, 1, 0, 1.0f }, this->gameobject->GetModelMatrixNoRotation()), this->gameobject->GetWorldCorner(fColorRGBA{ 1, 1, 0, 1.0f }, this->gameobject->GetModelMatrixNoRotation()));
	aradius1 = aradius1 * 0.5f;
	real aradius2 = Math::Distance(this->gameobject->GetWorldCorner(fColorRGBA{ 1, -1, 0, 1.0f }, this->gameobject->GetModelMatrixNoRotation()), this->gameobject->GetWorldCorner(fColorRGBA{ 1, 1, 0, 1.0f }, this->gameobject->GetModelMatrixNoRotation()));
	aradius2 = aradius2 * 0.5f;

	real bradius1 = Math::Distance(gb->GetWorldCorner(fColorRGBA{ -1, 1, 0, 1.0f }, gb->GetModelMatrixNoRotation()), gb->GetWorldCorner(fColorRGBA{ 1, 1, 0, 1.0f }, gb->GetModelMatrixNoRotation()));
	bradius1 = bradius1 * 0.5f;
	real bradius2 = Math::Distance(gb->GetWorldCorner(fColorRGBA{ 1, -1, 0, 1.0f }, gb->GetModelMatrixNoRotation()), gb->GetWorldCorner(fColorRGBA{ 1, 1, 0, 1.0f }, gb->GetModelMatrixNoRotation()));
	bradius2 = bradius2 * 0.5f;

	real radius1, radius2;

	if (aradius1 >= aradius2)
		radius1 = aradius1;
	else
		radius1 = aradius2;

	if (bradius1 >= bradius2)
		radius2 = bradius1;
	else
		radius2 = bradius2;

	return radius1 + radius2;
}

Math::Vec3 Collision::GetAxis(Math::Vec3 point1, Math::Vec3 point2)
{
	Math::Vec3 edge = point1 - point2;
	Math::Vec3 edgeNormal = Math::Vec3{ -edge.y, edge.x, edge.z };
	Math::Normalize(edgeNormal);
	return edgeNormal;
}

bool Collision::isProjectionIntersecting(Math::Vec3 aCorners[], Math::Vec3 bCorners[], Math::Vec3 axis)
{
	real aMin, aMax, bMin, bMax;

	Math::GetMinMaxOfProjection(aCorners, axis, aMin, aMax);
	Math::GetMinMaxOfProjection(bCorners, axis, bMin, bMax);

	if (aMin > bMax) return false;
	if (aMax < bMin) return false;

	return true;
}

bool Collision::CheckCollision(Gameobject* gb)
{
	Math::Vec3 aCorners[4] =
	{
		this->gameobject->GetWorldCorner(fColorRGBA{ 1, 1, 0, 1.0f }),
		this->gameobject->GetWorldCorner(fColorRGBA{ -1, 1, 0, 1.0f }),
		this->gameobject->GetWorldCorner(fColorRGBA{ -1, -1, 0, 1.0f }),
		this->gameobject->GetWorldCorner(fColorRGBA{ 1, -1, 0, 1.0f }),
	};

	Math::Vec3 bCorners[4] =
	{
		gb->GetWorldCorner(fColorRGBA{ 1, 1, 0, 1.0f }),
		gb->GetWorldCorner(fColorRGBA{ -1, 1, 0, 1.0f }),
		gb->GetWorldCorner(fColorRGBA{ -1, -1, 0, 1.0f }),
		gb->GetWorldCorner(fColorRGBA{ 1, -1, 0, 1.0f }),
	};

	Math::Vec3 axis1 = GetAxis(aCorners[0], aCorners[1]);
	if (!this->isProjectionIntersecting(aCorners, bCorners, axis1)) return false;

	Math::Vec3 axis2 = GetAxis(aCorners[0], aCorners[3]);
	if (!this->isProjectionIntersecting(aCorners, bCorners, axis2)) return false;

	Math::Vec3 axis3 = GetAxis(bCorners[1], bCorners[2]);
	if (!this->isProjectionIntersecting(aCorners, bCorners, axis3)) return false;

	Math::Vec3 axis4 = GetAxis(bCorners[1], bCorners[0]);
	if (!this->isProjectionIntersecting(aCorners, bCorners, axis4)) return false;

	return true;
}


