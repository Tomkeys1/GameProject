
//EXTERNAL INCLUDES
#include <d3dcommon.h>
#include <string>
//INTERNAL INCLUDES
#include "rendering/shader.h"
#include "typedefs/winfile.h"
#include "typedefs/utils.h"
#include "application.h"

//Void Initialize
void Shader::Initialize(ID3D11Device* dev, HWND window)
{
	HRESULT hr = 0;

	//Get the shaderfiles.
	WinFile* vertexShaderFile = new WinFile(Application::GetInstancePtr()->GetFilesystem()->FileInDirectory("shader", "defaultvs.shader").c_str());
	WinFile* pixelShaderFile = new WinFile(Application::GetInstancePtr()->GetFilesystem()->FileInDirectory("shader", "defaultps.shader").c_str());

	V_RETURN(dev->CreateVertexShader(vertexShaderFile->Read(), vertexShaderFile->GetSize(), NULL, &this->mvertexShader));
	V_RETURN(dev->CreatePixelShader(pixelShaderFile->Read(), pixelShaderFile->GetSize(), NULL, &this->mpixelShader));

	//Create input layout
	D3D11_INPUT_ELEMENT_DESC layoutDesc[2] = { 0 };

	layoutDesc[0].SemanticName		= "POSITION";
	layoutDesc[0].Format			= DXGI_FORMAT_R32G32B32A32_FLOAT;
	layoutDesc[0].InputSlotClass	= D3D11_INPUT_PER_VERTEX_DATA;

	layoutDesc[1].SemanticName		= "COLOR";
	layoutDesc[1].Format			= DXGI_FORMAT_R32G32B32A32_FLOAT;
	layoutDesc[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	layoutDesc[1].InputSlotClass	= D3D11_INPUT_PER_VERTEX_DATA;

	ui32 elementCount = sizeof(layoutDesc) / sizeof(layoutDesc[0]);

	V_RETURN(dev->CreateInputLayout(layoutDesc, elementCount, vertexShaderFile->Read(), vertexShaderFile->GetSize(), &mlayout));
	SAFE_DELETE(vertexShaderFile);
	SAFE_DELETE(pixelShaderFile);

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

	devcon->IASetInputLayout(mlayout);

	devcon->VSSetShader(mvertexShader, NULL, 0);
	devcon->PSSetShader(mpixelShader, NULL, 0);

	devcon->DrawIndexed(indexCount, 0, 0);

	devcon->VSSetShader(nullptr, NULL, 0);
	devcon->PSSetShader(nullptr, NULL, 0);
}

//Void Cleanup	
void Shader::Cleanup(void)
{
	this->mvertexShader->Release();
	this->mpixelShader->Release();
	this->mlayout->Release();
	this->m_matrixBuffer->Release();
}

//SetShaderParameters
void Shader::SetShaderParameters(ID3D11DeviceContext* devcon, Math::Mat4x4 mvp)
{
	HRESULT hr = 0;

	ui32 bufferIndex = 0;

	devcon->UpdateSubresource(this->m_matrixBuffer, 0, NULL, &mvp, 0, 0);
	devcon->VSSetConstantBuffers(bufferIndex, 1, &m_matrixBuffer);
}
