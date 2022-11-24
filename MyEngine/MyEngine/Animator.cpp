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
	if (nullptr != anim)
		anim->SetRepeat(_repeat);
	mCurAnim = anim;
}

void Animator::RotSelectAnimation(const std::wstring& _animName, float _angle, bool _repeat)
{

	//CreateRotAnimation을 만들고... 그 애니메이션은 덮어쓸 수 있게 함 그 애니메이션은 텍스쳐만 다름

	Animation* anim = FindAnimation(_animName);
	Texture* orgTex = anim->GetTexture();
	
	// 신규 DC 초기화
	static Texture* rotTex = ResourceMgr::GetInstance().CreateTexture(L"RotAnimTex", orgTex->GetSize());
	Brush brush(rotTex->GetDC(), BRUSH_TYPE::MAGENTA);
	Rectangle(rotTex->GetDC(), -5, -5, rotTex->GetWidth() + 5, rotTex->GetHeight() + 5);

	const std::vector<AnimInfo>& animInfo = anim->GetAnimInfo();

	// Slice 크기의 임시 버퍼 생성
	static Texture* tempTex = ResourceMgr::GetInstance().CreateTexture(L"RotTempTex", animInfo.front().mSlice);
	static Texture* maskTex = ResourceMgr::GetInstance().CreateTexture(L"RotMaskTex", animInfo.front().mSlice);

	Brush tempBrush(tempTex->GetDC(), BRUSH_TYPE::MAGENTA);
	Rectangle(tempTex->GetDC(), -5, -5, tempTex->GetWidth() + 5, tempTex->GetHeight() + 5);

	Brush maskBrush(maskTex->GetDC(), BRUSH_TYPE::MAGENTA);
	Rectangle(maskTex->GetDC(), -5, -5, maskTex->GetWidth() + 5, maskTex->GetHeight() + 5);


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
			(int)animInfo[i].mSlice.x,
			(int)animInfo[i].mSlice.y,
			orgTex->GetDC(),
			(int)animInfo[i].mLeftTop.x,
			(int)animInfo[i].mLeftTop.y,
			(int)animInfo[i].mSlice.x,
			(int)animInfo[i].mSlice.y,
			0
		);

		PlgBlt(
			maskTex->GetDC(),
			points,
			tempTex->GetDC(),
			0, 0,
			(int)animInfo[i].mSlice.x,
			(int)animInfo[i].mSlice.y,
			NULL,
			0, 0
		);

		TransparentBlt(
			rotTex->GetDC(),
			(int)animInfo[i].mLeftTop.x,
			(int)animInfo[i].mLeftTop.y,
			(int)animInfo[i].mSlice.x,
			(int)animInfo[i].mSlice.y,
			maskTex->GetDC(),
			0, 0,
			(int)animInfo[i].mSlice.x,
			(int)animInfo[i].mSlice.y,
			RGB(255, 0, 255)
		);
	}

	anim->SetRepeat(_repeat);

	RegisterAnimation(
		_animName + L"Rot",
		rotTex,
		animInfo[0].mLeftTop,
		animInfo[0].mSlice,
		Vec2(animInfo[0].mSlice.x, animInfo[0].mLeftTop.y),
		animInfo[0].mDuration,
		(UINT)animInfo.size()
	);

	mCurAnim = FindAnimation(_animName + L"Rot");
	mCurAnim->SetEffectAnimation(true);

	// curanim에 들어가면 update를 통해 애니메이션의 각 프레임이
	// 변경된 texture로 바꿔주면 될듯
	// 그러면 기존과 동일한 texture를 만든 후 거기 현재 각도에 맞춰서 회전해서 그려주고
	// SetTexture로 변경한 후에
	// 그걸 Render에서 출력하도록 함

}
