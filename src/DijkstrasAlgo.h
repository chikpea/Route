/*
 * DijkstrasAlgo.h
 *
 *  Created on: 17-Dec-2015
 *      Author: asitm9
 */

#ifndef DIJKSTRASALGO_H_
#define DIJKSTRASALGO_H_

#include<iostream>
#include<vector>
#include<map>
#include<set>
#include<string>
#include<cstring>

#include <boost/heap/priority_queue.hpp>
#include <boost/heap/binomial_heap.hpp>


#include "RoadNetwork.h"

class DijkstrasAlgo {
public:
	DijkstrasAlgo(RoadNetwork &graph);

	int computeShortestPath(long long srcId, long long dstId );
	void setVisitedNodemark(long long mark);

private:
	RoadNetwork &graph;
	std::set<long long> visitedNodeMarks;
};



#endif /* DIJKSTRASALGO_H_ */
