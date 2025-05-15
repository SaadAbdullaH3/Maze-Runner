#include<iostream>
#include"SFML/Graphics.hpp"
#include"SFML/Audio.hpp"
#include<cstdlib>
#include<cmath>
#include<time.h>
using namespace sf;
using namespace std;


class AVLNode {
public:
	int key;
	AVLNode* left;
	AVLNode* right;
	Texture tex;
	Sprite items;
	Sprite addon;

	
	int height;

	// Add More functions or variables if required
	AVLNode(int val, Texture Tex) {
		this->key = val;
		this->tex = Tex;
		this->addon.setTexture(this->tex);
		/*this->addon.setPosition(900, x);
		x = x + 30;*/
		this->height = 0;
		this->right = nullptr;
		this->left = nullptr;
	}
};

class AVLTree {
public:
	AVLNode* root;
	int size;
	AVLTree() {
		root = nullptr;
		size = 0;
	}

	int height(AVLNode* node) {
		if (node == nullptr) {
			return 0;
		}
		else {
			return node->height;
		}

	}
	AVLNode* minValueNode(AVLNode* node) {
		AVLNode* current = node;
		while (current && current->left != nullptr) {
			current = current->left;
		}
		return current;
	}

	int getbalance(AVLNode* ptr) {
		return height(ptr->left) - height(ptr->right);
	}
	int max(int a, int b) {
		return (a > b) ? a : b;
	}

	AVLNode* rr(AVLNode* ptr) {
		if (!ptr || !ptr->left) {
			// Handle null pointers
			return nullptr;
		}

		AVLNode* x = ptr->left;
		AVLNode* z = x->right;

		x->right = ptr;
		ptr->left = z;

		// Update heights
		ptr->height = max(height(ptr->left), height(ptr->right)) + 1;
		x->height = max(height(x->left), height(x->right)) + 1;

		return x;
	}
	AVLNode* ll(AVLNode* ptr) {
		if (!ptr || !ptr->right) {
			// Handle null pointers
			return nullptr;
		}

		AVLNode* x = ptr->right;
		AVLNode* z = x->left;

		ptr->right = z;
		x->left = ptr;

		// Update heights
		ptr->height = 1 + max(height(ptr->left), height(ptr->right));
		x->height = 1 + max(height(x->left), height(x->right));

		return x;
	}

	AVLNode* insertion(AVLNode* ptr, int val, Texture tex) {
		if (ptr == nullptr) {
			ptr = new AVLNode(val,tex);
			return ptr;
		}
		else if (val < ptr->key) {
			ptr->left = insertion(ptr->left, val,tex);
		}
		else if (val > ptr->key) {
			ptr->right = insertion(ptr->right, val,tex);
		}

		if (height(ptr->left) > height(ptr->right)) {
			ptr->height = height(ptr->left) + 1;
		}
		else {
			ptr->height = height(ptr->right) + 1;
		}

		if (getbalance(ptr) > 1 && val < ptr->left->key) {
			return rr(ptr);
		}
		else if (getbalance(ptr) < -1 && val > ptr->right->key) {
			return ll(ptr);
		}
		else if (getbalance(ptr) > 1 && val > ptr->left->key) {
			ptr->left = ll(ptr);
			return rr(ptr);
		}
		else if (getbalance(ptr) < -1 && val < ptr->right->key) {
			ptr->right = rr(ptr);
			return ll(ptr);
		}

		//this->size++;
		return ptr;

	}
	void insert(int key,Texture tex) {
		root = insertion(this->root, key,tex);
	}
	void preorderTraversal(AVLNode* node, RenderWindow& window, float xPosition) {
		if (node != nullptr){
			// Set position before drawing
			node->addon.setPosition(900, xPosition);
			window.draw(node->addon);

			// Increment xPosition for next artifact
			xPosition += 50;
			preorderTraversal(node->right, window, xPosition);
			preorderTraversal(node->left, window, xPosition);
	
			
		}
	}

