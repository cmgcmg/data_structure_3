#ifndef VERTEX_H
#define VERTEX_H

#ifndef NULL
#define NULL	0
#endif

#include "Edge.h"

class Vertex
{
private:
    // the key of this vertex
    int m_key;
    // the number of the edges from this vertex to others
    int m_size;
    // the head pointer for the linked list of the edges
    Edge* m_pEHead;
    // the next pointer for the linked list of the vertics
    Vertex* m_pNext;

public:
    Vertex(); //Constructor
    Vertex(int key); //Constructor with Parameter
    ~Vertex(); //Destructor

    void SetNext(Vertex* pNext); // Set the next pointer of this vertex
    int GetKey() const; // Get the key of this vertex
    Vertex* GetNext() const; // Get the next pointer of this vertex
    int Size() const; // Get the number of the edges
    void AddEdge(int edgeKey, int weight); // Add edge with edgeNum at the end of the linked list for the edges
    Edge* GetHeadOfEdge() const; // Get the head pointer of the edge
    void Clear(); // Memory free for edges
};

#endif