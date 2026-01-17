#include "Sabre/Sabre.h"

#include "imgui/imgui.h"

#ifdef WINDOWS
#include "imgui/imgui_impl_glfw.h"
#endif

#ifdef API_GL41
#include "imgui/imgui_impl_opengl3.h"
#endif

#include "Sabre/ImGuiHelpers.h"

#include <glm/gtc/type_ptr.hpp>

#include <cstring>
#include "EditorLayer.h"

void SetupImGuiStyle()
{
	// Deep Dark style by janekb04 from ImThemes
	ImGuiStyle& style = ImGui::GetStyle();

	style.Alpha = 1.0f;
	style.DisabledAlpha = 0.6000000238418579f;
	style.WindowPadding = ImVec2(8.0f, 8.0f);
	style.WindowRounding = 7.0f;
	style.WindowBorderSize = 1.0f;
	style.WindowMinSize = ImVec2(32.0f, 32.0f);
	style.WindowTitleAlign = ImVec2(0.0f, 0.5f);
	style.WindowMenuButtonPosition = ImGuiDir_Left;
	style.ChildRounding = 4.0f;
	style.ChildBorderSize = 1.0f;
	style.PopupRounding = 4.0f;
	style.PopupBorderSize = 1.0f;
	style.FramePadding = ImVec2(5.0f, 2.0f);
	style.FrameRounding = 3.0f;
	style.FrameBorderSize = 1.0f;
	style.ItemSpacing = ImVec2(6.0f, 6.0f);
	style.ItemInnerSpacing = ImVec2(6.0f, 6.0f);
	style.CellPadding = ImVec2(6.0f, 6.0f);
	style.IndentSpacing = 25.0f;
	style.ColumnsMinSpacing = 6.0f;
	style.ScrollbarSize = 15.0f;
	style.ScrollbarRounding = 9.0f;
	style.GrabMinSize = 10.0f;
	style.GrabRounding = 3.0f;
	style.TabRounding = 4.0f;
	style.TabBorderSize = 1.0f;
	style.ColorButtonPosition = ImGuiDir_Right;
	style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
	style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

	style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.4980392158031464f, 0.4980392158031464f, 0.4980392158031464f, 1.0f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.09803921729326248f, 0.09803921729326248f, 0.09803921729326248f, 1.0f);
	style.Colors[ImGuiCol_ChildBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.1882352977991104f, 0.1882352977991104f, 0.1882352977991104f, 0.9200000166893005f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.1882352977991104f, 0.1882352977991104f, 0.1882352977991104f, 0.2899999916553497f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.239999994635582f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.0470588244497776f, 0.0470588244497776f, 0.0470588244497776f, 0.5400000214576721f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.1882352977991104f, 0.1882352977991104f, 0.1882352977991104f, 0.5400000214576721f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.2000000029802322f, 0.2196078449487686f, 0.2274509817361832f, 1.0f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.05882352963089943f, 0.05882352963089943f, 0.05882352963089943f, 1.0f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.1372549086809158f, 0.1372549086809158f, 0.1372549086809158f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.0470588244497776f, 0.0470588244497776f, 0.0470588244497776f, 0.5400000214576721f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.3372549116611481f, 0.3372549116611481f, 0.3372549116611481f, 0.5400000214576721f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.4000000059604645f, 0.4000000059604645f, 0.4000000059604645f, 0.5400000214576721f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.5568627715110779f, 0.5568627715110779f, 0.5568627715110779f, 0.5400000214576721f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.3294117748737335f, 0.6666666865348816f, 0.8588235378265381f, 1.0f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.3372549116611481f, 0.3372549116611481f, 0.3372549116611481f, 0.5400000214576721f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.5568627715110779f, 0.5568627715110779f, 0.5568627715110779f, 0.5400000214576721f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.0470588244497776f, 0.0470588244497776f, 0.0470588244497776f, 0.5400000214576721f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.1882352977991104f, 0.1882352977991104f, 0.1882352977991104f, 0.5400000214576721f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.2000000029802322f, 0.2196078449487686f, 0.2274509817361832f, 1.0f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.0f, 0.0f, 0.0f, 0.5199999809265137f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.0f, 0.0f, 0.0f, 0.3600000143051147f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.2000000029802322f, 0.2196078449487686f, 0.2274509817361832f, 0.3300000131130219f);
	style.Colors[ImGuiCol_Separator] = ImVec4(0.2784313857555389f, 0.2784313857555389f, 0.2784313857555389f, 0.2899999916553497f);
	style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.4392156898975372f, 0.4392156898975372f, 0.4392156898975372f, 0.2899999916553497f);
	style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.4000000059604645f, 0.4392156898975372f, 0.4666666686534882f, 1.0f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.2784313857555389f, 0.2784313857555389f, 0.2784313857555389f, 0.2899999916553497f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.4392156898975372f, 0.4392156898975372f, 0.4392156898975372f, 0.2899999916553497f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.4000000059604645f, 0.4392156898975372f, 0.4666666686534882f, 1.0f);
	style.Colors[ImGuiCol_Tab] = ImVec4(0.0f, 0.0f, 0.0f, 0.5199999809265137f);
	style.Colors[ImGuiCol_TabHovered] = ImVec4(0.1372549086809158f, 0.1372549086809158f, 0.1372549086809158f, 1.0f);
	style.Colors[ImGuiCol_TabActive] = ImVec4(0.2000000029802322f, 0.2000000029802322f, 0.2000000029802322f, 0.3600000143051147f);
	style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.0f, 0.0f, 0.0f, 0.5199999809265137f);
	style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.1372549086809158f, 0.1372549086809158f, 0.1372549086809158f, 1.0f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.5199999809265137f);
	style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.0f, 0.0f, 0.0f, 0.5199999809265137f);
	style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.2784313857555389f, 0.2784313857555389f, 0.2784313857555389f, 0.2899999916553497f);
	style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.0f, 1.0f, 1.0f, 0.05999999865889549f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.2000000029802322f, 0.2196078449487686f, 0.2274509817361832f, 1.0f);
	style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.3294117748737335f, 0.6666666865348816f, 0.8588235378265381f, 1.0f);
	style.Colors[ImGuiCol_NavHighlight] = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.0f, 0.0f, 0.0f, 0.699999988079071f);
	style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(1.0f, 0.0f, 0.0f, 0.2000000029802322f);
	style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(1.0f, 0.0f, 0.0f, 0.3499999940395355f);
}

