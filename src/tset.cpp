// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp = 1) : BitField(mp)
{
    MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s)
    : BitField(s.BitField), MaxPower(s.MaxPower)
{
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) 
    : BitField(bf), MaxPower (bf.GetLength())
{
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

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
    BitField = s.BitField;
    MaxPower = s.MaxPower;
    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    if (BitField != s.BitField) { return 0; }
    return 1;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    if (BitField != s.BitField) { return 1; }
    return 0;
}

TSet TSet::operator+(const TSet &s) // объединение
{
    /*TSet res;
    res.BitField = BitField | s.BitField;
    res.MaxPower = max(MaxPower, s.MaxPower);*/
    return BitField | s.BitField;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    TSet res(*this);
    res.InsElem(Elem);
    return res;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    TSet res(*this);
    res.DelElem(Elem);
    return res;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    return BitField & s.BitField;
}

TSet TSet::operator~(void) // дополнение
{
    return ~BitField;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    istr.ignore(1);
    while (istr.peek() == ')') {
        int i = 0;
        istr >> i;
        s.InsElem(i);
    }
    istr.ignore(1);
    return istr;
    /*
    int i;
    char d;
    istr>>d;
    while(d!=')'){
        istr>>i;
        s.InsElem(i);
        istr>>d;
    }
    return
    */
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
    ostr << '{';
    for (int i = 0; i < s.MaxPower; i++) {
        if (s.BitField.GetBit(i)) {
            ostr << i<<' ';
        }
    }
    ostr << '}';
    return ostr;
}
