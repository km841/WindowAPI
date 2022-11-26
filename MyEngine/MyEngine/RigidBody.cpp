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
	//힘의 크기
	float force = mForce.Len();
	if (0.f != force)
	{
		mForce.Norm();
		//가속도
		float accel = force / mMass;
		mAccel = mForce * accel;
	}
	//가속도를 속도에 더한다
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

