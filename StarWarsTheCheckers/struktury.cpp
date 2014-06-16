
//using namespace std;
//#define _CRT_SECURE_NO_WARNINGS
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
#include "sturktury.h"



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

// nowe kopiowanie
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