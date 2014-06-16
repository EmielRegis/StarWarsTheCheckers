
using namespace std;
#define _CRT_SECURE_NO_WARNINGS
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
#include "inicjacja.h"







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