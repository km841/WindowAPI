#pragma once
#include "Common.h"
#include "yaResource.h"

namespace ya
{
	
	class Resources
	{
		typedef std::map<std::wstring, Resource*>::iterator ResourceIter;

	public:

		template<typename T>
		static T* Find(const std::wstring& key)
		{
			ResourceIter iter = mResources.find(key);

			if (mResources.end() != iter)
			{
				return dynamic_cast<T*>(iter->second);
			}
			
			return nullptr;
		}

		template<typename T>
		static T* Load(const std::wstring& key, const std::wstring& path)
		{
			T* resource = Find<T>(path);
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

		static void Release()
		{
			ResourceIter iter = mResources.begin();
			for (; iter != mResources.end(); ++iter)
			{
				if (iter->second == nullptr)
					continue;

				delete iter->second;
				iter->second = nullptr;
			}
		}


	private:
		static std::map<std::wstring, Resource*> mResources;


	};

	
}


