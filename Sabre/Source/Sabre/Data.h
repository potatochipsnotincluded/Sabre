#pragma once
#include "Debug.h"

#include <string>
#include <filesystem>
#include <fstream>
#include <sstream>

// No one will ever know . . . heh heh heh

namespace Sabre {

    template <typename To, typename From>
    inline constexpr To StaticCast(From value)
    {
        return (To)value; // Shhh
    }

    template <typename To, typename From>
    inline constexpr To* ReinterpretPtr(From* value)
    {
        return (To*)value;
    }

    template <typename To, typename From>
    inline constexpr To& StaticRefCast(From& value)
    {
        return (To&)value;
    }

    inline std::string LoadFile(std::filesystem::path filepath)
    {
        std::ifstream file = std::ifstream(filepath);
        if (!file.is_open())
        {
            SABRE_LOG(Severity::Error, "Could not open file {}, maybe try harder?", filepath.string());
            return "";
        }
        std::stringstream ss;
        ss << file.rdbuf();
        return ss.str();
    }

    inline std::filesystem::path GetAssetFile(std::filesystem::path filepath)
    {
        return std::filesystem::path(SOLUTION_DIR) / (filepath);
    }

}