#ifndef __PAUSE_MENU_H__
#define __PAUSE_MENU_H__

#include "Module.h"
#include "GuiButton.h"
#include "GuiCheckbox.h"
#include "GuiSlider.h"

struct SDL_Texture;

class PauseMenu : public Module
{
public:

	PauseMenu(bool start_enabled);

	// Destructor
	virtual ~PauseMenu();

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

	bool OnGuiMouseClickEvent(GuiControl* control);

	bool CheckAudioSave(pugi::xml_node&);

	int buttonClickedFx = 0;
	int sceneTimer;
	int pauseTimer;
	int noPauseTimer;
	bool options = false;
	bool TitleTransition = false;

private:


	SDL_Texture* PauseFrame;
	SDL_Texture* PauseTitle;
	SDL_Texture* settingsLetters;


	SDL_Texture* resumeButton;
	SDL_Texture* optionsButton;
	SDL_Texture* backToTitleButton;
	SDL_Texture* exitButton;
	SDL_Texture* returnButton;

	SDL_Texture* resumeButtonOnIdle;
	SDL_Texture* optionsButtonOnIdle;
	SDL_Texture* backToTitleButtonOnIdle;
	SDL_Texture* exitButtonOnIdle;
	SDL_Texture* returnButtonOnIdle;

	SDL_Texture* resumeButtonPressed;
	SDL_Texture* optionsButtonPressed;
	SDL_Texture* backToTitleButtonPressed;
	SDL_Texture* exitButtonPressed;
	SDL_Texture* returnButtonPressed;
	
	//CHECBOX TEXTURES
	SDL_Texture* fullScreenCheckOn;
	SDL_Texture* fullScreenCheckOff;
	SDL_Texture* fullScreenTag;
	SDL_Texture* VSyncOn;
	SDL_Texture* VSyncOff;

	SDL_Texture* fullScreenCheckOnOnIdle;
	SDL_Texture* fullScreenCheckOffOnIdle;
	SDL_Texture* VSyncOnOnIdle;
	SDL_Texture* VSyncOffOnIdle;

	SDL_Texture* fullScreenCheckOnPressed;
	SDL_Texture* fullScreenCheckOffPressed;
	SDL_Texture* VSyncOnPressed;
	SDL_Texture* VSyncOffPressed;
	//SLIDER TEXTURES
	SDL_Texture* baseSlider_fx;
	SDL_Texture* baseSlider_music;
	SDL_Texture* sliderSelector;

	//GUI BUTTONS
	GuiButton* resumeButton_;
	GuiButton* optionsButton_;
	GuiButton* backToTitleButton_;
	GuiButton* exitButton_;
	GuiButton* returnButton_;
	//GUI CHECKBOX
	GuiCheckbox* fullScreenCheck_tag_;
	GuiCheckbox* fullScreenCheck_;
	GuiCheckbox* VSyncCheck;
	GuiCheckbox* VSyncCheck_tag_;

	//GUI SLIDER
	GuiSlider* musicVolumeSlider;
	GuiSlider* fxVolumeSlider;
};

#endif // __SCENE_FOREST_H__