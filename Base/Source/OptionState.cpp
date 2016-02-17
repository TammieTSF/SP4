#include <iostream>
using namespace std;

#include "GameStateManager.h"
#include "optionstate.h"
#include "menustate.h"

COptionState COptionState::theMenuState;

void COptionState::Init()
{

}

void COptionState::Init(const int width, const int height)
{

}

void COptionState::Cleanup()
{

}

void COptionState::Pause()
{

}

void COptionState::Resume()
{

}

void COptionState::HandleEvents(CGameStateManager* theGSM)
{}

void COptionState::HandleEvents(CGameStateManager* theGSM, const unsigned char key, const bool status)
{}

void COptionState::HandleEvents(CGameStateManager* theGSM, const double mouse_x, const double mouse_y,
	const int button_Left, const int button_Middle, const int button_Right)
{}

void COptionState::Update(CGameStateManager* theGSM)
{

}

void COptionState::Update(CGameStateManager* theGSM, const double m_dElapsedTime)
{
}

void COptionState::Draw(CGameStateManager* theGSM)
{

}
