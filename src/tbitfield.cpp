// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len > 0)
	{
		BitLen = len;
		MemLen = len / (sizeof(TELEM) * 8);
		pMem = new TELEM[MemLen];
		for (int i = 0; i <= MemLen; i++)
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
	pMem = new TELEM[bf.BitLen];
	for (int i = 0; i < bf.BitLen; i++)
		pMem[i] = bf.pMem[i];
	BitLen = bf.BitLen;
}

TBitField::~TBitField()
{
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return MemLen;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
		TELEM mask = 1;
		int position = n % (sizeof(TELEM) * 8);//на какой позиции находится бит в ячейке массива
		mask = mask << position;
		if(GetBit(n)==1)
			return ~mask;
		if (GetBit(n) == 0)
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
	int num = n / BitLen;//в какой ячейке массива содержится бит
	int position = n % (sizeof(TELEM) * 8);//на какой позиции находится бит в ячейке массива
	pMem[num] = pMem[num] | GetMemMask(pMem[num]);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	int num = n / BitLen;
	int position = n % (sizeof(TELEM) * 8);
	pMem[num] = pMem[num] & ~(GetMemMask(pMem[num]));
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	int a = 1;
	int num = n / BitLen;//в какой ячейке массива содержится бит
	int position = n % (sizeof(TELEM) * 8);//на какой позиции находится бит в ячейке массива
	a = a << position;
	if (pMem[num] & a == a)
		return 1;
	if (pMem[num] & a == 0)
		return 0;
}
//
//// битовые операции
//
//TBitField& TBitField::operator=(const TBitField &bf) // присваивание
//{
//}
//
//int TBitField::operator==(const TBitField &bf) const // сравнение
//{
//  return 0;
//}
//
//int TBitField::operator!=(const TBitField &bf) const // сравнение
//{
//  return 0;
//}
//
//TBitField TBitField::operator|(const TBitField &bf) // операция "или"
//{
//}
//
//TBitField TBitField::operator&(const TBitField &bf) // операция "и"
//{
//}
//
//TBitField TBitField::operator~(void) // отрицание
//{
//}
//
//// ввод/вывод
//
//istream &operator>>(istream &istr, TBitField &bf) // ввод
//{
//}
//
//ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
//{
//}
