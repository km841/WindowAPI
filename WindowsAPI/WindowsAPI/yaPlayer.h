#pragma once
#include "yaGameObject.h"

namespace ya
{
    class Player :
        public GameObject
    {

    public:
        Player();
        virtual ~Player();

        virtual void Tick()          override;
        virtual void Render(HDC hdc) override;

    private:
        float mSpeed;

    };
}


