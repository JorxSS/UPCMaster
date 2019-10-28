#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneKen.h"
#include "ModuleSceneHonda.h"
#include "ModulePlayer.h"
#include "SDL/include/SDL.h"



ModuleSceneHonda::ModuleSceneHonda(bool start_enabled) : Module(start_enabled)
{

	// ground
	ground.x = 8;
	ground.y = 376;
	ground.w = 848;
	ground.h = 63;

	//foreground
	foreground.x = 127;
	foreground.y = 128;
	foreground.w = 633;
	foreground.h = 199;

	// roof
	background.x = 90;
	background.y = 8;
	background.w = 633;
	background.h = 47;

	//onsen
	onsen.x = 164;
	onsen.y = 66;
	onsen.w = 335;
	onsen.h = 50;

	//reverse foreground
	rev_for.x = 586;
	rev_for.y = 128;
	rev_for.w = 175;
	rev_for.h = 199;

	// reverse roof
	rev_back.x = 240;
	rev_back.y = 8;
	rev_back.w = 557;
	rev_back.h = 47;
	//art
	mount.frames.push_back({ 225, 64, 223, 103 });
	mount.frames.push_back({ 456, 64, 223, 103 });
	mount.speed = 0.02f;

	//water
	water.frames.push_back({ 8, 448, 284, 8 });
	water.frames.push_back({ 296, 448, 284, 12 });
	water.frames.push_back({ 588, 448, 284, 19 });
	water.speed = 0.02f;
	//xino
	xino.frames.push_back({ 535, 184, 96, 104 });
	//xino.frames.push_back({ 792, 64, 96, 104 });
	xino.frames.push_back({ 688, 64, 96, 104 });
	xino.speed = 0.02f;

}

ModuleSceneHonda::~ModuleSceneHonda()
{
}

bool ModuleSceneHonda::Start()
{
	LOG("Loading Honda scene");
	
	graphics = App->textures->Load("honda_stage2.png");
	reverse = App->textures->Load("hondareverse.png");
	anim =  App->textures->Load("honda_stage.png");


	// TODO 7: Enable the player module
	App->player->Enable();
	// TODO 0: trigger background music
	App->audio->PlayMusic("honda.ogg");


	return true;
}

update_status ModuleSceneHonda::Update() 
{
	App->renderer->Blit(graphics, -60, 170, &ground);
	App->renderer->Blit(reverse, 550, 0, &rev_for);
	App->renderer->Blit(reverse, 220, 0, &rev_back);
	App->renderer->Blit(graphics, 0, 0, &foreground);
	App->renderer->Blit(graphics, -60, 0, &background);
	App->renderer->Blit(anim, 408, 56, &(xino.GetCurrentFrame()));
	App->renderer->Blit(anim, 185, 56, &(mount.GetCurrentFrame()));
	App->renderer->Blit(graphics, 200, 140, &onsen);
	App->renderer->Blit(anim, 225, 152, &(water.GetCurrentFrame()));



	return UPDATE_CONTINUE;
}

bool ModuleSceneHonda::CleanUp()
{
	LOG("Unloading Honda scene");

	App->textures->Unload(graphics);
	App->textures->Unload(reverse);
	App->textures->Unload(anim);
	App->player->Disable();
	return true;
}
