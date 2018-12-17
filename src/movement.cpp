
//EXTERNAL INCLUDES
//INTERNAL INCLUDES
#include "systems/inputhandler.h"
#include "components/movement.h"
#include "typedefs/utils.h"

//Void Initialize
void Movement::Initialize(char* comName, ComponentType comType, Gameobject* gb)
{
	//Initialize the base.
	Component::Initialize(comName, comType, gb);
}

void Movement::Update(void)
{
	//Execute the components Update function.
	Component::Update();

	if (Input::GetInstancePtr()->GetKey(KeyCode::A))
	{
		this->GetGameObject()->GetTransform().position.x -= 0.0001f;
	}
	else if (Input::GetInstancePtr()->GetKey(KeyCode::D))
	{
		this->GetGameObject()->GetTransform().position.x += 0.0001f;
	}

	if (Input::GetInstancePtr()->GetKey(KeyCode::S))
	{
		this->GetGameObject()->GetTransform().position.y -= 0.0001f;
	}
	else if (Input::GetInstancePtr()->GetKey(KeyCode::W))
	{
		this->GetGameObject()->GetTransform().position.y += 0.0001f;
	}

	if (Input::GetInstancePtr()->GetKeyUp(KeyCode::V))
	{
		this->GetGameObject()->SetVisiblity(!this->GetGameObject()->isVisisble());
	}
}

void Movement::Cleanup(void)
{
	Component::Cleanup();

}
