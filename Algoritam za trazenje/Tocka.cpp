#include "Tocka.h"
#include<iostream>
#include<string>
#include<vector>
#include<math.h>
#include<queue>
#include<Windows.h>
using namespace std;

//############# PRIVATE ##############

void Dijkstra::set_dot(string dot_symbol)
{
	int red, stupac;

	do
	{
		cout << dot_symbol << " red: ";
		cin >> red;
		cout << dot_symbol << " stupac: ";
		cin >> stupac;

		if (red < 0 || stupac < 0 || red > REDAKA || stupac > STUPACA)
		{
			clearScreen;
			cout << "Error" << endl
				<< "Red must be from 1 to 20" << endl
				<< "Stupac must be from 1 to 40" << endl;
			Sleep(4000);
			clearScreen;
		}

	} while (red<0 || stupac<0 || red>REDAKA || stupac>STUPACA);
	
	
	if (dot_symbol == "A")
	{
		A.init(red, stupac);
	}
	else if (dot_symbol == "B") 
	{
		B.init(red, stupac);
	}

}

void Dijkstra::set_wall()
{
	wall.init(11, 10);
}

void Dijkstra::set_field()
{
	for (unsigned x = 0; x < REDAKA; x++)
	{
		for (unsigned y = 0; y < STUPACA; y++)
		{
			field[x][y].current_position.init(x, y);
		}
	}

	field[A.x][A.y].distance = 0;
}

int Dijkstra::get_distance(Tocka current, Tocka next)
{
	return 10*sqrt(pow((current.x- next.x), 2) + pow((current.y- next.y), 2));
}

void Dijkstra::draw_path()
{
	for (auto it = path.rbegin(); it != path.rend(); ++it)
	{
		iscrtaj((*it));
		if (it != path.rend() - 1) clearScreen;
	}
}

//############# PUBLIC ##############

Dijkstra::Dijkstra()
{
	set_dot("A");
	set_dot("B");
	set_wall();
	set_field();
	clearScreen;
}

void Dijkstra::iscrtaj(Tocka location)
{

	for (unsigned x = 1; x < REDAKA; x++)
	{
		for (unsigned y = 1; y < STUPACA; y++)
		{
			if (x == A.x && y == A.y) cout << "A"; //start
			else if (x == B.x && y == B.y) cout << "B"; //end
			else if (location.x==x && location.y==y) cout << "*"; //current location
			else if (x < wall.x && y == wall.y) cout<<"|"; //wall
			else cout << "-"; //space
		}

		cout << endl;
	}
	
	Sleep(100);
}

void Dijkstra::Dijkstra_algorithm()
{
	Tocka current = A;
	Tocka next;
	
	while (current.x != B.x || current.y != B.y)
	{
		int Start_X = current.x - 1;
		int Start_Y = current.y - 1;

		int End_X = current.x + 1;
		int End_Y = current.y + 1;

		for (int x = Start_X; x <=End_X; x++)
		{
			for (int y = Start_Y; y <= End_Y; y++)
			{
				if (x == current.x && y == current.y) continue;
				else if (x < 0 || x >= REDAKA || y < 0 || y >= STUPACA) continue; //must be in boundaries
				else if (field[current.x][current.y].visited) continue; //was it visited
				else if (current.x<wall.x && current.y==wall.y) continue; //wall

				next.init(x, y);
				int TenativeDistance = get_distance(current, next) + field[current.x][current.y].distance;
				if (TenativeDistance < field[x][y].distance)
				{
					field[x][y].distance = TenativeDistance;
					field[x][y].last_position = current;
					pq.push(field[x][y]);
				}
			}
		}
	
		field[current.x][current.y].visited = true;

		current = pq.top().current_position;
		pq.pop();
	}

	while (current.x != A.x || current.y != A.y)
	{
		path.push_back(current);
		current = field[current.x][current.y].last_position;
	}

}


