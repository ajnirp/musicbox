#include "painting.hpp"
#include "texture.hpp"

int define_painting() {
	int painting = glGenLists(1);
	GLuint texture_painting = LoadTexture("tex/swamp.bmp");
	glNewList(painting, GL_COMPILE);
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D, texture_painting);
		glBegin(GL_QUADS); // the painting is 200x150 pixels, so its aspect ratio is 4:3 or 2:1.5
			glTexCoord2f(0.0, 1.0);glVertex3f(-4,5,-4+0.01); // top left
			glTexCoord2f(1.0, 1.0);glVertex3f(0,5,-4+0.01); // top right
			glTexCoord2f(1.0, 0.0);glVertex3f(0,2,-4+0.01); // bottom right
			glTexCoord2f(0.0, 0.0);glVertex3f(-4,2,-4+0.01); // bottom left
		glEnd();
	glEndList();
	return painting;
}