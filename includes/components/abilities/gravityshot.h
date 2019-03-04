
#pragma once
//EXTERNAL INCLUDES
#include <thread>
//INTERNAL INCLUDES
#include "components/component.h"


//Class Movement that is derived from class Component.
class GravityShot : public Component
{
	//Declare the public functions that are overwritten.
public:
	GravityShot();

	void Initialize(Gameobject* gb);
	virtual void Update(void) override;
	virtual void Cleanup(void) override;
	GravityShotValues& GetBulletValues(void);

private:
	void Deflect(void);
	bool deflecting = false;
	std::thread mirrorThread;
	GravityShotValues gravityShot;
	Gameobject* origin;
};