
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
		fColorRGBA col = fColorRGBA{ 0.960f, 0.713f, 0.0f, 1.0f },
		bool hasCollision = false
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
	void SetCollision(bool b);
	void SetIsColliding(bool b);
	void SetIsTrigger(bool b);
	void SetHitObject(Gameobject* hit);

	bool hasMesh(void);
	bool hasCollision(void);
	bool isColliding();
	bool isTrigger(void);
	bool isVisisble(void);

	const char* GetName(void);
	Math::Vec3& GetEulerRotation(void);
	Math::Quaternion GetRotation(void);
	Math::Mat4x4 GetModelMatrix(void);
	Transform& GetTransform(void);
	Geometry* GetMesh(void);
	Shader* GetMaterial(void);
	Gameobject* GetHitObject(void);

//Declare private variables.
private:
	Gameobject* hitObject;
	Geometry* mesh;
	Shader* material;

	Transform transform;
	Math::Vec3 eulerRotation;
	Math::Mat4x4 modelMatrix;

	std::vector<Component*> components;

	const char* name;
	bool bMesh;
	bool collision;
	bool is_colliding =  false;
	bool is_trigger = false;
	bool isRendering = true;
};
