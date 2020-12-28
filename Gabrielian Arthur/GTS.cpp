#pragma once
#include "GTS.h"
#include "utils.h"
#include <queue>
unordered_map<int, Pipe> pGroup = unordered_map<int, Pipe>{};
unordered_map<int, CS> csGroup = unordered_map<int, CS>{};

GTS::GTS(ifstream& fin)
{
	pGroup.clear();
	csGroup.clear();
	int pSize;
	int csSize;
	fin >> pSize;
	fin >> csSize;
	fin >> Pipe::pMaxId;
	fin >> CS::csMaxid;
	while (pSize--)
	{
		int id;
		fin >> id;
		pGroup.insert(make_pair(id, Pipe(fin)));
	}
	while (csSize--)
	{
		int id;
		fin >> id;
		csGroup.insert(make_pair(id, CS(fin)));
	}
}

void GTS::SaveToFile(ofstream& fout)
{
	fout << pGroup.size() << '\n'
		<< csGroup.size() << '\n'
		<< Pipe::pMaxId << '\n'
		<< CS::csMaxid << '\n';
	for (pair<int, Pipe> p : pGroup)
	{
		fout << p.first << '\n';
		p.second.SaveToFile(fout);
	}
	for (pair<int, CS> cs : csGroup)
	{
		fout << cs.first << '\n';
		cs.second.SaveToFile(fout);
	}
}

ostream& operator << (ostream& out, const GTS& GTS)
{
	out << "Количество труб - " << GTS.pGroup.size() << "\n";
	for (const pair<int, Pipe>& p : GTS.pGroup)
	{
		out << "Труба " << p.first << ".\n";
		out << p.second;
	}
	out << "Количество КС - " << GTS.csGroup.size() << "\n";
	for (const pair<int, CS>& cs : GTS.csGroup)
	{
		out << "Компрессорная станция " << cs.first << ".\n";
		out << cs.second;
	}
	return out;
}

template <typename T>
int GetInputId(const unordered_map<int, T>& objGroup)
{
	int id;
	while (true)
	{
		proverka2(id, "Введите ID: ");
		if (id == 0)
		{
			cout << "Вы вышли из режима поиска по ID.\n";
			return -1;
		}
		else if (objGroup.count(id))
		{
			return id;
		}
		cout << "Такого ID не существует. Пожалуйста, введите существующий ID.\n";
	}
}

vector<vector<int>> GTS::GetEdgesAndVertexes(unordered_map<int, int>& indexVertexes, int& n)
{
	set<int> vertexes;
	for (const pair<int, Pipe>& p : pGroup)
		if (CanBeUsed(p.second))
		{
			vertexes.insert(p.second.startid);
			vertexes.insert(p.second.endid);
		}
	n = vertexes.size();
	unordered_map<int, int> invertIndexVertexes;
	int i = 0;
	for (const int& vertex : vertexes)
	{
		indexVertexes.insert(make_pair(i, vertex));
		invertIndexVertexes.insert(make_pair(vertex, i++));
	}
	vector<vector<int>> edges;
	edges.resize(n);
	for (const pair<int, Pipe>& p : pGroup)
		if (CanBeUsed(p.second))
			edges[invertIndexVertexes[p.second.startid]].push_back(invertIndexVertexes[p.second.endid]);
	return edges;
}

bool dfs(int v, vector<char>& cl, vector<int>& p, int& cycle_st, const vector<vector<int>>& edges) {
	cl[v] = 1;
	for (size_t i = 0; i < edges[v].size(); ++i) {
		int to = edges[v][i];
		if (cl[to] == 0) {
			p[to] = v;
			if (dfs(to, cl, p, cycle_st, edges))
				return true;
		}
		else if (cl[to] == 1) {
			cycle_st = to;
			return true;
		}
	}
	cl[v] = 2;
	return false;
}

bool HasCycle(vector<vector<int>>& edges, int n)
{
	vector<char> cl;
	vector<int> p;
	int cycle_st;
	p.assign(n, -1);
	cl.assign(n, 0);
	cycle_st = -1;
	for (int i = 0; i < n; ++i)
		if (dfs(i, cl, p, cycle_st, edges))
			break;
	if (cycle_st == -1)
	{
		return false;
	}
	else
	{
		cout << "Внимание! У графа есть цикл, дальнейшие действия невозможны!\n";
		return true;
	}
}

