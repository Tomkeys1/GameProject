
#pragma once
// EXTERNAL INCLUDES
// INTERNAL INCLUDES
#include "math/vector3.h"
#include "math/quaternion.h"

//Declare struct Transform.
struct Transform
{
	Math::Vec3 position;
	Math::Vec3 scaling;
	Math::Quaternion rotation;
};
