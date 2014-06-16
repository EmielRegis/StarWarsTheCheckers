#ifndef mechanika_gracza_h
#define mechanika_gracza_h

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

// sprawdzenie - preksztalcenie w damke
void czy_damka(Gracz_s gracz, Pole_s **pola, Pion_s *pion, int c, int &biale_damki, int &czarne_damki, ALLEGRO_BITMAP **guziki);

// sprawdza, czy dla danego gracza mozliwe jest wykonanie bicia
bool czy_bicie (Gracz_s gracz, Pole_s **poles, Pion_s *piony);

//sprawdzenie czy dla konkretnego pionu jest jeszcze bicie
bool czy_bicie_rek_pion (Gracz_s gracz, Pole_s **poles, Pion_s *piony, int c);

// sprawdza, czy dla danego gracza mozliwe jest wykonanie ruchu
bool czy_ruch (Gracz_s gracz, Pole_s **poles, Pion_s *piony);

// podswietlenie bicia
int podswietlenie_bicia (Gracz_s gracz, Pole_s **plansza, Pion_s *pion, int x, int y);

// wykonanie bicia
bool bicie (Pole_s **szachownica, Pion_s *piony, Gracz_s gracz, int x, int y, int c, int &biale_pionki, int &czarne_pionki, int &biale_damki, int &czarne_damki, ALLEGRO_BITMAP **guziki);

// podswietlenie mozliwych ruchow do wykonania
int podswietlenie_ruchow (Gracz_s gracz, Pole_s **plansza, Pion_s *pion, int x, int y);

// wykonanie ruchu
bool ruch(Pole_s **szachownica, Pion_s *piony, Gracz_s gracz, int x, int y, int c, int &biale_damki, int &czarne_damki, ALLEGRO_BITMAP **guziki);

// tura gracza
bool tura (Gracz_s gracz, Gracz_s gracz2, Pole_s **szachownica, Pion_s *pion, ALLEGRO_EVENT_QUEUE *&kolejka, int &biale_pionki, int &czarne_pionki, int &biale_damki, int &czarne_damki, int &sterujaca, ALLEGRO_BITMAP **guziki);




#endif