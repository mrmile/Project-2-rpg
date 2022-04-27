#include "GuiButton.h"
#include "Render.h"
#include "App.h"
#include "Audio.h"
#include "TitleScreen.h"
#include "GuiManager.h"

#include <iostream>
using namespace std;

GuiButton::GuiButton(uint32 id, SDL_Rect bounds, const char* text,SDL_Texture* texture) : GuiControl(GuiControlType::BUTTON, id)
{
	this->bounds = bounds;
	this->text = text;
	this->texture = texture;
	canClick = true;
	drawBasic = false;
}

GuiButton::~GuiButton()
{

}

bool GuiButton::Update(float dt)
{
	if (state != GuiControlState::DISABLED)
	{
		if (app->input->usingGamepadID[0] == false)
		{
			int mouseX, mouseY;
			app->input->GetMousePosition(mouseX, mouseY);

			if ((mouseX > bounds.x && mouseX < (bounds.x + bounds.w)) &&
				(mouseY > bounds.y && mouseY < bounds.y + bounds.h))
			{
				state = GuiControlState::FOCUSED;

				if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_UP)
				{
					state = GuiControlState::PRESSED;
					//cout << "Pressed " << endl;
					NotifyObserver();
				}
				else if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_REPEAT)
				{
					state = GuiControlState::SELECTED;
					//cout << "Selected " << endl;
					//NotifyObserver();
				}

			}
			else
			{
				state = GuiControlState::NORMAL;
			}
		}
		else if (app->input->usingGamepadID[0] == true)
		{

			if ((app->input->arrowPointerPosition.x > bounds.x && app->input->arrowPointerPosition.x < (bounds.x + bounds.w)) &&
				(app->input->arrowPointerPosition.y > bounds.y && app->input->arrowPointerPosition.y < bounds.y + bounds.h))
			{
				state = GuiControlState::FOCUSED;
				
				if (app->input->keys[SDL_SCANCODE_Z] == KeyState::KEY_UP)
				{
					state = GuiControlState::PRESSED;
					//cout << "Pressed " << endl;
					NotifyObserver();
				}
				else if (app->input->keys[SDL_SCANCODE_Z] == KeyState::KEY_REPEAT)
				{
					state = GuiControlState::SELECTED;
					//cout << "Selected " << endl;
					//NotifyObserver();
				}

			}
			else
			{
				state = GuiControlState::NORMAL;
			}
		}

	}

	return true;
}

bool GuiButton::PostUpdate()
{
	return true;
}

bool GuiButton::Draw(Render* render)
{
	

	// Draw the right button depending on state
	switch (state)
	{

	case GuiControlState::DISABLED:
	{
		
			render->DrawTexture2(texture, bounds.x, bounds.y, NULL); //<--Usar esto
	} break;

	case GuiControlState::NORMAL:
	{
	
			render->DrawTexture2(texture, bounds.x, bounds.y, NULL); //<--Usar esto
	} break;

	//L14: TODO 4: Draw the button according the GuiControl State
	case GuiControlState::FOCUSED:
	{
	
			render->DrawTexture2(texture, bounds.x, bounds.y, NULL); //<--Usar esto
	} break;
	case GuiControlState::PRESSED:
	{
		
			render->DrawTexture2(texture, bounds.x, bounds.y, NULL); //<--Usar esto
	} break;

	/******/

	case GuiControlState::SELECTED:
	{
			render->DrawTexture2(texture, bounds.x, bounds.y, NULL); //<--Usar esto
	}break;
	default:
		break;
	}

	return false;
}