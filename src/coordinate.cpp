#include "coordinate.hpp"
#include <iostream>

using namespace std;

// Add two coordinates together
coordinate_t
coordinate_t::add(coordinate_t c) {
	coordinate_t result;
	result.xx = this->xx + c.xx;
	result.yy = this->yy + c.yy;
	result.zz = this->zz + c.zz;
	return result;
}

// Scalar multiply a coordinate with a float
coordinate_t
coordinate_t::scalarMult(float t) {
	coordinate_t result;
	result.xx = this->xx * t;
	result.yy = this->yy * t;
	result.zz = this->zz * t;
	return result;
}

// Using the de Casteljau algorithm, calculate the point on the curve
// corresponding to the parameter t
coordinate_t
deCasteljau(vector<coordinate_t> points, float t) {
	int n = points.size() - 1;
	if (n == 0) return points[0];
	else {
		vector<coordinate_t> temp_points;
		for (int i = 0 ; i < n ; i++) {
			coordinate_t new_point;
			new_point = points[i].scalarMult(1-t).add(points[i+1].scalarMult(t));
			temp_points.push_back(new_point);
		}
		return deCasteljau(temp_points, t);
	}
}

// Get all the de Casteljau points for t = [0, spacing, 2*spacing, 2*spacing, ..., 1)
vector<coordinate_t> complete(vector<coordinate_t> points, float spacing) {
	cout << "Calculating the set of curve points\n";
	vector<coordinate_t> curve_points;
	for(float i=0 ; i <= 1 ; i=i+spacing) {
		coordinate_t point = deCasteljau(points, i);
		curve_points.push_back(point);
	}
	curve_points.push_back(points[points.size()-1]);
	return curve_points;
}