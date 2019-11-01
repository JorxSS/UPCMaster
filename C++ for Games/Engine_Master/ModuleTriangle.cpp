#include "ModuleTriangle.h"
#include "ModuleShaders.h"
#include "Application.h"
#include "Math/float3.h"
#include "Math/float4.h"
#include "Math/float3x3.h"
#include "Geometry/Frustum.h"
#include "Math/MathAll.h"



ModuleTriangle::ModuleTriangle()
{
}


ModuleTriangle::~ModuleTriangle()
{
}

bool ModuleTriangle::Init() {
	float buffer_data[] = { -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f };
	
	Frustum frustum;
	frustum.type = FrustumType::PerspectiveFrustum;
	frustum.pos = float3::zero;
	frustum.front = -float3::unitZ;
	frustum.up = float3::unitY;
	frustum.nearPlaneDistance = 0.1f;
	frustum.farPlaneDistance = 100.0f;
	frustum.verticalFov = math::pi / 4.0f;
	frustum.horizontalFov = 2.f * atanf(tanf(frustum.verticalFov * 0.5f) *(SCREEN_WIDTH/SCREEN_HEIGHT));

	model = math::float4x4::FromTRS(math::float3(0.0f, 0.0f, -4.0f),math::float3x3::RotateY(math::pi / 4.0f), math::float3(1.0f,1.0f, 1.0f));	
	view = LookAt(math::float3(0.0f, 1.f, 4.0f),math::float3(0.0f, 0.0f, 0.0f), math::float3(0.0f,1.0f, 0.0f));
	proj = frustum.ProjectionMatrix();
	//math::float4x4 transform = proj * float4x4(model) * view;
	
/*	float4 FirstPoint = transform * float4(buffer_data[0], buffer_data[1],buffer_data[2], 1);
	float4 SecondPoint = transform * float4(buffer_data[3], buffer_data[4], buffer_data[5], 1);
	float4 ThirdPoint = transform * float4(buffer_data[6], buffer_data[7], buffer_data[8], 1);

	FirstPoint = FirstPoint / FirstPoint.w;
	SecondPoint = SecondPoint / SecondPoint.w;
	ThirdPoint = ThirdPoint / ThirdPoint.w;

	buffer_data[0] = FirstPoint.x;
	buffer_data[1] = FirstPoint.y;
	buffer_data[2] = FirstPoint.z;
	buffer_data[3] = SecondPoint.x;
	buffer_data[4] = SecondPoint.y;
	buffer_data[5] = SecondPoint.z;
	buffer_data[6] = ThirdPoint.x;
	buffer_data[7] = ThirdPoint.y;
	buffer_data[8] = ThirdPoint.z;*/


	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(buffer_data), buffer_data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return true;
}

update_status ModuleTriangle::Update()
{

	/*glEnableVertexAttribArray(0); // attribute 0
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 0, (void*)0 );
	glDrawArrays(GL_TRIANGLES, 0, 3); // start at 0 and 3 tris
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);*/

	glUseProgram(App->shader->def_program);
	glUniformMatrix4fv(glGetUniformLocation(App->shader->def_program, "model"), 1, GL_TRUE, &model[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(App->shader->def_program, "view"), 1, GL_TRUE, &view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(App->shader->def_program, "proj"), 1, GL_TRUE, &proj[0][0]);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

		
	return UPDATE_CONTINUE;
}

float4x4 ModuleTriangle::LookAt(float3 target, float3 eye, float3 up) {

	float4x4 matrix;

	math::float3 f(target - eye); f.Normalize();
	math::float3 s(f.Cross(up)); s.Normalize();
	math::float3 u(s.Cross(f));
	matrix[0][0] = s.x; matrix[0][1] = s.y; matrix[0][2] = s.z;
	matrix[1][0] = u.x; matrix[1][1] = u.y; matrix[1][2] = u.z;
	matrix[2][0] = -f.x; matrix[2][1] = -f.y; matrix[2][2] = -f.z;
	matrix[0][3] = -s.Dot(eye); matrix[1][3] = -u.Dot(eye); matrix[2][3] = f.Dot(eye);
	matrix[3][0] = 0.0f; matrix[3][1] = 0.0f; matrix[3][2] = 0.0f; matrix[3][3] = 1.0f;

	return matrix;
}
