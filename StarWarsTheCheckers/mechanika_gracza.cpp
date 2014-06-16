
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
#include "sturktury.h"
#include "mechanika_gracza.h"

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