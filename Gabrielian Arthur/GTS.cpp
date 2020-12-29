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

ostream& operator << (ostream& out, const GTS& gts)
{
	out << "The amount of pipes - " << gts.pGroup.size() << "\n";
	for (const pair<int, Pipe>& p : gts.pGroup)
	{
		out << "Pipe " << p.first << ".\n";
		out << p.second;
	}
	out << "The amount of CS - " << gts.csGroup.size() << "\n";
	for (const pair<int, CS>& cs : gts.csGroup)
	{
		out << "Compressor station " << cs.first << ".\n";
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
		proverka2(id, "Type ID: ");
		if (id == 0)
		{
			cout << "You have exited ID search mode.\n";
			return -1;
		}
		else if (objGroup.count(id))
		{
			return id;
		}
		cout << "There is no such ID. Please enter an existing ID.\n";
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
		cout << "The graph has a cycle, no further action is possible!\n";
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
	printf("The shortest paths:\n");
	for (int i = 0; i < N; i++)
		if (D[i] != INT_MAX)
		{
			cout << indexVertexes[start] << " -> " << indexVertexes[i] << " = " << D[i] << '\n';
			cout << "   The path lies through the vertices: ";
			WritePath(T, start, i, indexVertexes);
			cout << '\n';
		}
		else
		{
			cout << "The path " << indexVertexes[start] << " -> " << indexVertexes[i] << " doesn't exist\n";
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
	proverka2(start, "Type ID CS, from which you need to calculate the paths (0 - exit): ");
	if (invertIndexVertexes.find(start) != invertIndexVertexes.end())
		start = invertIndexVertexes[start];
	else
	{
		cout << "CS doesn't exist in the network!!";
		return;
	}
	Dijkstra(graph, n, start, indexVertexes);
}

void GTS::EditPipe()
{
	int id = GetInputId(pGroup);
	if (id != -1)
		pGroup[id].Edit();
}

void GTS::EditCs()
{
	int id = GetInputId(csGroup);
	if (id != -1)
	{
		cout << "\nWhat do you want to do with CS?\n"
			<< "1 - Change the number of working workshops\n"
			<< "0 and etc. - Exit\n";
		int input;
		proverka2(input, "Enter: ");
		switch (input)
		{
		case 1:
			csGroup[id].Edit_CS();
			break;
		default:
			cout << "You are out of editing mode.";
			break;
		}
	}
}


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

void GTS::DeletePipe()
{
	int id = GetInputId(pGroup);
	if (id != -1)
	{
		pGroup.erase(id);
		cout << "The pipe successfully deleted!\n";
	}
}

void GTS::DeleteCs()
{
	int id = GetInputId(csGroup);
	if (id != -1)
	{
		csGroup.erase(id);
		cout << "CS successfully deleted!\n";
	}
}


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
			cout << indexVertexes[Stack.top()] << " -> CS ";
			Stack.pop();
		}
	}
}


void GTS::ConnectPipe()
{
	int id = GetInputId(pGroup);
	if (id != -1)
	{
		cout << "CS from which the pipe comes out:\n";
		int outCsId = GetInputId(csGroup);
		cout << "CS from which the pipe comes in:\n";
		int inCsId = GetInputId(csGroup);
		while (inCsId == outCsId)
		{
			cout << "The pipe cannot enter the same CS! Enter another ID:\n";
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
		cout << "Exiting the pipe-to-CS communication mode...\n";
	}
}

void GTS::DisconnectPipe()
{
	int id = GetInputId(pGroup);
	if (id != -1)
	{
		pGroup[id].startid = -1;
		pGroup[id].endid = -1;
	}
	else
	{
		cout << "Exiting the pipe-to-CS communication mode...\n";
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
	proverka2(start, "Enter the ID of the CS from which the stream will come: ");
	if (invertIndexVertexes.find(start) != invertIndexVertexes.end())
		start = invertIndexVertexes[start];
	else
	{
		cout << "CS doesn't exist in the network";
		return;
	}
	int end;
	proverka2(end, "Enter the ID of the CS to which the stream will come: ");
	if (invertIndexVertexes.find(end) != invertIndexVertexes.end())
		end = invertIndexVertexes[end];
	else
	{
		cout << "CS doesn't exist in the network";
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
	cout << "Maximum flow: " << maxflow << endl;
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
			cout << "CS " << p.second.startid << " -> Pipe " << p.first << " -> CS " << p.second.endid << '\n';
}


GTS::GTS() { }