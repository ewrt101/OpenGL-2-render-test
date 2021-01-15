#include "Plane.h"

Plane::Plane(float size, float tile, Color color1, Color color2){
    base_size = size;
    tile_size = tile;
    base_color = new Color(color1.r, color1.g, color1.b);
    tile_color = new Color(color2.r, color2.g, color2.b);
}

void Plane::draw(){
    bool flag = false;

	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	for(int x = -base_size; x <= base_size; x += tile_size)
	{
		for(int z = -base_size; z <= base_size; z += tile_size)
		{
			if(flag) glColor3f(base_color->r, base_color->g, base_color->b);
			else glColor3f(tile_color->r, tile_color->g, tile_color->b);
			glVertex3f(x, 0, z);
			glVertex3f(x, 0, z+20);
			glVertex3f(x+20, 0, z+20);
			glVertex3f(x+20, 0, z);
			flag = !flag;
		}
	}
	glEnd();
}

