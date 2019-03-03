
#pragma once

//EXTERNAL INCLUDES
#include <thread>
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
	void Damage(void);
	bool damaging = false;
	std::thread damageThread;
	HealthValues health;
};