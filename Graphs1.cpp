#include "graphs1.h"
#include <QDebug>

Graphs::Graphs(int cap)
{
	size = 1;
	capcity = cap;
    vertex = new int[capcity];
    edges = new  int* [capcity] ;
    for(int i = 0; i < capcity; i++) {
		edges[i] = new int[capcity];
    }
}	
 
void Graphs::add_vertex(int data)
{ 
	vertex[size] = data;
    qDebug() << vertex[size];
	for(int index = 0; index < capcity; index++) 
	{	
		edges[size][index] = -1;

	}
	size++;
}
	
void Graphs::add_edge(int data)
{
    edges[size-1][data]=1;
//    qDebug() << edges[size-1][data];
//    for (int i = 0; i < edges.size(); i++) {
//        for (int y = 0; y < edges[i].size(); y++) {
//            qDebug() << edges[i][y];
//        }
//    }
}	
	
Graphs::~Graphs()
{
	delete [] vertex;
	for(int i = 0; i < size; i++)
		delete [] edges[i];
	delete [] edges;
}
