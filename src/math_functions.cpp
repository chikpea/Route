/*
 * math_functions.cpp
 *
 *  Created on: 16-Dec-2015
 *      Author: asitm9
 */


#include<math.h>

#include "math_functions.h"


double getLength(Node* a, Node* b){
	int R = 6371;
	double x = ( a->lon - b->lon ) * cos( ( a->lon + b->lon )/2  );
	double y = ( a->lat - b->lat );
	return floorf( sqrtf( x*x + y*y ) * R );
}
