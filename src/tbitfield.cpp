// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len <= 0) {
		throw - 1;
	}
	BitLen = len;
	MemLen =  len / 32 + 1;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++) {
		pMem[i] = 0;
	}
}

TBitField::TBitField(const TBitField &b) // конструктор копирования
{
	BitLen = b.BitLen;
	MemLen = b.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++) {
		pMem[i] = b.pMem[i];
	}
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n < 0 || n > BitLen) {
		throw - 1;
	}
	return  BitLen / 32;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if (n < 0 || n > BitLen) {
		throw - 1;
	}
	int shift = n % 32;
	return 1 << shift;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n < 0 || n > BitLen) {
		throw - 1;
	}
	TELEM mask = GetMemMask(n);
	int index = GetMemIndex(n);
	pMem[index] = pMem[index] | mask;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n < 0 || n > BitLen) {
		throw - 1;
	}
	TELEM mask = ~GetMemMask(n);
	int index = GetMemIndex(n);
	pMem[index] = pMem[index] & mask;
}

TELEM TBitField::GetBit(const int n) const // получить значение бита
{
	if (n < 0 || n > BitLen) {
		throw - 1;
	}
	TELEM mask = GetMemMask(n);
	int index = GetMemIndex(n);
	TELEM res = pMem[index] & mask;
	return res;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (*this != bf) {
		delete[]pMem;
		pMem = new TELEM[bf.MemLen];
		MemLen = bf.MemLen;
	}
	BitLen = bf.BitLen;
	for (int i = 0; i < MemLen; i++) {
		pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen) { return false; }
	for (int i = 0; i < MemLen - 1; i++) {
		if (pMem[i] != bf.pMem[i]) { return false; }
	}
	for (int i = (MemLen - 1) * 32; i < BitLen; i++) {
		if (GetBit(i) != bf.GetBit(i)) { return false; }
	}
  return true;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen) { return 1; }
	for (int i = 0; i < MemLen - 1; i++) {
		if (pMem[i] != bf.pMem[i]) { return 1; }
	}
	for (int i = (MemLen - 1) * 32; i < BitLen; i++) {
		if (GetBit(i) != bf.GetBit(i)) { return 1; }
	}
	return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	return*this;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	return* this;
}

TBitField TBitField::operator~(void) // отрицание
{
	return*this;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	return istr;

}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	return ostr;

}
