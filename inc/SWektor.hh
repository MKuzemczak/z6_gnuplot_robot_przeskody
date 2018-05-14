#ifndef SWEKTOR_HH
#define SWEKTOR_HH

/*!
  * \file
  * \brief Zawiera definicję klasy SWektor
  */

#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <iomanip>
#include <sstream>
#include <typeinfo>
#include <QDebug>

#include "rozmiar.h"

//#define EPSILON 0.0000001

/*!
 * \brief Klasa SWektor, wektor zawierający Wymiar elementów typu Typ
 */
template <typename Typ, int Wymiar>
class SWektor {
  Typ tab[Wymiar];

  public:

  static double liczba_Wektorow;
  /*!
   * \brief Konstruktor
   * Zeruje wszystkie elementy
   */
  SWektor();
  SWektor(const SWektor & w) ;
  SWektor(double x, double y, double z)
  {
      tab[0] = x;
      tab[1] = y;
      tab[2] = z;

      liczba_Wektorow++;
  }

  ~SWektor() {liczba_Wektorow--;}

  const SWektor <Typ, Wymiar> operator + (const SWektor <Typ, Wymiar> & V) const;
  const SWektor <Typ, Wymiar> operator - (const SWektor <Typ, Wymiar> & V) const;
  const Typ operator * (const SWektor <Typ, Wymiar> & V) const;
  const SWektor <Typ, Wymiar> operator * (const Typ l) const;
  const SWektor <Typ, Wymiar> operator / (const Typ l) const;
	
  const	SWektor <Typ, Wymiar> operator += (const SWektor <Typ, Wymiar> & V);
  const	SWektor <Typ, Wymiar> operator += (const Typ l);
  const	SWektor <Typ, Wymiar> operator -= (const SWektor <Typ, Wymiar> & V);
  const	SWektor <Typ, Wymiar> operator -= (const Typ l);
  const	SWektor <Typ, Wymiar> operator *= (const Typ l);
  const	SWektor <Typ, Wymiar> operator /= (const Typ l);
  const bool operator == (const SWektor <Typ, Wymiar> & V);

  const SWektor <Typ, Wymiar> cross (const SWektor <Typ, Wymiar> & V) const;

	Typ & operator [] (const int index);
	const Typ & operator [] (const int index) const;


    /*!
     * \brief Moduł wektora
     * \return Pierwiastej z sumy kwadratów elementów wektora
     */
	const double mod() const;

    /*!
     * \brief Zamienia dwa elementy wektora miejscami
     * \param el1 - indeks pierwszego elementu
     * \param el2 - indeks drugiego elemntu
     */
	void zamienElementy (const int el1, const int el2);

    /*!
     * \brief Setter wektora
     * \param V - tablica z elementami do dodania do wektora.
     * \pre V musi zawierać przynajmniej tyle elementów, co wektor.
     *          Gdy będzie większa, do wektora zostaną wpisane pierwsze elementy.
     */
	void set(const Typ *V);

    /*!
     * \brief Szerokość najszerszej w zapisie liczby w wektorze
     *
     * \return Szerokość, w liczbie znaków, liczby, która wypisana na wyjście
     *          standardowe jest najszersza
     */
	int szer() const;
};

template<typename Typ, int Wymiar>
double SWektor<Typ, Wymiar>::liczba_Wektorow = 0;

// konstruktor klasy SWektor
template <typename Typ, int Wymiar>
SWektor<Typ, Wymiar>::SWektor()
{
    for (int i = 0; i < Wymiar; i++)
    {
        tab[i] = 0;
    }

    liczba_Wektorow++;
}

template <typename Typ, int Wymiar>
SWektor<Typ, Wymiar>::SWektor(const SWektor & w)
{
    for (int i = 0; i < Wymiar; i++)
    {
        tab[i] = w.tab[i];
    }

    liczba_Wektorow++;

}

template <typename Typ, int Wymiar>
const SWektor <Typ, Wymiar> SWektor<Typ, Wymiar>::cross (const SWektor <Typ, Wymiar> & V) const
{
    SWektor<Typ, Wymiar> w;

    if(Wymiar == 3)
    {
        SWektor<Typ, Wymiar> ret(tab[1] * V[2] - tab[2] * V[1],
                                 (tab[2] * V[0] - tab[0] * V[2]),
                                 tab[0] * V[1] - tab[1] * V[0]);

        return ret;
    }

    return w;
}

