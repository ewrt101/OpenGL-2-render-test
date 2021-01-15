#include "Wall_border.h"


Wall_border::Wall_border(float _lenght, float _height){
    length = _lenght;
    height = _height;

    for (int i = 0; i < (length * 2) +1; i++) {
		vx[i] = i - length;
        vy[i] = 0;
        vz[i] = 0;
        wx[i] = i - length;
        wy[i] = height;
        wz[i] = 0;

	}   
}

void Wall_border::draw(){
    glBegin(GL_QUAD_STRIP);
	for (int i = 0; i < (length*2) +1; i++) {
		glTexCoord2f(vx[i], vy[i]);     glVertex3f(vx[i], vy[i], vz[i]);
		glTexCoord2f(wx[i], wy[i]);     glVertex3f(wx[i], wy[i] , wz[i]);
	}
	glEnd();
}