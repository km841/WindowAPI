#pragma once
#include "Component.h"

class Animation;
class Animator :
    public Component
{
public:
    Animator();
    virtual ~Animator();

public:
    virtual void Update();
    virtual void Render();

private:
    std::map<std::wstring, Animation*> mAnimMap;
};

