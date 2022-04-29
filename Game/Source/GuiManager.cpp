#include "GuiManager.h"
#include "App.h"
#include "Textures.h"

#include "GuiButton.h"
#include "GuiCheckbox.h"
#include "GuiSlider.h"
#include "Audio.h"
#include "Log.h"

GuiManager::GuiManager(bool start_enabled) : Module(start_enabled)
{
	name.Create("guiManager");
}

GuiManager::~GuiManager() {}

bool GuiManager::Start()
{
	arrowPointer = app->tex->Load("Assets/textures/GUI/customCursor.png");
	app->input->GetMousePosition(app->input->arrowPointerPosition.x, app->input->arrowPointerPosition.y);

	return true;
}

GuiControl* GuiManager::CreateGuiControl(GuiControlType type, int id, const char* text, SDL_Rect bounds, Module* observer,SDL_Texture* texture,SDL_Texture* sliderTexture, SDL_Rect sliderBounds)
{
	// L14: TODO1_D: Create a GUI control and add it to the list of controls

	GuiControl* control = nullptr;

	//Call the constructor according to the GuiControlType
	switch (type)
	{
	case GuiControlType::BUTTON:
		control = new GuiButton(id, bounds, text,texture);
		break;
	
	case GuiControlType::CHECKBOX:
		control = new GuiCheckbox(id, bounds, text);
		break;
	case GuiControlType::SLIDER:
		control = new GuiSlider(id, bounds, sliderBounds,texture,sliderTexture);
		break;
	default:
		break;
	}
	//Set the observer
	control->SetObserver(observer);

	// Created GuiControls are added to the list of controls
	if (control != nullptr) controls.add(control);
	return control;
}

bool GuiManager::Update(float dt)
{	

	accumulatedTime += dt;
	if (accumulatedTime >= updateMsCycle) doLogic = true;

	UpdateAll(dt,doLogic);

	if (doLogic == true)
	{
		accumulatedTime = 0.0f;
		doLogic = false;
	}

	return true;
}

bool GuiManager::PostUpdate()
{
	if (app->input->arrowPointerPosition.x < -app->render->camera.x / 10000) app->input->arrowPointerPosition.x = -app->render->camera.x / 10000;
	if (app->input->arrowPointerPosition.y < -app->render->camera.y / 10000) app->input->arrowPointerPosition.y = -app->render->camera.y / 10000;
	if (app->input->arrowPointerPosition.x > -app->render->camera.x / 10000 + app->render->camera.w/2 - 10) app->input->arrowPointerPosition.x = -app->render->camera.x / 10000 + app->render->camera.w/2 - 10;
	if (app->input->arrowPointerPosition.y > -app->render->camera.y / 10000 + app->render->camera.h/2 - 10) app->input->arrowPointerPosition.y = -app->render->camera.y / 10000 + app->render->camera.h/2 - 10;

	if (app->input->usingGamepadID[0] == false)
	{
		int mouseX, mouseY;
		app->input->GetMousePosition(mouseX, mouseY);

		app->render->DrawTexture(arrowPointer, mouseX - app->render->camera.x / 2, mouseY - app->render->camera.y / 2, NULL);
	}
	else if (app->input->usingGamepadID[0] == true)
	{
		app->render->DrawTexture(arrowPointer, app->input->arrowPointerPosition.x - app->render->camera.x / 2, app->input->arrowPointerPosition.y - app->render->camera.y / 2, NULL);
	}

	return true;
}

bool GuiManager::UpdateAll(float dt, bool doLogic) {

	if (doLogic) {

		ListItem<GuiControl*>* control = controls.start;

		while (control != nullptr)
		{
			control->data->Update(dt);
			control = control->next;
		}

	}
	return true; 

}

bool GuiManager::Draw() 
{

	ListItem<GuiControl*>* control = controls.start;
	
	while (control != nullptr)
	{
		control->data->Draw(app->render);
		control = control->next;
	}

	return true;

}
void GuiManager::DestroyGuiControl(int id)
{
	ListItem<GuiControl*>* control = controls.start;
	while (control != nullptr)
	{
		if (control->data->id == id)
		{
			controls.del(control);
		}
		control = control->next;
	}
	
}
bool GuiManager::CleanUp()
{
	ListItem<GuiControl*>* control = controls.start;

	while (control != nullptr)
	{
		RELEASE(control);
	}

	return true;
}



