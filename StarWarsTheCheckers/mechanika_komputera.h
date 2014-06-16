#ifndef mechanika_kumputera_h
#define mechanika_komputera_h

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

// sprawdzenie - preksztalcenie w damke
void ai_czy_damka (Gracz_s gracz, ai_Pole_s **pola, ai_Pion_s *pion, int c);

//sprawdzenie
bool ai_czy_bicie_rek_pion (Gracz_s gracz, ai_Pole_s **poles, ai_Pion_s *piony, int c);

// dla komputera sprawdza, czy dla danego gracza mozliwe jest wykonanie bicia
bool ai_czy_bicie (ai_Pole_s **poles, ai_Pion_s *piony, Gracz_s gracz, stack <int> &stos);

// bicie komputerowe
bool ai_bicie (ai_Pole_s **szachownica, ai_Pion_s *piony, Gracz_s gracz, int x, int y, int c );

// dla komputera sprawdza, czy dla danego gracza mozliwe jest wykonanie ruchu
bool ai_czy_ruch (ai_Pole_s **poles, ai_Pion_s *piony, Gracz_s gracz, stack <int> &stos);

// komputerowe wykonanie ruchu
bool ai_ruch(ai_Pole_s **szachownica, ai_Pion_s *piony, Gracz_s gracz, int x, int y, int c );

// ewaluacja min-maxowa
int ewaluacja (ai_Pion_s *pion, Gracz_s gracz);

// algorytm minmax
int min_max(int depth, int maxdepth, ai_Pole_s **szachownica, ai_Pion_s *pion, Gracz_s gracz, bool cb, int xx,int yy,int cc);

// tura gracza komputerowego
bool tura_komputer(Pole_s **szachownica, Pion_s *pion, Gracz_s gracz, int &biale_pionki, int &czarne_pionki, int &biale_damki, int &czarne_damki, ALLEGRO_BITMAP **guziki);

// ewaluacja min-maxowa 2
int ewaluacja2 (ai_Pion_s *pion, Gracz_s gracz);

// algorytm minmax - ulepszona wersja
decyzja minmax2 (int depth, int maxdepth, ai_Pole_s **szachownica, ai_Pion_s *pion, Gracz_s gracz, int x,int y,int c);

// nowa wersja tury gracza sztucznej inteligencji
bool tura_kompa2 (Pole_s **polka, Pion_s *pionki, Gracz_s gracz, int &biale_pionki, int &czarne_pionki, int &biale_damki, int &czarne_damki, ALLEGRO_BITMAP **guziki);






#endif