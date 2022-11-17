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
	Texture* tex = GetTexture();
	mVertices[(UINT)VERTICES_POINT::LEFT_TOP] = Vec2(0.f, 0.f);
	mVertices[(UINT)VERTICES_POINT::RIGHT_TOP] = Vec2(tex->GetSize().x , 0.f);
	mVertices[(UINT)VERTICES_POINT::LEFT_BOTTOM] = Vec2(0.f, tex->GetSize().y);
}

void Sword::Update()
{
	// pos�� ���ϴ°�? �÷��̾� ���� offset
	// ���콺 ��ġ�� ���� ���� ����
	Player* player = Player::GetPlayer();

	if (nullptr != player) {

		Texture* tex = GetTexture();
		Vec2 playerPos = player->GetPos();
		PLAYER_DIR playerDir = player->GetPlayerDir();

		// �⺻ �𼭸��� �����ص״ٰ�, ���콺 ������ ���� ���
		// angle�� ���ϴ� �� : �÷��̾ �ٶ󺸴� ��ġ (1, 0) or (-1, 0)�� ���콺���� ����
		// �ٶ󺸴� ������ ��ġ�� ���� -100��

		Vec2 dirVec = { 0, 0 };
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

		float offsetDegree = DegreeToRadian(185.f);
		float angle = (float)(acos(dirVec.Dot(mousePos)) - offsetDegree) * 5.f;

		if (PLAYER_DIR::LEFT == playerDir)
		{
			angle = angle / 2.f;
		}

		Vec2 rotOffset = GetOffset();
		rotOffset.Norm();

		float offsetDistance = 30.f;
		rotOffset = RotateVector(rotOffset, angle);
		rotOffset = rotOffset * offsetDistance;

		Vec2 textureAnchor = tex->GetSize() / 2.f;

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
			mRotatedVertices[i] = (mRotatedVertices[i] * distances[i]) + textureAnchor;
		}
		
		SetPos(playerPos + rotOffset);
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

		Player* player = Player::GetPlayer();
		PLAYER_DIR dir = player->GetPlayerDir();
		float offsetX = 0.f;
		float offsetY = GetYOffset();

		switch (dir)
		{
		case PLAYER_DIR::LEFT:
			offsetX = GetLeftDirOffset();
			break;

		case PLAYER_DIR::RIGHT:
			offsetX = GetRightDirOffset();
			break;
		}

		Vec2 pos = RENDER_POS(GetPos());
		TransparentBlt(
			BACK_BUF_DC,
			// 40�� �׽�Ʈ�� ���� �ӽð�
			(int)(pos.x - size.x + offsetX),
			(int)(pos.y - size.y + offsetY),
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
