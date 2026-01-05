#pragma once
#include "Sabre/Texture.h"

#include <filesystem>

namespace Sabre {

	struct Material
	{
		Texture Albedo;
		float Smoothness;
		float Metallic;

		Material(const std::filesystem::path& albedoPath, float smoothness, float metallic) : Albedo(albedoPath) {
			Smoothness = smoothness;
			Metallic = metallic;
		}
	};

}