void topologicalSortUtil(int v, bool visited[], stack<int>& Stack, vector<vector<int>>& edges)
{
	visited[v] = true;

	vector<int>::iterator i;
	for (i = edges[v].begin(); i != edges[v].end(); ++i)
		if (!visited[*i])
			topologicalSortUtil(*i, visited, Stack, edges);

	Stack.push(v);
}

void WritePath(int* T, int Start, int Vertex, unordered_map<int, int> indexVertexes)
{
	if (Vertex != Start)
		WritePath(T, Start, T[Vertex], indexVertexes);
	cout << indexVertexes[Vertex] << ' ';
}

void Dijkstra(const vector<vector<int>>& G, int N, int start, unordered_map<int, int> indexVertexes)
{
	int min, index;
	int* D;
	int* V;
	int* T;
	V = (int*)malloc(N * sizeof(int));
	D = (int*)malloc(N * sizeof(int));
	T = (int*)malloc(N * sizeof(int));
	for (int i = 0; i < N; i++)
	{
		V[i] = 0;
		D[i] = INT_MAX;
		T[i] = -1;
	}
	T[start] = 0;
	D[start] = 0;
	for (int count = 0; count < N - 1; count++)
	{
		min = INT_MAX;
		for (int i = 0; i < N; i++)
			if ((V[i] == 0) && (D[i] <= min))
			{
				min = D[i];
				index = i;
			}
		V[index] = 1;
		for (int i = 0; i < N; i++)
			if ((V[i] == 0) && (G[index][i] != 0) && (D[index] != INT_MAX) && ((D[index] + G[index][i]) < D[i]))
			{
				D[i] = D[index] + G[index][i];
				T[i] = index;
			}

	}
	printf("Кратчайшие пути:\n");
	for (int i = 0; i < N; i++)
		if (D[i] != INT_MAX)
		{
			cout << indexVertexes[start] << " -> " << indexVertexes[i] << " = " << D[i] << '\n';
			cout << "   Путь лежит через вершины: ";
			WritePath(T, start, i, indexVertexes);
			cout << '\n';
		}
		else
		{
			cout << "Путь " << indexVertexes[start] << " -> " << indexVertexes[i] << " не существует\n";
		}
}

