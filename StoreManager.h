#pragma once

#include "value.h"



class CStoreManager
{
private:
	vector<class CStore*> m_vecStore;

public:
	bool Init();
	void Run();

private:
	CStore * CreateStore(STORE_TYPE eType);
	int OutputMenu();

	DECLARE_SINGLE(CStoreManager);
};