	AVLNode* remove(AVLNode* root, int key) {
		if (root == nullptr) {
			return nullptr; // Item not found
		}

		if (key < root->key) {
			root->left = remove(root->left, key);
		}
		else if (key > root->key) {
			root->right = remove(root->right, key);
		}
		else {
			// Node to remove found
			if (root->left == nullptr || root->right == nullptr) {
				AVLNode* temp = root->left ? root->left : root->right;
				if (temp == nullptr) {
					temp = root;
					root = nullptr;
				}
				else {
					*root = *temp;
				}
				delete temp;
			}
			else {
				AVLNode* temp = minValueNode(root->right);
				root->key = temp->key;
				root->right = remove(root->right, temp->key);
			}
		}

		// Update height and balance factor
		if (root == nullptr) {
			return root;
		}
		root->height = 1 + std::max(height(root->left), height(root->right));
		int balance = getbalance(root);

		// Perform rotations if necessary
		if (balance > 1 && getbalance(root->left) >= 0) {
			return rr(root);
		}
		if (balance > 1 && getbalance(root->left) < 0) {
			root->left = ll(root->left);
			return rr(root);
		}
		if (balance < -1 && getbalance(root->right) <= 0) {
			return ll(root);
		}
		if (balance < -1 && getbalance(root->right) > 0) {
			root->right = rr(root->right);
			return ll(root);
		}
		return root;
	}

	bool search(AVLNode* root, int key) {
		// Base cases: root is null or key found at root
		if (root == nullptr || root->key == key) {
			return (root != nullptr); // Return true if root is not null
		}

		// If key is smaller than the root's key, search left subtree
		if (key < root->key) {
			return search(root->left, key);
		}
		// If key is greater than the root's key, search right subtree
		else {
			return search(root->right, key);
		}
	}


};

class Node2 {
public:
	Sprite data;
	Node2* next;

	Node2(Sprite sprite) : data(sprite), next(nullptr) {}
};

class LinkedList {
public:
	Node2* head;

	LinkedList() : head(nullptr) {}

	// Function to insert a new node with given sprite data
	void insert(Sprite sprite) {

		Node2* newNode = new Node2(sprite);
		newNode->next = head;
		head = newNode;
		
	}

	
	bool compareTextures(const sf::Texture& texture1, const sf::Texture& texture2) {
		
		return texture1.getSize() == texture2.getSize();
	}

	void remove(const sf::Texture& texture) {
		Node2* current = head;
		Node2* prev = nullptr;

		// Traverse the list to find the node with the given texture
		while (current != nullptr) {
			if (compareTextures(*current->data.getTexture(), texture)) {
				// Found the node, remove it
				if (prev == nullptr) {
					head = current->next;
				}
				else {
					prev->next = current->next;
				}
				delete current;
				return;
			}
			prev = current;
			current = current->next;
		}
	}


	// Function to display all sprites in the linked list
	void display(sf::RenderWindow& window) {
		Node2* current = head;
		while (current != nullptr) {
			window.draw(current->data);
			current = current->next;
		}
	}
};






class Node
{
public:
	int data;
	Sprite Player;
	Texture Tex;
	Node* next;
	Node* prev;
	Node* up;
	Node* down;
	int Xcord;
	int Ycord;
	float delta_x = 0, delta_y = 0 , speed = 0.3;
	RectangleShape shape;
	Node(int data = 0, int x = 0, int y = 0) {
		if (data == 1) {
			shape.setSize(Vector2f(50, 42));
			shape.setFillColor(Color::Green);
			shape.setOutlineColor(Color::Magenta);
			shape.setOutlineThickness(2.3);
			Xcord = x;
			Ycord = y;
			shape.setPosition(Xcord, Ycord);


		}
		//cell.setTexture(tex);
		this->data = data;
		this->next = nullptr;
		this->up = nullptr;
		this->down = nullptr;
		this->prev = nullptr;

	}

	void move(std::string s) {

		if (s == "l")
		{
			delta_x = -1;
		}
		else if (s == "r")
		{
			delta_x = 1;
		}
		if (s == "u")
			delta_y = -1;
		else if (s == "d")
			delta_y = 1;

		delta_x *= speed;
		delta_y *= speed;

		Player.move(delta_x, delta_y);

	}
};

