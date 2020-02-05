#include "functions.h"

void handleMenu(Event event, RenderWindow *window, button play, button settings, button exit, int &stage, Background mainmenu) {
	if (event.type == event.MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			if (play.isPressed({ (float)event.mouseButton.x, (float)event.mouseButton.y })) {
				stage = 1;
			}
	//		else if (settings.isPressed({ (float)event.mouseButton.x, (float)event.mouseButton.y })) {
	//			stage = 5;
	//		}
			else if (exit.isPressed({ (float)event.mouseButton.x, (float)event.mouseButton.y })) {
				window->close();
			}
		}
	}


	window->clear();
	mainmenu.drawTo(window);
	play.drawTo(window);
//	settings.drawTo(window);
	exit.drawTo(window);
	window->display();
}

void handlePausedMenu(RectangleShape *shelf, Sprite *heal, Texture *heal_, button *resume, button *shop, RenderWindow *window, Event *event, bool &paused, int &stage, bool &inShop, int &scoreMultpl) {
	
	if (paused == true) {
		resume->drawTo(window);
		shop->drawTo(window);
		if (event->type == event->MouseButtonPressed) {
			if (event->mouseButton.button == sf::Mouse::Left) {
				if (resume->isPressed({ (float)event->mouseButton.x, (float)event->mouseButton.y })) {
					paused = false;
					inShop = false;
				}
				else if (shop->isPressed({ (float)event->mouseButton.x, (float)event->mouseButton.y })) {
					if (inShop == false) {
						std::cout << "LET'S SHOP\n";
						
						inShop = true;
						//	stage = 6; //SHOP STAGE 
					}
				}
			}
		}
	}
}

void handleShop(Sound *sound, RectangleShape *shelf, Sprite *heal, Texture *heal_, RenderWindow *window, Event *event, int &scoreMultpl, int &gold_, Player *ship, float &HPbar_, RectangleShape *HPbar, Texture Hp[], text *mltpl, text *goldmltpl, int &glmltpl) {

	if (event->type == event->MouseButtonReleased) {
		if (event->mouseButton.button == sf::Mouse::Left) {
			std::cout << "MOUSEPRESSSSED\n";
			if (heal->getGlobalBounds().contains({ (float)event->mouseButton.x, (float)event->mouseButton.y })) {
				if (gold_ >= 20) {
					if (ship->getHP() != ship->getHPmax()) {
						sound->play();
						ship->healMax();
						gold_ -= 20;
						std::cout << "HEALED\n";
							HPbar_ = 10 -  10;
							HPbar->setTexture(&Hp[(int)HPbar_]);
					//	HPbar--setSize({ 210.f, 25.1f });
					}
					else
						std::cout << "FULL HP\n";
				}
				else std::cout << "INSUFFICIENT BALANCE\n";
			}
			else if (mltpl->getBounds().contains({ (float)event->mouseButton.x, (float)event->mouseButton.y }))
			{
				if (gold_ >= 20*scoreMultpl) {
					sound->play();
					mltpl->setStr("2X SCORE\nMULTIPLIER\n" + std::to_string(20 * scoreMultpl) + " GOLD");
					scoreMultpl *= 2;
					std::cout << "SCORE MULTIPLIER PURCHASED " <<scoreMultpl << std::endl;
					gold_ -= 20*scoreMultpl;
					mltpl->drawTo(window);	
				}
				else std::cout << "INSUFFICIENT BALANCE\n";
			}
			else if (goldmltpl->getBounds().contains({ (float)event->mouseButton.x, (float)event->mouseButton.y }))
			{
				if (gold_ >= 20 * glmltpl) {
					sound->play();
					goldmltpl->setStr("2X GOLD\nMULTIPLIER\n" + std::to_string(20 * glmltpl) + " GOLD");
					glmltpl *= 2;
					std::cout << "GOLD MULTIPLIER PURCHASED " << scoreMultpl << std::endl;
					gold_ -= 20 * glmltpl;
					
				}
				else std::cout << "INSUFFICIENT BALANCE\n";
			}
			//		else if (shop->isPressed({ (float)event->mouseButton.x, (float)event->mouseButton.y })) {
		//
			//			}
		}
		
	}
}



void isCollidingWindow(Player *ship, RenderWindow *window) {
	if (ship->getPos().x <= 0)
		ship->setPos(0.f, ship->getPos().y);
	//Right
	if (ship->getPos().x >= window->getSize().x - ship->getBounds().width)
		ship->setPos(window->getSize().x - ship->getBounds().width, ship->getPos().y);
	//Up
	if (ship->getPos().y <= 0)
		ship->setPos(ship->getPos().x, 0.f);
	//Down
	if (ship->getPos().y >= window->getSize().y - ship->getBounds().height)
		ship->setPos(ship->getPos().x, window->getSize().y - ship->getBounds().height);
}


