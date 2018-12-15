
//EXTERNAL INCLUDES
#include <d3dcommon.h>
#include <string>
//INTERNAL INCLUDES
#include "rendering/renderer.h"
#include "rendering/shader.h"
#include "typedefs/winfile.h"
#include "typedefs/utils.h"
#include "application.h"

//Void Initialize
void Shader::Initialize(ID3D11Device* dev)
{
	HRESULT hr = 0;

	//Create matrix buffer
	D3D11_BUFFER_DESC matrixBufferDesc;

	matrixBufferDesc.ByteWidth = sizeof(Math::Mat4x4);
	matrixBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = 0;
	matrixBufferDesc.MiscFlags = 0;

	V_RETURN(dev->CreateBuffer(&matrixBufferDesc, NULL, &m_matrixBuffer));
}

//Void Render
void Shader::Render(ID3D11DeviceContext* devcon, ui32 indexCount, Math::Mat4x4 mvp)
{
	SetShaderParameters(devcon, mvp);

	devcon->IASetInputLayout(Application::GetInstancePtr()->GetRenderer()->mlayout);

	devcon->VSSetShader(Application::GetInstancePtr()->GetRenderer()->mvertexShader, NULL, 0);
	devcon->PSSetShader(Application::GetInstancePtr()->GetRenderer()->mpixelShader, NULL, 0);

	devcon->DrawIndexed(indexCount, 0, 0);

	devcon->VSSetShader(nullptr, NULL, 0);
	devcon->PSSetShader(nullptr, NULL, 0);
}

//Void Cleanup	
void Shader::Cleanup(void)
{
	//this->m_matrixBuffer->Release();
}

//SetShaderParameters
void Shader::SetShaderParameters(ID3D11DeviceContext* devcon, Math::Mat4x4 mvp)
{
	HRESULT hr = 0;

	ui32 bufferIndex = 0;

	devcon->UpdateSubresource(this->m_matrixBuffer, 0, NULL, &mvp, 0, 0);
	devcon->VSSetConstantBuffers(bufferIndex, 1, &m_matrixBuffer);
}
