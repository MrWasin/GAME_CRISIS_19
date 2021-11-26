#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include"SFML\System.hpp"
#include <iostream>
#include <list>
#include <math.h>
#include <cstdlib>
#include<stdio.h>
#include<utility>
#include<algorithm>
#include<string>
#include<vector>
#include<windows.h>
#include<time.h>

using namespace std;
using namespace sf;

void Showtext(int x, int y, string word, int size, sf::RenderWindow& window, sf::Font* font);
void updatascore(string a, int b);
void Showscoreboard(sf::RenderWindow& window);

int main()
{
	srand(time(NULL));

	sf::VideoMode desktop = sf::VideoMode().getDesktopMode();
	sf::RenderWindow window(desktop, "CRISIS 19", sf::Style::None);
	sf::Texture score_items;
	sf::Texture HP_items;
	sf::Texture players;
	sf::Texture Bullets;
	sf::Texture Enemies_01;
	sf::Texture Enemies_02;
	sf::Texture Homes;
	sf::Texture BGPlays;
	sf::Texture BGScores;
	sf::Texture Citadels;
	sf::SoundBuffer Whenhit;

	//items.loadFromFile("wship1.png");
	score_items.loadFromFile("Textures/itemScore.png");
	HP_items.loadFromFile("Textures/item.png");
	players.loadFromFile("Textures/ship.png");
	Bullets.loadFromFile("Textures/bullet.png");
	Enemies_01.loadFromFile("Textures/enemy_01.png");
	Enemies_02.loadFromFile("Textures/enemy_02.png");
	Citadels.loadFromFile("Textures/citadel.png");
	Homes.loadFromFile("Textures/backgroundhome.jpg"); 
	BGPlays.loadFromFile("Textures/backgroundplay.jpg");
	BGScores.loadFromFile("Textures/backgroundScore.jpg");
	Whenhit.loadFromFile("Sound/hit.ogg");

	sf::Sound Whenhits;
	Whenhits.setBuffer(Whenhit);

	Sprite Home;
	Home.setTexture(Homes);
	
	Sprite BGPlay;
	BGPlay.setTexture(BGPlays);

	Sprite BGScore;
	BGScore.setTexture(BGScores);

	Sprite Bullet;
	Bullet.setTexture(Bullets);
	Bullet.setScale(0.2f, 0.2f);

	Sprite HP_item;
	HP_item.setTexture(HP_items);
	HP_item.setScale(0.2f, 0.2f);

	Sprite score_item;
	score_item.setTexture(score_items);
	score_item.setScale(0.2f, 0.2f);

	Sprite Enemy_01;
	Enemy_01.setTexture(Enemies_01);
	Enemy_01.setScale(0.2f, 0.2f);

	Sprite Enemy_02;
	Enemy_02.setTexture(Enemies_02);
	Enemy_02.setScale(0.2f, 0.2f);

	Sprite Citadel;
	Citadel.setTexture(Citadels);
	Citadel.setPosition(360, 750);
	Citadel.setScale(0.2f, 0.2f);

	Sprite player;
	player.setTexture(players);
	player.setPosition(860, 900);
	player.setScale(0.2f, 0.2f);
	Vector2f playerCenter;

	std::vector<Sprite> updateBullets;
	updateBullets.push_back(Sprite(Bullet));

	std::vector<Sprite> updateEnemies_01;
	updateEnemies_01.push_back(Sprite(Enemy_01));

	std::vector<Sprite> updateEnemies_02;
	updateEnemies_02.push_back(Sprite(Enemy_02));

	std::vector<Sprite> updateHP_items;
	updateHP_items.push_back(Sprite(HP_item));

	std::vector<Sprite> updateScore_items;
	updateScore_items.push_back(Sprite(score_item));

	int shootTimer = 800;
	int Enemy_01SpawnTimer = 0;
	int Enemy_02SpawnTimer = 0;
	int HP_itemSpawnTimer = 0;
	int Score_itemSpawnTimer = 0;

	Font font;
	if (!font.loadFromFile("Fonts/Amazing-Kids.ttf"))
		throw("ERROR::GAME::Failed to load font");

	Font font01;
	if (!font01.loadFromFile("Fonts/PixellettersFull.ttf"))
		throw("ERROR::GAME::Failed to load font");

	Text namegametext;
	namegametext.setFont(font);
	namegametext.setCharacterSize(120);
	namegametext.setFillColor(Color::Green);
	namegametext.setString("CRISIS 19");
	namegametext.setPosition(750, 10);

	Text numbertext;
	numbertext.setFont(font01);
	numbertext.setCharacterSize(60);
	numbertext.setFillColor(Color::Green);
	numbertext.setString("64010790");
	numbertext.setPosition(1400, 900);

	Text nametext;
	nametext.setFont(font01);
	nametext.setCharacterSize(60);
	nametext.setFillColor(Color::Green);
	nametext.setString("Wasin Thaosombat");
	nametext.setPosition(1400, 850);

	Text starttext;
	starttext.setFont(font);
	starttext.setCharacterSize(60);
	starttext.setFillColor(Color::Green);
	starttext.setString("START");
	starttext.setPosition(250, 250);
	
	Text exittext;
	exittext.setFont(font);
	exittext.setCharacterSize(60);
	exittext.setFillColor(Color::Green);
	exittext.setString("EXIT");
	exittext.setPosition(250, 550);

	Text highscoretext;
	highscoretext.setFont(font);
	highscoretext.setCharacterSize(60);
	highscoretext.setFillColor(Color::Green);
	highscoretext.setString("HIGH SCORE");
	highscoretext.setPosition(250, 400);

	Text scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(60);
	scoreText.setFillColor(Color::Black);
	scoreText.setPosition(1500.f, 50.f);
	int startus = 0;
	int score = 0;
	int HP = 0;
	RectangleShape Bar;
	Bar.setFillColor(Color::Green);
	Bar.setSize(Vector2f((float)HP * 100.f, 100.f));

	std::string playerInput;
	sf::Text playerText("", font, 70);
	playerText.setPosition(740, 270);
	playerText.setFillColor(sf::Color::Black);

	sf::Text End("Enter", font, 80);
	End.setPosition(745, 425);

	sf::Text Back("Back", font, 80);
	Back.setPosition(845, 805);
	

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{

			if (event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode < 128 && HP <= 0)
				{
					playerInput.push_back(event.text.unicode);

				}
				if (event.text.unicode == '\b')
				{
					playerInput.pop_back();
					playerInput.pop_back();

				}
			}
			if (event.Event::KeyPressed && event.Event::key.code == sf::Keyboard::Escape)
				window.close();
		}

		if (starttext.getGlobalBounds().contains(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y))
		{
			starttext.setFillColor(sf::Color::Green);
		}
		else if (highscoretext.getGlobalBounds().contains(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y))
		{
			highscoretext.setFillColor(sf::Color::Green);
		}
		else if (exittext.getGlobalBounds().contains(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y))
		{
			exittext.setFillColor(sf::Color::Green);
		}
		else
		{
			starttext.setFillColor(sf::Color::White);
			highscoretext.setFillColor(sf::Color::White);
			exittext.setFillColor(sf::Color::White);
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (starttext.getGlobalBounds().contains(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y))
			{
				startus = 1;
			}
			else if (highscoretext.getGlobalBounds().contains(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y))
			{
				startus = 2;
			}
			else if (exittext.getGlobalBounds().contains(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y))
			{
				window.close();
			}
		}

		//Home
		if (startus == 0) 
		{
			HP = 100;
			score = 0;
			player.setPosition(860, 900);
			window.clear();
			window.draw(Home);
			window.draw(nametext);
			window.draw(numbertext);
			window.draw(namegametext);
			starttext.setPosition(250, 250);
			highscoretext.setPosition(250, 400);
			exittext.setPosition(250, 550);
			window.draw(starttext);
			window.draw(highscoretext);
			window.draw(exittext);
			window.display();
		}

		//Play
		if (startus == 1)
		{
			playerCenter = Vector2f(player.getPosition().x + 100, player.getPosition().y - 40);

			//Left world collision
			if (player.getGlobalBounds().left < 0.f)
			{
				player.setPosition(0.f, player.getGlobalBounds().top);
			}
			//Right world collision
			else if (player.getGlobalBounds().left + player.getGlobalBounds().width >= window.getSize().x)
			{
				player.setPosition(window.getSize().x - player.getGlobalBounds().width, player.getGlobalBounds().top);
			}

			//Top world collision
			if (player.getGlobalBounds().top < 0.f)
			{
				player.setPosition(player.getGlobalBounds().left, 0.f);
			}
			//Bottom world collision
			else if (player.getGlobalBounds().top + player.getGlobalBounds().height >= window.getSize().y)
			{
				player.setPosition(player.getGlobalBounds().left, window.getSize().y - player.getGlobalBounds().height);
			}

			//Speedplayer
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				player.move(-3.0f, 0.f);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				player.move(3.0f, 0.f);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				player.move(0.f, -3.0f);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				player.move(0.f, 3.0f);

			//score_items
			if (Score_itemSpawnTimer < 5000)
				Score_itemSpawnTimer++;

			if (Score_itemSpawnTimer >= 5000)
			{
				score_item.setPosition((rand() % int(window.getSize().x - score_item.getScale().x)), 0.f);
				updateScore_items.push_back(Sprite(score_item));

				Score_itemSpawnTimer = 0;
			}

			for (size_t i = 0; i < updateScore_items.size(); i++)
			{
				updateScore_items[i].move(0.f, 1.f);

				if (updateScore_items[i].getPosition().y > window.getSize().y)
					updateScore_items.erase(updateScore_items.begin() + i);
			}


			//HP_items
			if (HP < 25) 
			{
				if (HP_itemSpawnTimer < 2000)
					HP_itemSpawnTimer++;

				if (HP_itemSpawnTimer >= 2000)
				{
					HP_item.setPosition((rand() % int(window.getSize().x - HP_item.getScale().x)), 0.f);
					updateHP_items.push_back(Sprite(HP_item));

					HP_itemSpawnTimer = 0;
				}

				for (size_t i = 0; i < updateHP_items.size(); i++)
				{
					updateHP_items[i].move(0.f, 1.f);

					if (updateHP_items[i].getPosition().y > window.getSize().y)
						updateHP_items.erase(updateHP_items.begin() + i);
				}
			}
			
			//BULLETS
			if (score < 100)
			{
				if (shootTimer < 550 - (score * 5))
					shootTimer++;
			}
			else if (score >= 100)
			{
				if (shootTimer < 50)
					shootTimer++;
			}

			if (score < 100)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && shootTimer >= 550 - (score * 5)) //Shoot
				{
					Bullet.setPosition(playerCenter);
					updateBullets.push_back(Bullet);

					shootTimer = 0;
				}
			}
			else if (score >= 100)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && shootTimer >= 50) //Shoot
				{
					Bullet.setPosition(playerCenter);
					updateBullets.push_back(Bullet);

					shootTimer = 0;
				}
			}

			for (size_t i = 0; i < updateBullets.size(); i++)
			{
				updateBullets[i].move(0.f, -3.f);

				if (updateBullets[i].getPosition().y <= 0)
					updateBullets.erase(updateBullets.begin() + i);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
			}

			//Enemies_01
			if (score < 450)
			{
				if (Enemy_01SpawnTimer < 1000 - (score * 2))
					Enemy_01SpawnTimer++;
			}
			else if (score >= 450)
			{
				if (Enemy_01SpawnTimer < 100)
					Enemy_01SpawnTimer++;
			}

			if (score < 450)
			{
				if (Enemy_01SpawnTimer >= 1000 - (score * 2))
				{
					Enemy_01.setPosition((rand() % int(window.getSize().x - Enemy_01.getScale().x)), 0.f);
					updateEnemies_01.push_back(Sprite(Enemy_01));

					Enemy_01SpawnTimer = 0;
				}
			}
			else if (score >= 450)
			{
				if (Enemy_01SpawnTimer >= 100)
				{
					Enemy_01.setPosition((rand() % int(window.getSize().x - Enemy_01.getScale().x)), 0.f);
					updateEnemies_01.push_back(Sprite(Enemy_01));

					Enemy_01SpawnTimer = 0;
				}
			}

			for (size_t i = 0; i < updateEnemies_01.size(); i++)
			{
				updateEnemies_01[i].move(0.f, 1.0f);

				if (updateEnemies_01[i].getPosition().y > window.getSize().y)
					updateEnemies_01.erase(updateEnemies_01.begin() + i);
			}

			//Enemies_02
			if (score >= 50) 
			{
				if (score < 950)
				{
					if (Enemy_02SpawnTimer < 1000 - score)
						Enemy_02SpawnTimer++;
				}
				else if (score >= 950)
				{
					if (Enemy_02SpawnTimer < 50)
						Enemy_02SpawnTimer++;
				}

				if (score < 950)
				{
					if (Enemy_02SpawnTimer >= 1000 - score)
					{
						Enemy_02.setPosition((rand() % int(window.getSize().x - Enemy_02.getScale().x)), 0.f);
						updateEnemies_02.push_back(Sprite(Enemy_02));

						Enemy_02SpawnTimer = 0;
					}
				}
				else if (score >= 950)
				{
					if (Enemy_02SpawnTimer >= 50)
					{
						Enemy_02.setPosition((rand() % int(window.getSize().x - Enemy_02.getScale().x)), 0.f);
						updateEnemies_02.push_back(Sprite(Enemy_02));

						Enemy_02SpawnTimer = 0;
					}
				}

				for (size_t i = 0; i < updateEnemies_02.size(); i++)
				{
					updateEnemies_02[i].move(0.f, 0.5f);

					if (updateEnemies_02[i].getPosition().y > window.getSize().y)
						updateEnemies_02.erase(updateEnemies_02.begin() + i);
				}
			}


			//Collision Enemies_01
			if (!updateEnemies_01.empty() && !updateBullets.empty())
			{
				for (size_t i = 0; i < updateBullets.size(); i++)
				{
					for (size_t k = 0; k < updateEnemies_01.size(); k++)
					{
						if(score < 100)
						{
							if (updateBullets[i].getGlobalBounds().intersects(updateEnemies_01[k].getGlobalBounds()))
							{
								shootTimer = 550 - score * 5;

								updateBullets.erase(updateBullets.begin() + i);
								updateEnemies_01.erase(updateEnemies_01.begin() + k);

								score = score + 5;
								break;
							}
						}
						else if (score >= 100)
						{
							if (updateBullets[i].getGlobalBounds().intersects(updateEnemies_01[k].getGlobalBounds()))
							{
								shootTimer = 50;

								updateBullets.erase(updateBullets.begin() + i);
								updateEnemies_01.erase(updateEnemies_01.begin() + k);

								score = score + 5;
								break;
							}
						}
					}
				}
			}
			for (size_t i = 0; i < updateEnemies_01.size(); i++)
			{
				if (player.getGlobalBounds().intersects(updateEnemies_01[i].getGlobalBounds()))
				{
					Whenhits.play();
					score = score + 5;
					HP = HP - 5;

					updateEnemies_01.erase(updateEnemies_01.begin() + i);
				}
				else if (Citadel.getGlobalBounds().intersects(updateEnemies_01[i].getGlobalBounds()))
				{
					HP = HP - 5;

					updateEnemies_01.erase(updateEnemies_01.begin() + i);
				}
			}

			//Collision Enemies_02
			if (!updateEnemies_02.empty() && !updateBullets.empty())
			{
				for (size_t i = 0; i < updateBullets.size(); i++)
				{
					for (size_t k = 0; k < updateEnemies_02.size(); k++)
					{
						if (score < 100)
						{
							if (updateBullets[i].getGlobalBounds().intersects(updateEnemies_02[k].getGlobalBounds()))
							{
								shootTimer = 550 - score * 5;

								updateBullets.erase(updateBullets.begin() + i);
								updateEnemies_02.erase(updateEnemies_02.begin() + k);

								score = score + 10;
								break;
							}
						}
						else if (score >= 100)
						{
							if (updateBullets[i].getGlobalBounds().intersects(updateEnemies_02[k].getGlobalBounds()))
							{
								shootTimer = 50;

								updateBullets.erase(updateBullets.begin() + i);
								updateEnemies_02.erase(updateEnemies_02.begin() + k);

								score = score + 10;
								break;
							}
						}
					}
				}
			}
			for (size_t i = 0; i < updateEnemies_02.size(); i++)
			{
				if (player.getGlobalBounds().intersects(updateEnemies_02[i].getGlobalBounds()))
				{
					Whenhits.play();
					score = score + 10;
					HP = HP - 10;

					updateEnemies_02.erase(updateEnemies_02.begin() + i);
				}
				else if (Citadel.getGlobalBounds().intersects(updateEnemies_02[i].getGlobalBounds()))
				{
					HP = HP - 10;

					updateEnemies_02.erase(updateEnemies_02.begin() + i);
				}
			}

			//Collision Score_items
			for (size_t i = 0; i < updateScore_items.size(); i++)
			{
				if (player.getGlobalBounds().intersects(updateScore_items[i].getGlobalBounds()))
				{
					score = score * 2;

					updateScore_items.erase(updateScore_items.begin() + i);

				}
			}
		
			//Collosion HP_items
			for (size_t i = 0; i < updateHP_items.size(); i++)
			{
				if (player.getGlobalBounds().intersects(updateHP_items[i].getGlobalBounds()))
				{
					HP = HP + 50;

					updateHP_items.erase(updateHP_items.begin() + i);

				}
			}

			Bar.setPosition(10, 10);
			Bar.setSize(Vector2f((float)HP * 15.f, 25.f));
			window.clear();

			scoreText.setString("Score: " + std::to_string(score));
			
			window.clear();
			starttext.setPosition(-0, 0);
			highscoretext.setPosition(-0, 0);
			exittext.setPosition(-0, 0);
			window.draw(BGPlay);
			window.draw(Citadel);
			window.draw(player);
			
			//Draw Enemies_01
			for (size_t i = 0; i < updateEnemies_01.size(); i++)
			{
				window.draw(updateEnemies_01[i]);
			}

			//Draw Enemies_02
			if (score >= 50) 
			{
				for (size_t i = 0; i < updateEnemies_02.size(); i++)
				{
					window.draw(updateEnemies_02[i]);
				}
			}
			
			//Draw Bullets
			for (size_t i = 0; i < updateBullets.size(); i++)
			{
				window.draw(updateBullets[i]);
			}

			//Draw Score_items
			if (score >= 100) 
			{
				for (size_t i = 0; i < updateScore_items.size(); i++)
				{
					window.draw(updateScore_items[i]);
				}
			}

			//Draw HP_items
			if (HP < 25) 
			{
				for (size_t i = 0; i < updateHP_items.size(); i++)
				{
					window.draw(updateHP_items[i]);
				}
			}

			window.draw(Bar);
			window.draw(scoreText);
			window.display();

			if (HP <= 0)
			{
				Whenhits.play();
				startus = 3;
				window.display();
			}
		}

		//HIGH SCORE
		if (startus == 2) 
		{
			if (Back.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
			{
				Back.setFillColor(sf::Color::Green);
				Back.setStyle(sf::Text::Underlined);
			}
			else
			{
				Back.setFillColor(sf::Color::Red);
				Back.setStyle(0);
			}

			window.clear();
			window.draw(BGScore);
			Showscoreboard(window);
			window.draw(Back);
			window.display();

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (Back.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
					startus = 0;
			}
		}

		//End game
		if (startus == 3)
		{
			if (End.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
			{
				End.setFillColor(sf::Color::Green);
				End.setStyle(sf::Text::Underlined);
			}
			else
			{
				End.setFillColor(sf::Color::Red);
				End.setStyle(0);
			}
			window.clear();
			window.draw(BGScore);
			window.draw(End);
			playerText.setString("Name here:  " + playerInput);
			window.draw(playerText);
			window.display();

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (End.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
				{
					startus = 0;
					updatascore(playerInput, score);
				}

			}

		}
	}
	return 0;
}

