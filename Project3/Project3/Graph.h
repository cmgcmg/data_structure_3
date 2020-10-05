#ifndef GRAPH_H
#define GRAPH_H

#include "Vertex.h"
#include "Edge.h"

#include <fstream>
#include <vector>

class Graph
{
private:
    // the head pointer for the linked list of the vertics
    Vertex* m_pVHead;
    // the number of the vertics
    int m_vSize;

public:
	Graph(); //Constructor
    ~Graph(); //Destructor

    void AddVertex(int vertexKey); // Add vertex with vertexNum at the end of the linked list for the vertics
    // add edge from the vertex which the number is startVertexKey to the vertex which the number is endVertexKey
	// [startVertexKey] ---weight---> [endVertexKey]
    void AddEdge(int startVertexKey, int endVertexKey, int weight);
    Vertex* FindVertex(int key); /// Get the vertex which the key is vertexNum
    int Size() const; // Get the number of the vertics
    void Clear(); // Memory free for the vertics

	// print out the graph as matrix form
	// file stream for the result log
    void Print(std::ofstream& fout);
	// check whether the graph has negative edge or not.
	// true if the graph has negative edge.
	// false otherwise.
    bool IsNegativeEdge();
    // find the path from startVertexKey to endVertexKey with DFS (stack)
    // the start vertex key
    // the end vertex key
    // the key list of the vertics which are included in the path<para/>
    // the last element should be the total cost<para/>
    // for the special case, it would be others
    std::vector<int> FindPathDfs(int startVertexKey, int endVertexKey);
     /*<summary>
     find the shortest path from startVertexKey to endVertexKey with Dijkstra using std::set
     </summary>
    
     <param name="startVertexKey">
     the start vertex key
     </param>
     <param name="endVertexKey">
     the end vertex key
     </param>
    
     <returns>
     the key list of the vertics which are included in the shortest path<para/>
     the last element should be the total cost<para/>
     for the special case, it would be others
     </returns>*/
    std::vector<int> FindShortestPathDijkstraUsingSet(int startVertexKey, int endVertexKey);
    /// <summary>
    /// find the shortest path from startVertexKey to endVertexKey with Dijkstra using MinHeap
    /// </summary>
    ///
    /// <param name="startVertexKey">
    /// the start vertex key
    /// </param>
    /// <param name="endVertexKey">
    /// the end vertex key
    /// </param>
    ///
    /// <returns>
    /// the key list of the vertics which are included in the shortest path<para/>
    /// the last element should be the total cost<para/>
    /// for the special case, it would be others
    /// </returns>
    std::vector<int> FindShortestPathDijkstraUsingMinHeap(int startVertexKey, int endVertexKey);
    /// <summary>
    /// find the shortest path from startVertexKey to endVertexKey with Bellman-Ford
    /// </summary>
    ///
    /// <param name="startVertexKey">
    /// the start vertex key
    /// </param>
    /// <param name="endVertexKey">
    /// the end vertex key
    /// </param>
    ///
    /// <returns>
    /// the key list of the vertics which are included in the shortest path<para/>
    /// the last element should be the total cost<para/>
    /// for the special case, it would be others
    /// </returns>
    std::vector<int> FindShortestPathBellmanFord(int startVertexKey, int endVertexKey);
};

#endif