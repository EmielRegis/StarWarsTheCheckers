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
#include "operacje_na_plikach.h"

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
	//cout <<endl<< "aaaale" <<nazzwa;
	FILE *plik;
	char *nazwa = nazzwa;
	//cout<<endl<<"x"<<nazwa<<"x"<<endl;
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
