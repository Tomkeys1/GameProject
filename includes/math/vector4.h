
#pragma once
//EXTERNAL INCLUDES
#include <assert.h>
#include <cmath>
#include <limits>
//INTERNAL INCLUDES
#include "types/types.h"

namespace Math
{
	struct Vec4
	{
		real x;
		real y;
		real z;
		real w;

		static const Vec4 zero;
		static const Vec4 unit_x;
		static const Vec4 unit_y;
		static const Vec4 neg_unit_x;
		static const Vec4 neg_unit_y;
		static const Vec4 unit_scale;
	};

	inline Vec4 operator+(const Vec4& lhs, const Vec4& rhs)
	{
		return Vec4
		{
			(lhs.x + rhs.x),
			(lhs.y + rhs.y),
			(lhs.z + rhs.z),
			(lhs.w + rhs.w)
		};
	}

	inline Vec4 operator+(const Vec4& lhs, real scalar)
	{
		return Vec4
		{
			(lhs.x + scalar),
			(lhs.y + scalar),
			(lhs.z + scalar),
			(lhs.w + scalar)
		};
	}

	inline Vec4 operator-(const Vec4& lhs, const Vec4& rhs)
	{
		return Vec4
		{
			(lhs.x - rhs.x),
			(lhs.y - rhs.y),
			(lhs.z - rhs.z),
			(lhs.w - rhs.w)
		};
	}

	inline Vec4 operator-(const Vec4& lhs, real scalar)
	{
		return Vec4
		{
			(lhs.x - scalar),
			(lhs.y - scalar),
			(lhs.z - scalar),
			(lhs.w - scalar)
		};
	}

	inline Vec4 operator*(const Vec4& lhs, real scalar)
	{
		return Vec4
		{
			(lhs.x * scalar),
			(lhs.y * scalar),
			(lhs.z * scalar),
			(lhs.w * scalar)
		};
	}

	inline Vec4 operator/(const Vec4& lhs, real scalar)
	{
		assert(scalar != 0.0f);

		return Vec4
		{
			(lhs.x / scalar),
			(lhs.y / scalar),
			(lhs.z / scalar),
			(lhs.w / scalar)
		};
	}

	inline Vec4& operator+=(Vec4& lhs, const Vec4& rhs)
	{
		lhs.x += rhs.x;
		lhs.y += rhs.y;
		lhs.z += rhs.z;
		lhs.w += rhs.w;

		return lhs;
	}

	inline Vec4& operator+=(Vec4& lhs, real scalar)
	{
		lhs.x += scalar;
		lhs.y += scalar;
		lhs.z += scalar;
		lhs.w += scalar;

		return lhs;
	}

	inline Vec4& operator-=(Vec4& lhs, const Vec4& rhs)
	{
		lhs.x -= rhs.x;
		lhs.y -= rhs.y;
		lhs.z -= rhs.z;
		lhs.w -= rhs.w;

		return lhs;
	}

	inline Vec4& operator-=(Vec4& lhs, real scalar)
	{
		lhs.x -= scalar;
		lhs.y -= scalar;
		lhs.z -= scalar;
		lhs.w -= scalar;

		return lhs;
	}

	inline Vec4& operator*=(Vec4& lhs, real scalar)
	{
		lhs.x *= scalar;
		lhs.y *= scalar;
		lhs.z *= scalar;
		lhs.w *= scalar;

		return lhs;
	}

	inline Vec4& operator/=(Vec4& lhs, real scalar)
	{
		assert(scalar != 0.0f);

		lhs.x /= scalar;
		lhs.y /= scalar;
		lhs.z /= scalar;
		lhs.w /= scalar;

		return lhs;
	}
}
