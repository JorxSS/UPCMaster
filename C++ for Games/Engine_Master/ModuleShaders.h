#pragma once
#include "Module.h"

class ModuleShaders : public Module
{
public:
	ModuleShaders();
	~ModuleShaders();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void readShader(char*, const char*);
	unsigned int def_program;

		
};

