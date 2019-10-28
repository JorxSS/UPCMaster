#pragma once
#include "Module.h"
#include "Globals.h"
#include "SDL/include/SDL.h"

class ModuleImGui :public Module
{
public:
	ModuleImGui();
	~ModuleImGui();
	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void EventManager(SDL_Event);
	
};