Sabre::Entity CreateEntityDefault(Sabre::Scene* m_Scene, std::string& tag)
{
	Sabre::Entity entity = m_Scene->AddEntity();
	m_Scene->AddComponent<Sabre::TransformComponent>(entity, glm::vec3(), glm::vec3(), glm::vec3(1));
	m_Scene->AddComponent<Sabre::TagComponent>(entity, tag);

	return entity;
}

EditorLayer::EditorLayer(int argc, char* argv[]) : Layer(argc, argv), m_Camera({ 0.0f, 0.0f, 5.0f }, { 0.0f, 0.0f, 0.0f }, 45, true, 0.1f, 100.0f)
{

}

EditorLayer::~EditorLayer()
{
#ifdef API_GL41
	ImGui_ImplOpenGL3_Shutdown();
#endif
#ifdef WINDOWS
	ImGui_ImplGlfw_Shutdown();
#endif
	ImGui::DestroyContext();

}

void EditorLayer::OnInit()
{
	SABRE_LOG(Severity::Debug, "Sabre Engine Initialising");
	SABRE_LOG(Severity::Debug, "Version: {}.{}.{}", SABRE_VERSION_MAJOR, SABRE_VERSION_MINOR, SABRE_VERSION_PATCH);
#ifdef API_GL41
	SABRE_LOG(Severity::Debug, "Using API: OpenGL 4.1");
#endif

	m_CurrentProject = Sabre::Project("", "");

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();


	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	ImGui::StyleColorsDark();
	SetupImGuiStyle();

	m_NormalFont = io.Fonts->AddFontFromFileTTF(Sabre::GetAssetFile("Assets/Fonts/Roboto-Regular.ttf").string().c_str(), 15);
	m_BoldFont = io.Fonts->AddFontFromFileTTF(Sabre::GetAssetFile("Assets/Fonts/Roboto-Bold.ttf").string().c_str(), 15);
	io.FontDefault = m_NormalFont;

#ifdef WINDOWS
#ifdef API_GL41
	ImGui_ImplGlfw_InitForOpenGL(Sabre::Window::m_Window, true);
#endif
#endif

#ifdef API_GL41
	ImGui_ImplOpenGL3_Init("#version 130");
#endif
	m_SunLight = Sabre::SunLight(glm::normalize(glm::vec3(0.3f, 1.0f, 0.5f)), glm::vec3(1, 1, 1), 1, 0.1f);
	Sabre::SetSunLight(&m_SunLight);

	Sabre::g_MainCamera = &m_Camera;

	m_Scene.OnInit();
}

