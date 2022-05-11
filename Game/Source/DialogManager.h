#ifndef __DIALOG_MANAGER_H__
#define __DIALOG_MANAGER_H__

#pragma once
#include "Module.h"
#include "GuiControl.h"
#include "GuiButton.h"

class DialogManager : public Module
{
public:
	DialogManager(bool startEnabled = true);
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

	SDL_Texture* textButton = nullptr;
	SDL_Texture* textRectanlgeNPC = nullptr;
	SDL_Texture* textRectanlgePlayer = nullptr;
	SDL_Texture* textNameNPC1 = nullptr;
	SDL_Texture* textNameNPC2 = nullptr;
	SDL_Texture* textNameNPC3 = nullptr;
	SDL_Texture* textNameNPC4 = nullptr;
	SDL_Texture* textNamePlayer = nullptr;
	SDL_Texture* textOption1 = nullptr;
	SDL_Texture* textOption2 = nullptr;
	SDL_Texture* textOptionUnselected = nullptr;
	
	GuiButton* GUItextButton = nullptr;
	GuiButton* GUItextRectanlgeNPC = nullptr;
	GuiButton* GUItextOption1 = nullptr;
	GuiButton* GUItextOption2 = nullptr;

public:

	int dialoguePhase = 0;
	bool option1Selected = false;
	bool option2Selected= false;
	bool option1SelectedSecondDialog = false;
	bool option2SelectedSecondDialog = false;
	int scoreFont = -1;
	int nodeCounter = 0;
};

#endif // !__DIALOG_MANAGER_H__
