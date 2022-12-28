#pragma once
class Map;
class BossMap;
class Stage
{
public:
	Stage(STAGE_TYPE _type);
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
	inline STAGE_TYPE GetStageType() const { return mStageType; }

	inline Map* GetBossSideMap() const { return mBossSideMap; }
	void SetBossSideMap(Map* _sideMap);
	void SetBossMap(BossMap* _bossMap);

private:
	STAGE_TYPE mStageType;
	std::vector<Map*> mMaps;
	
	

protected:
	Map* mCurMap;
	Map* mStartMap;

	Map* mBossSideMap;
	BossMap* mBossMap;

	Vec2 mInitPlayerPos;
	//Vec2 mBossSideMapPos;
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

