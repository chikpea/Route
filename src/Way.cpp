#include <map>
#include <vector>
#include <string>
#include <iostream>

#include "Way.h"

Way::Way( long long id, bool visible, long long osm_id, int maxspeed_forward, int maxspeed_backward):
    id(id),
    visible(visible),
    length(0),
    oneWayType(NO),
    osm_id(osm_id),
    maxspeed_forward(maxspeed_forward),
    maxspeed_backward(maxspeed_backward){

        }

Way::~Way(){
}

void Way::addNodeRef( Node* pNode){
    if( pNode ) m_NodeRefs.push_back(pNode);
}

void Way::addTag( std::string key, std::string value){
    m_Tags[key] = value;
}

bool Way::hasTag( std::string key ){
    return (m_Tags.count(key)>0);
}
