
//EXTERNAL INCLUDES
//INTERNAL INCLUDES
#include "application.h"
#include "scene/scene.h"
#include "scene/gameobject.h"
#include "components/movement.h"
#include "components/abilities/gravityshot.h"
#include "components/shooting.h"
#include "components/bullet.h"
#include "rendering/renderer.h"
#include "rendering/geometry.h"
#include "rendering/shader.h"
#include "rendering/camera.h"
#include "physics/rigidbody.h"
#include "components/health.h"

//Gameobject Constructor.
Gameobject::Gameobject(std::string name, bool render, bool isRoot, bool cam, Gameobject* parent, fColorRGBA col, bool hasCollision, Meshes mesh, bool mirror)
{
	//Set this gameobjects position, scaling and rotation to 0;
	this->transform.position = { 0, 0, 0 };
	this->transform.scaling = { 1, 1, 0 };
	this->transform.rotation = { 1, 0, 0, 0 };
	this->eulerRotation = { 0, 0, 0 };

	this->name = name;


	if (cam)
		return;

	if (render)
	{
		this->material = new Shader();
		this->mesh = new Geometry(this, col, mesh);
		this->bMesh = true;
	}
	else
	{	
		this->bMesh = false;
	}

	this->copied = 0;
	this->collision = hasCollision;
	this->tag = "";
	this->hitObject = nullptr;
	this->isMirror = mirror;


	this->rigidbody = new Rigidbody(this);
	this->rigidbody->GetRigidbodyValues().mass = 100.0f;
	this->rigidbody->GetRigidbodyValues().isEnabled = false;
	this->rigidbody->GetRigidbodyValues().isKinematic = false;
	this->rigidbody->GetRigidbodyValues().dragCoefficient = 0.024f;
	this->rigidbody->GetRigidbodyValues().airDensity = 1.20f;
	this->rigidbody->GetRigidbodyValues().gravityDir = Math::Vec3::neg_unit_y;

	if (isRoot)
	{
		this->activated = true;
	}
	else
	{
		this->SetActive(true, parent);	
	}

}

void Gameobject::CreateCopy(void)
{
	std::string tempName = this->name;
	tempName += '(' + std::to_string(this->copied) + ')';
	this->copied++;

	Gameobject* temp = new Gameobject(this->name, this->bMesh, false, false, reinterpret_cast<Gameobject*>(this->GetParent()), this->mesh->GetColor(), this->collision, this->mesh->GetMeshType(), this->isMirror);
	temp->transform = this->transform;
	temp->rigidbody->GetRigidbodyValues() = this->rigidbody->GetRigidbodyValues();
	temp->eulerRotation = this->eulerRotation;
	temp->tag = this->tag;
	temp->name = tempName;
	temp->is_trigger = this->is_trigger;
	temp->isRendering = this->isRendering;
	temp->modelMatrix = this->modelMatrix;

	Application::GetInstancePtr()->GetScene()->AddGameobject(temp);

	for (Component* com : this->components)
	{
		switch (com->GetType())
		{
		case ComponentType::Movement:
		{
			Movement* mov = new Movement;
			mov->GetMovementValues() = reinterpret_cast<Movement*>(this->GetComponent(ComponentType::Movement))->GetMovementValues();
			Application::GetInstancePtr()->GetScene()->AddComponent(temp, mov);
		}
		break;
		case ComponentType::Bullet:
		{
			Bullet* bul = new Bullet;
			bul->GetBulletValues() = reinterpret_cast<Bullet*>(this->GetComponent(ComponentType::Bullet))->GetBulletValues();
			Application::GetInstancePtr()->GetScene()->AddComponent(temp, bul);
		}
		break;
		case ComponentType::Shoot:
		{
			Shooting* shot = new Shooting;
			shot->GetShootingValues() = reinterpret_cast<Shooting*>(this->GetComponent(ComponentType::Shoot))->GetShootingValues();
			Application::GetInstancePtr()->GetScene()->AddComponent(temp, shot);
		}
		break;
		case ComponentType::Health:
		{
			Health* health = new Health;
			health->GetHealthValues() = reinterpret_cast<Health*>(this->GetComponent(ComponentType::Health))->GetHealthValues();
			Application::GetInstancePtr()->GetScene()->AddComponent(temp, health);
		}
		break;
		case ComponentType::GravityShot:
		{
			GravityShot* gShot = new GravityShot;
			gShot->GetBulletValues() = reinterpret_cast<GravityShot*>(this->GetComponent(ComponentType::GravityShot))->GetBulletValues();
			Application::GetInstancePtr()->GetScene()->AddComponent(temp, gShot);
		}
		break;
		}
	}

	Application::GetInstancePtr()->GetRenderer()->InitializeGameobject(temp);
	temp->SetActive(this->activated);
}

