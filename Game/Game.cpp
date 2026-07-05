#include "Game.h"

// Project Includes
#include "MiniginEngine.h"
#include "TestScene.h"

dae::Game::Game() = default;

void dae::Game::Start()
{
	test::LoadTestScene();
}

void dae::Game::Update()
{

}