void createBullets(Sound *doubleShot, Sound *tripleShot, Sound *singleShot, Player *ship, int &shootDelay, int shootDelay_, Texture *bulletText) {
	if ((Keyboard::isKeyPressed(Keyboard::Space) || Mouse::isButtonPressed(Mouse::Left)) && shootDelay >= shootDelay_) {
		if (ship->getLvl() <= 2) {
			singleShot->play();
			ship->bullets.push_back(Bullet(bulletText, { ship->getPos().x  , ship->getPos().y - 15 },10));		//SHOOTING LVL 1
		}
		else if (ship->getLvl() == 3) {
			doubleShot->play();
			ship->bullets.push_back(Bullet(bulletText, { ship->getPos().x + 5, ship->getPos().y  }, 10));     //SHOOTING LVL 2
			
			ship->bullets.push_back(Bullet(bulletText, { ship->getPos().x - 5 , ship->getPos().y  }, 10));
		}
		else if (ship->getLvl() >= 4) {
			tripleShot->play();
			ship->bullets.push_back(Bullet(bulletText, { ship->getPos().x  , ship->getPos().y - 15 }, 10));		//SHOOTING LVL 3
			ship->bullets.push_back(Bullet(bulletText, { ship->getPos().x + 5, ship->getPos().y }, 10));
			ship->bullets.push_back(Bullet(bulletText, { ship->getPos().x - 5 , ship->getPos().y }, 10));
		}
		//else if(ship->buffed){ 
		shootDelay = 0;
	}
}

void handleEnemies(std::vector<Explosion> &explosions, sf::Texture *explosionText, sf::RectangleShape *HPbar, float &HPbar_, int &d1, int d1_, int &d2, int d2_, std::vector<Boss>& bosses, int &bossType, bool &anyBoss, Player *ship, int &enemySpawnDelay, int enemySpawnDelay_, std::vector<Enemy> &enemyShips, std::vector<Asteroid> &asteroids, Texture &enemyShip1, Texture &enemyShipText,  Texture &asteroidText, sf::RenderWindow *window, int asteroidSpawnDelay_, int &asteroidSpawDelay) {
	if (enemySpawnDelay < enemySpawnDelay_) {
		enemySpawnDelay++;
	}
	//enemy spawn
	if (d1 >= d1_) {
		enemyShips.push_back(Enemy(&enemyShip1, true, false, 30, Vector2f(1, 1), 2));
		d1 = 0;
	}
	if (d1 < d1_) {
		d1++;
	//	std::cout << d1 << " ";
	}
	
	if (d2 >= 2000) {
		if (ship->getLvl() <= 2) {
			for (int i = 0; i <= window->getSize().x / 72; i++) {
				asteroids.push_back(Asteroid(&asteroidText, window->getSize(), ship->getLvl(), i, 0));
			}
			
		}
		if (ship->getLvl() == 3) {
			for (int i = 0; i <= window->getSize().x / 72; i++) {
				asteroids.push_back(Asteroid(&asteroidText, window->getSize(), ship->getLvl(), i, 0));
				
				asteroids.push_back(Asteroid(&asteroidText, window->getSize(), ship->getLvl(), i, 2));
			}
		}
		if (ship->getLvl() >= 4) {
			for (int i = 0; i <= window->getSize().x / 72; i++) {
				asteroids.push_back(Asteroid(&asteroidText, window->getSize(), ship->getLvl(), i, 0));
				asteroids.push_back(Asteroid(&asteroidText, window->getSize(), ship->getLvl(), i, 1));
				asteroids.push_back(Asteroid(&asteroidText, window->getSize(), ship->getLvl(), i, 2));
			}
		}

		d2 = 0;
	}
	if (d2 < 2000) {
		d2++;
	}
	if (enemySpawnDelay >= enemySpawnDelay_)
	{
	//	if (randomNumber(20) == 5) {
	//		std::cout << "Worked\n";
	//		enemyShips.push_back(Enemy(&enemyShip1, true, false, 30, Vector2f(1, 1)));
	//	}
	//	else {
			enemyShips.push_back(Enemy(&enemyShipText, window->getSize(), ship->getLvl(), false, ship->getLvl()));
			enemySpawnDelay = 0; //reset timer
	//	}
	}
	if (asteroidSpawDelay < asteroidSpawnDelay_) {
		asteroidSpawDelay++;
		}
	if (asteroidSpawDelay >= asteroidSpawnDelay_)
	{
		asteroids.push_back(Asteroid(&asteroidText, window->getSize(), ship->getLvl()));
		asteroidSpawDelay = 0; //reset timer
	}

	//ENEMY SHIPS MOVING AND COLLIDING WITH ENEMY
	for (size_t i = 0; i < enemyShips.size(); i++)
	{
		
		if (enemyShips[i].canMove) {
			enemyShips[i].move(enemyShips[i].horisontalSpeed, enemyShips[i].getSpeed());
		}
		else enemyShips[i].move(0.f, enemyShips[i].getSpeed());
		enemyShips[i].shoot("textures/bullet.png");
		if (enemyShips[i].getPos().x >= window->getSize().x - 50) {
			enemyShips[i].horisontalSpeed = enemyShips[i].horisontalSpeed * (-1);
		}
		if (enemyShips[i].getPos().x <= 0 + enemyShips[i].getSize().x) {
			enemyShips[i].horisontalSpeed = enemyShips[i].horisontalSpeed * (-1);
		}
		if (enemyShips[i].getPos().y >= window->getSize().y + enemyShips[i].getBounds().height)
		{
			enemyShips.erase(enemyShips.begin() + i);
			break;
		}

		if (enemyShips[i].getBounds().intersects(ship->getBounds()))
		{
			explosions.push_back(Explosion(explosionText, { enemyShips[i].getPos().x - 55, enemyShips[i].getPos().y - 45 }));
			enemyShips.erase(enemyShips.begin() + i);

			ship->takeDamage(ship->getLvl()); // PLAYER TAKE DAMAGE FROM LVL 1 ENEMY NEED TO CHECK FOR ENEMIE'S LVL
			HPbar_ = 10.5;
			HPbar->setSize({ 210.f, 23.f });
			break;
		}
		
	}
	for (size_t i = 0; i < asteroids.size(); i++)
	{
		asteroids[i].move(0.f, asteroids[i].getSpeed());
	}
	//ASTEROIDS MOVING AND COLLIDING WITH PLAYER
	for (size_t i = 0; i < asteroids.size(); i++)
	{
		

		if (asteroids[i].getPos().y >= window->getSize().y + asteroids[i].getBounds().height)
		{
			asteroids.erase(asteroids.begin() + i);
			break;
		}

		if (asteroids[i].getBounds().intersects(ship->getBounds()))
		{
			asteroids.erase(asteroids.begin() + i);

			ship->takeDamage(ship->getLvl()); 
			HPbar_ = 10.5;
			HPbar->setSize({ 210.f, 23.f });
			break;
		}
	}
}

