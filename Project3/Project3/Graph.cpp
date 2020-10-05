#include "Graph.h"
#include "Stack.h"
#include "MinHeap.h"
#include <limits.h>
#include <set>
#include <tuple>
#include <iostream>
using namespace std;

#define DFS_FIRST_PATH

//Constructor
Graph::Graph()
{
	m_pVHead = NULL;
	m_vSize = 0;
}
//Destructor
Graph::~Graph()
{
	Clear();
}
// Add vertex with vertexNum at the end of the linked list for the vertics
void Graph::AddVertex(int vertexKey)
{
	Vertex* SearchVertex = FindVertex(vertexKey); //SearchVertex is NULL, Insert New Vertex

	if (SearchVertex != NULL) return; //SearchVertex is Already Exist, return

	Vertex* New_Vertex = new Vertex(vertexKey); //Create New Vertex with Parameter
	Vertex* CurVertex = m_pVHead; //CurVertex is Head of Vertex
	
	//Head of Vertex is Not Exist
	if (m_pVHead == NULL)
	{
		m_pVHead = New_Vertex; //Head of Vertex is New_Vertex
		m_vSize++; //Plus Vertex Size 

		New_Vertex = NULL;
		delete New_Vertex;
		return; //return
	}

	//Head of Vertex is Exist
	//CurVertex Point to the last Vertex
	while (CurVertex->GetNext() != NULL)
	{
		CurVertex = CurVertex->GetNext();
	}
	//Last Vertex -> New_Vertex
	CurVertex->SetNext(New_Vertex);

	m_vSize++; //Plus Vertex Size

	New_Vertex = NULL;
	delete New_Vertex;
}
// Add edge from the vertex which the number is startVertexKey to the vertex which the number is endVertexKey
void Graph::AddEdge(int startVertexKey, int endVertexKey, int weight)
{
	Vertex* SearchVertex = FindVertex(startVertexKey); //Find the vertex to be connected

	if (SearchVertex == NULL) return;

	SearchVertex->AddEdge(endVertexKey, weight); //Call AddEdge with endVertexKey, weight	
}
// Get the vertex which the key is vertexNum
Vertex* Graph::FindVertex(int key)
{
	//Vertex is Not Exist
	if (m_pVHead == NULL)
	{
		return NULL; //return NULL
	}

	//Vertex is Exist
	else
	{
		Vertex* Cur = m_pVHead; //Cur is Head Vertex

		//Search Vertex while Loop
		while (Cur != NULL)
		{
			if (Cur->GetKey() == key) return Cur; //return Find Vertex

			Cur = Cur->GetNext();
		}

		return NULL; //Not Find
	}
}
// Get the number of the vertics
int Graph::Size() const
{
	return m_vSize;
}
// Memory free for the vertics
void Graph::Clear()
{
	if (m_pVHead != NULL)
	{
		Vertex* pCur = m_pVHead;
		for (;;)   //until end position of Vertex list
		{   //Delete All Vertex at Graph
			pCur->Clear();   //Clear all Edge list connected with Vertex
			m_pVHead = pCur->GetNext();
			delete pCur;   //Delete Vertex
			m_vSize--;
			if (m_pVHead == NULL) break;
			pCur = m_pVHead;
		}
	}
}
// print out the graph as matrix form
// file stream for the result log
void Graph::Print(std::ofstream& fout)
{
	fout << "====== PRINT ======" << endl;

	Vertex* CurVertex = m_pVHead; //CurVertex is Head Vertex
	Edge* CurEdge = NULL;
		
	//Explore for all vertices
	while (CurVertex)
	{	
		CurEdge = NULL;

		//CurEdge is NULL or First Edge Connected
		if (CurVertex->GetHeadOfEdge() != NULL) CurEdge = CurVertex->GetHeadOfEdge();

		for (int i = 0; i < m_vSize; i++)
		{	
			//Not Exist Edge or Not Conneted Edge
			if (CurEdge == NULL || CurEdge->GetKey() != i)
			{
				fout << "0 ";
			}
			//Connected Edge
			else
			{
				if (i == CurEdge->GetKey())
				{
					fout << CurEdge->GetWeight() << " "; //Print Weight of Edge
					if (CurEdge->GetNext() != NULL) CurEdge = CurEdge->GetNext(); //CurEdge is Next Edge
				}

				else
				{
					fout << "0 ";
				}
			}
				
		}
		fout << endl;

		CurVertex = CurVertex->GetNext(); //CurVertex is Next CurVertex
	}
	fout << "===================" << endl;
}
// check whether the graph has negative edge or not.
// true if the graph has negative edge.
// false otherwise.
bool Graph::IsNegativeEdge()
{	
	Vertex* Cur = m_pVHead; //Cur is Head Vertex
	Edge* eCur = NULL; //eCur is Edge Pointer

	//explore for All Vertex
	while(Cur)
	{
		//Connected Edge is Exist
		if (Cur->GetHeadOfEdge() != NULL)
		{
			eCur = Cur->GetHeadOfEdge(); //eCur is Head Edge

			//explore for All Edge
			while (eCur)
			{
				if (eCur->GetWeight() < 0) return true; //Negative Weight, return true

				eCur = eCur->GetNext(); //eCur is Next Edge
			}
		}

		Cur = Cur->GetNext(); //Cur is Next Vertex
	}

	return false; //Not Negative Weight, return false
}
// find the path from startVertexKey to endVertexKey with DFS (stack)
std::vector<int> Graph::FindPathDfs(int startVertexKey, int endVertexKey)
{
	int Dist = 0; //for Total Cost
	Stack<pair<int, int>> s; //first Key is Vertex Key, second Key is Weight of Edge
	Vertex* Cur;  Edge* eCur; //Vertex, Edge Pointer
	vector<int> Path, Cost; //vector<int> for Path & Cost
	vector<bool> visited(m_vSize); //Visiting vector

	s.Push(make_pair(startVertexKey, 0)); //Push startVertexKey, Weight is 0

	while (!s.IsEmpty())
	{
		//Not Visit
		if (visited[s.Top().first] == false)
		{	
			visited[s.Top().first] = true; //Visit
			Path.push_back(s.Top().first); //Append Path Vector
			Cost.push_back(s.Top().second); //Append Cost Vector
			if (s.Top().first == endVertexKey) break; // Arrive EndVertexKey

			Cur = FindVertex(s.Top().first); //Cur is StartVertex
			eCur = Cur->GetHeadOfEdge(); //eCur is Connected to Edge

			while (eCur)
			{
				//if Not visit, Push VertexKey and Weight of connected to Edge
				if (!visited[eCur->GetKey()]) s.Push(make_pair(eCur->GetKey(), eCur->GetWeight()));

				//eCur is Next Edge
				eCur = eCur->GetNext();
			}
		}
		//Not Push or If the road is blocked
		//Look for unvisited Paths
		while (visited[s.Top().first] == true)
		{
			Path.pop_back(); //Pop Path
			Cost.pop_back(); //Pop Cost
			s.Pop(); //Pop Stack
		}
	}

	//Calculate Total Distance
	for (int i = 0; i < Cost.size(); i++)
	{
		Dist = Dist + Cost[i];
	}
	//Path + Total Distance
	Path.push_back(Dist);

	Cost.clear(); // Remove Cost Vector
	visited.clear(); // Remove visited vector
	s.~Stack(); // Destructor Stack

	return Path; //return Result
}
// find the shortest path from startVertexKey to endVertexKey with Dijkstra using std::set
std::vector<int> Graph::FindShortestPathDijkstraUsingSet(int startVertexKey, int endVertexKey)
{                                                   //Find shortest path using set
	vector<int> dist(m_vSize, INT_MAX); //Vector for managing distance of path
	vector<bool> visit(m_vSize, false); //Vector for check visit
	vector<int> path(m_vSize, -1);      //Vector for saving previous path
	vector<pair<int, int>> temp;      //Vector for shortest path

	vector<int> t_shortestPath;         //Vector for reverse path order
	vector<int> shortestPath;
	Vertex* pV; Edge* pE;

	dist[startVertexKey] = 0;         //Dist of start Vertex is 0
	pV = FindVertex(startVertexKey);   //pV is pointing the startvertex

	while (1)
	{
		visit[pV->GetKey()] = true;      //visit = true
		pE = pV->GetHeadOfEdge();

		//Check Edges
		while (pE)
		{
			//Update
			if (dist[pE->GetKey()] > dist[pV->GetKey()] + pE->GetWeight())   //Judge which distance is shorter, 
			{
				dist[pE->GetKey()] = dist[pV->GetKey()] + pE->GetWeight();   //Update shorter path
				path[pE->GetKey()] = pV->GetKey();                     //Save previous vertexs   
			}

			pE = pE->GetNext();         //Move to next edge
		}

		for (int i = 0; i < m_vSize; i++)            //Insert non-visited vertex into temp vector
		{
			if (visit[i] == false)
			{
				temp.push_back(make_pair(dist[i], i));
			}
		}
		if (temp.size() == 0) break;      //If vertexes are all visited, break.

		set<pair<int, int>> s(temp.begin(), temp.end()); //Insert non-visited vertexes with their data (weight, key)
														 //Using set, vertexes are sorted in ascending order.
		temp.clear();   //Clear temp path

		pV = FindVertex(s.begin()->second); //begin of the set is shortest weight edge.
	}

	int p = endVertexKey;

	while (p != -1) {      //Push vertexes in path, from end vertex 
		t_shortestPath.push_back(p);
		p = path[p];
	}

	while (t_shortestPath.size() != 0) {   //reverse the order.
		shortestPath.push_back(t_shortestPath.back());
		t_shortestPath.pop_back();
	}

	shortestPath.push_back(dist[endVertexKey]);   //Push total distance 
	return shortestPath;

}
// find the shortest path from startVertexKey to endVertexKey with Dijkstra using MinHeap
std::vector<int> Graph::FindShortestPathDijkstraUsingMinHeap(int startVertexKey, int endVertexKey)
{
	MinHeap<int, int> Heap; //Heap with VertexKey and Cost
	vector<int> dist(m_vSize, INT_MAX); // dist vector with Cost
	vector<int> prev(m_vSize, -1); // prev vector with Previous Edge
	pair<int, int> tmp; // for temporary storage

	Heap.Push(startVertexKey, 0); //Insert StartVertexKey and Cost(0)
	dist[startVertexKey] = 0; //Initialize Distance of startVertexKey

	//Until until set is empty
	while (!Heap.IsEmpty())
	{
		tmp = Heap.Top(); //tmp is Top of Heap
		Heap.Pop(); //Pop

		int u = tmp.first; //VertexKey of Top

		Vertex* Cur = FindVertex(u);
		Edge* eCur = Cur->GetHeadOfEdge(); //eCur is Edge connected to u

	    //For all connected Edge
		while (eCur)
		{
			int v = eCur->GetKey(); //v is the vertex of the connected edge
			int weight = eCur->GetWeight(); //weight is Cost of the connected edge

			//The part that modifies the short path
			if (dist[v] > dist[u] + weight)
			{
				if (dist[v] != INT_MAX)
				{
					Heap.Pop();
				}

				dist[v] = dist[u] + weight; //Dist Vector Update
				prev[v] = u; //Prev Vertor Update
				Heap.Push(v, dist[v]); //Push  VertexKey, Distance
			}

			eCur = eCur->GetNext(); //eCur is Next Edge
		}
	}

	Stack<int> s; //Stack with Path

	int temp = endVertexKey;

	s.Push(temp); //Push EndVertexKey

	//Obtain Path from endVertexKety by tracing backwards
    //Use Prev Vector
	while (temp != startVertexKey)
	{
		temp = prev[temp]; //tracing backwards used by prev vector
		s.Push(temp); //Push stack
	}

	prev.clear(); //Remove Prev Vector

	//push_back Path to prev Vector, Pop Stack
	while (!s.IsEmpty())
	{
		prev.push_back(s.Top()); //back
		s.Pop();
	}

	prev.push_back(dist[endVertexKey]); // Append Cost to Path

	s.~Stack(); //Remove Stack
	dist.clear(); //Remove dist Vector
	Heap.~MinHeap();

	return prev; //return Result
}
// find the shortest path from startVertexKey to endVertexKey with Bellman-Ford
std::vector<int> Graph::FindShortestPathBellmanFord(int startVertexKey, int endVertexKey)
{	
	vector<int> dist(m_vSize, INT_MAX); //Dist Vector Initialization with INT_MAX
	vector<int> path(m_vSize, -1); //Path Vector Initialization with -1

	Vertex* Cur; Edge* eCur;
	int u = startVertexKey; // u is VertexKey
	dist[u] = 0; //start Vertex Initialization

	//for Vertex Size
	for(int j = 0; j < m_vSize; j++)
	{	
		//Vertex proceed in order
		for (int k = 0; k < m_vSize; k++)
		{	
			Cur = FindVertex(k); //Cur is Key of Update Vertex 
			eCur = Cur->GetHeadOfEdge(); //eCur is Connected Edge
			u = Cur->GetKey(); // u is Vertex Key of Connected Edge

			while(eCur)
			{
				int v = eCur->GetKey(); // v is Vertex Key of Connected Edge
				int w = eCur->GetWeight(); // w is Cost of Connected Edge

				//Update Path
				if (dist[u] != INT_MAX && dist[v] > dist[u] + w)
				{
					dist[v] = dist[u] + w; // Distance Update for v
					path[v] = u; // Path Update for v
				}

				eCur = eCur->GetNext(); //eCur is Next Edge
			}
		}
	}
	//Step2, Detect Negative Edge
	//if Distance is Update, Negative Dected
	//Vertex proceed in order
	for (int j = 0; j < m_vSize; j++)
	{
		for (int k = 0; k < m_vSize; k++)
		{
			//for Update Vertex
			Cur = FindVertex(k); //Cur is Key of Update Vertex 
			eCur = Cur->GetHeadOfEdge(); //eCur is Connected Edge
			u = Cur->GetKey(); // u is Vertex Key of Connected Edge

			while (eCur)
			{
				int v = eCur->GetKey(); // v is Vertex Key of Connected Edge
				int w = eCur->GetWeight(); // w is Cost of Connected Edge

				//Negative Edge Detected
				if (dist[u] != INT_MAX && dist[v] > dist[u] + w)
				{
					return (vector<int>)0;
				}
				eCur = eCur->GetNext(); //eCur is Next Edge
			}
		}
	}

	Stack<int> s; //Stack with Path

	int temp = endVertexKey;

	s.Push(temp); //Push EndVertexKey

	//Obtain Path from endVertexKety by tracing backwards
    //Use Prev Vector
	while (temp != startVertexKey)
	{
		temp = path[temp]; //tracing backwards used by prev vector
		s.Push(temp); //Push stack
	}

	path.clear(); //Remove Prev Vector

	//push_back Path to prev Vector, Pop Stack
	while (!s.IsEmpty())
	{
		path.push_back(s.Top()); //back
		s.Pop();
	}

	path.push_back(dist[endVertexKey]); // Append Cost to Path

	s.~Stack(); //Remove Stack
	dist.clear(); //Remove dist Vector

	return path; //return Result
}