class AdjList
{
public:
	Node* head;
	AdjList() {
		this->head = nullptr;
	}
	void Insert(int data, int x, int y) {
		Node* NewNode = new Node(data, x, y);
		if (this->head == nullptr) {
			head = NewNode;

		}
		else
		{
			Node* traPTR = this->head;
			while (traPTR->next != nullptr) {
				traPTR = traPTR->next;
			}
			traPTR->next = NewNode;
			traPTR->next->prev = traPTR;
		}
	}
	void Display() {
		Node* traPTR = this->head;
		while (traPTR != nullptr) {

			cout << traPTR->data;
			if (traPTR->next != nullptr) {
				cout << "->";
			}
			traPTR = traPTR->next;
		}
	}
};

class Graph {
public:
	int maxVertices; //max no of vertices in your graph
	int noOfVertices; // initially 0, increments with every call to createVertex
	int x;
	int y;
	AdjList** maze;
	Graph(int maxVertices = 0) {
		this->maze = new AdjList * [maxVertices];
		this->maxVertices = maxVertices;
		this->noOfVertices = 0;
		x = -10;
		y = -10;

		for (int i = 0; i < this->maxVertices; i++) {
			this->maze[i] = new AdjList[maxVertices];
		}

		for (int i = 0; i < maxVertices; i++)
		{
			y += 45;
			for (int j = 0; j < maxVertices; j++)
			{
				x += 45;

				if (i == 0 || i == maxVertices - 1)
				{
					maze[i][j].Insert(1, x, y);
					continue;

				}

				if (j == 0 || j == maxVertices - 1)
				{
					maze[i][j].Insert(1, x, y);

				}
				maze[i][j].Insert(1, x, y);
			}
			x = -10;
		}

		

		// remover(1, 1); // Start from inner block (1, 1)remover(1, 1); // Start from inner block (1, 1)
	}
	
	void remover(int x, int y, bool c) {
		
		int dx[] = { 1, -1, 0, 0 };
		int dy[] = { 0, 0, 1, -1 };

		
		for (int i = 0; i < 4; ++i) {
			
			int j = rand() % 4;
			// Swap directions at indices i and j
			int temp = dx[i];
			dx[i] = dx[j];
			dx[j] = temp;
			temp = dy[i];
			dy[i] = dy[j];
			dy[j] = temp;
		}

		// Iterate through the shuffled directions
		for (int i = 0; i < 4; ++i) {
			
			int newX = x + dx[i]; // Move 2 steps instead of 1
			int newY = y + dy[i];
			if (c == false)
			{
			    newX = newX * 2; // Move 2 steps instead of 1
				//newY = newY + 2;
				c = true;
			}
			if (c == true)
			{
				 newY = newY * 2;
				 //newX = newX + 2;
				 c = false;
			}

			// Check if the new cell is valid and not visited
			if (newX >= 1 && newX < maxVertices - 1 && newY >= 1 && newY < maxVertices - 1 &&
				maze[newX][newY].head->shape.getFillColor() != Color::Black) {
				// Introduce a probability factor to decide whether to mark the cell as a path or not
				if (rand() % 50 < 60) { // Adjust the probability (70%) as needed
					maze[x][y].head->shape.setFillColor(Color::Black);
					remover(newX, newY, c); // Recursively call remover for the new cell
				}
			}
		}
	}



