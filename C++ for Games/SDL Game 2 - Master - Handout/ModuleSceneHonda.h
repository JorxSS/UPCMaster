#ifndef __MODULESCENEHONDA_H__
#define __MODULESCENEHONDA_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleSceneHonda : public Module
{
public:
	ModuleSceneHonda( bool start_enabled = true);
    ~ModuleSceneHonda();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Texture* reverse = nullptr;
	SDL_Texture* anim = nullptr;
	SDL_Rect ground;
	SDL_Rect background;
	SDL_Rect foreground;
	SDL_Rect rev_back;
	SDL_Rect rev_for;
	SDL_Rect onsen;
	Animation water;
	Animation mount;
	Animation xino;
};

#endif // __MODULESCENEHONDA_H__
