
#pragma once
//EXTERNAL INCLUDES
#include <assert.h>
#include <cmath>
//INTERNAL INCLUDES
#include "typedefs/types.h"

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
}