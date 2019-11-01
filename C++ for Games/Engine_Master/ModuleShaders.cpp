#include "ModuleShaders.h"
#include <glew.h>



ModuleShaders::ModuleShaders()
{
}


ModuleShaders::~ModuleShaders()
{
}

bool ModuleShaders::Init()
{
	char *vertexShader = nullptr;
	char *fragmentShader = nullptr;
	//FILE *file = nullptr;
    /*
	fopen_s(&file, "shaders/default.vs", "rb");
	if (file) {
		fseek(file, 0, SEEK_END);
		int size = ftell(file);
		rewind(file);
		vertexShader = (char*)malloc(size + 1);

		fread(vertexShader, 1, size, file);
		vertexShader[size] = 0;

		fclose(file);
	}


	fopen_s(&file, "shaders/default.fs", "rb");
	if (file) {
		fseek(file, 0, SEEK_END);
		int size = ftell(file);
		rewind(file);
		fragmentShader = (char*)malloc(size + 1);

		fread(fragmentShader, 1, size, file);
		fragmentShader[size] = 0;

		fclose(file);
	}
	*/
	readShader(vertexShader, "shaders/vsdefault.txt");
	readShader(fragmentShader, "shaders/fsdefault.txt");

	unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexShader, nullptr);
	glCompileShader(vertex);
	unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentShader, nullptr);
	glCompileShader(fragment);

	def_program = glCreateProgram();
	glAttachShader(def_program, vertex);
	glAttachShader(def_program, fragment);
	glLinkProgram(def_program);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
	return true;
}

update_status ModuleShaders::PreUpdate()
{
	return UPDATE_CONTINUE;
}

update_status ModuleShaders::Update()
{
	return UPDATE_CONTINUE;

}

update_status ModuleShaders::PostUpdate()
{
	return UPDATE_CONTINUE;

}

bool ModuleShaders::CleanUp()
{
	return true;
}

void ModuleShaders::readShader(char* shader, const char* path) {

	FILE *file = nullptr;

	fopen_s(&file, path, "rb");
	if (file) {
		fseek(file, 0, SEEK_END);
		int size = ftell(file);
		rewind(file);
		shader = (char*)malloc(size + 1);

		fread(shader, 1, size, file);
		shader[size] = 0;

		fclose(file);
	}
}


