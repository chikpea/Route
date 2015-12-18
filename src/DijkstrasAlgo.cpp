/*
 * DijkstrasAlgo.cpp
 *
 *  Created on: 17-Dec-2015
 *      Author: asitm9
 */

#include<iostream>
#include<vector>
#include<map>
#include<set>
#include<string>
#include<cstring>

#include "DijkstrasAlgo.h"
#include "RoadNetwork.h"

struct decreasingOrderMyType
{
    bool operator() (const Arc & lhs, const Arc & rhs) const
    {
        return lhs.cost > rhs.cost;
    }
};

using namespace boost::heap;


DijkstrasAlgo::DijkstrasAlgo(RoadNetwork &graph)
:graph(graph){}


int DijkstrasAlgo::computeShortestPath(long long srcId, long long dstId ){

	typedef boost::heap::priority_queue< Arc> MyPriQue;

	priority_queue< Arc, boost::heap::compare<decreasingOrderMyType> > pq;
	/*
	pq.push(2);
	pq.push(0);
	pq.push(1);
	std::cout<<pq.top();
	*
	for(MyPriQue::const_iterator it = pq.begin(); it != pq.end();++it){
		std::cout << *it << ' ';
	}

	*/


	std::cout << std::endl;

	Arc src = Arc( srcId, 0);
	pq.push( src );
	std::cout<<pq.top().cost;
	while( !pq.empty() ){
		if(visitedNodeMarks.count( pq.top().cost ) ){
			pq.pop();
		}
		else{
			Arc top = pq.top();
			std::vector<Arc> a_v = graph.adjacentArcs[top.headNodeId];
		}
	}

	return 0;
}

void DijkstrasAlgo::setVisitedNodemark(long long mark){
	visitedNodeMarks.insert( mark );
}




