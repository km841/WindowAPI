#pragma once
#include "GameObject.h"

// ���Ͱ� �������� n���� ������ �ְ� �ϰ�,
// ���Ͱ� ��� �� Gold�� static �Լ��� ����
// n���� 100�� �̻��̶�� goldbar�� �����Ű�� �ƴ϶�� coin�� ���
// ���� �����ϰ� �־����� �Ǵµ� ������ �������� �ؼ� ���۰� ����ϰ� ����

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

