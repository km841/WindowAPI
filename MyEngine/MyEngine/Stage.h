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

public:
	inline void SetInitPlayerPos(Vec2 _pos) { mInitPlayerPos = _pos; }
	inline Vec2 GetInitPlayerPos() { return mInitPlayerPos; }
	void TransitionToMap(Map* _map);
	void AddMap(const std::wstring& _path);

	inline Map* GetStartMap() const { return mMaps[0]; }

	void ChainMaps(Map* _map);

private:
	STAGE_TYPE mType;
	std::vector<Map*> mMaps;
	

protected:
	Map* mCurMap;
	Map* mStartMap;
	Vec2 mInitPlayerPos;
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

