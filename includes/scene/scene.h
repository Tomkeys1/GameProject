
#pragma once
//EXTERNAL INCLUDES
#include <map>
//INTERNAL INCLUDES
#include "typedefs/types.h"


class Gameobject;
class Component;

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
	void Update(void);
	void Cleanup(void);

	void AddGameobject(const char* name, CreateMode mode, Gameobject* parent = nullptr, fColorRGBA color = fColorRGBA{ 0.960f, 0.713f, 0.0f, 1.0f });
	void AddMesh(Gameobject* gb, Vertex* vertices, ui32* indicies, ui32 vLength, ui32 iLength);
	void AddComponent(Gameobject* gb, Component* comType);

	Gameobject* GetGameobject(std::string name);
	Gameobject* GetGameobject();

private:
	Gameobject* root;
	std::map < std::string, Gameobject* > gameObjects;
};