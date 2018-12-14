
// EXTERNAL INCLUDES
// INTERNAL INCLUDES
#include "application.h"
#include "scene/gameobject.h"
#include "components/movement.h"
#include "rendering/renderer.h"
#include "rendering/shader.h"
#include "systems/console.h"

//Declare Application as a Singleton.
DECLARE_SINGLETON(Application)

//Void Initialize
void Application::Initialize(char* title, iVec2 resolution, ui32 displayID)
{
	//Instantiate the window.
	Window::GetInstance().Instantiate(title, resolution.x, resolution.y, displayID);

	//Create the scenegraph root.
	this->root = new Gameobject;
	this->root->SetName("root");

	//Create gameobjects.
	Gameobject* player1 = new Gameobject;
	Gameobject* player2 = new Gameobject;

	//Add childs.
	this->root->AddChild(player1);
	this->root->AddChild(player2);

	std::list<Node*> test;
	std::vector<Gameobject*> gameObjects;
	
	this->root->GetAllChildren(this->root, test);

	for (Node* node : test)
	{
		gameObjects.push_back(reinterpret_cast<Gameobject*>(node));
	}

	//Set gameobjects names.
	player1->SetName("player1");
	player2->SetName("player2");

	Vertex* v = new Vertex[4];
	ui32* i = new ui32[6];

	v[0].position = fColorRGBA{ -1, 1, 0, 1.0f };
	v[0].color = fColorRGBA{ 0.960f, 0.713f, 0.0f, 1.0f };
	
	v[1].position = fColorRGBA{ 1, 1, 0, 1.0f };
	v[1].color = fColorRGBA{ 0.960f, 0.713f, 0.0f, 1.0f };
	
	v[2].position = fColorRGBA{ 1, -1, 0, 1.0f };
	v[2].color = fColorRGBA{ 0.960f, 0.713f, 0.0f, 1.0f };
	
	v[3].position = fColorRGBA{ -1, -1, 0, 1.0f };
	v[3].color = fColorRGBA{ 0.960f, 0.713f, 0.0f, 1.0f };

	i[0] = 3;
	i[1] = 0;
	i[2] = 1;
	i[3] = 3;
	i[4] = 1;
	i[5] = 2;


	player2->SetMeshData(v, i, 4, 6);
	player1->SetMeshData(v, i, 4, 6);


	//Create and initialize a new movment component.
	Movement* mov = new Movement;
	mov->Initialize("movement", ComponentType::Movement);

	//Add player1 the movement component.
	player1->AddComponent(mov);

	//Create and initialize the renderer.
	Application::renderer = new Renderer;
	Application::filesystem = new Filesystem;
	Application::renderer->Initialize(gameObjects, displayID);

}

//Void Update
void Application::Update(void)
{
	//Do loop.
	do
	{
		// Pump window messages
		Window::GetInstancePtr()->DispatchMessages();

		//If escape key, close window.
		if (GetAsyncKeyState(VK_ESCAPE))
			break;

		// Update Gamestate
		this->root->Update();
		// Render Gamestate
		Application::renderer->Render();

	} while (true);
}

//Void Cleanup
void Application::CleanUp(void)
{
	//Release all pointers and safe delete the renderer
	Application::renderer->CleanUp();
	Console::GetInstancePtr()->CleanUp();
	SAFE_DELETE(this->renderer);
	Console::GetInstancePtr()->Release();
	Window::GetInstancePtr()->Release();
	Application::GetInstancePtr()->Release();
}

Filesystem* Application::GetFilesystem()
{
	return this->filesystem;
}

