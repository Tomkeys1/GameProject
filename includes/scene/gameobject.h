
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
	Gameobject();

	virtual void Update(void) override;
	void Cleanup(void);

	void AddComponent(Component* component);
	void DeleteComponent(Component* component);

	void SetMeshData(fColorRGBA col = fColorRGBA{ 0.960f, 0.713f, 0.0f, 1.0f });
	void SetMeshData(Vertex* vertices, ui32* indicies, ui32 vLength, ui32 iLength);
	void SetName(char* gameobjectName);

	bool hasMesh(void);

	Math::Mat4x4 GetModelMatrix(void);
	Transform& GetTransform(void);
	Geometry* GetMesh(void);
	Shader* GetMaterial(void);

//Declare private variables.
private:
	char* name;
	bool bMesh;

	Geometry* mesh;
	Shader* material;

	Transform transform;
	Math::Mat4x4 modelMatrix;

	std::vector<Component*> components;


};
