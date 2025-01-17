#pragma once

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleTriangle;
class ModuleInput;
class ModuleShaders;
class ModuleImGui;

class Application
{
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

public:
	ModuleRender* renderer = nullptr;
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleTriangle* triangle = nullptr;
	ModuleShaders* shader = nullptr;
	ModuleImGui* imgui = nullptr;
	

private:

	std::list<Module*> modules;

};

extern Application* App;
