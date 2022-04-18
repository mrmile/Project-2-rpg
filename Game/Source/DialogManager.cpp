#include "DialogManager.h"
#include "App.h"
#include "SceneMainMap.h"
#include "Window.h"
#include "Render.h"
#include "GuiManager.h"
#include "ModuleFonts.h"
#include "ModulePlayer.h"
#include "Textures.h"
#include "GuiManager.h"
#include "Audio.h"

DialogManager::DialogManager(bool startEnabled):Module(startEnabled)
{
	name.Create("DialogManager");

}

DialogManager::~DialogManager()
{
	
}

bool DialogManager::Awake(pugi::xml_node&)
{


	return true;
}

bool DialogManager::Start()
{
	textRectanlgeNPC = app->tex->Load("Assets/textures/GUI/textButtonNPC.png");
	textRectanlgePlayer = app->tex->Load("Assets/textures/GUI/textButtonPlayer.png");
	textNameNPC = app->tex->Load("Assets/textures/GUI/textNameNPC.png");
	textNamePlayer = app->tex->Load("Assets/textures/GUI/textNamePlayer.png");
	textOptionUnselected = app->tex->Load("Assets/textures/GUI/optionUnselected.png");
	textOption1 = app->tex->Load("Assets/textures/GUI/option1.png");
	textOption2 = app->tex->Load("Assets/textures/GUI/option1.png");

	buttonClickedFx = app->audio->LoadFx("Assets/audio/fx/buttonClickedFX.wav");

	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	scoreFont = app->fonts->Load("Assets/textures/Fonts/rtype_font3.png", lookupTable, 2);

	GUItextRectanlgeNPC = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 22, "Text Button", { 0,0,100,100 }, this, textRectanlgeNPC, NULL, {});
	GUItextOption1 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 23, "Option Button", { 470,240,108,35 }, this, textOption1, NULL, {});
	GUItextOption2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 24, "Option Button", { 470,285,108,35 }, this, textOption2, NULL, {});

	return true;
}

bool DialogManager::Update(float dt)
{
	if (app->player->npcClose == true && dialoguePhase == 0)
	{
		GUItextRectanlgeNPC->canClick = true;
		GUItextOption1->canClick = true;
		GUItextOption2->canClick = true;
	}

	if (app->player->npcClose == false && dialoguePhase == 0)
	{
		GUItextRectanlgeNPC->canClick = false;
		GUItextOption1->canClick = true;
		GUItextOption2->canClick = true;
	}

	if (app->player->npc2Close == true && dialoguePhase == 0)
	{
		GUItextRectanlgeNPC->canClick = true;
		GUItextOption1->canClick = true;
		GUItextOption2->canClick = true;
	}

	if (app->player->npc2Close == false && dialoguePhase == 0)
	{
		GUItextRectanlgeNPC->canClick = false;
		GUItextOption1->canClick = true;
		GUItextOption2->canClick = true;
	}

	if (app->player->npc3Close == true && dialoguePhase == 0)
	{
		GUItextRectanlgeNPC->canClick = true;
		GUItextOption1->canClick = true;
		GUItextOption2->canClick = true;
	}

	if (app->player->npc3Close == false && dialoguePhase == 0)
	{
		GUItextRectanlgeNPC->canClick = false;
		GUItextOption1->canClick = true;
		GUItextOption2->canClick = true;
	}


	return true;
}

