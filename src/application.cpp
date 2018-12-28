
// EXTERNAL INCLUDES
// INTERNAL INCLUDES
#include "application.h"
#include "scene/gameobject.h"
#include "rendering/renderer.h"
#include "rendering/shader.h"
#include "systems/console.h"
#include "systems/inputhandler.h"
#include "scene/scene.h"

//Declare Application as a Singleton.
DECLARE_SINGLETON(Application)

//Void Initialize
void Application::Initialize(char* title, iVec2 resolution, ui32 displayID)
{
	this->scene = new Scene;

	//Instantiate the window.
	Window::GetInstance().Instantiate(title, resolution.x, resolution.y, displayID);
	Application::renderer = new Renderer;
	Application::filesystem = new Filesystem;
	Application::renderer->Initialize(displayID);

	//Create the scenegraph root.
	this->scene->Initialize();

	//Create and initialize the renderer.
}

//Void Updatea
void Application::Update(void)
{
	//Do loop.
	do
	{
		// Pump window messages
		Window::GetInstancePtr()->DispatchMessages();

		//If escape key, close window.
		if (Input::GetInstancePtr()->GetKeyDown(KeyCode::Escape))
			break;

		// Update Gamestate
		this->scene->Update();

		// Render Gamestate
		Application::renderer->Render();

		if (Input::GetInstancePtr()->GetUpState())
			Input::GetInstancePtr()->EradicateUpKeys();
	} while (true);
}

//Void Cleanup
void Application::CleanUp(void)
{
	//Release all pointers and safe delete the renderer
	Console::GetInstancePtr()->CleanUp();
	Application::renderer->CleanUp();
	SAFE_DELETE(this->renderer);
	this->scene->Cleanup();
	Console::GetInstancePtr()->Release();
	Input::GetInstancePtr()->Release();
	Window::GetInstancePtr()->Release();
	Application::GetInstancePtr()->Release();
}

void Application::AddGameobject(Gameobject* gb)
{
	this->gameObjects.push_back(gb);
}

Filesystem* Application::GetFilesystem()
{
	return this->filesystem;
}

Renderer* Application::GetRenderer()
{
	return this->renderer;
}

Scene* Application::GetScene()
{
	return this->scene;
}



