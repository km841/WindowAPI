#pragma once
#include "Gold.h"
class GoldBar :
    public Gold
{
public:
    GoldBar();
    virtual ~GoldBar();

public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Destroy() override;

public:
    virtual void OnCollision(Collider* _other);
    virtual void OnCollisionEnter(Collider* _other);
    virtual void OnCollisionExit(Collider* _other);


};

