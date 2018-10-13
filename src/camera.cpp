#include "rendering/camera.h"
#include "typedefs/transform.h"
#include "scene/gameobject.h"

Camera::Camera(real width, real height, real nearC, real farC)
{
	this->gameobject = new Gameobject;

	this->width = width;
	this->height = height;
	this->mNearClip = nearC;
	this->mFarClip = farC;

	this->gameobject->GetTransform().position = { 0, 0, -10 };
	this->initialPosition = this->gameobject->GetTransform().position;
}


void Camera::CleanUp(void)
{
	SAFE_DELETE(this->gameobject);
}

void Camera::LookAt(const Transform& objectTransform)
{
	Math::Vec3 X, Y, Z, C;

	C = this->gameobject->GetTransform().position;

	Z = C - objectTransform.position;
	Math::Normalize(Z);

	X = Math::Cross(Z, Math::Vec3::unit_y);
	Math::Normalize(X);

	Y = Math::Cross(X, Z);
	Math::Normalize(Y);

	Math::Mat4x4 rotation = 
	{
		X.x, Y.x, -Z.x, 0,
		X.y, Y.y, -Z.y, 0,
		X.z, Y.z, -Z.z, 0,
		0, 0, 0, 1
	};

	Math::Mat4x4 translation = 
	{
		1, 0, 0, -C.x,
		0, 1, 0, -C.y,
		0, 0, 1, -C.z,
		0, 0, 0, 0
	};

	this->viewMatrix = translation * rotation;
}

void Camera::Follow(const Transform& objectTransform, Math::Vec3 offset)
{
	this->gameobject->GetTransform().position = objectTransform.position + offset;
}

Math::Mat4x4 Camera::GetMVP(Transform objectTransform)
{ 
	Math::Vec3 rotation;

	rotation.x = objectTransform.rotation.x;
	rotation.y = objectTransform.rotation.y;
	rotation.z = objectTransform.rotation.z;

	Math::Vec3 offset = this->initialPosition;

	//Follow(objectTransform, offset);

	LookAt(objectTransform);

	Math::Mat4x4 worldMatrix = Math::Mat4x4::identity;
	Math::Mat4x4 modelMatrix = Math::CreateTranslationMatrix(objectTransform.position) * Math::CreateRotationMatrix(rotation) * Math::CreateScalingMatrix(objectTransform.scaling);
	worldMatrix = worldMatrix * modelMatrix;

	Math::Mat4x4 viewMatrix = Math::Mat4x4::identity;
	viewMatrix = viewMatrix * this->viewMatrix;

	Math::Mat4x4 projectionMatrix = Math::Mat4x4::identity; 
	projectionMatrix = projectionMatrix * Math::CreateProjectionMatrix(this->width, this->height, this->mNearClip, this->mFarClip);

	Math::Mat4x4 mvp = Math::Mat4x4::identity;

	mvp = mvp * projectionMatrix;
	mvp = mvp * viewMatrix;
	mvp = mvp * worldMatrix;

	Math::Transpose(mvp);

	return mvp;
}

Gameobject* Camera::GetGameobject(void) const
{
	return this->gameobject;
}
