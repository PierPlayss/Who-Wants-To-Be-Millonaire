#pragma once
//SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL_syswm.h>
#include <Windows.h>

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
#include "logic.h"

//OpenCV
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

string QuestionFont = { "res/fonts/kanit.otf" };

int SetMouseX, SetMouseY;
void mouseHandler(int event, int x, int y, int flags, void* userdata);
void SetMousePos(int x, int y) {
	SetMouseX = x;
	//cout << "x: " << SetMouseX << endl;
	SetMouseY = y;
	//cout << "y: " << SetMouseY << endl;
}
void onMouse(int event, int x, int y, int flags, void* params) {
	Mat* image = reinterpret_cast<Mat*>(params);
	switch (event) {
	case EVENT_LBUTTONDOWN: {
		int pixelvalue = static_cast<int>(image->at<uchar>(Point(x, y)));
		//cout << "The pixel value is x:" << x << " y:" << y << " . " << pixelvalue << endl;
		SetMousePos(x, y);
	}break;

	}

}



void questionanimation(SDL_Texture* questionTexture, SDL_Texture* optionsTexture, RenderWindow window, string pregunta, string respuestas[4], int respuestacorrecta, SDL2SoundEffects se, Mix_Music* bgm) {

	const int FPS = 60;
	int refreshRate = 1000 / FPS;
	int frame = 0;

	SDL_Event event;
	int clicks = 0;
	bool over = false;
	int mouseX, mouseY;


	//variables
	int optionsopacity = 0;
	int questionopacity = 0;
	int opacidadpregunta = 0;
	int opacidadcomodin[3] = { 0,0,0 };
	int cincuentaActivado = false;
	int opcionesRandom[4] = {0,0,0,0};
	int contadorRandom = 0;
	int randomTemp;

	respuestacorrecta = respuestacorrecta - 1;

	string letras[4]{ "A:","B:","C:","D:" };
	bool startQuestion = false;
	

	bool opcion[4] = { 0,0,0,0 };
	int contador = 0;
	int contador2 = 0;
	int contador3 = 0;
	int clicked = -1;
	int clicked2 = -1;
	bool locked = false;
	bool answered = false;
	

	float tamaño1 = 1;
	float tamaño2 = 1;
	bool end1 = false;
	bool end2 = false;
	

	//Texturas 
	SDL_Texture* lockedTexture = window.loadTexture("res/gfx/respuesta.png");
	SDL_Texture* correctaTexture = window.loadTexture("res/gfx/correcta.png");
	SDL_Texture* incorrectaTexture = window.loadTexture("res/gfx/incorrecta.png");

	SDL_Texture* comodin1Texture = window.loadTexture("res/gfx/comodin1.png");


	//Entidades
	Entity questionE(10, 0, 1920, 1080, questionTexture);
	Entity optionsE(10, 0, 1920, 1080, optionsTexture);
	
	Entity correct(0, 0, 1920, 1080, correctaTexture);
	Entity incorrect(0, 0, 1920, 1080, incorrectaTexture);

	Entity comodinCincuenta(590,575,99,53,comodin1Texture);


	//OpenCV

	Mat Settings(300, 200, CV_8UC3, Scalar(238, 238, 238));
	Mat reset(300, 200, CV_8UC3, Scalar(238, 238, 238));
	int buttons[3] = { 0,0,0 };

	bool cincuentacincuenta = false;
	bool llamada = false;
	bool publico = false;

	//Botones

	Mat comodin1 = imread("res/gfx/5050.png");
	//resize(comodin1, comodin1, Size(), 0.7, 0.7);
	
	//Music
	Mix_PlayMusic(bgm, -1);
	bool soundPlayed = false;

	while (!over) {

		window.RenderWindow::clear();

		//window.backgroundColor(255, 0, 255, 255);

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT) {
				over = true;
			}
			if (locked == true) {

				if (event.type == SDL_KEYDOWN) {
					if ((event.key.keysym.sym == SDLK_RETURN)) {
						//check if correct answer
						answered = true;
					}
				}
				
			}
			else {
				if (event.type == SDL_KEYDOWN) {
					if ((event.key.keysym.sym == SDLK_RETURN)) {
						if (cincuentacincuenta == true) {
						
							if (cincuentaActivado == false) {

								srand(time(NULL));
								while (contadorRandom < 2) {
									randomTemp = rand() % 4;

									if (randomTemp != respuestacorrecta and opcionesRandom[randomTemp] != 1) {
										opcionesRandom[randomTemp] = 1;
										contadorRandom++;
										cout << "randomTemp " << randomTemp << endl;
									}
								}

								cincuentaActivado = true;
								/*	for (int i = 0; i < 4; i++) {
										cout << opcionesRandom[i] << " ";

									}
									cout << endl;
									cout << contadorRandom << endl;*/
							}
						}
						
					}
				}

			}
			if (event.type == SDL_MOUSEBUTTONUP) {
				if (event.button.state == SDL_RELEASED) {
					clicks++;
					
					if (clicks == 1) {
						if (answered == true) {
							over = true;
							
						}
						if (opcion[3] == true) {
							if (mouseX > 100 and mouseX < 630 and mouseY>550 and mouseY < 600 and answered == false) {
								clicked = 0;
								clicked2 = 0;
								locked = true;
								
							}
							if (mouseX > 100 and mouseX < 630 and mouseY>615 and mouseY < 665 and answered == false) {
								clicked2 = 2;
								clicked = 1;
								locked = true;
								
							}
							if (mouseX > 645 and mouseX < 1150 and mouseY>550 and mouseY < 600 and answered == false) {
								clicked = 2;
								clicked2 = 1;
								locked = true;
								
							}
							if (mouseX > 645 and mouseX < 1150 and mouseY>615 and mouseY < 665 and answered == false) {
								clicked = 3;
								clicked2 = 3;
								locked = true;
								
							}
						}


						if (opcion[2] == true) {
							opcion[3] = true;
						}
						if (opcion[1] == true) {
							opcion[2] = true;
						}
						if (opcion[0] == true) {
							opcion[1] = true;
						}
						if (opcion[0] == false and end2 == true) {
							opcion[0] = true;
						}
						
						
						}
						clicks = 0;
					}

				
			}
			if (event.type == SDL_MOUSEMOTION) {

				mouseX = event.motion.x;
				mouseY = event.motion.y;
				//cout << mouseX << "," << mouseY << endl;

			}
			if (event.type == SDL_KEYDOWN) {
				if (locked==false and (event.key.keysym.sym == SDLK_RETURN) &&
					(event.key.keysym.mod & KMOD_ALT))
				{
					window.ToggleFullscreen();
				}
				if (event.key.keysym.sym == SDLK_ESCAPE) {
					over = true;
				}

			}
		}
		
		//Ventana OpenCv
		setMouseCallback("Settings", onMouse, reinterpret_cast<void*>(&Settings));
		
		reset.copyTo(Settings(Rect(0, 0, reset.cols, reset.rows)));

		comodin1.copyTo(Settings(Rect(25, 10, comodin1.cols, comodin1.rows)));

		if (settingsmouse(SetMouseX, SetMouseY, buttons) == true and buttons[0] == 1) {
			
			cincuentacincuenta = true;
			SetMouseX = -1;
			SetMouseY = -1;
		
		}
		if (settingsmouse(SetMouseX, SetMouseY, buttons) == true and buttons[1] == 1) {

			llamada = true;
			SetMouseX = -1;
			SetMouseY = -1;
		}
		if (settingsmouse(SetMouseX, SetMouseY, buttons) == true and buttons[2] == 1) {

			publico = true;
			SetMouseX = -1;
			SetMouseY = -1;
		}

		//Pregunta y respuestas imagen - Opacidad y animacion
		if (questionopacity < 255) {
			questionopacity += 5;
			if (questionopacity > 255) {
				questionopacity = 255;
			}
		}
		SDL_SetTextureAlphaMod(questionTexture, questionopacity);
		SDL_SetTextureAlphaMod(optionsTexture, questionopacity);





		if (tamaño1 >= 0.68) {
			tamaño1 -= 0.02;
			if (tamaño1 <= 0.66) {
				tamaño1 = 0.66;

			}
		}

		if (tamaño1 < 0.75) {
			end1 = true;
		}
		

		if (end1 == true) {

			if (tamaño2 > (0.66)) {
				tamaño2 -= 0.01;

			}
		}
		
		if (tamaño2 < 0.70) {
			end2 = true;
		}


		window.renderCenter(questionE, tamaño1, 0, 0);
		window.renderCenter(optionsE, tamaño2, 0, 0);

		////////////////////////////////////////////////

		//Detector comodin
		
		
		if (cincuentacincuenta == true) {
			if (cincuentaActivado == false) {
				locked = false;

			}
		}


		//Pregunta string y opciones
		if (locked == true and answered == false) {
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < 2; j++) {
					if (contador2 == clicked) {
						Entity locked(0 + (560 * i), 0 + (60 * j), 1280, 720, lockedTexture);
						window.render(locked, 0.99);
					}
					contador2++;
				}
			}

		}
	
	
		//Mostrar respuestas

		if (answered == true) {
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < 2; j++) {

					if (clicked2 != respuestacorrecta) {
						if (contador3 == clicked) {
							Entity incorrect(0 + (560 * i), 0 + (60 * j), 1280, 720, incorrectaTexture);
							window.render(incorrect, 0.99);
							if (soundPlayed == false) {
								Mix_PauseMusic();
								se.playSoundEffect(3);
								soundPlayed = true;
							}
							
						}
					}
					if (contador3 == respuestacorrecta) {
						Entity correct(0 + (560 * i), 0 + (60 * j), 1280, 720, correctaTexture);
						window.render(correct, 0.99);
						if (soundPlayed == false) {
							Mix_PauseMusic();
							se.playSoundEffect(0);
							soundPlayed = true;
						}
					}

					contador3++;
				}
				
			}
		
		}

		if (end2==true and opacidadpregunta < 255) {
			opacidadpregunta += 15;
		}
		if (end2 == true) {
			if (opacidadpregunta > 50) {
				window.textCustom(pregunta.c_str(), QuestionFont, 0, 0, 30, 30, 30, opacidadpregunta - 50, 30, 1, 3, 132);
			}
			window.textCustom(pregunta.c_str(), QuestionFont, 0, 0, 255, 255, 255, opacidadpregunta, 30, 1, 0, 130);
			
		}

		//Respuestas

		for (int i = 0; i < 2;i++) {
			for (int j = 0; j < 2; j++) {
				if (opcion[contador] == true and opcionesRandom[contador]==0) {
					if (locked == true and clicked2 == contador and answered==false) {
						window.drawText(letras[contador].c_str(), 130 + (540 * j), 550 + (58 * i), 1, 1, 1, 255, 30);
						window.drawText(respuestas[contador].c_str(), 161 + (540 * j), 551 + (58 * i), 1, 1, 1, 255, 30);
					}
					else {
						window.drawText(letras[contador].c_str(), 130 + (540 * j), 550 + (58 * i), 234, 167, 2, 255, 30);
						window.drawText(respuestas[contador].c_str(), 161 + (540 * j), 551 + (58 * i), 20, 20, 20, 230, 30);
						window.drawText(respuestas[contador].c_str(), 160 + (540 * j), 550 + (58 * i), 255, 255, 255, 255, 30);
					}
					
				}
				contador++;
			}
			
		}
		
		//Comodines
		if (cincuentacincuenta == true) {
			if (opacidadcomodin[0] < 255) {
				opacidadcomodin[0] += 5;
				if (opacidadcomodin[0] > 255) {
					opacidadcomodin[0] = 255;
				}
			}
			SDL_SetTextureAlphaMod(comodin1Texture, opacidadcomodin[0]);
			window.render(comodinCincuenta, 1);

		}

		

	

		contador = 0;
		contador2 = 0;
		contador3 = 0;
		
		//window.MakeWindowTransparent(RGB(0, 0, 0));

		window.display();
		imshow("Settings", Settings);

		Sleep(refreshRate);
		if (frame == FPS) {
			frame = 0;
		}
		else frame++;
	}

	SDL_DestroyTexture(correctaTexture);
	SDL_DestroyTexture(lockedTexture);
	SDL_DestroyTexture(incorrectaTexture);
}


