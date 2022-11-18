#include "pch.h"
#include "Animator.h"
#include "Animation.h"
#include "Texture.h"
#include "ResourceMgr.h"


Animator::Animator()
{
}

Animator::~Animator()
{
	for (auto& anim : mAnimMap)
	{
		if (nullptr != anim.second)
		{
			delete anim.second;
			anim.second = nullptr;
		}
	}
}

void Animator::Update()
{
	if (nullptr != mCurAnim)
		mCurAnim->Update();
}

void Animator::Render()
{
	if (nullptr != mCurAnim)
		mCurAnim->Render();
}

Animation* Animator::CreateAnimation(const std::wstring& _animName, Texture* _tex, Vec2 _leftTop
							       , Vec2 _slice, Vec2 _offset, float _duration, UINT _frmCount)
{
	Animation* anim = FindAnimation(_animName);
	if (nullptr != anim)
		return nullptr;

	anim = new Animation;
	anim->mOwner = this;
	anim->SetName(_animName);
	
	anim->Create(_tex, _leftTop, _slice, _offset, _duration, _frmCount);
	return anim;
}

void Animator::RegisterAnimation(const std::wstring& _animName, Texture* _tex, Vec2 _leftTop, Vec2 _slice, Vec2 _offset
							         , float _duration, UINT _frmCount)
{
	Animation* anim = CreateAnimation(_animName, _tex, _leftTop, _slice, _offset, _duration, _frmCount);
	AddAnimation(_animName, anim);
}

Animation* Animator::FindAnimation(const std::wstring& _animName)
{
	std::map<std::wstring, Animation*>::iterator iter = mAnimMap.find(_animName);
	if (iter != mAnimMap.end())
		return iter->second;

	return nullptr;
}

void Animator::SelectAnimation(const std::wstring& _animName, bool _repeat)
{
	Animation* anim = FindAnimation(_animName);	
	anim->SetRepeat(_repeat);
	mCurAnim = anim;

}

void Animator::RotSelectAnimation(const std::wstring& _animName, float _angle, bool _repeat)
{

	//CreateRotAnimation�� �����... �� �ִϸ��̼��� ��� �� �ְ� �� �� �ִϸ��̼��� �ؽ��ĸ� �ٸ�

	Animation* anim = FindAnimation(_animName);
	Texture* orgTex = anim->GetTexture();

	// �ű� DC �ʱ�ȭ
	static Texture* rotTex = ResourceMgr::GetInstance().CreateTexture(L"RotAnimTex", orgTex->GetSize());
	Brush brush(rotTex->GetDC(), BRUSH_TYPE::MAGENTA);
	Rectangle(rotTex->GetDC(), -1, -1, rotTex->GetWidth() + 1, rotTex->GetHeight() + 1);

	const std::vector<AnimInfo>& animInfo = anim->GetAnimInfo();

	// Slice ũ���� �ӽ� ���� ����
	static Texture* tempTex = ResourceMgr::GetInstance().CreateTexture(L"RotTempTex", animInfo.front().mSlice);
	Rectangle(tempTex->GetDC(), -1, -1, tempTex->GetWidth() + 1, tempTex->GetHeight() + 1);


	for (int i = 0; i < animInfo.size(); ++i)
	{
		Vec2 vertices[(UINT)VERTICES_POINT::END] = {};
		vertices[(UINT)VERTICES_POINT::LEFT_TOP] = { 0.f, 0.f };
		vertices[(UINT)VERTICES_POINT::RIGHT_TOP] = { animInfo[i].mSlice.x, 0.f };
		vertices[(UINT)VERTICES_POINT::LEFT_BOTTOM] = { 0.f, animInfo[i].mSlice.y };

		Vec2 anchorPoint = (animInfo[i].mSlice / 2.f);
		float distances[(UINT)VERTICES_POINT::END] = {};
		for (int i = 0; i < (UINT)VERTICES_POINT::END; ++i)
		{
			vertices[i] = vertices[i] - anchorPoint;
			distances[i] = vertices[i].Len();
			vertices[i].Norm();
		}

		for (int i = 0; i < (UINT)VERTICES_POINT::END; ++i)
		{
			vertices[i] = RotateVector(vertices[i], _angle);
			vertices[i] *= distances[i];
			vertices[i] += anchorPoint;
		}

		POINT points[(UINT)VERTICES_POINT::END] = {
			vertices[(UINT)VERTICES_POINT::LEFT_TOP],
			vertices[(UINT)VERTICES_POINT::RIGHT_TOP],
			vertices[(UINT)VERTICES_POINT::LEFT_BOTTOM]
		};
		
		TransparentBlt(
			tempTex->GetDC(),
			0, 0,
			animInfo[i].mSlice.x,
			animInfo[i].mSlice.y,
			orgTex->GetDC(),
			animInfo[i].mLeftTop.x,
			animInfo[i].mLeftTop.y,
			animInfo[i].mSlice.x,
			animInfo[i].mSlice.y,
			0
		);

		PlgBlt(
			tempTex->GetDC(),
			points,
			tempTex->GetDC(),
			0, 0,
			animInfo[i].mSlice.x,
			animInfo[i].mSlice.y,
			NULL,
			0, 0
		);
		//Rectangle(
		//	rotTex->GetDC(),
		//	animInfo[i].mLeftTop.x  ,
		//	animInfo[i].mLeftTop.y ,
		//	animInfo[i].mSlice.x + 1,
		//	animInfo[i].mSlice.y + 1
		//	);



		BitBlt(
			rotTex->GetDC(),
			animInfo[i].mLeftTop.x,
			animInfo[i].mLeftTop.y,
			animInfo[i].mSlice.x,
			animInfo[i].mSlice.y,
			tempTex->GetDC(),
			0, 0,
			SRCCOPY
		);
	}

	
	//anim->SetTexture(rotTex);
	anim->SetRepeat(_repeat);

	RegisterAnimation(
		_animName + L"Rot",
		rotTex,
		animInfo[0].mLeftTop,
		animInfo[0].mSlice,
		Vec2(animInfo[0].mSlice.x, 0.f),
		animInfo[0].mDuration,
		animInfo.size()
	);

	mCurAnim = FindAnimation(_animName + L"Rot");

	// curanim�� ���� update�� ���� �ִϸ��̼��� �� ��������
	// ����� texture�� �ٲ��ָ� �ɵ�
	// �׷��� ������ ������ texture�� ���� �� �ű� ���� ������ ���缭 ȸ���ؼ� �׷��ְ�
	// SetTexture�� ������ �Ŀ�
	// �װ� Render���� ����ϵ��� ��

}
