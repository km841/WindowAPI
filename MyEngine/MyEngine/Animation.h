#pragma once
class Animation
{
public:
    Animation();
    virtual ~Animation();

public:
    virtual void Update();
    virtual void Render();
};

