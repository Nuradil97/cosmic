#pragma once
#pragma warning(disable:4996)
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "button.h"
#include "Background.h"
#include "Player.h"
#include "var.h"
#include "Enemy.h"
#include "text.h"
#include "Boss.h"
#include "Explosion.h"
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>
#include "Coin.h"

using namespace sf;

void handleMenu(Event event, RenderWindow *window, button play, button settings, button exit, int &stage, Background mainmenu);

void handleEnemies(std::vector<Explosion> &explosions, sf::Texture *explosionText, ::RectangleShape *HPbar,float &HPbar_, int &d1, int d1_, int &d2, int d2_, std::vector<Boss>& bosses, int &bossType, bool &anyBoss,Player *ship, int &enemySpawnDelay, int enemySpawnDelay_, std::vector<Enemy> &enemyShips, std::vector<Asteroid> &asteroids, Texture &enemyShip1, Texture &enemyShipText, Texture &asteroidText, sf::RenderWindow *window, int asteroidSpawnDelay_, int &asteroidSpawDelay);

void handlePausedMenu(RectangleShape *shelf, Sprite *heal, Texture *heal_, button *resume, button *shop, RenderWindow *window, Event *event, bool &paused, int &stage, bool &inShop, int &scoreMultpl );

void handleShop(Sound *sound, RectangleShape *shelf, Sprite *heal, Texture *heal_, RenderWindow *window, Event *event, int &scoreMultpl, int &gold_, Player *ship, float &HPbar_, RectangleShape *HPbar, Texture Hp[], text *mltpl, text *goldmltpl, int &glmltpl);

void isCollidingWindow(Player *ship, RenderWindow *window);

void createBullets(Sound *doubleShot,Sound *tripleShot,Sound *singleShot, Player *ship, int &shootDelay, int shootDelay_, Texture *bulletText);

int randomNumber(int max);

int randomNumber(int max, int except);

int checkHighScore();

void updateHighScore(int score);

void updateGold(int& gold);

void reset(int &enemySpawnDelay, int &asteroidsSpawnDelay, int &d1, int &d2, int &scoreMultpl, int &goldMultpl, std::vector<Explosion> &explosions, RenderWindow *window, Player *ship,int &scoreboard, int &gold, std::vector<Enemy>& enemyVec, std::vector<Bullet>& bulletVec, std::vector<Asteroid>& asteroidVec, float &HPbar_);
