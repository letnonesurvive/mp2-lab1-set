// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля
#include "tset.h"
#include <conio.h>
#include "Windows.h"
TSet::TSet(int mp = 0) : BitField(mp)
{
	MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.MaxPower)
{
	this->BitField = s.BitField;
	this->MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf.GetLength())
{
	MaxPower = bf.GetLength();
}

TSet::operator TBitField()
{
	return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	BitField.ClrBit(Elem);
}
//
//// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	this->BitField = s.BitField;
	this->MaxPower = s.MaxPower;
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	if (this->MaxPower == s.MaxPower)
	{
		if (BitField == s.BitField)
			return 1;
		//if (BitField != s.BitField)
		return 0;
	}
	else return 0;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	if (this->MaxPower == s.MaxPower)
	{
		if (BitField != s.BitField)
			return 1;
		return 0;
	}
	else return 1;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	TSet tmp;
	tmp.BitField = this->BitField | s.BitField;
	tmp.MaxPower = tmp.BitField.GetLength();
	return tmp;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	if (Elem > this->MaxPower)
		throw "out of range";
	TSet tmp(this->MaxPower);
	this->BitField.SetBit(Elem);
	tmp.BitField = BitField;
	tmp.MaxPower = this->GetMaxPower();
	return tmp;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{

	if (Elem > this->MaxPower)
		throw "out of range";
	TSet tmp(this->MaxPower);
	this->BitField.ClrBit(Elem);
	tmp.BitField = BitField;
	tmp.MaxPower = this->GetMaxPower();
	return tmp;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	TSet tmp;
	tmp.BitField = this->BitField & s.BitField;
	tmp.MaxPower = tmp.BitField.GetLength();
	return tmp;
}

TSet TSet::operator~(void) // дополнение
{
	BitField = ~BitField;
	return *this;
}
//
//// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	int a;
	while (1)
	{
		cin >> a;
		s.InsElem(a);
		if (a = _getch() == 13)
			break;
		a = 0;
	}
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	ostr << "{";
	for (int i = 0; i < s.MaxPower; i++)
	{
		if (s.IsMember(i))
			ostr << i << " ";
	}
	ostr << "}";
	return ostr;
}
