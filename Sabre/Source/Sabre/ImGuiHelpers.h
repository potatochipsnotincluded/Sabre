#pragma once
#include "imgui/imgui.h"

#include "glm/glm.hpp"

#include <string>

namespace Sabre {

	inline void InputChar(std::string_view label, std::string* str)
	{
		char buffer[260] = {};
		std::strncpy(buffer, str->c_str(), sizeof(buffer) - 1);

		if (ImGui::InputText(label.data(), buffer, sizeof(buffer)))
		{
			*str = buffer;
		}
	}

	inline void InputVec3(std::string_view label, int32_t ID, float delta, glm::vec3& value)
	{
		ImGui::Text(label.data()); ImGui::SameLine();


		ImVec4 red = ImVec4(1.0f, 0.13f, 0.13f, 1.0f);
		ImVec4 green = ImVec4(0.13f, 1.0f, 0.22f, 1.0f);
		ImVec4 blue = ImVec4(0.19f, 0.54f, 1.0f, 1.0f);

		ImGui::PushStyleColor(ImGuiCol_Button, red);
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, red);
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, red);

		ImGui::PushID(ID+3);
		ImGui::SmallButton("X"); ImGui::SameLine();
		ImGui::PopID();

		ImGui::PopStyleColor(3);

		ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.15f);
		ImGui::PushID(ID); ImGui::DragFloat("###inputvec3x", &value.x, delta); ImGui::PopID(); ImGui::SameLine();
		ImGui::PopItemWidth();

		ImGui::PushStyleColor(ImGuiCol_Button, green);
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, green);
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, green);

		ImGui::PushID(ID + 4);
		ImGui::SmallButton("Y"); ImGui::SameLine();
		ImGui::PopID();

		ImGui::PopStyleColor(3);

		ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.15f);
		ImGui::PushID(ID + 1); ImGui::DragFloat("###inputvec3y", &value.y, delta); ImGui::PopID(); ImGui::SameLine();
		ImGui::PopItemWidth();

		ImGui::PushStyleColor(ImGuiCol_Button, blue);
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, blue);
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, blue);

		ImGui::PushID(ID + 5);
		ImGui::SmallButton("Z"); ImGui::SameLine();
		ImGui::PopID();

		ImGui::PopStyleColor(3);

		ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.15f);
		ImGui::PushID(ID+2); ImGui::DragFloat("###inputvec3z", &value.z, delta); ImGui::PopID();
		ImGui::PopItemWidth();
	}

}