
#pragma once
//EXTERNAL INCLUDES
#include <map>
#include <vector>
#include <thread>
//INTERNAL INCLUDES
#include "typedefs/types.h"


class Gameobject;
class Component;
class EnemySpawner;

enum class CreateMode 
{
	EMPTY,
	NORMAL
};



class Scene
{
public:
	Scene();

	void Initialize(void);
	void Update(real deltaTime);
	void Cleanup(void);

	void CreateObjectPool(std::string name, ui32 amount, Gameobject* type);
	void AddGameobject(const char* name, CreateMode mode, Gameobject* parent = nullptr, fColorRGBA color = fColorRGBA{ 0.960f, 0.713f, 0.0f, 1.0f }, bool hasCollision = false, Meshes mesh = Meshes::BOX, bool isMirror = false);
	void AddGameobject(Gameobject* gb);
	void AddMesh(Gameobject* gb, Vertex* vertices, ui32* indicies, ui32 vLength, ui32 iLength);
	void AddComponent(Gameobject* gb, Component* comType);
	void DeleteGameobject(Gameobject* gb, bool deactivate);

	void SetActivity(Gameobject* gb, Gameobject* parent, bool active);

	void DeleteGameobjects(void);

	Gameobject* GetGameobject(std::string name);
	Gameobject* GetGameobject();
	Gameobject* GetObjectItem(std::string objectPool, bool deleteObject);
	EnemySpawner* GetEnemySpawner(void);
	bool& GetPaused();
	bool& GetEnd();

private:
	bool paused = false;
	bool end = false;

	Gameobject* root;
	EnemySpawner* eSpawner;
	std::map <std::string, std::vector<Gameobject*>> objectPools;
	std::map < std::string, Gameobject* > sleeping_gameObjects;
	std::map < std::string, Gameobject* > gameObjects;
	std::vector< Gameobject* > deleteGb;
};