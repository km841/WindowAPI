#pragma once
#include "GameObject.h"
class NPC :
    public GameObject
{
public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Destroy() override;

private:

};

