
#pragma once
//EXTERNAL INCLUDES
#include <assert.h>
#include <cmath>
//INTERNAL INCLUDES
#include "typedefs/types.h"
#include "math/vector3.h"
#include "math/quaternion.h"

//Namespace Math
namespace Math
{
	//Declare new 4x4 Matrix
	struct Mat4x4
	{
		real m11, m12, m13, m14;
		real m21, m22, m23, m24;
		real m31, m32, m33, m34;
		real m41, m42, m43, m44;

		//Declare identity and zero matrix. See mat4x4.cpp for definiton
		static const Mat4x4 identity;
		static const Mat4x4 zero;
	};

	//Add each matrix value with its counterpart matrix.
	inline Mat4x4 operator+(const Mat4x4& lhs, const Mat4x4& rhs)
	{
		return Mat4x4
		{
			lhs.m11 + rhs.m11,
			lhs.m12 + rhs.m12,
			lhs.m13 + rhs.m13,
			lhs.m14 + rhs.m14,

			lhs.m21 + rhs.m21,
			lhs.m22 + rhs.m22,
			lhs.m23 + rhs.m23,
			lhs.m24 + rhs.m24,

			lhs.m31 + rhs.m31,
			lhs.m32 + rhs.m32,
			lhs.m33 + rhs.m33,
			lhs.m34 + rhs.m34,

			lhs.m41 + rhs.m41,
			lhs.m42 + rhs.m42,
			lhs.m43 + rhs.m43,
			lhs.m44 + rhs.m44
		};
	}

	//Subtract each matrix value with its counterpart matrix.
	inline Mat4x4 operator-(const Mat4x4& lhs, const Mat4x4& rhs)
	{
		return Mat4x4
		{
			lhs.m11 - rhs.m11,
			lhs.m12 - rhs.m12,
			lhs.m13 - rhs.m13,
			lhs.m14 - rhs.m14,
					
			lhs.m21 - rhs.m21,
			lhs.m22 - rhs.m22,
			lhs.m23 - rhs.m23,
			lhs.m24 - rhs.m24,
					
			lhs.m31 - rhs.m31,
			lhs.m32 - rhs.m32,
			lhs.m33 - rhs.m33,
			lhs.m34 - rhs.m34,
					
			lhs.m41 - rhs.m41,
			lhs.m42 - rhs.m42,
			lhs.m43 - rhs.m43,
			lhs.m44 - rhs.m44
		};
	}

	//Multiply columns by rows.
	inline Mat4x4 operator*(const Mat4x4& lhs, const Mat4x4& rhs)
	{
		return Mat4x4
		{
			(lhs.m11 * rhs.m11) + (lhs.m12 * rhs.m21) + (lhs.m13 * rhs.m31) + (lhs.m14 * rhs.m41),
			(lhs.m11 * rhs.m12) + (lhs.m12 * rhs.m22) + (lhs.m13 * rhs.m32) + (lhs.m14 * rhs.m42),
			(lhs.m11 * rhs.m13) + (lhs.m12 * rhs.m23) + (lhs.m13 * rhs.m33) + (lhs.m14 * rhs.m43),
			(lhs.m11 * rhs.m14) + (lhs.m12 * rhs.m24) + (lhs.m13 * rhs.m34) + (lhs.m14 * rhs.m44),

			(lhs.m21 * rhs.m11) + (lhs.m22 * rhs.m21) + (lhs.m23 * rhs.m31) + (lhs.m24 * rhs.m41),
			(lhs.m21 * rhs.m12) + (lhs.m22 * rhs.m22) + (lhs.m23 * rhs.m32) + (lhs.m24 * rhs.m42),
			(lhs.m21 * rhs.m13) + (lhs.m22 * rhs.m23) + (lhs.m23 * rhs.m33) + (lhs.m24 * rhs.m43),
			(lhs.m21 * rhs.m14) + (lhs.m22 * rhs.m24) + (lhs.m23 * rhs.m34) + (lhs.m24 * rhs.m44),

			(lhs.m31 * rhs.m11) + (lhs.m32 * rhs.m21) + (lhs.m33 * rhs.m31) + (lhs.m34 * rhs.m41),
			(lhs.m31 * rhs.m12) + (lhs.m32 * rhs.m22) + (lhs.m33 * rhs.m32) + (lhs.m34 * rhs.m42),
			(lhs.m31 * rhs.m13) + (lhs.m32 * rhs.m23) + (lhs.m33 * rhs.m33) + (lhs.m34 * rhs.m43),
			(lhs.m31 * rhs.m14) + (lhs.m32 * rhs.m24) + (lhs.m33 * rhs.m34) + (lhs.m34 * rhs.m44),

			(lhs.m41 * rhs.m11) + (lhs.m42 * rhs.m21) + (lhs.m43 * rhs.m31) + (lhs.m44 * rhs.m41),
			(lhs.m41 * rhs.m12) + (lhs.m42 * rhs.m22) + (lhs.m43 * rhs.m32) + (lhs.m44 * rhs.m42),
			(lhs.m41 * rhs.m13) + (lhs.m42 * rhs.m23) + (lhs.m43 * rhs.m33) + (lhs.m44 * rhs.m43),
			(lhs.m41 * rhs.m14) + (lhs.m42 * rhs.m24) + (lhs.m43 * rhs.m34) + (lhs.m44 * rhs.m44)
		};
	}

