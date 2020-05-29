// dijkstra.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
/*
Алгоритм Дейкстры на бинарной куче
Чешуин Михаил, Красильникова Ольга
Имеются города с номерами от 1 до N и дороги между некоторыми из них.
По дороге можно ехать в любом направлении. Известна длина каждой дороги.
Нужно найти кратчайший путь из города S в город T.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <string>
#include <cstdio>
#include <queue>
#include <algorithm>
#include <map>

#define MAX 100000

using namespace std;

vector<pair<int, int>> tree(MAX); //(distance,node)
vector<vector<int>> cityes(MAX, vector < int >(MAX));
vector<int> dist(MAX, 0x3FFFFFFF);
int quantityOfCityes, quantityOfRoads, startCity, endCity;

int main()
{
	fstream input("input.txt");
	ofstream output("output.txt");
	int i, len, firstCity, secondCity, weightRoad, start, end;
	input >> quantityOfCityes >> quantityOfRoads >> startCity >> endCity;
	while (!input.eof()) {
		input >> firstCity >> secondCity >> weightRoad;
		cityes[firstCity][secondCity] = weightRoad;
		cityes[secondCity][firstCity] = weightRoad;
	}
	if (startCity > endCity) {
		start = endCity;
		end = startCity;
	}
	else {
		start = startCity;
		end = endCity;
	}
	tree[0] = make_pair(0, start); len = 1; dist[start] = 0;
	map <int, vector<int>> paths;
	vector<int> path;
	path.push_back(startCity);
	while (len)
	{
		pair < int, int > cityPair = tree[0];
		pop_heap(tree.begin(), tree.begin() + len, greater<pair<int, int>>()); len--;
		for (i = 1; i <= quantityOfCityes; i++)
			if (cityes[cityPair.second][i] && (dist[i] > dist[cityPair.second] + cityes[cityPair.second][i]))
			{
				dist[i] = dist[cityPair.second] + cityes[cityPair.second][i];
				tree[len] = make_pair(dist[i], i); len++;
				if (i != end ) {
					path.push_back(i);
				}
				else {
					paths.insert(make_pair(dist[i], path));
				}
				push_heap(tree.begin(), tree.begin() + len, greater<pair<int, int>>());
			}
	}

	if (start != endCity) {
		if (dist[endCity] == 0x3FFFFFFF) {
			printf("NO");
		}
		else {
			output << dist[endCity];
			const vector<int> buf = paths[dist[endCity]];
			for (int i = 0; i < buf.size(); i++) {
				output << buf[i] << " ";
			}
			output << endCity;
		}
	}
	else {
		if (dist[startCity] == 0x3FFFFFFF) {
			printf("NO");
		}
		else {
			output << dist[startCity];
			const vector<int> buf = paths[dist[startCity]];
			for (int i = 0; i < buf.size(); i++) {
				output << buf[i] << " ";
			}
			output << endCity;
		}
	}

	input.close();
	output.close();

	return 0;

}
