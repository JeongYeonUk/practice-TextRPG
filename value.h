#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <unordered_map> // 일반 map 보다 훨씬 빠름
#include <string>
#include <time.h>

using namespace std;

#include "defines.h"
#include "Flag.h"

template <typename T>
T Input()
{
	T	data;
	cin >> data;

	if (cin.fail())
	{
		cin.clear();
		cin.ignore(1024, '\n');
		return 0;
	}

	return data;
}

template<typename T>
void Safe_Delete_VecOrList(T& p)
{
	// typename을 사용하지 않으면
	// compiler는 T가 type인지 non-type인지 알 길이 없으므로
	// error 발생
	typename T::iterator iter;
	typename T::iterator iterEnd = p.end();

	for (iter = p.begin(); iter != iterEnd; ++iter)
	{
		SAFE_DELETE(*iter);
	}

	p.clear();
}

template<typename T>
void Safe_Delete_Map(T& p)
{
	// typename을 사용하지 않으면
	// compiler는 T가 type인지 non-type인지 알 길이 없으므로
	// error 발생
	typename T::iterator iter;
	typename T::iterator iterEnd = p.end();

	for (iter = p.begin(); iter != iterEnd; ++iter)
	{
		SAFE_DELETE(iter->second);
	}

	p.clear();
}

typedef struct _tagCharacterInfo
{
	int iAttackMin;
	int iAttackMax;
	int iArmorMin;
	int iArmorMax;
	int iHP;
	int iHPMax;
	int iMP;
	int iMPMax;
	int iLevel;
	int iExp;
}CHARACTERINFO, *PCHARACTERINFO;

typedef struct _tagItemInfo
{
	ITEM_TYPE	eType;
	string		strTypeName;
	int			iPrice;
	int			iSell;
	string		strDesc;
}ITEMINFO, *PITEMINFO;

static int g_iLvUpTable[MAX_LEVEL] = { 4000, 10000, 20000, 35000, 52000, 72000, 90000, 130000, 170000, 250000 };

typedef struct _tagLevelUpInfo
{
	int iAttackMin;
	int iAttackMax;
	int iArmorMin;
	int iArmorMax;
	int iHP;
	int iMP;
}LEVELUPINFO, *PLEVELUPINFO;