bool DialogManager::PostUpdate()
{

	if (app->player->pauseMenu == false)
	{

		if (app->player->npcClose == true)
		{
			/*app->render->DrawTexture2(textRectanlgePlayer, 0, 0, NULL);*/
			/*app->fonts->BlitText(app->player->position.x, app->player->position.y, scoreFont, "this is just a font test");*/
			if (GUItextRectanlgeNPC->state == GuiControlState::NORMAL && GUItextRectanlgeNPC->canClick == true) GUItextRectanlgeNPC->SetTexture(textRectanlgeNPC);
			GUItextRectanlgeNPC->Draw(app->render);

			//if (GUItextOption1->state == GuiControlState::NORMAL && GUItextOption1->canClick == true) GUItextOption1->SetTexture(textOptionUnselected);
			//if (GUItextOption1->state == GuiControlState::FOCUSED && GUItextOption1->canClick == true) GUItextOption1->SetTexture(textOption1);
			//GUItextOption1->Draw(app->render);

			//if (GUItextOption2->state == GuiControlState::NORMAL && GUItextOption2->canClick == true) GUItextOption2->SetTexture(textOptionUnselected);
			//if (GUItextOption2->state == GuiControlState::FOCUSED && GUItextOption2->canClick == true) GUItextOption2->SetTexture(textOption2);
			//GUItextOption2->Draw(app->render);

			if (dialoguePhase == 0)
			{
				app->render->DrawTexture2(textRectanlgePlayer, 0, 0, NULL);
				app->render->DrawTexture2(textNameNPC, 0, 0, NULL);

				app->fonts->BlitText(80, 250, scoreFont, "first dialog test, you have two options");
				app->fonts->BlitText(80, 270, scoreFont, "and you can do it two times");
				/*app->fonts->BlitText(80, 290, scoreFont, "first dialog test, you have two options");*/

				app->fonts->BlitText(493, 253, scoreFont, "select 1");
				app->fonts->BlitText(493, 300, scoreFont, "select 2");

				if (GUItextOption1->state == GuiControlState::NORMAL && GUItextOption1->canClick == true) GUItextOption1->SetTexture(textOptionUnselected);
				if (GUItextOption1->state == GuiControlState::FOCUSED && GUItextOption1->canClick == true) GUItextOption1->SetTexture(textOption1);
				GUItextOption1->Draw(app->render);

				if (GUItextOption2->state == GuiControlState::NORMAL && GUItextOption2->canClick == true) GUItextOption2->SetTexture(textOptionUnselected);
				if (GUItextOption2->state == GuiControlState::FOCUSED && GUItextOption2->canClick == true) GUItextOption2->SetTexture(textOption2);
				GUItextOption2->Draw(app->render);
			}

			if (dialoguePhase == 1 && option1Selected == true && nodeCounter == 1)
			{
				app->render->DrawTexture2(textRectanlgePlayer, 0, 0, NULL);
				app->render->DrawTexture2(textNamePlayer, 0, 0, NULL);
				app->fonts->BlitText(80, 260, scoreFont, "option 1 is selected, first test");
				app->fonts->BlitText(80, 280, scoreFont, "but i can chose again");

				app->fonts->BlitText(493, 253, scoreFont, "select 1");
				app->fonts->BlitText(493, 300, scoreFont, "select 2");

				if (GUItextOption1->state == GuiControlState::NORMAL && GUItextOption1->canClick == true) GUItextOption1->SetTexture(textOptionUnselected);
				if (GUItextOption1->state == GuiControlState::FOCUSED && GUItextOption1->canClick == true) GUItextOption1->SetTexture(textOption1);
				GUItextOption1->Draw(app->render);

				if (GUItextOption2->state == GuiControlState::NORMAL && GUItextOption2->canClick == true) GUItextOption2->SetTexture(textOptionUnselected);
				if (GUItextOption2->state == GuiControlState::FOCUSED && GUItextOption2->canClick == true) GUItextOption2->SetTexture(textOption2);
				GUItextOption2->Draw(app->render);
			}

			if (dialoguePhase == 1 && option2Selected == true && nodeCounter == 1)
			{
				app->render->DrawTexture2(textRectanlgePlayer, 0, 0, NULL);
				app->render->DrawTexture2(textNamePlayer, 0, 0, NULL);
				app->fonts->BlitText(80, 260, scoreFont, "option 2 is selected, first test");
				app->fonts->BlitText(80, 280, scoreFont, "but i can chose again");

				app->fonts->BlitText(493, 253, scoreFont, "select 1");
				app->fonts->BlitText(493, 300, scoreFont, "select 2");

				if (GUItextOption1->state == GuiControlState::NORMAL && GUItextOption1->canClick == true) GUItextOption1->SetTexture(textOptionUnselected);
				if (GUItextOption1->state == GuiControlState::FOCUSED && GUItextOption1->canClick == true) GUItextOption1->SetTexture(textOption1);
				GUItextOption1->Draw(app->render);

				if (GUItextOption2->state == GuiControlState::NORMAL && GUItextOption2->canClick == true) GUItextOption2->SetTexture(textOptionUnselected);
				if (GUItextOption2->state == GuiControlState::FOCUSED && GUItextOption2->canClick == true) GUItextOption2->SetTexture(textOption2);
				GUItextOption2->Draw(app->render);
			}

			if (dialoguePhase == 2 && option1Selected == true && nodeCounter == 2)
			{
				app->render->DrawTexture2(textNameNPC, 0, 0, NULL);
				app->fonts->BlitText(80, 260, scoreFont, "option 1 is selected, first test");
				app->fonts->BlitText(80, 280, scoreFont, "chosen in the second try");
			}

			if (dialoguePhase == 2 && option2Selected == true && nodeCounter == 2)
			{
				app->render->DrawTexture2(textNameNPC, 0, 0, NULL);
				app->fonts->BlitText(80, 260, scoreFont, "option 2 is selected, first test");
				app->fonts->BlitText(80, 280, scoreFont, "chosen in the second try");
			}
		}

		if (app->player->npc2Close == true)
		{
			/*app->render->DrawTexture2(textRectanlgePlayer, 0, 0, NULL);*/
			/*app->fonts->BlitText(app->player->position.x, app->player->position.y, scoreFont, "this is just a font test");*/
			if (GUItextRectanlgeNPC->state == GuiControlState::NORMAL && GUItextRectanlgeNPC->canClick == true) GUItextRectanlgeNPC->SetTexture(textRectanlgeNPC);
			GUItextRectanlgeNPC->Draw(app->render);

			//if (GUItextOption1->state == GuiControlState::NORMAL && GUItextOption1->canClick == true) GUItextOption1->SetTexture(textOptionUnselected);
			//if (GUItextOption1->state == GuiControlState::FOCUSED && GUItextOption1->canClick == true) GUItextOption1->SetTexture(textOption1);
			//GUItextOption1->Draw(app->render);

			//if (GUItextOption2->state == GuiControlState::NORMAL && GUItextOption2->canClick == true) GUItextOption2->SetTexture(textOptionUnselected);
			//if (GUItextOption2->state == GuiControlState::FOCUSED && GUItextOption2->canClick == true) GUItextOption2->SetTexture(textOption2);
			//GUItextOption2->Draw(app->render);

			if (dialoguePhase == 0)
			{
				app->render->DrawTexture2(textRectanlgePlayer, 0, 0, NULL);
				app->render->DrawTexture2(textNameNPC, 0, 0, NULL);

				app->fonts->BlitText(80, 250, scoreFont, "second dialog test, you have two options");
				app->fonts->BlitText(80, 270, scoreFont, "second dialog test, you have two options");
				app->fonts->BlitText(80, 290, scoreFont, "second dialog test, you have two options");
				app->fonts->BlitText(493, 253, scoreFont, "select 1");
				app->fonts->BlitText(493, 300, scoreFont, "select 2");

				if (GUItextOption1->state == GuiControlState::NORMAL && GUItextOption1->canClick == true) GUItextOption1->SetTexture(textOptionUnselected);
				if (GUItextOption1->state == GuiControlState::FOCUSED && GUItextOption1->canClick == true) GUItextOption1->SetTexture(textOption1);
				GUItextOption1->Draw(app->render);

				if (GUItextOption2->state == GuiControlState::NORMAL && GUItextOption2->canClick == true) GUItextOption2->SetTexture(textOptionUnselected);
				if (GUItextOption2->state == GuiControlState::FOCUSED && GUItextOption2->canClick == true) GUItextOption2->SetTexture(textOption2);
				GUItextOption2->Draw(app->render);
			}

			if (dialoguePhase == 2 && option1Selected == true)
			{
				app->render->DrawTexture2(textNamePlayer, 0, 0, NULL);
				app->fonts->BlitText(80, 260, scoreFont, "option 1 is selected, second test");
			}

			if (dialoguePhase == 2 && option2Selected == true)
			{
				app->render->DrawTexture2(textNamePlayer, 0, 0, NULL);
				app->fonts->BlitText(80, 260, scoreFont, "option 2 is selected, second test");
			}
		}

		if (app->player->npc3Close == true)
		{
			/*app->render->DrawTexture2(textRectanlgePlayer, 0, 0, NULL);*/
			/*app->fonts->BlitText(app->player->position.x, app->player->position.y, scoreFont, "this is just a font test");*/
			if (GUItextRectanlgeNPC->state == GuiControlState::NORMAL && GUItextRectanlgeNPC->canClick == true) GUItextRectanlgeNPC->SetTexture(textRectanlgeNPC);
			GUItextRectanlgeNPC->Draw(app->render);

			//if (GUItextOption1->state == GuiControlState::NORMAL && GUItextOption1->canClick == true) GUItextOption1->SetTexture(textOptionUnselected);
			//if (GUItextOption1->state == GuiControlState::FOCUSED && GUItextOption1->canClick == true) GUItextOption1->SetTexture(textOption1);
			//GUItextOption1->Draw(app->render);

			//if (GUItextOption2->state == GuiControlState::NORMAL && GUItextOption2->canClick == true) GUItextOption2->SetTexture(textOptionUnselected);
			//if (GUItextOption2->state == GuiControlState::FOCUSED && GUItextOption2->canClick == true) GUItextOption2->SetTexture(textOption2);
			//GUItextOption2->Draw(app->render);

			if (dialoguePhase == 0)
			{
				app->render->DrawTexture2(textRectanlgePlayer, 0, 0, NULL);
				app->render->DrawTexture2(textNameNPC, 0, 0, NULL);

				app->fonts->BlitText(80, 250, scoreFont, "third dialog test, you have two options");
				app->fonts->BlitText(80, 270, scoreFont, "third dialog test, you have two options");
				app->fonts->BlitText(80, 290, scoreFont, "third dialog test, you have two options");
				app->fonts->BlitText(493, 253, scoreFont, "select 1");
				app->fonts->BlitText(493, 300, scoreFont, "select 2");

				if (GUItextOption1->state == GuiControlState::NORMAL && GUItextOption1->canClick == true) GUItextOption1->SetTexture(textOptionUnselected);
				if (GUItextOption1->state == GuiControlState::FOCUSED && GUItextOption1->canClick == true) GUItextOption1->SetTexture(textOption1);
				GUItextOption1->Draw(app->render);

				if (GUItextOption2->state == GuiControlState::NORMAL && GUItextOption2->canClick == true) GUItextOption2->SetTexture(textOptionUnselected);
				if (GUItextOption2->state == GuiControlState::FOCUSED && GUItextOption2->canClick == true) GUItextOption2->SetTexture(textOption2);
				GUItextOption2->Draw(app->render);
			}

			if (dialoguePhase == 3 && option1Selected == true)
			{
				app->render->DrawTexture2(textNamePlayer, 0, 0, NULL);
				app->fonts->BlitText(80, 260, scoreFont, "option 1 is selected, third test");
			}

			if (dialoguePhase == 3 && option2Selected == true)
			{
				app->render->DrawTexture2(textNamePlayer, 0, 0, NULL);
				app->fonts->BlitText(80, 260, scoreFont, "option 2 is selected, third test");
			}
		}

		if (app->player->npcClose == false && app->player->npc2Close == false && app->player->npc3Close == false)
		{
			dialoguePhase = 0;
			option1Selected = false;
			option2Selected = false;
			nodeCounter = 0;
		}
		/*if (nodeCounter == 2 && option1Selected == true)
		{
			option1Selected = false;

			nodeCounter = 3;
			option1Selected = true;
		}
		if (nodeCounter == 2 && option2Selected == true)
		{
			option2Selected = false;

			nodeCounter = 3;
			option2Selected = true;
		}*/
		/*if (app->player->npc2Close == false)
		{
			dialoguePhase = 0;
		}
		if (app->player->npc3Close == false)
		{
			dialoguePhase = 0;
		}*/
	}
	
	//button->Draw(app->render);
	
	return true;
}

