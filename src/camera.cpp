#include "rendering/camera.h"
#include "typedefs/transform.h"
#include "scene/gameobject.h"

Camera::Camera(real width, real height, real nearC, real farC)
{
	this->gameobject = new Gameobject("camera", false, false, true);

	this->width = width;
	this->height = height;
	this->mNearClip = nearC;
	this->mFarClip = farC;

	this->gameobject->GetTransform().position = { 0, 0, -5 };
	this->initialPosition = this->gameobject->GetTransform().position;
}


void Camera::CleanUp(void)
{
	SAFE_DELETE(this->gameobject);
}

void Camera::CreateViewMatrix()
{
	Math::Vec3 X, Y, Z, C;

	C = this->gameobject->GetTransform().position;
	Z = Math::Vec3::unit_z;

	X = Math::Cross(Math::Vec3::unit_y, Z);
	Math::Normalize(X);

	Y = Math::Cross(Z, X);

	Math::Mat4x4 matrix = 
	{
		X.x, Y.x, Z.x, 0,
		X.y, Y.y, Z.y, 0,
		X.z, Y.z, Z.z, 0,
		-Math::Dot(X, C), -Math::Dot(Y, C), -Math::Dot(Z, C), 1
	};

	this->viewMatrix = Math::Transpose(matrix);
}

void Camera::Follow(const Transform& objectTransform)
{
	this->gameobject->GetTransform().position = objectTransform.position;
}

Math::Mat4x4 Camera::GetVP()
{ 
	CreateViewMatrix();

	Math::Mat4x4 viewMatrix = Math::Mat4x4::identity;
	viewMatrix = viewMatrix * this->viewMatrix;

	Math::Mat4x4 projectionMatrix = Math::Mat4x4::identity; 
	projectionMatrix = projectionMatrix * Math::CreateProjectionMatrix(this->width, this->height, this->mNearClip, this->mFarClip);

	return projectionMatrix * viewMatrix;
}

Gameobject* Camera::GetGameobject(void) const
{
	return this->gameobject;
}
