#pragma once
#include <nlohmann/json.hpp>
#include <fstream>

namespace dae
{
    template <typename T>
    static T ParseData(const std::string& jsonFile)
    {
        std::ifstream f(jsonFile);
        if (!f.is_open())
            throw std::runtime_error("Could not open file: " + jsonFile);

        try
        {
            return nlohmann::json::parse(f).get<T>();
        }
        catch (const nlohmann::json::exception& e)
        {
            throw std::runtime_error("JSON parse error in " + jsonFile + ": " + e.what());
        }
    }
}