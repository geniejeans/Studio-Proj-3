#include "Screen.h"
#include "GL\glew.h"
#include "GLFW\glfw3.h"

#include "GraphicsManager.h"
#include "MeshBuilder.h"
#include "Mesh.h"
#include "SpriteEntity.h"
#include "LoadTGA.h"
#include "Application.h"
#include "EntityManager.h"
#include "MouseController.h"

#include <iostream>
using namespace std;

Screen* Screen::sInstance = new Screen(SceneManager::GetInstance());
extern GLFWwindow* m_window;


Screen::Screen()
{
}

Screen::Screen(SceneManager* _sceneMgr) :
	theScreenState(MAIN_MENU),
	MainMenu_Background(NULL),
	Instructions_Background(NULL),
	Credits_Background(NULL),
	StartButton(NULL),
	InstructionsButton(NULL),
	CreditButton(NULL),
	QuitButton(NULL),
	StartButtonPos(0.f, 0.f, 0.f),
	InstructionsButtonPos(0.f, 0.f, 0.f),
	CreditsButtonPos(0.f, 0.f, 0.f),
	QuitButtonPos(0.f, 0.f, 0.f),
	StartButtonScale(1.f, 1.f, 1.f),
	InstructionsButtonScale(1.f, 1.f, 1.f),
	CreditsButtonScale(1.f, 1.f, 1.f),
	QuitButtonScale(1.f, 1.f, 1.f),
	isWithin(false),
	StartButtonScaleOffset(0.f, 0.f, 0.f),
	InstructionsButtonScaleOffset(0.f, 0.f, 0.f),
	CreditsButtonScaleOffset(0.f, 0.f, 0.f),
	QuitButtonScaleOffset(0.f, 0.f, 0.f),
	StartGameButtonCondition(0.f),
	InstructionsButtonCondition(0.f),
	CreditsButtonCondition(0.f),
	QuitButtonCondition(0.f),
	mousePos(0.f, 0.f, 0.f),
	x_pos(0.f),
	y_pos(0.f)
{
	_sceneMgr->AddScene("Screen", this);
}

Screen::~Screen()
{
	if (MainMenu_Background)
	{
		delete MainMenu_Background;
		MainMenu_Background = NULL;
	}
}

