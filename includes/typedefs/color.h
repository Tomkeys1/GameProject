
#pragma once
#include "types.h"

enum class ColorCode
{
	RED,
	GREEN,
	YELLOW,
	ORANGE,
	BLUE, 
	BLACK,
	WHITE,
};

namespace Color
{
	inline fColorRGBA GetColor(ColorCode code)
	{
		switch (code)
		{
		case ColorCode::RED:
			return fColorRGBA{ 1.0, 0.0f, 0.0f, 1.0f };
			break;
		case ColorCode::GREEN:
			return fColorRGBA{ 0.403f, 1.0f, 0.0f, 1.0f };
			break;
		case ColorCode::YELLOW:
			return fColorRGBA{ 1.0f, 0.698f, 0.0f, 1.0f };
			break;
		case ColorCode::ORANGE:
			return fColorRGBA{ 1.0f, 0.478f, 0.0f, 1.0f };
			break;
		case ColorCode::BLUE:
			return fColorRGBA{ 0.0f, 0.529f, 1.0f, 1.0f };
			break;
		case ColorCode::BLACK:
			return fColorRGBA{ 0.0f, 0.0f, 0.0f, 0.0f };
			break;
		case ColorCode::WHITE:
			return fColorRGBA{ 1.0f, 1.0f, 1.0f, 1.0f };
			break;
		}
	}
}
