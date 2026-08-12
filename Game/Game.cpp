#include "Game.h"
#include "GameState.h"

dae::Game::Game()
	: m_pCurrentState{ std::make_unique<GameState>() }
{
}

dae::Game::~Game() = default;

void dae::Game::Start()
{
	
}

void dae::Game::Update()
{
	m_pCurrentState->Update();
}