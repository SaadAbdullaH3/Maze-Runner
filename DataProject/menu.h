// Saad abdullah 22i1045 Abdullah Saleem 22i0882
//
#include "game.h"
class Menu {
public:
	Sprite menu_back;
	Texture menu_tex;
	Font font;
	int i;
	Menu()
	{
		/*menu_tex.loadFromFile("img/background-1.jpg");
		menu_back.setTexture(menu_tex);
		i = 1;
		menu_back.setScale(3, 3);*/
		font.loadFromFile("img/pixel.ttf");
	}

	void display_menu()

	{

		Sprite logo;
		Texture logo_tex;
		logo_tex.loadFromFile("img/background.png");
		logo.setTexture(logo_tex);
		logo.setPosition(270, 70);
		logo.setColor(Color::Red);
		logo.setScale(1, 1);

		Sprite cursor;
		Texture curs;
		curs.loadFromFile("img/cursor.png");
		cursor.setTexture(curs);
		cursor.setScale(1, 1);

		Sprite instr;
		Texture ins;
		ins.loadFromFile("img/instructionscreen.jpg");
		instr.setTexture(ins);
		instr.setPosition(0, -1000);
		instr.setScale(0.32, 0.24);

		/*Sprite hs_back;
		Texture hs;
		hs.loadFromFile("img/background-1.png");
		hs_back.setTexture(hs);
		hs_back.setPosition(0, 0);
		hs_back.setScale(1, 1.5);*/

		Text text("0", font);
		text.setCharacterSize(50);
		text.setPosition(300, 350);//this is position of the text on the window
		text.setString("PLAY");//this is whats gonna be displayed on the screen
		text.setFillColor(Color::Red);
		text.setFont(font);

		Text text1("0", font);
		text1.setCharacterSize(50);
		text1.setPosition(210, 420);//this is position of the text on the window
		text1.setString("INSTRUCTIONS");//this is whats gonna be displayed on the screen
		text1.setFont(font);

		Text text2("0", font);
		text2.setCharacterSize(50);
		text2.setPosition(220, 490);//this is position of the text on the window
		text2.setString("HIGH SCORES");//this is whats gonna be displayed on the screen
		text2.setFont(font);

		Text text3("0", font);
		text3.setCharacterSize(50);
		text3.setPosition(300, 560);//this is position of the text on the window
		text3.setString("EXIT");//this is whats gonna be displayed on the screen
		text3.setFont(font);

		bool flag = false;
		bool flag1 = false;
		Game g;
		//display menu screen here
		srand(time(0));
		RenderWindow wind(VideoMode(780, 780),"Maze Runner");
		/*ifstream inp("Score.txt");
		int size = 0;
		int score1;
		while (inp >> score1)
		{
			size++;
		}
		int* all_scores = new int [size] {};
		int j = 0;
		inp.close();
		ifstream inp1("Score.txt");
		while (inp1 >> score1)
		{
			all_scores[j] = score1;
			j++;
		}
		int temp;
		for (int i = 0; i < size; i++) {
			for (int j = i + 1; j < size; j++) {
				if (all_scores[i] < all_scores[j]) {
					temp = all_scores[i];
					all_scores[i] = all_scores[j];
					all_scores[j] = temp;
				}
			}
		}*/
		//Text high_score1("0", font);
		//high_score1.setCharacterSize(50);
		//high_score1.setPosition(210, 350);//this is position of the text on the window
		//high_score1.setString("Score = " + std::to_string(all_scores[0]));//this is whats gonna be displayed on the screen
		//high_score1.setFont(font);

		//Text high_score2("0", font);
		//high_score2.setCharacterSize(50);
		//high_score2.setPosition(210, 420);//this is position of the text on the window
		//high_score2.setString("Score = " + std::to_string(all_scores[1]));//this is whats gonna be displayed on the screen
		//high_score2.setFont(font);

		//Text high_score3("0", font);
		//high_score3.setCharacterSize(50);
		//high_score3.setPosition(210, 490);//this is position of the text on the window
		//high_score3.setString("Score = " + std::to_string(all_scores[2]));//this is whats gonna be displayed on the screen
		//high_score3.setFont(font);
		while (wind.isOpen())
		{
			Event event;
			while (wind.pollEvent(event))
			{
				//instr.scale(0.01, 0.01);
				if (event.type == Event::Closed) // If cross/close is clicked/pressed
					wind.close();
				if (event.type == Event::KeyPressed)
				{
					if (event.key.code == Keyboard::Down)
					{
						if (i == 0)
						{
							text3.setFillColor(Color::White);
							text.setFillColor(Color::Red);
							i++;

						}
						else if (i == 1)
						{
							text.setFillColor(Color::White);
							text1.setFillColor(Color::Red);
							i++;
						}
						else if (i == 2)
						{
							text1.setFillColor(Color::White);
							text2.setFillColor(Color::Red);
							i++;
						}
						else if (i == 3)
						{
							text2.setFillColor(Color::White);
							text3.setFillColor(Color::Red);
							i = 0;
						}
					}
					if (event.key.code == Keyboard::Up)
					{
						if (i == 0)
						{
							text2.setFillColor(Color::Red);
							text3.setFillColor(Color::White);
							i = 3;

						}
						else if (i == 1)
						{
							text3.setFillColor(Color::Red);
							text.setFillColor(Color::White);
							i--;
						}
						else if (i == 2)
						{
							text.setFillColor(Color::Red);
							text1.setFillColor(Color::White);
							i--;
						}
						else if (i == 3)
						{
							text1.setFillColor(Color::Red);
							text2.setFillColor(Color::White);
							i--;
						}
					}
					if (event.key.code == Keyboard::Enter)
					{
						if (i == 1)
						{
							wind.close();
							g.start();
						}
						if (i == 0)
						{
							wind.close();
						}
					}

				}
				//cout << cursor.getPosition().x << "      , " << cursor.getPosition().y << endl;
				if (event.type == Event::KeyReleased);
				//mouse events
				if (event.type == Event::MouseButtonPressed);
				{
					instr.setPosition(0, -1000);
					flag = false;

					if (cursor.getPosition().x >= 300 && cursor.getPosition().x <= 440 && cursor.getPosition().y >= 350 && cursor.getPosition().y <= 400 && event.key.code == Mouse::Left)
					{
						wind.close();
						g.start();
						cursor.setPosition(0, 0);
					}
					if (cursor.getPosition().x >= 210 && cursor.getPosition().x <= 525 && cursor.getPosition().y >= 420 && cursor.getPosition().y <= 470 && event.key.code == Mouse::Left)
					{
						instr.setPosition(0, 0);
						cursor.setPosition(0, 0);
						flag = true;
					}
					if (cursor.getPosition().x >= 220 && cursor.getPosition().x <= 507 && cursor.getPosition().y >= 490 && cursor.getPosition().y <= 540 && event.key.code == Mouse::Left && flag == false)
					{
						flag = true;
						cursor.setPosition(0, 0);
					}
					if (cursor.getPosition().x >= 300 && cursor.getPosition().x <= 440 && cursor.getPosition().y >= 560 && cursor.getPosition().y <= 610 && event.key.code == Mouse::Left)
					{
						wind.close();
					}
				}
				if (event.type == Event::MouseWheelMoved);
				if (event.type == Event::MouseMoved)
				{
					wind.setMouseCursorVisible(false);
					cursor.setPosition(event.mouseMove.x, event.mouseMove.y);
					if (cursor.getPosition().x >= 300 && cursor.getPosition().x <= 440 && cursor.getPosition().y >= 350 && cursor.getPosition().y <= 400)
						text.setFillColor(Color::Red);
					else
						text.setFillColor(Color::White);
					if (cursor.getPosition().x >= 210 && cursor.getPosition().x <= 525 && cursor.getPosition().y >= 420 && cursor.getPosition().y <= 470)
						text1.setFillColor(Color::Red);
					else
						text1.setFillColor(Color::White);
					if (cursor.getPosition().x >= 220 && cursor.getPosition().x <= 507 && cursor.getPosition().y >= 490 && cursor.getPosition().y <= 540)
						text2.setFillColor(Color::Red);
					else
						text2.setFillColor(Color::White);
					if (cursor.getPosition().x >= 300 && cursor.getPosition().x <= 440 && cursor.getPosition().y >= 560 && cursor.getPosition().y <= 610)
						text3.setFillColor(Color::Red);
					else
						text3.setFillColor(Color::White);
				}
				//				if (event.type == Event::MouseEntered);
				//				if (event.type == Event::MouseLeft);
				//				//window events
				//				if (event.type == Event::LostFocus);
				//				if (event.type == Event::GainedFocus);

			}

			wind.clear(); //clears the screen
		//	wind.draw(menu_back);
			wind.draw(text);
			wind.draw(text1);
			wind.draw(text2);
			wind.draw(text3);
			/*if (flag == true)
			{
				wind.draw(hs_back);
				wind.draw(high_score1);
				wind.draw(high_score2);
				wind.draw(high_score3);
			}*/
			wind.draw(logo);
			wind.draw(instr);
			wind.draw(cursor);
			wind.display();
		}
		// add functionality of all the menu options here

		//if Start game option is chosen

		//    g.start_game();



	}


};
