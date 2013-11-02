#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>

#include "bezier.hpp"

using namespace std;

int define_bezier_curve(vector<coordinate_t> curve_points) {
	int bezier = glGenLists(1);
	glNewList(bezier, GL_COMPILE);
		// glColor4f(1,1,1,1);
		glBegin(GL_LINE_STRIP);
			for(unsigned int i=0 ; i < curve_points.size() ; i++) {
				glVertex3f(curve_points[i].xx, curve_points[i].yy, curve_points[i].zz);
			}
		glEnd();
		glBegin(GL_POINTS);
			for(unsigned int i=0 ; i < curve_points.size() ; i++) {
				glColor4f(0,1,0,1);
				glVertex3f(curve_points[i].xx, curve_points[i].yy, curve_points[i].zz);
			}
		glEnd();
	glEndList();
	return bezier;
}
