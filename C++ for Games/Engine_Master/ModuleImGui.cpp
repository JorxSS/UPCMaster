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
	SDL_GetWindowMaximumSize(App->window->window, &max_w, &max_h);
	SDL_GetWindowMinimumSize(App->window->window, &min_w, &min_h);
	
	return true;
}

update_status ModuleImGui::PreUpdate()
{
	LOG("IMGUI PREUPDATE \n");
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->window->window);
	ImGui::NewFrame();

	return UPDATE_CONTINUE;;
}

update_status ModuleImGui::Update()
{
	LOG("IMGUI UPDATE \n");
	//ImGui::ShowDemoWindow();
	Menu();
	Draw("Console");
	return UPDATE_CONTINUE;;
}

update_status ModuleImGui::PostUpdate()
{
	LOG("IMGUI POSTUPDATE \n");
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	SDL_GL_SwapWindow(App->window->window);
	return UPDATE_CONTINUE;;
}

bool ModuleImGui::CleanUp()
{
	LOG("IMGUI BEING DESTROYED \n");
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	return true;
}

void ModuleImGui::EventManager(SDL_Event event)
{
	ImGui_ImplSDL2_ProcessEvent(&event);
}

void ModuleImGui::Draw(const char * title, bool * p_opened)
{
	ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);
	ImGui::Begin(title, p_opened);
	if (ImGui::Button("Clear")) Clear();
	ImGui::SameLine();
	bool copy = ImGui::Button("Copy");
	ImGui::SameLine();
	Filter.Draw("Filter", -100.0f);
	ImGui::Separator();
	ImGui::BeginChild("scrolling");
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 1));
	if (copy) ImGui::LogToClipboard();

	if (Filter.IsActive())
	{
		const char* buf_begin = logBuffer.begin();
		const char* line = buf_begin;
		for (int line_no = 0; line != NULL; line_no++)
		{
			const char* line_end = (line_no < LineOffsets.Size) ? buf_begin + LineOffsets[line_no] : NULL;
			if (Filter.PassFilter(line, line_end))
				ImGui::TextUnformatted(line, line_end);
			line = line_end && line_end[1] ? line_end + 1 : NULL;
		}
	}
	else
	{
		ImGui::TextUnformatted(logBuffer.begin());
	}

	if (ScrollToBottom)
		ImGui::SetScrollHere(1.0f);
	ScrollToBottom = false;
	ImGui::PopStyleVar();
	ImGui::EndChild();
	ImGui::End();
}

