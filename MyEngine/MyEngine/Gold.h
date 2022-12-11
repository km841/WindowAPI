#pragma once
#include "GameObject.h"

// 몬스터가 랜덤으로 n원을 가지고 있게 하고,
// 몬스터가 사망 시 Gold의 static 함수를 통해
// n원이 100원 이상이라면 goldbar를 드랍시키고 아니라면 coin을 드랍
// 힘은 일정하게 주어지게 되는데 각도는 랜덤으로 해서 원작과 비슷하게 제작

class Texture;
class Gold :
    public GameObject
{
public:
    Gold();
    virtual ~Gold();

public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Destroy() override;

public:
    inline Texture* GetTexture() const { return mTexture; }
    inline void     SetTexture(Texture* _tex) { mTexture = _tex; }

public:
    static void Drop(Gold* _gold, Vec2 _pos, int _money, float _angle);
    
public:
    inline void SetMoney(int _money) { mMoney = _money; }
    inline int  GetMoney() const { return mMoney; }
    

public:
    virtual void OnCollision(Collider* _other);
    virtual void OnCollisionEnter(Collider* _other);
    virtual void OnCollisionExit(Collider* _other);

protected:
    Texture* mTexture;
    int mMoney;

};

