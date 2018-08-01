#pragma once

#include "value.h"

class CObjectManager
{
private:
	unordered_map<string, class CObj*> m_mapObj;

public:
	bool Init();
	CObj* CreateObject(const string& strKey, OBJECT_TYPE eType);
	CObj* FindObject(const string& strKey);
	CObj* CloneObject(const string& strKey);
	CObj* CloneObject(STAGE_TYPE eType);

	DECLARE_SINGLE(CObjectManager);
};

