
#pragma once
//EXTERNAL INCLUDES
//INTERNAL INCLUDES
#include "component.h"

//Class Movement that is derived from class Component.
class Movement : public Component 
{
//Declare the public functions that are overwritten.
public:
	virtual void Initialize(char* comName, ComponentType comType) override;
	virtual void Update(void) override;
};
