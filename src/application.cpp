
// EXTERNAL INCLUDES
#include <thread>
// INTERNAL INCLUDES
#include "application.h"
#include "scene/gameobject.h"
#include "rendering/renderer.h"
#include "rendering/shader.h"
#include "systems/console.h"
#include "systems/inputhandler.h"
#include "scene/scene.h"
#include "typedefs/time.h"

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

	real delta_time = 0.0f;
	std::chrono::time_point currentTime = std::chrono::steady_clock::now();
	std::chrono::time_point newTime = std::chrono::steady_clock::now();

	INIT_TIMER;
	while (this->running)
	{
		START_TIMER;
		newTime = std::chrono::steady_clock::now();

		delta_time = std::chrono::duration_cast<std::chrono::duration<real>>(newTime - currentTime).count();
		currentTime = newTime;

		Window::GetInstancePtr()->DispatchMessages();
		if (Input::GetInstancePtr()->GetKeyUp(KeyCode::P))
		{
			this->running = false;
				break;
			}

		// Update Gamestate && Update Renderer
		std::thread gamestateThread(&Scene::Update,this->scene, delta_time);
		std::thread renderThread(&Renderer::Render, Application::renderer);
		gamestateThread.join();
		renderThread.join();

		if (Input::GetInstancePtr()->GetUpState())
			Input::GetInstancePtr()->EradicateUpKeys();

		this->scene->DeleteGameobjects();
		
		STOP_TIMER("Update time taken: ");
	}

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



