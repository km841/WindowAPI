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

	// 맵을 집어넣을 때 맵 파일의 주소를 집어넣음
	// 맵을 연결해주는건?
	// Stage의 Enter에서 처리
	// 무슨 근거로 연결해주나?
	// 각 맵과 통로의 쌍을 Stage가 알고 있어야 한다.
	// 따라서 맵 파일 이름과, 열려있는 통로를 알고 있으면 됨
	// 그런데 모든 던전은 남는 곳 없이 퍼즐처럼 짜여있어야 한다.
	// 막혀있는곳이 마지막에 가게 하려면?

	// 맵 간에 
};

