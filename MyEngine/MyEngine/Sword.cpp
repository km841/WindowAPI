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
	// shortsword�� pos
	// pos.x - size.x, pos.y - size.y�� �»��
	// pos.x + size.x, pos.y - size.y�� ����
	// pos.x - size.x, pos.y + size.y�� ���ϴ�

	// 10�� �ö� Į�� ��ġ��?
	// (xcos10' - ysin10'), (xsin10' + ycos10')

	// pos�� ���ϴ°�? �÷��̾� ���� offset
	// ���콺 ��ġ�� ���� ���� ����
	Player* player = Player::GetPlayer();

	if (nullptr != player) {

		Texture* tex = GetTexture();
		Vec2 playerPos = player->GetPos();
		Vec2 offset = GetOffset();
		PLAYER_DIR playerDir = player->GetPlayerDir();
		Vec2 dirVec = { 0, 0 };

		// �⺻ �𼭸��� �����ص״ٰ�, ���콺 ������ ���� ���
		// angle�� ���ϴ� �� : �÷��̾ �ٶ󺸴� ��ġ (1, 0) or (-1, 0)�� ���콺���� ����
		// �ٶ󺸴� ������ ��ġ�� ���� -100��

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
	// ������ ���� ������
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

		//anchor�� transparentblt���� ���ɵ�

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
