
#pragma once

enum class ComponentType
{
	Movement = 0,
	Shoot = 1,
	Bullet = 2,
	Collision = 3,
	Health = 4
};

struct MovementValues
{
	real stoppingCoefficient;
	real velocity;
	real maxSpeed;
	real speed;
	real rotationSpeed;
	Math::Vec3 direction;
};

struct BulletValues
{
	real speed;
	real time;
	Math::Vec3 dir;
};

struct ShootingValues
{
	bool available;
	real timer;
	real speed;
	real growth;
	real time;
};

struct RigidbodyValues
{
	bool isEnabled;
	bool isKinematic;
	bool gravityEnabled;

	real mass;
	real airDensity;
	real dragCoefficient;
	real areaOfObject;

	Math::Vec3 gravityDir;
};

struct HealthValues
{
	bool shield;

	real health;
	real damage;
	real resistance;
};
