#include "dylib.hpp"
#include <Windows.h>
#include <iostream>
#include <cppbass.h>
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_sdl3.h"
#include "imgui/backends/imgui_impl_opengl3.h"
using namespace std;
const char* glsl_version = "#version 130";
namespace GL {
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
}
static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

void BeginAndRenderImguiMenu() {
	GL::glfwSetErrorCallback(glfw_error_callback);
	static char* stringvalue;
	if (!GL::glfwInit()) {
		exit(322);
	}
	GL::glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	GL::glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	GL::GLFWwindow* windowx = GL::glfwCreateWindow(1250, 700, "Hello from un4seen bass!!!", nullptr, nullptr);
	if (!windowx) {
		MessageBoxA(0, "Failed to Create Window!!!", "bassExample-ImguiVersion-GLFW", MB_OK | MB_ICONERROR);
		exit(44122);
	}
	else {
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
		GL::glfwMakeContextCurrent(windowx);
		GL::glfwSwapInterval(1); // Enable vsync
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsLight();

		// Setup Platform/Renderer backends
		ImGui_ImplOpenGL3_Init();
		ImGui_ImplGlfw_InitForOpenGL(windowx, true);
		while (!GL::glfwWindowShouldClose(windowx)) 
		{
			GL::glfwPollEvents();
			if (GL::glfwGetWindowAttrib(windowx, GLFW_ICONIFIED) != 0)
			{
				ImGui_ImplGlfw_Sleep(10);
				continue;
			}
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
			bool show_menu = true;
			if (show_menu) 
			{
				ImGui::Begin("bassExample-ImguiVersion-GLFW by RikkoMatsumatoOfficial", 0, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings);
				ImGui::Text("This Is My First Program for bass(as Example in GLFW)... So Enjoy to use this!!!");
				ImGui::InputText("Write You're Filename with Folder for Correct Work with BASS.dll(x64)", stringvalue, sizeof(stringvalue));
				if (ImGui::Button("Play Music", ImVec2(210, 245))) {
					cppbass::BASS_INIT();
					cppbass::BASS_Start();
					uint32_t zmmn = cppbass::BASS_StreamCreateFile((LPCSTR)stringvalue, BASS_LOOP);
					cppbass::BASS_ChannelPlay(zmmn);
				}
				ImGui::End();
				ImGui::Render();
				int display_w, display_h;
				GL::glfwGetFramebufferSize(windowx, &display_w, &display_h);
				GL::glViewport(0, 0, display_w, display_h);
				GL::glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
				GL::glClear(GL_COLOR_BUFFER_BIT);
				ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

				GL::glfwSwapBuffers(windowx);
			}
			
		}
		// Cleanup
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		GL::glfwDestroyWindow(windowx);
		GL::glfwTerminate();


	}
}
void MainThread() {
	BeginAndRenderImguiMenu();
}
int main() {
	CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(MainThread), 0, 0, 0);
	while (true)
	{
		Sleep(2100);
	}
	return 0;
}