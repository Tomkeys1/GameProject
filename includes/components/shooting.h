
#pragma once
//EXTERNAL INCLUDES
//INTERNAL INCLUDES
#include "component.h"

//Class Movement that is derived from class Component.
class Shooting : public Component
{
	//Declare the public functions that are overwritten.
public:
	Shooting();

	void Initialize(Gameobject* gb);
	virtual void Update(void) override;
	virtual void Cleanup(void) override;

	ShootingValues& GetShootingValues(void);
private:
	Math::Vec3 GetPos(Gameobject* gb);

	ShootingValues shoot;
};