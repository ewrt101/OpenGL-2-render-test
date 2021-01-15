//  ========================================================================
//  COSC363: Computer Graphics Assignment 1 
//
//  FILE NAME: Main.cpp
//  
//	Author: daniel mcinnes
//  ========================================================================

#include "BUILD_ORDER.h"
//#include "loadTGA.h"

using namespace std;


//--Globals ---------------------------------------------------------------
int plane_size = 800;
int plane_square_size = 20;
int border_wall_size = 50;
int border_wall_height = 5;

//objects loaded from .off files
MeshLoader Cannon("./Models/Cannon.off", new Color(1,1,1));
MeshLoader cow("./Models/Cow.off", new Color(1,0,1));

//colors
Color floor_color_one(0.25f,0.25f,0.25f);
Color floor_color_two(0.5f,0.5f,0.5f);
Color Building_Color(1,1,0.75f);

Color a(1,0,1);
Color b(0,0,0);

//planes
Plane ground(plane_size,plane_square_size,floor_color_one,floor_color_two);
Plane plane(200,20,a,b);

//borderwalls
TextrueLoader_TGA wallTexture("./Textures/Wall.tga");
Wall_border WB_back(border_wall_size,border_wall_height);
Wall_border WB_left(border_wall_size,border_wall_height);
Wall_border WB_right(border_wall_size,border_wall_height);
Wall_border WB_forward(border_wall_size,border_wall_height);

//billbord texture
TextrueLoader_TGA billboardTexture("./Textures/billbord.tga");

//skybox texture
TextrueLoader_TGA SkyBoxTexture("./Textures/Skybox.tga");

//camera
float angle=0, look_x, look_z=-1., eye_x, eye_z;  //Camera parameters
float speed = 1;
float update = 10;
float turn = 1;

//move
int upK, downK, leftK, rightK;


//stand1
float s1Pos[11] = {1.25f,1,0.75f,0.5f,0.25f,0,0.25f,0.5f,0.75f,1,1.25f};
float s1bool[11] = {1,1,1,1,1,1,1,1,1,1,1};
float s1Step = 0.01f;

//stand2
float s2Rot[5] = {0};
float s2Spin = 1;
float s2Rate = 2;

//stand3
TextrueLoader_TGA s2Texture("./Textures/picFrame.tga");
float s3height = 0;
float s3Bool = 0;
float s3BoolS = 0;
float s3Spin = 0;
float s3Rate1 =0.25;
float s3Rate2 =50;


