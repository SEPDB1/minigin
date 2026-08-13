#include "Level.h"
#include "Map.h"
#include "Renderer.h"

dae::Level::Level()
	: m_Map{ std::make_unique<Map>("Json/MainMap.json") }
{
	SDLRenderer::GetInstance().SetBackgroundColor(0, 255, 0, 255);
}

dae::Level::~Level() = default;
