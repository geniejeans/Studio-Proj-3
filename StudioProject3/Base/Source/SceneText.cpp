#include "SceneText.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "MeshBuilder.h"
#include "Application.h"
#include "Utility.h"
#include "LoadTGA.h"
#include <sstream>
#include "KeyboardController.h"
#include "MouseController.h"
#include "SceneManager.h"
#include "GraphicsManager.h"
#include "ShaderProgram.h"
#include "EntityManager.h"

#include "GenericEntity.h"
#include "GroundEntity.h"
#include "TextEntity.h"
#include "SpriteEntity.h"
#include "Light.h"
#include "SkyBox/SkyBoxEntity.h"

#include "RenderHelper.h"


#include <iostream>
using namespace std;

SceneText* SceneText::sInstance = new SceneText(SceneManager::GetInstance());

SceneText::SceneText()
{
}

SceneText::SceneText(SceneManager* _sceneMgr)
{
	_sceneMgr->AddScene("Start", this);
}

SceneText::~SceneText()
{
}

void SceneText::Init()
{
	glDisable(GL_CULL_FACE);
	// Load all the meshes
	MeshBuilder::GetInstance()->GenerateCrossHair("crosshair");
	MeshBuilder::GetInstance()->GenerateQuad("healthR", Color(1, 0, 0), 1.f);
	MeshBuilder::GetInstance()->GenerateQuad("healthG", Color(0, 0.5, 0), 1.f);
	MeshBuilder::GetInstance()->GenerateQuad("quad", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GetMesh("quad")->textureID = LoadTGA("Image//calibri.tga");
	MeshBuilder::GetInstance()->GenerateText("text", 16, 16);
	MeshBuilder::GetInstance()->GetMesh("text")->textureID = LoadTGA("Image//calibri.tga");
	MeshBuilder::GetInstance()->GetMesh("text")->material.kAmbient.Set(1, 0, 0);
	MeshBuilder::GetInstance()->GenerateRing("ring", Color(1, 0, 1), 36, 1, 0.5f);
	MeshBuilder::GetInstance()->GenerateSphere("lightball", Color(1, 1, 1), 18, 36, 1.f);
	MeshBuilder::GetInstance()->GenerateSphere("sphere", Color(1, 0, 0), 18, 36, 1.0f);
	MeshBuilder::GetInstance()->GenerateSphere("Troopbullet", Color(0, 0, 1), 18, 36, 2.f);
	MeshBuilder::GetInstance()->GenerateSphere("Turretbullet", Color(1, 0, 0), 18, 36, 2.f);
	MeshBuilder::GetInstance()->GenerateSphere("particle", Color(1,0, 0), 18, 36, 0.4f);
	
	MeshBuilder::GetInstance()->GenerateCone("cone", Color(0.5f, 1, 0.3f), 36, 10.f, 10.f);
	MeshBuilder::GetInstance()->GenerateCube("cube", Color(1.0f, 1.0f, 0.0f), 1.0f);
	MeshBuilder::GetInstance()->GetMesh("cone")->material.kDiffuse.Set(0.99f, 0.99f, 0.99f);
	MeshBuilder::GetInstance()->GetMesh("cone")->material.kSpecular.Set(0.f, 0.f, 0.f);
	//MoneyRain
	MeshBuilder::GetInstance()->GenerateQuad("MONEY_RAIN", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GetMesh("MONEY_RAIN")->textureID = LoadTGA("Image//RandomEvents//Coin.tga");
	//ThunderStorm
	MeshBuilder::GetInstance()->GenerateQuad("THUNDER_STORM", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GetMesh("THUNDER_STORM")->textureID = LoadTGA("Image//RandomEvents//Lightning.tga");
	MeshBuilder::GetInstance()->GenerateQuad("UI", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GetMesh("UI")->textureID = LoadTGA("Image//HUDScreen_Full.tga");
	MeshBuilder::GetInstance()->GenerateQuad("UIRno", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GetMesh("UIRno")->textureID = LoadTGA("Image//HUDScreen_FullRadarNo.tga");
	MeshBuilder::GetInstance()->GenerateQuad("UILevel1", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GetMesh("UILevel1")->textureID = LoadTGA("Image//HUDScreen_Lv1.tga");
	MeshBuilder::GetInstance()->GenerateQuad("UILevel2", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GetMesh("UILevel2")->textureID = LoadTGA("Image//HUDScreen_Lv2.tga");
	MeshBuilder::GetInstance()->GenerateQuad("Loading", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GetMesh("Loading")->textureID = LoadTGA("Image//LoadingScreen.tga");
	MeshBuilder::GetInstance()->GenerateQuad("UILevel2Rno", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GetMesh("UILevel2Rno")->textureID = LoadTGA("Image//HUDScreen_Lv2RadarNo.tga");
	//TROOPS
	MeshBuilder::GetInstance()->GenerateOBJ("testTroop", "OBJ//PlayerTrooperOBJ.obj");
	MeshBuilder::GetInstance()->GetMesh("testTroop")->textureID = LoadTGA("Image//Troop_TextureTGA.tga");

	MeshBuilder::GetInstance()->GenerateOBJ("testTroop2", "OBJ//PlayerTrooperOBJ.obj");
	MeshBuilder::GetInstance()->GetMesh("testTroop2")->textureID = LoadTGA("Image//TroopArcher_TextureTGA.tga");

	MeshBuilder::GetInstance()->GenerateOBJ("testTroop3", "OBJ//PlayerTrooperOBJ.obj");
	MeshBuilder::GetInstance()->GetMesh("testTroop3")->textureID = LoadTGA("Image//TroopTank_TextureTGA.tga");
	
	//SHIELDED TROOPS
	MeshBuilder::GetInstance()->GenerateOBJ("ShieldedTroop", "OBJ//PlayerTrooperOBJ.obj");
	MeshBuilder::GetInstance()->GetMesh("ShieldedTroop")->textureID = LoadTGA("Image//TroopShielded_TextureTGA.tga");
	
	MeshBuilder::GetInstance()->GenerateOBJ("ShieldedArcherTroop", "OBJ//PlayerTrooperOBJ.obj");
	MeshBuilder::GetInstance()->GetMesh("ShieldedArcherTroop")->textureID = LoadTGA("Image//TroopArcherShielded_TextureTGA.tga");

	MeshBuilder::GetInstance()->GenerateOBJ("ShieldedTankTroop", "OBJ//PlayerTrooperOBJ.obj");
	MeshBuilder::GetInstance()->GetMesh("ShieldedTankTroop")->textureID = LoadTGA("Image//TroopTankShielded_TextureTGA.tga");

	//BASES
	MeshBuilder::GetInstance()->GenerateOBJ("ninjaTroop", "OBJ//Enemy_trooper.obj");
	MeshBuilder::GetInstance()->GetMesh("ninjaTroop")->textureID = LoadTGA("Image//Enemy_TextureTGA.tga");
	MeshBuilder::GetInstance()->GenerateOBJ("enemyBase", "OBJ//BaseCakeCastle_OBJ.obj");
	MeshBuilder::GetInstance()->GetMesh("enemyBase")->textureID = LoadTGA("Image//EnemyBase_Texture.tga");
	MeshBuilder::GetInstance()->GenerateOBJ("playerBase", "OBJ//BaseCakeCastle_OBJ.obj");
	MeshBuilder::GetInstance()->GetMesh("playerBase")->textureID = LoadTGA("Image//PlayerBase_Texture.tga");

	//TURRETS
	MeshBuilder::GetInstance()->GenerateOBJ("turretBot", "OBJ//CandyTurret_Bottom.obj");
	MeshBuilder::GetInstance()->GetMesh("turretBot")->textureID = LoadTGA("Image//TurretTexture.tga");
	MeshBuilder::GetInstance()->GenerateOBJ("turretTop", "OBJ//CandyTurret_Top.obj");
	MeshBuilder::GetInstance()->GetMesh("turretTop")->textureID = LoadTGA("Image//TurretTexture.tga");

	MeshBuilder::GetInstance()->GenerateOBJ("turretBot2", "OBJ//CandyTurret_Bottom.obj");
	MeshBuilder::GetInstance()->GetMesh("turretBot2")->textureID = LoadTGA("Image//TurretTextureMedium.tga");
	MeshBuilder::GetInstance()->GenerateOBJ("turretTop2", "OBJ//CandyTurret_Top.obj");
	MeshBuilder::GetInstance()->GetMesh("turretTop2")->textureID = LoadTGA("Image//TurretTextureMedium.tga");

	MeshBuilder::GetInstance()->GenerateOBJ("turretBot3", "OBJ//CandyTurret_Bottom.obj");
	MeshBuilder::GetInstance()->GetMesh("turretBot3")->textureID = LoadTGA("Image//TurretTextureHard.tga");
	MeshBuilder::GetInstance()->GenerateOBJ("turretTop3", "OBJ//CandyTurret_Top.obj");
	MeshBuilder::GetInstance()->GetMesh("turretTop3")->textureID = LoadTGA("Image//TurretTextureHard.tga");

	//TREES AND TARGET
	MeshBuilder::GetInstance()->GenerateOBJ("tree", "OBJ//JellyTree_OBJ.obj");
	MeshBuilder::GetInstance()->GetMesh("tree")->textureID = LoadTGA("Image//JellyTree_Texture.tga");
	MeshBuilder::GetInstance()->GenerateOBJ("BombTarget", "OBJ//quad.obj");
	MeshBuilder::GetInstance()->GetMesh("BombTarget")->textureID = LoadTGA("Image//BombTarget.tga");

	MeshBuilder::GetInstance()->GenerateOBJ("IndicatorTarget", "OBJ//quad.obj");
	MeshBuilder::GetInstance()->GetMesh("IndicatorTarget")->textureID = LoadTGA("Image//Target.tga");

	MeshBuilder::GetInstance()->GenerateOBJ("IndicatorSelect", "OBJ//quad.obj");
	MeshBuilder::GetInstance()->GetMesh("IndicatorSelect")->textureID = LoadTGA("Image//Selection.tga");


	MeshBuilder::GetInstance()->GenerateQuad("SKYBOX_FRONT", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GenerateQuad("SKYBOX_BACK", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GenerateQuad("SKYBOX_LEFT", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GenerateQuad("SKYBOX_RIGHT", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GenerateQuad("SKYBOX_TOP", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GenerateQuad("SKYBOX_BOTTOM", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GetMesh("SKYBOX_FRONT")->textureID = LoadTGA("Image//SkyBox//boxFront.tga");
	MeshBuilder::GetInstance()->GetMesh("SKYBOX_BACK")->textureID = LoadTGA("Image//SkyBox//boxBack.tga");
	MeshBuilder::GetInstance()->GetMesh("SKYBOX_LEFT")->textureID = LoadTGA("Image//SkyBox//boxLeft.tga");
	MeshBuilder::GetInstance()->GetMesh("SKYBOX_RIGHT")->textureID = LoadTGA("Image//SkyBox//boxRight.tga");
	MeshBuilder::GetInstance()->GetMesh("SKYBOX_TOP")->textureID = LoadTGA("Image//SkyBox//boxUp.tga");
	MeshBuilder::GetInstance()->GetMesh("SKYBOX_BOTTOM")->textureID = LoadTGA("Image//SkyBox//boxDown.tga");
}

void SceneText::Update(double dt)
{
	

}

void SceneText::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GraphicsManager::GetInstance()->UpdateLightUniforms();

	// Setup 3D pipeline then render 3D
	GraphicsManager::GetInstance()->SetPerspectiveProjection(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
//	GraphicsManager::GetInstance()->AttachCamera(&camera);
	EntityManager::GetInstance()->Render();

	//Enable blend mode
	glEnable(GL_BLEND);

	// Setup 2D pipeline then render 2D
	int halfWindowWidth = Application::GetInstance().GetWindowWidth() / 2;
	int halfWindowHeight = Application::GetInstance().GetWindowHeight() / 2;
	GraphicsManager::GetInstance()->SetOrthographicProjection(-halfWindowWidth, halfWindowWidth, -halfWindowHeight, halfWindowHeight, -10, 10);
	GraphicsManager::GetInstance()->DetachCamera();
	EntityManager::GetInstance()->RenderUI();

	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	//Do you rendering on screen here. Centre of screen is (0,0)
	glDisable(GL_BLEND);

}

void SceneText::Exit()
{
	
}