void display()  
{
	float lpos[4] = {100., 100., 100., 1.0};  //light's position

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);    //GL_LINE = Wireframe;   GL_FILL = Solid
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye_x, 2, eye_z,  look_x, 2, look_z,   0, 1, 0);	
	glLightfv(GL_LIGHT0, GL_POSITION, lpos);   //set light position

	glPushMatrix();
	glScalef(.1,.1,.1);
	ground.draw();
	glPopMatrix();

	//walls
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, wallTexture.txId);

	glPushMatrix();

	glTranslatef(0, 0, -border_wall_size); 
	WB_back.draw();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0, 0, border_wall_size); 
	WB_forward.draw();
	glPopMatrix();
	
	glPushMatrix();
	glRotatef(90,0,1,0);
	glTranslatef(0, 0, border_wall_size); 
	WB_left.draw();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90,0,1,0);
	glTranslatef(0, 0, -border_wall_size); 
	WB_right.draw();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);

	//building
	glPushMatrix();
	glTranslatef(0, 0, -10); 
		//right
		glPushMatrix();
		glColor3f(Building_Color.r, Building_Color.g, Building_Color.b);
		glTranslatef(-14.5, 5, -10); 
		glScalef(0.1,1,3);
		glutSolidCube(10);
		glPopMatrix();
		//left
		glPushMatrix();
		glColor3f(Building_Color.r, Building_Color.g, Building_Color.b);
		glTranslatef(14.5, 5, -10); 
		glScalef(0.1,1,3);
		glutSolidCube(10);
		glPopMatrix();
		//back
		glPushMatrix();
		glColor3f(Building_Color.r, Building_Color.g, Building_Color.b);
		glTranslatef(0, 5, -25); 
		glScalef(3,1,0.1);
		glutSolidCube(10);
		glPopMatrix();
		//forward
		glPushMatrix();
		glColor3f(Building_Color.r, Building_Color.g, Building_Color.b);
		glTranslatef(-2.5, 5, 5); 
		glScalef(2.5,1,0.1);
		glutSolidCube(10);
		glPopMatrix();
		//forward top
		glPushMatrix();
		glColor3f(Building_Color.r, Building_Color.g, Building_Color.b);
		glTranslatef(12.5, 7.5, 5); 
		glScalef(0.5,0.5,0.1);
		glutSolidCube(10);
		glPopMatrix();
		//forward left
		glPushMatrix();
		glColor3f(Building_Color.r, Building_Color.g, Building_Color.b);
		glTranslatef(14.5, 2.5, 5); 
		glScalef(0.1,0.5,0.1);
		glutSolidCube(10);
		glPopMatrix();
		//roof
		glPushMatrix();
		glColor3f(0.9, 0.9, 0.9);
		glTranslatef(0, 10.5, -8); 
		glScalef(3,0.1,3.5);
		glutSolidCube(10);
		glPopMatrix();

		//billbord
		glPushMatrix();
			glTranslatef(0, 5, 5.51f); 
			glRotatef(180,0,1,0);
			glScalef(2,2,2);

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, billboardTexture.txId);
			glBegin(GL_QUADS);
				glNormal3f(0, 0, 1);
				glTexCoord2f(0, 1);  glVertex3f(5, -2.5f, 0);
				glTexCoord2f(0, 0);  glVertex3f(5, 2.5f, 0);
				glTexCoord2f(1, 0);  glVertex3f(-5, 2.5f, 0);
				glTexCoord2f(1, 1);  glVertex3f(-5, -2.5f, 0);
			glEnd();
			glDisable(GL_TEXTURE_2D);
			glDisable(GL_BLEND);
		glPopMatrix();

		//stand 1
		glPushMatrix();
		glTranslatef(-12, 0.5f, 2.5f); 
		//wave
		glPushMatrix();
			glPushMatrix();
				glTranslatef(0, 1 + (s1Pos[0] * 4), -1.25); 
				glScalef(0.25,0.25,0.25);
				glColor3f(s1Pos[0], 0, 1);
				glPushMatrix();
					glTranslatef(0, 1, 0); 
					glutSolidCube(0.5);
					glTranslatef(0, -2, 0); 
					glutSolidCube(0.5);
				glPopMatrix();
				glutSolidCube(1);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0, 1 + (s1Pos[1] * 4), -1); 
				glScalef(0.25,0.25,0.25);
				glColor3f(s1Pos[1], 0, 1);
				glPushMatrix();
					glTranslatef(0, 1, 0); 
					glutSolidCube(0.5);
					glTranslatef(0, -2, 0); 
					glutSolidCube(0.5);
				glPopMatrix();
				glutSolidCube(1);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0, 1 + (s1Pos[2] * 4), -0.75); 
				glScalef(0.25,0.25,0.25);
				glColor3f(s1Pos[2], 0, 1);
				glPushMatrix();
					glTranslatef(0, 1, 0); 
					glutSolidCube(0.5);
					glTranslatef(0, -2, 0); 
					glutSolidCube(0.5);
				glPopMatrix();
				glutSolidCube(1);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0, 1 + (s1Pos[3] * 4), -0.5); 
				glScalef(0.25,0.25,0.25);
				glColor3f(s1Pos[3], 0, 1);
				glPushMatrix();
					glTranslatef(0, 1, 0); 
					glutSolidCube(0.5);
					glTranslatef(0, -2, 0); 
					glutSolidCube(0.5);
				glPopMatrix();
				glutSolidCube(1);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0, 1 + (s1Pos[4] * 4), -0.25); 
				glScalef(0.25,0.25,0.25);
				glColor3f(s1Pos[4], 0, 1);
				glPushMatrix();
					glTranslatef(0, 1, 0); 
					glutSolidCube(0.5);
					glTranslatef(0, -2, 0); 
					glutSolidCube(0.5);
				glPopMatrix();
				glutSolidCube(1);
			glPopMatrix();
			
			glPushMatrix();
				glTranslatef(0, 1 + (s1Pos[5] * 4), 0); 
				glScalef(0.25,0.25,0.25);
				glColor3f(s1Pos[5], 0, 1);
				glPushMatrix();
					glTranslatef(0, 1, 0); 
					glutSolidCube(0.5);
					glTranslatef(0, -2, 0); 
					glutSolidCube(0.5);
				glPopMatrix();
				glutSolidCube(1);
			glPopMatrix();
			
			glPushMatrix();
				glTranslatef(0, 1 + (s1Pos[6] * 4), 0.25); 
				glScalef(0.25,0.25,0.25);
				glColor3f(s1Pos[6], 0, 1);
				glPushMatrix();
					glTranslatef(0, 1, 0); 
					glutSolidCube(0.5);
					glTranslatef(0, -2, 0); 
					glutSolidCube(0.5);
				glPopMatrix();
				glutSolidCube(1);
			glPopMatrix();
			
			glPushMatrix();
				glTranslatef(0, 1 + (s1Pos[7] * 4), 0.5); 
				glScalef(0.25,0.25,0.25);
				glColor3f(s1Pos[7], 0, 1);
				glPushMatrix();
					glTranslatef(0, 1, 0); 
					glutSolidCube(0.5);
					glTranslatef(0, -2, 0); 
					glutSolidCube(0.5);
				glPopMatrix();
				glutSolidCube(1);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0, 1 + (s1Pos[8] * 4), 0.75); 
				glScalef(0.25,0.25,0.25);
				glColor3f(s1Pos[8], 0, 1);
				glPushMatrix();
					glTranslatef(0, 1, 0); 
					glutSolidCube(0.5);
					glTranslatef(0, -2, 0); 
					glutSolidCube(0.5);
				glPopMatrix();
				glutSolidCube(1);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0, 1 + (s1Pos[9] * 4), 1); 
				glScalef(0.25,0.25,0.25);
				glColor3f(s1Pos[9], 0, 1);
				glPushMatrix();
					glTranslatef(0, 1, 0); 
					glutSolidCube(0.5);
					glTranslatef(0, -2, 0); 
					glutSolidCube(0.5);
				glPopMatrix();
				glutSolidCube(1);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0, 1 + (s1Pos[10] * 4), 1.25); 
				glScalef(0.25,0.25,0.25);
				glColor3f(s1Pos[10], 0, 1);
				glPushMatrix();
					glTranslatef(0, 1, 0); 
					glutSolidCube(0.5);
					glTranslatef(0, -2, 0); 
					glutSolidCube(0.5);
				glPopMatrix();
				glutSolidCube(1);
			glPopMatrix();
		glPopMatrix();
		

		glScalef(4,1,4);
		glColor3f(1, 1, 1);
		glutSolidCube(1);
		glPopMatrix();

		//stand 2
		glPushMatrix();
		glTranslatef(-11, 0.5f, -21.5f); 

		glPushMatrix();
			glTranslatef(0,4,0); 
			glRotatef(s2Spin,1,0,0);
			glScalef(0.25,0.25,0.25);
			glPushMatrix();
				glColor3f(1, 1, 0);
				glutSolidSphere(1,25,25);

				glRotatef(s2Rot[0],0,1,0);
				glPushMatrix();
					glTranslatef(2.5,-2,0); 
					glColor3f(1, 0.8, 0);
					glutSolidSphere(1,25,25);

					glRotatef(s2Rot[1],0,1,0);
					glPushMatrix();
						glTranslatef(2.5,-2,0); 
						glColor3f(1, 0.6, 0);
						glutSolidSphere(1,25,25);

						glRotatef(s2Rot[2],0,1,0);
						glPushMatrix();
							glTranslatef(2.5,-2,0); 
							glColor3f(1, 0.4, 0);
							glutSolidSphere(1,25,25);

							glRotatef(s2Rot[3],0,1,0);
							glPushMatrix();
								glTranslatef(2.5,-2,0); 
								glColor3f(1, 0.2, 0);
								glutSolidSphere(1,25,25);

								glRotatef(s2Rot[4],0,1,0);
								glPushMatrix();
									glTranslatef(2.5,-2,0); 
									glColor3f(1, 0, 0);
									glutSolidSphere(1,25,25);
								glPopMatrix();
								//subBalls l6
								glColor3f(0, 1, 1);
								glPushMatrix();
									glTranslatef(2.5,-2,-1); 
									glutSolidSphere(0.5,25,25);
								glPopMatrix();
								glPushMatrix();
									glTranslatef(2.5,-2,1); 
									glutSolidSphere(0.5,25,25);
								glPopMatrix();
							glPopMatrix();

							//subBalls l5
							glColor3f(0, 1, 0.8);
							glPushMatrix();
								glTranslatef(2.5,-2,-1); 
								glutSolidSphere(0.5,25,25);
							glPopMatrix();
							glPushMatrix();
								glTranslatef(2.5,-2,1); 
								glutSolidSphere(0.5,25,25);
							glPopMatrix();

						glPopMatrix();

						//subBalls l4
						glColor3f(0, 1, 0.6);
						glPushMatrix();
							glTranslatef(2.5,-2,-1); 
							glutSolidSphere(0.5,25,25);
						glPopMatrix();
						glPushMatrix();
							glTranslatef(2.5,-2,1); 
							glutSolidSphere(0.5,25,25);
						glPopMatrix();

					glPopMatrix();

					//subBalls l3
					glColor3f(0, 1, 0.4);
					glPushMatrix();
						glTranslatef(2.5,-2,-1); 
						glutSolidSphere(0.5,25,25);
					glPopMatrix();
					glPushMatrix();
						glTranslatef(2.5,-2,1); 
						glutSolidSphere(0.5,25,25);
					glPopMatrix();

				glPopMatrix();

				//subBalls l2
				glColor3f(0, 1, 0.2);
				glPushMatrix();
					glTranslatef(2.5,-2,-1); 
					glutSolidSphere(0.5,25,25);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(2.5,-2,1); 
					glutSolidSphere(0.5,25,25);
				glPopMatrix();

			glPopMatrix();
		glPopMatrix();
		glScalef(6,1,6);
		glColor3f(1, 1, 1);
		glutSolidCube(1);
		glPopMatrix();

		//stand 3
		glPushMatrix();
		
		glTranslatef(11, 0.5f, -21.5f); 
		glPushMatrix();
			glTranslatef(0, 1 + s3height, 0); 
			glRotatef(s3Spin,0,1,0);
			glPushMatrix();
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, s2Texture.txId);
				glBegin(GL_QUADS);
					glNormal3f(0,0,1);		glTexCoord2f(0, 0);		glVertex3f(-1.5, 0, 0);
					glNormal3f(0,0,1);		glTexCoord2f(1, 0);		glVertex3f(1.5, 0, 0);
					glNormal3f(0,0,1);		glTexCoord2f(1, 1);		glVertex3f(1.5, 4, 0);
					glNormal3f(0,0,1);		glTexCoord2f(0, 1);		glVertex3f(-1.5, 4, 0);
				glEnd();
				glDisable(GL_TEXTURE_2D);
			glPopMatrix();

			glColor3f(0.59, 0.29, 0);

			glPushMatrix();
				glScalef(3,0.25,0.25);
				glutSolidCube(1);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0, 4, 0); 
				glScalef(3,0.25,0.25);
				glutSolidCube(1);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(1.625, 2, 0); 
				glScalef(0.25,4.25,0.25);
				glutSolidCube(1);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-1.625, 2, 0); 
				glScalef(0.25,4.25,0.25);
				glutSolidCube(1);
			glPopMatrix();

		glPopMatrix();
		glScalef(6,1,6);
		glColor3f(1, 1, 1);
		glutSolidCube(1);
		glPopMatrix();


	glPopMatrix();
	

	//cannon
	glPushMatrix();
	glTranslatef(0, 5, 0); 
	glColor3f(1, 0, 0);
	glScalef(.2,.2,.2);
	Cannon.draw();
	glPopMatrix();

	/*
	glPushMatrix();
	glTranslatef(0, 0, 10); 
	//glScalef(20,20,20);
	cow.draw();
	glPopMatrix();
	*/


	//skybox
	glPushMatrix();
		glTranslatef(eye_x, 0, eye_z); 
		glScalef(200,200,200);
		glEnable(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, SkyBoxTexture.txId);
		glBegin(GL_QUADS);
			//forward
			glNormal3f(0,0,1);		glTexCoord2f(1, 0.333);		glVertex3f(-0.5, -0.5, 0.5);
			glNormal3f(0,0,1);		glTexCoord2f(0.75, 0.333);		glVertex3f(0.5,-0.5, 0.5);
			glNormal3f(0,0,1);		glTexCoord2f(0.75, 0.666);		glVertex3f(0.5, 0.5, 0.5);
			glNormal3f(0,0,1);		glTexCoord2f(1, 0.666);		glVertex3f(-0.5, 0.5, 0.5);

			//back
			glNormal3f(0,0,1);		glTexCoord2f(0.25, 0.333);		glVertex3f(-0.5, -0.5, -0.5);
			glNormal3f(0,0,1);		glTexCoord2f(0.5, 0.333);		glVertex3f(0.5,-0.5, -0.5);
			glNormal3f(0,0,1);		glTexCoord2f(0.5, 0.666);		glVertex3f(0.5, 0.5, -0.5);
			glNormal3f(0,0,1);		glTexCoord2f(0.25, 0.666);		glVertex3f(-0.5, 0.5, -0.5);

			//left
			glNormal3f(0,0,1);		glTexCoord2f(0.25, 0.333);		glVertex3f(-0.5, -0.5, -0.5);
			glNormal3f(0,0,1);		glTexCoord2f(0, 0.333);			glVertex3f(-0.5,-0.5, 0.5);
			glNormal3f(0,0,1);		glTexCoord2f(0, 0.666);			glVertex3f(-0.5, 0.5, 0.5);
			glNormal3f(0,0,1);		glTexCoord2f(0.25, 0.666);		glVertex3f(-0.5, 0.5, -0.5);

			//right
			glNormal3f(0,0,1);		glTexCoord2f(0.5, 0.333);		glVertex3f(0.5, -0.5, -0.5);
			glNormal3f(0,0,1);		glTexCoord2f(0.75, 0.333);		glVertex3f(0.5,-0.5, 0.5);
			glNormal3f(0,0,1);		glTexCoord2f(0.75, 0.666);		glVertex3f(0.5, 0.5, 0.5);
			glNormal3f(0,0,1);		glTexCoord2f(0.5, 0.666);		glVertex3f(0.5, 0.5, -0.5);

			//top
			glNormal3f(0,-1,0);		glTexCoord2f(0.25, 0.666);			glVertex3f(-0.5, 0.5, -0.5);
			glNormal3f(0,-1,0);		glTexCoord2f(0.25, 1);		glVertex3f(-0.5, 0.5, 0.5);
			glNormal3f(0,-1,0);		glTexCoord2f(0.5, 1);		glVertex3f(0.5, 0.5, 0.5);
			glNormal3f(0,-1,0);		glTexCoord2f(0.5, 0.666);			glVertex3f(0.5, 0.5, -0.5);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();

    glFlush();

	glutSwapBuffers();	

}


