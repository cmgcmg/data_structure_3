#include "Manager.h"
#include <cstring>
#include <iostream>
using namespace std;
#pragma warning (disable:4996)
#pragma warning (disable:4101)
#define _CRT_SECURE_NO_WARNINGS

Manager::~Manager()
{
    if (fout.is_open())
        fout.close();

    if (ferr.is_open())
        ferr.close();
}

void Manager::Run(const char* filepath)
{
    fout.open(RESULT_LOG_PATH);
    ferr.open(ERROR_LOG_PATH);

	char LoadData[128] = { 0 }; // Command Data 
	char Command[64] = { 0 }; // Command
	char *arg1 = NULL; // Arguments
	char *arg2 = NULL; // Arguments
	char *cpy_arg2 = NULL; //Copy Arguments
	char cpy_arg[64] = { 0 }; //Copy Arguments for Arguments Count
	int arg_Count = 0;	//Arguments Count

	ifstream fin;
	fin.open(filepath); //filepath open

	//File open fail,
	if (!fin)
	{
		PrintError(CommandFileNotExist);
		fout << "====== SYSTEM ======" << endl;
		fout << "CommandFileNotExist" << endl;
		fout << "=====================" << endl;
		fout.close();
		ferr.close(); //file close
		return; //exit
	}

	//File open success,
	while (!fin.eof())
	{
		fin.getline(LoadData, 128);
		arg_Count = 0;
		strcpy(cpy_arg, LoadData); //Copy cpy_arg to LoadData

		if (strlen(LoadData) == 0) break; // Command is Not Exist

		cpy_arg2 = strtok(cpy_arg, " ");

		if (cpy_arg == NULL) arg_Count = 0;

		else
		{	
			//Couting arg count
			for (int i = 0; strtok(NULL, " ") != NULL; i++) arg_Count = arg_Count + 1;
		}

		//Get command
		strcpy(Command, strtok(LoadData, " "));

		//Command is LOAD
		if (strcmp(Command, "LOAD") == 0)
		{			
			arg1 = strtok(NULL, " "); //arg1 is filename

			PrintError(Load(arg1)); //LOAD
		}
		//Command is PRINT
		else if (strcmp(Command, "PRINT") == 0)
		{
			PrintError(Print()); //PRINT
		}
		//Command is DFS
		else if (strcmp(Command, "DFS") == 0)
		{	
			if (arg_Count < 2) //Lack arg count
			{
				PrintError(VertexKeyNotExist);
				fout << "====== DFS ======" << endl;
				fout << "VertexKeyNotExist" << endl;
				fout << "=================" << endl;	
			}

			if (arg_Count == 2)
			{
				arg1 = strtok(NULL, " "); //arg1 is startVertexKey
				arg2 = strtok(NULL, " "); //arg2 is endVertexKey
				PrintError(FindPathDfs(atoi(arg1), atoi(arg2))); //Call FindPathDfs
			}
		}
		//Command is DIJKSTRA
		else if (strcmp(Command, "DIJKSTRA") == 0)
		{	
			if (arg_Count < 2) //Lack arg count
			{	
				fout << "====== DIJKSTRA ======" << endl;
				fout << "VertexKeyNotExist" << endl;
				fout << "======================" << endl;
				PrintError(VertexKeyNotExist);
			}

			if (arg_Count == 2)
			{
				arg1 = strtok(NULL, " "); //arg1 is startVertexKey
				arg2 = strtok(NULL, " "); //arg2 is endVertexKey
				PrintError(FindShortestPathDijkstraUsingSet(atoi(arg1), atoi(arg2))); //Call FindShortestPathDijkstraUsingSet
			}
		}
		//Command is DIJKSTRAMIN
		else if (strcmp(Command, "DIJKSTRAMIN") == 0)
		{
			if (arg_Count < 2) //Lack arg count
			{
				fout << "====== DIJKSTRAMIN ======" << endl;
				fout << "VertexKeyNotExist" << endl;
				fout << "=========================" << endl;
				PrintError(VertexKeyNotExist);
			}

			if (arg_Count == 2)
			{
				arg1 = strtok(NULL, " "); //arg1 is startVertexKey
				arg2 = strtok(NULL, " "); //arg2 is endVertexKey
				PrintError(FindShortestPathDijkstraUsingMinHeap(atoi(arg1), atoi(arg2))); //Call FindShortestPathDijkstraUsingMinHeap
			}
		}
		//Command is BELLMANFORD
		else if (strcmp(Command, "BELLMANFORD") == 0)
		{	
			if (arg_Count < 2)
			{
				fout << "====== BELLMANFORD ======" << endl;
				fout << "VertexKeyNotExist" << endl;
				fout << "=========================" << endl;
				PrintError(VertexKeyNotExist);
			}

			if (arg_Count == 2)
			{
				arg1 = strtok(NULL, " "); //arg1 is startVertexKey
				arg2 = strtok(NULL, " "); //arg2 is endVertexKey
				PrintError(FindShortestPathBellmanFord(atoi(arg1), atoi(arg2))); //Call FindShortestPathBellmanFord
			}
		}
		//Command is Not Exist
		else
		{	
			fout << "====== " << Command << " ======" << endl;
			fout << "NonDefinedCommand" << endl;
			fout << "====================" << endl;
			PrintError(NonDefinedCommand);
		}
	}

	fin.close(); // file close

}

