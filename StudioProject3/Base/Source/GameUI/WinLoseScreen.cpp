#include "WinLoseScreen.h"
#include "GL\glew.h"
#include "GLFW\glfw3.h"

#include "../Application.h"
#include "GraphicsManager.h"
#include "MeshBuilder.h"
#include "Mesh.h"
#include "LoadTGA.h"
#include "../EntityManager.h"
#include "MouseController.h"

WinLoseScreen* WinLoseScreen::sInstance = new WinLoseScreen(SceneManager::GetInstance());
extern GLFWwindow* m_window;


WinLoseScreen::WinLoseScreen()
{
}

WinLoseScreen::WinLoseScreen(SceneManager * _sceneMgr) :
	theWinLoseState(WIN),
	Win_Background(NULL),
	Level(""),
	m_bSwitchLevel(false),
	m_fTimeBeforeLevelChange(4.f),
	States(0)
{
	_sceneMgr->AddScene("WinLoseScreen", this);
}

WinLoseScreen::~WinLoseScreen()
{
	if (Win_Background)
	{
		delete Win_Background;
		Win_Background = NULL;
	}
}

void WinLoseScreen::SetStates(int WinLoseState)
{
	switch (WinLoseState)
	{
	case 0:
	{
		theWinLoseState = WIN_LOSE_STATE::WIN;
		States = WinLoseState;
		break;
	}
	case 1:
	{
		theWinLoseState = WIN_LOSE_STATE::LOSE;
		States = WinLoseState;
		break;
	}
	}
}

int WinLoseScreen::GetStates()
{
	return States;
}

void WinLoseScreen::SetLevel(string Level)
{
	this->Level = Level;
}

string WinLoseScreen::GetLevel()
{
	return Level;
}

void WinLoseScreen::SetSwitchLevel(bool is_True)
{
	this->m_bSwitchLevel = is_True;
}

bool WinLoseScreen::GetSwitchLevel()
{
	return m_bSwitchLevel;
}

void WinLoseScreen::Init()
{
	m_worldHeight = (float)Application::GetWindowHeight();
	m_worldWidth = (float)Application::GetWindowWidth();

	currProg = GraphicsManager::GetInstance()->LoadShader("default", "Shader//Texture.vertexshader", "Shader//Texture.fragmentshader");
	// Tell the graphics manager to use the shader we just loaded
	GraphicsManager::GetInstance()->SetActiveShader("default");

	// Win Background
	MeshBuilder::GetInstance()->GenerateQuad("WIN_BACKGROUND", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GetMesh("WIN_BACKGROUND")->textureID = LoadTGA("Image//WinScreen.tga");

	Win_Background = Create::Sprite2DObject("WIN_BACKGROUND",
		Vector3(m_worldWidth * 0.f, m_worldHeight * 0.f, 0.f),
		Vector3(m_worldWidth, m_worldHeight, 0.f), true);

	// Lose Background
	MeshBuilder::GetInstance()->GenerateQuad("LOSE_BACKGROUND", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GetMesh("LOSE_BACKGROUND")->textureID = LoadTGA("Image//LoseScreen.tga");

	Lose_Background = Create::Sprite2DObject("LOSE_BACKGROUND",
		Vector3(m_worldWidth * 0.f, m_worldHeight * 0.f, 0.f),
		Vector3(m_worldWidth, m_worldHeight, 0.f), true);

	//Creating textOBj
	float fontSize = 80.0f;

	textObj[0] = Create::Text2DObject("text", Vector3(0 - 80.f, m_worldHeight * -0.15f, 2.f), "", Vector3(fontSize, fontSize, fontSize), Color(1.0f, 0.0f, 0.0f));

}

void WinLoseScreen::Update(double dt)
{
	EntityManager::GetInstance()->Update(dt);

	m_worldHeight = (float)Application::GetWindowHeight();
	m_worldWidth = (float)Application::GetWindowWidth();

	switch (theWinLoseState)
	{
	case WIN:
	{
		Win_Background->SetPosition(Vector3(m_worldWidth * 0.f, m_worldHeight * 0.f, 1.f));
		Lose_Background->SetPosition(Vector3(m_worldWidth * 0.f, m_worldHeight * 0.f, 0.f));

		break;
	}
	case LOSE:
	{
		Win_Background->SetPosition(Vector3(m_worldWidth * 0.f, m_worldHeight * 0.f, 0.f));
		Lose_Background->SetPosition(Vector3(m_worldWidth * 0.f, m_worldHeight * 0.f, 1.f));

		break;
	}
	}

	if (GetSwitchLevel())
	{
		m_fTimeBeforeLevelChange -= (float)dt;

		std::ostringstream ss;
		ss.precision(1);
		ss << m_fTimeBeforeLevelChange;
		textObj[0]->SetText(ss.str());

		if (GetLevel() == "1" && GetStates() == 1)
		{
			if (m_fTimeBeforeLevelChange < 1.f)
			{
				SceneManager::GetInstance()->SetActiveScene("Level1");
				m_fTimeBeforeLevelChange = 4.f;
				m_bSwitchLevel = false;
			}
		}
		else if (GetLevel() == "2" && GetStates() == 1)
		{
			if (m_fTimeBeforeLevelChange < 1.f)
			{
				SceneManager::GetInstance()->SetActiveScene("Level2");
				m_fTimeBeforeLevelChange = 4.f;
				m_bSwitchLevel = false;
			}
		}
		else if (GetLevel() == "3" && GetStates() == 1)
		{
			if (m_fTimeBeforeLevelChange < 1.f)
			{
				SceneManager::GetInstance()->SetActiveScene("Level3");
				m_fTimeBeforeLevelChange = 4.f;
				m_bSwitchLevel = false;
			}
		}
		else if (GetLevel() == "4"  && GetStates() == 1)
		{
			if (m_fTimeBeforeLevelChange < 1.f)
			{
				SceneManager::GetInstance()->SetActiveScene("Level4");
				m_fTimeBeforeLevelChange = 4.f;
				m_bSwitchLevel = false;
			}
		}
		else if (GetLevel() == "4" && GetStates() == 0)
		{
			if (m_fTimeBeforeLevelChange < 1.f)
			{
				SceneManager::GetInstance()->SetActiveScene("Screen");
				m_fTimeBeforeLevelChange = 4.f;
				m_bSwitchLevel = false;
			}
		}
	}
}

void WinLoseScreen::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_BLEND);

	int halfWindowWidth = Application::GetInstance().GetWindowWidth() / 2;
	int halfWindowHeight = Application::GetInstance().GetWindowHeight() / 2;

	GraphicsManager::GetInstance()->SetOrthographicProjection(-halfWindowWidth, halfWindowWidth, -halfWindowHeight, halfWindowHeight, -10, 10);
	GraphicsManager::GetInstance()->DetachCamera();
	EntityManager::GetInstance()->RenderUI();

	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();

	glDisable(GL_BLEND);
}

void WinLoseScreen::Exit()
{
	GraphicsManager::GetInstance()->DetachCamera();
	EntityManager::GetInstance()->ClearEntityList();
}
