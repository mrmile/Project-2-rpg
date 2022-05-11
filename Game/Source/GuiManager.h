#ifndef __GUIMANAGER_H__
#define __GUIMANAGER_H__

#include "Module.h"
#include "GuiControl.h"
#include "Input.h"

#include "List.h"

class GuiManager : public Module
{
public:

	// Constructor
	GuiManager(bool start_enabled = true);

	// Destructor
	virtual ~GuiManager();

	// Called before the first frame
	 bool Start();

	 bool Update(float dt);

	 bool PostUpdate();

	bool UpdateAll(float dt,bool logic);

	bool Draw();

	// Called before quitting
	bool CleanUp();

	// Additional methods
	GuiControl* CreateGuiControl(GuiControlType type, int id, const char* text, SDL_Rect bounds, Module* observer, SDL_Texture* texture,SDL_Texture* sliderTexture,SDL_Rect sliderBounds);
	void DestroyGuiControl(int id);
	void AddGuiControl(GuiControl* entity);

public:

	List<GuiControl*> controls;

	float accumulatedTime = 0.0f;
	float updateMsCycle = 0.0f;
	bool doLogic = false;

	SDL_Texture* texture = nullptr;

	SDL_Texture* arrowPointer = nullptr;

};

#endif // __GUIMANAGER_H__