int randomNumber(int max) //RETURNS RANDOM NUMBER LESS THAN MAX 
{
	return rand() % max;
}

int randomNumber(int max, int except) //RANDOM NUMBER LESS THAN max AND EXCEPT except
{
	int random;
	random = 0;
	do {
		random = rand() % (max + 1);
	} while (random == except);
	return random;
}

void reset(int &enemySpawnDelay, int &asteroidsSpawnDelay, int &d1, int &d2, int &scoreMultpl, int &goldMultpl, std::vector<Explosion> &explosions, RenderWindow *window, Player *ship, int &scoreboard, int &gold, std::vector<Enemy>& enemyVec, std::vector<Bullet> &bulletVec, std::vector<Asteroid>& asteroidVec, float &HPbar_) {
	
	ship->resetBuffs();
	ship->resetHP();
	ship->setPos(WINDOW_SIZE_X / 2, WINDOW_SIZE_Y - ship->getSize().y);
	HPbar_ = 0;
	enemySpawnDelay = 100;
	asteroidsSpawnDelay = 50;
	d1 = 2000;
	d2 = 50000;
	scoreMultpl = 1;
	goldMultpl = 1;
	if (!enemyVec.empty()) {
		std::cout << "Enemy Vector cleared\n";
		enemyVec.clear();
	}
	if (!bulletVec.empty()) {
		std::cout << "Bullets Vector cleared\n";
		bulletVec.clear();
	}
	if (!asteroidVec.empty()) {
		std::cout << "Asteroids Vector cleared\n";
		asteroidVec.clear();
	}
	if (!explosions.empty()) {
		std::cout << "Explosions vector cleared\n";
		explosions.clear();
	}
	
	window->clear();
	window->display();
	//ADD GOLD TO TOTAL GOLD INSIDE A FILE 
	//-------------------------
	gold = 0;
	//CHECK FOR THE HIGH SCORE
	scoreboard = 0;

}

int checkHighScore() {
	int highscore;
	std::ifstream inFile;
	inFile.open("gamedata/highscore.txt");
	if (inFile.fail()) {
		std::cerr << "Error opening score file\n";
		exit(1);
	}
	inFile >> highscore;
	inFile.close();
	return highscore;
}

//IOStream
void updateHighScore(int score) {
	std::ofstream outFile;
	outFile.open("gamedata/highscore.txt");
	outFile.clear();
	outFile << score << " HIGHSCORE";
	outFile.close();
}

void updateGold(int &gold) {
	int goldExists;
	std::ifstream inFile;
	std::ofstream outFile;
	inFile.open("gamedata/gold.txt");
	if (inFile.fail()) {
		std::cerr << "Error opening score file\n";
		exit(1);
	}
	inFile >> goldExists;
	inFile.close();
	outFile.open("gamedata/gold.txt");
	goldExists = goldExists + gold;
	outFile.clear();
	outFile << goldExists << " GOLDS";
	outFile.close();
	gold = 0;
}

