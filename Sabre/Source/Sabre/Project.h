#pragma once
#include <filesystem>

namespace Sabre {

	struct Project
	{
		std::filesystem::path FilePath;
		std::string Name;
	};

}