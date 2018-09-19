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
		MemLen = (len / (sizeof(TELEM) * 8))+1;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
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
	MemLen = bf.MemLen;
	BitLen = bf.BitLen;
	for (int i = 0; i < bf.MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[] pMem;
}
int TBitField::min(int left, int right)
{
	if (left <= right)
		return left;
	else return right;
}
int TBitField::max(int left,int right)
{
	if (left >= right)
		return left;
	else return right;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if(n>=0)
		return pMem[n];
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
	if (n >= 0&&n<=BitLen)
	{
		int num = n / (sizeof(TELEM) * 8);//в какой ячейке массива содержится бит
		int position = n % (sizeof(TELEM) * 8);//на какой позиции находится бит в ячейке массива
		pMem[num] = pMem[num] | GetMemMask(position);
	}
	else throw "incorrect value";

}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n >= 0 && n <= BitLen)
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
	if (n >= 0&&n<=BitLen)
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
	if (BitLen == bf.BitLen)
	{
		for (int i = 0; i < bf.MemLen; i++)
			pMem[i] = bf.pMem[i];
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		return *this;
	}
	if ((BitLen > bf.BitLen)||(BitLen<bf.BitLen))
	{
		delete[] pMem;
		pMem = new TELEM[bf.MemLen];
		for (int i = 0; i < bf.MemLen; i++)
			pMem[i] = bf.pMem[i];
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		return *this;
	}
}

bool TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen)
		return 0;
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

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen)
		return 0;
	else
	{
		for (int i = 0; i < bf.MemLen; i++)
		{
			if (this->pMem[i] == bf.pMem[i])
				return false;
		}
	}
	return true;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
		TBitField tmp(max(this->GetLength(),bf.GetLength()));
		for (int i = 0; i <min(this->MemLen,bf.MemLen) ; i++)
		{
			tmp.pMem[i] = tmp.pMem[i] | (this->pMem[i] | bf.pMem[i]);
		}
		return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	TBitField tmp(max(this->GetLength(), bf.GetLength()));
	for (int i = 0; i < min(this->MemLen, bf.MemLen); i++)
	{
		tmp.pMem[i] = tmp.pMem[i] | (this->pMem[i] & bf.pMem[i]);
	}
	return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TELEM basis = BitLen - ((MemLen - 1) * sizeof(TELEM) * 8);
	TELEM tmp = pow(2,basis-1)-1;
	for (int i = 0; i < this->MemLen; i++)
	{
		if(i==MemLen-1)
			pMem[i] = (~pMem[i])&tmp;
		else
		pMem[i] = ~pMem[i];
	}
	return *this;
}

//// ввод/вывод
//
istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	return ostr;
}