void Manager::PrintError(Result result)
{
    ferr << "Error code: " << result << std::endl;
}

/// <summary>
/// make a graph
/// </summary>
///
/// <param name="filepath">
/// the filepath to read to make the graph
/// </param>
///
/// <returns>
/// Result::Success if load is successful.
/// Result::LoadFileNotExist if file is not exist.
/// </returns>
Result Manager::Load(const char* filepath)
{
	
	ifstream fin;
	fin.open(filepath);

	//File Open Fail
	if (!fin)
	{
		PrintError(LoadFileNotExist);
		fout << "====== LOAD ======" << endl;
		fout << "LoadFileNotExist" << endl;
		fout << "====================" << endl;
		return LoadFileNotExist; //return Error
	}

	//File Open Success
	char LoadData[256] = { 0 };
	int StartVertex = 0;
	int Weight = 0;
	int VertexCount = 0;

	fin.getline(LoadData, 256);
	VertexCount = atoi(LoadData); //Map Size

	//Until End of File
	while (!fin.eof())
	{
		fin.getline(LoadData, 256);

		if (strlen(LoadData) == 0) break; //End of File

		for (int EndVertex = 0; EndVertex < VertexCount; EndVertex++)
		{
			if (EndVertex == 0) Weight = atoi(strtok(LoadData, " "));
			else Weight = atoi(strtok(NULL, " "));

			m_graph.AddVertex(StartVertex);
			if (Weight != 0) m_graph.AddEdge(StartVertex, EndVertex, Weight);
		}

		StartVertex = StartVertex + 1;
	}

	fout << "====== LOAD ======" << endl;
	fout << "Success           " << endl;
	fout << "==================" << endl;
	return Success;
}
/// <summary>
/// print out the graph as matrix form
/// </summary>
///
/// <returns>
/// Result::Success if the printing is successful
/// Result::GraphNotExist if there is no graph
/// </returns>
Result Manager::Print()
{	
	//graph is Not Exist
	if (m_graph.Size() == 0)
	{	
		fout << "====== PRINT ======" << endl;
		fout << "GraphNotExist" << endl;
		fout << "====================" << endl;
		return GraphNotExist;
	}

	//Call Print function
	m_graph.Print(fout);
    // TODO: implement
	return Success;
}
/// <summary>
/// find the path from startVertexKey to endVertexKey with DFS (stack)
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
/// Result::InvalidVertexKey or Result::GraphNotExist or Result::InvalidAlgorithm if an exception has occurred.
/// Result::Success otherwise.
/// </returns>
Result Manager::FindPathDfs(int startVertexKey, int endVertexKey)
{
    //Graph is Not Exist
	if (m_graph.Size() == 0)
	{	
		fout << "====== DFS ======" << endl;
		fout << "GraphNotExist" << endl;
		fout << "=================" << endl;
		return GraphNotExist;
	}

	//StartVertex is Not Exist or EndVertex is Not Exist
	if (m_graph.FindVertex(startVertexKey) == NULL || m_graph.FindVertex(endVertexKey) == NULL)
	{	
		fout << "====== DFS ======" << endl;
		fout << "InvalidVertexKey" << endl;
		fout << "=================" << endl;
		return InvalidVertexKey;
	}
	//NegativeEdge is Exist
	if (m_graph.IsNegativeEdge())
	{	
		fout << "====== DFS ======" << endl;
		fout << "InvalidAlgorithm" << endl;
		fout << "=================" << endl;
		return InvalidAlgorithm;
	}
	//result is result of DFS
	vector<int> result = m_graph.FindPathDfs(startVertexKey, endVertexKey);

	fout << "====== DFS ======" << endl;

	//Write
	int Size = result.size();

	for (int i = 0; i < Size; i++)
	{
		fout << result[i] << " ";
	}

	fout << endl << "=================" << endl;

	result.clear();

	return Success;
}
/// <summary>
/// find the shortest path from startVertexKey to endVertexKey with Dijkstra using std::set
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
/// Result::InvalidVertexKey or Result::GraphNotExist or Result::InvalidAlgorithm if an exception has occurred.
/// Result::Success otherwise.
/// </returns>
Result Manager::FindShortestPathDijkstraUsingSet(int startVertexKey, int endVertexKey)
{
	//Graph is Not Exist
	if (m_graph.Size() == 0)
	{
		fout << "====== DIJKSTRA ======" << endl;
		fout << "GraphNotExist" << endl;
		fout << "======================" << endl;
		return GraphNotExist;
	}
	//StartVertex is Not Exist or EndVertex is Not Exist
	if (m_graph.FindVertex(startVertexKey) == NULL || m_graph.FindVertex(endVertexKey) == NULL)
	{	
		fout << "====== DIJKSTRA ======" << endl;
		fout << "InvalidVertexKey" << endl;
		fout << "======================" << endl;
		return InvalidVertexKey;
	}
	//NegativeEdge is Exist
	if (m_graph.IsNegativeEdge())
	{	
		fout << "====== DIJKSTRA ======" << endl;
		fout << "InvalidAlgorithm" << endl;
		fout << "======================" << endl;
		return InvalidAlgorithm;
	}

	//result is result of FindShortestPathDijkstraUsingSet
	vector<int> result = m_graph.FindShortestPathDijkstraUsingSet(startVertexKey, endVertexKey);

	fout << "====== DIJKSTRA ======" << endl;

	//Write
	int Size = result.size();

	for (int i = 0; i < Size; i++)
	{
		fout << result[i] << " ";
	}
	
	fout << endl << "======================" << endl;

	result.clear();

	return Success;
}
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
/// Result::InvalidVertexKey or Result::GraphNotExist or Result::InvalidAlgorithm if an exception has occurred.
/// Result::Success otherwise.
/// </returns>
Result Manager::FindShortestPathDijkstraUsingMinHeap(int startVertexKey, int endVertexKey)
{
	//Graph is Not Exist
	if (m_graph.Size() == 0)
	{
		fout << "====== DIJKSTRAMIN ======" << endl;
		fout << "GraphNotExist" << endl;
		fout << "=========================" << endl;
		return GraphNotExist;
	}
	//StartVertex is Not Exist or EndVertex is Not Exist
	if (m_graph.FindVertex(startVertexKey) == NULL || m_graph.FindVertex(endVertexKey) == NULL)
	{
		fout << "====== DIJKSTRAMIN ======" << endl;
		fout << "InvalidVertexKey" << endl;
		fout << "=========================" << endl;
		return InvalidVertexKey;
	}
	//NegativeEdge is Exist
	if (m_graph.IsNegativeEdge())
	{
		fout << "====== DIJKSTRAMIN ======" << endl;
		fout << "InvalidAlgorithm" << endl;
		fout << "=========================" << endl;
		return InvalidAlgorithm;
	}
	//result is result of FindShortestPathDijkstraUsingMinHeap
	vector<int> result = m_graph.FindShortestPathDijkstraUsingMinHeap(startVertexKey, endVertexKey);

	fout << "====== DIJKSTRAMIN ======" << endl;

	//Write
	int Size = result.size();

	for (int i = 0; i < Size; i++)
	{
		fout << result[i] << " ";
	}

	fout << endl << "=========================" << endl;

	result.clear();

	return Success;
}
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
/// Result::InvalidVertexKey or Result::GraphNotExist or Result::NegativeCycleDetected if exception has occurred.
/// Result::Success otherwise.
/// </returns>
Result Manager::FindShortestPathBellmanFord(int startVertexKey, int endVertexKey)
{
	//Graph is Not Exist
	if (m_graph.Size() == 0)
	{
		fout << "====== BellmanFord ======" << endl;
		fout << "GraphNotExist" << endl;
		fout << "=========================" << endl << endl << endl;
		return GraphNotExist;
	}
	//StartVertex is Not Exist or EndVertex is Not Exist
	if (m_graph.FindVertex(startVertexKey) == NULL || m_graph.FindVertex(endVertexKey) == NULL)
	{
		fout << "====== BellmanFord ======" << endl;
		fout << "InvalidVertexKey" << endl;
		fout << "=========================" << endl << endl << endl;
		return InvalidVertexKey;
	}

	//result is result of FindShortestPathBellmanFord
	vector<int> result = m_graph.FindShortestPathBellmanFord(startVertexKey, endVertexKey);

	//NegativeCycle Detected
	if (result == (vector<int>)0)
	{
		fout << "====== BELLMANFORD ======" << endl;
		fout << "NegativeCycleDetected" << endl;
		fout << "=========================" << endl << endl << endl;

		result.clear();
		return NegativeCycleDetected;
	}
	
	//NegativeCycle Not Detected, WRITE result
	else
	{	
		int Size = result.size();

		fout << "====== BELLMANFORD ======" << endl;
		for (int i = 0; i < Size; i++)
		{
			fout << result[i] << " ";
		}
		fout << endl << "=========================" << endl;

		result.clear();
		return Success;
	}
}