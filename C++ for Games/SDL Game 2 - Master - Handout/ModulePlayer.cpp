#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "SDL/include/SDL.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA
ModulePlayer::ModulePlayer(bool start_enabled) : Module(start_enabled)
{
	position.x = 180;
	position.y = 120;

	// idle animation (arcade sprite sheet)
	idle.frames.push_back({7, 14, 60, 90});
	idle.frames.push_back({95, 15, 60, 89});
	idle.frames.push_back({184, 14, 60, 90});
	idle.frames.push_back({276, 11, 60, 93});
	idle.frames.push_back({366, 12, 60, 92});
	idle.speed = 0.1f;
	
	// walk backward animation (arcade sprite sheet)
	backward.frames.push_back({542, 131, 61, 87});
	backward.frames.push_back({628, 129, 59, 90});
	backward.frames.push_back({713, 128, 57, 90});
	backward.frames.push_back({797, 127, 57, 90});
	backward.frames.push_back({883, 128, 58, 91});
	backward.frames.push_back({974, 129, 57, 89});
	backward.speed = 0.1f;

	// TODO 8: setup the walk forward animation from ryu4.png
	forward.frames.push_back({8,136,54,83});
	forward.frames.push_back({77,131,61,88});
	forward.frames.push_back({161,128,63,91});
	forward.frames.push_back({259,128,62,89});
	forward.frames.push_back({352,128,53,91});
	forward.frames.push_back({432,131,50,88});
	forward.speed = 0.1f;

}

ModulePlayer::~ModulePlayer()
{
	// Homework : check for memory leaks
}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("ryu4.png"); // arcade version

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

// Update
update_status ModulePlayer::Update()
{
	// TODO 9: Draw the player with its animation
	// make sure to detect player movement and change its
	// position while cycling the animation(check Animation.h)
	int speed = 1;
	
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) {
		position.x -= speed;
		App->renderer->Blit(graphics, position.x, position.y, &(backward.GetCurrentFrame()));
	}else if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {
		position.x += speed;
		App->renderer->Blit(graphics, position.x, position.y, &(forward.GetCurrentFrame()));
	}
	else {
		App->renderer->Blit(graphics, position.x, position.y, &(idle.GetCurrentFrame()));
	}

	return UPDATE_CONTINUE;
}