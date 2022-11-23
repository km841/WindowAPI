#pragma once
#include "NPC.h"

class Texture;
class BlackSmithNPC :
    public NPC
{
public:
    BlackSmithNPC();
    virtual ~BlackSmithNPC();

public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Destroy() override;

private:
    Texture* mDefaultTexture;
};

