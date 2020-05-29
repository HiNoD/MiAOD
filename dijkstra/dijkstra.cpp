// dijkstra.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
/*
Алгоритм Дейкстры на бинарной куче
Чешуин Михаил, Красильникова Ольга
Имеются города с номерами от 1 до N и дороги между некоторыми из них.
По дороге можно ехать в любом направлении. Известна длина каждой дороги.
Нужно найти кратчайший путь из города S в город T.
*/


#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <limits>
#include <set>
#include <utility>
#include <algorithm>
#include <iterator>
#include <fstream>
using namespace std;

typedef int vertex_t;
typedef double weight_t;

const weight_t max_weight = numeric_limits<double>::infinity();

struct neighbor {
	vertex_t target;
	weight_t weight;
	neighbor(vertex_t arg_target, weight_t arg_weight)
		: target(arg_target), weight(arg_weight) { }
};

typedef vector<vector<neighbor> > adjacency_list_t;


void DijkstraComputePaths(vertex_t source,
	const adjacency_list_t& adjacency_list, vector<weight_t>& min_distance,
	vector<vertex_t>& previous) {
	int n = adjacency_list.size();
	min_distance.clear();
	min_distance.resize(n, max_weight);
	min_distance[source] = 0;
	previous.clear();
	previous.resize(n, -1);
	set<pair<weight_t, vertex_t> > vertex_queue;
	vertex_queue.insert(make_pair(min_distance[source], source));

	while (!vertex_queue.empty()) {
		weight_t dist = vertex_queue.begin()->first;
		vertex_t u = vertex_queue.begin()->second;
		vertex_queue.erase(vertex_queue.begin());

		const vector<neighbor>& neighbors = adjacency_list[u];
		for (vector<neighbor>::const_iterator neighbor_iter = neighbors.begin();
			neighbor_iter != neighbors.end();  neighbor_iter++) {
			vertex_t v = neighbor_iter->target;
			weight_t weight = neighbor_iter->weight;
			weight_t distance_through_u = dist + weight;
			if (distance_through_u < min_distance[v]) {
				vertex_queue.erase(make_pair(min_distance[v], v));

				min_distance[v] = distance_through_u;
				previous[v] = u;
				vertex_queue.insert(make_pair(min_distance[v], v));
			}
		}
	}
}


list<vertex_t> DijkstraGetShortestPathTo(vertex_t vertex,
	const vector<vertex_t>& previous) {
	list<vertex_t> path;
	for (; vertex != -1; vertex = previous[vertex])
		path.push_front(vertex);
	return path;
}


int main() {
	int numberOfCityes, startCity, endCity, countRoads, firstCity, secondCity, distance;
	fstream input("input.txt");
	ofstream output("output.txt");
	input >> numberOfCityes >> countRoads >> startCity >> endCity;
	adjacency_list_t adjacency_list(numberOfCityes+1);
	while (!input.eof()) {
		input >> firstCity >> secondCity >> distance;
		adjacency_list[firstCity].push_back(neighbor(secondCity, distance));
		adjacency_list[secondCity].push_back(neighbor(firstCity, distance));
	}
	vector<weight_t> min_distance;
	vector<vertex_t> previous;
	DijkstraComputePaths(startCity, adjacency_list, min_distance, previous);
	if (min_distance[endCity] == numeric_limits<double>::infinity()) {
		output << "No" << endl;
	}
	else {
		output << min_distance[endCity] << endl;
		list<vertex_t> path = DijkstraGetShortestPathTo(endCity, previous);
		copy(path.begin(), path.end(), ostream_iterator<vertex_t>(output, " "));
		output << endl;
	}
	input.close();
	output.close();
	return 0;
}