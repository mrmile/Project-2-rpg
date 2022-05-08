#ifndef __QUEST_MANAGER_H__
#define __QUEST_MANAGER_H__

#include "Module.h"
#include "List.h"
#include "EntityManager.h"

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

	// Called before quitting
	bool CleanUp();
	
	int counter = 0;

	int mainQuestID = 0;
	int secondaryQuestID = 0;

};

#endif // __QUEST_MANAGER_H__