#ifndef __TRANSITIONS_H__
#define __TRANSITIONS_H__

#include "Module.h"
#include "Render.h"
#include "SDL/include/SDL_rect.h"

class Transitions : public Module
{
public:

	// Constructor
	Transitions(bool start_enabled = true);

	// Destructor
	virtual ~Transitions();

	// Called before the first frame

	bool Awake();

	bool Start();

	bool Update();

	bool PostUpdate();

	bool CleanUp();
	void SelectTransition(int id,int timer_in_transition, int timer_out_transition);
	//NEED TO CREATE MORE DRAWTRANSITIONS
	void DrawTransition1();
	void DrawTransition2();
	void DrawTransition3();
	void DrawTransition4();


public:

	enum Fade_Step
	{
		NONE,
		TRANSTITION,
		FROM_TRANSITION
	} currentStep = Fade_Step::NONE;

	int animationSelected;
	int timer_in_transition = 0;
	int timer_out_transition = 0;
	uint win_width;
	uint win_height;

	// The rectangles of the screen, used to render the animation
	
	SDL_Texture* combatFull;
	SDL_Texture* combat80;
	SDL_Texture* combat60;
	SDL_Texture* combat40;
	SDL_Texture* combat20;
};

#endif // __WINDOW_H__