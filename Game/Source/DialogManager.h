#ifndef __DIALOG_MANAGER_H__
#define __DIALOG_MANAGER_H__

#pragma once
#include "Module.h"
#include "GuiControl.h"
#include "GuiButton.h"

class DialogManager : public Module
{
public:
	DialogManager(bool startEnabled);
	~DialogManager();

	bool Awake(pugi::xml_node&);
	bool Start();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

	bool OnGuiMouseClickEvent(GuiControl* control);

	int buttonClickedFx = 0;

	/*bool SetActiveDialog(Dialog* dialog);*/
	/*bool OnGuiMouseClickEvent(GuiControl* control);*/

private:

	SDL_Texture* textButton;
	SDL_Texture* textRectanlgeNPC;
	SDL_Texture* textRectanlgePlayer;
	SDL_Texture* textOption1;
	SDL_Texture* textOption2;
	SDL_Texture* textOptionUnselected;
	
	GuiButton* GUItextButton;
	GuiButton* GUItextRectanlgeNPC;
	GuiButton* GUItextOption1;
	GuiButton* GUItextOption2;

public:

	int dialoguePhase = 0;
	bool option1Selected = false;
	bool option2Selected = false;
	int scoreFont = -1;
};

#endif // !__DIALOG_MANAGER_H__