	inline Mat4x4 operator*(const Mat4x4& lhs, const Vec3& rhs)
	{
		return Mat4x4
		{
			(lhs.m11 * rhs.x) + (lhs.m12 * rhs.y) + (lhs.m13 * rhs.z) + (lhs.m14),
			(lhs.m11 * rhs.x) + (lhs.m12 * rhs.y) + (lhs.m13 * rhs.z) + (lhs.m14),
			(lhs.m11 * rhs.x) + (lhs.m12 * rhs.y) + (lhs.m13 * rhs.z) + (lhs.m14),
			(lhs.m11 * rhs.x) + (lhs.m12 * rhs.y) + (lhs.m13 * rhs.z) + (lhs.m14),
							
			(lhs.m21 * rhs.x) + (lhs.m22 * rhs.y) + (lhs.m23 * rhs.z) + (lhs.m24),
			(lhs.m21 * rhs.x) + (lhs.m22 * rhs.y) + (lhs.m23 * rhs.z) + (lhs.m24),
			(lhs.m21 * rhs.x) + (lhs.m22 * rhs.y) + (lhs.m23 * rhs.z) + (lhs.m24),
			(lhs.m21 * rhs.x) + (lhs.m22 * rhs.y) + (lhs.m23 * rhs.z) + (lhs.m24),
							
			(lhs.m31 * rhs.x) + (lhs.m32 * rhs.y) + (lhs.m33 * rhs.z) + (lhs.m34),
			(lhs.m31 * rhs.x) + (lhs.m32 * rhs.y) + (lhs.m33 * rhs.z) + (lhs.m34),
			(lhs.m31 * rhs.x) + (lhs.m32 * rhs.y) + (lhs.m33 * rhs.z) + (lhs.m34),
			(lhs.m31 * rhs.x) + (lhs.m32 * rhs.y) + (lhs.m33 * rhs.z) + (lhs.m34),
							
			(lhs.m41 * rhs.x) + (lhs.m42 * rhs.y) + (lhs.m43 * rhs.z) + (lhs.m44),
			(lhs.m41 * rhs.x) + (lhs.m42 * rhs.y) + (lhs.m43 * rhs.z) + (lhs.m44),
			(lhs.m41 * rhs.x) + (lhs.m42 * rhs.y) + (lhs.m43 * rhs.z) + (lhs.m44),
			(lhs.m41 * rhs.x) + (lhs.m42 * rhs.y) + (lhs.m43 * rhs.z) + (lhs.m44)
		};
	}

	//Multiply each matrix value by a scalar product
	inline Mat4x4 operator*(const Mat4x4& lhs, float scalar)
	{
		return Mat4x4
		{
			lhs.m11 * scalar,
			lhs.m12 * scalar,
			lhs.m13 * scalar,
			lhs.m14 * scalar,

			lhs.m21 * scalar,
			lhs.m22 * scalar,
			lhs.m23 * scalar,
			lhs.m24 * scalar,

			lhs.m31 * scalar,
			lhs.m32 * scalar,
			lhs.m33 * scalar,
			lhs.m34 * scalar,
	
			lhs.m41 * scalar,
			lhs.m42 * scalar,
			lhs.m43 * scalar,
			lhs.m44 * scalar
		};
	}