Gameobject* Gameobject::CreateCopy(bool getGb)
{
	std::string tempName = this->name;
	tempName += '(' + std::to_string(this->copied) + ')';
	this->copied++;

	Gameobject* temp = new Gameobject(this->name, this->bMesh, false, false, reinterpret_cast<Gameobject*>(this->GetParent()), this->mesh->GetColor(), this->collision, this->mesh->GetMeshType(), this->isMirror);
	temp->transform = this->transform;
	temp->rigidbody->GetRigidbodyValues() = this->rigidbody->GetRigidbodyValues();
	temp->eulerRotation = this->eulerRotation;
	temp->tag = this->tag;
	temp->name = tempName;
	temp->is_trigger = this->is_trigger;
	temp->isRendering = this->isRendering;
	temp->modelMatrix = this->modelMatrix;
	temp->SetActive(this->activated);

	Application::GetInstancePtr()->GetScene()->AddGameobject(temp);

	for (Component* com : this->components)
	{
		switch (com->GetType())
		{
		case ComponentType::Movement:
		{
			Movement* mov = new Movement;
			mov->GetMovementValues() = reinterpret_cast<Movement*>(this->GetComponent(ComponentType::Movement))->GetMovementValues();
			Application::GetInstancePtr()->GetScene()->AddComponent(temp, mov);
		}
		break;
		case ComponentType::Bullet:
		{
			Bullet* bul = new Bullet;
			bul->GetBulletValues() = reinterpret_cast<Bullet*>(this->GetComponent(ComponentType::Bullet))->GetBulletValues();
			Application::GetInstancePtr()->GetScene()->AddComponent(temp, bul);
		}
		break;
		case ComponentType::Shoot:
		{
			Shooting* shot = new Shooting;
			shot->GetShootingValues() = reinterpret_cast<Shooting*>(this->GetComponent(ComponentType::Shoot))->GetShootingValues();
			Application::GetInstancePtr()->GetScene()->AddComponent(temp, shot);
		}
		break;
		case ComponentType::Health:
		{
			Health* health = new Health;
			health->GetHealthValues() = reinterpret_cast<Health*>(this->GetComponent(ComponentType::Health))->GetHealthValues();
			Application::GetInstancePtr()->GetScene()->AddComponent(temp, health);
		}
		break;
		case ComponentType::GravityShot:
		{
			GravityShot* gShot = new GravityShot;
			gShot->GetBulletValues() = reinterpret_cast<GravityShot*>(this->GetComponent(ComponentType::GravityShot))->GetBulletValues();
			Application::GetInstancePtr()->GetScene()->AddComponent(temp, gShot);
		}
		break;
		}
	}

	Application::GetInstancePtr()->GetRenderer()->InitializeGameobject(temp);

	return temp;
}

Gameobject::~Gameobject()
{
	this->Cleanup();
}

//Void Update
void Gameobject::Update()
{
	if (!this->activated)
		return;

	//Execute the bases Update.
	Node::Update();

	this->rigidbody->Update();

	//For all component pointers in the components list of this gameobject.
	for (Component* component : this->components)  
	{
		//Check for the component type.
		//Update the casted components.
		switch (component->GetType()) 
		{
			case ComponentType::Movement :
				(reinterpret_cast<Movement*>(component))->Update();
				break;
			case ComponentType::Bullet:
				(reinterpret_cast<Bullet*>(component))->Update();
				break;
			case ComponentType::Shoot:
				(reinterpret_cast<Shooting*>(component))->Update();
				break;
			case ComponentType::Health:
				(reinterpret_cast<Health*>(component))->Update();
				break;
			case ComponentType::GravityShot:
				(reinterpret_cast<GravityShot*>(component))->Update();
				break;
		}
	}
}

