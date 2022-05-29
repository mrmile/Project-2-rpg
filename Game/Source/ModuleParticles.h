#ifndef __MODULE_PARTICLES_H__
#define __MODULE_PARTICLES_H__

#include "Module.h"

//#include "Globals.h"
#include "Particle.h"
#include "Collider.h"
#include "Log.h"

#define MAX_ACTIVE_PARTICLES 100

struct SDL_Texture;
struct Collider;

class ModuleParticles : public Module
{
public:
	// Constructor
	// Initializes all the particles in the array to nullptr
	ModuleParticles(bool start_enabled = true);

	//Destructor
	~ModuleParticles();

	// Called when the module is activated
	// Loads the necessary textures for the particles
	bool Start() override;

	// Called at the beginning of the application loop
	// Removes all particles pending to delete
	bool PreUpdate() override;

	// Called at the middle of the application loop
	// Iterates all the particles and calls its Update()
	// Removes any "dead" particles
	bool Update(float dt) override;

	// Called at the end of the application loop
	// Iterates all the particles and draws them
	bool PostUpdate() override;

	// Called on application exit
	// Destroys all active particles left in the array
	bool CleanUp() override;

	// Called when a particle collider hits another collider
	void OnCollision(Collider* c1, Collider* c2) override;

	// Creates a new particle and adds it to the array
	// Param particle	- A template particle from which the new particle will be created
	// Param x, y		- Position x,y in the screen (upper left axis)
	// Param delay		- Delay time from the moment the function is called until the particle is displayed in screen
	Particle* AddParticle(const Particle& particle, int x, int y, Collider::Type colliderType = Collider::Type::NONE, uint delay = 0);

public:

	//Template particle for explosion (example)
	Particle enemyDefeat;
	Particle coin;
	Particle lifeRecoverPowerUp;
	Particle checkPoint;
	Particle checkPointGrabbed;
	Particle goalPool;
	Particle firework1;
	Particle firework2;
	Particle firework3;


	Particle enemyAttack;
	Particle RangedAttack;
	Particle playerAttack;
	Particle playerRangedAttack;

	Particle RadioActive;
	Particle PlayerPickUpRadius;

	Particle ItemFood;
	Particle ItemHealthPack;
	Particle ItemRadio;
	Particle ItemCard;
	Particle ItemDefaultGun;
	Particle ItemLongRangeGun;
	Particle ItemShortRangeGun;
	Particle ItemKnife;
	Particle ItemGrenade;
	Particle ItemSuit;
	Particle ItemGun;

public:
	// Particles spritesheet loaded into an SDL Texture
	SDL_Texture* texture = nullptr;
	SDL_Texture* texture_items = nullptr;

	// An array to store and handle all the particles
	Particle* particles[MAX_ACTIVE_PARTICLES] = { nullptr };

};

#endif // !__MODULEPARTICLES_H__