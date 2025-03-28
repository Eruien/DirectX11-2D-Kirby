#pragma once
#include "LStd.h"

template<class T>
class LManager
{
public:
	static LManager<T>& GetInstance()
	{
		static LManager<T> input;
		return input;
	}
public:
	ID3D11Device* m_pDevice = nullptr;
	ID3D11DeviceContext* m_pImmediateContext = nullptr;
	using LList = std::unordered_map<std::wstring, T*>;
public:
	LList m_map;
public:
	T* Load(std::wstring filePath);
	T* GetPtr(std::wstring key);
	bool Get(std::wstring key, T& managerType);
	void Set(ID3D11Device* pDevice, ID3D11DeviceContext* pImmediateContext);
	bool Release();
private:
	LManager() {}
public:
	virtual ~LManager() {}
};

template<class T>
void LManager<T>::Set(ID3D11Device* pDevice, ID3D11DeviceContext* pImmediateContext)
{
	m_pDevice = pDevice;
	m_pDevice->AddRef();
	m_pImmediateContext = pImmediateContext;
	m_pImmediateContext->AddRef();
}

template<class T>
T* LManager<T>::Load(std::wstring filePath)
{
	std::size_t found = filePath.find_last_of(L"/");
	std::wstring path = filePath.substr(0, found + 1);
	std::wstring key = filePath.substr(found + 1);

	T* data = GetPtr(key);

	if (data != nullptr)
	{
		return data;
	}

	T* managerType = new T;

	if (managerType->Load(m_pDevice, filePath))
	{
		m_map.insert(std::make_pair(key, managerType));
		return managerType;
	}

	delete managerType;
	return nullptr;
}

template<class T>
T* LManager<T>::GetPtr(std::wstring key)
{
	auto iter = m_map.find(key);

	if (iter == m_map.end())
	{
		return nullptr;
	}

	return iter->second;
}

template<class T>
bool LManager<T>::Get(std::wstring key, T& managerType)
{
	auto iter = m_map.find(key);

	if (iter == m_map.end())
	{
		return false;
	}
	managerType = *(iter->second);

	return true;
}

template<class T>
bool LManager<T>::Release()
{
	m_pDevice->Release();
	m_pImmediateContext->Release();
	for (auto& map : m_map)
	{
		map.second->Release();
		delete map.second;
	}
	
	m_map.clear();
	return true;
}
