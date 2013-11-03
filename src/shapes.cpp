#include <GL/gl.h>
#include <GL/glut.h>
#include "shapes.hpp"

void define_cylinder(float bottom_radius, float top_radius, float height, int texture_id) {
	GLUquadric* quad = gluNewQuadric();
	glTranslatef(0,height/2.0,0);
	glRotatef(90,1,0,0);
	if (texture_id != -1) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture_id);
		gluQuadricTexture(quad, true);
	}
	gluCylinder(quad,bottom_radius,top_radius,height,10,10);
	glRotatef(-90,1,0,0);
	glTranslatef(0,-1*height/2.0,0);
	if (texture_id != -1) {
		glDisable(GL_TEXTURE_2D);
	}

	gluDeleteQuadric(quad);
}

void define_sphere(float radius, int texture_id) {
	GLUquadric* quad = gluNewQuadric();
	if (texture_id != -1) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture_id);
		gluQuadricTexture(quad, true);
	}
	gluSphere(quad,radius,10,10);
	if (texture_id != -1) {
		glDisable(GL_TEXTURE_2D);
	}
	
	gluDeleteQuadric(quad);
}