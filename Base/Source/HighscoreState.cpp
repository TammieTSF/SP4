#include <iostream>
using namespace std;

#include "GameStateManager.h"
#include "menustate.h"
#include "highscorestate.h"

CHighscoreState CHighscoreState::theIntroState;

void CHighscoreState::Init()
{
}

void CHighscoreState::Init(const int width, const int height)
{
}

void CHighscoreState::Cleanup()
{
}

void CHighscoreState::Pause()
{
}

void CHighscoreState::Resume()
{
}

void CHighscoreState::HandleEvents(CGameStateManager* theGSM)
{
}

void CHighscoreState::HandleEvents(CGameStateManager* theGSM, const unsigned char key, const bool status)
{
}

void CHighscoreState::HandleEvents(CGameStateManager* theGSM, const double mouse_x, const double mouse_y,
							   const int button_Left, const int button_Middle, const int button_Right)
{
}

void CHighscoreState::Update(CGameStateManager* theGSM) 
{
}

void CHighscoreState::Update(CGameStateManager* theGSM, const double m_dElapsedTime)
{
}

void CHighscoreState::Draw(CGameStateManager* theGSM) 
{
}
