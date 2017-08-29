#ifndef LEVEL2_H
#define LEVEL2_H

#include "Scene.h"
#include "Mtx44.h"
#include "../PlayerInfo/PlayerInfo.h"
#include "../GroundEntity.h"
#include "../FPSCamera.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "../GenericEntity.h"
#include "../Enemy/Enemy3D.h"
#include "../Hardware Abstraction/Keyboard.h"
#include "../Hardware Abstraction/mouse.h"
#include "../MiniMap\Minimap.h"
#include "../CameraEffects\CameraEffects.h"
#include "../SpriteEntity.h"
#include "../Furniture\Furniture.h"
#include "../Bomb.h"

class ShaderProgram;
class SceneManager;
class TextEntity;
class Light;

class Level2 : public Scene
{
public:
	Level2();
	~Level2();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

private:
	Level2(SceneManager* _sceneMgr); // This is used to register to SceneManager

	ShaderProgram* currProg;
	CPlayerInfo* playerInfo;
	GroundEntity* groundEntity;
	FPSCamera camera;
	TextEntity* textObj[3];
	Light* lights[2];
	Vector3 test;

	CMinimap *theMinimap;
	Bomb* BombTarget;
	EntityBase* IndicatorTarget;

	static Level2* sInstance; // The pointer to the object that gets registered
	CKeyboard* theKeyboard;
	CMouse* theMouse;

	float elapsed_time;
	float complete_time;
	float spawnDelay = 0.f;
	const float coolDown = 30.f;
};

#endif