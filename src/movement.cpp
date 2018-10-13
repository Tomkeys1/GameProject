
//EXTERNAL INCLUDES
//INTERNAL INCLUDES
#include "components/movement.h"
#include "typedefs/utils.h"

//Void Initialize
void Movement::Initialize(char * comName, ComponentType comType)
{
	//Initialize the base.
	Component::Initialize(comName, comType);
}

void Movement::Update(void)
{
	//Execute the components Update function.
	Component::Update();
}
