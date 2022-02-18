#ifndef __MODULE_H__
#define __MODULE_H__

#include "SString.h"

#include "PugiXml/src/pugixml.hpp"

class App;
class PhysBody;
struct Collider;
class GuiControl;

class Module
{
public:

	Module(bool start_enabled = false) : active(start_enabled)
	{
	}

	bool Init()
	{
		return true;
	}

	// Called before render is available
	// L01: DONE 5: Sending config file to all modules
	virtual bool Awake(pugi::xml_node&)
	{
		return true;
	}

	// Called before the first frame
	virtual bool Start()
	{
		return true;
	}

	bool IsEnabled() const
	{
		return active;
	}

	// Called each loop iteration
	virtual bool PreUpdate()
	{
		return true;
	}

	// Called each loop iteration
	virtual bool Update(float dt)
	{
		return true;
	}

	// Called each loop iteration
	virtual bool PostUpdate()
	{
		return true;
	}

	// Called before quitting
	virtual bool CleanUp()
	{
		return true;
	}
	

    // L02: DONE 2: Create new virtual methods to Load / Save state
	virtual bool LoadState(pugi::xml_node&)
	{
		return true;
	}
	virtual bool SaveState(pugi::xml_node&) const
	{
		return true;
	}
	virtual bool CheckSave(pugi::xml_node&) 
	{
		return true;
	}
	virtual bool CheckAudioSave(pugi::xml_node&)
	{
		return true;
	}
	
	virtual bool OnGuiMouseClickEvent(GuiControl* control)
	{
		return true;
	}
	

	bool IsActive() const
	{
		return active;
	}
	void Enable()
	{
		if (active == false)
		{
			active = true;
			Start();
		}
	}
	void Disable()
	{
		if (active == true)
		{
			active = false;
			CleanUp();
		}
	}

	virtual void b2dOnCollision(PhysBody* bodyA, PhysBody* bodyB)
	{
	}

	virtual void OnCollision(Collider* c1, Collider* c2)
	{
	}

public:

	SString name;
	bool active;

};

#endif // __MODULE_H__