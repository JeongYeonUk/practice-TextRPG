#include "Store.h"
#include "ItemWeapon.h"
#include "ItemArmor.h"

CStore::CStore()
{
}


CStore::~CStore()
{
	Safe_Delete_VecOrList(m_vecItem);
}

CItem * CStore::CreateItem(const string & strName, ITEM_TYPE eType, int iPrice, int iSell, const string & strDesc)
{
	CItem* pItem = nullptr;

	switch (eType)
	{
	case IT_WEAPON:
		pItem = new CItemWeapon;
		break;
	case IT_ARMOR:
		pItem = new CItemArmor;
		break;
	default:
		break;
	}

	if (!pItem->Init())
	{
		SAFE_DELETE(pItem);
		return NULL;
	}

	pItem->SetName(strName);
	pItem->SetItemInfo(eType, iPrice, iSell, strDesc);

	m_vecItem.push_back(pItem);

	return pItem;
}

void CStore::OutputItemList()
{
	for (size_t i = 0; i < m_vecItem.size(); ++i)
	{
		cout << i + 1 << ". ";
		m_vecItem[i]->Render();
		cout << endl;
	}
}

void CStore::OutputTag(const string & StoreName)
{
	cout << "======================" << StoreName << "======================" << endl;
}
