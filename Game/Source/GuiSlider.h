#ifndef __GUISLIDER_H__
#define __GUISLIDER_H__

#include "GuiControl.h"

#include "Point.h"
#include "SString.h"

class GuiSlider : public GuiControl
{
public:

	GuiSlider(uint32 id, SDL_Rect bounds, SDL_Rect sliderBounds,SDL_Texture* texture,SDL_Texture* sliderTexture);
	virtual ~GuiSlider();

	bool Update(float dt);
	bool PostUpdate();
	bool Draw(Render* render);

	int mouseX, mouseY;
	unsigned int click;

	
	bool canClick = true;
	bool drawBasic = false;
};

#endif // __GUIBUTTON_H__