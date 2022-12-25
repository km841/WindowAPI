#pragma once
class Map;
class Stage
{
public:
	Stage();
	virtual ~Stage();

public:
	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	virtual void Destroy();

public:
	virtual void Enter() = 0;
	virtual void Exit() = 0;

private:
	STAGE_TYPE mType;
	
	std::vector<Map*> mMaps;

	// ���� ������� �� �� ������ �ּҸ� �������
	// ���� �������ִ°�?
	// Stage�� Enter���� ó��
	// ���� �ٰŷ� �������ֳ�?
	// �� �ʰ� ����� ���� Stage�� �˰� �־�� �Ѵ�.
	// ���� �� ���� �̸���, �����ִ� ��θ� �˰� ������ ��
	// �׷��� ��� ������ ���� �� ���� ����ó�� ¥���־�� �Ѵ�.
	// �����ִ°��� �������� ���� �Ϸ���?

	// �� ���� 
};

