#pragma once
#include "Common.h"
#include "yaResource.h"

namespace ya
{
	
	template<typename T>
	class Resources
	{
		typedef std::map<std::wstring, Resource*>::iterator ResourceIter;

	public:

		static T* Find(const std::wstring& key)
		{
			ResourceIter iter = mResources.find(key);

			if (mResources.end() != iter)
			{
				return dynamic_cast<T*>(iter->second);
			}
			
			return nullptr;
		}

		static T* Load(const std::wstring& key, const std::wstring& path)
		{
			T* resource = Find(path);
			if (nullptr != resource)
			{
				return resource;
			}

			resource = new T;
			if (FAILED(resource->Load(path)))
			{
				MessageBox(nullptr, L"Image Load Fail !", L"Error", MB_OK);
				return nullptr;
			}

			resource->SetKey(key);
			resource->SetPath(path);

			mResources.insert(std::make_pair(key, resource));

			return dynamic_cast<T*>(resource);
		}


	private:
		static std::map<std::wstring, Resource*> mResources;


	};

	template<typename T>
	std::map<std::wstring, Resource*> Resources<T>::mResources;
}


