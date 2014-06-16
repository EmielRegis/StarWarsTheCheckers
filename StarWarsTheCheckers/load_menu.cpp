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
#include"operacje_na_plikach.h"
#include"sturktury.h"
#include"load_menu.h"

// rysowanie menu load
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


// obsluga menu load
int load_window (Gracz_s gracz1, Gracz_s gracz2, Pole_s **szachownica, Pion_s *pion, int &biale_pionki, int &czarne_pionki, int &biale_damki, int &czarne_damki,
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
				//cout << endl <<strpom1 <<endl;
				//cout << endl <<strpom1.length() <<endl;
				char *str3;
				str3 = (char*)malloc(strpom1.length()*sizeof(char)+1);
				strpom1.copy(str3,strpom1.length(),0);
				str3[strpom1.length()]='\0';
				//cout<<str3<<"|";
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