#include "GLFWGL4ImGUILayer.hpp"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"
#include "implot.h"

OpenMIMO::GLFWGL4ImGUILayer::GLFWGL4ImGUILayer(GLFWwindow* windowPtr, std::string_view layerName) :
    ImGUILayer(layerName), m_WindowPtr(windowPtr)
{
}

OpenMIMO::GLFWGL4ImGUILayer::~GLFWGL4ImGUILayer()
{
    m_WindowPtr = nullptr;
}

void OpenMIMO::GLFWGL4ImGUILayer::OnAttach()
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsLight();

    ImGui_ImplGlfw_InitForOpenGL(m_WindowPtr, true);
    ImGui_ImplOpenGL3_Init();
}

void OpenMIMO::GLFWGL4ImGUILayer::OnDetach()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void OpenMIMO::GLFWGL4ImGUILayer::OnUpdate()
{
}

void OpenMIMO::GLFWGL4ImGUILayer::BeginFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void OpenMIMO::GLFWGL4ImGUILayer::EndFrame()
{
    /*Future implementation*/
    //ImGuiIO& io = ImGui::GetIO();
	//auto app = Application::GetInstance();
	//io.DisplaySize = ImVec2((float)app->GetWindow()->GetWidth(), (float)app->GetWindow()->GetHeight());

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}