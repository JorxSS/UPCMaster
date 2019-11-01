#pragma once
#include "Module.h"
#include "Globals.h"
#include "MathGeoLib.h"

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
	math::float4x4 model;
	math::float4x4 view;
	math::float4x4 proj;

};


