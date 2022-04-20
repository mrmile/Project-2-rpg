#include "GuiCheckbox.h"
#include "Render.h"
#include "App.h"
#include "Audio.h"

GuiCheckbox::GuiCheckbox(uint32 id, SDL_Rect bounds, const char* text) : GuiControl(GuiControlType::BUTTON, id)
{
	this->bounds = bounds;
	this->text = text;

	canClick = true;
	drawBasic = false;

}

GuiCheckbox::~GuiCheckbox()
{

}

bool GuiCheckbox::Update(float dt)
{
	if (state != GuiControlState::DISABLED)
	{
		// L14: TODO 3_D: Update the state of the GUiButton according to the mouse position
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
			else
			{
				state = GuiControlState::NORMAL;
			}
		}

	}

	return true;
}

bool GuiCheckbox::PostUpdate()
{
	return true;
}

bool GuiCheckbox::Draw(Render* render)
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