	void path2()
	{

		for (int i = 1; i < 17; i++)
		{
			for (int j = 1; j < 17; j++)
			{
				if (i % 2 != 0)
				{
					maze[i][j].head->shape.setFillColor(Color::Black);
				}
			}
		}

		int choose = 0;
		for (int i = 1; i < 17; i++)
		{
				choose = 1 + rand() % 16;
				maze[choose][i].head->shape.setFillColor(Color::Black);
				for (int i = choose; i < choose; i++)
				{
					int choose2 = 1 + rand() % 16 ;
					maze[choose2][i].head->shape.setFillColor(Color::Black);

				}
			
		}
		
		for (int i = 1; i < 17; i++)
		{
			choose = 1 + rand() % 16;
			if (maze[i-1][choose].head->shape.getFillColor() == Color::Green)
			{
				if (maze[i + 1][choose].head->shape.getFillColor() == Color::Green)
				{
					maze[i][choose].head->shape.setFillColor(Color::Green);
				}
			}

			if (maze[i - 1][choose].head->shape.getFillColor() == Color::Black)
			{
				if (maze[i + 1][choose].head->shape.getFillColor() == Color::Green)
				{
					maze[i+1][choose].head->shape.setFillColor(Color::Black);
				}
			}
			if (maze[i - 1][choose].head->shape.getFillColor() == Color::Green)
			{
				if (maze[i + 1][choose].head->shape.getFillColor() == Color::Black)
				{
					maze[i][choose].head->shape.setFillColor(Color::Black);
				}
			}
			if (maze[i - 1][choose].head->shape.getFillColor() == Color::Green )
			{
				if (maze[i + 1][choose].head->shape.getFillColor() == Color::Green)
				{
					maze[i+1][choose-1].head->shape.setFillColor(Color::Black);
					maze[i + 1][choose + 1].head->shape.setFillColor(Color::Black);
					
				}
			}
			
		}

		for (int i = 1; i < 17; i++)
		{
			maze[16][i].head->shape.setFillColor(Color::Black);
		}
		

	
	}

	void Graphdisplay() {
		for (int i = 0; i < this->maxVertices; i++) {
			for (int j = 0; j < this->maxVertices; j++)
			{
				this->maze[i][j].Display();

			}
			cout << endl;
		}
	}
};


class Enemy {

public:

	Sprite enemy;
	Texture tex;
	float x;
	int y;
	float speed;
	bool check;

	Enemy() {
		this->check = false;
		tex.loadFromFile("img/monster.png");
		enemy.setTexture(tex);
		enemy.setScale(0.4, 0.4);
		x = 1;
		y = 0;
		speed = 0.3;
		
		int green_count=0;
	
	}

	void move(bool& flag)
	{
		if (flag == false)
		{
			
			enemy.move(0.4, 0);
			if (enemy.getPosition().x >= 617)
				flag = true;
		}
		if (flag == true)
		{
			
			enemy.move(-0.4, 0);
			if (enemy.getPosition().x <= 100)
				flag = false;
		}

	}

};

class Game {

public:
	Time T;
	SoundBuffer sbuff;
	
	Music s;
	
	float prog;
	Graph* Maze;
	Node* playerptr;
	bool check;
	int xInd;
	int yInd;
	bool check2 = true;
	bool check3 = false;
	bool check4 = true;
	bool check5 = true;
	bool flag = true;
	bool flag1 = true;
	bool flag2 = true;
	int count = 0;
	int r2;
	int r1;
	int score = 0;
	AVLTree inventory;
	Node* Treasure;
	LinkedList Disp_inv;
	Enemy* E;
	RectangleShape frame;
	Text scr , scr2,scr3;
	Font pixel;

