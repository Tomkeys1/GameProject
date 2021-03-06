
#pragma once
// EXTERNAL INCLUDES
#include <thread>
#include <vector>
#include <list>
// INTERNAL INCLUDES
#include "typedefs/types.h"
#include "typedefs/utils.h"
#include "systems/console.h"
#include "systems/filesystem.h"


//Forward declarations.
class Window;
class Renderer;
class Gameobject;
class Node;
class Scene;
class Camera;


//Class Application
class Application
{
	//Define Application as a singleton. See utils.h for definition.
	DEFINE_SINGLETON(Application)

//Declare public functions.
public:
	void Initialize(char* title, iVec2 resolution, ui32 displayID = 0);
	void Update(void);
	void CleanUp(void);

	Filesystem* GetFilesystem();
	Renderer* GetRenderer();
	Scene* GetScene();

//Declare private variables
private:

	const int FRAMES_PER_SECOND = 144;
	const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;
	bool running = true;

	Scene* scene;
	Filesystem* filesystem;
	Renderer* renderer;
	Gameobject* root;

	std::vector<Gameobject*> gameObjects;
};
