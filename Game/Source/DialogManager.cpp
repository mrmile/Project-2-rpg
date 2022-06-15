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
#include "ModuleUI.h"

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
	textNameNPC1 = app->tex->Load("Assets/textures/GUI/textNameNPC1.png");
	textNameNPC2 = app->tex->Load("Assets/textures/GUI/textNameNPC2.png");
	textNameNPC3 = app->tex->Load("Assets/textures/GUI/textNameNPC3.png");
	textNameNPC4 = app->tex->Load("Assets/textures/GUI/textNameNPC4.png");
	textNameFINAL_BOSS = app->tex->Load("Assets/textures/GUI/textNamePatientZero.png");
	textNamePlayer = app->tex->Load("Assets/textures/GUI/textNamePlayer.png");
	textOptionUnselected = app->tex->Load("Assets/textures/GUI/optionUnselected.png");
	textOption1 = app->tex->Load("Assets/textures/GUI/option1.png");
	textOption2 = app->tex->Load("Assets/textures/GUI/option1.png");
	tntExample = app->tex->Load("Assets/textures/GUI/tntExampleDialog.png");

	buttonClickedFx = app->audio->LoadFx("Assets/audio/fx/UISounds/buttonClickedFX.wav");

	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	scoreFont = app->fonts->Load("Assets/textures/Fonts/rtype_font3.png", lookupTable, 2);

	GUItextRectanlgeNPC = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 22, "Text Button", { 0,0,100,100 }, this, textRectanlgeNPC, NULL, {});
	GUItextOption1 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 23, "Option Button", { 470,240,108,35 }, this, textOption1, NULL, {});
	GUItextOption2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 24, "Option Button", { 470,285,108,35 }, this, textOption2, NULL, {});


	QTE_keys_pointerPositionX = 0;

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

	if (app->player->npc4Close == true && dialoguePhase == 0)
	{
		GUItextRectanlgeNPC->canClick = true;
		GUItextOption1->canClick = true;
		GUItextOption2->canClick = true;
	}

	if (app->player->npc4Close == false && dialoguePhase == 0)
	{
		GUItextRectanlgeNPC->canClick = false;
		GUItextOption1->canClick = true;
		GUItextOption2->canClick = true;
	}


	return true;
}

