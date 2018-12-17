
#pragma once
//EXTERNAL INCLUDES
#include <vector>
//INTERNAL INCLUDES
#include "node.h"
#include "typedefs/transform.h"
#include "typedefs/utils.h"
#include "math/mat4x4.h"

//Forward declaration.
class Component;
class Geometry;
class Shader;

//Class Gameobject derived from class Node. This is class cant be inherited.
class Gameobject final : public Node
{
//Declare public functions. And override some functions of class Node.
public:
	Gameobject
	(
		bool render = true, bool isRoot = false, bool cam = false,
		Gameobject* parent = nullptr,
		fColorRGBA col = fColorRGBA{ 0.960f, 0.713f, 0.0f, 1.0f }
	);

	Gameobject
	(
		Vertex* vertices, ui32* indicies, ui32 vLength, ui32 iLength, 
		fColorRGBA col = fColorRGBA{ 0.960f, 0.713f, 0.0f, 1.0f }, 
		bool render = true, bool isRoot = false,
		Gameobject* parent = nullptr
	);

	~Gameobject();

	virtual void Update(void) override;
	void Cleanup(void);

	void AddComponent(Component* component);
	void DeleteComponent(Component* component);

	void SetMeshData(Vertex* vertices, ui32* indicies, ui32 vLength, ui32 iLength);
	void SetName(const char* gameobjectName);
	void SetVisiblity(bool b);
	void SetVisi(bool b);

	bool hasMesh(void);
	bool isVisisble(void);

	const char* GetName(void);
	Math::Mat4x4 GetModelMatrix(void);
	Transform& GetTransform(void);
	Geometry* GetMesh(void);
	Shader* GetMaterial(void);

//Declare private variables.
private:

	Geometry* mesh;
	Shader* material;

	Transform transform;
	Math::Mat4x4 modelMatrix;

	std::vector<Component*> components;

	const char* name;
	bool bMesh;
	bool isRendering = true;
};