void ModuleImGui::Menu()
{
	bool* p_open = NULL;
	static bool fullscreen = false;
	static bool borderless = false;
	static bool resizable = false;
	static bool fsdesktop = false;
	ImGuiWindowFlags window_flags = 0;
	if (fullscreen)        window_flags |= ImGuiWindowFlags_NoTitleBar;
	if (borderless)       window_flags |= ImGuiWindowFlags_NoScrollbar;
	if (resizable)           window_flags |= ImGuiWindowFlags_NoResize;
	if (fsdesktop)            window_flags |= ImGuiWindowFlags_NoMove;

	static float display_brightness = SDL_GetWindowBrightness(App->window->window);
	static int screen_w = 0;
	static int screen_h = 0;
	SDL_GetWindowSize(App->window->window, &screen_w, &screen_h);

	if (!ImGui::Begin("Jordi Demo Engine 0.1", p_open, window_flags))
	{
		// Early out if the window is collapsed, as an optimization.
		ImGui::End();
		return;
	}

	ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_FirstUseEver);
	ImGui::PushItemWidth(ImGui::GetFontSize() * -12);
	ImGui::Text("Jordi Engine with IMGUI. (%s)", IMGUI_VERSION);
	ImGui::Spacing();
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("About.."))
		{
			
			ImGui::EndMenu();

		}
		ImGui::EndMenuBar();
	}


	if (ImGui::CollapsingHeader("Help"))
	{
		ImGui::Text("PROGRAMMER GUIDE:");
		ImGui::BulletText("Please see the comments in imgui.cpp.");
		ImGui::BulletText("Please see the examples/ application.");
		ImGui::Separator();

		ImGui::Text("USER GUIDE:");
		ImGui::ShowUserGuide();
	}
	if (ImGui::CollapsingHeader("Application"))
	{
		ImGui::Text("Engine Version: ");ImGui::SameLine();
		ImGui::TextColored(ImVec4(1, 1, 0, 1), "0.1");
		ImGui::Separator();

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		
		int fps = ImGui::GetIO().Framerate;
		//Get frames
		if (frames.size() > 120) //Max seconds to show
		{
			for (size_t i = 1; i < frames.size(); i++)
			{
				frames[i - 1] = frames[i];
			}
			frames[frames.size() - 1] = fps;
		}
		else
		{
			frames.push_back(fps);
		}
		char title[25];
		sprintf_s(title, 25, "Framerate: %d", fps);
		ImGui::PlotHistogram("##framerate", &frames[0], frames.size(), 0, title, 0.0f, 1000.0f, ImVec2(310, 100));
	}
	if (ImGui::CollapsingHeader("Window")) {

		if (ImGui::SliderFloat("Brightness", &display_brightness, 0, 1.00f)) {

		}
		if (ImGui::SliderInt("Width", &screen_w, min_w, max_w)) {
			App->renderer->WindowResized(screen_w, screen_h);
		}
		if (ImGui::SliderInt("Height", &screen_h, min_h, max_h)) {
			App->renderer->WindowResized(screen_w, screen_h);
		}

		if (ImGui::Checkbox("Fullscreen", &fullscreen)) App->renderer->WindowResized(max_w,max_h);
		ImGui::SameLine();
		ImGui::Checkbox("Resizable", &resizable);

		ImGui::Checkbox("Borderless", &borderless);
		ImGui::SameLine();
		ImGui::Checkbox("Full Desktop", &fsdesktop);

	}
	if (ImGui::CollapsingHeader("Hardware")) {
		/*SDL_version compiled;
		SDL_GetVersion(&compiled);
		ImGui::Text("SDL VERSION: "); ImGui::SameLine();
		ImGui::TextColored(ImVec4(1, 1, 0, 1), (char*)compiled);
		ImGui::Text("GPU: "); ImGui::SameLine();
		ImGui::TextColored(ImVec4(1, 1, 0, 1), (char*)SDL_GetCPUCount());
		ImGui::Text("SDL Version: ", SDL_GetVersion );
		ImGui::Text("CPU: ", SDL_GetCPUCount(), SDL_GetCPUCacheLineSize() );
		ImGui::Text("System RAM: ", SDL_GetSystemRAM() );*/
		char* vendor =(char*)glGetString(GL_VENDOR);
		char* card = (char*)glGetString(GL_RENDERER);
		char* ver = (char*)glGetString(GL_VERSION);
		ImGui::Text("GPU: "); ImGui::SameLine();
		ImGui::TextColored(ImVec4(1, 1, 0, 1), card);
		ImGui::Text("Brand: "); ImGui::SameLine();
		ImGui::TextColored(ImVec4(1, 1, 0, 1), vendor);
		ImGui::Text("Version: "); ImGui::SameLine();
		ImGui::TextColored(ImVec4(1, 1, 0, 1), ver);

	}
	if (ImGui::CollapsingHeader("About..")) {

		ImGui::Text("JS ENGINE 0.1"); 
		ImGui::Text("This Engine was created as a project for the Master Degree 'Advanced Programming for AAA Video Games' made in the UPC from Barcelona");
		ImGui::Text("Authors:  "); ImGui::SameLine();
		ImGui::TextColored(ImVec4(1, 1, 0, 1), "Jordi Sauras Salas");
		ImGui::Text("Libraries Used: "); ImGui::SameLine();
		ImGui::TextColored(ImVec4(1, 1, 0, 1), "SLD2, GLEW, IMGUI");
		ImGui::Text("Liscense: "); ImGui::SameLine();
		ImGui::TextColored(ImVec4(1, 1, 0, 1), "TO DO");

	}

	ImGui::End();
}
