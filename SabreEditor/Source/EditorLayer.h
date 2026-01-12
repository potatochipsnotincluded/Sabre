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
	std::string m_DefaultTag = "New Entity";
	Sabre::SunLight m_SunLight;
	Sabre::Camera m_Camera;

	glm::vec4 m_ClearColour;
	
	Sabre::Scene m_Scene;

	ImFont* m_NormalFont;
	ImFont* m_BoldFont;

	bool m_ShouldClose = false;
};