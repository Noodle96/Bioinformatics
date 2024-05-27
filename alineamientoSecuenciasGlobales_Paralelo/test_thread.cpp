/*
	^ Compile : g++ -O2 -std=c++11 -pthread hello_world.cpp -o hello_world
	^ Run: ./a.out
*/
#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include <cstdint>
#include <vector>
#include <thread>
using namespace std;

const uint64_t num_threads = 4;
std::vector<thread> threads;
std::vector<std::vector<int>> matrix(4, std::vector<int>(3));

void say_hello(uint64_t id);
void procesarArchivo(const std::string &nombreArchivo)
{
	cout << "nameFile: " << nombreArchivo << endl;
	ifstream archivo(nombreArchivo);
	string linea;
	if (archivo.is_open())
	{
		while (std::getline(archivo, linea))
		{
			// istringstream ss(linea);
			// cout << "[" << nombreArchivo << "] " << linea << endl;
		}
		archivo.close();
	}
	else
	{
		std::cerr << "Error al abrir el archivo" << nombreArchivo << std::endl;
	}
}

void solve(){
	// print matriz
	cout << "print matriz" << endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	cout << "print by diagonales" << endl;
	vector<pair<int, int>> indices;
	// row
	for (int e = 0; e < 4; e++){
		int col = 0;
		int e_ = e;
		while (1){
			indices.push_back({e_, col});
			if (e_ == 0 || col == 2) break;
			e_--; col++;
		}
		cout << "print indices row" << endl;
		for(auto e: indices){
			cout << e.first << " " << e.second << endl;
		}cout << endl;
		indices.clear();
	}

	//col
	for(int j = 1; j < 3; j++){
		int row = 3;
		int j_ = j;
		while(1){
			indices.push_back({row,j_});
			if(row == 0 || j_ == 2) break;
			row--; j_++;
		}
		cout << "print indices col" << endl;
		for(auto e: indices){
			cout << e.first << " " << e.second << endl;
		}cout << endl;
		indices.clear();
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
#ifdef DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			matrix[i][j] = 100 + i * 3 + j;
		}
	}

	solve();

	// for (uint64_t id = 0; id < num_threads; id++)
	// {
	// 	string nameArchivo = "data/archivo_part_" + to_string(id) + ".txt";
	// 	threads.emplace_back(procesarArchivo, nameArchivo);
	// }

	// // join each thread at the end
	// for (auto &thread : threads)
	// 	thread.join();
}

void say_hello(uint64_t id)
{
	std::cout << "Hello from thread: " << id << std::endl;
}
