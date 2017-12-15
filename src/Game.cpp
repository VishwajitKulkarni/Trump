///\file
#include "Game.h"
#include "CardTexManager.h"
#include <vector>
#include <string.h>
#include <SDL2/SDL_mixer.h>

std::vector<Cards*> player;
Cards* card1;
Cards* PL;
Cards* PU;
Cards* PR;
SDL_Renderer* Game::renderer = NULL;

static const char *backgroundSound = "assets/background.mp3";
int Count;
Game::Game() {
	card1 = NULL;
	PL = NULL;
	PU = NULL;
	PR = NULL;
	suitsDisplay.x = SCREEN_WIDTH / 2 - 200;
	suitsDisplay.y = 400;
	suitsDisplay.h = 100;
	suitsDisplay.w = 400;
	text.x = SCREEN_WIDTH / 2 - 200;
	text.y = 300;
	text.h = 100;
	text.w = 400;
	Trump = '0';
	ip_font = NULL;
	ip_string = "Enter IP address:  ";
	playedSuit = '0';
	playedCard = 0;
	myTurn = NULL;
	Trump = '0';
	isRunning = NULL;
	window = NULL;
	ip_surface = NULL;
	ip_texture = NULL;
	ip_color.r = 255;
	ip_color.g = 255;
	ip_color.b = 255;
	ip_color.a = 255;
	surface = NULL;
	backgroundtex = NULL;
	suitSelectTex = NULL;
	TrumpTex = NULL;
	TrumpSuitTex = NULL;
	textTex = NULL;
	ip = false;
	Takebutton = false;
	TakeTrump = false;
	showTrump = false;
	PlayerLeft = false;
	PlayerUp = false;
	PlayerRight = false;
	scoreTeamA = '0';
	scoreTeamB = '0';
	TeamATex = NULL;
	TeamBTex = NULL;
	TeamA = "Score Team A:  x";
	TeamB = "Score Team B:  x";
}

Game::~Game() {

}

void Game::init(int xpos, int ypos, int width, int height) {
	int flags = SDL_WINDOW_SHOWN;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		window = SDL_CreateWindow("Trump", xpos, ypos, width, height, flags);
		if (window) {
			std::cout << "window created" << std::endl;
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			//SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
			backgroundtex = CardTexManager::LoadTexture("assets/test.png");
			suitSelectTex = CardTexManager::LoadTexture("assets/suit.png");
			textTex = CardTexManager::LoadTexture("assets/text.png");
			SDL_FreeSurface(surface);
			std::cout << "Renderer created" << std::endl;
			TTF_Init();
			ip_font = TTF_OpenFont("assets/DejaVuSans.ttf", 50);

		}

		isRunning = true;
		Count = 0;
	} else {
		isRunning = false;
	}

	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
	Mix_Music *music = Mix_LoadMUS(backgroundSound);
	Mix_PlayMusic(music, 1);

}

bool Game::handleEvent() {
	int mousex, mousey;
	SDL_Event event;
	SDL_PollEvent(&event);
	if (event.type == SDL_QUIT) {
		isRunning = false;
		return false;
	} else if (event.type == SDL_MOUSEBUTTONDOWN && Takebutton) {
		if (event.button.button == SDL_BUTTON_LEFT) {
			mousex = event.button.x;
			mousey = event.button.y;
			button(mousex, mousey);
		}
	} else if (event.type == SDL_MOUSEBUTTONDOWN && TakeTrump) {
		if (event.button.button == SDL_BUTTON_LEFT) {
			mousex = event.button.x;
			mousey = event.button.y;
			selectTrumpButton(mousex, mousey);
		}
	} else if ((event.type == SDL_TEXTINPUT || event.type == SDL_KEYDOWN)
			&& ip) {
		if (event.key.keysym.sym == SDLK_PERIOD
				|| event.key.keysym.sym == SDLK_0
				|| event.key.keysym.sym == SDLK_1
				|| event.key.keysym.sym == SDLK_2
				|| event.key.keysym.sym == SDLK_3
				|| event.key.keysym.sym == SDLK_4
				|| event.key.keysym.sym == SDLK_5
				|| event.key.keysym.sym == SDLK_6
				|| event.key.keysym.sym == SDLK_7
				|| event.key.keysym.sym == SDLK_8
				|| event.key.keysym.sym == SDLK_9) {
			ip_string += SDL_GetScancodeName(event.key.keysym.scancode);
		} else if (event.key.keysym.sym == SDLK_BACKSPACE
				&& ip_string.length() > 19) {
			ip_string = ip_string.substr(0, ip_string.length() - 1);
		} else if (event.key.keysym.sym == SDLK_RETURN) {
			return false;
		}
	}
	return true;
}

void Game::RenderIP() {
	int w = 0, h = 0;
	ip_surface = TTF_RenderText_Solid(ip_font, ip_string.c_str(), ip_color);
	ip_texture = SDL_CreateTextureFromSurface(renderer, ip_surface);
	SDL_FreeSurface(ip_surface);
	SDL_QueryTexture(ip_texture, NULL, NULL, &w, &h);
	ip_Rect.x = 0;
	ip_Rect.y = 0;
	ip_Rect.w = w;
	ip_Rect.h = 100;
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, backgroundtex, NULL, NULL);
	SDL_RenderCopy(renderer, ip_texture, NULL, &ip_Rect);
	SDL_RenderPresent(renderer);

}

