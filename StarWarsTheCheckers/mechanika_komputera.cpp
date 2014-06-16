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
#include "inicjacja.h"
#include "mechanika_gracza.h"
#include "mechanika_komputera.h"



// zmienna liczaca ruchy
int licznik;

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


// algorytm minmax - ulepszona wersja
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


// nowa wersja tury gracza sztucznej inteligencji
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