/****************************************************************************
*	Przeciazenie operatora dla wczytywania SWektora ze strumienia wejsciowego.
*	Wczytuje w formacie liczba(znak_bialy)liczba(znak_bialy)liczba...
*
*		Strm - strumien wejsciowy
*		Wek	 - zawiera wartosci wczytane.
*
* Zwraca strumien wejsciowy z ktorym zostalo wywolane.
*****************************************************************************/
template <typename Typ, int Wymiar>
std::istream& operator >> (std::istream &Strm, SWektor <Typ, Wymiar> &Wek)
{
    for (int i = 0; i < Wymiar; i++)
    {
        Strm >> Wek[i];
    }

    return Strm;
}

template <typename Typ>
int szerLiczby(Typ l)
{
	int ret;
	std::stringstream wyswietlanaLiczba;

	//wyswietlanaLiczba << std::fixed;
	wyswietlanaLiczba << std::setprecision(DOKLADNOSC);
	wyswietlanaLiczba << l;
	ret = wyswietlanaLiczba.str().length();

	return ret;
}

/****************************************************************************
*	Przeciazenie operatora dla wyswietlenia SWektora na strumien wyjsciowy.
*	Wyswietla w formacie:
*
*
*		Strm - strumien wyjsciowy
*		Wek	 - zawiera SWektor do wyswietlenia.
*
* Zwraca strumien wyjsciowy z ktorym zostalo wywolane.
*****************************************************************************/
template <typename Typ, int Wymiar>
std::ostream& operator << (std::ostream &Strm, const SWektor <Typ, Wymiar> &Wek)
{
	for (int i = 0; i < Wymiar - 1; i++)
	{
		Strm << Wek[i] << " ";
	}

	Strm << Wek[Wymiar - 1];

	return Strm;
}

template <typename Typ, int Wymiar>
QDebug & operator << (QDebug &Strm, const SWektor <Typ, Wymiar> &Wek)
{
    for (int i = 0; i < Wymiar - 1; i++)
    {
        Strm << Wek[i] << " ";
    }

    Strm << Wek[Wymiar - 1];

    return Strm;
}


template <typename Typ, int Wymiar>
const bool SWektor <Typ, Wymiar>::operator == (const SWektor <Typ, Wymiar> & V)
{
    for(int i = 0; i < Wymiar; i++)
    {
        if(fabs(tab[i] - V[i]) > EPSILON)
            return false;
    }

    return true;
}

template <typename Typ, int Wymiar>
const SWektor <Typ, Wymiar> SWektor <Typ, Wymiar>::operator + (const SWektor <Typ, Wymiar> & V) const
{
    SWektor <Typ, Wymiar> ret;

    for(int i = 0; i < Wymiar; i++) 
    {
        ret[i] = tab[i] + V[i];
    }

    return ret;
}

template <typename Typ, int Wymiar>
const SWektor <Typ, Wymiar> SWektor <Typ, Wymiar>::operator - (const SWektor <Typ, Wymiar> & V) const
{
    SWektor <Typ, Wymiar> ret;

    for(int i = 0; i < Wymiar; i++) 
    {
        ret[i] = tab[i] - V[i];
    }

    return ret;
}

template <typename Typ, int Wymiar>
const Typ SWektor <Typ, Wymiar>::operator*(const SWektor <Typ, Wymiar> & V) const
{
    Typ ret;

		ret = 0;

    for(int i = 0; i < Wymiar; i++) 
    {
        ret += tab[i] * V.tab[i];
    }

    return ret;    
}

template <typename Typ, int Wymiar>
const SWektor <Typ, Wymiar> SWektor <Typ, Wymiar>::operator*(const Typ l) const
{
    SWektor <Typ, Wymiar> ret;

    for(int i = 0; i < Wymiar; i++) 
    {
        ret[i] = tab[i] * l;
    }

    return ret;    
}

