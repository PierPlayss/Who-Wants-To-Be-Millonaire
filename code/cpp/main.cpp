//SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

//C++
#include <iostream>
#include <vector>
#include <sstream>
#include <Windows.h>
#include <fstream>
#include <string>
//Headers
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "SDL2SoundEffects.h"



#include "animation.h"
#include "QuestionAnimation.h"

using namespace std;


RenderWindow window("Who wants to be a millonaire", 1280, 720);
//RenderWindow gamesWindow("Games Window", 1000, 500);

const int FPS = 60;
int refreshRate = 1000 / FPS;
int frame = 0;


//variables
int optionsopacity = 0 ;
int questionopacity = 0 ;


float tamaño1 = 1;
float tamaño2 = 1;
bool end1 = false;

//////////////////////////////
  //CANTIDAD DE PREGUNTAS//

const int cantidadpreguntas = 3;

/// /////////////////////////

string preguntas[cantidadpreguntas];
string respuestas[cantidadpreguntas][4];
string tempResp[4];
string respuestaCorrectaString;
int respuestaCorrecta[cantidadpreguntas];




int main(int argc, char* argv[]) {

	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << endl;

	if (!(IMG_Init(IMG_INIT_PNG)))
		cout << "IMG_init has failed. Error: " << SDL_GetError() << endl;

	if (TTF_Init() == -1) {
		cout << "TTF_init has failed. Error: " << SDL_GetError() << endl;
	}
	int mouseX, mouseY;
	int clicks = 0;
	int clickMenu = 0;

	//Sounds
	//SDL2SoundEffects se;
	//se.addSoundEffect("res/sound/memory/pink.mp3");//0


	//Mix_Music* bgm = Mix_LoadMUS("res/sound/music.mp3");
	//se.addSoundEffect("res/sound/strike.mp3"); //0


	//Textures 
	SDL_Texture* questionTexture = window.loadTexture("res/gfx/question.png");
	SDL_Texture* optionsTexture = window.loadTexture("res/gfx/options.png");

	//BG and Logo
	SDL_Texture* bgTexture = window.loadTexture("res/gfx/bg.png");
	SDL_Texture* logoTexture = window.loadTexture("res/gfx/logo.png");
	SDL_Texture* FSTexture = window.loadTexture("res/gfx/firstscreen.png");

	SDL_SetTextureAlphaMod(FSTexture, 150);


	//Entities
	Entity bgEntity(0, 0, 1280, 720, bgTexture);
	Entity logoEntity(0, 0, 394, 394, logoTexture);
	Entity lineas(-20,-280, 1280, 1280, FSTexture);


	//Music and Effects
	SDL2SoundEffects se;
	se.addSoundEffect("res/sound/correct.mp3"); //0
	se.addSoundEffect("res/sound/music.mp3"); //1
	se.addSoundEffect("res/sound/questionStart.mp3"); //2
	se.addSoundEffect("res/sound/wrong.mp3"); //3
	Mix_Music* bgm = Mix_LoadMUS("res/sound/questionMusic.mp3");

	SDL_Event event;
	SDL_Event mouseEvent{ SDL_MOUSEMOTION };
	
	bool gameRunning = true;
	//Menu 
	int contador = 0;
	bool start = false;
	bool stop = false;
	bool toggleMenu = false;
	int intmenu = 0;
	int ended = 0;

	//Variables
	float angle = 0;

	//Leer preguntas y respuestas
	fstream txt;
	stringstream ans;
	txt.open("game.txt");
	for (int i = 0; i < cantidadpreguntas; i++) {
		getline(txt, preguntas[i]);
		for (int j = 0; j < 4; j++) {
			getline(txt, respuestas[i][j]);
		}
		getline(txt, respuestaCorrectaString);
		ans.clear();
		ans << respuestaCorrectaString;
		ans >> respuestaCorrecta[i];
			
	}
	txt.close();
	
	se.playSoundEffect(1);

	srand(time(NULL));
	while (gameRunning)
	{	
		
		int aux = 0;
		bool rendered = true;
		window.RenderWindow::clear();
		// Get our controls and events
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				gameRunning = false;
			if (event.type == SDL_MOUSEMOTION) {

				mouseX = event.motion.x;
				mouseY = event.motion.y;
				//cout << mouseX << "," << mouseY << endl;
				
			}
			if (event.type == SDL_MOUSEBUTTONUP) {
				if (event.button.state == SDL_RELEASED) {
					
					SDL_Delay(20);
					clicks++;
					clickMenu++;
					if (clicks == 1) {
						if (toggleMenu == false) {
							if (start == false) {
								start = true;
							}
							else {
								stop = true;
							}
						}
						clicks = 0;
					}
					
				}
			}
			
			if (event.type == SDL_KEYDOWN) {
				if ((event.key.keysym.sym == SDLK_RETURN) &&
					(event.key.keysym.mod & KMOD_ALT))
				{
					window.ToggleFullscreen(); 
				}
				if (event.key.keysym.sym == SDLK_ESCAPE) {
					if (toggleMenu == false) {
						toggleMenu = true;
					}
					else toggleMenu = false;
				}
				
			}
		}
		
		

		if (start == true) {
			for (int i = 0; i < cantidadpreguntas; i++) {
				for (int j = 0; j < 4; j++) {
					tempResp[j] = respuestas[i][j];
				}
				questionanimation(questionTexture, optionsTexture, window,preguntas[i],tempResp,respuestaCorrecta[i],se,bgm);
			}
			start = false;
		}
	
		angle += 0.5;
		if (angle >= 360) {
			angle = 0;
		}

		//window.backgroundColor(100, 100, 100, 100);
		window.render(bgEntity, 1);
		window.renderFlip(lineas, angle, 1, 0);
		window.renderCenter(logoEntity, 1, 0, 0);

		window.display();
		


		Sleep(refreshRate);
		if (frame == FPS) {
			frame = 0;
		}
		else frame++;

	}
	
	window.cleanUp();
	SDL_Quit();
	TTF_Quit();

	return 0;
}

