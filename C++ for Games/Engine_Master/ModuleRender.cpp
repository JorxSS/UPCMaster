#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "SDL.h"

ModuleRender::ModuleRender()
{
}

// Destructor
ModuleRender::~ModuleRender()
{
}

// Called before render is available
bool ModuleRender::Init()
{
	LOG("Creating Renderer context");
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	context = SDL_GL_CreateContext(App->window->window);
	GLenum err = glewInit();
	LOG("Using Glew %s \n", glewGetString(GLEW_VERSION));
	LOG("Vendor: %s \n", glGetString(GL_VENDOR));
	LOG("Renderer: %s \n", glGetString(GL_RENDERER));
	LOG("OpenGL version supported %s \n", glGetString(GL_VERSION));
	LOG("GLSL: %s \n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	
	return true;
}

update_status ModuleRender::PreUpdate()
{
	int width;
	int height;
	SDL_GetWindowSize(App->window->window, &width, &height);
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleRender::Update()
{

	return UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate()
{

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRender::CleanUp()
{
	LOG("Destroying renderer");
	SDL_GL_DeleteContext(context);
	//Destroy window
	
	return true;
}

void ModuleRender::WindowResized(unsigned width, unsigned height)
{

	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

