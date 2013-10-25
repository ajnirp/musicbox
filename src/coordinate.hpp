#ifndef COORDINATE_H
#define COORDINATE_H

#include <vector>

using namespace std;

class coordinate_t {
public:
	float xx;
	float yy;
	float zz;

	coordinate_t add(coordinate_t c);
	coordinate_t scalarMult(float t);
};

coordinate_t deCasteljau(vector<coordinate_t> points, float t);
vector<coordinate_t> complete(vector<coordinate_t> points, float spacing);

#endif