void EditorLayer::OnUpdate()
{
	static float s_MouseSensitivity = 0.15f;
	static float s_ScrollSpeed = 70.5f;
	static bool s_FirstMouse = true;
	static glm::vec2 s_LastMousePos(0.0f);
	static bool s_FirstMouseRotate = true;
	static bool s_FirstMousePan = true;

	static glm::vec2 s_LastMousePosRotate(0.0f);
	static glm::vec2 s_LastMousePosPan(0.0f);

	if (Sabre::Window::IsMouseDown(SABRE_MOUSE_BUTTON_RIGHT))
	{
		auto pos = Sabre::Window::GetMousePosition();
		glm::vec2 mousePos(pos.x, pos.y);

		if (s_FirstMouseRotate)
		{
			s_LastMousePosRotate = mousePos;
			s_FirstMouseRotate = false;
		}

		glm::vec2 delta = mousePos - s_LastMousePosRotate;
		s_LastMousePosRotate = mousePos;

		m_Camera.Rotation.y += delta.x * s_MouseSensitivity;
		m_Camera.Rotation.x -= delta.y * s_MouseSensitivity;
		m_Camera.Rotation.x = glm::clamp(m_Camera.Rotation.x, -89.0f, 89.0f);
	}
	else
	{
		s_FirstMouseRotate = true;
	}


	glm::vec3 eulerDegrees(
		m_Camera.Rotation.x,
		m_Camera.Rotation.y,
		0.0f
	);

	glm::vec3 eulerRadians = glm::radians(eulerDegrees);

	float pitch = eulerRadians.x;
	float yaw = eulerRadians.y;

	glm::vec3 forward;
	forward.x = std::cos(pitch) * std::sin(yaw);
	forward.y = std::sin(pitch);
	forward.z = -std::cos(pitch) * std::cos(yaw);

	forward = glm::normalize(forward);

	glm::vec3 worldUp(0.0f, 1.0f, 0.0f);

	glm::vec3 right = glm::normalize(glm::cross(forward, worldUp));
	glm::vec3 up = glm::normalize(glm::cross(right, forward));
	static float s_PanSensitivity = 0.01f;

	if (Sabre::Window::IsMouseDown(SABRE_MOUSE_BUTTON_MIDDLE))
	{
		auto pos = Sabre::Window::GetMousePosition();
		glm::vec2 mousePos(pos.x, pos.y);

		if (s_FirstMousePan)
		{
			s_LastMousePosPan = mousePos;
			s_FirstMousePan = false;
		}

		glm::vec2 delta = mousePos - s_LastMousePosPan;
		s_LastMousePosPan = mousePos;

		m_Camera.Position -= right * delta.x * s_PanSensitivity;
		m_Camera.Position += up    * delta.y * s_PanSensitivity;
	}
	else
	{
		s_FirstMousePan = true;
	}

	m_Camera.Position +=
		forward * (float)Sabre::Window::GetScrollOffset() * s_ScrollSpeed * (float)Sabre::Window::GetDeltaTime();

	m_Scene.OnUpdate();

	Sabre::Renderer::ClearScreen(m_Scene.ClearColour);

	DrawImGui();
}

void EditorLayer::OnRender()
{
	m_Scene.OnRender();
}