bool DialogManager::PostUpdate()
{

	if (app->player->pauseMenu == false && app->player->showCombatHUD == false)
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
				app->render->DrawTexture2(textNameNPC1, 0, 0, NULL);

				app->fonts->BlitText(80, 250, scoreFont, "waaaaaah, im scared!");
				app->fonts->BlitText(80, 270, scoreFont, "waaaaaaaaah");
				app->fonts->BlitText(80, 290, scoreFont, "waaaaaah, im scared!");
				/*app->fonts->BlitText(80, 290, scoreFont, "first dialog test, you have two options");*/

				app->fonts->BlitText(483, 253, scoreFont, "dont worry");
				app->fonts->BlitText(493, 300, scoreFont, "shhhhh");

				if (GUItextOption1->state == GuiControlState::NORMAL && GUItextOption1->canClick == true) GUItextOption1->SetTexture(textOptionUnselected);
				if (GUItextOption1->state == GuiControlState::FOCUSED && GUItextOption1->canClick == true) GUItextOption1->SetTexture(textOption1);
				GUItextOption1->Draw(app->render);

				if (GUItextOption2->state == GuiControlState::NORMAL && GUItextOption2->canClick == true) GUItextOption2->SetTexture(textOptionUnselected);
				if (GUItextOption2->state == GuiControlState::FOCUSED && GUItextOption2->canClick == true) GUItextOption2->SetTexture(textOption2);
				GUItextOption2->Draw(app->render);
			}

			if (dialoguePhase == 1 && option1Selected == true)
			{
				/*app->render->DrawTexture2(textRectanlgePlayer, 0, 0, NULL);*/
				app->render->DrawTexture2(textNameNPC1, 0, 0, NULL);

				app->fonts->BlitText(80, 250, scoreFont, "thanks sir!");
				/*app->fonts->BlitText(80, 270, scoreFont, "try but i can choose again")*/;

				/*app->fonts->BlitText(493, 253, scoreFont, "select 1");
				app->fonts->BlitText(493, 300, scoreFont, "select 2");

				if (GUItextOption1->state == GuiControlState::NORMAL && GUItextOption1->canClick == true) GUItextOption1->SetTexture(textOptionUnselected);
				if (GUItextOption1->state == GuiControlState::FOCUSED && GUItextOption1->canClick == true) GUItextOption1->SetTexture(textOption1);
				GUItextOption1->Draw(app->render);

				if (GUItextOption2->state == GuiControlState::NORMAL && GUItextOption2->canClick == true) GUItextOption2->SetTexture(textOptionUnselected);
				if (GUItextOption2->state == GuiControlState::FOCUSED && GUItextOption2->canClick == true) GUItextOption2->SetTexture(textOption2);
				GUItextOption2->Draw(app->render);*/
			}

			if (dialoguePhase == 1 && option2Selected == true)
			{
				/*app->render->DrawTexture2(textRectanlgePlayer, 0, 0, NULL);*/
				app->render->DrawTexture2(textNameNPC1, 0, 0, NULL);

				app->fonts->BlitText(80, 250, scoreFont, "waaaaaah");
				app->fonts->BlitText(80, 270, scoreFont, "waaaaaaaaah");
				app->fonts->BlitText(80, 290, scoreFont, "waaaaaah");

				/*app->fonts->BlitText(493, 253, scoreFont, "select 1");
				app->fonts->BlitText(493, 300, scoreFont, "select 2");

				if (GUItextOption1->state == GuiControlState::NORMAL && GUItextOption1->canClick == true) GUItextOption1->SetTexture(textOptionUnselected);
				if (GUItextOption1->state == GuiControlState::FOCUSED && GUItextOption1->canClick == true) GUItextOption1->SetTexture(textOption1);
				GUItextOption1->Draw(app->render);

				if (GUItextOption2->state == GuiControlState::NORMAL && GUItextOption2->canClick == true) GUItextOption2->SetTexture(textOptionUnselected);
				if (GUItextOption2->state == GuiControlState::FOCUSED && GUItextOption2->canClick == true) GUItextOption2->SetTexture(textOption2);
				GUItextOption2->Draw(app->render);*/
			}

			/*if (dialoguePhase == 2 && option1SelectedSecondDialog == true)
			{
				app->render->DrawTexture2(textNameNPC1, 0, 0, NULL);
				app->fonts->BlitText(80, 250, scoreFont, "you have selected the option number one");
				app->fonts->BlitText(80, 270, scoreFont, "for the second try");
			}

			if (dialoguePhase == 2 && option2SelectedSecondDialog == true)
			{
				app->render->DrawTexture2(textNameNPC1, 0, 0, NULL);
				app->fonts->BlitText(80, 250, scoreFont, "you have selected the option number two");
				app->fonts->BlitText(80, 270, scoreFont, "for the second try");
			}*/
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
				app->render->DrawTexture2(textNameNPC2, 0, 0, NULL);
				app->render->DrawTexture2(tntExample, -60, 275, NULL);

				app->fonts->BlitText(77, 240, scoreFont, "the exit is blocked, compadre...");
				app->fonts->BlitText(77, 260, scoreFont, "i remember there were a couple of tnt");
				app->fonts->BlitText(77, 280, scoreFont, "somewhere around. look and activate them.");
				app->fonts->BlitText(77, 300, scoreFont, "they may destroy these large rocks.");
				app->fonts->BlitText(473, 253, scoreFont, "okey, thanks");
				/*app->fonts->BlitText(493, 300, scoreFont, "axe");*/

				if (GUItextOption1->state == GuiControlState::NORMAL && GUItextOption1->canClick == true) GUItextOption1->SetTexture(textOptionUnselected);
				if (GUItextOption1->state == GuiControlState::FOCUSED && GUItextOption1->canClick == true) GUItextOption1->SetTexture(textOption1);
				GUItextOption1->Draw(app->render);

				/*if (GUItextOption2->state == GuiControlState::NORMAL && GUItextOption2->canClick == true) GUItextOption2->SetTexture(textOptionUnselected);
				if (GUItextOption2->state == GuiControlState::FOCUSED && GUItextOption2->canClick == true) GUItextOption2->SetTexture(textOption2);
				GUItextOption2->Draw(app->render);*/
			}

			if (dialoguePhase == 2 && option1Selected == true)
			{
				app->render->DrawTexture2(textNameNPC2, 0, 0, NULL);
				app->fonts->BlitText(80, 250, scoreFont, "buena suerte wey!");
			}

			/*if (dialoguePhase == 2 && option2Selected == true)
			{
				app->render->DrawTexture2(textNamePlayer, 0, 0, NULL);
				app->fonts->BlitText(80, 250, scoreFont, "i prefer to have an axe with me");
			}*/
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
				app->render->DrawTexture2(textNameNPC3, 0, 0, NULL);

				app->fonts->BlitText(77, 240, scoreFont, "night have fallen, be careful. zombies");
				app->fonts->BlitText(77, 260, scoreFont, "during nightime transform into very large");
				app->fonts->BlitText(77, 280, scoreFont, "monsters, i call them volatiles. if you");
				app->fonts->BlitText(77, 300, scoreFont, "got caught you will die instantly");

				app->fonts->BlitText(483, 253, scoreFont, "continue");
				app->fonts->BlitText(493, 300, scoreFont, "...");

				if (GUItextOption1->state == GuiControlState::NORMAL && GUItextOption1->canClick == true) GUItextOption1->SetTexture(textOptionUnselected);
				if (GUItextOption1->state == GuiControlState::FOCUSED && GUItextOption1->canClick == true) GUItextOption1->SetTexture(textOption1);
				GUItextOption1->Draw(app->render);

				if (GUItextOption2->state == GuiControlState::NORMAL && GUItextOption2->canClick == true) GUItextOption2->SetTexture(textOptionUnselected);
				if (GUItextOption2->state == GuiControlState::FOCUSED && GUItextOption2->canClick == true) GUItextOption2->SetTexture(textOption2);
				GUItextOption2->Draw(app->render);
			}

			if (dialoguePhase == 3 && option1Selected == true)
			{
				app->render->DrawTexture2(textNameNPC3, 0, 0, NULL);
				app->fonts->BlitText(80, 250, scoreFont, "i have explored the zone and its clean");
				app->fonts->BlitText(80, 270, scoreFont, "but if you make some noise they will");
				app->fonts->BlitText(80, 290, scoreFont, "all come to you so keep it quiet");
			}

			if (dialoguePhase == 3 && option2Selected == true)
			{
				app->render->DrawTexture2(textNameNPC3, 0, 0, NULL);
				app->fonts->BlitText(80, 250, scoreFont, "i have explored the zone and its clean");
				app->fonts->BlitText(80, 270, scoreFont, "but if you make some noise they will");
				app->fonts->BlitText(80, 290, scoreFont, "all come to you so keep it quiet");
			}
		}

		if (app->player->npc4Close == true)
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
				app->render->DrawTexture2(textNameNPC4, 0, 0, NULL);

				app->fonts->BlitText(77, 250, scoreFont, "once you get on the floating platform you");
				app->fonts->BlitText(77, 270, scoreFont, "wont be able to go back to this main zone");
				app->fonts->BlitText(77, 290, scoreFont, "are you sure you want to continue");
				/*app->fonts->BlitText(77, 300, scoreFont, "got caught you will die instantly");*/
				/*app->fonts->BlitText(80, 290, scoreFont, "first dialog test, you have two options");*/

				app->fonts->BlitText(493, 253, scoreFont, "yes");
				app->fonts->BlitText(493, 300, scoreFont, "no");

				if (GUItextOption1->state == GuiControlState::NORMAL && GUItextOption1->canClick == true) GUItextOption1->SetTexture(textOptionUnselected);
				if (GUItextOption1->state == GuiControlState::FOCUSED && GUItextOption1->canClick == true) GUItextOption1->SetTexture(textOption1);
				GUItextOption1->Draw(app->render);

				if (GUItextOption2->state == GuiControlState::NORMAL && GUItextOption2->canClick == true) GUItextOption2->SetTexture(textOptionUnselected);
				if (GUItextOption2->state == GuiControlState::FOCUSED && GUItextOption2->canClick == true) GUItextOption2->SetTexture(textOption2);
				GUItextOption2->Draw(app->render);
			}

			if (dialoguePhase == 1 && option1Selected == true)
			{
				/*app->render->DrawTexture2(textRectanlgePlayer, 0, 0, NULL);*/
				app->render->DrawTexture2(textNameNPC4, 0, 0, NULL);
				app->fonts->BlitText(80, 250, scoreFont, "good luck buddy!");

				/*app->fonts->BlitText(493, 253, scoreFont, "miami");
				app->fonts->BlitText(493, 300, scoreFont, "boston");

				if (GUItextOption1->state == GuiControlState::NORMAL && GUItextOption1->canClick == true) GUItextOption1->SetTexture(textOptionUnselected);
				if (GUItextOption1->state == GuiControlState::FOCUSED && GUItextOption1->canClick == true) GUItextOption1->SetTexture(textOption1);
				GUItextOption1->Draw(app->render);

				if (GUItextOption2->state == GuiControlState::NORMAL && GUItextOption2->canClick == true) GUItextOption2->SetTexture(textOptionUnselected);
				if (GUItextOption2->state == GuiControlState::FOCUSED && GUItextOption2->canClick == true) GUItextOption2->SetTexture(textOption2);
				GUItextOption2->Draw(app->render);*/
			}

			if (dialoguePhase == 1 && option2Selected == true)
			{
				/*app->render->DrawTexture2(textRectanlgePlayer, 0, 0, NULL);*/

				app->render->DrawTexture2(textNameNPC4, 0, 0, NULL);
				app->fonts->BlitText(80, 250, scoreFont, "i will guess you are still not ready");

				/*app->fonts->BlitText(493, 253, scoreFont, "miami");
				app->fonts->BlitText(493, 300, scoreFont, "boston");

				if (GUItextOption1->state == GuiControlState::NORMAL && GUItextOption1->canClick == true) GUItextOption1->SetTexture(textOptionUnselected);
				if (GUItextOption1->state == GuiControlState::FOCUSED && GUItextOption1->canClick == true) GUItextOption1->SetTexture(textOption1);
				GUItextOption1->Draw(app->render);

				if (GUItextOption2->state == GuiControlState::NORMAL && GUItextOption2->canClick == true) GUItextOption2->SetTexture(textOptionUnselected);
				if (GUItextOption2->state == GuiControlState::FOCUSED && GUItextOption2->canClick == true) GUItextOption2->SetTexture(textOption2);
				GUItextOption2->Draw(app->render);*/
			}

			/*if (dialoguePhase == 2 && option1SelectedSecondDialog == true)
			{
				app->render->DrawTexture2(textNameNPC4, 0, 0, NULL);
				app->fonts->BlitText(80, 250, scoreFont, "its a long and dangerous road the one");
				app->fonts->BlitText(80, 270, scoreFont, "to miami, you wont survive alone");
			}

			if (dialoguePhase == 2 && option2SelectedSecondDialog == true)
			{
				app->render->DrawTexture2(textNameNPC4, 0, 0, NULL);
				app->fonts->BlitText(80, 250, scoreFont, "i hope you are lying to me, boston");
				app->fonts->BlitText(80, 270, scoreFont, "is full of zombies its imposible to");
				app->fonts->BlitText(80, 290, scoreFont, "reach the city");
			}*/
		}

		if (app->player->activateFinalBoss == true)
		{
			app->player->finalBossPhaseCounter++;

			if ((app->player->finalBossPhaseCounter > 10 && app->player->finalBossPhaseCounter < 1860)
				|| (app->player->finalBossPhaseCounter > 4380 && app->player->finalBossPhaseCounter < 4980))
			{
				app->render->DrawTexture2(textRectanlgeNPC, 0, 0, NULL);
				app->render->DrawTexture2(textNameFINAL_BOSS, 0, 0, NULL);
			}

			if (app->player->finalBossPhaseCounter > 10 && app->player->finalBossPhaseCounter <= 660)
			{
				app->fonts->BlitText(77, 240, scoreFont, "well well, looks like you have found me.");
				app->fonts->BlitText(77, 260, scoreFont, "as you may imagine i am the patient zero.");
			}

			if (app->player->finalBossPhaseCounter > 660 && app->player->finalBossPhaseCounter <= 1260)
			{
				app->fonts->BlitText(77, 240, scoreFont, "its amazing you have made your way until");
				app->fonts->BlitText(77, 260, scoreFont, "here. i have to admit you have done a");
				app->fonts->BlitText(77, 280, scoreFont, "very good job.");
			}

			if (app->player->finalBossPhaseCounter > 1260 && app->player->finalBossPhaseCounter < 1860)
			{
				app->fonts->BlitText(77, 240, scoreFont, "but now i will kill you! you all have");
				app->fonts->BlitText(77, 260, scoreFont, "done lots of damage to me with the");
				app->fonts->BlitText(77, 280, scoreFont, "experiments.");
			}

			if (app->player->finalBossPhaseCounter > 4380 && app->player->finalBossPhaseCounter <= 4740)
			{
				app->fonts->BlitText(77, 240, scoreFont, "i did not wanted to survive to the");
				app->fonts->BlitText(77, 260, scoreFont, "accident. and now, you will pay for it.");
			}

			if (app->player->finalBossPhaseCounter > 4740 && app->player->finalBossPhaseCounter < 4980)
			{
				app->fonts->BlitText(77, 240, scoreFont, "you all deserve the worst. prepare to");
				app->fonts->BlitText(77, 260, scoreFont, "die.");
			}

			SDL_Rect quad;
			quad = { 203 - 100, 62, app->player->QTE_Counter/2/*/2 - 76*/, 16 };
			
			
			//app->player->QTE_Counter_bar;
			if (app->player->finalBossPhaseCounter > 1918 && app->player->finalBossPhaseCounter <= 1920)
			{

				app->player->QTE_Counter = 600;
				QTE_keys_pointerPositionX = 160;
			}
			if (app->player->finalBossPhaseCounter > 1920 && app->player->finalBossPhaseCounter <= 2520)
			{
				app->player->QTE_Counter--;

				app->render->DrawTexture2(app->moduleUI->QTE_swat1, 0, 10, NULL);

				app->render->DrawTexture2(app->moduleUI->QTE_kb_combo_1, 0, 0, NULL);
				app->render->DrawTexture2(app->moduleUI->QTE_timer_bar, -100, 0, NULL);
				app->render->DrawTexture2(app->moduleUI->QTE_keys_pointer, QTE_keys_pointerPositionX, 150, NULL);

				if (app->player->QTE_Counter > 300)app->render->DrawRectangle2(quad, 0, 255, 0, 255, 0.0f, true);
				else if (app->player->QTE_Counter > 150 && app->player->QTE_Counter <= 300)app->render->DrawRectangle2(quad, 255, 255, 0, 255, 0.0f, true);
				else if (app->player->QTE_Counter <= 150)app->render->DrawRectangle2(quad, 255, 0, 0, 255, 0.0f, true);

				if (app->input->keys[SDL_SCANCODE_Z] == KEY_DOWN && QTE_keys_pointerPositionX == 160)
				{
					QTE_keys_pointerPositionX = 230;
				}
				//else if(app->input->keys[SDL_SCANCODE_Z] != KEY_DOWN && QTE_keys_pointerPositionX == 160) QTE_keys_pointerPositionX = 160;

				if (app->input->keys[SDL_SCANCODE_C] == KEY_DOWN && QTE_keys_pointerPositionX == 230)
				{
					QTE_keys_pointerPositionX = 300;
				}
				//else if(app->input->keys[SDL_SCANCODE_C] != KEY_DOWN && QTE_keys_pointerPositionX == 230) QTE_keys_pointerPositionX = 160;

				if (app->input->keys[SDL_SCANCODE_X] == KEY_DOWN && QTE_keys_pointerPositionX == 300)
				{
					QTE_keys_pointerPositionX = 360;
				}
				//else if(app->input->keys[SDL_SCANCODE_X] != KEY_DOWN && QTE_keys_pointerPositionX == 300) QTE_keys_pointerPositionX = 160;

				if (app->input->keys[SDL_SCANCODE_X] == KEY_DOWN && QTE_keys_pointerPositionX == 360)
				{
					QTE_keys_pointerPositionX = 430;
				}
				//else if (app->input->keys[SDL_SCANCODE_X] != KEY_DOWN && QTE_keys_pointerPositionX == 360) QTE_keys_pointerPositionX = 160;

				if (app->input->keys[SDL_SCANCODE_Z] == KEY_DOWN && QTE_keys_pointerPositionX == 430)
				{
					QTE_keys_pointerPositionX = 700;
				}
				//else if (app->input->keys[SDL_SCANCODE_Z] != KEY_DOWN && QTE_keys_pointerPositionX == 430) QTE_keys_pointerPositionX = 160;

				if (app->player->QTE_Counter <= 0 && QTE_keys_pointerPositionX != 700) app->player->finalBossPlayerStrikes++;
			}


			if (app->player->finalBossPhaseCounter > 2520 && app->player->finalBossPhaseCounter <= 2522)
			{
				app->player->QTE_Counter = 600;
				QTE_keys_pointerPositionX = 160;
			}
			if (app->player->finalBossPhaseCounter > 2522 && app->player->finalBossPhaseCounter <= 3122)
			{
				app->player->QTE_Counter--;

				app->render->DrawTexture2(app->moduleUI->QTE_zombie1, 0, 10, NULL);

				app->render->DrawTexture2(app->moduleUI->QTE_kb_combo_2, 0, 0, NULL);
				app->render->DrawTexture2(app->moduleUI->QTE_timer_bar, -100, 0, NULL);
				app->render->DrawTexture2(app->moduleUI->QTE_keys_pointer, QTE_keys_pointerPositionX, 150, NULL);

				if (app->player->QTE_Counter > 300)app->render->DrawRectangle2(quad, 0, 255, 0, 255, 0.0f, true);
				else if (app->player->QTE_Counter > 150 && app->player->QTE_Counter <= 300)app->render->DrawRectangle2(quad, 255, 255, 0, 255, 0.0f, true);
				else if (app->player->QTE_Counter <= 150)app->render->DrawRectangle2(quad, 255, 0, 0, 255, 0.0f, true);

				if (app->input->keys[SDL_SCANCODE_C] == KEY_DOWN && QTE_keys_pointerPositionX == 160)
				{
					QTE_keys_pointerPositionX = 230;
				}
				//else if (app->input->keys[SDL_SCANCODE_C] != KEY_DOWN && QTE_keys_pointerPositionX == 160) QTE_keys_pointerPositionX = 160;

				if (app->input->keys[SDL_SCANCODE_X] == KEY_DOWN && QTE_keys_pointerPositionX == 230)
				{
					QTE_keys_pointerPositionX = 300;
				}
				//else if (app->input->keys[SDL_SCANCODE_X] != KEY_DOWN && QTE_keys_pointerPositionX == 230) QTE_keys_pointerPositionX = 160;

				if (app->input->keys[SDL_SCANCODE_Z] == KEY_DOWN && QTE_keys_pointerPositionX == 300)
				{
					QTE_keys_pointerPositionX = 360;
				}
				//else if (app->input->keys[SDL_SCANCODE_Z] != KEY_DOWN && QTE_keys_pointerPositionX == 300) QTE_keys_pointerPositionX = 160;

				if (app->input->keys[SDL_SCANCODE_RIGHT] == KEY_DOWN && QTE_keys_pointerPositionX == 360)
				{
					QTE_keys_pointerPositionX = 430;
				}
				//else if (app->input->keys[SDL_SCANCODE_RIGHT] != KEY_DOWN && QTE_keys_pointerPositionX == 360) QTE_keys_pointerPositionX = 160;

				if (app->input->keys[SDL_SCANCODE_Z] == KEY_DOWN && QTE_keys_pointerPositionX == 430)
				{
					QTE_keys_pointerPositionX = 700;
				}
				//else if (app->input->keys[SDL_SCANCODE_Z] != KEY_DOWN && QTE_keys_pointerPositionX == 430) QTE_keys_pointerPositionX = 160;

				if (app->player->QTE_Counter <= 0 && QTE_keys_pointerPositionX != 700) app->player->finalBossPlayerStrikes++;
			}


			if (app->player->finalBossPhaseCounter > 3122 && app->player->finalBossPhaseCounter <= 3124)
			{
				app->player->QTE_Counter = 600;
				QTE_keys_pointerPositionX = 160;
			}
			if (app->player->finalBossPhaseCounter > 3124 && app->player->finalBossPhaseCounter <= 3724)
			{
				app->player->QTE_Counter--;

				app->render->DrawTexture2(app->moduleUI->QTE_swat2, 0, 10, NULL);

				app->render->DrawTexture2(app->moduleUI->QTE_kb_combo_3, 0, 0, NULL);
				app->render->DrawTexture2(app->moduleUI->QTE_timer_bar, -100, 0, NULL);
				app->render->DrawTexture2(app->moduleUI->QTE_keys_pointer, QTE_keys_pointerPositionX, 150, NULL);

				if (app->player->QTE_Counter > 300)app->render->DrawRectangle2(quad, 0, 255, 0, 255, 0.0f, true);
				else if (app->player->QTE_Counter > 150 && app->player->QTE_Counter <= 300)app->render->DrawRectangle2(quad, 255, 255, 0, 255, 0.0f, true);
				else if (app->player->QTE_Counter <= 150)app->render->DrawRectangle2(quad, 255, 0, 0, 255, 0.0f, true);

				if (app->input->keys[SDL_SCANCODE_UP] == KEY_DOWN && QTE_keys_pointerPositionX == 160)
				{
					QTE_keys_pointerPositionX = 230;
				}
				//else if (app->input->keys[SDL_SCANCODE_UP] != KEY_DOWN && QTE_keys_pointerPositionX == 160) QTE_keys_pointerPositionX = 160;

				if (app->input->keys[SDL_SCANCODE_Z] == KEY_DOWN && QTE_keys_pointerPositionX == 230)
				{
					QTE_keys_pointerPositionX = 300;
				}
				//else if (app->input->keys[SDL_SCANCODE_Z] != KEY_DOWN && QTE_keys_pointerPositionX == 230) QTE_keys_pointerPositionX = 160;

				if (app->input->keys[SDL_SCANCODE_DOWN] == KEY_DOWN && QTE_keys_pointerPositionX == 300)
				{
					QTE_keys_pointerPositionX = 360;
				}
				//else if (app->input->keys[SDL_SCANCODE_DOWN] != KEY_DOWN && QTE_keys_pointerPositionX == 300) QTE_keys_pointerPositionX = 160;

				if (app->input->keys[SDL_SCANCODE_RIGHT] == KEY_DOWN && QTE_keys_pointerPositionX == 360)
				{
					QTE_keys_pointerPositionX = 430;
				}
				//else if (app->input->keys[SDL_SCANCODE_LEFT] != KEY_DOWN && QTE_keys_pointerPositionX == 360) QTE_keys_pointerPositionX = 160;

				if (app->input->keys[SDL_SCANCODE_X] == KEY_DOWN && QTE_keys_pointerPositionX == 430)
				{
					QTE_keys_pointerPositionX = 700;
				}
				//else if (app->input->keys[SDL_SCANCODE_X] != KEY_DOWN && QTE_keys_pointerPositionX == 430) QTE_keys_pointerPositionX = 160;

				if (app->player->QTE_Counter <= 0 && QTE_keys_pointerPositionX != 700) app->player->finalBossPlayerStrikes++;
			}


			if (app->player->finalBossPhaseCounter > 3724 && app->player->finalBossPhaseCounter <= 3726)
			{
				app->player->QTE_Counter = 600;
				QTE_keys_pointerPositionX = 160;
			}
			if (app->player->finalBossPhaseCounter > 3726 && app->player->finalBossPhaseCounter <= 4326)
			{
				app->player->QTE_Counter--;

				app->render->DrawTexture2(app->moduleUI->QTE_zombie2, 0, 10, NULL);

				app->render->DrawTexture2(app->moduleUI->QTE_kb_combo_4, 0, 0, NULL);
				app->render->DrawTexture2(app->moduleUI->QTE_timer_bar, -100, 0, NULL);
				app->render->DrawTexture2(app->moduleUI->QTE_keys_pointer, QTE_keys_pointerPositionX, 150, NULL);

				if (app->player->QTE_Counter > 300)app->render->DrawRectangle2(quad, 0, 255, 0, 255, 0.0f, true);
				else if (app->player->QTE_Counter > 150 && app->player->QTE_Counter <= 300)app->render->DrawRectangle2(quad, 255, 255, 0, 255, 0.0f, true);
				else if (app->player->QTE_Counter <= 150)app->render->DrawRectangle2(quad, 255, 0, 0, 255, 0.0f, true);

				if (app->input->keys[SDL_SCANCODE_LEFT] == KEY_DOWN && QTE_keys_pointerPositionX == 160)
				{
					QTE_keys_pointerPositionX = 230;
				}
				//else if (app->input->keys[SDL_SCANCODE_LEFT] != KEY_DOWN && QTE_keys_pointerPositionX == 160) QTE_keys_pointerPositionX = 160;

				if (app->input->keys[SDL_SCANCODE_DOWN] == KEY_DOWN && QTE_keys_pointerPositionX == 230)
				{
					QTE_keys_pointerPositionX = 300;
				}
				//else if (app->input->keys[SDL_SCANCODE_DOWN] != KEY_DOWN && QTE_keys_pointerPositionX == 230) QTE_keys_pointerPositionX = 160;

				if (app->input->keys[SDL_SCANCODE_Z] == KEY_DOWN && QTE_keys_pointerPositionX == 300)
				{
					QTE_keys_pointerPositionX = 360;
				}
				//else if (app->input->keys[SDL_SCANCODE_Z] != KEY_DOWN && QTE_keys_pointerPositionX == 300) QTE_keys_pointerPositionX = 160;

				if (app->input->keys[SDL_SCANCODE_RIGHT] == KEY_DOWN && QTE_keys_pointerPositionX == 360)
				{
					QTE_keys_pointerPositionX = 430;
				}
				//else if (app->input->keys[SDL_SCANCODE_RIGHT] != KEY_DOWN && QTE_keys_pointerPositionX == 360) QTE_keys_pointerPositionX = 160;

				if (app->input->keys[SDL_SCANCODE_UP] == KEY_DOWN && QTE_keys_pointerPositionX == 430)
				{
					QTE_keys_pointerPositionX = 700;
				}
				//else if (app->input->keys[SDL_SCANCODE_UP] != KEY_DOWN && QTE_keys_pointerPositionX == 430) QTE_keys_pointerPositionX = 160;

				if (app->player->QTE_Counter <= 0 && QTE_keys_pointerPositionX != 700) app->player->finalBossPlayerStrikes++;
			}



			if (app->player->finalBossPhaseCounter > 4980 && app->player->finalBossPhaseCounter <= 4982)
			{
				app->player->QTE_Counter = 600;
				QTE_keys_pointerPositionX = 160;
			}
			if (app->player->finalBossPhaseCounter > 4982 && app->player->finalBossPhaseCounter <= 5582)
			{
				app->player->QTE_Counter--;

				app->render->DrawTexture2(app->moduleUI->QTE_swat1, 0, 10, NULL);

				app->render->DrawTexture2(app->moduleUI->QTE_kb_combo_5, 0, 0, NULL);
				app->render->DrawTexture2(app->moduleUI->QTE_timer_bar, -100, 0, NULL);
				app->render->DrawTexture2(app->moduleUI->QTE_keys_pointer, QTE_keys_pointerPositionX, 150, NULL);

				if (app->player->QTE_Counter > 300)app->render->DrawRectangle2(quad, 0, 255, 0, 255, 0.0f, true);
				else if (app->player->QTE_Counter > 150 && app->player->QTE_Counter <= 300)app->render->DrawRectangle2(quad, 255, 255, 0, 255, 0.0f, true);
				else if (app->player->QTE_Counter <= 150)app->render->DrawRectangle2(quad, 255, 0, 0, 255, 0.0f, true);

				if (app->input->keys[SDL_SCANCODE_UP] == KEY_DOWN && QTE_keys_pointerPositionX == 160)
				{
					QTE_keys_pointerPositionX = 230;
				}
				//else if (app->input->keys[SDL_SCANCODE_UP] != KEY_DOWN && QTE_keys_pointerPositionX == 160) QTE_keys_pointerPositionX = 160;

				if (app->input->keys[SDL_SCANCODE_Z] == KEY_DOWN && QTE_keys_pointerPositionX == 230)
				{
					QTE_keys_pointerPositionX = 300;
				}
				//else if (app->input->keys[SDL_SCANCODE_Z] != KEY_DOWN && QTE_keys_pointerPositionX == 230) QTE_keys_pointerPositionX = 160;

				if (app->input->keys[SDL_SCANCODE_C] == KEY_DOWN && QTE_keys_pointerPositionX == 300)
				{
					QTE_keys_pointerPositionX = 360;
				}
				//else if (app->input->keys[SDL_SCANCODE_C] != KEY_DOWN && QTE_keys_pointerPositionX == 300) QTE_keys_pointerPositionX = 160;

				if (app->input->keys[SDL_SCANCODE_RIGHT] == KEY_DOWN && QTE_keys_pointerPositionX == 360)
				{
					QTE_keys_pointerPositionX = 430;
				}
				//else if (app->input->keys[SDL_SCANCODE_RIGHT] != KEY_DOWN && QTE_keys_pointerPositionX == 360) QTE_keys_pointerPositionX = 160;

				if (app->input->keys[SDL_SCANCODE_X] == KEY_DOWN && QTE_keys_pointerPositionX == 430)
				{
					QTE_keys_pointerPositionX = 700;
				}
				//else if (app->input->keys[SDL_SCANCODE_X] != KEY_DOWN && QTE_keys_pointerPositionX == 430) QTE_keys_pointerPositionX = 160;

				if (app->player->QTE_Counter <= 0 && QTE_keys_pointerPositionX != 700) app->player->finalBossPlayerStrikes++;
			}


			

			if (app->player->finalBossPhaseCounter > 5582 && app->player->finalBossPhaseCounter <= 5584)
			{
				app->player->QTE_Counter = 0;
				QTE_keys_pointerPositionX = 700;
			}
			if (app->player->finalBossPhaseCounter > 5584 && app->player->finalBossPhaseCounter <= 6184)
			{
				//app->player->QTE_Counter--;

				app->render->DrawTexture2(app->moduleUI->QTE_swat_final, 0, 10, NULL);

				app->render->DrawTexture2(app->moduleUI->QTE_kb_combo_spam, 0, 0, NULL);
				app->render->DrawTexture2(app->moduleUI->QTE_strength_bar, -100, 0, NULL);
				app->render->DrawTexture2(app->moduleUI->QTE_keys_pointer, QTE_keys_pointerPositionX, 150, NULL);

				if (app->player->QTE_Counter > 400)app->render->DrawRectangle2(quad, 0, 255, 0, 255, 0.0f, true);
				else if (app->player->QTE_Counter > 150 && app->player->QTE_Counter <= 400)app->render->DrawRectangle2(quad, 255, 255, 0, 255, 0.0f, true);
				else if (app->player->QTE_Counter <= 150)app->render->DrawRectangle2(quad, 255, 0, 0, 255, 0.0f, true);

				if (app->input->keys[SDL_SCANCODE_Z] == KEY_DOWN)
				{
					if (app->player->QTE_Counter < 594)app->player->QTE_Counter += 10;
				}
				else if (app->input->keys[SDL_SCANCODE_Z] == KEY_IDLE)
				{
					if (app->player->QTE_Counter > 0)app->player->QTE_Counter--;
				}

				
			}
			if(app->player->finalBossPhaseCounter > 6184 && app->player->finalBossPhaseCounter <= 6186 && app->player->QTE_Counter < 520)app->player->finalBossPlayerStrikes++;


			if (app->player->finalBossPhaseCounter > 6420 && app->player->finalBossPhaseCounter <= 6422)
			{
				if (app->player->finalBossPlayerStrikes >= 5) app->player->playerHP = 0;
				else if (app->player->finalBossPlayerStrikes < 5) app->player->playerWin = true;

			}
		}

		



		if (app->player->npcClose == false && app->player->npc2Close == false && app->player->npc3Close == false && app->player->npc4Close == false)
		{
			dialoguePhase = 0;
			option1Selected = false;
			option2Selected = false;
			option1SelectedSecondDialog = false;
			option2SelectedSecondDialog = false;
		}
	}
	
	//button->Draw(app->render);
	
	return true;
}

