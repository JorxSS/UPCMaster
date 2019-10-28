#include "ModuleImGui.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"


ModuleImGui::ModuleImGui()
{
}


ModuleImGui::~ModuleImGui()
{
}

bool ModuleImGui::Init()
{
	const char* glsl_version = "#version 130";
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	bool err = glewInit() != GLEW_OK;
	if (err)
	{
		LOG("GUI NOT RUNNING");
		return false;
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	ImGui::StyleColorsDark();

	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer->context);
	ImGui_ImplOpenGL3_Init(glsl_version);
	
	return true;
}

update_status ModuleImGui::PreUpdate()
{
	LOG("IMGUI PREUPDATE");
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->window->window);
	ImGui::NewFrame();

	return UPDATE_CONTINUE;;
}

update_status ModuleImGui::Update()
{
	LOG("IMGUI UPDATE");
	ImGui::ShowDemoWindow();

	return UPDATE_CONTINUE;;
}

update_status ModuleImGui::PostUpdate()
{
	LOG("IMGUI POSTUPDATE");
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	SDL_GL_SwapWindow(App->window->window);
	return UPDATE_CONTINUE;;
}

bool ModuleImGui::CleanUp()
{
	LOG("IMGUI BEING DESTROYED");
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	return true;
}

void ModuleImGui::EventManager(SDL_Event event)
{
	ImGui_ImplSDL2_ProcessEvent(&event);
}
