#include <iostream>
using namespace std;

#include "GameStateManager.h"
#include "highscorestate.h"
#include "optionstate.h"
#include "playstate.h"
#include "gamestate.h"
#include "menustate.h"

CMenuState CMenuState::theMenuState;

void CMenuState::Init()
{
	theScene = new CSceneManager2D(800, 600);
	theScene->Init();
}

void CMenuState::Init(const int width, const int height)
{
	theScene = new CSceneManager2D(800, 600);
	theScene->Init();
}

void CMenuState::Cleanup()
{
	theScene->Exit();
	delete theScene;
	theScene = NULL;
}

void CMenuState::Pause()
{
}

void CMenuState::Resume()
{
}

void CMenuState::HandleEvents(CGameStateManager* theGSM)
{
}

void CMenuState::HandleEvents(CGameStateManager* theGSM, const unsigned char key, const bool status)
{
}

void CMenuState::HandleEvents(CGameStateManager* theGSM, const double mouse_x, const double mouse_y,
							  const int button_Left, const int button_Middle, const int button_Right)
{
}

void CMenuState::Update(CGameStateManager* theGSM) 
{
}

void CMenuState::Update(CGameStateManager* theGSM, const double m_dElapsedTime)
{

#if GSM_DEBUG_MODE
#endif

	if (Application::IsKeyPressed(VK_DOWN))
	{
		if (Select < 4) // Max. Number of Options
		{
			Select++;	// Move the cursor down
			Sleep(150);

		}
	}
	if (Application::IsKeyPressed(VK_UP))
	{
		if (Select > 0) // Selection is not the first one.
		{
			Select--;
			Sleep(150);
		}
	}

	if (Select == 1)
	{
		theScene->PlaySelect = true;
		theScene->HighscoreSelect = false;
		theScene->OptionSelect = false;
		theScene->ExitSelect = false;
	}
	else if (Select == 2)
	{
		theScene->PlaySelect = false;
		theScene->HighscoreSelect = true;
		theScene->OptionSelect = false;
		theScene->ExitSelect = false;
	}
	else if (Select == 3)
	{
		theScene->PlaySelect = false;
		theScene->HighscoreSelect = false;
		theScene->OptionSelect = true;
		theScene->ExitSelect = false;
	}
	else if (Select == 4)
	{
		theScene->PlaySelect = false;
		theScene->HighscoreSelect = false;
		theScene->OptionSelect = false;
		theScene->ExitSelect = true;
	}

	if (Application::IsKeyPressed(VK_RETURN) || Application::IsKeyPressed(VK_SPACE))
	{
		if (Select == 1)
		{
			theGSM->ChangeState(CPlayState::Instance());
		}
		if (Select == 2)
		{
			theGSM->ChangeState(CHighscoreState::Instance());
		}
		if (Select == 3)
		{
			theGSM->ChangeState(COptionState::Instance());
		}
		if (Select == 4)
		{
			exit(0);
		}
	}
}

void CMenuState::Draw(CGameStateManager* theGSM) 
{
	theScene->RenderMainMenu();
}
