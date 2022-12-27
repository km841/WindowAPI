#pragma once
#include "Singleton.h"

class GameObject;
class AI;
class Map;
class Stage;
class EventRegisteror
	: public Singleton< EventRegisteror >
{
public:
	void CreateObject(GameObject* _obj, OBJECT_TYPE _eType);
	void DeleteObject(GameObject* _obj);
	void DeleteObjectFromScene(GameObject* _obj);
	void TransfortObject(GameObject* _obj, SCENE_TYPE _eType);
	void ChangeScene(SCENE_TYPE _eType);
	void ChangeMonsterState(AI* _ai, MONSTER_STATE _eState);

	void TransitionToMap(Stage* _stage, Map* _map);
	void EnableUI(UI_TYPE _eType);
	void DisableUI(UI_TYPE _eType);

	void EnableHUD(HUD_TYPE _eType);
	void DisableHUD(HUD_TYPE _eType);

private:

};

