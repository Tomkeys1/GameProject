
#pragma once

//EXTERNAL INCLUDES
//INTERNAL INCLUDES
#include "component.h"

//Class Movement that is derived from class Component.
class Health : public Component
{
	//Declare the public functions that are overwritten.
public:
	Health();

	void Initialize(Gameobject* gb);
	virtual void Update(void) override;
	virtual void Cleanup(void) override;
	HealthValues& GetHealthValues(void);

private:
	HealthValues health;
};