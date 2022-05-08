#ifndef __GAMEPAD_INPUT_H__
#define __GAMEPAD_INPUT_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"

struct SDL_Texture;
struct Collider;

class GamepadInput : public Module
{
public:
	// Constructor
	GamepadInput(bool start_enabled = true);

	// Destructor
	~GamepadInput();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start() override;

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	bool Update(float dt) override;

	bool PostUpdate();

	// Draws gamepad debug info in the screen
	void DebugDrawGamepadInfo();

public:

	// Font score index
	uint score = 000;
	int scoreFont = -1;
	char scoreText[10] = { "\0" };

	// Debugdraw for gamepad data
	bool debugGamepadInfo = false;

	uint32 keyDownDelay;

};

#endif //!__GAMEPADINPUT_H__
