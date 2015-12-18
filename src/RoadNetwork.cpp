/*
 * RoadNetwork.cpp
 *
 *  Created on: 14-Dec-2015
 *      Author: asitm9
 */

#include<cstdio>
#include<vector>
#include<map>
#include<string>
#include<iostream>
#include<string.h>
#include<expat.h>

#include "RoadNetwork.h"
#include "math_functions.h"

/*
 * Guide to compile
 * g++ -w -g  driver.cpp -lexpat -o driver.o
 */

// using namespace std;

static Way* t_Way;

static void startElement( void *userData, const char *name, const char **atts ){


	RoadNetwork* r_Net = (RoadNetwork*) userData;
	if( strcmp( name, "node" )==0 ){

		if( atts!=NULL ){
			long long id = -1;
			double lat = 0;
			double lon = 0;
			const char **at = (const char**) atts;
			while( *at!=NULL ){
				const char *name = *at++;
				const char *val = *at++;

				if( strcmp( name, "id" )==0){
					id = atoll( val );
				}
				if( strcmp( name, "lat" )==0 ){
					lat = atof( val );
				}
				if( strcmp( name, "lon" )==0 ){
					lon = atof( val );
				}

			}
			r_Net->addNode( new Node( id, lat, lon ) );
		}

	}
	if( strcmp( name, "way" )==0 ){
		if( atts!=NULL ){
			long long id = -1;
			bool vis = false;
			const char **at = (const char**) atts;
			while( *at!=NULL ){
				const char *name = *at++;
				const char *val = *at++;

				if( strcmp( name, "id" )==0){
					id = atoll( val );
				}
				if( strcmp( name, "visible" )==0){
					vis = strcmp( val, "true" ) == 0;
				}
			}
			//r_Net->addWay( new Way( id, vis, id, -1, -1 ) );
			t_Way = new Way( id, vis, id, -1, -1 );
		}
	}
	if( strcmp( name, "nd" )==0 ){
		if( t_Way!=NULL && atts!=NULL){
			//std::cout<<"13\n";
			long long refId = -1;
			const char **at = (const char**) atts;
			while( *at!=NULL ){
				const char *name = *at++;
				const char *val = *at++;
				if( strcmp( name, "ref" )==0){
					refId = atoll( val );

				}
			}
			if( r_Net->m_Nodes[refId] ){
				//std::cout<<"14\n";
				t_Way->addNodeRef( r_Net->m_Nodes[refId] );
			}
			else{
				//std::cout<<"15\n";
			}

		}
	}

	if( strcmp( name, "tag" )==0 ){
		if( t_Way!=NULL && atts!=NULL){
			std::string k;
			const char **at = (const char**) atts;
			while( *at!=NULL ){
				const char *name = *at++;
				const char *val = *at++;
				if( strcmp( name, "k" )==0){
					if( strcmp( val, "highway" )==0){

						k = val;
						t_Way->type = k;
					}
				}
			}

		}
	}
}

static void endElement( void *userData, const char *name ){
	//std::cout<<"out"<<std::endl;
	RoadNetwork* r_Net = (RoadNetwork*) userData;
	if( strcmp( name, "way" )==0 ){
		if( t_Way && (strcmp( t_Way->type.c_str(), "highway" )==0) ){
			//std::cout<<"out-->"<<t_Way->id<<std::endl;
			r_Net->addWay( t_Way );
		}

	}
	//t_Way = 0;
	/*
	if( t_Way!=NULL )
		delete t_Way;
		*
		* 400907
way size:47254
		* */

}

Node::Node( long long id, double lat, double lon )
: osmId(id),lat(lat),lon(lon){}

Arc::Arc(long long headNodeId, int cost)
: headNodeId( headNodeId ), cost( cost ) {}

RoadNetwork::RoadNetwork()
: numNodes( 0 ), numEdges( 0 ){}

void RoadNetwork::addNode( Node* node ){
	//nodes.push_back( node );
	m_Nodes[node->osmId] = node;
	numNodes++;
}
void RoadNetwork::addWay(Way* way){
	ways.push_back( way );
}

long long RoadNetwork::getNumberOfNodes(){
	return numNodes;
}

Node* RoadNetwork::findNode( long long nodeRefId )
const{
	std::map<long long, Node*>::const_iterator  it = m_Nodes.find( nodeRefId );
	return ( it!=m_Nodes.end() ) ? it->second : 0;
}

void RoadNetwork::addEdge(Node* src, Node* dst ){

	//http://stackoverflow.com/questions/28973152/boostgraph-dijkstra-and-custom-objects-and-properties
	int cost = getLength( src, dst );

	if( adjacentArcs.count( src->osmId ) ){
		std::vector<Arc> tmp = adjacentArcs[src->osmId];
		tmp.push_back( Arc( dst->osmId, cost ) ) ;
		adjacentArcs[src->osmId] = tmp ;

	}
	else{
		std::vector<Arc> tmp;
		tmp.push_back( Arc( dst->osmId, cost ) ) ;
		adjacentArcs[src->osmId] = tmp ;
	}

}

void RoadNetwork::spitWay(){

	for( std::vector<Way*>::iterator m_w = ways.begin();
	m_w != ways.end(); m_w++ ){
		Way* way_it = *m_w;
		std::vector<Node*>::iterator it = way_it->m_NodeRefs.begin();
		it++;
		for( std::vector<Node*>::iterator m_n = it;
		m_n != way_it->m_NodeRefs.end(); m_n++ ){
			Node* dst = *m_n;
			Node* src = *(m_n -1);
			addEdge( src, dst );
		}

	}
}

void RoadNetwork::readFromosmFile( RoadNetwork& r_Net, char* fileName ){

	FILE* fp = fopen(fileName, "rb");
	if( fp ){
		// std::cout<<"here"<<std::endl;
		XML_Parser parser = XML_ParserCreate( NULL );
		XML_SetUserData( parser, (void*) &r_Net );
		XML_SetElementHandler( parser, startElement, endElement );

		int done;
		do{
			char buf[BUFSIZ];
			size_t len = fread( buf, 1, sizeof(buf), fp );
			done = len < sizeof( buf );
			if( !XML_Parse( parser, buf, (int)len, done ) ){
				fprintf(stderr,
                 "%s at line %d\n",
                 XML_ErrorString(XML_GetErrorCode(parser)),
                 (int)XML_GetCurrentLineNumber(parser));
				fclose(fp);
			}

		}while( !done );
	}
}






