// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле
#include "iostream";
#include "string"
#include "tbitfield.h"
TBitField::TBitField(int len = 0)
{
	if (len >= 0)
	{
		BitLen = len;
		MemLen = (len / (sizeof(TELEM) * 8)) + 1;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
		{
			pMem[i] = 0;
		}
	}
	if (len < 0)
	{
		throw "negative len";
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	pMem = new TELEM[bf.MemLen];
	MemLen = bf.MemLen;
	BitLen = bf.BitLen;
	for (int i = 0; i < bf.MemLen; i++)
		pMem[i] = bf.pMem[i];
}
TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n >= 0)
		return n / sizeof(TELEM) * 8;
	else throw"negative value";
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	TELEM mask = 1;
	int position = n % (sizeof(TELEM) * 8);//на какой позиции находится бит в ячейке массива
	mask = mask << position;
	return mask;
}

//// доступ к битам битового поля
//
int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n >= 0 && n < BitLen)
	{
		int num = n / (sizeof(TELEM) * 8);//в какой ячейке массива содержится бит
		int position = n % (sizeof(TELEM) * 8);//на какой позиции находится бит в ячейке массива
		pMem[num] = pMem[num] | GetMemMask(position);
	}
	else throw "incorrect value";

}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n >= 0 && n < BitLen)
	{
		int num = n / (sizeof(TELEM) * 8);
		int position = n % (sizeof(TELEM) * 8);
		TELEM a = GetMemMask(position);
		pMem[num] = pMem[num] & (~GetMemMask(position));
	}
	else throw "negative index";
}


int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n >= 0 && n <= BitLen)
	{
		int a = 1;
		int num = n / (sizeof(TELEM) * 8);//в какой ячейке массива содержится бит
		int position = n % (sizeof(TELEM) * 8);//на какой позиции находится бит в ячейке массива
		a = a << position;
		if ((pMem[num] & a) == a)
			return 1;
		if ((pMem[num] & a) == 0)
			return 0;
	}
	else throw "negative index";
}
//
//// битовые операции
//
TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	delete[] pMem;
	pMem = new TELEM[bf.MemLen];
	for (int i = 0; i < bf.MemLen; i++)
		pMem[i] = bf.pMem[i];
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	return *this;

}

bool TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen)
		return false;
	else
	{
		for (int i = 0; i < bf.MemLen; i++)
		{
			if (this->pMem[i] != bf.pMem[i])
				return false;
		}
		return true;
	}
}

bool TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen)
		return true;
	else
	{
		for (int i = 0; i < bf.MemLen; i++)
		{
			if (this->pMem[i] != bf.pMem[i])
				return true;
		}
		return false;
	}
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int MaxSize = BitLen > bf.BitLen ? BitLen : bf.BitLen;
	int MinMemLen = MemLen < bf.MemLen ? MemLen : bf.MemLen;
	TBitField tmp(MaxSize);
	for (int i = 0; i < MinMemLen; i++)
	{
		tmp.pMem[i] = (this->pMem[i] | bf.pMem[i]);
	}
	return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int MaxSize = BitLen > bf.BitLen ? BitLen : bf.BitLen;
	int MinMemLen = MemLen < bf.MemLen ? MemLen : bf.MemLen;
	TBitField tmp(MaxSize);
	for (int i = 0; i < MinMemLen; i++)
	{
		tmp.pMem[i] = (this->pMem[i] & bf.pMem[i]);
	}
	return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
	int tmp = 0;
	int index = BitLen % (sizeof(TELEM) * 8);
	for (int i = 0; i < index; i++)
		tmp = tmp + pow(2, i);
	for (int i = 0; i < MemLen; i++)
	{
		if (i == MemLen - 1)
			pMem[i] = ~pMem[i] & tmp;
		else
			pMem[i] = ~pMem[i];
	}
	return *this;
}

//// ввод/вывод
//
istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	string str;
	istr >> str;
	int j = str.size() - 1;
	for (int i = 0; i < str.size(); i++, j--)
	{
		if (str[i] == '1')
			bf.SetBit(j);
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	int j = bf.BitLen - 1;
	for (int i = 0; i < bf.BitLen; i++, j--)
	{
		if (bf.GetBit(j) == 0)
			ostr << 0;
		else
			ostr << 1;
	}
	return ostr;
}
