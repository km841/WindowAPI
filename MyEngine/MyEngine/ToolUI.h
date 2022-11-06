#pragma once
#include "UI.h"

class Tile;
class ToolUI :
    public UI
{
public:
	ToolUI();
	~ToolUI();

public:
	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	virtual void Destroy();

public:


private:
	


};