void Move(){
	if(leftK == 1) angle -= turn / update;  //Change direction
	else if(rightK == 1) angle += turn / update;
	else if(downK == 1)
	{  //Move backward
		eye_x -= speed*sin(angle)/update;
		eye_z += speed*cos(angle)/update;
	}
	else if(upK == 1)
	{ //Move forward
		eye_x += speed*sin(angle)/update;
		eye_z -= speed*cos(angle)/update;
	}
	//make player stay in bounds
	if(eye_x > 49.5f){
		eye_x = 49.5f;
	}
	if(eye_x < -49.5f){
		eye_x = -49.5f;
	}
	if(eye_z > 49.5f){
		eye_z = 49.5f;
	}
	if(eye_z < -49.5f){
		eye_z = -49.5f;
	}

	look_x = eye_x + 100*sin(angle);
	look_z = eye_z - 100*cos(angle);
}

void Stand1(){
	
	for (int i = 0; i < 11; i++) {
		if (s1Pos[i] >= 1.25f){
			s1bool[i] = -1;
		}else if (s1Pos[i] <= 0){
			s1bool[i] = 1;
		}

		s1Pos[i] += (s1Step * s1bool[i]) / update;
	}
}

void Stand2(){
	for (int i = 0; i < 5; i++) {
		s2Rot[i] += (s2Rate*(i+1)) / update;
	}
	s2Spin += s2Rate / update;

}

