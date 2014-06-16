#ifndef struktury_h
#define struktury_h
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <iostream>
#include <stack>
#include <conio.h>
#include <string>
#include <vector>
#include <Windows.h>
using namespace std;
#define _CRT_SECURE_NO_WARNINGS



// definicja umownych kolorow w strukturach
enum kolor {bialy, czarny, zielony, czerwony, niewidzialny, brak, zadne};

// definicja mozliwych postaci figury
enum status {pionek, damka};

//definicja stanu gracza
enum stan {zwyciezca, przegrany, remis, w_trakcie_gry};

// definicja stanow tury
enum stan_tury {pods_bicie, czyn_bicie, pods_ruch, czyn_ruch};

// struktura pola
struct Pion_s
{
	kolor kolor_pionu;
	status status;
	bool niezbity;
	float pozycja_x;
	float pozycja_y;
	ALLEGRO_BITMAP *grafika;
	ALLEGRO_SAMPLE *dzwiek[6];
};

// struktura pionu
struct Pole_s
{
	kolor kolor_pola;
	kolor podswietlenie;
	kolor zajete;
	bool zaznaczone;
	int pozycja_x;
	int pozycja_y;
	ALLEGRO_BITMAP *grafika;
};

// struktura gracza
struct Gracz_s
{
	unsigned nr_gracza;
	kolor kolor_gracza;
	stan stan;
	
};

// wirtualna struktura pola
struct ai_Pole_s
{
	kolor kolor_pola;
	kolor zajete;
	int pozycja_x;
	int pozycja_y;
};

// wirtualna struktura pionu
struct ai_Pion_s
{
	kolor kolor_pionu;
	status status;
	bool niezbity;
	float pozycja_x;
	float pozycja_y;
};

// struktura decyzyjna dla algorytmu minmax
struct decyzja
{
	int eval;
	int x;
	int y;
	int c;
	bool decyzja_czy_bicie;
};

// zamiana koloru pola/figury na przeciwny
kolor zamiana (kolor gracz1);

//odswiezenie planszy - mechanika gry
void odswiezenie_mechanika (Pole_s **plansza);

// odswiezenie planszy i pionow - grafika
void odswiezenie_grafika(Pole_s **szachownica, Pion_s *piony, int numer, ALLEGRO_BITMAP **guziki);

// odtwarzanie glosu postaci
void glos (Pion_s *pion, int c, stan_tury stan);

// kopiowanie tablicy dwuwymiarowej pol
Pole_s **kopiuj_pola(Pole_s **old_pole, int n);

// kopiowanie tablicy dwuwymiarowej pol do nowej struktury
ai_Pole_s **ai_kopiuj_pola(Pole_s **old_pole, int n);

// nowe kopiowanie
ai_Pole_s **si_ai_kopiuj_pola(ai_Pole_s **old_pole, int n);

// kopiowanie pionow
Pion_s *kopiuj_pion(Pion_s *old_pion, int n);

// kopiowanie pionow do struktury nowej
ai_Pion_s *ai_kopiuj_pion(Pion_s *old_pion, int n);

// nowe kopiowanie pionow
ai_Pion_s *si_ai_kopiuj_pion(ai_Pion_s *old_pion, int n);

// reset stanu gry do ustawien poczatkowych
void board_reset(Gracz_s gracz1, Pole_s **szachownica, Pion_s *f, int &biale_pionki, int &czarne_pionki, int &biale_damki, int &czarne_damki);

//zmiana gracza
Gracz_s zamiana_gracza(Gracz_s gracz);

#endif