#include "functions.h"

using namespace sf;

int main() {
	srand(time(NULL));
	
	RenderWindow window(VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "Space action!", Style::Default);
	window.setFramerateLimit(60);
	//SFML INITIALIZATION
	 
		Font font;
	font.loadFromFile("fonts/AGENCYB.TTF");
		Texture playerText;
	playerText.loadFromFile("textures/Ship2.png");
		Texture bulletText;
	bulletText.loadFromFile("textures/bullet.png");
		Texture enemyShipText;
	enemyShipText.loadFromFile("textures/enemyship.png");
		Texture enemyShip1;
	enemyShip1.loadFromFile("textures/ship.png");
		Texture coinText;
	coinText.loadFromFile("textures/coin1.png");
		Texture asteroidText;
	asteroidText.loadFromFile("textures/asteroid.png");
		Texture skytext;
	skytext.loadFromFile("textures/sky.jpg");
		text gold(&font, 20, Color::Yellow, 140, 10);
		text playerHP(&font, 20, Color::Black, 15, 35);
		text enemyHP(&font, 12, Color::White, -100, -100);
		text scoreboard(&font, 20, Color::Green, 10, 10);
		text gameOver(&font, 50, Color::Red, window.getSize().x / 2 - 80, window.getSize().y / 2, "GAME OVER"); 
		text newHighScore(&font,35, Color::Cyan, (float)window.getSize().x / 2 - 100, (float)window.getSize().y / 2 - 150);
		text highScore(&font, 30, Color::Green, (float)window.getSize().x / 2 - 60, (float)window.getSize().y / 2 - 400);
	Clock clock;
	Time time_;
	//ICON
	Image icon;
	icon.loadFromFile("textures/icon.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	//SOUNDS INIT

	SoundBuffer buffer;
	SoundBuffer buffer1;
	SoundBuffer buffer2;
	SoundBuffer buffer3;
	Sound singleShot;
	buffer.loadFromFile("audio/shot.ogg");
	singleShot.setBuffer(buffer);
	Sound tripleShot;
	buffer1.loadFromFile("audio/TripleShot.ogg");
	tripleShot.setBuffer(buffer1);
	Sound doubleShot;
	buffer2.loadFromFile("audio/DoubleShot.ogg");
	doubleShot.setBuffer(buffer2);
	Sound purchase;
	buffer3.loadFromFile("audio/purchase.wav");
	purchase.setBuffer(buffer3);
	//Enemy init
	std::vector<Enemy> enemyShips;
	std::vector<Asteroid> asteroids;
	std::vector<Boss> bosses;
	std::vector<Explosion> explosions;
	std::vector<Coin> coins;
	//EXPLOSION SPRITES 
	Texture explosionText;
	explosionText.loadFromFile("textures/explosion.png");
	//SHOP --------------------------------
	RectangleShape shelf;
	Sprite heal;
	Texture heal_;
	
	shelf.setFillColor(Color::White);
	shelf.setSize({ 600, 200 });
	shelf.setPosition(window.getSize().x / 2 - shelf.getSize().x / 2, window.getSize().y / 2 - shelf.getSize().y / 2 - 50);

	heal_.loadFromFile("textures/heal.png");
	heal.setTexture(heal_);
	heal.setScale({ 0.7f,0.7f });
	heal.setPosition(shelf.getGlobalBounds().left + heal.getScale().x * 98 / 2, shelf.getGlobalBounds().top + (shelf.getSize().y / 2) - heal.getScale().y * 79 / 2 - 20) ;
	text healCost(&font, 25, Color::Blue, heal.getPosition().x, heal.getPosition().y + heal.getScale().y * 79 + 20 , "20 GOLD");
	text doubleMultiplier(&font, 35, Color::Green, heal.getGlobalBounds().left + 150, shelf.getGlobalBounds().top + (shelf.getSize().y / 2) - 60, "2X SCORE\nMULTIPLIER\n20 GOLD");
	text goldMultiplier(&font, 35, Color::Blue, doubleMultiplier.getBounds().left + 200, shelf.getGlobalBounds().top + shelf.getSize().y / 2 - 60, "2X GOLD\nMULTIPLIER\n20 GOLD");
	//Health bar------------------------------------------------------------
	
	RectangleShape HPbar;
	//std::vector<Texture> Hp;
	HPbar.setPosition(10, 35);
	HPbar.setSize({210.f, 21.1f});
	Texture Hp[11];
	float HP_;
	float HPmax_;
	float HPbar_ = 0;
	for (int i = 0; i <= 10; i++) {
		Hp[i].loadFromFile("textures/hp/" + std::to_string(i) + ".png");
	}
	HPbar.setTexture(&Hp[0]);

	//Player init--------------------------------------------------------
	Player ship(&playerText);
	//
	bool paused = false;
	//VARIABLES FOR DELAYS AND ETC---------------------------------------
	int shootDelay_ = 20; //changed shoot delay
	int shootDelay = shootDelay_;
	int enemySpawnDelay = 0;
	int enemySpawnDelay_ = 100;
	int d1 = 0;
	int d1_ = 2000;
	int d2 = 0;
	int d2_ = 1000;
	int barDelay = 0;
	const int barDelay_ = 15;
	int asteroidSpawnDelay = 0;
	int asteroidSpawnDelay_ = 50;
	int score = 0;
	int scoreMultpl = 1;
	int gold_ = 0;
	int goldMultpl = 1;
	int stage = 0;
	bool anyBoss = false;
	int bossType = 0;
	bool inShop = false;		// if true, shop screen is drawn
	
	//Background
	//Background mainmenu({(float)window.getSize().x, (float)window.getSize().y}, sf::Color::Blue	);
	Background mainmenu({ (float)window.getSize().x, (float)window.getSize().y }, &skytext);
	//BUTTONS
	button playButton(
						{ (float)window.getSize().x / 2, (float)window.getSize().y / 8},	//size
						{ (float)window.getSize().x / 4, (float)window.getSize().y / 8 },  //pos
						Color::Transparent, "PLAY GAME", 30, &font);

	button settingsButton(
						{ (float)window.getSize().x / 2 - 50 , (float)window.getSize().y / 8 },										//size
						{ (float)window.getSize().x / 4 + 25, playButton.getCoords().y + playButton.getSize().y + 50 },		//pos
						Color::Transparent, "SETTINGS", 30, &font);

	button exitButton(
						{ (float)window.getSize().x / 2 - 100, (float)window.getSize().y / 8 },											//size
						{ (float)window.getSize().x / 4 + 50, settingsButton.getCoords().y + settingsButton.getSize().y + 50 },		//pos
						Color::Transparent, "EXIT GAME", 30, &font);

	button exitButton_(
						{ (float)window.getSize().x / 2 - 100, (float)window.getSize().y / 8 },											//size
						{ (float)window.getSize().x / 4 + 50, settingsButton.getCoords().y + settingsButton.getSize().y + 200 },		//pos
						Color::Transparent, "EXIT GAME", 30, &font);

	button newGame(
						{ (float)window.getSize().x / 2, (float)window.getSize().y / 8 },	//size
						{ (float)window.getSize().x / 4, (float)window.getSize().y / 8 },  //pos
						Color::Transparent, "PLAY AGAIN", 30, &font);
	button resumeGame(
						{ (float)window.getSize().x / 2, (float)window.getSize().y / 8 },	//size
						{ (float)window.getSize().x / 4, (float)window.getSize().y / 8 },  //pos
						Color::Transparent, "RESUME GAME", 30, &font);
	button shopItems(
						{ (float)window.getSize().x / 2 - 50 , (float)window.getSize().y / 8 },										//size
						{ (float)window.getSize().x / 4 + 25, WINDOW_SIZE_Y - 200 },		//pos
						Color::Transparent, "BUY POWERUPS", 30, &font);
	//GAME LOOP
	while (window.isOpen()) {
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;
	//	std::cout << time << std::endl;
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
		}
		//stage 0, main menu
		if (stage == 0) {
			handleMenu(event, &window, playButton, settingsButton, exitButton, stage, mainmenu);
		}
		
		//stage 1 , game
		if (stage == 1) {
			if (paused == false) {
				if (ship.getHP() > 0) {
					if (Keyboard::isKeyPressed(Keyboard::Escape)) {
						paused = true;
					}
					if (barDelay < barDelay_)
						barDelay++;
					else if (barDelay >= barDelay_) {
						HP_ = ship.getHP();
						HPmax_ = ship.getHPmax();
						if (HP_ < HPmax_) {
							HPbar_ = 10 - (HP_ / HPmax_) * 10;
							//		std::cout << HP_ << " " << HPbar_ << std::endl;
						}
						HPbar.setSize({ 210.f, 25.1f });
						barDelay = 0;
					}
					//Update Player
					ship.updateMoves();

					
					//Player Collision with window
					//Left
					isCollidingWindow(&ship, &window);
					//Update bullets
					if (shootDelay < shootDelay_)
						shootDelay++;
					//ADDING BULLETS NEEDS CHANGE
					createBullets(&doubleShot, &tripleShot, &singleShot, &ship, shootDelay, shootDelay_, &bulletText);
					//MANAGE BULLETS

					for (size_t i = 0; i < ship.bullets.size(); i++)
					{
						//Move
						ship.bullets[i].move(0.f, -ship.bullets[i].getSpeed());

						//Out of window bounds
						if (ship.bullets[i].getPos().y < 0)
						{
							std::cout << "Player bullet deleted\n";
							ship.bullets.erase(ship.bullets.begin() + i);
							break;
						}
						//Enemy collision
						for (size_t k = 0; k < enemyShips.size(); k++)
						{
							if (ship.bullets[i].getBounds().intersects(enemyShips[k].getBounds()))
							{
								if (enemyShips[k].getHP() <= 1)
								{
									//	if (enemyShips[k].type > 1) {
									explosions.push_back(Explosion(&explosionText, { enemyShips[k].getPos().x - 55, enemyShips[k].getPos().y - 45 }));

									//}
									score += enemyShips[k].getHPmax() * scoreMultpl;
									enemyShips.erase(enemyShips.begin() + k);
								}
								else {
									enemyShips[k].takeDamage(ship.getLvl()); //ENEMY TAKE DAMAGE 
																// IF PLAYER LVL 1 , HP--; NEED TO ADD CHECK FOR ENEMY LVL
								}
								ship.bullets.erase(ship.bullets.begin() + i);
								break;
							}

						}

					}
					
					for (size_t i = 0; i < ship.bullets.size(); i++) {
						//ASTEROIDS COLLISION
						for (size_t k = 0; k < asteroids.size(); k++)
						{
							if (ship.bullets[i].getBounds().intersects(asteroids[k].getBounds()))
							{
								if (asteroids[k].getHP() <= 1)
								{
									if (randomNumber(4) == 2) {
										std::cout << "COIN DROPPED\n";
										coins.push_back(Coin(&coinText, asteroids[k].getPos()));
									}
									score += asteroids[k].getHPmax() * scoreMultpl;
									asteroids.erase(asteroids.begin() + k);
								}
								else {
									asteroids[k].takeDamage(ship.getLvl()); //ENEMY TAKE DAMAGE 
												   // IF PLAYER LVL 1 , HP--; NEED TO ADD CHECK FOR ENEMY LVL
								}
								ship.bullets.erase(ship.bullets.begin() + i);
								break;
							}

						}
					}
					//Enemy
					handleEnemies(explosions, &explosionText, &HPbar, HPbar_, d1, d1_, d2, d2_, bosses, bossType, anyBoss, &ship, enemySpawnDelay, enemySpawnDelay_, enemyShips, asteroids, enemyShip1, enemyShipText, asteroidText, &window, asteroidSpawnDelay_, asteroidSpawnDelay);

					//UI Update
					scoreboard.setStr("Score: " + std::to_string(score));
					gold.setStr("Gold: " + std::to_string(gold_));

				}
				//Draw ===================================================================== DRAW
				window.clear();


				//player
				//ship.drawTo(&window);
				window.draw(ship);
				//Bullets
				for (size_t i = 0; i < ship.bullets.size(); i++)
				{
					//ship.bullets[i].drawTo(&window);
					window.draw(ship.bullets[i]);
				}
				for (size_t i = 0; i < coins.size(); i++) {

					coins[i].change();
					coins[i].move();
					std::cout << "DRAWING\n" << std::endl;
					coins[i].drawTo(&window);
					if (coins[i].getY() > window.getSize().y) {
						coins.erase(coins.begin() + i);
						std::cout << "COIN DELETED\n";
						break;
					}
					if (ship.getBounds().intersects(coins[i].getBounds())) {
						coins.erase(coins.begin() + i);
						gold_ = gold_ + goldMultpl;
						break;
					}
				}
				//enemy

				for (size_t i = 0; i < asteroids.size(); i++)
				{
					//asteroids[i].drawTo(&window);
					window.draw(asteroids[i]);
				}
				for (size_t i = 0; i < enemyShips.size(); i++)
				{
					enemyHP.setStr(std::to_string(enemyShips[i].getHP()) + "/" + std::to_string(enemyShips[i].getHPmax()));
					enemyHP.setPos(enemyShips[i].getPos().x, enemyShips[i].getPos().y - enemyHP.getBounds().height);
					enemyHP.drawTo(&window);
					//enemyShips[i].drawTo(&window);
					window.draw(enemyShips[i]);
				}
				/*		if (!bosses[bossType].isDead) {
							bosses[bossType].drawTo(&window);
						}
						for (size_t i = 0; i < bosses[bossType].bullets.size(); i++) {
							bosses[bossType].bullets[i].drawTo(&window);
						}*/
				for (size_t i = 0; i < enemyShips.size(); i++) {
					for (size_t k = 0; k < enemyShips[i].bullets.size(); k++) {
						enemyShips[i].bullets[k].move(0.f, enemyShips[i].bullets[k].getSpeed());
						//enemyShips[i].bullets[k].drawTo(&window);
						window.draw(enemyShips[i].bullets[k]);
						if (enemyShips[i].bullets[k].getPos().y >= window.getSize().y + enemyShips[i].bullets[k].getBounds().height)
						{
							std::cout << "ENEMY BULLET DELETED" << std::endl;
							enemyShips[i].bullets.erase(enemyShips[i].bullets.begin() + k);
							break;
						}

						if (enemyShips[i].bullets[k].getBounds().intersects(ship.getBounds()))
						{
							enemyShips[i].bullets.erase(enemyShips[i].bullets.begin() + k);

							ship.takeDamage(ship.getLvl());
							HPbar_ = 10.5;
							HPbar.setSize({ 210.f, 23.f });
							break;
						}
					}
				}
				for (size_t i = 0; i < explosions.size(); i++) {
					if (!explosions[i].isOver()) {

						explosions[i].change();
						explosions[i].drawTo(&window);
					}
					else if (explosions[i].isOver()) {


						explosions.erase(explosions.begin() + i);
					}
				}
				HPbar.setTexture(&Hp[(int)HPbar_]);

				ship.setLvl(enemyShips, score, d1_, d2_, enemySpawnDelay_, asteroidSpawnDelay_, scoreMultpl, shootDelay_);
				//UI
			}
			handlePausedMenu(&shelf, &heal, &heal_, &resumeGame, &shopItems, &window, &event, paused, stage, inShop, scoreMultpl);
			
			scoreboard.setPos(10, 10);
			scoreboard.setSize(20);
			scoreboard.drawTo(&window);
			if (inShop == false)
				gold.drawTo(&window);
			enemyHP.drawTo(&window);
			window.draw(HPbar);
			//MAKE HP ABOVE PLAYER			hpText.setPosition(ship.getPos().x, ship.getPos().y - hpText.getGlobalBounds().height);
			playerHP.setStr("HP " + std::to_string(ship.getHP()) + "/" + std::to_string(ship.getHPmax()));
			playerHP.drawTo(&window);
			
			if (inShop == true) {
				handleShop(&purchase, &shelf, &heal, &heal_, &window, &event, scoreMultpl, gold_, &ship, HPbar_, &HPbar, Hp, &doubleMultiplier, &goldMultiplier, goldMultpl);
				window.draw(shelf);
				window.draw(heal);
				healCost.drawTo(&window);
				doubleMultiplier.drawTo(&window);
				goldMultiplier.drawTo(&window);
				gold.setStr("Gold: " + std::to_string(gold_));
			}
			window.display();
			if (ship.getHP() <= 0) {

				stage = 3;
			}
		}
			//AFTER GAME IS OVER ASLS FOR THE NEXT GAME
			if (stage == 3) {
				if (gold_ != 0) {
					updateGold(gold_);
				}
				
				
				while (window.pollEvent(event)) {
					if (event.type == event.MouseButtonPressed) {
						if (event.mouseButton.button == sf::Mouse::Left) {
							if (newGame.isPressed({ (float)event.mouseButton.x, (float)event.mouseButton.y })) {
								if (score > checkHighScore()) {
									std::cout << "NEW RECORD\n";
									updateHighScore(score);
								}
								reset(enemySpawnDelay_, asteroidSpawnDelay_, d1_, d2_, scoreMultpl, goldMultpl, explosions, &window, &ship, score , gold_, enemyShips, ship.bullets, asteroids, HPbar_); // RESETTING ALL NECESSARY VARIABLES FOR NEW GAME
								stage = 1;
							}
							else if (exitButton_.isPressed({ (float)event.mouseButton.x, (float)event.mouseButton.y })) {
								{
									if (score > checkHighScore()) {
										std::cout << "NEW RECORD\n";
										updateHighScore(score);
									}
								}
								window.close();
							}
						}
					}
					std::cout << ship.bullets.size() << " " << enemyShips.size() << " " << asteroids.size() << " " << explosions.size() << std::endl;
					highScore.setPos((float)window.getSize().x / 2 - 60, (float)window.getSize().y / 2 - 100);
					window.clear();
					mainmenu.drawTo(&window);
					gameOver.drawTo(&window);
					exitButton_.drawTo(&window);
					newGame.drawTo(&window);
					scoreboard.setStr("Your score : " + std::to_string(score));
					scoreboard.setSize(30);
					scoreboard.setPos( (float)window.getSize().x / 2 - 60, (float)window.getSize().y / 2 - 170 );
					if (checkHighScore() >= score) {
						highScore.setStr("High Score : " + std::to_string(checkHighScore()));
						highScore.drawTo(&window);
						scoreboard.drawTo(&window);
					}
					else if (checkHighScore() < score) {
						std::cout << "NEW RECORD\n";
						
						newHighScore.setStr("New High Score: " + std::to_string(score));
						newHighScore.drawTo(&window);

					}
					
					//IF highest score 
					//draw(text highscore);
					window.display();
				}
				
			}
		//	window.display();-
		
	}
	return 0;
}