//Void Cleanup
void Gameobject::Cleanup(void)
{
	//Empty this gameobjects name.
	this->name = "";
	SAFE_DELETE(this->rigidbody)

	for (Component* component : this->components)
	{
		//Check for the component type.
		//Update the casted components.
		switch (component->GetType())
		{
		case ComponentType::Movement:
			(reinterpret_cast<Movement*>(component))->Cleanup();
			break;
		case ComponentType::Shoot:
			(reinterpret_cast<Shooting*>(component))->Cleanup();
			break;
		case ComponentType::Bullet:
			(reinterpret_cast<Bullet*>(component))->Cleanup();
			break;
		case ComponentType::Health:
			(reinterpret_cast<Health*>(component))->Cleanup();
			break;
		case ComponentType::GravityShot:
			(reinterpret_cast<GravityShot*>(component))->Cleanup();
			break;
		}

		delete component;
	}
	this->components.clear();
	Node::Cleanup();

}

//Void AddComponent
void Gameobject::AddComponent(Component* component)
{
	//Store the inputed component pointer into this gameobjects components list.
	this->components.push_back(component);
}

//Void DeleteComponent
void Gameobject::DeleteComponent(Component* component)
{
	//Get the id of the inputed component pointer in this gameobjects components list.
	std::ptrdiff_t id = std::find(this->components.begin(), this->components.end(), component) - this->components.begin();

	//If the id is in this gameobjects components list.
	if (id >= this->components.size())
	{
		//Delete the component.
		this->components.erase(this->components.begin() + id);
	}
	else
	{
		//Component wasnt found.
		LOG("The Component wasnt found.");
	}
}

void Gameobject::SetMeshData(Vertex* vertices, ui32* indicies, ui32 vLength, ui32 iLength)
{
	this->material = new Shader();
	this->mesh = new Geometry(vertices, indicies, vLength, iLength, this);
	this->bMesh = true;
}

std::string Gameobject::GetName(void)
{
	return this->name;
}

std::string  Gameobject::GetTag(void)
{
	return this->tag;
}

Math::Vec3 Gameobject::GetWorldCorner(fColorRGBA corner)
{
	Math::Mat4x4 mvp = Application::GetInstancePtr()->GetRenderer()->GetCamera()->GetVP() * this->GetModelMatrixInvertRotation();

	fColorRGBA temp2 = corner * mvp;

	return Math::Vec3
	{
		this->GetTransform().position.x + temp2.r * 100.0f,
		this->GetTransform().position.y + temp2.g * 100.0f,
		0.0f,
	};
}

Math::Vec3 Gameobject::GetWorldCorner(fColorRGBA corner, Math::Mat4x4 matrix)
{
	Math::Mat4x4 mvp = Application::GetInstancePtr()->GetRenderer()->GetCamera()->GetVP() * matrix;

	fColorRGBA temp2 = corner * mvp;

	return Math::Vec3
	{
		this->GetTransform().position.x + temp2.r * 100.0f,
		this->GetTransform().position.y + temp2.g * 100.0f,
		0.0f,
	};
}

Math::Vec3& Gameobject::GetEulerRotation(void)
{
	return this->eulerRotation;
}

Math::Quaternion Gameobject::GetRotation(void)
{
	return this->transform.rotation;
}

Component* Gameobject::GetComponent(ComponentType type)
{
	for (Component* component : this->components)
	{
		if (component->GetType() == type)
			return component;
	}
	return nullptr;
}

Math::Mat4x4 Gameobject::GetModelMatrix(void)
{
	this->modelMatrix = Math::Mat4x4::identity;
	modelMatrix = modelMatrix * Math::CreateRotationMatrix(this->eulerRotation);
	modelMatrix = modelMatrix * Math::CreateScalingMatrix(this->transform.scaling * 100.0f);
	modelMatrix = modelMatrix * Math::CreateTranslationMatrix(this->transform.position / 100.0f);

	return this->modelMatrix;
}

