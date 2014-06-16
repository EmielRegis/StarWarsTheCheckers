
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
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

// definicja rozmiaru okna
const int dlugosc_okna = 860, szerokosc_okna = 640;

// definicja umownych kolorow w strukturach
enum kolor {bialy, czarny, zielony, czerwony, niewidzialny, brak, zadne};

// zamiana koloru pola/figury na przeciwny
kolor zamiana (kolor gracz1)
{
	switch (gracz1)
	{
	case bialy:
		return czarny;
		break;
	case czarny:
		return bialy;
		break;
	case zielony:
		return zadne;
		break;
	case czerwony:
		return zadne;
		break;
	default:
		return niewidzialny;
		break;
	}
}

// zmienna liczaca ruchy
int licznik;

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

// tablica - szachownica pol
Pole_s **pole;

// tworzenie szachownicy pol
Pole_s **tworzenie_szachownicy(ALLEGRO_BITMAP *pb, ALLEGRO_BITMAP *pcz, ALLEGRO_BITMAP **guziki)
{
	//al_clear_to_color(al_map_rgb_f(0.0,0.0,0.0));
	//al_draw_bitmap(guziki[0],0.0,0.0,NULL);
	//al_draw_bitmap(guziki[1],611.0,30.0,NULL);
	//al_draw_bitmap(guziki[2],686.0,300.0,NULL);
	//al_draw_bitmap(guziki[3],618.0,437.0,NULL);
	//al_draw_bitmap(guziki[4],618.0,537.0,NULL);
	
	Pole_s **p;
	p = new Pole_s*[10];
	for (unsigned i=0; i<10; i++)
	{
		p[i] = new Pole_s[10];
		for (unsigned j=0; j<10; j++)
		{
			if ((i != 0) && (i !=9) && (j !=0) && (j!=9))
			{
				if ((i+j)%2 == 1)
				{
					p[i][j].kolor_pola = czarny;
					p[i][j].grafika = pcz;
					//al_draw_bitmap (p[i][j].grafika,j*64, i*64,NULL);
					p[i][j].zajete = brak;
				}
				else
				{
					p[i][j].kolor_pola = bialy;
					p[i][j].zajete = brak;
					p[i][j].grafika = pb;
					//al_draw_bitmap (p[i][j].grafika,j*64, i*64, NULL);
				}
			}
			else
			{
				p[i][j].kolor_pola = niewidzialny;
				p[i][j].zajete = niewidzialny;
			}
			p[i][j].podswietlenie = zadne;
			p[i][j].pozycja_x = j;
			p[i][j].pozycja_y = i;
		}
	}
	return p;
}

// licznik figur 
int liczba_bialych;
int liczba_czarnych;
int liczba_bialych_damek;
int liczba_czarnych_damek;

// tablica - lista figur
Pion_s *figura;

// tworzenie listy figur
Pion_s *tworzenie_listy_figur(Gracz_s gracz1, Pole_s **szachownica, int &biale_pionki, int &czarne_pionki)
{

	Pion_s *f;
	unsigned c = 0;
	f = new Pion_s[24];
	for (unsigned i=1; i<=3; i++)
	{
		for (unsigned j=1; j<=8; j++)
		{
			if ((i+j)%2 == 1)
			{
				

				f[c].kolor_pionu = zamiana(gracz1.kolor_gracza);
				f[c].niezbity = true;
				f[c].status = pionek;
				f[c].pozycja_x = (float) j;
				f[c].pozycja_y = (float) i;
				if (gracz1.kolor_gracza == bialy)
				{
					f[c].grafika = al_load_bitmap("obrazy/bohaterowie/stormtrooper.png");
					f[c].dzwiek[0] = al_load_sample("dzwieki/glosy/stormtrooper1.ogg");
					f[c].dzwiek[1] = al_load_sample("dzwieki/glosy/stormtrooper2.ogg");
					f[c].dzwiek[2] = al_load_sample("dzwieki/glosy/stormtrooper3.ogg");
					f[c].dzwiek[3] = al_load_sample("dzwieki/glosy/stormtrooper4.ogg");
					f[c].dzwiek[4] = al_load_sample("dzwieki/glosy/stormtrooper5.ogg");
					f[c].dzwiek[5] = al_load_sample("dzwieki/glosy/stormtrooper6.ogg");

					//al_draw_bitmap (f[c].grafika, 64*f[c].pozycja_x, 64*f[c].pozycja_y, NULL);
					czarne_pionki++;
					szachownica[i][j].zajete = czarny;
				}
				else 
				{
					f[c].grafika = al_load_bitmap("obrazy/bohaterowie/r2d22.png");
					f[c].dzwiek[0] = al_load_sample("dzwieki/glosy/r2d21.ogg");
					f[c].dzwiek[1] = al_load_sample("dzwieki/glosy/r2d22.ogg");
					f[c].dzwiek[2] = al_load_sample("dzwieki/glosy/r2d23.ogg");
					f[c].dzwiek[3] = al_load_sample("dzwieki/glosy/r2d24.ogg");
					f[c].dzwiek[4] = al_load_sample("dzwieki/glosy/r2d25.ogg");
					f[c].dzwiek[5] = al_load_sample("dzwieki/glosy/r2d26.ogg");
					//al_draw_bitmap (f[c].grafika, 64*f[c].pozycja_x, 64*f[c].pozycja_y, NULL);
					biale_pionki++;
					szachownica[i][j].zajete = bialy;
				}
				c++;
			}
		}
	}

	for (unsigned i=6; i<=8; i++)
	{
		for (unsigned j=1; j<=8; j++)
		{
			if ((i+j)%2 == 1)
			{
			
				f[c].kolor_pionu = gracz1.kolor_gracza;
				f[c].niezbity = true;
				f[c].status = pionek;
				f[c].pozycja_x = (float) j;
				f[c].pozycja_y = (float) i;
				if (gracz1.kolor_gracza == czarny)
				{
					f[c].grafika = al_load_bitmap("obrazy/bohaterowie/stormtrooper.png");
					f[c].dzwiek[0] = al_load_sample("dzwieki/glosy/stormtrooper1.ogg");
					f[c].dzwiek[1] = al_load_sample("dzwieki/glosy/stormtrooper2.ogg");
					f[c].dzwiek[2] = al_load_sample("dzwieki/glosy/stormtrooper3.ogg");
					f[c].dzwiek[3] = al_load_sample("dzwieki/glosy/stormtrooper4.ogg");
					f[c].dzwiek[4] = al_load_sample("dzwieki/glosy/stormtrooper5.ogg");
					f[c].dzwiek[5] = al_load_sample("dzwieki/glosy/stormtrooper6.ogg");
					//al_draw_bitmap (f[c].grafika, 64*f[c].pozycja_x, 64*f[c].pozycja_y, NULL);
					czarne_pionki++;
					szachownica[i][j].zajete = czarny;
				}
				else 
				{
					f[c].grafika = al_load_bitmap("obrazy/bohaterowie/r2d22.png");
					f[c].dzwiek[0] = al_load_sample("dzwieki/glosy/r2d21.ogg");
					f[c].dzwiek[1] = al_load_sample("dzwieki/glosy/r2d22.ogg");
					f[c].dzwiek[2] = al_load_sample("dzwieki/glosy/r2d23.ogg");
					f[c].dzwiek[3] = al_load_sample("dzwieki/glosy/r2d24.ogg");
					f[c].dzwiek[4] = al_load_sample("dzwieki/glosy/r2d25.ogg");
					f[c].dzwiek[5] = al_load_sample("dzwieki/glosy/r2d26.ogg");
					//al_draw_bitmap (f[c].grafika, 64*f[c].pozycja_x, 64*f[c].pozycja_y, NULL);
					biale_pionki++;
					szachownica[i][j].zajete = bialy;
				}
				c++;
			}
		}
	}
	return f;
}

// reset stanu gry do ustawien poczatkowych
void board_reset(Gracz_s gracz1, Pole_s **szachownica, Pion_s *f, int &biale_pionki, int &czarne_pionki, int &biale_damki, int &czarne_damki)
{
	biale_pionki = 0;
	czarne_pionki = 0;
	biale_damki = 0;
	czarne_damki = 0;
	for (unsigned i=0; i<10; i++)
	{
		for (unsigned j=0; j<10; j++)
		{
			if ((i != 0) && (i !=9) && (j !=0) && (j!=9))
			{
				szachownica[i][j].zajete = brak;
			}
			else
			{
				szachownica[i][j].zajete = niewidzialny;
			}
			szachownica[i][j].podswietlenie = zadne;
			szachownica[i][j].pozycja_x = j;
			szachownica[i][j].pozycja_y = i;
		}
	}
	unsigned c = 0;
	for (unsigned i=1; i<=3; i++)
	{
		for (unsigned j=1; j<=8; j++)
		{
			if ((i+j)%2 == 1)
			{	
				f[c].kolor_pionu = zamiana(gracz1.kolor_gracza);
				f[c].niezbity = true;
				f[c].pozycja_x = (float) j;
				f[c].pozycja_y = (float) i;
				if (gracz1.kolor_gracza == bialy)
				{
					if (f[c].status == damka)
					{
						f[c].grafika = al_load_bitmap("obrazy/bohaterowie/stormtrooper.png");
						f[c].dzwiek[0] = al_load_sample("dzwieki/glosy/stormtrooper1.ogg");
						f[c].dzwiek[1] = al_load_sample("dzwieki/glosy/stormtrooper2.ogg");
						f[c].dzwiek[2] = al_load_sample("dzwieki/glosy/stormtrooper3.ogg");
						f[c].dzwiek[3] = al_load_sample("dzwieki/glosy/stormtrooper4.ogg");
						f[c].dzwiek[4] = al_load_sample("dzwieki/glosy/stormtrooper5.ogg");
						f[c].dzwiek[5] = al_load_sample("dzwieki/glosy/stormtrooper6.ogg");
						f[c].status = pionek;
					}
					czarne_pionki++;
					szachownica[i][j].zajete = czarny;
				}
				else 
				{
					if (f[c].status == damka)
					{
						f[c].grafika = al_load_bitmap("obrazy/bohaterowie/r2d22.png");
						f[c].dzwiek[0] = al_load_sample("dzwieki/glosy/r2d21.ogg");
						f[c].dzwiek[1] = al_load_sample("dzwieki/glosy/r2d22.ogg");
						f[c].dzwiek[2] = al_load_sample("dzwieki/glosy/r2d23.ogg");
						f[c].dzwiek[3] = al_load_sample("dzwieki/glosy/r2d24.ogg");
						f[c].dzwiek[4] = al_load_sample("dzwieki/glosy/r2d25.ogg");
						f[c].dzwiek[5] = al_load_sample("dzwieki/glosy/r2d26.ogg");
						f[c].status = pionek;
					}
					biale_pionki++;
					szachownica[i][j].zajete = bialy;
				}
				c++;
			}
		}
	}
	for (unsigned i=6; i<=8; i++)
	{
		for (unsigned j=1; j<=8; j++)
		{
			if ((i+j)%2 == 1)
			{
				f[c].kolor_pionu = gracz1.kolor_gracza;
				f[c].niezbity = true;
				f[c].pozycja_x = (float) j;
				f[c].pozycja_y = (float) i;
				if (gracz1.kolor_gracza == czarny)
				{
					if (f[c].status == damka)
					{
						f[c].grafika = al_load_bitmap("obrazy/bohaterowie/stormtrooper.png");
						f[c].dzwiek[0] = al_load_sample("dzwieki/glosy/stormtrooper1.ogg");
						f[c].dzwiek[1] = al_load_sample("dzwieki/glosy/stormtrooper2.ogg");
						f[c].dzwiek[2] = al_load_sample("dzwieki/glosy/stormtrooper3.ogg");
						f[c].dzwiek[3] = al_load_sample("dzwieki/glosy/stormtrooper4.ogg");
						f[c].dzwiek[4] = al_load_sample("dzwieki/glosy/stormtrooper5.ogg");
						f[c].dzwiek[5] = al_load_sample("dzwieki/glosy/stormtrooper6.ogg");
						f[c].status = pionek;
					}
					czarne_pionki++;
					szachownica[i][j].zajete = czarny;
				}
				else
				{
					if (f[c].status == damka)
					{
						f[c].grafika = al_load_bitmap("obrazy/bohaterowie/r2d22.png");
						f[c].dzwiek[0] = al_load_sample("dzwieki/glosy/r2d21.ogg");
						f[c].dzwiek[1] = al_load_sample("dzwieki/glosy/r2d22.ogg");
						f[c].dzwiek[2] = al_load_sample("dzwieki/glosy/r2d23.ogg");
						f[c].dzwiek[3] = al_load_sample("dzwieki/glosy/r2d24.ogg");
						f[c].dzwiek[4] = al_load_sample("dzwieki/glosy/r2d25.ogg");
						f[c].dzwiek[5] = al_load_sample("dzwieki/glosy/r2d26.ogg");
						f[c].status = pionek;
					}
					biale_pionki++;
					szachownica[i][j].zajete = bialy;
				}
				c++;
			}
		}
	}
}

// licznik ruchow bez bicia
unsigned bez_bicia;

//odswiezenie planszy - mechanika gry
void odswiezenie_mechanika (Pole_s **plansza)
{
	for (unsigned i=1; i<=8; i++)
	{
		for (unsigned j=1; j<=8; j++)
		{
			if (plansza[i][j].podswietlenie != zadne)
			{
				plansza[i][j].podswietlenie = zadne;
			}
		}
	}
}

// odswiezenie planszy i pionow - grafika
void odswiezenie_grafika(Pole_s **szachownica, Pion_s *piony, int numer, ALLEGRO_BITMAP **guziki)
{
	al_clear_to_color(al_map_rgb_f(0.0,0.0,0.0));
	al_draw_bitmap(guziki[0],0.0,0.0,NULL);
	al_draw_bitmap(guziki[1],611.0,30.0,NULL);
	al_draw_bitmap(guziki[2],686.0,300.0,NULL);
	al_draw_bitmap(guziki[3],618.0,437.0,NULL);
	al_draw_bitmap(guziki[4],618.0,537.0,NULL);
	for (unsigned i=0; i<10; i++)
	{
		for (unsigned j=0; j<10; j++)
		{
			if ((i != 0) && (i !=9) && (j !=0) && (j!=9))
			{
				if ((i+j)%2 == 1)
				{
					al_draw_bitmap (szachownica[i][j].grafika,j*64, i*64,NULL);
				}
				else
				{
					al_draw_bitmap (szachownica[i][j].grafika,j*64, i*64,NULL);
				}
			}
		}
	}
	if (numer == 1)
	{
		for (int k=0; k<24;k++)
		{
			if (piony[k].niezbity == true)
			
			{				
				if (piony[k].kolor_pionu == czarny)
				{
					al_draw_bitmap (piony[k].grafika, 64*piony[k].pozycja_x, 64*piony[k].pozycja_y, NULL);
					if (piony[k].status == damka)
					{
						al_draw_bitmap (piony[k].grafika, 64*piony[k].pozycja_x, 64*piony[k].pozycja_y, NULL);
					}
				}
				else if (piony[k].kolor_pionu == bialy)
				{
					al_draw_bitmap (piony[k].grafika, 64*piony[k].pozycja_x, 64*piony[k].pozycja_y, NULL);
					if (piony[k].status == damka)
					{
						al_draw_bitmap (piony[k].grafika, 64*piony[k].pozycja_x, 64*piony[k].pozycja_y, NULL);
					}
				}
			}
		}
	}
	else
	{
		for (int k=23; k>=0;k--)
		{
			if (piony[k].niezbity == true)
			
			{				
				if (piony[k].kolor_pionu == czarny)
				{
					al_draw_bitmap (piony[k].grafika, 64*piony[k].pozycja_x, 64*piony[k].pozycja_y, NULL);
					if (piony[k].status == damka)
					{
						al_draw_bitmap (piony[k].grafika, 64*piony[k].pozycja_x, 64*piony[k].pozycja_y, NULL);
					}
				}
				else if (piony[k].kolor_pionu == bialy)
				{
					al_draw_bitmap (piony[k].grafika, 64*piony[k].pozycja_x, 64*piony[k].pozycja_y, NULL);
					if (piony[k].status == damka)
					{
						al_draw_bitmap (piony[k].grafika, 64*piony[k].pozycja_x, 64*piony[k].pozycja_y, NULL);
					}
				}
			}
		}
	}
	
	al_flip_display();
}