void EditorLayer::DrawImGui()
{
	if (m_ProjectCreated)
	{
		static bool show_demo_window = true;

		if (show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);

		static bool s_OpenSavePopup = false;
		static bool s_OpenLoadPopup = false;

		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("Sabre"))
			{
				if (ImGui::MenuItem("Save Level"))
					s_OpenSavePopup = true;
				if (ImGui::MenuItem("Load Level"))
					s_OpenLoadPopup = true;
				if (ImGui::MenuItem("Close"))
					Sabre::Window::RequestQuit();
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Scene"))
			{
				if (ImGui::MenuItem("Add Entity"))
					CreateEntityDefault(&m_Scene, m_DefaultTag);
				ImGui::EndMenu();
			}



			ImGui::EndMainMenuBar();
		}
		
		if (s_OpenSavePopup)
		{
			ImGui::OpenPopup("SaveLevelPopup");
			s_OpenSavePopup = false;
		}

		if (s_OpenLoadPopup)
		{
			ImGui::OpenPopup("LoadLevelPopup");
			s_OpenLoadPopup = false;
		}

		if (ImGui::BeginPopupModal("SaveLevelPopup"))
		{
			static char scene[260] = {};
			ImGui::Text("Scene"); ImGui::SameLine();
			ImGui::InputText("###scenepath", scene, 260);

			std::filesystem::path scenePath = std::string(scene);

			if (ImGui::Button("Save!"))
			{
				m_Scene.Serialize(scenePath, m_CurrentProject);
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}

		if (ImGui::BeginPopupModal("LoadLevelPopup"))
		{
			static char scene[260] = {};
			ImGui::Text("Scene"); ImGui::SameLine();
			ImGui::InputText("###scenepath", scene, 260);

			std::filesystem::path scenePath = std::string(scene);

			if (ImGui::Button("Load!"))
			{
				m_Scene.Deserialize(scenePath, m_CurrentProject);
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}


		ImGui::Begin("Scene Settings");

		float colour[4] = { m_Scene.ClearColour.r, m_Scene.ClearColour.g, m_Scene.ClearColour.b, m_Scene.ClearColour.a };

		ImGui::Text("Clear Colour: ");
		ImGui::SameLine();
		ImGui::ColorEdit4("###m_Sceneclearcolour", colour);

		ImGui::Text("Ambient: ");
		ImGui::SameLine();
		ImGui::DragFloat("###m_Sceneambient", &m_SunLight.AmbientIntensity, 0.025f);

		m_Scene.ClearColour.r = colour[0];
		m_Scene.ClearColour.g = colour[1];
		m_Scene.ClearColour.b = colour[2];
		m_Scene.ClearColour.a = colour[3];

		ImGui::PushFont(m_BoldFont);
		if (ImGui::CollapsingHeader("Sun Light"))
		{
			ImGui::PopFont();

			ImGui::Text("Colour "); ImGui::SameLine();
			ImGui::ColorEdit3("###sabcollightm_Scene", glm::value_ptr(Sabre::GetSunLight()->Colour));

			Sabre::InputVec3("Direction", (int32_t)(&Sabre::GetSunLight()->Direction), 0.001f, Sabre::GetSunLight()->Direction);

			ImGui::Text("Intensity "); ImGui::SameLine();
			ImGui::DragFloat("###sabintlightm_Scene", &Sabre::GetSunLight()->Intensity, 0.01f, 0, 5);
		}
		else
		{ 
			ImGui::PopFont();
		}

		ImGui::End();

		ImGui::PushFont(m_NormalFont);

		ImGui::Begin("Scene");

		for (Sabre::UUID entity : m_Scene.GetAllEntities())
		{
			Sabre::Entity asEntity = m_Scene.GetEntity(entity);
			std::string& tag = m_Scene.GetComponent<Sabre::TagComponent>(asEntity).Tag;

			ImGui::PushID(entity);

			if (ImGui::Selectable(tag.c_str(), entity == m_SelectedEntity))
			{
				m_SelectedEntity = entity;
			}
			ImGui::PopID();

		}
		ImGui::PopFont();

		ImGui::End();

		ImGui::Begin("Inspector");

		if (m_SelectedEntity != 0xFFFFFF)
		{
			ImGui::PushFont(m_BoldFont);

			Sabre::Entity asEntity = m_Scene.GetEntity(m_SelectedEntity);
			auto& tagC = m_Scene.GetComponent<Sabre::TagComponent>(asEntity);

			Sabre::InputChar("###sabentitytag", &tagC.Tag);


			ImGui::PopFont();

			auto& transform = m_Scene.GetComponent<Sabre::TransformComponent>(asEntity);
			Sabre::TransformComponent::RenderImGui(transform, m_CurrentProject);

			if (m_Scene.HasComponent<Sabre::MeshComponent>(asEntity))
			{
				Sabre::MeshComponent::RenderImGui(m_Scene.GetComponent<Sabre::MeshComponent>(asEntity), m_CurrentProject);
			}

			auto& style = ImGui::GetStyle();
			float textWidth = ImGui::CalcTextSize("Add Component").x + style.FramePadding.x;

			ImGui::SetCursorPosX((ImGui::GetWindowWidth() / 2) - (textWidth / 2));

			if (ImGui::Button("Add Component"))
			{
				ImGui::OpenPopup("AddComponentPopup");
			}

			if (ImGui::BeginPopup("AddComponentPopup"))
			{
				if (ImGui::Button("Mesh Component"))
				{
					m_Scene.AddComponent<Sabre::MeshComponent>(asEntity, asEntity, m_CurrentProject.FilePath, "", "", 0, 0);
				}

				ImGui::EndPopup();
			}

		}
		ImGui::End();
	}
	else
	{
		ImGui::Begin("Select Project");

		ImGui::Text("No project loaded! Please select one.");

		std::string filePathStr = m_CurrentProject.FilePath.string();
		char bufP[260] = {};
		std::strncpy(bufP, filePathStr.c_str(), sizeof(bufP) - 1);

		ImGui::Text("Project Path "); ImGui::SameLine();
		ImGui::InputText("###projpath", bufP, 260);

		m_CurrentProject.FilePath = std::string(bufP);

		std::string nameStr = m_CurrentProject.Name.data();
		char bufN[260] = {};
		std::strncpy(bufN, nameStr.c_str(), sizeof(bufN) - 1);

		ImGui::Text("Project Name "); ImGui::SameLine();
		ImGui::InputText("###projnam", bufN, 260);

		m_CurrentProject.Name = std::string(bufN);

		if (ImGui::Button("Load!"))
		{
			m_ProjectCreated = true;
		}

		ImGui::End();
	}
}