Math::Mat4x4 Gameobject::GetModelMatrixNoRotation(void)
{
	Math::Mat4x4 temp = Math::Mat4x4::identity;
	temp = temp * Math::CreateRotationMatrix(Math::Vec3::zero);
	temp = temp * Math::CreateScalingMatrix(this->transform.scaling * 100.0f);
	temp = temp * Math::CreateTranslationMatrix(this->transform.position / 100.0f);

	return temp;
}

Math::Mat4x4 Gameobject::GetModelMatrixInvertRotation(void)
{
	Math::Mat4x4 temp = Math::Mat4x4::identity;
	temp = temp * Math::CreateRotationMatrix(Math::Negate(this->eulerRotation));
	temp = temp * Math::CreateScalingMatrix(this->transform.scaling * 100.0f);
	temp = temp * Math::CreateTranslationMatrix(this->transform.position / 100.0f);

	return temp;
}

//GetTransform
Transform& Gameobject::GetTransform(void)
{
	//Return this gameobjects transform.
	return this->transform;
}

Geometry* Gameobject::GetMesh(void)
{
	return this->mesh;
}

Shader* Gameobject::GetMaterial(void)
{
	return this->material;
}

Gameobject * Gameobject::GetHitObject(void)
{
	return this->hitObject;
}


Rigidbody* Gameobject::GetRigidbody(void)
{
	return this->rigidbody;
}

//Set name
void Gameobject::SetName(std::string gameobjectName)
{
	//Set this gameobjects name.
	this->name = gameobjectName;
}

void Gameobject::SetTag(std::string tag)
{
	this->tag = tag;
}

void Gameobject::SetVisiblity(bool b)
{
	this->isRendering = b;

	for (Node* child : this->GetAllChildren())
	{
		reinterpret_cast<Gameobject*>(child)->SetVisi(b);
	}
}

void Gameobject::SetVisi(bool b)
{
	this->isRendering = b;
}

void Gameobject::SetCollision(bool b)
{
	this->collision = b;
}

void Gameobject::SetIsColliding(bool b)
{
	this->is_colliding = b;
}

void Gameobject::SetIsTrigger(bool b)
{
	this->is_trigger = b;
}

void Gameobject::SetDeactivate(bool b)
{
	this->deactivate = b;
}

void Gameobject::SetActive(bool b, Gameobject* parent)
{
	this->activated = b;
	Application::GetInstancePtr()->GetScene()->SetActivity(this, parent, b);
}

void Gameobject::SetHitObject(Gameobject* hit)
{
	this->hitObject = hit;
}

bool Gameobject::hasMesh()
{
	if (this->bMesh == true)
		return true;
	return false;
}

bool Gameobject::hasCollision(void)
{
	return this->collision;
}

bool Gameobject::isColliding()
{
	return this->is_colliding;
}

bool Gameobject::IsMirror(void)
{
	return this->isMirror;
}

bool Gameobject::isDeactivate(void)
{
	return this->deactivate;
}

bool Gameobject::isActive(void)
{
	return this->activated;
}

bool Gameobject::isTrigger(void)
{
	return this->is_trigger;
}

bool Gameobject::isVisisble(void)
{
	if (this->isRendering == true)
		return true;
	return false;
}

bool Gameobject::inViewport(void)
{
	Math::Vec3 corners[4] =
	{
		this->GetWorldCorner(fColorRGBA{ 1, 1, 0, 1.0f }),
		this->GetWorldCorner(fColorRGBA{ -1, 1, 0, 1.0f }),
		this->GetWorldCorner(fColorRGBA{ -1, -1, 0, 1.0f }),
		this->GetWorldCorner(fColorRGBA{ 1, -1, 0, 1.0f }),
	};

	real xMin, xMax, yMin, yMax;

	Math::GetMinMaxOfProjection(corners, Math::Vec3::unit_x, xMin, xMax);
	Math::GetMinMaxOfProjection(corners, Math::Vec3::unit_y, yMin, yMax);

	if (xMin > 100.0f) return false;
	if (xMax < -100.0f) return false;
	if (yMin > 100.0f) return false;
	if (yMax < -100.0f) return false;

	return true;
}
