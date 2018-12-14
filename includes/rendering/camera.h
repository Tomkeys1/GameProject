
#pragma once
//EXTERNAL INCLUDES
//INTERNAL INCLUDES
#include "math/mat4x4.h"

class Transform;
class Gameobject;

class Camera
{
public:
	Camera(real width, real height, real nearC, real farC);

	void CreateViewMatrix();
	void Follow(const Transform& objectTransform);
	void CleanUp(void);
	Math::Mat4x4 GetVP();
	Gameobject* GetGameobject(void) const;

private:
	real width;
	real height;
	real mNearClip;
	real mFarClip;

	Math::Mat4x4 mvp;
	Math::Mat4x4 viewMatrix;
	Math::Vec3 initialPosition;
	Gameobject* gameobject;
};