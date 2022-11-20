#pragma once
#include "Singleton.h"

class GameObject;
class EventRegisteror
	: public Singleton< EventRegisteror >
{
public:
	void CreateObject(GameObject* _obj, OBJECT_TYPE _eType);
	void DeleteObject(GameObject* _obj);
	void ChangeScene(SCENE_TYPE _eType);

	void EnableUI(UI_TYPE _eType);
	void DisableUI(UI_TYPE _eType);

private:

};

