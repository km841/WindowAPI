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

public:
    virtual void OnCollision(Collider* _other);
    virtual void OnCollisionEnter(Collider* _other);
    virtual void OnCollisionExit(Collider* _other);

private:
    Texture* mDefaultTexture;
    bool mConversation;

};