	//Transform input matrix into transpose matrix. (a1, b1, c1, d1, a2, b2, c2, d2, a3, b3, c3, d3, a4, b4, c4, d4)
	inline Mat4x4 Transpose(const Mat4x4& mat)
	{
		return Mat4x4
		{
			mat.m11,
			mat.m21,
			mat.m31,
			mat.m41,

			mat.m12,
			mat.m22,
			mat.m32,
			mat.m42,

			mat.m13,
			mat.m23,
			mat.m33,
			mat.m43,

			mat.m14,
			mat.m24,
			mat.m34,
			mat.m44
		};
	}

	inline Mat4x4 CreateTranslationMatrix(const Vec3& transformVec)
	{
		return Mat4x4
		{
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			transformVec.x, transformVec.y, transformVec.z, 1
		};
	}

	inline Mat4x4 CreateScalingMatrix(const Vec3& scalingVec)
	{
		return Mat4x4
		{
			scalingVec.x, 0, 0, 0,
			0, scalingVec.y, 0, 0,
			0, 0, scalingVec.z, 0,
			0, 0, 0, 1
		};
	}

	inline Mat4x4 CreateRotationXMatrix(float thetha)
	{
		return Mat4x4
		{
			1, 0, 0, 0,
			0, cos(thetha), sin(thetha), 0,
			0, -sin(thetha), cos(thetha), 0,
			0, 0, 0, 1
		};
	}
	inline Mat4x4 CreateRotationYMatrix(float thetha)
	{
		return Mat4x4
		{
			cos(thetha), 0, -sin(thetha), 0,
			0, 1, 0, 0,
			sin(thetha), 0, cos(thetha), 0,
			0, 0, 0, 1
		};
	}
	inline Mat4x4 CreateRotationZMatrix(float thetha)
	{
		return Mat4x4
		{
			cos(thetha), sin(thetha), 0, 0,
			-sin(thetha), cos(thetha), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		};
	}

	inline Mat4x4 CreateRotationMatrixQuaternion(const Quaternion& rotation)
	{
		return Mat4x4
		{
			1.0f - 2.0f * rotation.y * rotation.y - 2.0f * rotation.z * rotation.z, 2.0f * rotation.x * rotation.y - 2.0f * rotation.z * rotation.w, 2.0f * rotation.x * rotation.z + 2.0f * rotation.y * rotation.w, 0.0f,
			2.0f * rotation.x * rotation.y + 2.0f * rotation.z * rotation.w, 1.0f - 2.0f * rotation.x * rotation.x - 2.0f * rotation.z * rotation.z, 2.0f * rotation.y * rotation.z - 2.0f * rotation.x * rotation.w, 0.0f,
			2.0f * rotation.x * rotation.z - 2.0f * rotation.y * rotation.w, 2.0f * rotation.y * rotation.z + 2.0f * rotation.x * rotation.w, 1.0f - 2.0f * rotation.x * rotation.x - 2.0f * rotation.y * rotation.y, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};
	}

	inline Mat4x4 CreateRotationMatrix(const Vec3& eulerRotation)
	{
		real thetha = eulerRotation.x * M_PI / 180.0f;
		real psi = eulerRotation.y * M_PI / 180.0f;
		real kappa = eulerRotation.z * M_PI / 180.0f;

		Mat4x4 rot = Math::CreateRotationXMatrix(thetha) * Math::CreateRotationYMatrix(psi) * Math::CreateRotationZMatrix(kappa);

		return rot;
	}


	inline Mat4x4 CreateProjectionMatrix(real width, real height, real nearC, real farC)
	{

		return Mat4x4
		{
			2.0f / width, 0, 0, 0,
			0, 2.0f / height, 0, 0,
			0, 0, 1.0f / (farC - nearC), 0,
			0, 0, nearC / (farC - nearC), 1,
		};
	}
}