	Game() {
		srand(time(NULL));
		if (!s.openFromFile("img/game.mp3")) {
			
			std::cerr << "Failed to load music file" << std::endl;
		}
		else {
			// Set music volume (optional)
			s.setVolume(50); // Adjust volume as needed
			// Play the music in a loop
			s.setLoop(true);
			s.play();
		}

		prog = 0;
		check = false;
		Maze = new Graph(18);
		Maze->maze[1][1].head->Tex.loadFromFile("img/player-transformed.png");
		Maze->maze[1][1].head->Player.setTexture(Maze->maze[1][1].head->Tex);
		Maze->maze[1][1].head->Player.setPosition(Maze->maze[1][1].head->Xcord, Maze->maze[1][1].head->Ycord);
		yInd = 1;
		xInd = 1;
		playerptr = Maze->maze[1][1].head;
		playerptr->Player.setScale(0.35, 0.3);

		frame.setFillColor(Color::Transparent);
		frame.setSize(Vector2f(400,70));
		frame.setOutlineColor(Color::Yellow);
		frame.setOutlineThickness(3.0);
		frame.setPosition(880,90);
		pixel.loadFromFile("img/pixel.ttf");
		scr.setFont(pixel);
		scr.setPosition(880, 50);
		scr.setCharacterSize(30);
		scr.setFillColor(Color::White);
		scr.setLineSpacing(0.5);
		scr.setOutlineColor(Color::Black);
		scr.setOutlineThickness(0.3);
		scr.setString("Inventory");
		scr2.setFont(pixel);
		scr2.setPosition(880, 500);
		scr2.setCharacterSize(30);
		scr2.setFillColor(Color::White);
		scr2.setLineSpacing(0.5);
		scr2.setOutlineColor(Color::Black);
		scr2.setOutlineThickness(0.3);

		scr3.setFont(pixel);
		scr3.setPosition(880, 350);
		scr3.setCharacterSize(30);
		scr3.setFillColor(Color::White);
		scr3.setLineSpacing(0.5);
		scr3.setOutlineColor(Color::Black);
		scr3.setOutlineThickness(0.3);
		
		Treasure = new Node[7];
		Treasure[0].Tex.loadFromFile("img/artifacts1-transformed.png");
		Treasure[0].Player.setTexture(Treasure[0].Tex);

		Treasure[1].Tex.loadFromFile("img/artifacts2-transformed.png");
		Treasure[1].Player.setTexture(Treasure[1].Tex);

		Treasure[2].Tex.loadFromFile("img/artifacts2-transformed.png");
		Treasure[2].Player.setTexture(Treasure[2].Tex);

		Treasure[3].Tex.loadFromFile("img/coin.png");
		Treasure[3].Player.setTexture(Treasure[3].Tex);

		Treasure[4].Tex.loadFromFile("img/coin.png");
		Treasure[4].Player.setTexture(Treasure[4].Tex);

		Treasure[5].Tex.loadFromFile("img/coin.png");
		Treasure[5].Player.setTexture(Treasure[5].Tex);

		Treasure[6].Tex.loadFromFile("img/coin.png");
		Treasure[6].Player.setTexture(Treasure[6].Tex);

		E = new Enemy[2];
		E[0].enemy.setPosition(Maze->maze[15][2].head->Xcord, Maze->maze[15][2].head->Ycord);
		E[1].enemy.setPosition(Maze->maze[5][10].head->Xcord, Maze->maze[5][10].head->Ycord);
	}

	
	void spawnArtifacts() {
		
		int artifactX[7];
		int artifactY[7];

		for (int i = 0; i < 7; ++i) { // Spawn six artifacts
			int x, y;
			bool artifactPlaced = false;
			int attempts = 0; // Track the number of attempts

			
			while (!artifactPlaced && attempts < 30000) { // Limiting to 100 attempts
			
				x = 1 + rand() % 15; 
				y = 1 + rand() % 15; 

			
				if (Maze->maze[x][y].head->shape.getFillColor() == Color::Black) {
					
					bool accessible = isAccessible(x, y);
					if (accessible) {
						
						bool overlap = false;
						for (int j = 0; j < i; ++j) {
							if (x == artifactX[j] && y == artifactY[j]) {
								overlap = true;
								break;
							}
						}
						if (!overlap) {
							// Store the position of the artifact
							artifactX[i] = x;
							artifactY[i] = y;
							// Place the artifact in the selected cell
							Treasure[i].Player.setPosition(Maze->maze[x][y].head->Xcord, Maze->maze[x][y].head->Ycord);
							Treasure[i].Player.setScale(0.7, 0.7);
							Treasure[i].Xcord = Maze->maze[x][y].head->Xcord;
							Treasure[i].Ycord = Maze->maze[x][y].head->Ycord;
							artifactPlaced = true; // Mark artifact as placed
						}
					}
				}
				attempts++; 
			}
		}
	}






bool isAccessible(int x, int y) {
    // Check if the selected cell is surrounded by any green cell
    if (Maze->maze[x - 1][y].head->shape.getFillColor() == Color::Green ||
       // Maze->maze[x + 1][y].head->shape.getFillColor() == Color::Green ||
        Maze->maze[x][y - 1].head->shape.getFillColor() == Color::Green //||
        /*Maze->maze[x][y + 1].head->shape.getFillColor() == Color::Green*/) {
        return false; 
    }
   
    return true; // Assuming there's always a path from player to artifact
}

