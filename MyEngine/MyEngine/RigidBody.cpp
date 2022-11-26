#include "pch.h"
#include "RigidBody.h"
#include "TimeMgr.h"
#include "GameObject.h"

RigidBody::RigidBody()
	:mMass(1.f)
	,mGravity(false)
	,mGravityAcc(0.f, 1800.f)
{
}

RigidBody::~RigidBody()
{
}

void RigidBody::Update()
{
	//���� ũ��
	float force = mForce.Len();
	if (0.f != force)
	{
		mForce.Norm();
		//���ӵ�
		float accel = force / mMass;
		mAccel = mForce * accel;
	}
	//���ӵ��� �ӵ��� ���Ѵ�
	mVelocity += mAccel * DT;
	if (mOwner->GetGravity())
		mVelocity += (mGravityAcc * DT);

	Move();

	mAccel = ZERO_VECTOR;
	mForce = ZERO_VECTOR;
}

void RigidBody::Move()
{
	Vec2 ownerPos = mOwner->GetPos();
	mOwner->SetPos(ownerPos + (mVelocity * DT));
}