void Stand3(){
	if (s3BoolS != 1){
		if (s3height >= 3){
			s3Bool = -1;
			s3BoolS = 1;
		}else if (s3height <= 0){
			s3Bool = 1;
			s3BoolS = 1;
		}

		s3height += (s3Rate1 * s3Bool) / update;
	}else{
		s3Spin += s3Rate2 / update;

		if(s3Spin >= 360 ){
			s3Spin = 0;
			s3BoolS = 0;
		}
	}
	
}

void Loop(int i){
	Move();
	Stand1();
	Stand2();
	Stand3();
	glutPostRedisplay();
    glutTimerFunc(update, Loop, 0);
}

void LoadAllTextures(){
	wallTexture.loadTexture();
	billboardTexture.loadTexture();
	s2Texture.loadTexture();
	SkyBoxTexture.loadTexture();
}


//------- Initialize OpenGL parameters -----------------------------------
void initialize()
{
	LoadAllTextures();
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);	//Background colour

	glEnable(GL_LIGHTING);					//Enable OpenGL states
	glEnable(GL_LIGHT0);

	float white[3] = {1, 1, 1};
	//float black[3] = {0, 0, 0};
	float gray[3] = {0.2, 0.2, 0.2};
	float cyan[3] = {0, 1, 1};
	glLightfv(GL_LIGHT0, GL_AMBIENT, gray);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, cyan);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, cyan);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100);

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
 	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, 1, 0.1, 1000);  //The camera view volume  
}

//for special key inputs
//--------------------------------------------------------------------------------
void special(int key, int x, int y)
{
	if(key == GLUT_KEY_LEFT){
		leftK = 1;
	}else if (key == GLUT_KEY_RIGHT){
		rightK = 1;
	}else if (key == GLUT_KEY_DOWN){
		downK = 1;
	}else if (key == GLUT_KEY_UP){
		upK = 1;
	}
}

void specialUp(int key, int x, int y){
	if(key == GLUT_KEY_LEFT){
		leftK = 0;
	}else if (key == GLUT_KEY_RIGHT){
		rightK = 0;
	}else if (key == GLUT_KEY_DOWN){
		downK = 0;
	}else if (key == GLUT_KEY_UP){
		upK = 0;
	}
}

int main(int argc, char** argv)
{
    //base stuff
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB| GLUT_DEPTH);
    glutInitWindowSize (800, 800); 
    glutInitWindowPosition (10, 10);
    glutCreateWindow ("Assignment 1");
    initialize();

    //run display
    glutDisplayFunc(display);

	glutTimerFunc(update, Loop, 0);

	glutSpecialFunc(special);
	glutSpecialUpFunc(specialUp); 

    glutMainLoop();
    return 0;

}