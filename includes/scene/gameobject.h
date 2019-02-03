
#pragma once
//EXTERNAL INCLUDES
#include <vector>
//INTERNAL INCLUDES
#include "node.h"
#include "math/mathfunctions.h"
#include "typedefs/transform.h"
#include "typedefs/utils.h"
#include "math/mat4x4.h"
#include "typedefs/components.h"
#include "typedefs/time.h"

//Forward declaration.
class Component;
class Rigidbody;
class Geometry;
class Shader;

//Class Gameobject derived from class Node. This is class cant be inherited.
class Gameobject final : public Node
{
//Declare public functions. And override some functions of class Node.
public:
	Gameobject
	(
		std::string name = "",
		bool render = true, bool isRoot = false, bool cam = false,
		Gameobject* parent = nullptr,
		fColorRGBA col = fColorRGBA{ 0.960f, 0.713f, 0.0f, 1.0f },
		bool hasCollision = false,
		Meshes mesh = Meshes::BOX,
		bool mirror = false
	);
	~Gameobject();

	virtual void Update(void) override;
	void Cleanup(void);

	void AddComponent(Component* component);
	void DeleteComponent(Component* component);

	void SetMeshData(Vertex* vertices, ui32* indicies, ui32 vLength, ui32 iLength);
	void SetName(std::string gameobjectName);
	void SetTag(std::string tag);
	void SetVisiblity(bool b);
	void SetVisi(bool b);
	void SetCollision(bool b);
	void SetIsColliding(bool b);
	void SetIsTrigger(bool b);
	void SetDeactivate(bool b);
	void SetActive(bool b, Gameobject* parent = nullptr);
	void SetHitObject(Gameobject* hit);

	bool hasMesh(void);
	bool hasCollision(void);
	bool isColliding(void);
	bool IsMirror(void);
	bool isDeactivate(void);
	bool isActive(void);
	bool isTrigger(void);
	bool isVisisble(void);
	bool inViewport(void);

	std::string GetName(void);
	std::string GetTag(void);
	Math::Mat4x4 GetModelMatrix(void);
	Math::Mat4x4 GetModelMatrixNoRotation(void);
	Math::Mat4x4 GetModelMatrixInvertRotation(void);
	Math::Vec3 GetWorldCorner(fColorRGBA corner);
	Math::Vec3 GetWorldCorner(fColorRGBA corner, Math::Mat4x4 matrix);
	Math::Vec3& GetEulerRotation(void);
	Math::Quaternion GetRotation(void);
	Component* GetComponent(ComponentType type);
	Transform& GetTransform(void);
	Geometry* GetMesh(void);
	Shader* GetMaterial(void);
	Gameobject* GetHitObject(void);
	Rigidbody* GetRigidbody(void);
	void CreateCopy(void);
	Gameobject* CreateCopy(bool getGb);

//Declare private variables.
private:
	Rigidbody* rigidbody;
	Gameobject* hitObject;
	Geometry* mesh;
	Shader* material;

	Transform transform;
	Math::Vec3 eulerRotation;
	Math::Mat4x4 modelMatrix;

	std::vector<Component*> components;

	std::string name;
	std::string tag; 
	bool activated = true;
	bool isMirror = false;
	bool bMesh;
	bool collision;
	bool is_colliding =  false;
	bool is_trigger = false;
	bool isRendering = true;
	bool deactivate = false;
	ui32 copied;
};
