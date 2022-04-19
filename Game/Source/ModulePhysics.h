#pragma once
#include "Module.h"
#include "App.h"
#include "Box2D/Box2D/Box2D.h"

#define GRAVITY_X 0.0f
#define GRAVITY_Y -32.0f

#define PIXELS_PER_METER 50.0f // if touched change METER_PER_PIXEL too
#define METER_PER_PIXEL 0.02f // this is 1 / PIXELS_PER_METER !

#define METERS_TO_PIXELS(m) ((int) floor(PIXELS_PER_METER * m))
#define PIXEL_TO_METERS(p)  ((float) METER_PER_PIXEL * p)

// Small class to return to other modules to track position and rotation of physics bodies
class PhysBody
{
public:
	PhysBody() : listener(NULL), body(NULL)
	{}

	void GetPosition(int& x, int &y) const;
	float GetRotation() const;
	bool Contains(int x, int y) const;
	int RayCast(int x1, int y1, int x2, int y2, float& normal_x, float& normal_y) const;

public:
	int width, height;
	b2Body* body;
	Module* listener;
};

// Module --------------------------------------
class ModulePhysics : public Module, public b2ContactListener // TODO
{
public:
	ModulePhysics(bool start_enabled = false);
	~ModulePhysics();

	bool Awake(pugi::xml_node&);
	bool Start();
	bool PreUpdate();
	bool PostUpdate();
	bool CleanUp();

	PhysBody* CreateCircle(int x, int y, int radius);
	PhysBody* CreateColliderRectangle(int x, int y, int width, int height);
	PhysBody* CreateRectangleSensor(int x, int y, int width, int height);
	PhysBody* CreateChain(int x, int y, int* points, int size);
	PhysBody* CreateChainLava(int x, int y, int* points, int size);
	PhysBody* CreatePlayerBox(int x, int y, int width, int height);
	PhysBody* CreatePlayerCircle(int x, int y, int radius);
	PhysBody* CreateNPCbox(int x, int y, int width, int height);
	PhysBody* CreateWalkingEnemyBox(int x, int y, int width, int height);

	// b2ContactListener ---
	void BeginContact(b2Contact* contact);

private:

	bool debug;
	b2World* world;
	b2Body* ground;
	
};