void Screen::Init()
{
	m_worldHeight = (float)Application::GetWindowHeight();
	m_worldWidth = (float)Application::GetWindowWidth();

	currProg = GraphicsManager::GetInstance()->LoadShader("default", "Shader//Texture.vertexshader", "Shader//Texture.fragmentshader");
	// Tell the graphics manager to use the shader we just loaded
	GraphicsManager::GetInstance()->SetActiveShader("default");

	// Main Menu Background
	MeshBuilder::GetInstance()->GenerateQuad("MAIN_MANU_BACKGROUND", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GetMesh("MAIN_MANU_BACKGROUND")->textureID = LoadTGA("Image//MainMenu.tga");

	// MainMenu Background
	MainMenu_Background = Create::Sprite2DObject("MAIN_MANU_BACKGROUND",
		Vector3(m_worldWidth * 0.f, m_worldHeight * 0.f, 1.f),
		Vector3(m_worldWidth, m_worldHeight, 0.f), true);

	// Main Menu Buttons/Selections
	// Start Game Option (Button)
	MeshBuilder::GetInstance()->GenerateQuad("START_GAME_OPTION", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GetMesh("START_GAME_OPTION")->textureID = LoadTGA("Image//StartGame_Option.tga");

	StartButtonPos.Set(m_worldWidth * 0.f, m_worldHeight * 0.f, 2.f);
	StartButtonScale.Set(200.f, 50.f, 1.f);

	StartButton = Create::Sprite2DObject("START_GAME_OPTION", Vector3(StartButtonPos.x, StartButtonPos.y, StartButtonPos.z),
		Vector3(StartButtonScale.x + StartButtonScaleOffset.x,
			StartButtonScale.y + StartButtonScaleOffset.y,
			StartButtonScale.z + StartButtonScaleOffset.z), true);


	// Instructions Background
	MeshBuilder::GetInstance()->GenerateQuad("INSTRUCTIONS_BACKGROUND", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GetMesh("INSTRUCTIONS_BACKGROUND")->textureID = LoadTGA("Image//InstructionScreen.tga");

	Instructions_Background = Create::Sprite2DObject("INSTRUCTIONS_BACKGROUND",
		Vector3(m_worldWidth * 0.f, m_worldHeight * 0.f, 0.f),
		Vector3(m_worldWidth, m_worldHeight, 1.f), true);

	// Instructions Buttons
	MeshBuilder::GetInstance()->GenerateQuad("INSTRUCTIONS_OPTION", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GetMesh("INSTRUCTIONS_OPTION")->textureID = LoadTGA("Image//Instructions_Option.tga");

	InstructionsButtonPos.Set(m_worldWidth * 0.f, m_worldHeight * -0.1f, 2.f);
	InstructionsButtonScale.Set(220.f, 50.f, 1.f);

	InstructionsButton = Create::Sprite2DObject("INSTRUCTIONS_OPTION", Vector3(InstructionsButtonPos.x, InstructionsButtonPos.y, InstructionsButtonPos.z),
		Vector3(InstructionsButtonScale.x + InstructionsButtonScaleOffset.x,
			InstructionsButtonScale.y + InstructionsButtonScaleOffset.y,
			InstructionsButtonScale.z + InstructionsButtonScaleOffset.z), true);


	// Credits Background
	MeshBuilder::GetInstance()->GenerateQuad("CREDITS_BACKGROUND", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GetMesh("CREDITS_BACKGROUND")->textureID = LoadTGA("Image//CreditsScreen.tga");

	Credits_Background = Create::Sprite2DObject("CREDITS_BACKGROUND",
		Vector3(m_worldWidth * 0.f, m_worldHeight * 0.f, 0.f),
		Vector3(m_worldWidth, m_worldHeight, 1.f), true);

	// Credits Buttons
	MeshBuilder::GetInstance()->GenerateQuad("CREDITS_OPTION", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GetMesh("CREDITS_OPTION")->textureID = LoadTGA("Image//Credits_Option.tga");

	CreditsButtonPos.Set(m_worldWidth * 0.f, m_worldHeight * -0.2f, 2.f);
	CreditsButtonScale.Set(150.f, 50.f, 1.f);

	CreditButton = Create::Sprite2DObject("CREDITS_OPTION", Vector3(CreditsButtonPos.x, CreditsButtonPos.y, CreditsButtonPos.z),
		Vector3(CreditsButtonScale.x + CreditsButtonScaleOffset.x,
			CreditsButtonScale.y + CreditsButtonScaleOffset.y,
			CreditsButtonScale.z + CreditsButtonScaleOffset.z), true);


	// Quit Button
	MeshBuilder::GetInstance()->GenerateQuad("QUIT_OPTION", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GetMesh("QUIT_OPTION")->textureID = LoadTGA("Image//Quit_Option.tga");

	QuitButtonPos.Set(m_worldWidth * 0.f, m_worldHeight * -0.3f, 2.f);
	QuitButtonScale.Set(80.f, 40.f, 1.f);

	QuitButton = Create::Sprite2DObject("QUIT_OPTION", Vector3(QuitButtonPos.x, QuitButtonPos.y, QuitButtonPos.z),
		Vector3(QuitButtonScale.x + QuitButtonScaleOffset.x,
			QuitButtonScale.y + QuitButtonScaleOffset.y,
			QuitButtonScale.z + QuitButtonScaleOffset.z), true);

}

void Screen::Update(double dt)
{
	EntityManager::GetInstance()->Update(dt);

	m_worldHeight = (float)Application::GetWindowHeight();
	m_worldWidth = (float)Application::GetWindowWidth();

	MouseController::GetInstance()->GetMousePosition(x_pos, y_pos);
	mousePos.Set((x_pos - 800 / 2), (y_pos - 600 / 2) * -1.f);

	switch (theScreenState)
	{
	case MAIN_MENU:
	{
		MainMenu_Background->SetPosition(Vector3(m_worldWidth * 0.f, m_worldHeight * 0.f, 1.f));
		StartButton->SetPosition(Vector3(StartButtonPos.x, StartButtonPos.y, 2.f));
		InstructionsButton->SetPosition(Vector3(InstructionsButtonPos.x, InstructionsButtonPos.y, 2.f));
		CreditButton->SetPosition(Vector3(CreditsButtonPos.x, CreditsButtonPos.y, 2.f));
		QuitButton->SetPosition(Vector3(QuitButtonPos.x, QuitButtonPos.y, 2.f));

		Instructions_Background->SetPosition(Vector3(m_worldWidth * 0.f, m_worldHeight * 0.f, 0.f));
		Credits_Background->SetPosition(Vector3(m_worldWidth * 0.f, m_worldHeight * 0.f, 0.f));

		UpdateStartButton();
		UpdateInstructionsButton();
		UpdateCreditsButton();
		UpdateQuitButton();

		break;
	}
	case INSTRUCTIONS:
	{
		Instructions_Background->SetPosition(Vector3(m_worldWidth * 0.f, m_worldHeight * 0.f, 3.f));

		break;
	}
	case CREDITS:
	{
		Credits_Background->SetPosition(Vector3(m_worldWidth * 0.f, m_worldHeight * 0.f, 3.f));

		break;
	}
	}

	if (MouseController::GetInstance()->IsButtonPressed(MouseController::RMB))
	{
		theScreenState = MAIN_MENU;
	}
}

void Screen::UpdateStartButton()
{
	// Start Button Condition
	StartGameButtonCondition = (mousePos.x >= (StartButtonPos.x - StartButtonScale.x * 0.5f)) &&
		(mousePos.x <= (StartButtonPos.x + StartButtonScale.x * 0.5f)) &&
		(mousePos.y >= (StartButtonPos.y - StartButtonScale.y * 0.5f)) &&
		(mousePos.y <= (StartButtonPos.y + StartButtonScale.y * 0.5f));

	// Checking is the mouse cursor is inside the start button.
	if (StartGameButtonCondition)
	{
		// The word will be bigger
		StartButtonScaleOffset.Set(10.f, 10.f, 10.f);
		StartButton->SetScale(Vector3(StartButtonScale.x + StartButtonScaleOffset.x,
			StartButtonScale.y + StartButtonScaleOffset.y,
			StartButtonScale.z + StartButtonScaleOffset.z));

		isWithin = true;
	}
	else
	{
		// Reset to original size.
		StartButtonScaleOffset.Set(0.f, 0.f, 0.f);
		StartButton->SetScale(Vector3(StartButtonScale.x + StartButtonScaleOffset.x,
			StartButtonScale.y + StartButtonScaleOffset.y,
			StartButtonScale.z + StartButtonScaleOffset.z));

		isWithin = false;
	}

	// If the mouse is inside, and the start button is press.
	if (isWithin == true && StartGameButtonCondition)
	{
		if (MouseController::GetInstance()->IsButtonPressed(MouseController::LMB))
		{
			SceneManager::GetInstance()->SetActiveScene("Start");
		}
	}
}

void Screen::UpdateInstructionsButton()
{
	// Instruction Button Condition
	InstructionsButtonCondition = (mousePos.x >= (InstructionsButtonPos.x - InstructionsButtonScale.x * 0.5f)) &&
		(mousePos.x <= (InstructionsButtonPos.x + InstructionsButtonScale.x * 0.5f)) &&
		(mousePos.y >= (InstructionsButtonPos.y - InstructionsButtonScale.y * 0.5f)) &&
		(mousePos.y <= (InstructionsButtonPos.y + InstructionsButtonScale.y * 0.5f));

	// Checking is the mouse cursor is inside the instruction button.
	if (InstructionsButtonCondition)
	{
		// The word will be bigger
		InstructionsButtonScaleOffset.Set(10.f, 10.f, 10.f);
		InstructionsButton->SetScale(Vector3(InstructionsButtonScale.x + InstructionsButtonScaleOffset.x,
			InstructionsButtonScale.y + InstructionsButtonScaleOffset.y,
			InstructionsButtonScale.z + InstructionsButtonScaleOffset.z));

		isWithin = true;
	}
	else
	{
		// Reset to original size.
		InstructionsButtonScaleOffset.Set(0.f, 0.f, 0.f);
		InstructionsButton->SetScale(Vector3(InstructionsButtonScale.x + InstructionsButtonScaleOffset.x,
			InstructionsButtonScale.y + InstructionsButtonScaleOffset.y,
			InstructionsButtonScale.z + InstructionsButtonScaleOffset.z));

		isWithin = false;
	}

	// If the mouse is inside, and the instruction button is press.
	if (isWithin == true && InstructionsButtonCondition)
	{
		if (MouseController::GetInstance()->IsButtonPressed(MouseController::LMB))
		{
			theScreenState = INSTRUCTIONS;
		}
	}

}

void Screen::UpdateCreditsButton()
{
	// Credit Button Condition
	CreditsButtonCondition = (mousePos.x >= (CreditsButtonPos.x - CreditsButtonScale.x * 0.5f)) &&
		(mousePos.x <= (CreditsButtonPos.x + CreditsButtonScale.x * 0.5f)) &&
		(mousePos.y >= (CreditsButtonPos.y - CreditsButtonScale.y * 0.5f)) &&
		(mousePos.y <= (CreditsButtonPos.y + CreditsButtonScale.y * 0.5f));

	// Checking if the mouse cursor is inside the button.
	if (CreditsButtonCondition)
	{
		// The word will be bigger
		CreditsButtonScaleOffset.Set(10.f, 10.f, 10.f);
		CreditButton->SetScale(Vector3(CreditsButtonScale.x + CreditsButtonScaleOffset.x,
			CreditsButtonScale.y + CreditsButtonScaleOffset.y,
			CreditsButtonScale.z + CreditsButtonScaleOffset.z));

		isWithin = true;
	}
	else
	{
		// Reset it to original size.
		CreditsButtonScaleOffset.Set(0.f, 0.f, 0.f);
		CreditButton->SetScale(Vector3(CreditsButtonScale.x + CreditsButtonScaleOffset.x,
			CreditsButtonScale.y + CreditsButtonScaleOffset.y,
			CreditsButtonScale.z + CreditsButtonScaleOffset.z));

		isWithin = false;
	}

	// If the cursor is inside the button and quit button is press.
	if (isWithin == true && CreditsButtonCondition)
	{
		if (MouseController::GetInstance()->IsButtonDown(MouseController::LMB))
		{
			theScreenState = CREDITS;
		}
	}

}

void Screen::UpdateQuitButton()
{
	// Quit Button Condition
	QuitButtonCondition = (mousePos.x >= (QuitButtonPos.x - QuitButtonScale.x * 0.5f)) &&
		(mousePos.x <= (QuitButtonPos.x + QuitButtonScale.x * 0.5f)) &&
		(mousePos.y >= (QuitButtonPos.y - QuitButtonScale.y * 0.5f)) &&
		(mousePos.y <= (QuitButtonPos.y + QuitButtonScale.y * 0.5f));

	// Checking if the mouse cursor is inside the button.
	if (QuitButtonCondition)
	{
		// The word will be bigger
		QuitButtonScaleOffset.Set(10.f, 10.f, 10.f);
		QuitButton->SetScale(Vector3(QuitButtonScale.x + QuitButtonScaleOffset.x,
			QuitButtonScale.y + QuitButtonScaleOffset.y,
			QuitButtonScale.z + QuitButtonScaleOffset.z));

		isWithin = true;
	}
	else
	{
		// Reset it to original size.
		QuitButtonScaleOffset.Set(0.f, 0.f, 0.f);
		QuitButton->SetScale(Vector3(QuitButtonScale.x + QuitButtonScaleOffset.x,
			QuitButtonScale.y + QuitButtonScaleOffset.y,
			QuitButtonScale.z + QuitButtonScaleOffset.z));

		isWithin = false;
	}

	// If the cursor is inside the button and quit button is press.
	if (isWithin == true && QuitButtonCondition)
	{
		if (MouseController::GetInstance()->IsButtonDown(MouseController::LMB))
		{
			glfwSetWindowShouldClose(m_window, GL_TRUE);
		}
	}
}

void Screen::Render()
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

void Screen::Exit()
{
	GraphicsManager::GetInstance()->DetachCamera();
	EntityManager::GetInstance()->ClearEntityList();
}