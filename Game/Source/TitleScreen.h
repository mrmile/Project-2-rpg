#ifndef __TITLE_SCREEN_H__
#define __TITLE_SCREEN_H__

#include "Module.h"
#include "GuiButton.h"
#include "GuiCheckbox.h"
#include "GuiSlider.h"

struct SDL_Texture;

class TitleScreen : public Module
{
public:

	TitleScreen(bool start_enabled = false);

	// Destructor
	virtual ~TitleScreen();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Define multiple Gui Event methods
	bool OnGuiMouseClickEvent(GuiControl* control);

	bool SaveState(pugi::xml_node&) const;
	bool CheckSave(pugi::xml_node&);
	bool CheckAudioSave(pugi::xml_node&);

	//void b2dOnCollision(PhysBody* bodyA, PhysBody* bodyB);


	int sceneTimer;
	int delay;
	int delayToCredits;
	int delayToContinue;
	bool transition=false;
	bool continueTransition=false;
	bool credits = false;
	

	bool GameHasContinued = false;

	int buttonClickedFx = 0;
	int buttonNotClickedFx = 0;

	bool titleScreenWait = true;
	bool SavedGame;

	bool Vsync = false;
	bool FullScreen = false;
public:

	bool MainMenu = true;
	bool toTitleScreen = false;
	bool OptionsMenu = false;

	SDL_Texture* titleScreen = nullptr;
	SDL_Texture* titleScreenLetters = nullptr;
	SDL_Texture* settingsLetters = nullptr;
	SDL_Texture* creditsScene = nullptr;
	SDL_Texture* loading = nullptr;
	//BUTTONS TEXTURES
	SDL_Texture* newGameButton = nullptr;
	SDL_Texture* continueButton = nullptr;
	SDL_Texture* continueButtonOff = nullptr;
	SDL_Texture* optionsButton = nullptr;
	SDL_Texture* creditsButton = nullptr;
	SDL_Texture* returnButton = nullptr;
	SDL_Texture* exitButton = nullptr;

	SDL_Texture* newGameButtonOnIdle = nullptr;
	SDL_Texture* continueButtonOnIdle = nullptr;
	SDL_Texture* continueButtonOffOnIdle = nullptr;
	SDL_Texture* optionsButtonOnIdle = nullptr;
	SDL_Texture* creditsButtonOnIdle = nullptr;
	SDL_Texture* returnButtonOnIdle = nullptr;
	SDL_Texture* exitButtonOnIdle = nullptr;

	SDL_Texture* newGameButtonPressed = nullptr;
	SDL_Texture* continueButtonPressed = nullptr;
	SDL_Texture* continueButtonOffPressed = nullptr;
	SDL_Texture* optionsButtonPressed = nullptr;
	SDL_Texture* creditsButtonPressed = nullptr;
	SDL_Texture* returnButtonPressed = nullptr;
	SDL_Texture* exitButtonPressed = nullptr;
	//CHECBOX TEXTURES
	SDL_Texture* fullScreenCheckOn = nullptr;
	SDL_Texture* fullScreenCheckOff = nullptr;
	SDL_Texture* fullScreenTag = nullptr;
	SDL_Texture* VSyncOn = nullptr;
	SDL_Texture* VSyncOff = nullptr;

	SDL_Texture* fullScreenCheckOnOnIdle = nullptr;
	SDL_Texture* fullScreenCheckOffOnIdle = nullptr;
	SDL_Texture* VSyncOnOnIdle = nullptr;
	SDL_Texture* VSyncOffOnIdle = nullptr;

	SDL_Texture* fullScreenCheckOnPressed = nullptr;
	SDL_Texture* fullScreenCheckOffPressed = nullptr;
	SDL_Texture* VSyncOnPressed = nullptr;
	SDL_Texture* VSyncOffPressed = nullptr;
	//SLIDER TEXTURES
	SDL_Texture* baseSlider_fx = nullptr;
	SDL_Texture* baseSlider_music = nullptr;
	SDL_Texture* sliderSelector = nullptr;

	SDL_Texture* sliderSelectorOnIdle = nullptr;

	SDL_Texture* sliderSelectorPressed = nullptr;

	//GUI BUTTONS
	GuiButton* newGameButton_;
	GuiButton* continueButton_;
	GuiButton* optionsButton_;
	GuiButton* creditsButton_;
	GuiButton* returnButton_;
	GuiButton* exitButton_;
	//GUI CHECKBOX
	GuiCheckbox* fullScreenCheck_tag_;
	GuiCheckbox* fullScreenCheck_;
	GuiCheckbox* VSyncCheck;
	GuiCheckbox* VSyncCheck_tag_;

	//GUI SLIDER
	GuiSlider* musicVolumeSlider;
	GuiSlider* fxVolumeSlider;
};

#endif // __TITLE_SCREEN_H__