#pragma once

class Res
{
public:
	Res()
		:mKey{}
	{ }
	Res(const std::wstring& _key)
		:mKey{}
	{ }
	virtual ~Res() {}

public:
	virtual bool Load(const std::wstring& _path) = 0;

	inline void                SetKey(const std::wstring& _key) { mKey = _key; }
	inline const std::wstring& GetKey() const { return mKey; };

private:
	std::wstring mKey;

};

