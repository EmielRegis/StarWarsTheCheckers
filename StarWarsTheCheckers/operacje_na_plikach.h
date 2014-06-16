#ifndef operacje_na_plikach_h
#define operacje_na_plikach_h

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


//tworzenie pliku konfiguracyjnego
void config_file();

//zapisywanie stanu gry
void save_game (int licznik, char *slowo, Gracz_s gracz1, Gracz_s gracz2, Pole_s **szachownica, Pion_s *pion, int sterujaca, int biale_pionki, int czarne_pionki, int biale_damki, int czarne_damki);

void load_game (char *nazzwa,Gracz_s gracz1, Gracz_s gracz2, Pole_s **szachownica, Pion_s *pion, int sterujaca, int biale_pionki, int czarne_pionki, int biale_damki, int czarne_damki);

#endif