// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len > 0) {
		BitLen = len;
		MemLen = (len / (sizeof(TELEM) * 8) + 1);
		pMem = new TELEM[MemLen];
		for(size_t i = 0; i < MemLen; i++)
			pMem[i] = 0;
	}
	else {
		throw "Incorrect data lenth";
	}
}

//printf_s("%s%d", "TEST",BitLen);
TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (size_t i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return pMem[n];
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	TELEM mask = 1;
	return mask << (n % (sizeof(TELEM) * 8));
}
//
// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n >= 0 && n < BitLen) {
		int indexInt = n / (sizeof(TELEM) * 8);
		pMem[indexInt] = pMem[indexInt] | GetMemMask(n);
	}
	else {
		throw "Incorrect index";
	}
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n >= 0 && n < BitLen) {
		int indexInt = n / (sizeof(TELEM) * 8);
		pMem[indexInt] = pMem[indexInt] & (~GetMemMask(n));
	}
	else {
		throw "Incorrect index";
	}
}

int TBitField::GetBit(const int n) const // получить значение бита
{

	return 0;
}

// битовые операции
/*
TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
  return 0;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
}

TBitField TBitField::operator~(void) // отрицание
{
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
}
*/