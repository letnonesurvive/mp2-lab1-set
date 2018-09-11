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
	if (len <= 0)
	{
		throw "negative len";
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	pMem = new TELEM[bf.MemLen];
	for (int i = 0; i < bf.MemLen; i++)
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
	if (n >= 0&&n<=BitLen)
	{
		int num = n / BitLen;//в какой ячейке массива содержится бит
		int position = n % (sizeof(TELEM) * 8);//на какой позиции находится бит в ячейке массива
		pMem[num] = pMem[num] | GetMemMask(pMem[num]);
	}
	else throw "incorrect value";

}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n >= 0 && n <= BitLen)
	{
		int num = n / BitLen;
		int position = n % (sizeof(TELEM) * 8);
		pMem[num] = pMem[num] & (GetMemMask(pMem[num]));
	}
	else throw "negative index";
}
	

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n >= 0&&n<=BitLen)
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
	else throw "negative index";
}
//
//// битовые операции
//
TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (this->BitLen >= bf.BitLen)
	{
		this->BitLen = bf.BitLen;
		for (int i = 0; i <= bf.MemLen; i++)
			this->pMem[i] = bf.pMem[i];
	}
	else throw;
}

//int TBitField::operator==(const TBitField &bf) const // сравнение
//{
//	for (int i = 0; i < MemLen; i++)
//	{
//		if (i == MemLen - 1)
//			return 1;
//		if (this->pMem[i] == bf.pMem[i] && i != MemLen - 1)
//			continue;
//		if (this->pMem[i] != bf.pMem[i])
//		{
//			break;
//			return 0;
//		}
//	}
//}

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
