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

using namespace std;
const int MAX_COUNT_ROADS = 1000000;

int main()
{
	int startCity, endCity, quantityOfCityes, quantityOfRoads, firstCity, secondCity, weightRoad;
	fstream input("input.txt");
	ofstream output("output.txt");
	input >> quantityOfCityes >> quantityOfRoads >> startCity >> endCity;
	vector<vector<int> > matrixWeight(quantityOfCityes, vector<int>(quantityOfCityes, 0));
	vector<int> minDistance(quantityOfCityes, MAX_COUNT_ROADS);
	vector<int> visitedPeacks(quantityOfCityes, 1); 
	int temp, minIndex, min;
	int resultWeight = 0;
	int begin_index = startCity - 1;
	while (!input.eof()) {
		input >> firstCity >> secondCity >> weightRoad;
		matrixWeight[firstCity - 1][secondCity - 1] = weightRoad;
		matrixWeight[secondCity - 1][firstCity - 1] = weightRoad;
	}
	minDistance[begin_index] = 0;
	do {
		minIndex = MAX_COUNT_ROADS;
		min = MAX_COUNT_ROADS;
		for (int i = 0; i < quantityOfCityes; i++)
		{ 
			if ((visitedPeacks[i] == 1) && (minDistance[i] < min))
			{
				min = minDistance[i];
				minIndex = i;
			}
		}
		if (minIndex != MAX_COUNT_ROADS)
		{
			for (int i = 0; i < quantityOfCityes; i++)
			{
				if (matrixWeight[minIndex][i] > 0)
				{
					temp = min + matrixWeight[minIndex][i];
					if (temp < minDistance[i])
					{
						minDistance[i] = temp;
					}
				}
			}
			visitedPeacks[minIndex] = 0;
		}
	} while (minIndex < MAX_COUNT_ROADS);
	vector<int> ver(quantityOfCityes); 
	int end = endCity - 1;
	ver[0] = end + 1;
	int k = 1;
	int weight = minDistance[end];
	bool isFirstTime = true;
	while (end != begin_index)
	{
		if (isFirstTime) {
			for (int i = 0; i < quantityOfCityes; i++) {
				if (matrixWeight[i][end] != 0)
				{
					int temp = weight - matrixWeight[i][end];
					if (temp == minDistance[i])
					{
						weight = temp;
						end = i;
						ver[k] = i + 1;
						k++;
					}
				}
			}
			isFirstTime = false;
		}
		else{
			end = begin_index;
		}
	}
	
	if (resultWeight == 0) {
		output << "No" << endl;
	}
	else {
		for (int i = 0; i < ver.size(); i++) {
			if (ver[i] != startCity) {
				resultWeight += matrixWeight[ver[i] - 1][ver[i + 1] - 1];
			}
			else {
				i = ver.size();
			}
		}
		output << resultWeight << endl; 
		for (int i = k - 1; i >= 0; i--)
			output << ver[i] << " ";
	}
	input.close();
	output.close();
	return 0;
}
