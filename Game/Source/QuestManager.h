#ifndef __QUEST_MANAGER_H__
#define __QUEST_MANAGER_H__

#include "Module.h"
#include "List.h"
#include "EntityManager.h"
#include "Animation.h"
#include "Point.h"

enum MainQuests
{
	M_NONE = 0,
	FIND_THE_DOCTOR_1,
	LOOK_FOR_THE_COMPUTER_2,
	KILL_THE_PATIENT_ZERO_3,
};

enum SecondaryQuests
{
	S_NONE = 0,
	ACTIVATE_SWITCHES,
};

class QuestManager : public Module
{
public:

	QuestManager(bool start_enabled = true);

	// Destructor
	virtual ~QuestManager();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update(float dt);

	bool PostUpdate();

	void SwitchMainQuest(int questID);
	void SwitchSecondaryQuest(int questID);

	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&) const;

	// Called before quitting
	bool CleanUp();
	
	int questCounter = 0;

	int mainQuestID = 0;
	int secondaryQuestID = 0;

	char switchesActivatedText[10] = { "\0" };
	int descriptionCounter = 0;

	SDL_Texture* mainQuestDescription_1 = nullptr;
	SDL_Texture* mainQuestDescription_2 = nullptr;
	SDL_Texture* mainQuestDescription_3 = nullptr;

	SDL_Texture* secondaryQuestSwitches = nullptr;

	SDL_Texture* questCompletionMessage = nullptr;

	uint questCompleted = 0;


	Animation* currentAnimation = nullptr;

	Animation questCompletionAnim;
	Animation none;

};

#endif // __QUEST_MANAGER_H__