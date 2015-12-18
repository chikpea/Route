/*
 * RoadNetwork.h
 *
 *  Created on: 14-Dec-2015
 *      Author: asitm9
 */

#ifndef ROADNETWORK_H_
#define ROADNETWORK_H_

#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<cstring>

#include "Way.h"


class Way;
class Way;
class Node{
    public:
        long long osmId;

        double lat;
        double lon;
        Node( long long id=-1, double lat=0, double lon=0 );
};

class Arc{
    public:
        Arc(long long headNodeId, int cost);

        long long headNodeId;
        int cost;
};

class RoadNetwork {
    public:
        RoadNetwork();

        std::string asString();
        //void addNode(long long osmId, double lat, double lng);
        void addNode(Node* node);
        void addEdge( Node* src, Node* dst );

		void addWay( Way* way );
		void spitWay();

        void readFromosmFile( RoadNetwork& r_Net, char* filename );
        long long getNumberOfNodes();
        Node* findNode( long long nodeRefId ) const;

    public:
        long long numNodes ;
        long long numEdges ;

        // the adjacency lists. Note that each edge {u,v} is stored as two arcs:
        //(u,v) and (v,u) . The total number of entries in these arrays is therefore exactly twice
        // the number of edges in the graph.

        std::map < long long, std::vector<Arc> > adjacentArcs;
        //std::vector<Node*> nodes;
        std::vector<Way*> ways;
        std::map<long long, Node* > m_Nodes;

};



#endif /* ROADNETWORK_H_ */
