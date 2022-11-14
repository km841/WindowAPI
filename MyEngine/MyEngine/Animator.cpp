#include "pch.h"
#include "Animator.h"
#include "Animation.h"


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
