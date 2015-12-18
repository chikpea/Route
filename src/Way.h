/*
 * Way.h
 *
 *  Created on: 14-Dec-2015
 *      Author: asitm9
 */

#ifndef WAY_H_
#define WAY_H_
#include<map>
#include<vector>

class Node;
enum OneWayType{ YES, NO, REVERSED };

class Way{
public:
    std::vector<Node*> m_NodeRefs;
    std::map<std::string, std::string> m_Tags;

    long long id;
    bool visible;

    std::string name;

    std::string type;
    std::string clss;

    std::string geom;

    double length;

    int maxspeed_forward;
    int maxspeed_backward;

    OneWayType oneWayType;

    long long osm_id;


    Way( long long id, bool visible, long long osm_id, int maxspeed_forward, int maxspeed_backward);

    ~Way();

    void addNodeRef( Node* pNode );
    void addTag( std::string key, std:: string value);
    bool hasTag(std::string key);
};




#endif /* WAY_H_ */
