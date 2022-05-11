#ifndef __GUICONTROL_H__
#define __GUICONTROL_H__

#include "Input.h"
#include "Render.h"
#include "Module.h"

#include "Point.h"
#include "SString.h"

#include "SDL/include/SDL.h"

enum class GuiControlType
{
	BUTTON,
	TOGGLE,
	CHECKBOX,
	SLIDER,
	SLIDERBAR,
	COMBOBOX,
	DROPDOWNBOX,
	INPUTBOX,
	VALUEBOX,
	SPINNER
};

enum class GuiControlState
{
	DISABLED,
	NORMAL,
	FOCUSED,
	PRESSED,
	SELECTED
};

class GuiControl
{
public:

	GuiControl(GuiControlType type, uint32 id) : type(type), id(id), state(GuiControlState::NORMAL) {}

	GuiControl(GuiControlType type, SDL_Rect bounds, const char* text) :type(type),state(GuiControlState::NORMAL),bounds(bounds),text(text)
	{
		color.r = 255; color.g = 255; color.b = 255;
		texture=nullptr;
	}
	/*
	GuiControl(GuiControlType type, SDL_Rect bounds, const char* text, SDL_Rect ExtraBounds) :type(type), state(GuiControlState::NORMAL), bounds(bounds),extraBounds(ExtraBounds)
	{
		
	}
	*/
	
	

	virtual bool Update(float dt)
	{
		return true;
	}

	virtual bool Draw(Render* render)
	{
		return true;
	}

	void SetTexture(SDL_Texture* tex)
	{
		texture = tex;
		
	}
	void SetSliderTexture(SDL_Texture* tex)
	{
		textureForSlider = tex;
		
	}

	void SetObserver(Module* module)
	{
		observer = module;
	}

	void NotifyObserver()
	{
		observer->OnGuiMouseClickEvent(this);
	}

public:

	bool SelectedForDrawing;
	uint32 id;
	GuiControlType type;
	GuiControlState state;

	SString text;           // Control text (if required)
	SDL_Rect bounds;        // Position and size
	SDL_Rect extraBounds;
	SDL_Color color;        // Tint color

	SDL_Texture* texture = nullptr;
	SDL_Texture* textureForSlider = nullptr;	// Texture atlas reference
	SDL_Rect section;       // Texture atlas base section

	//Font font;              // Text font

	int SliderLevel;

	Module* observer;        // Observer module (it should probably be an array/list)
};

#endif // __GUICONTROL_H__