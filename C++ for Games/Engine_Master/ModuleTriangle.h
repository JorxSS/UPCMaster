#pragma once
#include "Module.h"
#include "Globals.h"
#include "Math/float3x4.h"

class ModuleTriangle :public Module
{
public:
	ModuleTriangle();
	virtual ~ModuleTriangle();
	bool Init();
	update_status Update();
	float4x4 LookAt(float3, float3, float3);

private:
	GLuint	vbo;

};


