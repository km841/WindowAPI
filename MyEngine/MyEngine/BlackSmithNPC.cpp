#include "pch.h"
#include "BlackSmithNPC.h"
#include "Animation.h"
#include "Animator.h"
#include "ResourceMgr.h"
#include "Texture.h"
#include "Collider.h"
#include "Player.h"
#include "CameraMgr.h"
#include "KeyMgr.h"
#include "FontMgr.h"
#include "UIMgr.h"
#include "EventRegisteror.h"

BlackSmithNPC::BlackSmithNPC()
	:mConversation(false)
{
	SetType(OBJECT_TYPE::NPC);
	CreateComponent(new Animator);
	GetAnimator()->SetOwner(this);

	mDefaultTexture = 
		ResourceMgr::GetInstance().Load<Texture>(L"BLACKSMITH_ANIMATION", L"Texture\\blacksmith_animation.bmp");
	
	Texture* keyTexture = 
		ResourceMgr::GetInstance().Load<Texture>(L"F_KEY", L"Texture\\F.bmp");
	SetKeyTexture(keyTexture);

	SetSize(Vec2( 72, 78));

	GetAnimator()->RegisterAnimation(
		L"BlackSmithAnim",
		mDefaultTexture,
		Vec2(0.f, 0.f),
		Vec2(72.f, 78.f),
		Vec2(72.f, 0.f),
		0.05f,
		6
	);


	CreateComponent(new Collider);
	GetCollider()->SetOwner(this);

	GetCollider()->SetSize(Vec2(30.f, 30.f));
	GetCollider()->SetOffset(Vec2(0.f, -15.f));

	GetAnimator()->SelectAnimation(L"BlackSmithAnim", true);
}

BlackSmithNPC::~BlackSmithNPC()
{
}

void BlackSmithNPC::Initialize()
{
}

void BlackSmithNPC::Update()
{
	GameObject::Update();

	if (mConversation && IS_JUST_PRESSED(KEY::F))
	{
		FontMgr::GetInstance().NPCLineClear();
		EventRegisteror::GetInstance().DisableHUD(HUD_TYPE::NPC_LINE);
		mConversation = false;
	}

	if (mCollision && IS_JUST_PRESSED(KEY::F) && false == UIMgr::GetInstance().GetHUDState(HUD_TYPE::NPC_LINE))
	{
		EventRegisteror::GetInstance().EnableHUD(HUD_TYPE::NPC_LINE);
		FontMgr::GetInstance().OutputNPCLine(L"그리 좋은 물건은 아니지만. 보탬은 될걸세!", Vec2(30, 680));
		mConversation = true;
	}


}

void BlackSmithNPC::Render()
{
	GameObject::Render();

	if (mCollision)
	{
		Texture* fKeyTexture = GetKeyTexture();
		Vec2 fKeyPos = GetPos();
		fKeyPos.y -= 110.f;

		fKeyPos = RENDER_POS(fKeyPos);
		Vec2 textureSize = fKeyTexture->GetSize();

		TransparentBlt(
			BACK_BUF_DC,
			(int)(fKeyPos.x - ((textureSize.x * TIMES) / 2.f)),
			(int)(fKeyPos.y - ((textureSize.y * TIMES) / 2.f)),
			(int)(textureSize.x * TIMES),
			(int)(textureSize.y * TIMES),
			fKeyTexture->GetDC(),
			0, 0,
			(int)textureSize.x,
			(int)textureSize.y,
			RGB(255, 0, 255)
		);
	}

}

void BlackSmithNPC::Destroy()
{
}

void BlackSmithNPC::OnCollision(Collider* _other)
{
	if (OBJECT_TYPE::PLAYER == _other->GetOwner()->GetType())
	{
		mCollision = true;
	}
}

void BlackSmithNPC::OnCollisionEnter(Collider* _other)
{
	
}

void BlackSmithNPC::OnCollisionExit(Collider* _other)
{
	if (OBJECT_TYPE::PLAYER == _other->GetOwner()->GetType())
	{
		mCollision = false;
	}
}
