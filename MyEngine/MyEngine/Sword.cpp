#include "pch.h"
#include "Sword.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "Player.h"
#include "TimeMgr.h"
#include "CameraMgr.h"
#include "MouseMgr.h"

Sword::Sword()
{

}

Sword::~Sword()
{
	if (mTransTexture)
		delete mTransTexture;

	mTransTexture = nullptr;
}

void Sword::Initialize()
{
	mAnchor = Vec2(0.1f, 0.5f);

	Texture* tex = GetTexture();


	mVertices[(UINT)VERTICES_POINT::LEFT_TOP] = Vec2(0.f, 0.f);
	mVertices[(UINT)VERTICES_POINT::RIGHT_TOP] = Vec2(tex->GetSize().x , 0.f);
	mVertices[(UINT)VERTICES_POINT::LEFT_BOTTOM] = Vec2(0.f, tex->GetSize().y);
}

void Sword::Update()
{
	// shortsword의 pos
	// pos.x - size.x, pos.y - size.y가 좌상단
	// pos.x + size.x, pos.y - size.y가 우상단
	// pos.x - size.x, pos.y + size.y가 좌하단

	// 10도 올라간 칼의 위치는?
	// (xcos10' - ysin10'), (xsin10' + ycos10')

	// pos를 정하는건? 플레이어 기준 offset
	// 마우스 위치에 따라 각도 변경
	Player* player = Player::GetPlayer();

	if (nullptr != player) {

		Texture* tex = GetTexture();
		Vec2 playerPos = player->GetPos();
		Vec2 offset = GetOffset();
		PLAYER_DIR playerDir = player->GetPlayerDir();
		Vec2 dirVec = { 0, 0 };

		// 기본 모서리를 저장해뒀다가, 마우스 각도에 따라 계산
		// angle을 구하는 법 : 플레이어가 바라보는 위치 (1, 0) or (-1, 0)과 마우스간의 각도
		// 바라보는 각도와 일치할 때는 -100도

		switch (playerDir)
		{
		case PLAYER_DIR::LEFT:
			dirVec = Vec2(-1, 0);
			break;
		case PLAYER_DIR::RIGHT:
			dirVec = Vec2(1, 0);
			break;
		}

		Vec2 mousePos = MOUSE_POS;
		mousePos.Norm();

		float angle = (float)(acos(dirVec.Dot(mousePos)) - PI) * 5.f;

		Vec2 textureAnchor = (tex->GetSize() / 2.f);
		textureAnchor.x = textureAnchor.x / 2.f;

		for (int i = 0; i < (UINT)VERTICES_POINT::END; ++i)
		{
			mRotatedVertices[i] = mVertices[i] - textureAnchor;
		}
		
		float distances[(UINT)VERTICES_POINT::END] = {
			mRotatedVertices[(UINT)VERTICES_POINT::LEFT_TOP].Len(),
			mRotatedVertices[(UINT)VERTICES_POINT::RIGHT_TOP].Len(),
			mRotatedVertices[(UINT)VERTICES_POINT::LEFT_BOTTOM].Len(),
		};

		for (int i = 0; i < (UINT)VERTICES_POINT::END; ++i)
		{
			mRotatedVertices[i].Norm();
			mRotatedVertices[i] = RotateVector(mRotatedVertices[i], angle);
		}

		for (int i = 0; i < (UINT)VERTICES_POINT::END; ++i)
		{
			mRotatedVertices[i] = mRotatedVertices[i] * distances[i] + textureAnchor;
		}

		SetPos(playerPos + offset);
	}
}

void Sword::Render()
{
	// 각도에 따라 렌더링
	Texture* tex = GetTexture();
	Texture* transTex = GetTransTexture();
	Vec2 size = GetSize();

	if (nullptr != tex && nullptr != transTex)
	{
		Brush brush(transTex->GetDC(), BRUSH_TYPE::MAGENTA);
		Rectangle(
			transTex->GetDC(), -1, -1
			, (int)(transTex->GetSize().x + 1)
			, (int)(transTex->GetSize().y + 1));

		POINT points[(UINT)VERTICES_POINT::END] = {
			mRotatedVertices[(UINT)VERTICES_POINT::LEFT_TOP],
			mRotatedVertices[(UINT)VERTICES_POINT::RIGHT_TOP],
			mRotatedVertices[(UINT)VERTICES_POINT::LEFT_BOTTOM]
		};

		PlgBlt(
			transTex->GetDC(),
			points,
			tex->GetDC(),
			0, 0,
			(int)transTex->GetSize().x,
			(int)transTex->GetSize().y,
			NULL,
			0, 0
		);

		//anchor가 transparentblt에서 사용될듯

		Vec2 pos = RENDER_POS(GetPos());
		TransparentBlt(
			BACK_BUF_DC,
			(int)(pos.x - size.x),
			(int)(pos.y - size.y),
			(int)size.x,
			(int)size.y,
			transTex->GetDC(),
			0, 0,
			(int)transTex->GetSize().x,
			(int)transTex->GetSize().y,
			RGB(255, 0, 255)
			
		);
	}
}
