#pragma once
#include "Pipe.h"
#include "Compressor.h"
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include "utils.h"
#include <set>
#include <stack>
#include <iostream>


using namespace std;

class GTS
{
	//unordered_set<int> edges;
	//unordered_set<int> vertex; 
	//unordered_map<int, int> IdIndexCS;
	//unordered_map<int, int> IdIndexPipe;

	//vector<vector<int>> AdjacencyMatrix;
	//vector<vector<int>> IncidenceMatrix;

	unordered_map<int, Pipe> pGroup;
	unordered_map<int, CS> csGroup;

	vector<vector<int>> GetEdgesAndVertexes(unordered_map<int, int>& indexVertexes, int& n);
	bool is_changed;


public:
	GTS();
    GTS(ifstream& fin);
	friend ostream& operator << (ostream& out, const GTS& GTS);
	void SaveToFile(ofstream& fout);
	bool HasPipe() const;
	bool HasCs(int count = 1) const;
	//void EditPipe();
	//void EditCs();
	//void DeletePipe();
	//void DeleteCs();
	//void SearchPipes();
	//void SearchCss();
	void ConnectPipe();
	void DisonnectPipe();
	bool CanBeUsed(const Pipe& p) const;
	void ShowNetwork();
	void FindMaxFlow();
	void FindShortestPath();
	void UpdateIndex();
	void AddCS();
	void AddPipe();
	//void CreateAdjacencyMatrix(unordered_map<int, CS>&, unordered_map<int, Pipe>&);
	void TopologicalSort();

	//void TopSort();

};

