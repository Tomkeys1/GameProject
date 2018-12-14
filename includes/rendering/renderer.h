
#pragma once
//EXTERNAL INCLUDES
#include <d3d11.h>
#include <vector>
//INTERNAL INCLUDES
#include "window.h"

class Shader;
class Geometry;
class Camera;
class Gameobject;

//Class Renderer
class Renderer 
{
//Declare public functions.
public: 
	void Initialize(std::vector<Gameobject*> gbList, ui32 displayID = 0, ui32 adapterID = 0, HWND targetWindow = Window::GetInstance().handle);
	void Render(void);
	void CleanUp(void);

//Declare private functions and variables.
private:
	void GetAdapters();

	//DirectX variables.
	IDXGISwapChain* swapchain;         
	ID3D11Device* dev;                     
	ID3D11DeviceContext* devcon;
	IDXGIAdapter* adapter;
	IDXGIFactory* factory;
	ID3D11RenderTargetView* backbuffer;
	Camera* camera;

	std::vector <IDXGIAdapter*> adapters;
	std::vector <Gameobject*> gameObjects;
};