void mouseHandler(int event, int x, int y, int flags, void* userdata)
{
	cout << "\n-- event: " << event << endl;
	cout << "mouse position: (" << x << ", " << y << ")" << endl;
	cout << "flags: " << flags << endl;

	//Simple events comparison
	if (event == EVENT_LBUTTONDOWN) { cout << "Left button of the mouse is clicked" << endl; }
	else if (event == EVENT_RBUTTONDOWN) { cout << "Right button of the mouse is clicked" << endl; }
	else if (event == EVENT_MBUTTONDOWN) { cout << "Middle button of the mouse is clicked" << endl; }
	else if (event == EVENT_MOUSEMOVE) { cout << "Mouse move over the window" << endl; }

	//Comparisons using the 'flags' argument. Note: flags = event_flag + another event_flag
	if (flags == (EVENT_FLAG_CTRLKEY + EVENT_FLAG_LBUTTON))
	{
		cout << "Left mouse button is clicked while pressing CTRL key" << endl;
	}
	else if (flags == (EVENT_FLAG_SHIFTKEY + EVENT_FLAG_RBUTTON))
	{
		cout << "Right mouse button is clicked while pressing SHIFT key" << endl;
	}
	else if (flags == (EVENT_FLAG_SHIFTKEY + EVENT_FLAG_CTRLKEY + EVENT_FLAG_ALTKEY))
	{
		cout << "SHIFT, CTRL and ALT keys are pressed" << endl; //To execute, move your mouse
	}
	else if (event == EVENT_MOUSEMOVE && flags == EVENT_FLAG_ALTKEY) //ALT is a particular case
	{//For the ALT KEY, AND operation is nedeed with the event
		cout << "Mouse is moved over the window while pressing ALT key" << endl;
	}
}