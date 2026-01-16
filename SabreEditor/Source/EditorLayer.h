#include "Sabre/Sabre.h"
#include "Sabre/Application.h"

class EditorLayer : public Sabre::Layer
{
public:
	EditorLayer(int argc, char* argv[]);
	virtual ~EditorLayer() override;

	virtual void OnInit() override;
	virtual void OnUpdate() override;
	virtual void OnRender() override;
private:
	void DrawImGui();

	void Serialize(const std::filesystem::path& scenePath);
	void Deserialize(const std::filesystem::path& scenePath);
private:
	std::string m_DefaultTag = "New Entity";
	Sabre::SunLight m_SunLight;
	Sabre::Camera m_Camera;

	glm::vec4 m_ClearColour;
	
	Sabre::Scene m_Scene;

	Sabre::UUID m_SelectedEntity = 0xFFFFFF;

	ImFont* m_NormalFont;
	ImFont* m_BoldFont;

	bool m_ShouldClose = false;

	Sabre::Project m_CurrentProject;

	bool m_ProjectCreated = false;
};