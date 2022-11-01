#pragma once

class Res;
class ResourceMgr 
	: public Singleton< ResourceMgr >
{	
	typedef std::map<std::wstring, Res*> ResourceMap;

public:
	ResourceMgr() {}
	~ResourceMgr();

public:

	template<typename T>
	T* Load(const std::wstring& _key, const std::wstring& _path)
	{
		auto iter = mResMap.find(_key);
		if (iter != mResMap.end())
		{
			return dynamic_cast<T*>(iter->second);
		}

		T* res = new T;
		res->SetKey(_key);
		res->Load(mDefaultPath + _path);
		mResMap.insert(std::make_pair(_key, res));
		
		return res;
	}


private:
	ResourceMap			mResMap;
	static std::wstring mDefaultPath;
};

