#ifndef __MODULE_PLAYER_H__
#define __MODULE_PLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"
#include "ModulePhysics.h"
#include "GameManager.h"
#include "GuiButton.h"


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

	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Load / Save
	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&) const;

	bool OnGuiMouseClickEvent(GuiControl* control);

	//void b2dOnCollision(PhysBody* bodyA, PhysBody* bodyB);

	// Collision callback, called when the player intersects with another collider
	void OnCollision(Collider* c1, Collider* c2) override;

	iPoint GetLastPosition();


	void RangedAttack();

	void MeleeAttack();
	

public:
	// Position of the player in the map
	iPoint position;
	
	int counter;

	int CounterForEnemySelection = -1;
	iPoint enemySelected;

	bool EnemySelectionBool = false;
	//Player body for physics implementation
	PhysBody* Player;

	//Related to Equipment (this will be later used in combat)
	
	int EquipmentRange;
	int EquipmentDamage;

	//Computer Puzzle from the Military Base
	int computerPhase = 0;
	bool note1 = false;
	bool note5 = false;
	bool note10 = false;
	bool note15 = false;

	int MeleeDamage;

	int PlayerMaxHP;
	// The speed in which we move the player (pixels per frame)
	int speed = 1;

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;
	
	//TEXTURE FOR UI LIFES AND -?-
	SDL_Texture* texture2 = nullptr;

	SDL_Texture* ptsScore = nullptr;

	SDL_Texture* gameOverScreen = nullptr;

	SDL_Texture* doctorNote = nullptr;

	SDL_Texture* computerBG = nullptr;

	SDL_Texture* selectedEnemy = nullptr;

	SDL_Texture* selectedEnemyNotInRange = nullptr;

	//Computer textures and GUI

	SDL_Texture* returnComputer = nullptr;
	SDL_Texture* computerExecutable = nullptr;
	SDL_Texture* noteComputerDay1 = nullptr;
	SDL_Texture* noteComputerDay5 = nullptr;
	SDL_Texture* noteComputerDay10 = nullptr;
	SDL_Texture* noteComputerDay15 = nullptr;
	SDL_Texture* folderComputer = nullptr;

	SDL_Texture* noteDay1 = nullptr;
	SDL_Texture* noteDay5 = nullptr;
	SDL_Texture* noteDay10 = nullptr;
	SDL_Texture* noteDay15 = nullptr;

	GuiButton* returnComputerGUI;
	GuiButton* computerExecutableGUI;
	GuiButton* noteComputerDay1GUI;
	GuiButton* noteComputerDay5GUI;
	GuiButton* noteComputerDay10GUI;
	GuiButton* noteComputerDay15GUI;
	GuiButton* folderComputerGUI;

	SDL_Texture* characterHealth100 = nullptr;
	SDL_Texture* characterHealth80 = nullptr;
	SDL_Texture* characterHealth60 = nullptr;
	SDL_Texture* characterHealth40 = nullptr;
	SDL_Texture* characterHealth20 = nullptr;
	SDL_Texture* characterHealth20Grey = nullptr;
	SDL_Texture* characterHealth0 = nullptr;

	//Low Health Effects
	SDL_Texture* lowHealthBlood = nullptr;
	SDL_Texture* lowHealthGreyBg = nullptr;

	//Inventory and Map Icons
	SDL_Texture* inventoryMapIcons = nullptr;

	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;

	// A set of animations

	//IDLE

	Animation idleRightAnim;
	Animation idleLeftAnim;
	Animation idleDownAnim;
	Animation idleUpAnim;

	Animation idleUpLeftAnim;
	Animation idleUpRightAnim;
	Animation idleDownLeftAnim;
	Animation idleDownRightAnim;


	//WALK

	Animation rightWalkAnim;
	Animation leftWalkAnim;
	Animation downWalkAnim;
	Animation upWalkAnim;

	Animation rightDownWalkAnim;
	Animation leftDownWalkAnim;
	Animation rightUpWalkAnim;
	Animation leftUpWalkAnim;


	//RUN

	Animation rightRunAnim; // Las animaciones de Run son las mismas que las del walk pero se le cambia la velocidad del pushBack()
	Animation leftRunAnim;
	Animation downRunAnim;
	Animation upRunAnim;

	Animation rightDownRunAnim;
	Animation leftDownRunAnim;
	Animation rightUpRunAnim;
	Animation leftUpRunAnim;


	//ATTACK

	Animation rightAttackAnim;
	Animation leftAttackAnim;
	Animation downAttackAnim;
	Animation upAttackAnim;

	Animation rightDownAttackAnim;
	Animation leftDownAttackAnim;
	Animation rightUpAttackAnim;
	Animation leftUpAttackAnim;


	//RECHARGE

	Animation rightRechargeAnim;
	Animation leftRechargeAnim;
	Animation downRechargeAnim;
	Animation upRechargeAnim;

	Animation rightDownRechargeAnim;
	Animation leftDownRechargeAnim;
	Animation rightUpRechargeAnim;
	Animation leftUpRechargeAnim;


	//MELE ATTACK

	Animation rightMeleAttackAnim;
	Animation leftMeleAttackAnim;
	Animation downMeleAttackAnim;
	Animation upMeleAttackAnim;

	Animation rightDownMeleAttackAnim;
	Animation leftMeleDownAttackAnim;
	Animation rightUpMeleAttackAnim;
	Animation leftUpMeleAttackAnim;


	//DIE 

	Animation die;

	// BATTLE WIN

	Animation battleWin;

	

	// Sound effects indices
	uint dead = 0;
	uint damaged = 0;
	uint paused = 0;
	uint gameOverfx = 0;
	uint itemGrab = 0;
	uint shoot = 0;
	uint gameOver = 0;

	uint computerOn = 0;
	uint computerOff = 0;
	uint computerClick = 0;
	uint harborUnlockFx = 0;

	uint explosionFx_far = 0;
	uint alarmCardReaderFx = 0;
	uint alarmSwitch1Fx = 0;
	uint alarmSwitch2Fx = 0;
	uint alarmSwitch3Fx = 0;
	uint alarmSwitch4Fx = 0;
	uint alarmSwitch5Fx = 0;
	uint switchOkFx = 0;
	uint decodeButtonFx = 0;

	// The player's colliders
	Collider* collider = nullptr;

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

	//Low Health Effects

	int lowHPdelay = 0;

	//Margin of movement
	int horizontalMargin = 45;

	//Collision bools
	bool plantCollision;

	//Pause Menu
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
	
	bool playerAttacked = false;
	//test for continue mechanic
	bool saved_game = false;

	int entranceID;
	bool exitActivated;

	//test for the dialog system
	bool npcClose = false;
	bool npc2Close = false;
	bool npc3Close = false;
	bool npc4Close = false;

	//turnos de combate para el player
	GameState entityStatePlayer;
	TurnState entityTurnPlayer;

	//Combat Menu for the Player
	bool showCombatHUD = false;
	bool meleeAttack = false;

	bool inBossBatle = false;

	//Escape Combat 
	bool escapeCombat = false;
	int escapeCombatCounterToReset = 0;

	// Reading/watching notes or videos
	bool readingNote = false;
	bool usingComputer = false;
	bool usingSwitch = false;
	bool usingCardReader = false;

	bool harborUnlock = false;
	bool baseUnlock = false;
	bool rock1Removed = false;
	bool rock2Removed = false;
	int switchesPressed = 0;
	bool switch1Ok = false;
	bool switch2Ok = false;
	bool switch3Ok = false;
	bool switch4Ok = false;
	bool switch5Ok = false;

	//FX
	int walkSoundID = 0;
	/*int computerButtonsFX = 0;*/
	uint heartbeatFX = 0;
	uint playerHurtSound = 0;
	uint playerWalkSound[7] = { 0 };

};

#endif //!__MODULE_PLAYER_H__