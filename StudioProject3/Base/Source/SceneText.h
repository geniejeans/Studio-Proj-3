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
#include "Hardware Abstraction/Keyboard.h"
#include "Hardware Abstraction/mouse.h"
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

	static SceneText* sInstance; // The pointer to the object that gets registered
};

#endif