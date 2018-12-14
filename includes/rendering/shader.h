
#pragma once
//EXTERNAL INCLUDES
#include <d3d11.h>
#include <string>
//INTERNAL INCLUDES
#include "math/mat4x4.h"

class Shader 
{
	//Declare Struct Matrices
	struct Matrices 
	{
		Math::Mat4x4 worldMatrix;
		Math::Mat4x4 viewMatrix;
		Math::Mat4x4 projectionMatrix;
	};

//Declare public functions.
public:
	Shader(const char* vs, const char* ps);

	void Initialize(ID3D11Device* dev, HWND window);
	void Render(ID3D11DeviceContext* devcon, ui32 indexCount, Math::Mat4x4 vp);
	void Cleanup(void);

//Declare private functions and variables.
private:
	void SetShaderParameters(ID3D11DeviceContext*, Math::Mat4x4 vp);

	//DirectX variables.
	ID3D11VertexShader* mvertexShader;
	ID3D11PixelShader* mpixelShader;
	ID3D11InputLayout* mlayout;
	ID3D11Buffer* m_matrixBuffer;

	Math::Mat4x4 vp;

	const char* vsFilename;
	const char* psFilename;

};
