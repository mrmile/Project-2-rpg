#ifndef __MODULE_PLAYER_H__
#define __MODULE_PLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"
#include "ModulePhysics.h"

// sound fx web: https://themushroomkingdom.net/media/smw2/wav

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	// Constructor
	ModulePlayer(bool start_enabled = false);

	// Destructor
	~ModulePlayer();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Load / Save
	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&) const;

	//void b2dOnCollision(PhysBody* bodyA, PhysBody* bodyB);

	// Collision callback, called when the player intersects with another collider
	void OnCollision(Collider* c1, Collider* c2) override;

	iPoint GetLastPosition();
	

public:
	// Position of the player in the map
	iPoint position;
	//b2Vec2 positionToB2D;

	//Player body for physics implementation
	PhysBody* Player;
	
	//TEST OF IMPLEMENTATION
	PhysBody* TestingGround;

	// The speed in which we move the player (pixels per frame)
	int speed = 1;

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;
	
	//TEXTURE FOR UI LIFES AND COINS
	SDL_Texture* texture2 = nullptr;

	SDL_Texture* ptsScore;
	SDL_Texture* livesForScore;

	SDL_Texture* gameOverScreen;

	SDL_Texture* yoshiIcon;

	SDL_Texture* clockIcon;

	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;

	// A set of animations
	Animation idleRightAnim;
	Animation idleLeftAnim;
	Animation idleDownAnim;
	Animation idleUpAnim;

	Animation idleUpLeftAnim;
	Animation idleUpRightAnim;
	Animation idleDownLeftAnim;
	Animation idleDownRightAnim;


	Animation rightWalkAnim;
	Animation leftWalkAnim;
	Animation downWalkAnim;
	Animation upWalkAnim;

	Animation rightDownWalkAnim;
	Animation leftDownWalkAnim;
	Animation rightUpWalkAnim;
	Animation leftUpWalkAnim;


	Animation rightRunAnim; // Las animaciones de Run son las mismas que las del walk pero se le cambia la velocidad del pushBack()
	Animation leftRunAnim;
	Animation downRunAnim;
	Animation upRunAnim;

	Animation rightDownRunAnim;
	Animation leftDownRunAnim;
	Animation rightUpRunAnim;
	Animation leftUpRunAnim;


	Animation die;
	Animation battleWin;

	

	// Sound effects indices
	uint jumpSound = 0;
	uint hoverSound = 0;
	uint hoverSoundL = 0;
	uint dead = 0;
	uint damaged = 0;
	uint halfWayPoint = 0;
	uint coin = 0;
	uint recoverLifePowerUp = 0;
	uint levelClear = 0;
	uint firework = 0;
	uint paused = 0;
	uint gameOverfx = 0;

	// The player's colliders
	Collider* collider = nullptr;
	Collider* colliderFeet = nullptr;

	// A flag to detect when the player has been destroyed
	bool destroyed = false;

	// Font score index
	uint score = 000;
	int scoreFont = -1;
	char scoreText[10] = { "\0" };
	char lifeText[10] = { "\0" };
	char timerText[10] = { "\0" };

	//Lives player
	uint lives = 3;
	int livesFont = -1;
	char livesText[10] = { "\0" };
	int TransationToTilteDelay;
	int PlayerLookingPosition;
	int sceneTimer = 450;

	int playerTimer;
	int playerIdleAnimationTimer;
	int hoverTimer;
	int destroyedDelay;
	int playerHP;
	int invincibleDelay;
	int playerFPS;
	int playerScore = 0;
	bool playerWin= false;
	int winDelay;
	int gameOverDelay;
	bool checkPointReached;

	b2Vec2 b2VelocitySet;

	//Margin of movement
	int horizontalMargin = 45;

	//Collision bools
	bool plantCollision;

	bool pauseMenu = false;

	bool hasBeenDrawed = false;

	//Action things
	bool run = false;
	bool talking = false;
	bool horizontalCB = false;
	bool verticalCB = false;
	bool bidimensionalCB = false;
	bool createPlayer;
	bool deletePlayer;
	bool layerZeroReveal;
	
	//test for continue mechanic
	bool saved_game = false;

	int entranceID;
	bool exitActivated;

	//test for the dialog system
	bool npcClose = false;
	bool npc2Close = false;
	bool npc3Close = false;
	bool npc4Close = false;
};

#endif //!__MODULE_PLAYER_H__