// odtwarzanie glosu postaci
void glos (Pion_s *pion, int c, stan_tury stan)
{
	
	int x = rand()% 3;
	int y = rand()% 3 + 3;
	al_stop_samples();
	switch (stan)
	{
	case pods_bicie:
		al_play_sample(pion[c].dzwiek[x], 1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
		break;
	case pods_ruch:
		al_play_sample(pion[c].dzwiek[x], 1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
		break;
	case czyn_bicie:
		al_play_sample(pion[c].dzwiek[y], 1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
		break;
	case czyn_ruch:
		al_play_sample(pion[c].dzwiek[y], 1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
		break;
	default:
		break;
	}
	x=0;
	y=0;
}

// sprawdzenie - preksztalcenie w damke
void czy_damka(Gracz_s gracz, Pole_s **pola, Pion_s *pion, int c, int &biale_damki, int &czarne_damki, ALLEGRO_BITMAP **guziki)
{
	if ((gracz.nr_gracza == 1) && (pion[c].pozycja_y == 1)&&(pion[c].status != damka))
	{
		pion[c].status = damka;
		if(pion[c].kolor_pionu == czarny)
		{
			pion[c].grafika = al_load_bitmap("obrazy/bohaterowie/darthvader1.png");
			al_draw_bitmap(pion[c].grafika,pion[c].pozycja_x, pion[c].pozycja_y,NULL);
			odswiezenie_grafika(pola, pion, gracz.nr_gracza, guziki);
			pion[c].dzwiek[0] = al_load_sample("dzwieki/glosy/darthvader1.ogg");
			pion[c].dzwiek[1] = al_load_sample("dzwieki/glosy/darthvader2.ogg");
			pion[c].dzwiek[2] = al_load_sample("dzwieki/glosy/darthvader3.ogg");
			pion[c].dzwiek[3] = al_load_sample("dzwieki/glosy/darthvader4.ogg");
			pion[c].dzwiek[4] = al_load_sample("dzwieki/glosy/darthvader5.ogg");
			pion[c].dzwiek[5] = al_load_sample("dzwieki/glosy/darthvader7.ogg");
			al_play_sample(pion[c].dzwiek[0],1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
			czarne_damki++;
		}
		else
		{
			pion[c].grafika = al_load_bitmap("obrazy/bohaterowie/masteryoda2.png");
			al_draw_bitmap(pion[c].grafika,pion[c].pozycja_x, pion[c].pozycja_y,NULL);
			odswiezenie_grafika(pola, pion, gracz.nr_gracza, guziki);
			pion[c].dzwiek[0] = al_load_sample("dzwieki/glosy/masteryoda1.ogg");
			pion[c].dzwiek[1] = al_load_sample("dzwieki/glosy/masteryoda2.ogg");
			pion[c].dzwiek[2] = al_load_sample("dzwieki/glosy/masteryoda3.ogg");
			pion[c].dzwiek[3] = al_load_sample("dzwieki/glosy/masteryoda4.ogg");
			pion[c].dzwiek[4] = al_load_sample("dzwieki/glosy/masteryoda5.ogg");
			pion[c].dzwiek[5] = al_load_sample("dzwieki/glosy/masteryoda6.ogg");
			al_play_sample(pion[c].dzwiek[0],1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
			biale_damki++;
		}
	}
	if ((gracz.nr_gracza == 2) && (pion[c].pozycja_y == 8)&&(pion[c].status != damka))
	{
		pion[c].status = damka;
		if(pion[c].kolor_pionu == czarny)
		{
			pion[c].grafika = al_load_bitmap("obrazy/bohaterowie/darthvader1.png");
			al_draw_bitmap(pion[c].grafika,pion[c].pozycja_x, pion[c].pozycja_y,NULL);
			odswiezenie_grafika(pola, pion, gracz.nr_gracza, guziki);
			pion[c].dzwiek[0] = al_load_sample("dzwieki/glosy/darthvader1.ogg");
			pion[c].dzwiek[1] = al_load_sample("dzwieki/glosy/darthvader2.ogg");
			pion[c].dzwiek[2] = al_load_sample("dzwieki/glosy/darthvader3.ogg");
			pion[c].dzwiek[3] = al_load_sample("dzwieki/glosy/darthvader4.ogg");
			pion[c].dzwiek[4] = al_load_sample("dzwieki/glosy/darthvader5.ogg");
			pion[c].dzwiek[5] = al_load_sample("dzwieki/glosy/darthvader7.ogg");
			al_play_sample(pion[c].dzwiek[0],1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
			biale_damki++;
		}
		else
		{
			pion[c].grafika = al_load_bitmap("obrazy/bohaterowie/masteryoda2.png");
			al_draw_bitmap(pion[c].grafika,pion[c].pozycja_x, pion[c].pozycja_y,NULL);
			odswiezenie_grafika(pola, pion, gracz.nr_gracza, guziki);
			pion[c].dzwiek[0] = al_load_sample("dzwieki/glosy/masteryoda1.ogg");
			pion[c].dzwiek[1] = al_load_sample("dzwieki/glosy/masteryoda2.ogg");
			pion[c].dzwiek[2] = al_load_sample("dzwieki/glosy/masteryoda3.ogg");
			pion[c].dzwiek[3] = al_load_sample("dzwieki/glosy/masteryoda4.ogg");
			pion[c].dzwiek[4] = al_load_sample("dzwieki/glosy/masteryoda5.ogg");
			pion[c].dzwiek[5] = al_load_sample("dzwieki/glosy/masteryoda6.ogg");
			al_play_sample(pion[c].dzwiek[0],1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
			czarne_damki++;
		}
	}
}

// sprawdza, czy dla danego gracza mozliwe jest wykonanie bicia
bool czy_bicie (Gracz_s gracz, Pole_s **poles, Pion_s *piony)
{
	int x =0, y=0;
	bool bicie = false;
	for (int i=0; i<24; i++)
	{ 
		if ((piony[i].kolor_pionu == gracz.kolor_gracza)&&(piony[i].niezbity==true))
		{
			x = (int) piony[i].pozycja_x;
			y = (int) piony[i].pozycja_y;
			switch (piony[i].status)
			{
			case pionek:
				if(((poles[y-1][x-1].zajete == zamiana(gracz.kolor_gracza))&&(poles[y-2][x-2].zajete == brak)) ||
					((poles[y-1][x+1].zajete == zamiana(gracz.kolor_gracza))&&(poles[y-2][x+2].zajete == brak)) ||
					((poles[y+1][x-1].zajete == zamiana(gracz.kolor_gracza))&&(poles[y+2][x-2].zajete == brak)) ||
					((poles[y+1][x+1].zajete == zamiana(gracz.kolor_gracza))&&(poles[y+2][x+2].zajete == brak)))
				{
					bicie = true;
					break;
				}
				break;
			case damka:
				int xx,yy;
				xx = x;
				yy = y;
				while (poles[yy-1][xx-1].zajete ==brak)
				{

				yy--;
				xx--;
				}
				if((poles[yy-1][xx-1].zajete == zamiana(gracz.kolor_gracza))&&(poles[yy-2][xx-2].zajete == brak))
				{
					bicie = true;
					break;
				}
				xx = x;
				yy = y;
				while (poles[yy-1][xx+1].zajete ==brak)
				{

					yy--;
					xx++;
				}
				if((poles[yy-1][xx+1].zajete == zamiana(gracz.kolor_gracza))&&(poles[yy-2][xx+2].zajete == brak))
				{
					bicie = true;
					break;
				}
				xx = x;
				yy = y;
				while (poles[yy+1][xx-1].zajete ==brak)
				{

					yy++;
					xx--;
				}
				if((poles[yy+1][xx-1].zajete == zamiana(gracz.kolor_gracza))&&(poles[yy+2][xx-2].zajete == brak))
				{
					bicie = true;
					break;
				}
				xx = x;
				yy = y;
				while (poles[yy+1][xx+1].zajete ==brak)
				{
					yy++;
					xx++;
				}
				if((poles[yy+1][xx+1].zajete == zamiana(gracz.kolor_gracza))&&(poles[yy+2][xx+2].zajete == brak))
				{
					bicie = true;
					break;
				}

				break;
			default:
				break;
			}
		}
	}
	return bicie;
}

//sprawdzenie czy dla konkretnego pionu jest jeszcze bicie
bool czy_bicie_rek_pion (Gracz_s gracz, Pole_s **poles, Pion_s *piony, int c)
{
	int x =0, y=0;
	bool bicie = false;
	if ((piony[c].kolor_pionu == gracz.kolor_gracza)&&(piony[c].niezbity==true))
	{
		x = (int) piony[c].pozycja_x;
		y = (int) piony[c].pozycja_y;
		if(((poles[y-1][x-1].zajete == zamiana(gracz.kolor_gracza))&&(poles[y-2][x-2].zajete == brak)) ||
			((poles[y-1][x+1].zajete == zamiana(gracz.kolor_gracza))&&(poles[y-2][x+2].zajete == brak)) ||
			((poles[y+1][x-1].zajete == zamiana(gracz.kolor_gracza))&&(poles[y+2][x-2].zajete == brak)) ||
			((poles[y+1][x+1].zajete == zamiana(gracz.kolor_gracza))&&(poles[y+2][x+2].zajete == brak)))
		{
			bicie = true;
		}
	}
	return bicie;
}

// sprawdza, czy dla danego gracza mozliwe jest wykonanie ruchu
bool czy_ruch (Gracz_s gracz, Pole_s **poles, Pion_s *piony)
{
	int x =0, y=0;
	bool ruch = false;
	for (int i=0; i<24; i++)
	{ 
		if ((piony[i].kolor_pionu == gracz.kolor_gracza)&&(piony[i].niezbity==true))
		{
			x = (int) piony[i].pozycja_x;
			y = (int) piony[i].pozycja_y;
			if (piony[i].status == pionek)
			{
				switch (gracz.nr_gracza)
				{
				case 1:
					if((poles[y-1][x-1].zajete == brak) || (poles[y-1][x+1].zajete == brak))			
					{
						ruch = true;
						break;
					}
					break;
				case 2:
					if((poles[y+1][x-1].zajete == brak) || (poles[y+1][x+1].zajete == brak))			
					{
						ruch = true;
						break;
					}
					break;
				default:
					break;
				}
			}
			else
			{
				if((poles[y+1][x-1].zajete == brak) || (poles[y+1][x+1].zajete == brak) || (poles[y-1][x-1].zajete == brak) || (poles[y-1][x+1].zajete == brak))
				{
					ruch = true;
					break;
				}
			}
		}
	}
	return ruch;
}

// podswietlenie bicia
int podswietlenie_bicia (Gracz_s gracz, Pole_s **plansza, Pion_s *pion, int x, int y)
{
	int c=-1;
	int d=-1;
	bool powodzenie = false;
	bool doglosu = false;
	if (plansza[y][x].zajete == gracz.kolor_gracza)
	{
		
		for (int i =0; i<24;i++)
		{
			if((pion[i].pozycja_x == x)&&(pion[i].pozycja_y == y)&&(pion[i].niezbity = true)&&(pion[i].kolor_pionu==gracz.kolor_gracza))
			{
				d = i;
				powodzenie = true;
				break;
			}
		}
	}
	if (powodzenie == true)
	{
		switch (pion[d].status)
		{
		case pionek:
			if((plansza[y-1][x-1].zajete == zamiana(gracz.kolor_gracza))&&(plansza[y-2][x-2].zajete == brak))
			{
				plansza[y-2][x-2].podswietlenie = czerwony;
				al_draw_rectangle((x-2)*64,(y-2)*64, (x-2)*64 + 63, (y-2)*64+63,al_map_rgb(255,0,0), 5);
				glos(pion,d,pods_bicie);
				c=d;
			}
			if((plansza[y-1][x+1].zajete == zamiana(gracz.kolor_gracza))&&(plansza[y-2][x+2].zajete == brak))
			{
				plansza[y-2][x+2].podswietlenie = czerwony;
				al_draw_rectangle((x+2)*64,(y-2)*64, (x+2)*64 + 63, (y-2)*64+63,al_map_rgb(255,0,0), 5);
				glos(pion,d,pods_bicie);
				c=d;
			}
			if((plansza[y+1][x-1].zajete == zamiana(gracz.kolor_gracza))&&(plansza[y+2][x-2].zajete == brak))
			{
				plansza[y+2][x-2].podswietlenie = czerwony;
				al_draw_rectangle((x-2)*64,(y+2)*64, (x-2)*64 + 63, (y+2)*64+63,al_map_rgb(255,0,0), 5);
				glos(pion,d,pods_bicie);
				c=d;

			}
			if((plansza[y+1][x+1].zajete == zamiana(gracz.kolor_gracza))&&(plansza[y+2][x+2].zajete == brak))
			{
				plansza[y+2][x+2].podswietlenie = czerwony;
				al_draw_rectangle((x+2)*64,(y+2)*64, (x+2)*64 + 63, (y+2)*64+63,al_map_rgb(255,0,0), 5);
				glos(pion,d,pods_bicie);
				c=d;
			}
			break;
		case damka:
			int xx,yy;
			xx = x;
			yy = y;
			while (plansza[yy-1][xx-1].zajete ==brak)
			{

			yy--;
			xx--;
			}
			if((plansza[yy-1][xx-1].zajete == zamiana(gracz.kolor_gracza))&&(plansza[yy-2][xx-2].zajete == brak))
			{
				plansza[yy-2][xx-2].podswietlenie = czerwony;
				al_draw_rectangle((xx-2)*64,(yy-2)*64, (xx-2)*64 + 63, (yy-2)*64+63,al_map_rgb(255,0,0), 5);
				c=d;
				doglosu=true;
			}

			xx = x;
			yy = y;
			while (plansza[yy-1][xx+1].zajete ==brak)
			{

				yy--;
				xx++;
			}
			if((plansza[yy-1][xx+1].zajete == zamiana(gracz.kolor_gracza))&&(plansza[yy-2][xx+2].zajete == brak))
			{
				plansza[yy-2][xx+2].podswietlenie = czerwony;
				al_draw_rectangle((xx+2)*64,(yy-2)*64, (xx+2)*64 + 63, (yy-2)*64+63,al_map_rgb(255,0,0), 5);
				c=d;
				doglosu=true;
			}

			xx = x;
			yy = y;
			while (plansza[yy+1][xx-1].zajete ==brak)
			{

				yy++;
				xx--;
			}
			if((plansza[yy+1][xx-1].zajete == zamiana(gracz.kolor_gracza))&&(plansza[yy+2][xx-2].zajete == brak))
			{
				plansza[yy+2][xx-2].podswietlenie = czerwony;
				al_draw_rectangle((xx-2)*64,(yy+2)*64, (xx-2)*64 + 63, (yy+2)*64+63,al_map_rgb(255,0,0), 5);
				c=d;
				doglosu = true;
			}

			xx = x;
			yy = y;
			while (plansza[yy+1][xx+1].zajete ==brak)
			{
				yy++;
				xx++;
			}
			if((plansza[yy+1][xx+1].zajete == zamiana(gracz.kolor_gracza))&&(plansza[yy+2][xx+2].zajete == brak))
			{
				plansza[yy+2][xx+2].podswietlenie = czerwony;
				al_draw_rectangle((xx+2)*64,(yy+2)*64, (xx+2)*64 + 63, (yy+2)*64+63,al_map_rgb(255,0,0), 5);
				c=d;
				doglosu = true;
			}
			if (doglosu== true)
			{
				glos(pion,d,pods_bicie);
			}
			break;
		default:
			break;
		}
	}
	return c;
}


// wykonanie bicia
bool bicie (Pole_s **szachownica, Pion_s *piony, Gracz_s gracz, int x, int y, int c, int &biale_pionki, int &czarne_pionki, int &biale_damki, int &czarne_damki, ALLEGRO_BITMAP **guziki)
{
	int d;
	bool powodzenie = false;
	float a=1.0, b=64.0;
	int i = (int) piony[c].pozycja_x;
	int j = (int) piony[c].pozycja_y;
	if ((szachownica[y][x].podswietlenie == czerwony)&&(szachownica[y][x].zajete == brak))	
	{
		if ((piony[c].pozycja_x < x)&&(piony[c].pozycja_y < y)&&(piony[c].niezbity==true))
		{
			glos(piony,c,czyn_bicie);
			while (piony[c].pozycja_x < x)
			{
				piony[c].pozycja_x = piony[c].pozycja_x +  a/b;
				piony[c].pozycja_y = piony[c].pozycja_y +  a/b;
				al_rest(0.01);
				odswiezenie_grafika(szachownica, piony, gracz.nr_gracza, guziki);
			}
			piony[c].pozycja_x =x;
			piony[c].pozycja_y = y;
			czy_damka(gracz,szachownica,piony,c, biale_damki, czarne_damki, guziki);
			for (int i =0; i<24;i++)
			{
				if((piony[i].pozycja_x == x-1)&&(piony[i].pozycja_y == y-1)&&(piony[i].niezbity==true))
				{
					d = i;
					break;
				}
			}
			piony[d].pozycja_x = 10.0;
			piony[d].pozycja_y = 10.0;
			szachownica[j][i].zajete = brak;
			szachownica[y][x].zajete = gracz.kolor_gracza;
	
			piony[d].niezbity = false;
			szachownica[y-1][x-1].zajete = brak;
			odswiezenie_mechanika(szachownica);
			if(gracz.kolor_gracza == czarny)
			{
				biale_pionki--;
				if (piony[d].status==damka)
				{
					biale_damki--;
				}
			}
			else
			{
				czarne_pionki--;
				if (piony[d].status==damka)
				{
					czarne_damki--;
				}
			}
			powodzenie = true;
		}
		
		else if ((piony[c].pozycja_x < x)&&(piony[c].pozycja_y > y)&&(piony[c].niezbity==true))
		{
			glos(piony,c,czyn_bicie);
			while (piony[c].pozycja_x <  x)
			{
				piony[c].pozycja_x = piony[c].pozycja_x +  a/b;
				piony[c].pozycja_y = piony[c].pozycja_y -  a/b;
				al_rest(0.01);
				odswiezenie_grafika(szachownica, piony, gracz.nr_gracza, guziki);
			}
			piony[c].pozycja_x =x;
			piony[c].pozycja_y = y;
			czy_damka(gracz,szachownica,piony,c, biale_damki, czarne_damki, guziki);
			for (int i =0; i<24;i++)
			{
				if((piony[i].pozycja_x == x-1)&&(piony[i].pozycja_y == y+1)&&(piony[i].niezbity==true))
				{
					d = i;
					break;
				}
			}
			piony[d].pozycja_x = 10.0;
			piony[d].pozycja_y = 10.0;
			szachownica[j][i].zajete = brak;
			szachownica[y][x].zajete = gracz.kolor_gracza;	
	
			piony[d].niezbity = false;
			szachownica[y+1][x-1].zajete = brak;
			odswiezenie_mechanika(szachownica);
			if(gracz.kolor_gracza == czarny)
			{
				biale_pionki--;
				if (piony[d].status==damka)
				{
					biale_damki--;
				}
			}
			else
			{
				czarne_pionki--;
				if (piony[d].status==damka)
				{
					czarne_damki--;
				}
			}
			powodzenie = true;
		}
		else if ((piony[c].pozycja_x > x)&&(piony[c].pozycja_y < y)&&(piony[c].niezbity==true))
		{
			glos(piony,c,czyn_bicie);
			while (piony[c].pozycja_x >  x)
			{
				piony[c].pozycja_x = piony[c].pozycja_x -  a/b;
				piony[c].pozycja_y = piony[c].pozycja_y +  a/b;
				al_rest(0.01);
				odswiezenie_grafika(szachownica, piony, gracz.nr_gracza, guziki);
			}
			piony[c].pozycja_x =x;
			piony[c].pozycja_y = y;
			czy_damka(gracz,szachownica,piony,c, biale_damki, czarne_damki, guziki);
			for (int i =0; i<24;i++)
			{
				if((piony[i].pozycja_x == x+1)&&(piony[i].pozycja_y == y-1)&&(piony[i].niezbity==true))
				{
					d = i;
					break;
				}
			}
			piony[d].pozycja_x = 10.0;
			piony[d].pozycja_y = 10.0;
			szachownica[j][i].zajete = brak;
			szachownica[y][x].zajete = gracz.kolor_gracza;
			
			piony[d].niezbity = false;
			szachownica[y-1][x+1].zajete = brak;
			odswiezenie_mechanika(szachownica);
			if(gracz.kolor_gracza == czarny)
			{
				biale_pionki--;
				if (piony[d].status==damka)
				{
					biale_damki--;
				}
			}
			else
			{
				czarne_pionki--;
				if (piony[d].status==damka)
				{
					czarne_damki--;
				}
			}
			powodzenie = true;
		}
		else if ((piony[c].pozycja_x > x)&&(piony[c].pozycja_y > y)&&(piony[c].niezbity==true))
		{
			glos(piony,c,czyn_bicie);
			while (piony[c].pozycja_x >  x)
			{
				piony[c].pozycja_x = piony[c].pozycja_x -  a/b;
				piony[c].pozycja_y = piony[c].pozycja_y -  a/b;
				al_rest(0.01);
				odswiezenie_grafika(szachownica, piony, gracz.nr_gracza,guziki);
			}
			piony[c].pozycja_x =x;
			piony[c].pozycja_y = y;
			czy_damka(gracz,szachownica,piony,c, biale_damki, czarne_damki, guziki);
			for (int i =0; i<24;i++)
			{
				if((piony[i].pozycja_x == x+1)&&(piony[i].pozycja_y == y+1)&&(piony[i].niezbity==true))
				{
					d = i;
					break;
				}
			}
			piony[d].pozycja_x = 10.0;
			piony[d].pozycja_y = 10.0;
			szachownica[j][i].zajete = brak;
			szachownica[y][x].zajete = gracz.kolor_gracza;
			piony[d].niezbity = false;
			szachownica[y+1][x+1].zajete = brak;
			odswiezenie_mechanika(szachownica);
			if(gracz.kolor_gracza == czarny)
			{
				biale_pionki--;
				if (piony[d].status==damka)
				{
					biale_damki--;
				}
			}
			else
			{
				czarne_pionki--;
				if (piony[d].status==damka)
				{
					czarne_damki--;
				}
			}
			powodzenie = true;
		}
		odswiezenie_mechanika(szachownica);

	}
	odswiezenie_grafika(szachownica, piony, gracz.nr_gracza, guziki);
	return powodzenie;
}



// podswietlenie mozliwych ruchow do wykonania
int podswietlenie_ruchow (Gracz_s gracz, Pole_s **plansza, Pion_s *pion, int x, int y)
{
	int c=-1,xx,yy;
	bool powodzenie = false;
	bool doglosu =false;
	if (plansza[y][x].zajete == gracz.kolor_gracza)
	{
		
		for (int i =0; i<24;i++)
		{
			if((pion[i].pozycja_x == x)&&(pion[i].pozycja_y == y)&&(pion[i].niezbity==true)&&(pion[i].kolor_pionu==gracz.kolor_gracza))
			{
				c = i;
				powodzenie = true;
				break;
			}
		}
	}
	if (powodzenie == true)

		
		
	{
		switch (pion[c].status)
		{
		case pionek:
			switch (gracz.nr_gracza)
			{
			case 1:
				if(plansza[y-1][x-1].zajete == brak)
				{
					glos(pion,c,pods_ruch);
					plansza[y-1][x-1].podswietlenie = zielony;
					al_draw_rectangle((x-1)*64,(y-1)*64, (x-1)*64 + 63, (y-1)*64+63,al_map_rgb(0,255,0), 5);
					
				}
				if(plansza[y-1][x+1].zajete == brak)
				{
					glos(pion,c,pods_ruch);
					plansza[y-1][x+1].podswietlenie = zielony;
					al_draw_rectangle((x+1)*64,(y-1)*64, (x+1)*64 + 63, (y-1)*64+63,al_map_rgb(0,255,0), 5);
					
				}
				break;
			case 2:
				if(plansza[y+1][x-1].zajete == brak)
				{
					glos(pion,c,pods_ruch);
					plansza[y+1][x-1].podswietlenie = zielony;
					al_draw_rectangle((x-1)*64,(y+1)*64, (x-1)*64 + 63, (y+1)*64+63,al_map_rgb(0,255,0), 5);
					
				}
				if(plansza[y+1][x+1].zajete == brak)
				{
					glos(pion,c,pods_ruch);
					plansza[y+1][x+1].podswietlenie = zielony;
					al_draw_rectangle((x+1)*64,(y+1)*64, (x+1)*64 + 63, (y+1)*64+63,al_map_rgb(0,255,0), 5);
					
				}
				break;
			default:
				;
				break;
			}
			break;
		case damka:
			
			xx = x;
			yy = y;
			while (plansza[yy-1][xx-1].zajete ==brak)
			{
				
				plansza[yy-1][xx-1].podswietlenie = zielony;
				al_draw_rectangle((xx-1)*64,(yy-1)*64, (xx-1)*64 + 63, (yy-1)*64+63,al_map_rgb(0,255,0), 5);
				yy--;
				xx--;
				doglosu = true;
			}
			xx = x;
			yy = y;
			while (plansza[yy-1][xx+1].zajete ==brak)
			{
				
				plansza[yy-1][xx+1].podswietlenie = zielony;
				al_draw_rectangle((xx+1)*64,(yy-1)*64, (xx+1)*64 + 63, (yy-1)*64+63,al_map_rgb(0,255,0), 5);
				yy--;
				xx++;
				doglosu = true;
			}
			xx = x;
			yy = y;
			while (plansza[yy+1][xx-1].zajete ==brak)
			{
				
				plansza[yy+1][xx-1].podswietlenie = zielony;
				al_draw_rectangle((xx-1)*64,(yy+1)*64, (xx-1)*64 + 63, (yy+1)*64+63,al_map_rgb(0,255,0), 5);
				yy++;
				xx--;
				doglosu=true;
			}
			
			xx = x;
			yy = y;
			while (plansza[yy+1][xx+1].zajete ==brak)
			{
				
				plansza[yy+1][xx+1].podswietlenie = zielony;
				al_draw_rectangle((xx+1)*64,(yy+1)*64, (xx+1)*64 + 63, (yy+1)*64+63,al_map_rgb(0,255,0), 5);
				yy++;
				xx++;
				doglosu=true;
			}
			if (doglosu ==true)
			{
				glos(pion,c,pods_ruch);
			}
			
			break;
		default:
			break;
		}
	}
	
	return c;
}

// wykonanie ruchu
bool ruch(Pole_s **szachownica, Pion_s *piony, Gracz_s gracz, int x, int y, int c, int &biale_damki, int &czarne_damki, ALLEGRO_BITMAP **guziki)
{
	bool powodzenie = false;
	float a=1.0, b=64.0;
	int i = (int) piony[c].pozycja_x;
	int j = (int) piony[c].pozycja_y;
	if (szachownica[y][x].podswietlenie == zielony)	
	{
		switch (piony[c].status)
		{
		case pionek:
			if (gracz.nr_gracza == 1)
			{	
				if ((piony[c].pozycja_x < x)&&(piony[c].niezbity==true))
				{
					glos(piony,c,czyn_ruch);
					while (piony[c].pozycja_x <  x)
					{
						piony[c].pozycja_x = piony[c].pozycja_x +  a/b;
						piony[c].pozycja_y = piony[c].pozycja_y -  a/b;
						al_rest(0.01);
						odswiezenie_grafika(szachownica, piony, gracz.nr_gracza, guziki);
					}
					piony[c].pozycja_x =x;
					piony[c].pozycja_y = y;
					czy_damka(gracz,szachownica,piony,c, biale_damki, czarne_damki, guziki);
					szachownica[j][i].zajete = brak;
					szachownica[y][x].zajete = gracz.kolor_gracza;
					odswiezenie_mechanika(szachownica);
					powodzenie = true;
				}
				else if ((piony[c].pozycja_x > x)&&(piony[c].niezbity==true))
				{
					glos(piony,c,czyn_ruch);
					while (piony[c].pozycja_x >  x)
					{
						piony[c].pozycja_x = piony[c].pozycja_x -  a/b;
						piony[c].pozycja_y = piony[c].pozycja_y -  a/b;
						al_rest(0.01);
						odswiezenie_grafika(szachownica, piony, gracz.nr_gracza, guziki);

					}
					piony[c].pozycja_x =x;
					piony[c].pozycja_y = y;
					czy_damka(gracz,szachownica,piony,c, biale_damki, czarne_damki, guziki);
					szachownica[j][i].zajete = brak;
					szachownica[y][x].zajete = gracz.kolor_gracza;
					odswiezenie_mechanika(szachownica);
					powodzenie = true;
				}

			}
			else 
			{
				if ((piony[c].pozycja_x < x)&&(piony[c].niezbity==true))
				{
					glos(piony,c,czyn_ruch);
					while (piony[c].pozycja_x <  x)
					{
						piony[c].pozycja_x = piony[c].pozycja_x +  a/b;
						piony[c].pozycja_y = piony[c].pozycja_y +  a/b;
						al_rest(0.01);
						odswiezenie_grafika(szachownica, piony, gracz.nr_gracza, guziki);
					}
					piony[c].pozycja_x =x;
					piony[c].pozycja_y = y;
					czy_damka(gracz,szachownica,piony,c, biale_damki, czarne_damki, guziki);
					szachownica[j][i].zajete = brak;
					szachownica[y][x].zajete = gracz.kolor_gracza;	
					odswiezenie_mechanika(szachownica);
					powodzenie = true;
				}
				else if ((piony[c].pozycja_x > x)&&(piony[c].niezbity==true))
				{
					glos(piony,c,czyn_ruch);
					while (piony[c].pozycja_x >  x)
					{
						piony[c].pozycja_x = piony[c].pozycja_x -  a/b;
						piony[c].pozycja_y = piony[c].pozycja_y +  a/b;
						al_rest(0.01);
						odswiezenie_grafika(szachownica, piony, gracz.nr_gracza, guziki);
					}
					piony[c].pozycja_x =x;
					piony[c].pozycja_y = y;
					czy_damka(gracz,szachownica,piony,c, biale_damki, czarne_damki, guziki);
					szachownica[j][i].zajete = brak;
					szachownica[y][x].zajete = gracz.kolor_gracza;	
					odswiezenie_mechanika(szachownica);
					powodzenie = true;
				}
			}
			break;
		case damka:
			if ((piony[c].pozycja_x < x)&&(piony[c].pozycja_y > y)&&(piony[c].niezbity==true))
			{
				glos(piony,c,czyn_ruch);
				while (piony[c].pozycja_x <  x)
				{
					piony[c].pozycja_x = piony[c].pozycja_x +  a/b;
					piony[c].pozycja_y = piony[c].pozycja_y -  a/b;
					al_rest(0.01);
					odswiezenie_grafika(szachownica, piony, gracz.nr_gracza, guziki);
				}
				piony[c].pozycja_x =x;
				piony[c].pozycja_y = y;
				czy_damka(gracz,szachownica,piony,c, biale_damki, czarne_damki, guziki);
				szachownica[j][i].zajete = brak;
				szachownica[y][x].zajete = gracz.kolor_gracza;
				odswiezenie_mechanika(szachownica);
				powodzenie = true;
			}
			else if ((piony[c].pozycja_x > x)&&(piony[c].pozycja_y > y)&&(piony[c].niezbity==true))
			{
				glos(piony,c,czyn_ruch);
				while (piony[c].pozycja_x >  x)
				{
					piony[c].pozycja_x = piony[c].pozycja_x -  a/b;
					piony[c].pozycja_y = piony[c].pozycja_y -  a/b;
					al_rest(0.01);
					odswiezenie_grafika(szachownica, piony, gracz.nr_gracza, guziki);
				}
				piony[c].pozycja_x =x;
				piony[c].pozycja_y = y;
				czy_damka(gracz,szachownica,piony,c, biale_damki, czarne_damki, guziki);
				szachownica[j][i].zajete = brak;
				szachownica[y][x].zajete = gracz.kolor_gracza;
				odswiezenie_mechanika(szachownica);
				powodzenie = true;
				}
			else if ((piony[c].pozycja_x < x)&&(piony[c].pozycja_y < y)&&(piony[c].niezbity==true))
			{
				glos(piony,c,czyn_ruch);
				while (piony[c].pozycja_x <  x)
				{
					piony[c].pozycja_x = piony[c].pozycja_x +  a/b;
					piony[c].pozycja_y = piony[c].pozycja_y +  a/b;
					al_rest(0.01);
					odswiezenie_grafika(szachownica, piony, gracz.nr_gracza, guziki);
				}
				piony[c].pozycja_x =x;
				piony[c].pozycja_y = y;
				czy_damka(gracz,szachownica,piony,c, biale_damki, czarne_damki, guziki);
				szachownica[j][i].zajete = brak;
				szachownica[y][x].zajete = gracz.kolor_gracza;	
				odswiezenie_mechanika(szachownica);
				powodzenie = true;
			}
			else if ((piony[c].pozycja_x > x)&&(piony[c].pozycja_y < y)&&(piony[c].niezbity==true))
			{
				glos(piony,c,czyn_ruch);
				while (piony[c].pozycja_x >  x)
				{
					piony[c].pozycja_x = piony[c].pozycja_x -  a/b;
					piony[c].pozycja_y = piony[c].pozycja_y +  a/b;
					al_rest(0.01);
					odswiezenie_grafika(szachownica, piony, gracz.nr_gracza, guziki);
				}
				piony[c].pozycja_x =x;
				piony[c].pozycja_y = y;
				czy_damka(gracz,szachownica,piony,c, biale_damki, czarne_damki, guziki);
				szachownica[j][i].zajete = brak;
				szachownica[y][x].zajete = gracz.kolor_gracza;	
				odswiezenie_mechanika(szachownica);
				powodzenie = true;
			}
			break;
		default:
			break;
		}	
	}
	//odswiezenie_grafika(figura);
	return powodzenie;
}




// tura gracza
bool tura (Gracz_s gracz, Gracz_s gracz2, Pole_s **szachownica, Pion_s *pion, ALLEGRO_EVENT_QUEUE *&kolejka, int &biale_pionki, int &czarne_pionki, int &biale_damki, int &czarne_damki, int &sterujaca, ALLEGRO_BITMAP **guziki)
{
	bool w1=false,w2=false; 
	bool cb = false;
	bool wyjscie;
	int x,y,c=-1;
		while(w1 == false)
		{
			cb = czy_bicie(gracz,szachownica,pion);
			if (cb==true)
			{
				bicie:
				ALLEGRO_EVENT klik;
				al_wait_for_event(kolejka, &klik);		
				if (klik.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
				
				{
					if ((klik.mouse.button & 1) && (klik.mouse.x >= 686) && (klik.mouse.x <= 750) && (klik.mouse.y >= 300) && (klik.mouse.y <= 364))
					{
						if (al_get_mixer_playing(al_get_default_mixer()))
						{
							guziki[2]=al_load_bitmap("obrazy/slajdy/sound_off.png");
							odswiezenie_grafika(szachownica,pion,gracz.nr_gracza,guziki);
							al_set_mixer_playing(al_get_default_mixer(), false);
						}
						else
						{
							guziki[2]=al_load_bitmap("obrazy/slajdy/sound_on.png");
							odswiezenie_grafika(szachownica,pion,gracz.nr_gracza,guziki);
							al_set_mixer_playing(al_get_default_mixer(), true);
						}
						continue;
					}
					if ((klik.mouse.button & 1) && (klik.mouse.x >= 618) && (klik.mouse.x <= 818) && (klik.mouse.y >= 437) && (klik.mouse.y <= 506))
					{
						guziki[3]=al_load_bitmap("obrazy/slajdy/save2.png");
						odswiezenie_grafika(szachownica,pion,gracz.nr_gracza,guziki);
						// tutaj beda instrukcje zapisywania stanu gry
						guziki[3]=al_load_bitmap("obrazy/slajdy/save1.png");
						if (sterujaca == 1)
						{
							sterujaca = 6;
							wyjscie = true;
							return true;
						}
						else if (sterujaca == 2)
						{
							sterujaca = 7;
							wyjscie = true;
							return true;
						}
					}
					if ((klik.mouse.button & 1) && (klik.mouse.x >= 618) && (klik.mouse.x <= 818) && (klik.mouse.y >= 537) && (klik.mouse.y <= 606))
					{
						guziki[4]=al_load_bitmap("obrazy/slajdy/return2.png");
						odswiezenie_grafika(szachownica,pion,gracz.nr_gracza,guziki);
						guziki[4]=al_load_bitmap("obrazy/slajdy/return1.png");
						sterujaca = 0;
						return true;
					}
					if (klik.mouse.button & 1)
					{

						odswiezenie_mechanika(szachownica);
						odswiezenie_grafika(szachownica, pion, gracz.nr_gracza, guziki);
						x = (klik.mouse.x)/64;
						y = (klik.mouse.y)/64;

						c = podswietlenie_bicia(gracz, szachownica, pion, x, y);
						al_flip_display();
					}
					else if ((klik.mouse.button & 2)&&(c>=0))
					{
						x = (klik.mouse.x)/64;
						y = (klik.mouse.y)/64;
						w1 =  bicie (szachownica,pion,gracz,x,y,c, biale_pionki, czarne_pionki, biale_damki, czarne_damki, guziki);
						if (czy_bicie_rek_pion(gracz,szachownica,pion,c) == true)
						{
							//x = figura[c].pozycja_x;
							//y=figura[c].pozycja_y;
							w1 = false;
							continue;
							
						}
						w2=false ;
						c=-1;
					}
				}
				else if (klik.type == ALLEGRO_EVENT_KEY_DOWN)
				{
					if (klik.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
					{
						sterujaca = -1;
						wyjscie = true;
						return true;
						//goto petla_glowna;
					}
				}
				else if (klik.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
				{
					sterujaca = -1;
					wyjscie = true;
					return true;
				}
			}
			else
			{
				if(czy_ruch(gracz,szachownica,pion)==false)
				{
					if (gracz.kolor_gracza == bialy)
					{
						biale_pionki = 0;
					}
					else
					{
						czarne_pionki = 0;
					}
					break;
				}
				ALLEGRO_EVENT klik;
				al_wait_for_event(kolejka, &klik);		
				if (klik.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
				{
					wyjscie = false;					
					if ((klik.mouse.button & 1) && (klik.mouse.x >= 686) && (klik.mouse.x <= 750) && (klik.mouse.y >= 300) && (klik.mouse.y <= 364))
					{
						if (al_get_mixer_playing(al_get_default_mixer()))
						{
							guziki[2]=al_load_bitmap("obrazy/slajdy/sound_off.png");
							odswiezenie_grafika(szachownica,pion,gracz.nr_gracza,guziki);
							al_set_mixer_playing(al_get_default_mixer(), false);
						}
						else
						{
							guziki[2]=al_load_bitmap("obrazy/slajdy/sound_on.png");
							odswiezenie_grafika(szachownica,pion,gracz.nr_gracza,guziki);
							al_set_mixer_playing(al_get_default_mixer(), true);
						}
						continue;
					}
					if ((klik.mouse.button & 1) && (klik.mouse.x >= 618) && (klik.mouse.x <= 818) && (klik.mouse.y >= 437) && (klik.mouse.y <= 506))
					{
						guziki[3]=al_load_bitmap("obrazy/slajdy/save2.png");
						odswiezenie_grafika(szachownica,pion,gracz.nr_gracza,guziki);
						// tutaj beda instrukcje zapisywania stanu gry
						guziki[3]=al_load_bitmap("obrazy/slajdy/save1.png");
						if (sterujaca == 1)
						{
							sterujaca = 6;
							wyjscie = true;
							return true;
						}
						else if (sterujaca == 2)
						{
							sterujaca = 7;
							wyjscie = true;
							return true;
						}
					}
					if ((klik.mouse.button & 1) && (klik.mouse.x >= 618) && (klik.mouse.x <= 818) && (klik.mouse.y >= 537) && (klik.mouse.y <= 606))
					{
						guziki[4]=al_load_bitmap("obrazy/slajdy/return2.png");
						odswiezenie_grafika(szachownica,pion,gracz.nr_gracza,guziki);
						guziki[4]=al_load_bitmap("obrazy/slajdy/return1.png");
						sterujaca = 0;
						return true;
					}
					if (klik.mouse.button & 1)
					{
						odswiezenie_mechanika(szachownica);
						odswiezenie_grafika(szachownica, pion, gracz.nr_gracza, guziki);
						x = (klik.mouse.x)/64;
						y = (klik.mouse.y)/64;
						c = podswietlenie_ruchow(gracz, szachownica, pion, x, y);
						al_flip_display();
					}
					else if ((klik.mouse.button & 2)&&(c>=0))
					{
						x = (klik.mouse.x)/64;
						y = (klik.mouse.y)/64;
						w1 = ruch (szachownica,pion,gracz,x,y,c, biale_damki, czarne_damki, guziki);
						w2 =false;
						c=-1;
					}
				}
				else if (klik.type == ALLEGRO_EVENT_KEY_DOWN)
				{
					if (klik.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
					{
						sterujaca = -1;
						wyjscie = true;
						return true;
						//goto petla_glowna;
					}
				}
				else if (klik.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
				{
					sterujaca = -1;
					wyjscie = true;
					return true;
				}
			}
		}
		cb = false;
		c=-1;
		return wyjscie;

}

// warunek zakonczenia rozgrywki
bool czy_koniec (int biale, int czarne, int biale_damki, int czarne_damki, ALLEGRO_DISPLAY *&okienko,bool wwyjscie)
{
	bool koniec= wwyjscie;
	if (biale <= 0)
	{
		koniec = true;
		al_show_native_message_box( okienko,"Koniec","Gra zostala zakoczona","Zwyciestwo odniosla druzyna Czarnych",NULL, ALLEGRO_MESSAGEBOX_YES_NO);
	}
	else if (czarne <= 0)
	{
		koniec = true;
		al_show_native_message_box( okienko,"Koniec","Gra zostala zakonczona","Zwyciestwo odniosla druzyna Bialych",NULL, ALLEGRO_MESSAGEBOX_YES_NO);
	}
	else if ((biale == 1) && (czarne==1) &&(biale_damki==1)&&(czarne_damki==1))
	{
		koniec = true;
		al_show_native_message_box( okienko,"Koniec","Gra zostala zakonczona","Remis",NULL, ALLEGRO_MESSAGEBOX_YES_NO);

	}
	return koniec;

}



struct ai_Pion_s
{
	kolor kolor_pionu;
	status status;
	bool niezbity;
	float pozycja_x;
	float pozycja_y;
};

// struktura pionu
struct ai_Pole_s
{
	kolor kolor_pola;
	kolor zajete;
	int pozycja_x;
	int pozycja_y;
};


// sprawdzenie - preksztalcenie w damke
void ai_czy_damka (Gracz_s gracz, ai_Pole_s **pola, ai_Pion_s *pion, int c)
{
	if ((gracz.nr_gracza == 1) && (pion[c].pozycja_y == 1)&&(pion[c].status != damka))
	{
		pion[c].status = damka;
		if(pion[c].kolor_pionu == czarny)
		{
			//liczba_czarnych_damek++;
		}
		else
		{

			//liczba_bialych_damek++;
		}
	}
	if ((gracz.nr_gracza == 2) && (pion[c].pozycja_y == 8)&&(pion[c].status != damka))
	{
		pion[c].status = damka;
		if(pion[c].kolor_pionu == czarny)
		{
	
			//liczba_czarnych_damek++;
		}
		else
		{

			//liczba_bialych_damek++;
		}
	}
}

//stack <int> stos;

//sprawdzenie
bool ai_czy_bicie_rek_pion (Gracz_s gracz, ai_Pole_s **poles, ai_Pion_s *piony, int c)
{
	int x =0, y=0;
	bool bicie = false;
	if ((piony[c].kolor_pionu == gracz.kolor_gracza)&&(piony[c].niezbity==true))
	{
		x = (int) piony[c].pozycja_x;
		y = (int) piony[c].pozycja_y;
		if(((poles[y-1][x-1].zajete == zamiana(gracz.kolor_gracza))&&(poles[y-2][x-2].zajete == brak)) ||
			((poles[y-1][x+1].zajete == zamiana(gracz.kolor_gracza))&&(poles[y-2][x+2].zajete == brak)) ||
			((poles[y+1][x-1].zajete == zamiana(gracz.kolor_gracza))&&(poles[y+2][x-2].zajete == brak)) ||
			((poles[y+1][x+1].zajete == zamiana(gracz.kolor_gracza))&&(poles[y+2][x+2].zajete == brak)))
		{
			bicie = true;
		}
	}
	return bicie;
}

// dla komputera sprawdza, czy dla danego gracza mozliwe jest wykonanie bicia
bool ai_czy_bicie (ai_Pole_s **poles, ai_Pion_s *piony, Gracz_s gracz, stack <int> &stos)
{
	int x =0, y=0;
	bool cbicie = false;
	for (int i=0; i<24; i++)
	{ 
		if ((piony[i].kolor_pionu == gracz.kolor_gracza)&&(piony[i].niezbity==true))
		{
			x = (int) piony[i].pozycja_x;
			y = (int) piony[i].pozycja_y;
			switch (piony[i].status)
			{
			case pionek:
				if((poles[y-1][x-1].zajete == zamiana(gracz.kolor_gracza))&&(poles[y-2][x-2].zajete == brak))
				{
					cbicie = true;
					stos.push(i);
					stos.push(y-2);
					stos.push(x-2);
					//break;
				}
				if((poles[y-1][x+1].zajete == zamiana(gracz.kolor_gracza))&&(poles[y-2][x+2].zajete == brak))
				{
					cbicie = true;
					stos.push(i);
					stos.push(y-2);
					stos.push(x+2);
					//break;
				}
				if((poles[y+1][x-1].zajete == zamiana(gracz.kolor_gracza))&&(poles[y+2][x-2].zajete == brak))
				{
					cbicie = true;
					stos.push(i);
					stos.push(y+2);
					stos.push(x-2);
					//break;
				}
				if((poles[y+1][x+1].zajete == zamiana(gracz.kolor_gracza))&&(poles[y+2][x+2].zajete == brak))
				{
					cbicie = true;
					stos.push(i);
					stos.push(y+2);
					stos.push(x+2);
					//break;
				}
				break;
			case damka:
				int xx,yy;
				xx = x;
				yy = y;
				while (poles[yy-1][xx-1].zajete ==brak)
				{

				yy--;
				xx--;
				}
				if((poles[yy-1][xx-1].zajete == zamiana(gracz.kolor_gracza))&&(poles[yy-2][xx-2].zajete == brak))
				{
					cbicie = true;
					stos.push(i);
					stos.push(yy-2);
					stos.push(xx-2);
					//break;
				}
				xx = x;
				yy = y;
				while (poles[yy-1][xx+1].zajete ==brak)
				{

					yy--;
					xx++;
				}
				if((poles[yy-1][xx+1].zajete == zamiana(gracz.kolor_gracza))&&(poles[yy-2][xx+2].zajete == brak))
				{
					cbicie = true;
					stos.push(i);
					stos.push(yy-2);
					stos.push(xx+2);
					//break;
				}
				xx = x;
				yy = y;
				while (poles[yy+1][xx-1].zajete ==brak)
				{

					yy++;
					xx--;
				}
				if((poles[yy+1][xx-1].zajete == zamiana(gracz.kolor_gracza))&&(poles[yy+2][xx-2].zajete == brak))
				{
					cbicie = true;
					stos.push(i);
					stos.push(yy+2);
					stos.push(xx-2);
					//break;
				}
				xx = x;
				yy = y;
				while (poles[yy+1][xx+1].zajete ==brak)
				{
					yy++;
					xx++;
				}
				if((poles[yy+1][xx+1].zajete == zamiana(gracz.kolor_gracza))&&(poles[yy+2][xx+2].zajete == brak))
				{
					cbicie = true;
					stos.push(i);
					stos.push(y+2);
					stos.push(x+2);
					//break;
				}

				break;
			default:
				break;
			}
		}
	}
	return cbicie;
}

//rekursujne bicia


// bicie komputerowe
bool ai_bicie (ai_Pole_s **szachownica, ai_Pion_s *piony, Gracz_s gracz, int x, int y, int c )
{
	int d;
	bool powodzenie = false;
	float a=1.0, b=64.0;
	int i = (int) piony[c].pozycja_x;
	int j = (int) piony[c].pozycja_y;
	if (szachownica[y][x].zajete == brak)
	{
		if ((piony[c].pozycja_x < x)&&(piony[c].pozycja_y < y)&&(piony[c].niezbity==true))
		{
			piony[c].pozycja_x =x;
			piony[c].pozycja_y = y;
			ai_czy_damka(gracz,szachownica,piony,c);
			for (int i =0; i<24;i++)
			{
				if((piony[i].pozycja_x == x-1)&&(piony[i].pozycja_y == y-1)&&(piony[i].niezbity==true))
				{
					d = i;
					break;
				}
			}
			piony[d].pozycja_x = 10.0;
			piony[d].pozycja_y = 10.0;
			szachownica[j][i].zajete = brak;
			szachownica[y][x].zajete = gracz.kolor_gracza;
			piony[d].niezbity = false;
			szachownica[y-1][x-1].zajete = brak;
			//odswiezenie_mechanika(szachownica);
			if(gracz.kolor_gracza == czarny)
			{
				//liczba_bialych--;
				if (piony[d].status==damka)
				{
					//liczba_bialych_damek--;
				}
			}
			else
			{
				//liczba_czarnych--;
				if (piony[d].status==damka)
				{
					//liczba_czarnych_damek--;
				}
			}
			powodzenie = true;
		}
		
		else if ((piony[c].pozycja_x < x)&&(piony[c].pozycja_y > y)&&(piony[c].niezbity==true))
		{
			piony[c].pozycja_x =x;
			piony[c].pozycja_y = y;
			ai_czy_damka(gracz,szachownica,piony,c);
			for (int i =0; i<24;i++)
			{
				if((piony[i].pozycja_x == x-1)&&(piony[i].pozycja_y == y+1)&&(piony[i].niezbity==true))
				{
					d = i;
					break;
				}
			}
			piony[d].pozycja_x = 10.0;
			piony[d].pozycja_y = 10.0;
			szachownica[j][i].zajete = brak;
			szachownica[y][x].zajete = gracz.kolor_gracza;	
	
			piony[d].niezbity = false;
			szachownica[y+1][x-1].zajete = brak;
			//odswiezenie_mechanika(szachownica);
			if(gracz.kolor_gracza == czarny)
			{
				//liczba_bialych--;
				if (piony[d].status==damka)
				{
					//liczba_bialych_damek--;
				}
			}
			else
			{
				//liczba_czarnych--;
				if (piony[d].status==damka)
				{
					//liczba_czarnych_damek--;
				}
			}
			powodzenie = true;
		}
		else if ((piony[c].pozycja_x > x)&&(piony[c].pozycja_y < y)&&(piony[c].niezbity==true))
		{
			piony[c].pozycja_x =x;
			piony[c].pozycja_y = y;
			ai_czy_damka(gracz,szachownica,piony,c);
			for (int i =0; i<24;i++)
			{
				if((piony[i].pozycja_x == x+1)&&(piony[i].pozycja_y == y-1)&&(piony[i].niezbity==true))
				{
					d = i;
					break;
				}
			}
			piony[d].pozycja_x = 10.0;
			piony[d].pozycja_y = 10.0;
			szachownica[j][i].zajete = brak;
			szachownica[y][x].zajete = gracz.kolor_gracza;
			
			piony[d].niezbity = false;
			szachownica[y-1][x+1].zajete = brak;
			//odswiezenie_mechanika(szachownica);
			if(gracz.kolor_gracza == czarny)
			{
				//liczba_bialych--;
				if (piony[d].status==damka)
				{
					//liczba_bialych_damek--;
				}
			}
			else
			{
				//liczba_czarnych--;
				if (piony[d].status==damka)
				{
					//liczba_czarnych_damek--;
				}
			}
			powodzenie = true;
		}
		else if ((piony[c].pozycja_x > x)&&(piony[c].pozycja_y > y)&&(piony[c].niezbity==true))
		{
			piony[c].pozycja_x =x;
			piony[c].pozycja_y = y;
			ai_czy_damka(gracz,szachownica,piony,c);
			for (int i =0; i<24;i++)
			{
				if((piony[i].pozycja_x == x+1)&&(piony[i].pozycja_y == y+1)&&(piony[i].niezbity==true))
				{
					d = i;
					break;
				}
			}
			piony[d].pozycja_x = 10.0;
			piony[d].pozycja_y = 10.0;
			szachownica[j][i].zajete = brak;
			szachownica[y][x].zajete = gracz.kolor_gracza;
			piony[d].niezbity = false;
			szachownica[y+1][x+1].zajete = brak;
			//odswiezenie_mechanika(szachownica);
			if(gracz.kolor_gracza == czarny)
			{
				//liczba_bialych--;
				if (piony[d].status==damka)
				{
					//liczba_bialych_damek--;
				}
			}
			else
			{
				//liczba_czarnych--;
				if (piony[d].status==damka)
				{
					//liczba_czarnych_damek--;
				}
			}
			powodzenie = true;
		}
		//odswiezenie_mechanika(szachownica);

	}
	//odswiezenie_grafika(figura, gracz.nr_gracza);
	return powodzenie;
}


// dla komputera sprawdza, czy dla danego gracza mozliwe jest wykonanie ruchu
bool ai_czy_ruch (ai_Pole_s **poles, ai_Pion_s *piony, Gracz_s gracz, stack <int> &stos)
{
	int x =0, y=0,xx,yy;
	bool ruch = false;
	for (int i=0; i<24; i++)
	{ 
		if ((piony[i].kolor_pionu == gracz.kolor_gracza)&&(piony[i].niezbity==true))
		{
			x = (int) piony[i].pozycja_x;
			y = (int) piony[i].pozycja_y;
			if (piony[i].status == pionek)
			{
				switch (gracz.nr_gracza)
				{
				case 1:
					if(poles[y-1][x-1].zajete == brak) 	
					{
						ruch = true;
						stos.push(i);
						stos.push(y-1);
						stos.push(x-1);
						//break;
					}
					if(poles[y-1][x+1].zajete == brak)
					{
						ruch = true;
						stos.push(i);
						stos.push(y-1);
						stos.push(x+1);
						//break;
					}
					break;
				case 2:
					if(poles[y+1][x-1].zajete == brak)		
					{
						ruch = true;
						stos.push(i);
						stos.push(y+1);
						stos.push(x-1);
						//break;
					}
					if(poles[y+1][x+1].zajete == brak)
					{
						ruch = true;
						stos.push(i);
						stos.push(y+1);
						stos.push(x+1);
						//break;

					}
					break;
				default:
					break;
				}
			}
			else
			{
				xx=x;
				yy=y;
				while(poles[yy+1][xx-1].zajete == brak)
				{
					ruch = true;
					stos.push(i);
					stos.push(yy+1);
					stos.push(xx-1);
					yy++;
					xx--;

				}
				xx=x;
				yy=y;
				while(poles[yy+1][xx+1].zajete == brak)
				{
					ruch = true;
					stos.push(i);
					stos.push(yy+1);
					stos.push(xx+1);
					yy++;
					xx++;
					
				}
				xx=x;
				yy=y;

				while(poles[yy-1][xx-1].zajete == brak)
				{
					ruch = true;
					stos.push(i);
					stos.push(yy-1);
					stos.push(xx-1);
					yy--;
					xx--;
					
				}
				xx=x;
				yy=y;
				while(poles[yy-1][xx+1].zajete == brak)
				{
					ruch = true;
					stos.push(i);
					stos.push(yy-1);
					stos.push(xx+1);
					yy--;
					xx++;
					
				}
			}
		}
	}
	return ruch;
}

// komputerowe wykonanie ruchu
bool ai_ruch(ai_Pole_s **szachownica, ai_Pion_s *piony, Gracz_s gracz, int x, int y, int c )
{
	bool powodzenie = false;
	float a=1.0, b=64.0;
	int i = (int) piony[c].pozycja_x;
	int j = (int) piony[c].pozycja_y;
	if (powodzenie == false)	
	{
		switch (piony[c].status)
		{
		case pionek:
			if (gracz.nr_gracza == 1)
			{	
				if ((piony[c].pozycja_x < x)&&(piony[c].niezbity==true))
				{

					piony[c].pozycja_x =x;
					piony[c].pozycja_y = y;
					ai_czy_damka(gracz,szachownica,piony,c);
					szachownica[j][i].zajete = brak;
					szachownica[y][x].zajete = gracz.kolor_gracza;
					//odswiezenie_mechanika(szachownica);
					powodzenie = true;
				}
				else if ((piony[c].pozycja_x > x)&&(piony[c].niezbity==true))
				{

					piony[c].pozycja_x =x;
					piony[c].pozycja_y = y;
					ai_czy_damka(gracz,szachownica,piony,c);
					szachownica[j][i].zajete = brak;
					szachownica[y][x].zajete = gracz.kolor_gracza;
					//odswiezenie_mechanika(szachownica);
					powodzenie = true;
				}

			}
			else 
			{
				if ((piony[c].pozycja_x < x)&&(piony[c].niezbity==true))
				{

					piony[c].pozycja_x =x;
					piony[c].pozycja_y = y;
					ai_czy_damka(gracz,szachownica,piony,c);
					szachownica[j][i].zajete = brak;
					szachownica[y][x].zajete = gracz.kolor_gracza;	
					//odswiezenie_mechanika(szachownica);
					powodzenie = true;
				}
				else if ((piony[c].pozycja_x > x)&&(piony[c].niezbity==true))
				{

					piony[c].pozycja_x =x;
					piony[c].pozycja_y = y;
					ai_czy_damka(gracz,szachownica,piony,c);
					szachownica[j][i].zajete = brak;
					szachownica[y][x].zajete = gracz.kolor_gracza;	
					//odswiezenie_mechanika(szachownica);
					powodzenie = true;
				}
			}
			break;
		case damka:
			if ((piony[c].pozycja_x < x)&&(piony[c].pozycja_y > y)&&(piony[c].niezbity==true))
			{

				piony[c].pozycja_x =x;
				piony[c].pozycja_y = y;
				//ai_czy_damka(gracz,szachownica,piony,c);
				szachownica[j][i].zajete = brak;
				szachownica[y][x].zajete = gracz.kolor_gracza;
				//odswiezenie_mechanika(szachownica);
				powodzenie = true;
			}
			else if ((piony[c].pozycja_x > x)&&(piony[c].pozycja_y > y)&&(piony[c].niezbity==true))
			{
				piony[c].pozycja_x =x;
				piony[c].pozycja_y = y;
				//ai_czy_damka(gracz,szachownica,piony,c);
				szachownica[j][i].zajete = brak;
				szachownica[y][x].zajete = gracz.kolor_gracza;
				//odswiezenie_mechanika(szachownica);
				powodzenie = true;
				}
			else if ((piony[c].pozycja_x < x)&&(piony[c].pozycja_y < y)&&(piony[c].niezbity==true))
			{

				piony[c].pozycja_x =x;
				piony[c].pozycja_y = y;
				//ai_czy_damka(gracz,szachownica,piony,c);
				szachownica[j][i].zajete = brak;
				szachownica[y][x].zajete = gracz.kolor_gracza;	
				//odswiezenie_mechanika(szachownica);
				powodzenie = true;
			}
			else if ((piony[c].pozycja_x > x)&&(piony[c].pozycja_y < y)&&(piony[c].niezbity==true))
			{

				piony[c].pozycja_x =x;
				piony[c].pozycja_y = y;
				//ai_czy_damka(gracz,szachownica,piony,c);
				szachownica[j][i].zajete = brak;
				szachownica[y][x].zajete = gracz.kolor_gracza;	
				//odswiezenie_mechanika(szachownica);
				powodzenie = true;
			}
			break;
		default:
			break;
		}	
	}
	//odswiezenie_grafika(figura);
	return powodzenie;
}

// kopiowanie tablicy dwuwymiarowej pol
Pole_s **kopiuj_pola(Pole_s **old_pole, int n)
{
	Pole_s **new_pole;
	new_pole = new Pole_s*[n];
	for (int i=0;i<n;i++)
	{
		new_pole[i] = new Pole_s[n];
		for (int j=0;j<n;j++)
		{
			new_pole[i][j].grafika = NULL;
			new_pole[i][j].kolor_pola = old_pole[i][j].kolor_pola;
			new_pole[i][j].podswietlenie= old_pole[i][j].podswietlenie;
			new_pole[i][j].pozycja_x=old_pole[i][j].pozycja_x;
			new_pole[i][j].pozycja_y=old_pole[i][j].pozycja_y;
			new_pole[i][j].zajete=old_pole[i][j].zajete;
		}
	}
	return new_pole;
}

// kopiowanie tablicy dwuwymiarowej pol do nowej struktury
ai_Pole_s **ai_kopiuj_pola(Pole_s **old_pole, int n)
{
	ai_Pole_s **new_pole;
	new_pole = new ai_Pole_s*[n];
	for (int i=0;i<n;i++)
	{
		new_pole[i] = new ai_Pole_s[n];
		for (int j=0;j<n;j++)
		{
			new_pole[i][j].kolor_pola = old_pole[i][j].kolor_pola;
			new_pole[i][j].pozycja_x=old_pole[i][j].pozycja_x;
			new_pole[i][j].pozycja_y=old_pole[i][j].pozycja_y;
			new_pole[i][j].zajete=old_pole[i][j].zajete;
		}
	}
	return new_pole;
}

// knowe kopiowanie
ai_Pole_s **si_ai_kopiuj_pola(ai_Pole_s **old_pole, int n)
{
	ai_Pole_s **new_pole;
	new_pole = new ai_Pole_s*[n];
	for (int i=0;i<n;i++)
	{
		new_pole[i] = new ai_Pole_s[n];
		for (int j=0;j<n;j++)
		{
			new_pole[i][j].kolor_pola = old_pole[i][j].kolor_pola;
			new_pole[i][j].pozycja_x=old_pole[i][j].pozycja_x;
			new_pole[i][j].pozycja_y=old_pole[i][j].pozycja_y;
			new_pole[i][j].zajete=old_pole[i][j].zajete;
		}
	}
	return new_pole;
}

// kopiowanie pionow
Pion_s *kopiuj_pion(Pion_s *old_pion, int n)
{
	Pion_s *new_pion;
	new_pion = new Pion_s[n];
	for (int i=0;i<n;i++)
	{
		new_pion[i].dzwiek[0] = NULL;
		new_pion[i].grafika = NULL;
		new_pion[i].kolor_pionu= old_pion[i].kolor_pionu;
		new_pion[i].niezbity=old_pion[i].niezbity;
		new_pion[i].pozycja_x=old_pion[i].pozycja_x;
		new_pion[i].pozycja_y=old_pion[i].pozycja_y;
		new_pion[i].status=old_pion[i].status;
	}
	return new_pion;
}

// kopiowanie pionow do struktury nowej
ai_Pion_s *ai_kopiuj_pion(Pion_s *old_pion, int n)
{
	ai_Pion_s *new_pion;
	new_pion = new ai_Pion_s[n];
	for (int i=0;i<n;i++)
	{
		new_pion[i].kolor_pionu= old_pion[i].kolor_pionu;
		new_pion[i].niezbity=old_pion[i].niezbity;
		new_pion[i].pozycja_x=old_pion[i].pozycja_x;
		new_pion[i].pozycja_y=old_pion[i].pozycja_y;
		new_pion[i].status=old_pion[i].status;
	}
	return new_pion;
}

// nowe kopiowanie pionow
ai_Pion_s *si_ai_kopiuj_pion(ai_Pion_s *old_pion, int n)
{
	ai_Pion_s *new_pion;
	new_pion = new ai_Pion_s[n];
	for (int i=0;i<n;i++)
	{
		new_pion[i].kolor_pionu= old_pion[i].kolor_pionu;
		new_pion[i].niezbity=old_pion[i].niezbity;
		new_pion[i].pozycja_x=old_pion[i].pozycja_x;
		new_pion[i].pozycja_y=old_pion[i].pozycja_y;
		new_pion[i].status=old_pion[i].status;
	}
	return new_pion;
}

// ewaluacja min-maxowa
int ewaluacja (ai_Pion_s *pion, Gracz_s gracz)
{
	int ev, g=0,k=0;
	for (int i=0;i<24;i++)
	{
		if(pion[i].niezbity==true)
		{
			if (pion[i].kolor_pionu==gracz.kolor_gracza)
			{
				k=k+2;
				if ((pion[i].pozycja_x==1)||(pion[i].pozycja_y==8)||(pion[i].pozycja_x==1)||(pion[i].pozycja_y==8))
				{
					k++;
				}
				if (pion[i].status == damka)
				{	
					k=k+14;
					g=g-5;
				}
			}
			else
			{
				g=g+2;
				if ((pion[i].pozycja_x==1)||(pion[i].pozycja_y==8)||(pion[i].pozycja_x==1)||(pion[i].pozycja_y==8))
				{
					g++;
				}
				if (pion[k].status==damka)
				{
					g=g+14;
					k=k-5;
				}
			}
		}
	}
	ev=k-g;
	return ev;
}

//zmiana gracza
Gracz_s zamiana_gracza(Gracz_s gracz)
{
	Gracz_s gracz2;
	if (gracz.kolor_gracza ==bialy)
	{
		gracz2.kolor_gracza =czarny;
	}
	else
	{
		gracz2.kolor_gracza=bialy;
	}
	if(gracz.nr_gracza ==1)
	{
		gracz2.nr_gracza=2;
	}
	else
	{
		gracz2.nr_gracza=1;
	}
	return gracz2;
}



// algorytm minmax
int min_max(int depth, int maxdepth, ai_Pole_s **szachownica, ai_Pion_s *pion, Gracz_s gracz, bool cb, int xx,int yy,int cc)
{
	int n=10, m=24, x,y,c, eval,wynik;
	int xxx=xx,ccc=cc,yyy=yy;
	bool jest_bicie = false, jest_ruch=false, czy_zbito = false, czy_ruszono = false, pom = false;
	bool cbb;
	cbb = cb;
	stack <int> stos;
	ai_Pole_s **n_szachownica = si_ai_kopiuj_pola(szachownica, n);
	ai_Pion_s *n_pion = si_ai_kopiuj_pion(pion, m);
	rekbicie2:
	if(cbb==true)
	{
		
		pom = ai_bicie(n_szachownica,n_pion,gracz,xxx,yyy,ccc);
	}
	else
	{
		pom = ai_ruch(n_szachownica,n_pion,gracz,xxx,yyy,ccc);
	}
	if(ai_czy_bicie_rek_pion(gracz,n_szachownica,n_pion,ccc)==true)
	{
		if((n_szachownica[yyy-1][xxx-1].zajete == zamiana(gracz.kolor_gracza))&&(n_szachownica[yyy-2][xxx-2].zajete == brak))
		{
			xxx = xxx-2;
			yyy=yyy-2;
			cbb=true;
			goto rekbicie2;
		}
		else if((n_szachownica[yyy-1][xxx+1].zajete == zamiana(gracz.kolor_gracza))&&(n_szachownica[yyy-2][xxx+2].zajete == brak))
		{
			xxx = xxx+2;
			yyy=yyy-2;
			cbb=true;
			goto rekbicie2;
		}
		else if((n_szachownica[yyy+1][xxx-1].zajete == zamiana(gracz.kolor_gracza))&&(n_szachownica[yyy+2][xxx-2].zajete == brak))
		{
			xxx = xxx-2;
			yyy=yyy+2;
			cbb=true;
			goto rekbicie2;
		}
		else if((n_szachownica[yyy+1][xxx+1].zajete == zamiana(gracz.kolor_gracza))&&(n_szachownica[yyy+2][xxx+2].zajete == brak))
		{
			xxx = xxx+2;
			yyy=yyy+2;
			cbb=true;
			goto rekbicie2;
		}


	}
	eval = ewaluacja(n_pion,gracz);
	if (depth==maxdepth)
	{
		for (int f=0;f<10;f++)
		{
			delete [] n_szachownica[f];
		}
		delete [] n_szachownica;
		n_szachownica = NULL;
		delete [] n_pion;
		n_pion = NULL;
		return eval;
	}
	jest_bicie = ai_czy_bicie(n_szachownica,n_pion,zamiana_gracza(gracz),stos);

	if (jest_bicie == false)
	{
		jest_ruch = ai_czy_ruch(n_szachownica,n_pion,zamiana_gracza(gracz),stos);
	}
	if (depth%2 == 0)
	{
		eval = -1000;
		while(stos.empty()==false)
		{
			x = stos.top();
			stos.pop();
			y= stos.top();
			stos.pop();
			c=stos.top();
			stos.pop();
			eval = max(eval, min_max(depth +1, maxdepth,n_szachownica,n_pion,zamiana_gracza(gracz),jest_bicie,x,y,c));
		}
		for (int f=0;f<10;f++)
		{
			delete [] n_szachownica[f];
		}
		delete [] n_szachownica;
		n_szachownica = NULL;
		delete [] n_pion;
		n_pion = NULL;
		return eval;	

	}
	else
	{
		eval = 1000;
		while(stos.empty()==false)
		{
			x = stos.top();
			stos.pop();
			y= stos.top();
			stos.pop();

			c=stos.top();
			stos.pop();
			eval = min(eval, min_max(depth +1, maxdepth,n_szachownica,n_pion,zamiana_gracza(gracz),jest_bicie,x,y,c));
			
		}
		for (int f=0;f<10;f++)
		{
			delete [] n_szachownica[f];
		}
		delete [] n_szachownica;
		n_szachownica = NULL;
		delete [] n_pion;
		n_pion = NULL;
		return eval;
	}

}


// tura gracza komputerowego
bool tura_komputer(Pole_s **szachownica, Pion_s *pion, Gracz_s gracz, int &biale_pionki, int &czarne_pionki, int &biale_damki, int &czarne_damki, ALLEGRO_BITMAP **guziki)
{
	int n=10, m=24, x,y,c,wynik,eval=-1000,xx,yy,cc;
	bool jest_bicie = false, jest_ruch=false, czy_zbito = false, czy_ruszono = false, czy_tura = false;
	stack <int> stos;
	ai_Pole_s **n_szachownica = ai_kopiuj_pola(szachownica, n);
	ai_Pion_s *n_pion = ai_kopiuj_pion(pion, m);
	
	jest_bicie = ai_czy_bicie(n_szachownica,n_pion,gracz,stos);
	if (jest_bicie == true)
	{
		
	
		
		while (stos.empty() ==false)
		{
			x = stos.top();
			stos.pop();
			y = stos.top();
				stos.pop();
			c = stos.top();
			stos.pop();
			wynik =  min_max(0, 4,n_szachownica,n_pion,gracz,jest_bicie,x,y,c);
			if (wynik>eval)
			{
				xx=x;
				yy=y;
				cc=c;
				eval = wynik;
			}
			//xx=x;
			//yy=y;
			//cc=c;
		}
		//xx=x;
		//yy=y;
		//cc=c;
		rekbicie:
		szachownica[yy][xx].podswietlenie=czerwony;
		czy_zbito = bicie(szachownica,pion,gracz,xx,yy,cc, biale_pionki, czarne_pionki, biale_damki, czarne_damki, guziki);
		if(czy_bicie_rek_pion(gracz,szachownica,pion,cc)==true)
		{
			

			if((szachownica[yy-1][xx-1].zajete == zamiana(gracz.kolor_gracza))&&(szachownica[yy-2][xx-2].zajete == brak))
			{
				xx = xx-2;
				yy=yy-2;
				goto rekbicie;
			}
			else if((szachownica[yy-1][xx+1].zajete == zamiana(gracz.kolor_gracza))&&(szachownica[yy-2][xx+2].zajete == brak))
			{
				xx = xx+2;
				yy=yy-2;
				goto rekbicie;
			}
			else if((szachownica[yy+1][xx-1].zajete == zamiana(gracz.kolor_gracza))&&(szachownica[yy+2][xx-2].zajete == brak))
			
				xx = xx-2;
				yy=yy+2;
				goto rekbicie;
			}
			else if((szachownica[yy+1][xx+1].zajete == zamiana(gracz.kolor_gracza))&&(szachownica[yy+2][xx+2].zajete == brak))
			{
				xx = xx+2;
				yy=yy+2;
				goto rekbicie;
			}


		
	}
	else
	{
		jest_ruch = ai_czy_ruch(n_szachownica,n_pion,gracz,stos);
		if(jest_ruch ==  true)
		{
			
			
			while (stos.empty() ==false)
			{
				x = stos.top();
				stos.pop();
				y = stos.top();
				stos.pop();
				c = stos.top();
				stos.pop();
				wynik =  min_max(0, 4,n_szachownica,n_pion,gracz,jest_bicie,x,y,c);
				if (wynik>eval)
				{
					xx=x;
					yy=y;
					cc=c;
					eval = wynik;
				}
				//xx=x;
				//yy=y;
				//cc=c;
			}
			szachownica[yy][xx].podswietlenie=zielony;
			czy_ruszono = ruch(szachownica,pion,gracz,xx,yy,cc, biale_damki, czarne_damki, guziki);
		}
	}
	if ((czy_zbito==true)||(czy_ruszono==true))
	{
		czy_tura = true;
	}
	return !(czy_tura);
}


// ewaluacja min-maxowa 2
int ewaluacja2 (ai_Pion_s *pion, Gracz_s gracz)
{
	int ev, g=0,k=0;
	for (int i=0;i<24;i++)
	{
		if(pion[i].niezbity==true)
		{
			if (gracz.nr_gracza == 2)
			{
				if (pion[i].kolor_pionu ==gracz.kolor_gracza)
				{
					k=k+2;
					if ((pion[i].pozycja_x==1)||(pion[i].pozycja_y==8)||(pion[i].pozycja_x==1)||(pion[i].pozycja_y==8))
					{
						k++;
					}
					if (pion[i].status == damka)
					{	
						k=k+14;
						g=g-5;
					}
				}
				else
				{
					g=g+2;
					if ((pion[i].pozycja_x==1)||(pion[i].pozycja_y==8)||(pion[i].pozycja_x==1)||(pion[i].pozycja_y==8))
					{
						g++;
					}
					if (pion[k].status==damka)
					{
						g=g+14;
						k=k-5;
					}
				}
			}
			else if (gracz.nr_gracza == 1)
			{
				if (pion[i].kolor_pionu ==zamiana(gracz.kolor_gracza))
				{
					k=k+2;
					if ((pion[i].pozycja_x==1)||(pion[i].pozycja_y==8)||(pion[i].pozycja_x==1)||(pion[i].pozycja_y==8))
					{
						k++;
					}
					if (pion[i].status == damka)
					{	
						k=k+14;
						g=g-5;
					}
				}
				else
				{
					g=g+2;
					if ((pion[i].pozycja_x==1)||(pion[i].pozycja_y==8)||(pion[i].pozycja_x==1)||(pion[i].pozycja_y==8))
					{
						g++;
					}
					if (pion[k].status==damka)
					{
						g=g+14;
						k=k-5;
					}
				}
			}
		}
	}
	ev=k-g;
	return ev;
}

struct decyzja
{
	int eval;
	int x;
	int y;
	int c;
	bool decyzja_czy_bicie;
};

decyzja minmax2 (int depth, int maxdepth, ai_Pole_s **szachownica, ai_Pion_s *pion, Gracz_s gracz, int x,int y,int c)
{
	int  xx,yy,cc;
	decyzja wybor;

	wybor.eval = ewaluacja2(pion,gracz);
	wybor.x =x;
	wybor.y=y;
	wybor.c=c;
	wybor.decyzja_czy_bicie=false;

	if(depth == maxdepth)
	{
		return wybor;
	}
	
	stack <int> stos;
	bool czybicie = false;
	bool czyruch = false;
	int wynikmax = -INFINITE, wynikmin= INFINITE,wynik;
	bool pom = false;
	
	
	
	
	czybicie = ai_czy_bicie(szachownica,pion,gracz,stos);
	wybor.decyzja_czy_bicie = czybicie;
	if (czybicie == false)
	{
		czyruch = ai_czy_ruch(szachownica,pion,gracz,stos);
		if (czyruch == false)
		{
			if (depth%2==0)
			{
			wybor.eval = -100000;
			//cout<< "przwewidzial przegrana kompa, poziom: " << depth << endl;
			}
			else
			{
				wybor.eval = 100000;
				//cout<< "przwewidzial przegrana gracza, poziom: " << depth << endl;
			}
			return wybor;	
		}
	}
	if (depth%2 ==0)
	{
		wybor.eval = -10000000;
	}
	else
	{
		wybor.eval = 10000000;
	}
	
	ai_Pole_s **pom_szachownica;
		ai_Pion_s *pom_pion;
	while (stos.empty() == false)
	{
		//system("CLS");
		++licznik;
		pom_szachownica = si_ai_kopiuj_pola(szachownica,10);
		pom_pion = si_ai_kopiuj_pion(pion,24);
		
		xx = stos.top();
		stos.pop();
		yy = stos.top();
		stos.pop();
		cc = stos.top();
		stos.pop();
		if(czybicie == true)
		{
			int ai_xx=xx, ai_yy=yy;
			rekbicie:
			pom = ai_bicie(pom_szachownica,pom_pion,gracz,ai_xx,ai_yy,cc);
			while(ai_czy_bicie_rek_pion(gracz,pom_szachownica,pom_pion,cc)==true)
			{
			

				if((pom_szachownica[ai_yy-1][ai_xx-1].zajete == zamiana(gracz.kolor_gracza))&&(pom_szachownica[ai_yy-2][ai_xx-2].zajete == brak))
				{
					ai_xx = ai_xx-2;
					ai_yy = ai_yy-2;
					goto rekbicie;
				}
				else if((pom_szachownica[ai_yy-1][ai_xx+1].zajete == zamiana(gracz.kolor_gracza))&&(pom_szachownica[ai_yy-2][ai_xx+2].zajete == brak))
				{
					ai_xx = ai_xx+2;
					ai_yy=ai_yy-2;
					goto rekbicie;
				}
				else if((pom_szachownica[ai_yy+1][ai_xx-1].zajete == zamiana(gracz.kolor_gracza))&&(pom_szachownica[ai_yy+2][ai_xx-2].zajete == brak))
				{
					ai_xx = ai_xx-2;
					ai_yy=ai_yy+2;
					goto rekbicie;
				}
				else if((pom_szachownica[ai_yy+1][ai_xx+1].zajete == zamiana(gracz.kolor_gracza))&&(pom_szachownica[ai_yy+2][ai_xx+2].zajete == brak))
				{
					ai_xx = ai_xx+2;
					ai_yy=ai_yy+2;
					goto rekbicie;
				}



			}
		}
		else
		{
			pom = ai_ruch(pom_szachownica,pom_pion,gracz,xx,yy,cc);
		}
		wynik = minmax2(depth+1,maxdepth,pom_szachownica,pom_pion,zamiana_gracza(gracz),xx,yy,cc).eval;
		if (depth%2 ==0)
		{
			if (wynik >= wybor.eval)
			{
				wybor.eval = wynik;
				if (depth==0)
				{
				wybor.x = xx;
				wybor.y=yy;
				wybor.c=cc;
				}
			}
			
		}
		else
		{
			if (wynik <= wybor.eval)
			{
				wybor.eval = wynik;
				if (depth==0)
				{
				wybor.x = xx;
				wybor.y=yy;
				wybor.c=cc;
				}
			}
			
		}


		for (int f=0;f<10;f++)
		{
			delete [] pom_szachownica[f];
		}
		delete [] pom_szachownica;
		pom_szachownica = NULL;
		delete [] pom_pion;
		pom_pion = NULL;
		
	}
	return wybor;

}

bool tura_kompa2 (Pole_s **polka, Pion_s *pionki, Gracz_s gracz, int &biale_pionki, int &czarne_pionki, int &biale_damki, int &czarne_damki, ALLEGRO_BITMAP **guziki)
{
	bool pom = false;
	decyzja wybor;
	//wybor.x=8;
	//wybor.y=5;
	//wybor.c = 11;
	//wybor.decyzja_czy_bicie = false;

	//system("CLS");
	//cout << endl;
	licznik = 0;

	ai_Pole_s **szachownica;
	ai_Pion_s *pion;
	szachownica = ai_kopiuj_pola(polka,10);
	pion = ai_kopiuj_pion(pionki,24);
	wybor = minmax2(0,4,szachownica,pion,gracz,1,1,1);
	if (wybor.decyzja_czy_bicie == true)
	{
		rekbicie:
		//cout << "Powinno byc BICIE"<<endl;
		polka[wybor.y][wybor.x].podswietlenie=czerwony;
		pom = bicie(polka,pionki,gracz,wybor.x,wybor.y,wybor.c, biale_pionki, czarne_pionki, biale_damki, czarne_damki, guziki);
		odswiezenie_mechanika(polka);
		if(czy_bicie_rek_pion(gracz,polka,pionki,wybor.c)==true)
		{
			

			if((polka[wybor.y-1][wybor.x-1].zajete == zamiana(gracz.kolor_gracza))&&(polka[wybor.y-2][wybor.x-2].zajete == brak))
			{
				wybor.x = wybor.x-2;
				wybor.y = wybor.y-2;
				goto rekbicie;
			}
			else if((polka[wybor.y-1][wybor.x+1].zajete == zamiana(gracz.kolor_gracza))&&(polka[wybor.y-2][wybor.x+2].zajete == brak))
			{
				wybor.x = wybor.x+2;
				wybor.y = wybor.y-2;
				goto rekbicie;
			}
			else if((polka[wybor.y+1][wybor.x-1].zajete == zamiana(gracz.kolor_gracza))&&(polka[wybor.y+2][wybor.x-2].zajete == brak))
			{
				wybor.x = wybor.x-2;
				wybor.y = wybor.y+2;
				goto rekbicie;
			}
			else if((polka[wybor.y+1][wybor.x+1].zajete == zamiana(gracz.kolor_gracza))&&(polka[wybor.y+2][wybor.x+2].zajete == brak))
			{
				wybor.x = wybor.x+2;
				wybor.y = wybor.y+2;
				goto rekbicie;
			}
		}
		
	}
	else
	{
		//cout<<"Powinien byc RUCH"<<endl;
		polka[wybor.y][wybor.x].podswietlenie=zielony;
		pom = ruch(polka,pionki,gracz,wybor.x,wybor.y,wybor.c, biale_damki, czarne_damki, guziki);
	}
	pom=false;
	//cout << licznik;
	//cout <<endl<<endl;
	return pom;
}


// tworzenie menu glownego
void main_menu_display (ALLEGRO_BITMAP **guziczki)
{
	al_clear_to_color(al_map_rgb(0,0,0));
	al_draw_bitmap(guziczki[0],0.0,0.0,NULL);
	al_draw_bitmap(guziczki[1],95.0,35.0,NULL);
	al_draw_bitmap(guziczki[2],162.0,240.0,NULL);
	al_draw_bitmap(guziczki[3],93.0,313.0,NULL);
	al_draw_bitmap(guziczki[4],188.0,386.0,NULL);
	al_draw_bitmap(guziczki[5],251.0,459.0,NULL);
	al_draw_bitmap(guziczki[6],220.0,532.0,NULL);

	al_flip_display();
}

// dzialanie menu glownego
void main_menu_execute (ALLEGRO_EVENT_QUEUE *&kolejeczka, int &sterujaca, ALLEGRO_BITMAP **guziczki)
{
	
	ALLEGRO_EVENT klik;
	main_menu_display(guziczki);
	//al_flip_display();
	bool pom = false;
	int pom2 = 0;
	while (!pom)
	{
		al_wait_for_event(kolejeczka, &klik);	
		if (klik.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			if ((klik.mouse.y >= 240)&&(klik.mouse.y < 300) && (pom2 != 1))
			{
				pom2=1;
				guziczki[2]=al_load_bitmap("obrazy/slajdy/single_player2.png");
				main_menu_display(guziczki);
				guziczki[2]=al_load_bitmap("obrazy/slajdy/single_player1.png");
			}
			else if ((klik.mouse.y >= 300)&&(klik.mouse.y < 373) && (pom2 != 2))
			{
				pom2=2;
				guziczki[3]=al_load_bitmap("obrazy/slajdy/pvp2.png");
				main_menu_display(guziczki);
				guziczki[3]=al_load_bitmap("obrazy/slajdy/pvp1.png");
			}
			else if ((klik.mouse.y >= 373)&&(klik.mouse.y < 446) && (pom2 != 3))
			{
				pom2=3;
				guziczki[4]=al_load_bitmap("obrazy/slajdy/online_game2.png");
				main_menu_display(guziczki);
				guziczki[4]=al_load_bitmap("obrazy/slajdy/online_game1.png");
			}
			else if ((klik.mouse.y >= 446)&&(klik.mouse.y < 516) && (pom2 != 4))
			{
				pom2=4;
				guziczki[5]=al_load_bitmap("obrazy/slajdy/options2.png");
				main_menu_display(guziczki);
				guziczki[5]=al_load_bitmap("obrazy/slajdy/options1.png");
			}
			else if ((klik.mouse.y >= 516)&&(klik.mouse.y < 592) && (pom2 != 5))
			{
				pom2=5;
				guziczki[6]=al_load_bitmap("obrazy/slajdy/quit_game2.png");
				main_menu_display(guziczki);
				guziczki[6]=al_load_bitmap("obrazy/slajdy/quit_game1.png");
			}
			else if (((klik.mouse.y >=592)|| (klik.mouse.y <240)) && (pom2 != 0))
			{
				pom2 = 0;
				main_menu_display(guziczki);
			}
		}
		else if (klik.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if (klik.mouse.button & 1)
			{
				if ((klik.mouse.y >= 240)&&(klik.mouse.y < 300))
				{
					sterujaca = 12;
					break;
				}
				else if ((klik.mouse.y >= 300)&&(klik.mouse.y < 373))
				{
					sterujaca = 13;
					break;
				}
				else if ((klik.mouse.y >= 373)&&(klik.mouse.y < 446))
				{
					//sterujaca = 3;
					//break;
				}
				else if ((klik.mouse.y >= 446)&&(klik.mouse.y < 516))
				{
					//sterujaca = 4;
					//break;
				}
				else if ((klik.mouse.y >= 516)&&(klik.mouse.y < 592))
				{
					sterujaca = -1;
					break;
				}
				else if (((klik.mouse.y >=592)|| (klik.mouse.y <240)))
				{
					;
				}
			}
		}
		else if (klik.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
				{
					sterujaca = -1;
					break;
				}
	}
}

//tworzenie pliku konfiguracyjnego
void config_file()
{
	FILE *plik;
	char *nazwa;
	plik = fopen("config.swc", "wt");
	nazwa = "Plik konfiguracyjny gry Star Wars The Checkers";
	fputs(nazwa, plik);
	fclose(plik);
}

//zapisywanie stanu gry
void save_game (int licznik, char *slowo, Gracz_s gracz1, Gracz_s gracz2, Pole_s **szachownica, Pion_s *pion, int sterujaca, int biale_pionki, int czarne_pionki, int biale_damki, int czarne_damki)
{
	FILE *plik;
	char *nazwa;
	nazwa = (char*)malloc((licznik+5)*sizeof(char));
	nazwa[0] = 's';
	nazwa[1] = 'a';
	nazwa[2] = 'v';
	nazwa[3] = 'e';
	nazwa[4] = '/';
	for (int l=5;l<(licznik+5);l++)
	{
		nazwa[l]=slowo[l-5];
	}
	plik = fopen(nazwa, "wb");
	fwrite(&gracz1, sizeof(gracz1), 1, plik);
	fwrite(&gracz2, sizeof(gracz1), 1, plik);
	for (int i=0;i<10;i++)
	{
		for (int j=0;j<10;j++)
		{
			fwrite(&szachownica[i][j], sizeof(szachownica[i][j]),1, plik);
		}
	}
	for (int k=0;k<24;k++)
	{
		fwrite(&pion[k],sizeof(pion[k]),1,plik);
	}
	fwrite(szachownica, sizeof(szachownica), 1, plik);
	fwrite(pion, sizeof(pion), 1, plik);
	fwrite(&sterujaca, sizeof(sterujaca), 1, plik);
	fwrite(&biale_pionki, sizeof(biale_pionki), 1, plik);
	fwrite(&czarne_pionki, sizeof(czarne_pionki), 1, plik);
	fwrite(&biale_damki, sizeof(biale_damki), 1, plik);
	fwrite(&czarne_damki, sizeof(czarne_damki), 1, plik);
	fclose(plik);
}

void load_game (char *nazzwa,Gracz_s gracz1, Gracz_s gracz2, Pole_s **szachownica, Pion_s *pion, int sterujaca, int biale_pionki, int czarne_pionki, int biale_damki, int czarne_damki)
{
	cout <<endl<< "aaaale" <<nazzwa;
	FILE *plik;
	char *nazwa = nazzwa;
	cout<<endl<<"x"<<nazwa<<"x"<<endl;
	plik = fopen(nazwa, "rb");
	fread(&gracz1, sizeof(gracz1), 1, plik);
	fread(&gracz2, sizeof(gracz1), 1, plik);
	for (int i=0;i<10;i++)
	{
		for (int j=0;j<10;j++)
		{
			fread(&szachownica[i][j], sizeof(szachownica[i][j]),1, plik);
		}
	}
	for (int k=0;k<24;k++)
	{
		fread(&pion[k],sizeof(pion[k]),1,plik);
	}
	fread(&sterujaca, sizeof(sterujaca), 1, plik);
	fread(&biale_pionki, sizeof(biale_pionki), 1, plik);
	fread(&czarne_pionki, sizeof(czarne_pionki), 1, plik);
	fread(&biale_damki, sizeof(biale_damki), 1, plik);
	fread(&czarne_damki, sizeof(czarne_damki), 1, plik);
	fclose(plik);
	for (unsigned i=0;i<10;i++)
	{
		for (unsigned j=0; j<10; j++)
		{
			if ((i != 0) && (i !=9) && (j !=0) && (j!=9))
			{
				if ((i+j)%2 == 1)
				{
					szachownica[i][j].grafika = al_load_bitmap("obrazy/tekstury/forcefield.jpg");

				}
				else
				{
					szachownica[i][j].grafika = al_load_bitmap("obrazy/tekstury/metal.jpg");
				}
			}
			else
			{
				;
			}
		}
	}
	int c =0;
	for (unsigned i=1; i<=3; i++)
	{
		for (unsigned j=1; j<=8; j++)
		{
			if ((i+j)%2 == 1)
			{
				if (gracz1.kolor_gracza == bialy)
				{
					pion[c].grafika = al_load_bitmap("obrazy/bohaterowie/stormtrooper.png");
					pion[c].dzwiek[0] = al_load_sample("dzwieki/glosy/stormtrooper1.ogg");
					pion[c].dzwiek[1] = al_load_sample("dzwieki/glosy/stormtrooper2.ogg");
					pion[c].dzwiek[2] = al_load_sample("dzwieki/glosy/stormtrooper3.ogg");
					pion[c].dzwiek[3] = al_load_sample("dzwieki/glosy/stormtrooper4.ogg");
					pion[c].dzwiek[4] = al_load_sample("dzwieki/glosy/stormtrooper5.ogg");
					pion[c].dzwiek[5] = al_load_sample("dzwieki/glosy/stormtrooper6.ogg");
				}
				else 
				{
					pion[c].grafika = al_load_bitmap("obrazy/bohaterowie/r2d22.png");
					pion[c].dzwiek[0] = al_load_sample("dzwieki/glosy/r2d21.ogg");
					pion[c].dzwiek[1] = al_load_sample("dzwieki/glosy/r2d22.ogg");
					pion[c].dzwiek[2] = al_load_sample("dzwieki/glosy/r2d23.ogg");
					pion[c].dzwiek[3] = al_load_sample("dzwieki/glosy/r2d24.ogg");
					pion[c].dzwiek[4] = al_load_sample("dzwieki/glosy/r2d25.ogg");
					pion[c].dzwiek[5] = al_load_sample("dzwieki/glosy/r2d26.ogg");
				}
				c++;
			}
		}
	}

	for (unsigned i=6; i<=8; i++)
	{
		for (unsigned j=1; j<=8; j++)
		{
			if ((i+j)%2 == 1)
			{
				if (gracz1.kolor_gracza == czarny)
				{
					pion[c].grafika = al_load_bitmap("obrazy/bohaterowie/stormtrooper.png");
					pion[c].dzwiek[0] = al_load_sample("dzwieki/glosy/stormtrooper1.ogg");
					pion[c].dzwiek[1] = al_load_sample("dzwieki/glosy/stormtrooper2.ogg");
					pion[c].dzwiek[2] = al_load_sample("dzwieki/glosy/stormtrooper3.ogg");
					pion[c].dzwiek[3] = al_load_sample("dzwieki/glosy/stormtrooper4.ogg");
					pion[c].dzwiek[4] = al_load_sample("dzwieki/glosy/stormtrooper5.ogg");
					pion[c].dzwiek[5] = al_load_sample("dzwieki/glosy/stormtrooper6.ogg");

				}
				else 
				{
					pion[c].grafika = al_load_bitmap("obrazy/bohaterowie/r2d22.png");
					pion[c].dzwiek[0] = al_load_sample("dzwieki/glosy/r2d21.ogg");
					pion[c].dzwiek[1] = al_load_sample("dzwieki/glosy/r2d22.ogg");
					pion[c].dzwiek[2] = al_load_sample("dzwieki/glosy/r2d23.ogg");
					pion[c].dzwiek[3] = al_load_sample("dzwieki/glosy/r2d24.ogg");
					pion[c].dzwiek[4] = al_load_sample("dzwieki/glosy/r2d25.ogg");
					pion[c].dzwiek[5] = al_load_sample("dzwieki/glosy/r2d26.ogg");

				}
				c++;
			}
		}
	}
}

void draw_load_window (int *wysokosc, string *nazwy, ALLEGRO_BITMAP **guziczki, ALLEGRO_FONT *naglowek, ALLEGRO_FONT *tekst_zwykly)
{
	al_clear_to_color(al_map_rgb(0,0,0));
	al_draw_bitmap(guziczki[0],0,0,NULL);
	al_draw_filled_rectangle(52.0,129.0,580.0,603.0,al_map_rgba(20,20,20,100));
	al_draw_filled_rectangle(618.0,337.0,818.0,406.0,al_map_rgb(253,211,3));
	al_draw_filled_rectangle(618.0,437.0,818.0,506.0,al_map_rgb(253,211,3));
	al_draw_filled_rectangle(618.0,537.0,818.0,606.0,al_map_rgb(253,211,3));
	al_draw_text(tekst_zwykly,al_map_rgb(0,0,0),718,348, ALLEGRO_ALIGN_CENTRE, "load");
	al_draw_text(tekst_zwykly,al_map_rgb(0,0,0),718,448, ALLEGRO_ALIGN_CENTRE, "delete");
	al_draw_text(tekst_zwykly,al_map_rgb(0,0,0),718,548, ALLEGRO_ALIGN_CENTRE, "cancel");
	al_draw_text(naglowek,al_map_rgb(253,211,3),430,18, ALLEGRO_ALIGN_CENTRE, "# Load game #");
	//al_flip_display();
	int c=0;
	while ((nazwy[c].length() > 1)&&(c<15))
	{
		char *str;
		str = new char[nazwy[c].length()];
		nazwy[c].copy(str,nazwy[c].length(),0);
		al_draw_text(tekst_zwykly,al_map_rgb(255,255,255),69,wysokosc[c],NULL,str);
		c++;
		delete str;
	}
	//al_flip_display();
}

int load_window (Gracz_s gracz1, Gracz_s gracz2, Pole_s **szachownica, Pion_s *pion, int biale_pionki, int czarne_pionki, int biale_damki, int czarne_damki,
				 ALLEGRO_EVENT_QUEUE *&kolejeczka, int &sterujaca, ALLEGRO_BITMAP **guziczki, ALLEGRO_FONT *naglowek, ALLEGRO_FONT *tekst_zwykly)
{
	int wysokosc[15];
	string nazwy [ 15 ];
	for (int i =0; i<15;i++)
	{
		wysokosc[i] = 0;
		nazwy[i]="1";
	}
	int c = 133;
	int j =0;
	WIN32_FIND_DATA plik;
	HANDLE u_plik;
	u_plik = FindFirstFile(TEXT("save/*.swcs"), &plik);
	do 
	{
		wysokosc[j]=c;
		nazwy[j] = plik.cFileName;
		j++;	
		c=c+30;
	} while ((FindNextFile(u_plik, &plik)) && (j<15));
	//CloseHandle(u_plik);
	FindClose(u_plik);
	DeleteFile("save/vcv.swcs");
	draw_load_window(wysokosc, nazwy, guziczki,naglowek,tekst_zwykly);
	al_flip_display();
	ALLEGRO_EVENT klik;
	bool pom = false;
	int pom2 = -1;
	int pom3 = -1;
	
	while(!pom)
	{
		al_wait_for_event(kolejeczka,&klik);
		if (klik.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			sterujaca = -1;
			return -1;
		}
		else if (klik.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			if (klik.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
			{
				sterujaca = -1;
				return -1;
			}
		}
		else if ((klik.type == ALLEGRO_EVENT_MOUSE_AXES))
		{
			
			if((klik.mouse.x<52)||(klik.mouse.x>580)||(klik.mouse.y < 135)||(klik.mouse.y > 164 + (j-1)*30)&&(pom2 != -1))
			{
				pom2 = -1;
				draw_load_window(wysokosc, nazwy, guziczki,naglowek,tekst_zwykly);
				if (pom3 != -1)
					{
						char *str5;
						str5 = new char[nazwy[pom3].length()];
						nazwy[pom3].copy(str5,nazwy[pom3].length(),0);
						al_draw_text(tekst_zwykly,al_map_rgb(253,111,120),69,wysokosc[pom3],NULL,str5);
						delete str5;
					}
				al_flip_display();
			}
			else
			{
				for (int k=0;k<15;k++)
				{
					if ((klik.mouse.x>=52)&&(klik.mouse.x<=580)&&(klik.mouse.y >= 135 + (k*30))&&(klik.mouse.y <= (164 + k*30))&&(nazwy[k].length() > 1)&&(pom2 != k))
					{
						pom2=k;
						char *str;
						str = new char[nazwy[k].length()];
						nazwy[k].copy(str,nazwy[k].length(),0);
						draw_load_window(wysokosc, nazwy, guziczki,naglowek,tekst_zwykly);
						al_draw_text(tekst_zwykly,al_map_rgb(253,211,2),69,wysokosc[k],NULL,str);
						if (pom3 != -1)
						{
							char *str2;
							str2 = new char[nazwy[pom3].length()];
							nazwy[pom3].copy(str2,nazwy[pom3].length(),0);
							al_draw_text(tekst_zwykly,al_map_rgb(253,111,120),69,wysokosc[pom3],NULL,str2);
							delete str2;
						}
						al_flip_display();
						delete str;
						
						break;
					}
		
				}
			}
		}
		else if ((klik.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN))
		{
			if ((klik.mouse.x>=618)&&(klik.mouse.x<= 818)&&(klik.mouse.y >= 537)&&(klik.mouse.y <= 606))
			{
				al_draw_text(tekst_zwykly,al_map_rgb(255,255,255),718,548, ALLEGRO_ALIGN_CENTRE, "cancel");
				al_flip_display();
				al_rest(0.3);
				sterujaca = 0;
				return 0;
			}
			else if ((klik.mouse.x>=618)&&(klik.mouse.x<= 818)&&(klik.mouse.y >= 437)&&(klik.mouse.y <= 506)&&(pom3 != -1))
			{
				
				al_draw_text(tekst_zwykly,al_map_rgb(255,255,255),718,448, ALLEGRO_ALIGN_CENTRE, "delete");
				al_flip_display();
				al_rest(0.3);
				string strpom1 = "save/";
				strpom1 += nazwy[pom3];
				cout << endl <<strpom1 <<endl;
				cout << endl <<strpom1.length() <<endl;
				char *str3;
				str3 = (char*)malloc(strpom1.length()*sizeof(char)+1);
				strpom1.copy(str3,strpom1.length(),0);
				str3[strpom1.length()]='\0';
				cout<<str3<<"|";
				DeleteFile(str3);
				delete str3;
				if (sterujaca == 10)
				{
					sterujaca = 10;
					return 10;
				}
				else if (sterujaca == 11)
				{
					sterujaca = 11;
					return 11;
				}	
			}
			else if ((klik.mouse.x>=618)&&(klik.mouse.x<= 818)&&(klik.mouse.y >= 337)&&(klik.mouse.y <= 406)&&(pom3 != -1))
			{
				
				al_draw_text(tekst_zwykly,al_map_rgb(255,255,255),718,348, ALLEGRO_ALIGN_CENTRE, "load");
				al_flip_display();
				string strpom2 = "save/";
				strpom2 += nazwy[pom3];
				char *str4;
				str4 = (char*)malloc(strpom2.length()*sizeof(char)+1);
				strpom2.copy(str4,strpom2.length(),0);
				str4[strpom2.length()]='\0';
				load_game(str4,gracz1,gracz2,szachownica,pion,sterujaca,biale_pionki,czarne_pionki,biale_damki,czarne_damki);
				delete str4;
				if (sterujaca == 10)
				{
					sterujaca = 1;
					return 1;
				}
				else if (sterujaca == 11)
				{
					sterujaca = 2;
					return 2;
				}
				
			}
			else
			{
				for (int k=0;k<15;k++)
				{
				if ((klik.mouse.x>=52)&&(klik.mouse.x<=580)&&(klik.mouse.y >= 135 + (k*30))&&(klik.mouse.y <= (164 + k*30))&&(nazwy[k].length() > 1))
					{
						pom3 = k;
						char *str;
						str = new char[nazwy[k].length()];
						nazwy[k].copy(str,nazwy[k].length(),0);
						draw_load_window(wysokosc, nazwy, guziczki,naglowek,tekst_zwykly);
						al_draw_text(tekst_zwykly,al_map_rgb(253,111,120),69,wysokosc[k],NULL,str);
						al_flip_display();
						delete str;
						break;
					}
				}
			}
		}
	}
}

void draw_save_window(ALLEGRO_BITMAP **guziczki, ALLEGRO_FONT *naglowek, ALLEGRO_FONT *tekst_zwykly, ALLEGRO_FONT *tekst_posredni)
{
	al_clear_to_color(al_map_rgb(0,0,0));
	al_draw_bitmap(guziczki[0],0,0,NULL);
	al_draw_bitmap(guziczki[1],200,350,NULL);
	al_draw_filled_rectangle(90.0,180.0,770.0,280.0,al_map_rgba(20,20,20,100));
	al_draw_filled_rectangle(618.0,337.0,818.0,406.0,al_map_rgb(253,211,3));
	al_draw_filled_rectangle(618.0,437.0,818.0,506.0,al_map_rgb(253,211,3));
	al_draw_filled_rectangle(618.0,537.0,818.0,606.0,al_map_rgb(253,211,3));
	al_draw_text(tekst_zwykly,al_map_rgb(0,0,0),718,348, ALLEGRO_ALIGN_CENTRE, "save");
	al_draw_text(tekst_zwykly,al_map_rgb(0,0,0),718,448, ALLEGRO_ALIGN_CENTRE, "clear");
	al_draw_text(tekst_zwykly,al_map_rgb(0,0,0),718,548, ALLEGRO_ALIGN_CENTRE, "cancel");
	al_draw_text(naglowek,al_map_rgb(253,211,3),430,18, ALLEGRO_ALIGN_CENTRE, "# Save game #");
}

int save_window(Gracz_s gracz1, Gracz_s gracz2, Pole_s **szachownica, Pion_s *pion, int biale_pionki, int czarne_pionki, int biale_damki, int czarne_damki,
				ALLEGRO_EVENT_QUEUE *&kolejeczka, int &sterujaca, ALLEGRO_BITMAP **guziczki, ALLEGRO_FONT *naglowek, ALLEGRO_FONT *tekst_zwykly, ALLEGRO_FONT *tekst_posredni)
{
	draw_save_window(guziczki,naglowek,tekst_zwykly,tekst_posredni);
	al_flip_display();
	ALLEGRO_EVENT klik;

	bool pom = false;
	draw_save_window(guziczki,naglowek,tekst_zwykly,tekst_posredni);
	int counter = 1;
	char *str;
	str = (char*)malloc(counter*sizeof(char));
	str[0] = ' ';
	while (!pom)
	{
		al_wait_for_event(kolejeczka,&klik);
		draw_save_window(guziczki,naglowek,tekst_zwykly,tekst_posredni);
		if (klik.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if ((klik.mouse.x>=618)&&(klik.mouse.x<= 818)&&(klik.mouse.y >= 537)&&(klik.mouse.y <= 606))
			{
				al_draw_text(tekst_zwykly,al_map_rgb(255,255,255),718,548, ALLEGRO_ALIGN_CENTRE, "cancel");
				al_flip_display();
				al_rest(0.3);
				if (sterujaca == 6)
					{
						sterujaca = 1;
						return 1;
					}
					else if (sterujaca == 7)
					{
						sterujaca = 2;
						return 2;
					}
			}
			else if ((klik.mouse.x>=618)&&(klik.mouse.x<= 818)&&(klik.mouse.y >= 437)&&(klik.mouse.y <= 506))
			{
				while (counter>1)
				{
					counter--;
					str[counter-1]='\0';
					//str[counter-2]='\0';
					str = (char*)realloc(str, counter*sizeof(char));
				}
				al_draw_text(tekst_zwykly,al_map_rgb(255,255,255),718,448, ALLEGRO_ALIGN_CENTRE, "clear");
				al_draw_text(tekst_posredni,al_map_rgb(255,255,255),430,190, ALLEGRO_ALIGN_CENTRE, str );
				al_flip_display();
				al_rest(0.15);
				al_draw_text(tekst_zwykly,al_map_rgb(0,0,0),718,448, ALLEGRO_ALIGN_CENTRE, "clear");
				al_flip_display();

			}
			else if ((klik.mouse.x>=618)&&(klik.mouse.x<= 818)&&(klik.mouse.y >= 337)&&(klik.mouse.y <= 406))
			{
				
				if (counter <= 2)
				{
					
					al_draw_text(tekst_posredni,al_map_rgb(255,255,255),430,190, ALLEGRO_ALIGN_CENTRE, str );
					al_draw_text(tekst_zwykly,al_map_rgb(253,111,120),430,270, ALLEGRO_ALIGN_CENTRE, "filename is too short");
					al_draw_text(tekst_zwykly,al_map_rgb(255,255,255),718,348, ALLEGRO_ALIGN_CENTRE, "save");
					al_flip_display();
					al_rest(0.15);
					draw_save_window(guziczki,naglowek,tekst_zwykly,tekst_posredni);
					al_draw_text(tekst_posredni,al_map_rgb(255,255,255),430,190, ALLEGRO_ALIGN_CENTRE, str );
					al_draw_text(tekst_zwykly,al_map_rgb(253,111,120),430,270, ALLEGRO_ALIGN_CENTRE, "filename is too short");
					al_flip_display();
					continue;
				}
				else
				{
					counter = counter +5;
					str = (char*)realloc(str, counter*sizeof(char));
					str[counter-6]='.';
					str[counter-5]='s';
					str[counter-4]='w';
					str[counter-3]='c';
					str[counter-2]='s';
					str[counter-1]='\0';
					draw_save_window(guziczki,naglowek,tekst_zwykly,tekst_posredni);
					al_draw_text(tekst_zwykly,al_map_rgb(255,255,255),718,348, ALLEGRO_ALIGN_CENTRE, "save");
					al_draw_text(tekst_posredni,al_map_rgb(255,255,255),430,190, ALLEGRO_ALIGN_CENTRE, str );
					al_flip_display();
					al_rest(0.15);
					draw_save_window(guziczki,naglowek,tekst_zwykly,tekst_posredni);
					al_draw_text(tekst_posredni,al_map_rgb(255,255,255),430,190, ALLEGRO_ALIGN_CENTRE, str );
					al_draw_text(tekst_zwykly,al_map_rgb(111,253,120),430,270, ALLEGRO_ALIGN_CENTRE, "game saved");
					al_flip_display();
					al_rest(0.7);
				
					save_game(counter, str,gracz1,gracz2,szachownica,pion,sterujaca,liczba_bialych,liczba_czarnych,liczba_bialych_damek,liczba_czarnych_damek);
					while (counter>1)
					{
						counter--;
						str[counter-1]='\0';
						//str[counter-2]='\0';
						str = (char*)realloc(str, counter*sizeof(char));
					}
					draw_save_window(guziczki,naglowek,tekst_zwykly,tekst_posredni);
					al_flip_display();
					if (sterujaca == 6)
					{
						sterujaca = 1;
						return 1;
					}
					else if (sterujaca == 7)
					{
						sterujaca = 2;
						return 2;
					}
				}
				//al_draw_text(tekst_zwykly,al_map_rgb(255,255,255),718,448, ALLEGRO_ALIGN_CENTRE, "save");
			}
		}
		else if(klik.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			if (klik.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
			{
				sterujaca = -1;
				return -1;
			}
			if (klik.keyboard.keycode == ALLEGRO_KEY_BACKSPACE)
			{
				if (counter>1)
				{
					counter--;
					str[counter-1]='\0';
					//str[counter-2]='\0';
					str = (char*)realloc(str, counter*sizeof(char));
					al_draw_text(tekst_posredni,al_map_rgb(255,255,255),430,190, ALLEGRO_ALIGN_CENTRE, str );
					al_flip_display();
					continue;
				}
			}
			if((((al_keycode_to_name(klik.keyboard.keycode)[0] >= 65)&&(al_keycode_to_name(klik.keyboard.keycode)[0] <= 90))||((al_keycode_to_name(klik.keyboard.keycode)[0] >= 48)&&(al_keycode_to_name(klik.keyboard.keycode)[0] <= 57)))&&(al_keycode_to_name(klik.keyboard.keycode)[1] == 0))
			{
				char *cr;
				cr = (char*)malloc(2*sizeof(char));
				cr[0] = al_keycode_to_name(klik.keyboard.keycode)[0];
				cr[1]='\0';
				cr[0] = tolower(cr[0]);
				counter++;
				str = (char*)realloc(str, counter*sizeof(char));
				str[counter-2]=cr[0];
				str[counter-1]='\0';
				al_draw_text(tekst_posredni,al_map_rgb(255,255,255),430,190, ALLEGRO_ALIGN_CENTRE, str );
				al_flip_display();
			}
		}
	}
	al_rest(5.0);
	return 1;
}

void draw_choose_window(ALLEGRO_BITMAP **guziczki, ALLEGRO_FONT *naglowek, ALLEGRO_FONT *tekst_zwykly, ALLEGRO_FONT *tekst_posredni)
{
	al_clear_to_color(al_map_rgb(0,0,0));
	al_draw_bitmap(guziczki[0],0,0,NULL);;
	//al_draw_filled_rectangle(90.0,180.0,770.0,280.0,al_map_rgba(20,20,20,100));
	al_draw_filled_rectangle(200.0,200.0,660.0,350.0,al_map_rgb(253,211,3));
	al_draw_filled_rectangle(200.0,400.0,660.0,550.0,al_map_rgb(253,211,3));
	//al_draw_filled_rectangle(618.0,537.0,818.0,606.0,al_map_rgb(253,211,3));
	al_draw_text(tekst_posredni,al_map_rgb(0,0,0),430,230, ALLEGRO_ALIGN_CENTRE, "new game");
	al_draw_text(tekst_posredni,al_map_rgb(0,0,0),430,430, ALLEGRO_ALIGN_CENTRE, "load game");
	//al_draw_text(tekst_zwykly,al_map_rgb(0,0,0),718,548, ALLEGRO_ALIGN_CENTRE, "cancel");
	al_draw_text(naglowek,al_map_rgb(253,211,3),430,18, ALLEGRO_ALIGN_CENTRE, "# Choose game #");
}

int choose_window(Gracz_s gracz1, Gracz_s gracz2, Pole_s **szachownica, Pion_s *pion, int biale_pionki, int czarne_pionki, int biale_damki, int czarne_damki,
				ALLEGRO_EVENT_QUEUE *&kolejeczka, int &sterujaca, ALLEGRO_BITMAP **guziczki, ALLEGRO_FONT *naglowek, ALLEGRO_FONT *tekst_zwykly, ALLEGRO_FONT *tekst_posredni)
{
	draw_choose_window(guziczki,naglowek,tekst_zwykly,tekst_posredni);
	al_flip_display();
	ALLEGRO_EVENT klik;
	bool pom = false;
	while (!pom)
	{
		al_wait_for_event(kolejeczka,&klik);
		draw_choose_window(guziczki,naglowek,tekst_zwykly,tekst_posredni);
		if (klik.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if ((klik.mouse.x >= 200)&&(klik.mouse.x <=660) &&(klik.mouse.y>=200)&&(klik.mouse.y<=350))
			{
				al_draw_text(tekst_posredni,al_map_rgb(255,255,255),430,230, ALLEGRO_ALIGN_CENTRE, "new game");
				al_flip_display();
				al_rest(0.15);
				board_reset(gracz1,szachownica,pion,biale_pionki,czarne_pionki,biale_damki,czarne_damki);
				if (sterujaca == 12)
				{
					sterujaca = 1;
					return 1;
				}
				else if (sterujaca == 13)
				{
					sterujaca = 2;
					return 2;
				}
			}
			else if ((klik.mouse.x >= 200)&&(klik.mouse.x <=660) &&(klik.mouse.y>=400)&&(klik.mouse.y<=550))
			{
				al_draw_text(tekst_posredni,al_map_rgb(255,255,255),430,430, ALLEGRO_ALIGN_CENTRE, "load game");
				al_flip_display();
				al_rest(0.15);
				if (sterujaca == 12)
				{
					sterujaca = 10;
					return 10;
				}
				else if (sterujaca == 13)
				{
					sterujaca = 11;
					return 11;
				}
			}
		}
	}
	return 0;
}



int  main()
{
	// ustawienie losowosci
	srand(time(0));

	// inicjalizacja modulow allegro
	al_init();
	al_install_keyboard();
	al_install_mouse();
	al_init_font_addon();
	al_init_image_addon();
	al_init_primitives_addon();
	al_init_ttf_addon();
	al_install_audio();
	al_init_acodec_addon();

	// zmienna do wyjscia z programu
	bool wyjscie = false;

	// zmienna sterujaca stanem programu
	int zmienna_steruj¹ca = 0;

	// ustawienia okna glownego
	ALLEGRO_DISPLAY *okno = al_create_display(dlugosc_okna, szerokosc_okna);
	ALLEGRO_BITMAP *ikona = al_load_bitmap("obrazy/ikona/ikona.jpg");
	ALLEGRO_BITMAP *firma = al_load_bitmap("obrazy/slajdy/firma.jpg");
	ALLEGRO_BITMAP *lightsaber = al_load_bitmap("obrazy/slajdy/red.png");
	al_set_display_icon(okno, ikona);
	al_set_new_display_flags(ALLEGRO_GENERATE_EXPOSE_EVENTS);
	al_set_window_title(okno, "Warcaby v0.01");
	al_clear_to_color(al_map_rgb_f(0.0,0.0,0.0));
	al_draw_bitmap(firma,110.0,0.0,NULL);
	al_flip_display();
	al_rest(1.7);

	// ustawienia czcionek
	ALLEGRO_FONT *sw_font_h = al_load_ttf_font("Czcionki/Starjedi.ttf",69,NULL);
	ALLEGRO_FONT *sw_font_r = al_load_ttf_font("Czcionki/Starjedi.ttf",27,NULL);
	ALLEGRO_FONT *sw_font_m = al_load_ttf_font("Czcionki/Starjedi.ttf",51,NULL);
	ALLEGRO_COLOR sw_bialy = al_map_rgb(255,255,255);
	ALLEGRO_COLOR sw_czarny = al_map_rgb(0,0,0);
	ALLEGRO_COLOR sw_zloty = al_map_rgb(253,211,2);

	// ustatwienia dzwieku
	al_reserve_samples(2);
	ALLEGRO_SAMPLE *podklad = al_load_sample("dzwieki/muzyka/starwars.wav");
	ALLEGRO_SAMPLE_INSTANCE *instancja = al_create_sample_instance(podklad);
	al_set_sample_instance_playmode(instancja, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(instancja, al_get_default_mixer());
	al_play_sample_instance(instancja);
	
	// ladowanie bitmap
	ALLEGRO_BITMAP *tytulowy = al_load_bitmap("obrazy/slajdy/tytulowy.jpg");
	ALLEGRO_BITMAP *przyciski[5];
	przyciski[0] = al_load_bitmap("obrazy/slajdy/star_background.jpg");
	przyciski[1] = al_load_bitmap("obrazy/slajdy/small_logo2.png");
	przyciski[2] = al_load_bitmap("obrazy/slajdy/sound_on.png");
	przyciski[3] = al_load_bitmap("obrazy/slajdy/save1.png");
	przyciski[4] = al_load_bitmap("obrazy/slajdy/return1.png");
	ALLEGRO_BITMAP *przyciski2[7];
	przyciski2[0] = al_load_bitmap("obrazy/slajdy/star_background.jpg");
	przyciski2[1] = al_load_bitmap("obrazy/slajdy/main_menu.png");
	przyciski2[2] = al_load_bitmap("obrazy/slajdy/single_player1.png");
	przyciski2[3] = al_load_bitmap("obrazy/slajdy/pvp1.png");
	przyciski2[4] = al_load_bitmap("obrazy/slajdy/online_game1.png");
	przyciski2[5] = al_load_bitmap("obrazy/slajdy/options1.png");
	przyciski2[6] = al_load_bitmap("obrazy/slajdy/quit_game1.png");
	al_clear_to_color(al_map_rgb_f(0.0,0.0,0.0));
	al_draw_bitmap(tytulowy,110.0,0.0,NULL);
	al_flip_display();
	al_rest(2.3);
	ALLEGRO_BITMAP *pole_biale = al_load_bitmap("obrazy/tekstury/metal.jpg");
	ALLEGRO_BITMAP *pole_czarne = al_load_bitmap("obrazy/tekstury/forcefield.jpg");
	/*ALLEGRO_BITMAP *r2d2 = al_load_bitmap("obrazy/bohaterowie/r2d22.png");
	ALLEGRO_BITMAP *stormtrooper = al_load_bitmap("obrazy/bohaterowie/stormtrooper.png");
	ALLEGRO_BITMAP *darthvader = al_load_bitmap("obrazy/bohaterowie/darthvader1.png");
	ALLEGRO_BITMAP *masteryoda = al_load_bitmap("obrazy/bohaterowie/masteryoda2.png");
	ALLEGRO_BITMAP *emperor = al_load_bitmap("obrazy/bohaterowie/emperor.png");
	ALLEGRO_BITMAP *hansolo = al_load_bitmap("obrazy/bohaterowie/hansolo.png");*/

	// tworzenie kolejki eventow
	ALLEGRO_EVENT_QUEUE *kolejka = al_create_event_queue();
	al_register_event_source(kolejka, al_get_mouse_event_source());
	al_register_event_source(kolejka, al_get_keyboard_event_source());
	al_register_event_source(kolejka, al_get_display_event_source(okno));

	// ustawienia graczy
	Gracz_s gracz_1, gracz_2;
	gracz_1.kolor_gracza = czarny;
	gracz_1.nr_gracza = 1;
	gracz_1.stan = w_trakcie_gry;
	gracz_2.kolor_gracza = zamiana(gracz_1.kolor_gracza);
	gracz_2.nr_gracza = 2;
	gracz_2.stan = w_trakcie_gry;

	// inicjalizacja planszy i figur
	pole = tworzenie_szachownicy(pole_biale, pole_czarne, przyciski);
	figura = tworzenie_listy_figur(gracz_1, pole, liczba_bialych, liczba_czarnych);
	//ALLEGRO_PATH *path = NULL;
	//path = al_get_path(ALLEGRO_RESOURCES_PATH);
	//ALLEGRO_FILECHOOSER *otwieracz = NULL;
	//otwieracz = al_create_native_file_dialog(NULL,"otwieracz","*.*",ALLEGRO_FILECHOOSER_SAVE);
	//bool xyz = false;
	//al_show_native_file_dialog(al_get_current_display(), otwieracz);
	//al_flip_display();

	// menu glowne
	main_menu:
	main_menu_execute(kolejka,zmienna_steruj¹ca,przyciski2);
	goto control_panel;


	// modul sterujacy
	control_panel:
	switch (zmienna_steruj¹ca)
	{
	case -1:
		goto the_end;
		break;
	case 0:
		goto main_menu;
		break;
	case 1:
		//board_reset(gracz_1,pole,figura,liczba_bialych,liczba_czarnych, liczba_bialych_damek, liczba_czarnych_damek);
		goto single_player;	
		break;
	case 2: 
		//board_reset(gracz_1,pole,figura,liczba_bialych,liczba_czarnych, liczba_bialych_damek, liczba_czarnych_damek);
		goto multi_player;
		break;
	case 3:
		goto online_game;
		break;
	case 4:
		goto options;
		break;
	case 5:
		goto g_load;
		break;
	case 6:
		goto g_save;
		break;
	case 7:
		goto g_save;
		break;
	case 8:
		goto g_save;
		break;
	case 9:
		goto g_save;
		break;
		case 10:
		goto g_load;
		break;
	case 11:
		goto g_load;
		break;
	case 12:
		goto new_or_load;
		break;
	case 13:
		goto new_or_load;
		break;
	}


	// wybieranie nowej lub wczytanej gry
new_or_load:
	choose_window(gracz_1,gracz_2,pole,figura,liczba_bialych,liczba_czarnych,liczba_bialych_damek,liczba_czarnych_damek,kolejka,zmienna_steruj¹ca,przyciski,sw_font_h,sw_font_r,sw_font_m);
	goto control_panel;
	

	// ladowanie ustawien
	g_load:
	//save_game(gracz_1,gracz_2,pole,figura,zmienna_steruj¹ca,liczba_bialych,liczba_czarnych,liczba_bialych_damek,liczba_czarnych_damek);
	load_window(gracz_1,gracz_2,pole,figura,liczba_bialych,liczba_czarnych,liczba_bialych_damek,liczba_czarnych_damek, kolejka,zmienna_steruj¹ca,przyciski,sw_font_h,sw_font_r);
	goto control_panel;


	// zapisywanie ustawien
	g_save:
	save_window(gracz_1,gracz_2,pole,figura,liczba_bialych,liczba_czarnych,liczba_bialych_damek,liczba_czarnych_damek,kolejka,zmienna_steruj¹ca,przyciski,sw_font_h,sw_font_r,sw_font_m);
	goto control_panel;


	// tryb dla jednego gracza
	single_player:
	odswiezenie_grafika(pole,figura,gracz_1.nr_gracza,przyciski);
	zmienna_steruj¹ca =1;
	while (!wyjscie)
	{
		if (!wyjscie)
		{
			wyjscie =tura(gracz_1, gracz_2,pole,figura,kolejka, liczba_bialych, liczba_czarnych, liczba_bialych_damek, liczba_czarnych_damek, zmienna_steruj¹ca, przyciski);
		if (wyjscie == false)
		{
			wyjscie=czy_koniec(liczba_bialych,liczba_czarnych, liczba_bialych_damek, liczba_czarnych_damek,okno,wyjscie);
		}
		}
		if (!wyjscie)
		{
		 wyjscie = tura_kompa2 (pole,figura, gracz_2, liczba_bialych, liczba_czarnych, liczba_bialych_damek, liczba_czarnych_damek, przyciski);
		 wyjscie=czy_koniec(liczba_bialych,liczba_czarnych, liczba_bialych_damek, liczba_czarnych_damek, okno,wyjscie);
		 //wyjscie=false;
		}
	}
	wyjscie = false;
	//save_game(gracz_1,gracz_2,pole,figura,zmienna_steruj¹ca,liczba_bialych,liczba_czarnych,liczba_bialych_damek,liczba_czarnych_damek);
	goto control_panel;


	//tryb dla dwoch graczy
	multi_player:
	odswiezenie_grafika(pole,figura,gracz_1.nr_gracza,przyciski);
	zmienna_steruj¹ca=2;
	while (!wyjscie)
	{
		if (!wyjscie)
		{
		wyjscie =tura(gracz_1, gracz_2,pole,figura,kolejka, liczba_bialych, liczba_czarnych, liczba_bialych_damek, liczba_czarnych_damek, zmienna_steruj¹ca, przyciski);
		if (wyjscie == false)
		{
			wyjscie=czy_koniec(liczba_bialych,liczba_czarnych, liczba_bialych_damek, liczba_czarnych_damek,okno,wyjscie);
		}
		}
		if (!wyjscie)
		{
		 wyjscie = tura(gracz_2, gracz_1,pole,figura,kolejka, liczba_bialych, liczba_czarnych, liczba_bialych_damek, liczba_czarnych_damek, zmienna_steruj¹ca, przyciski);
		 if (wyjscie == false)
		{
			wyjscie=czy_koniec(liczba_bialych,liczba_czarnych, liczba_bialych_damek, liczba_czarnych_damek,okno,wyjscie);
		}
		 //wyjscie=false;
		}
	}
	wyjscie = false;
	goto control_panel;


	// tryb internetowy
	online_game:
	goto control_panel;


	// opcje gry
	options:
	goto control_panel;


	// z gry
	the_end:
	al_rest(1.0);


    return 0;
}
 