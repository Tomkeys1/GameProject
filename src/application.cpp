
// EXTERNAL INCLUDES
// INTERNAL INCLUDES
#include "application.h"
#include "scene/gameobject.h"
#include "components/movement.h"
#include "components/shooting.h"
#include "rendering/renderer.h"
#include "rendering/shader.h"
#include "systems/console.h"
#include "systems/inputhandler.h"

//Declare Application as a Singleton.
DECLARE_SINGLETON(Application)

//Void Initialize
void Application::Initialize(char* title, iVec2 resolution, ui32 displayID)
{
	this->root = new Gameobject(false, true);
	this->root->SetName("root");
	this->root->MakeRoot();
	//Instantiate the window.
	Window::GetInstance().Instantiate(title, resolution.x, resolution.y, displayID);
	Application::renderer = new Renderer;
	Application::filesystem = new Filesystem;
	Application::renderer->Initialize(displayID);

	//Create the scenegraph root.

	//Create gameobjects.
	Gameobject* player1 = new Gameobject;
	Gameobject* player2 = new Gameobject(true, false, false, fColorRGBA{ 0.125f, 0.788f, 0.972f, 1.0f});


	//Add childs.
	//Set gameobjects names.
	player1->SetName("player1");
	player2->SetName("player2");

	player1->GetTransform().position = { 0, -0.7f, 0 };
	player2->GetTransform().scaling = { 100, 100, 100 };

	//Create and initialize a new movment component.
	Movement* mov = new Movement;
	Shooting* shot = new Shooting;

	shot->Initialize("shooting", ComponentType::Shoot, player1);
	mov->Initialize("movement", ComponentType::Movement, player1);

	//Add player1 the movement component.
	player1->AddComponent(mov);
	player1->AddComponent(shot);

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
		this->root->Update();

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
	this->gameObjects.clear();
	Application::renderer->CleanUp();
	SAFE_DELETE(this->renderer);
	this->root->Cleanup();
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

Gameobject* Application::GetRoot()
{
	return this->root;
}

