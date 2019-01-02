
#pragma once
//EXTERNAL INCLUDES
#include <assert.h>
#include <cmath>
//INTERNAL INCLUDES
#include "typedefs/types.h"
#include "math/mat4x4.h"

namespace Math
{
	inline real Clamp(real value, real min, real max)
	{
		if (value > max)
			value = max;
		if (value < min)
			value = min;

		return value;
	}

	inline fColorRGBA operator*(const fColorRGBA& vec4, Math::Mat4x4 mat)
	{
		return fColorRGBA
		{
			mat.m11 * vec4.r + mat.m12 * vec4.g + mat.m13 * vec4.b + mat.m14 * vec4.a,
			mat.m21 * vec4.r + mat.m22 * vec4.g + mat.m23 * vec4.b + mat.m24 * vec4.a,
			mat.m31 * vec4.r + mat.m32 * vec4.g + mat.m33 * vec4.b + mat.m34 * vec4.a,
			mat.m41 * vec4.r + mat.m42 * vec4.g + mat.m43 * vec4.b + mat.m44 * vec4.a,
		};
	}

	inline void GetMinMaxOfProjection(Math::Vec3 corners[], Math::Vec3 axis, real& min, real& max)
	{
		min = 0.018736723663f;
		max = 0.018736723663f;

		for (int i = 0; i < 4; i++)
		{
			Math::Vec3 point = corners[i];

			real value = ((point.x * axis.x) + (point.y * axis.y)) / ((axis.x * axis.x) + (axis.y * axis.y));

			point = Math::Vec3{ value * axis.x, value * axis.y, 0.0f };

			real projection = Math::Dot(point, axis);

			if (min == 0.018736723663f)
			{
				min = projection;
				max = projection;
			}
			else
			{
				if (projection < min)
					min = projection;

				if (projection > max)
					max = projection;
			}
		}
	}
}