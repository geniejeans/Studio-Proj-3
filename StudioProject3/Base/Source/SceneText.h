#ifndef SCENE_TEXT_H
#define SCENE_TEXT_H

#include "Scene.h"
#include "Mtx44.h"
#include "PlayerInfo/PlayerInfo.h"
#include "GroundEntity.h"
#include "FPSCamera.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "GenericEntity.h"
#include "Enemy/Enemy3D.h"
#include "Hardware Abstraction/Keyboard.h"
#include "Hardware Abstraction/mouse.h"
#include "MiniMap\Minimap.h"
#include "CameraEffects\CameraEffects.h"
#include "SpriteEntity.h"
#include "Furniture\Furniture.h"
#include "MoneyManager\Money.h"

class ShaderProgram;
class SceneManager;
class TextEntity;
class Light;
class SceneText : public Scene
{	
public:
	SceneText();
	~SceneText();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

private:
	SceneText(SceneManager* _sceneMgr); // This is used to register to SceneManager

	ShaderProgram* currProg;
	CPlayerInfo* playerInfo;
	GroundEntity* groundEntity;
	FPSCamera camera;
	TextEntity* textObj[2];
	Light* lights[2];

	CMinimap *theMinimap;

	static SceneText* sInstance; // The pointer to the object that gets registered
	CKeyboard* theKeyboard;
	CMouse* theMouse;

	CEnemy3D* testTroop[3];
	CEnemy3D* newTroop[20];
	CEnemy3D* ninjaTroop[7];

	CEnemy3D* turret[20];
	int spawnedTroops = 23;

	float spawnDelay = 0.f;
	const float coolDown = 5.f;

	MoneyRain* theMoney[50];
	Thunderstorm* theStorm[50];
};

#endif