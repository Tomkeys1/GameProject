
#pragma once
//EXTERNAL INCLUDES
//INTERNAL INCLUDES
#include "component.h"

//Class Movement that is derived from class Component.
class Movement : public Component 
{
//Declare the public functions that are overwritten.
public:
	Movement();

	void Initialize(Gameobject* gb);
	virtual void Update(void) override;
	virtual void Cleanup(void) override;

	real velocity;
	real maxSpeed;
private:
	void Move();
	void Rotate(void);
	
	real speed;
	bool horizontal;
	Math::Vec3 direction;

};
