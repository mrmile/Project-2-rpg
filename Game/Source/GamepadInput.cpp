#include "GamepadInput.h"
#include "ModulePlayer.h"
#include "SceneMainMap.h"

#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "ModuleParticles.h"
#include "Audio.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "Input.h"

#include <stdio.h>
#include <SDL\include\SDL_timer.h>
#include <SDL_mixer/include/SDL_mixer.h>
#include <SDL/include/SDL_gamecontroller.h>
#include <SDL/include/SDL_haptic.h>

GamepadInput::GamepadInput(bool startEnabled) : Module(startEnabled)
{

}

GamepadInput::~GamepadInput()
{

}

bool GamepadInput::Start()
{
	LOG("Loading Gamepad Module");

	bool ret = true;

	char lookupTable[] = { "0123456789" };
	scoreFont = app->fonts->Load("Assets/Art/UI/numbers_s.png", lookupTable, 1);

	keyDownDelay = 0;
	
	return ret;
}

bool GamepadInput::Update(float dt)
{
	// Get gamepad info
	GamePad& pad = app->input->pads[0];
	
	if (pad.left_x < 0.0f)
	{
		app->input->keys[SDL_SCANCODE_LEFT] = KeyState::KEY_REPEAT;
	}
	if (pad.left_x < 0.0f && keyDownDelay > 15)
	{
		app->input->keys[SDL_SCANCODE_LEFT] = KeyState::KEY_DOWN;

		keyDownDelay = 0;
	}

	if (pad.left_x > 0.0f)
	{
		app->input->keys[SDL_SCANCODE_RIGHT] = KeyState::KEY_REPEAT;
	}
	if (pad.left_x > 0.0f && keyDownDelay > 15)
	{
		app->input->keys[SDL_SCANCODE_RIGHT] = KeyState::KEY_DOWN;

		keyDownDelay = 0;
	}

	if (pad.left_y < 0.0f)
	{
		app->input->keys[SDL_SCANCODE_UP] = KeyState::KEY_REPEAT;
	}
	if (pad.left_y < 0.0f && keyDownDelay > 15)
	{
		app->input->keys[SDL_SCANCODE_UP] = KeyState::KEY_DOWN;

		keyDownDelay = 0;
	}

	if (pad.left_y > 0.0f)
	{
		app->input->keys[SDL_SCANCODE_DOWN] = KeyState::KEY_REPEAT;
	}
	if (pad.left_y > 0.0f && keyDownDelay > 15)
	{
		app->input->keys[SDL_SCANCODE_DOWN] = KeyState::KEY_DOWN;

		keyDownDelay = 0;
	}


	if (pad.right_x < 0.0f)
	{
		app->input->arrowPointerPosition.x -= 4;
	}

	if (pad.right_x > 0.0f)
	{
		app->input->arrowPointerPosition.x += 4;
	}

	if (pad.right_y < 0.0f)
	{
		app->input->arrowPointerPosition.y -= 4;
	}

	if (pad.right_y > 0.0f)
	{
		app->input->arrowPointerPosition.y += 4;
	}


	if (pad.l2 == true)
	{
		app->input->keys[SDL_SCANCODE_LSHIFT] = KeyState::KEY_REPEAT;
	}

	if (pad.x == true)
	{
		app->input->keys[SDL_SCANCODE_Z] = KeyState::KEY_REPEAT;
	}
	if (pad.x == true && keyDownDelay > 15)
	{
		app->input->keys[SDL_SCANCODE_Z] = KeyState::KEY_DOWN;

		keyDownDelay = 0;
	}

	if (pad.b == true && keyDownDelay > 15)
	{
		app->input->keys[SDL_SCANCODE_X] = KeyState::KEY_DOWN;

		keyDownDelay = 0;
	}

	if (pad.a == true && keyDownDelay > 15)
	{
		app->input->keys[SDL_SCANCODE_C] = KeyState::KEY_DOWN;

		keyDownDelay = 0;
	}

	if (pad.start == true && keyDownDelay > 15)
	{
		app->input->keys[SDL_SCANCODE_ESCAPE] = KeyState::KEY_DOWN;

		keyDownDelay = 0;
	}

	if (pad.back == true && keyDownDelay > 15)
	{
		//Open inventory KEY_DOWN

		keyDownDelay = 0;
	}

	keyDownDelay++;

	return true;
}

void GamepadInput::DebugDrawGamepadInfo()
{
	GamePad& pad = app->input->pads[0];

	sprintf_s(scoreText, 150, "pad 0 %s, press 1/2/3 for rumble", (pad.enabled) ? "plugged" : "not detected");
	app->fonts->BlitText(5, 10, scoreFont, scoreText);

	sprintf_s(scoreText, 150, "buttons %s %s %s %s %s %s %s %s %s %s %s",
		(pad.a) ? "a" : "",
		(pad.b) ? "b" : "",
		(pad.x) ? "x" : "",
		(pad.y) ? "y" : "",
		(pad.start) ? "start" : "",
		(pad.back) ? "back" : "",
		(pad.guide) ? "guide" : "",
		(pad.l1) ? "lb" : "",
		(pad.r1) ? "rb" : "",
		(pad.l3) ? "l3" : "",
		(pad.r3) ? "r3" : ""
	);
	app->fonts->BlitText(5, 20, scoreFont, scoreText);

	sprintf_s(scoreText, 150, "dpad %s %s %s %s",
		(pad.up) ? "up" : "",
		(pad.down) ? "down" : "",
		(pad.left) ? "left" : "",
		(pad.right) ? "right" : ""
	);
	app->fonts->BlitText(5, 30, scoreFont, scoreText);

	sprintf_s(scoreText, 150, "left trigger  %0.2f", pad.l2);
	app->fonts->BlitText(5, 40, scoreFont, scoreText);
	sprintf_s(scoreText, 150, "right trigger %0.2f", pad.r2);
	app->fonts->BlitText(5, 50, scoreFont, scoreText);

	sprintf_s(scoreText, 150, "left thumb    %.2fx, %0.2fy", pad.left_x, pad.left_y);
	app->fonts->BlitText(5, 60, scoreFont, scoreText);

	sprintf_s(scoreText, 150, "   deadzone   %0.2f", pad.left_dz);
	app->fonts->BlitText(5, 70, scoreFont, scoreText);

	sprintf_s(scoreText, 150, "right thumb   %.2fx, %0.2fy", pad.right_x, pad.right_y);
	app->fonts->BlitText(5, 80, scoreFont, scoreText);

	sprintf_s(scoreText, 150, "   deadzone   %0.2f", pad.right_dz);
	app->fonts->BlitText(5, 90, scoreFont, scoreText);
}