void Showtext(int x, int y, string word, int size, sf::RenderWindow& window, sf::Font* font)
{
	sf::Text text;
	text.setFont(*font);
	text.setPosition(x, y);
	text.setString(word);
	text.setFillColor(Color::Black);
	text.setCharacterSize(size);
	window.draw(text);
}

void updatascore(string a, int b)
{
	FILE* fp;
	char temp[255];
	int score[6];
	string name[6];
	vector <pair<int, string>> userScore;
	fp = fopen("./Score.txt", "r");
	if (fp == NULL)
		printf("File not found\n");

	for (int i = 0; i < 5; i++)
	{
		fscanf(fp, "%s", &temp);
		name[i] = temp;
		fscanf(fp, "%d", &score[i]);
		userScore.push_back(make_pair(score[i], name[i]));
	}

	name[5] = a;
	score[5] = b;
	userScore.push_back(make_pair(score[5], name[5]));
	sort(userScore.begin(), userScore.end());
	fclose(fp);
	fopen("Score.txt", "w");
	for (int i = 5; i >= 1; i--)
	{
		strcpy(temp, userScore[i].second.c_str());
		fprintf(fp, "%s %d\n", temp, userScore[i].first);
	}
	fclose(fp);
}

void Showscoreboard(sf::RenderWindow& window)
{
	sf::Font font;
	font.loadFromFile("Fonts/Amazing-Kids.ttf");

	FILE* fp;
	char temp[255];
	int score[6];
	string name[6];
	fp = fopen("./Score.txt", "r");
	for (int i = 0; i < 5; i++)
	{
		char no[3] = { '1' + i };
		no[1] = '.';
		no[2] = '\0';
		Showtext(700, 250 + 100 * i, no, 50, window, &font);
		fscanf(fp, "%s", &temp);
		Showtext(750, 250 + 100 * i, temp, 50, window, &font);
		fscanf(fp, "%d", &score[i]);
		char sc[10];
		int k = 0, j;
		if (score[i] == 0)
			sc[k++] = 48;
		while (score[i] > 0)
		{
			sc[k++] = score[i] % 10 + 48;
			score[i] /= 10;
		}
		sc[k] = '\0';
		char show[10];
		for (j = 0; j < strlen(sc); j++)
		{
			show[j] = sc[strlen(sc) - 1 - j];
		}
		show[j] = '\0';
		Showtext(1100, 250 + 100 * i, show, 50, window, &font);
	}
	fclose(fp);
}