bool DialogManager::CleanUp()
{
	app->tex->UnLoad(textRectanlgeNPC);
	app->tex->UnLoad(textRectanlgePlayer);
	app->tex->UnLoad(textOptionUnselected);
	app->tex->UnLoad(textNameNPC1);
	app->tex->UnLoad(textNameNPC2);
	app->tex->UnLoad(textNameNPC3);
	app->tex->UnLoad(textNameNPC4);
	app->tex->UnLoad(textNameFINAL_BOSS);
	app->tex->UnLoad(textNamePlayer);
	app->tex->UnLoad(textOption1);
	app->tex->UnLoad(textOption2);
	app->tex->UnLoad(tntExample);

	app->fonts->UnLoad(app->dialogManager->scoreFont);

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

				if (dialoguePhase == 2)
				{
					option1SelectedSecondDialog = true;
				}
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
			if (app->player->npc4Close == true)
			{
				app->audio->PlayFx(buttonClickedFx, 0);
				dialoguePhase++;
				option1Selected = true;

				if (dialoguePhase == 2)
				{
					option1SelectedSecondDialog = true;
				}
			}

		}
		if (control->id == 24 && GUItextOption2->canClick == true)
		{
			if (app->player->npcClose == true)
			{
				app->audio->PlayFx(buttonClickedFx, 0);
				dialoguePhase++;
				option2Selected = true;

				if (dialoguePhase == 2)
				{
					option2SelectedSecondDialog = true;
				}
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
			if (app->player->npc4Close == true)
			{
				app->audio->PlayFx(buttonClickedFx, 0);
				dialoguePhase++;
				option2Selected = true;

				if (dialoguePhase == 2)
				{
					option2SelectedSecondDialog = true;
				}
			}
		}
		


	default: break;
	}
	}

	return true;
}
