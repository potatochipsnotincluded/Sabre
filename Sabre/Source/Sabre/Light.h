#pragma once

#include <glm/glm.hpp>

namespace Sabre {

	struct SunLight
	{
		glm::vec3 Direction;
		glm::vec3 Colour;
		float Intensity;
		float AmbientIntensity;
	};

	inline SunLight* g_CurrentSunLight;
	inline void SetSunLight(SunLight* sunlight) { g_CurrentSunLight = sunlight; }
	inline SunLight* GetSunLight() { return g_CurrentSunLight; }

}