template <typename Typ, int Wymiar>
const SWektor <Typ, Wymiar> SWektor <Typ, Wymiar>::operator/(const Typ l) const
{
    SWektor <Typ, Wymiar> ret;

    for(int i = 0; i < Wymiar; i++) 
    {
        ret[i] = tab[i] / l;
    }

    return ret;
}

template <typename Typ, int Wymiar>
const SWektor <Typ, Wymiar> SWektor <Typ, Wymiar>::operator += (const SWektor <Typ, Wymiar> & V)
{
	for (int i = 0; i < Wymiar; i++)
	{
		tab[i] += V.tab[i];
	}
	
	return *this;
}

template <typename Typ, int Wymiar>
const SWektor <Typ, Wymiar> SWektor <Typ, Wymiar>::operator += (const Typ l)
{
	for (int i = 0; i < Wymiar; i++)
	{
		tab[i] += l;
	}

	return *this;
}

template <typename Typ, int Wymiar>
const SWektor <Typ, Wymiar> SWektor <Typ, Wymiar>::operator -= (const SWektor <Typ, Wymiar> & V)
{
	for (int i = 0; i < Wymiar; i++)
	{
		tab[i] -= V.tab[i];
	}
	
	return *this;
}

template <typename Typ, int Wymiar>
const SWektor <Typ, Wymiar> SWektor <Typ, Wymiar>::operator -= (const Typ l)
{
	for (int i = 0; i < Wymiar; i++)
	{
		tab[i] -= l;
	}

	return *this;
}

template <typename Typ, int Wymiar>
const SWektor <Typ, Wymiar> SWektor <Typ, Wymiar>::operator *= (const Typ l)
{
	for (int i = 0; i < Wymiar; i++)
	{
		tab[i] *= l;
	}
	
	return *this;
}

template <typename Typ, int Wymiar>
const SWektor <Typ, Wymiar> SWektor <Typ, Wymiar>::operator /= (const Typ l)
{
	for (int i = 0; i < Wymiar; i++)
	{
		tab[i] /= l;
	}
	
	return *this;
}

template <typename Typ, int Wymiar>
const SWektor <Typ, Wymiar> operator * (const Typ l, const SWektor <Typ, Wymiar> & V)
{
	SWektor <Typ, Wymiar> ret;

	for (int i = 0; i < Wymiar; i++)
	{
		ret[i] = V[i] * l;
	}

	return ret;
}

template <typename Typ, int Wymiar>
void SWektor <Typ, Wymiar>::zamienElementy(const int el1, const int el2)
{
	Typ tmp;

	tmp = tab[el1];
	tab[el1] = tab[el2];
	tab[el2] = tmp;
}

template <typename Typ, int Wymiar>
void SWektor <Typ, Wymiar>::set(const Typ *V)
{
	for (int i = 0; i < Wymiar; i++)
	{
		tab[i] = V[i];
	}
}

template <typename Typ, int Wymiar>
Typ &SWektor <Typ, Wymiar>::operator[](const int index)
{
    if(index >= Wymiar || index < 0)
    {
        std::cerr << "Error: Indeks SWektora poza granicami.\nWyjscie z programu.\n";
        exit(0);
    }

    return tab[index];
}

template <typename Typ, int Wymiar>
const Typ &SWektor <Typ, Wymiar>::operator[](const int index) const
{
    if(index >= Wymiar || index < 0)
    {
        std::cerr << "Error: Indeks SWektora poza granicami.\nWyjscie z programu.\n";
        exit(0);
    }

    return tab[index];
}

template <typename Typ, int Wymiar>
int SWektor <Typ, Wymiar>::szer() const
{
	int ret = 0, szerokoscWiersza = 0;

	for (int i = 0; i < Wymiar; i++)
	{
		// uzywam std::stringstream zeby formatowanie liczby bylo takie samo jak przy wyswietlaniu
		std::stringstream wyswietlanaLiczba;

		//wyswietlanaLiczba << std::fixed;
		wyswietlanaLiczba << std::setprecision(DOKLADNOSC);
		wyswietlanaLiczba << tab[i];
		szerokoscWiersza = wyswietlanaLiczba.str().length();

		if (szerokoscWiersza > ret)
			ret = szerokoscWiersza;

	}

	return ret;
}



#endif
