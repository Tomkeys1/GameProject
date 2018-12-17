
//EXTERNAL INCLUDES
//INTERNAL INCLUDES
#include "rendering/renderer.h"
#include "rendering/shader.h"
#include "rendering/geometry.h"
#include "rendering/camera.h"
#include "typedefs/transform.h"
#include "scene/gameobject.h"
#include "scene/scene.h"
#include "application.h"
#include "typedefs/color.h"


//Void Initialize
void Renderer::Initialize(ui32 displayID, ui32 adapterID, HWND targetWindow)
{

	//Get the Adapters.
	GetAdapters();

	//Get the selected Display.
	Display* selectedDisplay = Window::GetInstance().GetDisplay(displayID);

	D3D11_VIEWPORT viewport;

	viewport.Width = static_cast<float>(Window::GetInstance().GetDisplay(displayID)->width);
	viewport.Height = static_cast<float>(Window::GetInstance().GetDisplay(displayID)->height);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;

	//Declare 2 structs to hold information.
	DXGI_SWAP_CHAIN_DESC scs;
	DXGI_MODE_DESC scsMode;

	//Clear Swapchain struct
	ZeroMemory(&scs, sizeof(DXGI_SWAP_CHAIN_DESC));

	//Fill Swapchain mode struct
	scsMode.Width = selectedDisplay->width;
	scsMode.Height = selectedDisplay->height;
	scsMode.RefreshRate = DXGI_RATIONAL{1, 60};
	scsMode.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scsMode.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scsMode.Scaling = DXGI_MODE_SCALING::DXGI_MODE_SCALING_CENTERED;

	//Fill Swapchain struct
	scs.BufferDesc = scsMode;
	scs.SampleDesc.Count = 1;
	scs.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scs.BufferCount = 2;
	scs.OutputWindow = targetWindow;
	scs.Windowed = TRUE;

	this->adapter = adapters[adapterID];

	//Create a Device and a SwapChain
	HRESULT hr = D3D11CreateDeviceAndSwapChain
	(
		adapter,
		D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_UNKNOWN,
		NULL,
		D3D11_CREATE_DEVICE_DEBUG,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&scs,
		&swapchain,
		&dev,
		NULL,
		&devcon
	);

	//Crash the program if the creation wasnt succesful
	V_RETURN(hr);

	//Access Buffer
	ID3D11Texture2D *pBackBuffer;
	swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);


	D3D11_RASTERIZER_DESC rDesc = { };
	rDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
	rDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	rDesc.DepthClipEnable = true;

	ID3D11RasterizerState* pRasterizerState;
	V_RETURN(dev->CreateRasterizerState(&rDesc, &pRasterizerState));

	// Create the viewport.
	devcon->RSSetViewports(1, &viewport);
	devcon->RSSetState(pRasterizerState);

	//Get the shaderfiles.
	WinFile* vertexShaderFile = new WinFile(Application::GetInstancePtr()->GetFilesystem()->FileInDirectory("shader", "defaultvs.shader").c_str());
	WinFile* pixelShaderFile = new WinFile(Application::GetInstancePtr()->GetFilesystem()->FileInDirectory("shader", "defaultps.shader").c_str());

	V_RETURN(dev->CreateVertexShader(vertexShaderFile->Read(), vertexShaderFile->GetSize(), NULL, &this->mvertexShader));
	V_RETURN(dev->CreatePixelShader(pixelShaderFile->Read(), pixelShaderFile->GetSize(), NULL, &this->mpixelShader));

	//Create input layout
	D3D11_INPUT_ELEMENT_DESC layoutDesc[2] = { 0 };

	layoutDesc[0].SemanticName = "POSITION";
	layoutDesc[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	layoutDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;

	layoutDesc[1].SemanticName = "COLOR";
	layoutDesc[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	layoutDesc[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	layoutDesc[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;

	ui32 elementCount = sizeof(layoutDesc) / sizeof(layoutDesc[0]);

	V_RETURN(dev->CreateInputLayout(layoutDesc, elementCount, vertexShaderFile->Read(), vertexShaderFile->GetSize(), &mlayout));
	SAFE_DELETE(vertexShaderFile);
	SAFE_DELETE(pixelShaderFile);

	//Create the RenderTarget view and set it to the output merger stage.

	this->camera = new Camera(static_cast<real>(Window::GetInstance().widthOfWindow), static_cast<real>(Window::GetInstance().heightOfWindow), 0.0f, 10.0f);

	dev->CreateRenderTargetView(pBackBuffer, NULL, &backbuffer);
	devcon->OMSetRenderTargets(1, &backbuffer, NULL);

	pBackBuffer->Release();
	pRasterizerState->Release();
}

//Void Render
void Renderer::Render(void)
{
	//Set backround color.
	//Set the color to the backbuffer
	devcon->ClearRenderTargetView(backbuffer, reinterpret_cast<FLOAT*>(&Color::GetColor(ColorCode::WHITE)));

	Math::Mat4x4 vp = this->camera->GetVP();

	for (Gameobject* gb : this->gameObjects)
	{
		if (gb->hasMesh() && gb->isVisisble())
		{
			gb->GetMesh()->Render(devcon);
			gb->GetMaterial()->Render(devcon, gb->GetMesh()->iLength, Math::Mat4x4(vp * gb->GetModelMatrix()));

			for (Node* child : gb->GetAllChildren())
			{
				Gameobject* childGb = reinterpret_cast<Gameobject*>(child);
				if (childGb->hasMesh() && childGb->isVisisble())
				{
					childGb->GetMesh()->Render(devcon);
					childGb->GetMaterial()->Render(devcon, childGb->GetMesh()->iLength, Math::Mat4x4(vp * childGb->GetModelMatrix()));
				}
			}
		}

	}

	//Render the image.
	swapchain->Present(0, 0);
}

//Void Cleanup
void Renderer::CleanUp()
{
	//Release all pointers.

	this->gameObjects.clear();
	this->swapchain->Release();
	this->dev->Release();
	this->devcon->Release();
	this->factory->Release();
	this->backbuffer->Release();
	this->mvertexShader->Release();
	this->mpixelShader->Release();
	this->mlayout->Release();
}

void Renderer::InitializeGameobject(Gameobject* gb)
{
	gb->GetMesh()->Initialize(dev);
	gb->GetMaterial()->Initialize(dev);

	if(gb->GetParent()->hasRoot())
		this->gameObjects.push_back(gb);
}

//Void GetAdapters
void Renderer::GetAdapters()
{
	//Create a DirectX Factory.
	HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&factory));

	//Crash the program if it wasnt succesful
	V_RETURN(hr);

	ui32 index = 0;

	//Enumerate through all the adapters. And add those to this renderers adapter list.
	while (factory->EnumAdapters(index, &adapter) != DXGI_ERROR_NOT_FOUND)
	{
		adapters.push_back(adapter);
		++index;
	}
}
