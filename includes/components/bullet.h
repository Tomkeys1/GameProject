#pragma once
//EXTERNAL INCLUDES
//INTERNAL INCLUDES
#include "component.h"

//Class Movement that is derived from class Component.
class Bullet : public Component
{
	//Declare the public functions that are overwritten.
public:
	Bullet();

	void Initialize(Gameobject* gb);
	virtual void Update(void) override;
	virtual void Cleanup(void) override;
	void SetBulletValues(real speed, real time);

private:
	real speed;
	real time;


};