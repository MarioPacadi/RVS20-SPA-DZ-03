#pragma once
#include<string>
#include<vector>
#include<queue>
#include<Windows.h>
using namespace std;

#define REDAKA 21
#define STUPACA 41
#define clearScreen system("cls")

struct Tocka
{
	int x;
	int y;

	void init(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
};

struct node_dijakstra
{
	Tocka current_position;
	Tocka last_position;
	int distance=9999;
	bool visited = false;
};

struct Comparison
{
	bool operator() (node_dijakstra n1, node_dijakstra n2)
	{
		return n1.distance > n2.distance;
		// > shortest route
		// < longest route
	}
};

class Dijkstra
{
private:
	Tocka A; //start
	Tocka B; //end
	Tocka wall;
	node_dijakstra field[REDAKA][STUPACA]; //map

	vector<Tocka> path; //path
	priority_queue<node_dijakstra, vector<node_dijakstra>, Comparison> pq; //Comparison set to shortest route

	void set_dot(string dot_symbol);
	void set_wall();
	void set_field();
	int get_distance(Tocka current,Tocka next);
	void iscrtaj(Tocka location);

public:
	Dijkstra();

	void draw_path();
	void Dijkstra_algorithm();
};