void Game::Renderer() {
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, backgroundtex, NULL, NULL);

	for (int var = 0; var < player.size(); var++) {
		if (player[var]->isIsActive()) {
			player[var]->Render();
		}
	}
	if (TakeTrump) {
		SDL_RenderCopy(renderer, suitSelectTex, NULL, &suitsDisplay);
		SDL_RenderCopy(renderer, textTex, NULL, &text);
	}
	if (showTrump) {
		SDL_RenderCopy(renderer, TrumpTex, NULL, &TrumpText);
		SDL_RenderCopy(renderer, TrumpSuitTex, NULL, &TrumpSuit);
	}
	if (PlayerLeft) {
		PL->Render();
	}
	if (PlayerUp) {
		PU->Render();
	}
	if (PlayerRight) {
		PR->Render();
	}
	SDL_RenderPresent(renderer);
}

void Game::Load5Cards() {
	bool a[13] = { true, true, true, false, false, false, false, false, false,
			false, false, true, true };
	for (int var = 0; var < player.size(); var++) {
		player[var]->setIsActive(a[var]);
	}

}

void Game::loadAllCards() {
	bool a[13] = { true, true, true, true, true, true, true, true, true, true,
			true, true, true };
	for (int var = 0; var < player.size(); var++) {
		player[var]->setIsActive(a[var]);
	}

}

void Game::load(std::string file, char s, int num) {
	if (Count <= 6) {
		card1 = new Cards(file.c_str(), (SCREEN_WIDTH - 75) / 2 + (Count * 85),
				550, s, num, true);
		player.push_back(card1);
	} else if (Count > 6 && Count < 13) {
		card1 = new Cards(file.c_str(),
				(SCREEN_WIDTH - 75) / 2 - ((13 - Count) * 85), 550, s, num,
				true);
		player.push_back(card1);
	}
	Count++;

}

void Game::button(int x, int y) {
	for (int var = 0; var < player.size(); var++) {
		if ((((x > player[var]->getXpos())
				&& (x < player[var]->getXpos() + player[var]->getDestRw()))
				&& ((y > player[var]->getYpos())
						&& (y
								< player[var]->getYpos()
										+ player[var]->getDestRh())))
				&& player[var]->isActive) {

			playedSuit = player[var]->suit;
			playedCard = player[var]->num;
			player[var]->setIsActive(false);
			myTurn = false;
			Count = var;
		}
	}

}
void Game::playerMove() {

	player[Count]->setXpos(550);
	player[Count]->setYpos(350);
}

void Game::selectTrumpButton(int x, int y) {

	if ((x > 440) && (x < 540) && (y > 400) && (y < 500)) {
		Trump = 'D';
		TakeTrump = false;

	} else if ((x > 540) && (x < 640) && (y > 400) && (y < 500)) {
		Trump = 'S';
		TakeTrump = false;

	} else if ((x > 640) && (x < 740) && (y > 400) && (y < 500)) {
		Trump = 'H';
		TakeTrump = false;

	} else if ((x > 740) && (x < 840) && (y > 400) && (y < 500)) {
		Trump = 'C';
		TakeTrump = false;

	}

}

void Game::LoadPL(std::string fileName, char s, int n) {
	PL = new Cards(fileName.c_str(), 80, 300, s, n, true);
	PlayerLeft = true;
}

void Game::LoadPU(std::string fileName, char s, int n) {
	PU = new Cards(fileName.c_str(), 550, 100, s, n, true);
	PlayerUp = true;

}

void Game::LoadPR(std::string fileName, char s, int n) {
	PR = new Cards(fileName.c_str(), 1030, 300, s, n, true);
	PlayerRight = true;
}

void Game::trumpTex(std::string fileName) {
	TrumpTex = CardTexManager::LoadTexture("assets/trump.png");
	TrumpText.x = 10;
	TrumpText.y = 0;
	TrumpText.w = 150;
	TrumpText.h = 75;
	TrumpSuitTex = CardTexManager::LoadTexture(fileName.c_str());
	TrumpSuit.x = 45;
	TrumpSuit.y = 75;
	TrumpSuit.w = 80;
	TrumpSuit.h = 80;

}

/*void Game::score(char a, char b) {
	TeamA[15] = a;
	TeamB[15] = b;
	surface = TTF_RenderText_Solid(ip_font, TeamA.c_str(), ip_color);
	TeamATex = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	surface = TTF_RenderText_Solid(ip_font, TeamB.c_str(), ip_color);
	TeamBTex = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	SDL_QueryTexture(ip_texture, NULL, NULL, &w, &h);
		ip_Rect.x = 0;
		ip_Rect.y = 0;
		ip_Rect.w = w;
		ip_Rect.h = 100;
}
*/
void Game::update() {
	for (int var = 0; var < player.size(); var++) {
		player[var]->update();
	}

}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	Mix_CloseAudio();
	TTF_CloseFont(ip_font);
	SDL_Quit();
	std::cout << "Game cleaned" << std::endl;

}
