

#include<cstdio>
#include<vector>
#include<string>
#include<iostream>
#include<string.h>
#include<expat.h>

#include "RoadNetwork.h"
#include "Way.h"
#include "DijkstrasAlgo.h"

// #include "DijkstrasAlgo.cpp"


int main(int argc, char **ar){
    RoadNetwork rn;
    char* fileName = ar[1];
    char* p = "/home/asitm9/Vehicle Routing/code/c/file.xml";
    fileName = ( fileName == NULL ) ? p : fileName ;
    // std::cout<< fileName;
    rn.readFromosmFile( rn, fileName );
    std::cout<<rn.getNumberOfNodes()<<std::endl;
    //std::cout<<"way size:"<<rn.ways.size()<<std::endl;
    rn.spitWay();
    //std::cout<<"Adjacent size:"<<rn.adjacentArcs.size()<<std::endl;
    for( std::map<long long, std::vector<Arc> >::iterator
    it=rn.adjacentArcs.begin(); it!=rn.adjacentArcs.end();
    it++ ){
		std::vector<Arc> arc = it->second;
		if( arc.size() > 0 )
			std::cout<<"connected pts size:-"<<arc.size()<<"\n";

		for( std::vector<Arc>::iterator cp = arc.begin();
		cp!=arc.end(); cp++){
			Arc a = *cp;
			std::cout<<rn.m_Nodes[a.headNodeId]->lat<<"--"<<a.cost<<"\n";
		}


	//break;
	}
    DijkstrasAlgo da( rn );
    da.computeShortestPath( 1, 1 );

    return 0;
}


//g++ -w -g testit.cpp  -lexpat -o testit.o
//./testit.o /home/asitm9/Vehicle\ Routing/code/c/kolkata.osm
///home/asitm9/Vehicle\ Routing/code/c/kolkata.osm