	void start() {

		RenderWindow window(VideoMode(1300, 1000), "MazeRunner");
		Clock clock;
		float timer = 0, delay = 0.3; // Adjust delay as needed
	
		
		Maze->path2();
		Maze->remover(1, 1, check);

		
		spawnArtifacts(); 

		while (window.isOpen())
		{
			
			float time = clock.getElapsedTime().asSeconds();
			clock.restart();
			timer += time;
			
			//cout<<time<<endl; 
			Event e;
			scr2.setString("Score: " + to_string(score));
			scr3.setString("Progress: " + to_string(prog) +"%");
			while (window.pollEvent(e))
			{
				if (e.type == Event::Closed) 
					window.close();                        	    
			}
			if (timer > delay)
			{
				

			
				if (Keyboard::isKeyPressed(Keyboard::Left))
				{
					
					if (Maze->maze[xInd][yInd - 1].head->shape.getFillColor() == Color::Green)
					{

					}
					else
					{
						--yInd;
						playerptr = Maze->maze[xInd][yInd].head;
						playerptr->Tex.loadFromFile("img/player2-transformed.png");
						playerptr->Player.setTexture(playerptr->Tex);
						playerptr->Xcord = Maze->maze[xInd][yInd].head->Xcord;
						playerptr->Ycord = Maze->maze[xInd][yInd].head->Ycord;
						playerptr->Player.setPosition(Maze->maze[xInd][yInd].head->Xcord, Maze->maze[xInd][yInd].head->Ycord);
						playerptr->Player.setScale(0.35, 0.3);
					
						count = 0;



					}
				}                       
				if (Keyboard::isKeyPressed(Keyboard::Right)) 
				{

					if (Maze->maze[xInd][yInd + 1].head->shape.getFillColor() == Color::Green)
					{



					}
					else
					{



						yInd = yInd + 1;

						playerptr = Maze->maze[xInd][yInd].head;
						playerptr->Tex.loadFromFile("img/player-transformed.png");
						playerptr->Player.setTexture(playerptr->Tex);
						playerptr->Xcord = Maze->maze[xInd][yInd].head->Xcord;
						playerptr->Ycord = Maze->maze[xInd][yInd].head->Ycord;
						playerptr->Player.setPosition(Maze->maze[xInd][yInd].head->Xcord, Maze->maze[xInd][yInd].head->Ycord);
						playerptr->Player.setScale(0.35, 0.3);
						check2 = false;
						count = 0;

					}
				}

				if (Keyboard::isKeyPressed(Keyboard::Up) ) 
				{
					E[0].move(flag);
					E[1].move(flag1);
					
					if (Maze->maze[xInd - 1][yInd].head->shape.getFillColor() == Color::Green)
					{

					}
					else
					{
						--xInd;
						playerptr = Maze->maze[xInd][yInd].head;
						playerptr->Tex.loadFromFile("img/player3-transformed.png");
						playerptr->Player.setTexture(playerptr->Tex);
						playerptr->Xcord = Maze->maze[xInd][yInd].head->Xcord;
						playerptr->Ycord = Maze->maze[xInd][yInd].head->Ycord;
						playerptr->Player.setPosition(Maze->maze[xInd][yInd].head->Xcord, Maze->maze[xInd][yInd].head->Ycord);
						playerptr->Player.setScale(0.35, 0.3);
						check4 = false;
						count = 0;


					}
				}       
				if (Keyboard::isKeyPressed(Keyboard::Down) ) 
				{
				
					
					if (Maze->maze[xInd + 1][yInd].head->shape.getFillColor() == Color::Green)
					{

					}
					else
					{
						++xInd;
						playerptr = Maze->maze[xInd][yInd].head;
						playerptr->Tex.loadFromFile("img/player1-transformed.png");
						playerptr->Player.setTexture(playerptr->Tex);
						playerptr->Xcord = Maze->maze[xInd][yInd].head->Xcord;
						playerptr->Ycord = Maze->maze[xInd][yInd].head->Ycord;
						playerptr->Player.setPosition(Maze->maze[xInd][yInd].head->Xcord, Maze->maze[xInd][yInd].head->Ycord);
						playerptr->Player.setScale(0.35, 0.3);
						check5 = false;
						count = 0;

					}
				}

			timer = 0;
			}

			for (int i = 0; i < 7;i++)
			{
				if ((playerptr->Xcord == Treasure[i].Xcord) && (playerptr->Ycord == Treasure[i].Ycord))
				{
					if (Treasure[4].Xcord == playerptr->Xcord && Treasure[4].Ycord == playerptr->Ycord) {

						score += 100;

					}
					else if (Treasure[5].Xcord == playerptr->Xcord && Treasure[5].Ycord == playerptr->Ycord) {

						score += 100;

					}
					else if (Treasure[3].Xcord == playerptr->Xcord && Treasure[3].Ycord == playerptr->Ycord) {

						score += 100;

					}
					else if (Treasure[6].Xcord == playerptr->Xcord && Treasure[6].Ycord == playerptr->Ycord) {

						score += 100;

					}
					else if (Treasure[0].Xcord == playerptr->Xcord && Treasure[0].Ycord == playerptr->Ycord) {

						check3 = true;

					}

					Treasure[i].Xcord = Treasure[i].Xcord - 10000;
					Treasure[i].Ycord = Treasure[i].Ycord - 10000;
					Treasure[i].Player.setPosition(-1000, -1000);
					inventory.insert(i, Treasure[i].Tex);
					Disp_inv.insert(Treasure[i].Player);
				}
			}
			
			E[0].move(flag);
			E[1].move(flag1);

	
				


			
			if (playerptr->Player.getGlobalBounds().intersects(E[1].enemy.getGlobalBounds()))
			{
				if (inventory.search(inventory.root, 1) == true) {
					inventory.root = inventory.remove(inventory.root, 1);
					Disp_inv.remove(Treasure[1].Tex);
					E[1].enemy.setPosition(-1000, -1000);
					score += 100;
					
					
				}

				else if (inventory.search(inventory.root, 2) == true) {
					inventory.root = inventory.remove(inventory.root, 2);
					Disp_inv.remove(Treasure[2].Tex);
					E[1].enemy.setPosition(-1000, -1000);
					score += 100;
					
					
				}

				else
				{
					window.close();
					
				}
			}


		
			if (playerptr->Player.getGlobalBounds().intersects(E[0].enemy.getGlobalBounds()))
			{
				if (inventory.search(inventory.root, 1) == true) {
					inventory.root = inventory.remove(inventory.root, 1);
					Disp_inv.remove(Treasure[1].Tex);
					E[0].enemy.setPosition(-1000, -1000);
					score += 100;
					
					
				}
				else if (inventory.search(inventory.root, 2) == true) {
					inventory.root = inventory.remove(inventory.root, 2);
					Disp_inv.remove(Treasure[2].Tex);
					E[0].enemy.setPosition(-1000, -1000);
					score += 100;
					
			
				}
				else
				{
					window.close();
					
				}
			}

			
		//
			prog = (abs((1045.1 -sqrt(pow((755.0 - (float)playerptr->Xcord), 2) + pow((755.0 - (float)playerptr->Ycord), 2))) / 1045.1)) * 100;
			
		

			
			
			
			window.clear();
			for (int i = 0; i < 18; i++)
			{
				for (int j = 0; j < 18; j++)
				{
					window.draw(this->Maze->maze[i][j].head->shape);
				}
			}
			window.draw(scr);
			window.draw(scr2);
			window.draw(scr3);
			window.draw(frame);
			window.draw(playerptr->Player);
			window.draw(Treasure[0].Player);
			window.draw(Treasure[1].Player);
			window.draw(Treasure[2].Player);
			window.draw(Treasure[3].Player);
			window.draw(Treasure[4].Player);
			window.draw(Treasure[5].Player);
			window.draw(Treasure[6].Player);
			Node2* current = Disp_inv.head;
			int x = 0;

			while (current != nullptr) {
				window.draw(current->data);
				current->data.setPosition(900 + x, 100);
				x += 50;
				current = current->next;
			}
			if (playerptr->Xcord == 755 && playerptr->Ycord == 755 && check3 == true) {
				window.close();
			}
			//inventory.preorderTraversal(inventory.root, window,10);

			window.draw(E[0].enemy);
			window.draw(E[1].enemy);
			window.display();
		}

	}

};