bool DialogManager::CleanUp()
{
	app->tex->UnLoad(textRectanlgeNPC);
	app->tex->UnLoad(textRectanlgePlayer);
	app->tex->UnLoad(textOptionUnselected);
	app->tex->UnLoad(textNameNPC);
	app->tex->UnLoad(textNamePlayer);
	app->tex->UnLoad(textOption1);
	app->tex->UnLoad(textOption2);

	app->guiManager->DestroyGuiControl(22);
	app->guiManager->DestroyGuiControl(23);
	app->guiManager->DestroyGuiControl(24);

	return true;
}

bool DialogManager::OnGuiMouseClickEvent(GuiControl* control) {
	switch (control->type)
	{
	case GuiControlType::BUTTON:
	{
		//Checks the GUI element ID
		if (control->id == 22 && GUItextRectanlgeNPC->canClick == true)
		{
			app->audio->PlayFx(buttonClickedFx, 0);
		}
		if (control->id == 23 && GUItextOption1->canClick == true)
		{
			if (app->player->npcClose == true)
			{
				app->audio->PlayFx(buttonClickedFx, 0);
				dialoguePhase++;
				option1Selected = true;
				nodeCounter++;
			}
			if (app->player->npc2Close == true)
			{
				app->audio->PlayFx(buttonClickedFx, 0);
				dialoguePhase = 2;
				option1Selected = true;
			}
			if (app->player->npc3Close == true)
			{
				app->audio->PlayFx(buttonClickedFx, 0);
				dialoguePhase = 3;
				option1Selected = true;
			}
		}
		if (control->id == 24 && GUItextOption1->canClick == true)
		{
			if (app->player->npcClose == true)
			{
				app->audio->PlayFx(buttonClickedFx, 0);
				dialoguePhase++;
				option2Selected = true;
				nodeCounter++;
			}
			if (app->player->npc2Close == true)
			{
				app->audio->PlayFx(buttonClickedFx, 0);
				dialoguePhase = 2;
				option2Selected = true;
			}
			if (app->player->npc3Close == true)
			{
				app->audio->PlayFx(buttonClickedFx, 0);
				dialoguePhase = 3;
				option2Selected = true;
			}
		}


	default: break;
	}
	}

	return true;
}
