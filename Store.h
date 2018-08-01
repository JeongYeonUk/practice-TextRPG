#pragma once

#include "value.h"

class CStore
{
protected:
	CStore();

public:
	virtual ~CStore();

private:
	friend class CStoreManager;

protected:
	vector<class CItem*>	m_vecItem;

protected:
	CItem * CreateItem(const string& strName, ITEM_TYPE eType, int iPrice, int iSell,
		const string& strDesc);
	void OutputItemList();
	void OutputTag(const string& StoreName);

public:
	virtual bool Init() = 0;
	virtual void Run() = 0;
};