void GTS::FindShortestPath()
{
	set<int> vertexes;
	for (const pair<int, Pipe>& p : pGroup)
		if (CanBeUsed(p.second))
		{
			vertexes.insert(p.second.startid);
			vertexes.insert(p.second.endid);
		}
	int n = vertexes.size();
	unordered_map<int, int> invertIndexVertexes;
	unordered_map<int, int> indexVertexes;
	int i = 0;
	for (const int& vertex : vertexes)
	{
		indexVertexes.insert(make_pair(i, vertex));
		invertIndexVertexes.insert(make_pair(vertex, i++));
	}
	vector<vector<int>> graph;
	graph.resize(n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			graph[i].push_back(0);
	for (const pair<int, Pipe>& p : pGroup)
		if (CanBeUsed(p.second))
			graph[invertIndexVertexes[p.second.startid]][invertIndexVertexes[p.second.endid]] = p.second.GetLength();

	int start;
	proverka2(start, "Введите ID КС, из которой нужно посчитать пути (0 - выйти): ");
	if (invertIndexVertexes.find(start) != invertIndexVertexes.end())
		start = invertIndexVertexes[start];
	else
	{
		cout << "Ошибка! Такой КС нет в сети((";
		return;
	}
	Dijkstra(graph, n, start, indexVertexes);
}
//void GTS::UpdateIndex()
//{
//	int i = 0;
//	for (auto iter = IdIndexCS.begin(); iter != IdIndexCS.end(); iter++) {
//		iter->second = i;
//		++i;
//	}
//	i = 0;
//	for (auto iter = IdIndexPipe.begin(); iter != IdIndexPipe.end(); iter++) {
//		iter->second = i;
//	}
//}
//
//int GTS::GetCsIndex(int id) const
//{
//	return IdIndexCS.find(id)->second;
//}
//
//int GTS::GetCsId(int index) const
//{
//	for (auto iter = IdIndexCS.begin(); iter != IdIndexCS.end(); iter++) {
//		if (iter->second == index)
//			return iter->first;
//	}
//	return 0;
//}

void GTS::AddCS()
{
	CS cs;
	cin >> cs;
	csGroup.insert(make_pair(++CS::csMaxid, cs));
}

void GTS::AddPipe()
{
	Pipe p;
	cin >> p;
    pGroup.insert(make_pair(++Pipe::pMaxId, p));

}

//void GTS::ConnectEdges(unordered_map<int, CS>& mapCS, unordered_map<int, Pipe>& mapPipe)
//{
//	cout << "Enter start CS: " << endl;
//	int CSId1 = proverka(0, CS::GetMaxid());
//
//	//IdIndexCS.insert({ id, edges.size() - 1 });
//
//	cout << "Enter pipe" << endl;
//	int pipeId = proverka(0, Pipe::GetMaxid()); 
//
//	//IdIndexPipe.insert({ id, vertex.size() - 1 });
//
//	cout << "Enter end CS: " << endl;
//	int CSId2 = proverka(0, CS::GetMaxid());
//	mapPipe.find(pipeId)->second.SetStart(CSId1);
//	mapPipe.find(pipeId)->second.SetEnd(CSId2);
//	cout << "CS: " << CSId1 << " was connected with CS: " << CSId2 << " by Pipe with id: " << pipeId << endl;
//	//mapPipe.find(pipeId)->second.ChangeUsed();
//	is_changed = true;
//}
//
//
//void GTS::CreateAdjacencyMatrix(unordered_map<int, CS>& mapCS, unordered_map<int, Pipe>& mapPipe)
//{
//	int n = edges.size();
//	if (is_changed) {
//		UpdateIndex();
//		AdjacencyMatrix.clear();
//		AdjacencyMatrix.resize(n);
//		for (int i = 0; i < n; i++) {
//			AdjacencyMatrix[i].resize(n);
//			is_changed = false;
//		}
//	}
//	for (auto itr = mapPipe.begin(); itr != mapPipe.end(); itr++) {
//		if (itr->second.GetStart() != -1) {
//			AdjacencyMatrix[GetCsIndex(itr->second.GetStart())][GetCsIndex(itr->second.GetEnd())] = 1;
//		}
//	}
//	for (int i = 0; i < n; i++) {  
//		for (int j = 0; j < n; j++) {
//			cout << AdjacencyMatrix[i][j] << " ";
//		}
//		cout << endl;
//	}
//}
//
//void GTS::DeleteEdge(int id, unordered_map<int, Pipe>& mapPipe)
//{
//	is_changed = true;
//	edges.erase(id);
//	IdIndexCS.erase(id);
//
//	for (auto iter = mapPipe.begin(); iter != mapPipe.end(); iter++) {
//		if (iter->second.GetStart() == id || iter->second.GetEnd() == id) {
//			DeleteVertex(iter->first);
//			mapPipe.erase(iter->first);
//			break;
//		}
//	}
//}
//
//void GTS::DeleteVertex(int id)
//{
//	is_changed = true;
//	vertex.erase(id);
//	IdIndexPipe.erase(id);
//
//}

bool GTS::HasPipe() const
{
	return pGroup.size() != 0;
}

bool GTS::HasCs(int count) const
{
	return csGroup.size() >= count;
}

void GTS::TopologicalSort()
{
	unordered_map<int, int> indexVertexes;
	int n;
	vector<vector<int>> edges = GetEdgesAndVertexes(indexVertexes, n);
	if (HasCycle(edges, n) == false)
	{
		stack<int> Stack;

		bool* visited = new bool[n];
		for (int i = 0; i < n; i++)
			visited[i] = false;

		for (int i = 0; i < n; i++)
			if (visited[i] == false)
				topologicalSortUtil(i, visited, Stack, edges);

		while (Stack.empty() == false)
		{
			cout << "КС " << indexVertexes[Stack.top()] << " -> ";
			Stack.pop();
		}
	}
}


void GTS::ConnectPipe()
{
	int id = GetInputId(pGroup);
	if (id != -1)
	{
		cout << "КС, из которой выходит труба:\n";
		int outCsId = GetInputId(csGroup);
		cout << "КС, в которую входит труба:\n";
		int inCsId = GetInputId(csGroup);
		while (inCsId == outCsId)
		{
			cout << "Труба не может входить в ту же самую КС! Введите другой Id:\n";
			int inCsId = GetInputId(csGroup);
		}
		if (outCsId != -1 && inCsId != -1)
		{
			pGroup[id].startid = outCsId;
			pGroup[id].endid = inCsId;
		}
	}
	else
	{
		cout << "Выход из режима связи трубы с КС...\n";
	}
}

void GTS::DisonnectPipe()
{
	int id = GetInputId(pGroup);
	if (id != -1)
	{
		pGroup[id].startid = -1;
		pGroup[id].endid = -1;
	}
	else
	{
		cout << "Выход из режима связи трубы с КС...\n";
	}
}

void Enque(int x, vector<int>& q, int& tail, vector<int>& color)
{
	q[tail] = x;
	tail++;
	color[x] = 1;
}

int bfs(int start, int end, vector<int>& color, vector<int>& pred, vector<int>& q, vector<vector<int>>& capacity, vector<vector<int>>& flow, int n, int& head, int& tail)
{
	for (int u = 0; u < n; u++)
		color[u] = 0;

	head = 0;
	tail = 0;
	Enque(start, q, tail, color);
	pred[start] = -1;
	while (head != tail)
	{
		int u = q[head];
		head++;
		color[u] = 2;
		for (int v = 0; v < n; v++)
		{
			if (color[v] == 0 && (capacity[u][v] - flow[u][v]) > 0) {
				Enque(v, q, tail, color);
				pred[v] = u;
			}
		}
	}
	if (color[end] == 2)
		return 0;
	else return 1;
}

void GTS::FindMaxFlow()
{
	set<int> vertexes;
	for (const pair<int, Pipe>& p : pGroup)
		if (CanBeUsed(p.second))
		{
			vertexes.insert(p.second.startid);
			vertexes.insert(p.second.endid);
		}
	int n = vertexes.size();
	unordered_map<int, int> invertIndexVertexes;
	unordered_map<int, int> indexVertexes;
	int i = 0;
	for (const int& vertex : vertexes)
	{
		indexVertexes.insert(make_pair(i, vertex));
		invertIndexVertexes.insert(make_pair(vertex, i++));
	}
	vector<vector<int>> graph;
	graph.resize(n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			graph[i].push_back(0);
	for (const pair<int, Pipe>& p : pGroup)
		if (CanBeUsed(p.second))
			graph[invertIndexVertexes[p.second.startid]][invertIndexVertexes[p.second.endid]] = p.second.GetProductivity();

	int start;
	proverka2(start, "Введите ID КС, из которой будет идти поток: ");
	if (invertIndexVertexes.find(start) != invertIndexVertexes.end())
		start = invertIndexVertexes[start];
	else
	{
		cout << "Ошибка! Такой КС нет в сети((";
		return;
	}
	int end;
	proverka2(end, "Введите ID КС, в которую придёт поток: ");
	if (invertIndexVertexes.find(end) != invertIndexVertexes.end())
		end = invertIndexVertexes[end];
	else
	{
		cout << "Ошибка! Такой КС нет в сети((";
		return;
	}

	int head, tail;
	vector<vector<int>> flow;
	vector<int> color, pred, q;

	int maxflow = 0;
	flow.resize(n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			flow[i].push_back(0);
		color.push_back(-1);
		pred.push_back(-1);
		q.push_back(0);
	}
	q.push_back(0); q.push_back(0);
	while (bfs(start, end, color, pred, q, graph, flow, n, head, tail) == 0)
	{
		int delta = 10000;
		for (int u = end; pred[u] >= 0; u = pred[u])
		{
			delta = min(delta, (graph[pred[u]][u] - flow[pred[u]][u]));
		}
		for (int u = end; pred[u] >= 0; u = pred[u])
		{
			flow[pred[u]][u] += delta;
			flow[u][pred[u]] -= delta;
		}
		maxflow += delta;
	}
	cout << "Максимальный поток: " << maxflow << endl;
}


bool GTS::CanBeUsed(const Pipe& p) const
{
	return p.startid > 0 &&
		p.endid > 0 &&
		!p.GetStatus() &&
		csGroup.find(p.startid) != csGroup.end()
		&& csGroup.find(p.endid) != csGroup.end();
}

void GTS::ShowNetwork()
{
	for (const pair<int, Pipe>& p : pGroup)
		if (CanBeUsed(p.second))
			cout << "КС " << p.second.startid << " -- Труба " << p.first << " -> КС " << p.second.endid << '\n';
}
//void GTS::TopSort()
//{
//	vector<int> colors;
//	colors.resize(edges.size());
//	vector<int> TopSortedVector;
//	bool cycl = false;
//	for (int i = 0; i < edges.size(); i++) {
//		TopologicalSort(i, colors, cycl, TopSortedVector);
//	}
//	if (cycl) {
//		cout << "There is cycle" << endl;
//	}
//	else {
//		reverse(TopSortedVector.begin(), TopSortedVector.end());
//		cout << "Topological sort: " << endl;
//		for (int i = 0; i < TopSortedVector.size(); i++) {
//			cout << TopSortedVector[i] << " ";
//		}
//		cout << endl;
//	}
//}

GTS::GTS() { }