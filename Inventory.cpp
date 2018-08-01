#include "Inventory.h"
#include "Item.h"
#include "Player.h"
#include "ObjectManager.h"

DEFINITION_SINGLE(CInventory)

CInventory::CInventory() : m_iInvenMax(10)
{
}


CInventory::~CInventory()
{
	Safe_Delete_VecOrList(m_vecItem);
}

bool CInventory::Init()
{
	return true;
}

void CInventory::AddItem(CItem * pItem)
{
	if (m_iInvenMax == m_vecItem.size())
		return;
	m_vecItem.push_back(pItem);
}

void CInventory::Run()
{
	CPlayer*	pPlayer = (CPlayer*)GET_SINGLE(CObjectManager)->FindObject("Player");

	while (true)
	{
		system("cls");
		cout << "================= Inventory ================= " << endl << endl;
		pPlayer->Render();
		cout << endl;

		for (size_t i = 0; i < m_vecItem.size(); ++i)
		{
			cout << i + 1 << ". ";
			m_vecItem[i]->Render();
			cout << endl;
		}
		cout << m_vecItem.size() + 1 << ". 뒤로가기" << endl;
		cout << "장착할 아이템을 선택하세요 : ";
		int iItem = Input<int>();

		if (iItem < 1 || iItem > m_vecItem.size() + 1)
			continue;
		else if (iItem == m_vecItem.size() + 1)
			return;

		CItem* pEquip = pPlayer->Equip(m_vecItem[iItem - 1]);

		if (pEquip)
		{
			m_vecItem[iItem - 1] = pEquip;
		}
		else
		{
			vector<CItem*>::iterator iter = m_vecItem.begin() + (iItem - 1);

			m_vecItem.erase(iter);
		}
	}
}
