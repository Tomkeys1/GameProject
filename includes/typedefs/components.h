
#pragma once

enum class ComponentType
{
	Movement = 0,
	Shoot = 1,
	Bullet = 2,
	Collision = 3,
	Health = 4,
	GravityShot = 5
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
	bool activated;
	real speed;
	real time;
	Math::Vec3 dir;
};

struct ShootingValues
{
	ui64 shotID;
	bool available;
	real timer;
	real cooldown;
	real speed;
	real bulletSpeed;
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
	real velocity;

	Math::Vec3 gravityDir;
	Math::Vec3 movementDir;
};

struct HealthValues
{
	bool shield;

	real health;
	real damage;
	real resistance;
};


struct RaycastInfo
{
	real distance;
	Math::Vec3 hitPosition;
	Math::Vec3 hitNormal;
};

struct GravityShotValues
{
	real timeInAir;
	real gravityRadius;
	real pullSpeed;
	real cooldown;
	real timeToExplode;

	bool activated;
	real speed;
	real time;
	Math::Vec3 dir;

	Math::Vec3 direction;
	Math::Vec3 gravityDirection;
};
