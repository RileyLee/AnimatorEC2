// The sample box model.  You should build a file
// very similar to this for when you make your model in
// order to plug in to the animator project.

#include"r2d2.h"


// We are going to override (is that the right word?) the draw()
// method of ModelerView to draw out RobotArm
void RobotR2D2::draw()
{
	
	const float PI = 3.1415926535f;
	/* pick up the slider values */
	float PosX = bodyPositionX.getValue();
	float PosY = bodyPositionY.getValue();
	float PosZ = bodyPositionZ.getValue();
	float alpha = bodyRotation.getValue();
	float theta = bodyTilt.getValue();
	float phi = headRotation.getValue();
	float psi = armTilt.getValue();
	float cr = footTilt.getValue();
	float h1 = armLength.getValue();
	float h2 = footPosition.getValue();

	static GLfloat lmodel_ambient[] = { 0.4, 0.4, 0.4, 1.0 };

	// define the model
	glPushMatrix();
	{
	  frontierTexture.load();
	  frontierTexture.use();
  /*glColor3f(0.65,0.45,0.2);
	setDiffuseColor(0.604, 0.804, 0.196);
	setAmbientColor(0.604, 0.804, 0.196);*/
	  glBegin(GL_QUADS);
	  glTexCoord2f(0, 1); // specify the texture coordinate
	  glNormal3f(0, 1, 0); // specify the surface's normal at this vertex
	  glVertex3f(-10, -2, -10); // both before its corresponding vertex
	  
	  glTexCoord2f(1, 1);
	  glNormal3f(0, 1, 0);
	  glVertex3f(10, -2, -10);
	  
	  glTexCoord2f(1, 0);
	  glNormal3f(0, 1, 0);
	  glVertex3f(10, -2, 10);
	  
	  glTexCoord2f(0, 0);
	  glNormal3f(0, 1, 0);
	  glVertex3f(-10, -2, 10);
	  glEnd();
	  glEnd();
	  glDisable(GL_TEXTURE_2D);
	}


	glPushMatrix();
	glTranslatef(5.0f, 0.0f, 5.0f);
	glRotatef(-90.0, 1.0f, 0.0f, 0.0f);
	batteryTexture.load();
	batteryTexture.use();
	drawCylinder(1.0, 0.25, 0.25);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	body(PosX, PosY, PosZ, theta, alpha, velocity);
	head(phi);


	setDiffuseColor(0.8, 0.8, 0.8);
	setAmbientColor(0.8, 0.8, 0.8);

	right_arm(h1, psi);
	left_arm(h1, psi);


	glPushMatrix();									// Back Foot
	glTranslatef(0.0f, h2, -2.3f);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glScalef(0.60f, 0.7f, 0.5f);
	y_box(0.5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, h2, -2.5f);
	glRotatef(cr, 1.0f, 0.0f, 0.0f);
	foot(0.5, 0.5, 1.0, 0.7, 1.33);
	glPopMatrix();
	glPopMatrix();
	

	setDiffuseColor(0.0, 0.0, 0.0);
	setAmbientColor(0.0, 0.0, 0.0);
}

void RobotR2D2::left_arm(float h1, float psi){
	glPushMatrix();									
	setDiffuseColor(0.8, 0.8, 0.8);
	setAmbientColor(0.8, 0.8, 0.8);
	glTranslatef(-1.275f, 0.0f, 0.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	drawCylinder(0.075f, 0.30f, 0.30f);

	glTranslatef(0.0f, 0.0f, -0.2f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	upper_arm(h1, psi);
	glPopMatrix();
}

void RobotR2D2::right_arm(float h1, float psi){
	glPushMatrix();									
	glTranslatef(1.2f, 0.0f, 0.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	drawCylinder(0.075f, 0.30f, 0.30f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.45f, 0.0f, 0.0f);
	glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
	upper_arm(h1, psi);
	glPopMatrix();
}

void RobotR2D2::ground(float h)
{
	glDisable(GL_LIGHTING);
	glColor3f(0.65,0.45,0.2);
	setDiffuseColor(0.604, 0.804, 0.196);
	setAmbientColor(0.604, 0.804, 0.196);
	glPushMatrix();
	glScalef(500, 0, 500);
	y_box(h);
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

void RobotR2D2::body(float x, float y, float h, float theta, float alpha) {
	const float PI = 3.1415926535;
	setDiffuseColor(0.8, 0.8, 0.8);
	setAmbientColor(0.8, 0.8, 0.8);

	glRotatef(90.0f,-1.0f,0.0f,0.0f);				// Set up R2D2 base frame
	glTranslatef(x,y,h+3.0);
	glRotatef(alpha, 0.0f, 0.0f, 1.0f);
	glRotatef(theta, 1.0f, 0.0f, 0.0f);
	glPushMatrix();

	glPushMatrix();									//Body Cylinder
	bodyTexture.load();
	bodyTexture.use();
	glTranslatef(0.0f,0.0f,-1.9f);					
	drawCylinder(2.6, 1.25, 1.25);
	glDisable(GL_TEXTURE_2D);
	glTranslatef(0.0f, 0.0f, -0.4f);
	drawCylinder(0.4, 1.0, 1.25);
	
	glPopMatrix();

	glPushMatrix();									//Flame nozzle
	glTranslatef(0.0f,1.6f,-1.3f);
	drawCylinder(1.8f, 0.35f, 0.35f);
	glTranslatef(0.0f, 0.0f, 1.8f);
	drawCylinder(0.2f, 0.35f, 0.25f);
	glTranslatef(0.0f, 0.0f, -2.1f);
	//glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
	drawCylinder(0.3f, 0.45f, 0.35f);
	//glTranslatef(0.0f, 0.0f, 0.3f);
	flame();
	glPopMatrix();
}

void RobotR2D2::flame(){
	ModelerUserInterface* ui = ModelerUserInterface::getInstance();
	ParticleSystem* ps = ui->getParticleSystem();
	if (ps) {
	  ps->spawnParticles(ui->getTime());
	}
}

void RobotR2D2::head(float phi){
	glPushMatrix();									//Neck Cylinder
	glTranslatef(0.0f, 0.0f, 0.7f);
	setDiffuseColor(0.3, 0.3, 0.3);
	setAmbientColor(0.3, 0.3, 0.3);
	drawCylinder(0.2, 1.25, 1.25);
	glTranslatef(0.0f, 0.0f, 0.2f);					//Head
	setDiffuseColor(0.0, 0.0, 0.3);
	setAmbientColor(0.0, 0.0, 0.3);
	drawSphere(1.15);

	glRotatef(phi, 0.0f, 0.0f, 1.0f);

	glPushMatrix();									//Robot Camera
	glRotatef(55.0, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, 1.05f);
	setDiffuseColor(0.0, 0.0, 0.0);
	setAmbientColor(0.0, 0.0, 0.0);
	glutSolidSphere(0.25,64,64);
	glPopMatrix();

	glPushMatrix();									//red Indicator
	glRotatef(10.0, 0.0f, 0.0f, 1.0f);
	glRotatef(75.0, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, 1.15f);
	setDiffuseColor(1.0, 0.0, 0.0);
	setAmbientColor(1.0, 0.0, 0.0);
	drawSphere(0.10);
	glPopMatrix();

	glPushMatrix();									//projector
	glRotatef(25.0, 0.0f, 0.0f, 1.0f);
	glRotatef(70.0, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, 1.1f);
	setDiffuseColor(0.1, 0.3, 0.7);
	setAmbientColor(0.1, 0.3, 0.7);
	drawSphere(0.13);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.3f, 0.3f, 1.1f);					//Antenna
	setDiffuseColor(0.8, 0.8, 0.8);
	setAmbientColor(0.80, 0.8, 0.8);
	glRotatef(45.0, 0.0f, 0.0f, 1.0f);
	glRotatef(25.0, 0.0f, 1.0f, 0.0f);
	drawCylinder(0.2, 0.25, 0.15);
	glPopMatrix();

	glPopMatrix();
}

void RobotR2D2::upper_arm(float h, float psi) {					// draw the upper arm
	setDiffuseColor(0.85, 0.75, 0.25);
	setAmbientColor(0.95, 0.75, 0.25);
	glRotatef(psi, 1.0f, 0.0f, 0.0f);

	glPushMatrix();
	glTranslatef(0.175f, 0.0, 0.0);
	glRotatef(90.0,0.0f,-1.0f,0.0f);
	drawCylinder(0.35f, 0.55f, 0.55f);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90.0, 1.0f, 0.0f, 0.0f);
	glScalef(0.70f, 3.0f, 2.2f);
	y_box(0.25);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90.0, 1.0f, 0.0f, 0.0f);
	glScalef(0.60f, h*4, 1.8f);
	y_box(0.25);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f,0.0f,h-0.5);
	glRotatef(90.0, 1.0f, 0.0f, 0.0f);
	glScalef(0.60f, 2.0f, 2.2f);
	y_box(0.25);
	glPopMatrix();

	glPushMatrix();

	setDiffuseColor(0.85, 0.85, 0.85);
	setAmbientColor(0.95, 0.85, 0.85);
	glTranslatef(0.0f, 0.0f, h);
	//glScalef(0.60f, 2.0f, 2.2f);
	foot(-0.5,0.5,1.0,0.7,1.33);
	glPopMatrix();
}


void RobotR2D2::y_box(float h) {

	glBegin(GL_QUADS);

	glNormal3d(1.0, 0.0, 0.0);			// +x side
	glVertex3d(0.25, 0.0, 0.25);
	glVertex3d(0.25, 0.0, -0.25);
	glVertex3d(0.25, h, -0.25);
	glVertex3d(0.25, h, 0.25);

	glNormal3d(0.0, 0.0, -1.0);		// -z side
	glVertex3d(0.25, 0.0, -0.25);
	glVertex3d(-0.25, 0.0, -0.25);
	glVertex3d(-0.25, h, -0.25);
	glVertex3d(0.25, h, -0.25);

	glNormal3d(-1.0, 0.0, 0.0);			// -x side
	glVertex3d(-0.25, 0.0, -0.25);
	glVertex3d(-0.25, 0.0, 0.25);
	glVertex3d(-0.25, h, 0.25);
	glVertex3d(-0.25, h, -0.25);

	glNormal3d(0.0, 0.0, 1.0);			// +z side
	glVertex3d(-0.25, 0.0, 0.25);
	glVertex3d(0.25, 0.0, 0.25);
	glVertex3d(0.25, h, 0.25);
	glVertex3d(-0.25, h, 0.25);

	glNormal3d(0.0, 1.0, 0.0);			// top (+y)
	glVertex3d(0.25, h, 0.25);
	glVertex3d(0.25, h, -0.25);
	glVertex3d(-0.25, h, -0.25);
	glVertex3d(-0.25, h, 0.25);

	glNormal3d(0.0, -1.0, 0.0);			// bottom (-y)
	glVertex3d(0.25, 0.0, 0.25);
	glVertex3d(-0.25, 0.0, 0.25);
	glVertex3d(-0.25, 0.0, -0.25);
	glVertex3d(0.25, 0.0, -0.25);

	glEnd();
}


void RobotR2D2::foot(float h, float x1, float y1, float x2, float y2) {

	glBegin(GL_QUADS);

	double deltax = x2 - x1; double deltay = y2 - y1;

	glNormal3d(atan2(h, deltax), 0.0, atan2(deltax, h));			// +x side
	glVertex3d(x1 / 2, y1 / 2, 0);
	glVertex3d(x1 / 2, -y1 / 2, 0);
	glVertex3d(x2 / 2, -y2 / 2, -h);
	glVertex3d(x2 / 2, y2 / 2, -h);

	glNormal3d(0.0, 0.0, 1.0);			// -z side
	glVertex3d(x2 / 2, y2 / 2, -h);
	glVertex3d(x2 / 2, -y2 / 2, -h);
	glVertex3d(-x2 / 2, -y2 / 2, -h);
	glVertex3d(-x2 / 2, y2 / 2, -h);

	glNormal3d(atan2(h, deltax), 0.0, atan2(deltax, h));			// -x side
	glVertex3d(-x1 / 2, y1 / 2, 0);
	glVertex3d(-x1 / 2, -y1 / 2, 0);
	glVertex3d(-x2 / 2, -y2 / 2, -h);
	glVertex3d(-x2 / 2, y2 / 2, -h);

	glNormal3d(0.0, 0.0, 1.0);			// +z side
	glVertex3d(x1/2, y1/2, 0);
	glVertex3d(x1/2, -y1/2, 0);
	glVertex3d(-x1 / 2, -y1 / 2, 0);
	glVertex3d(-x1 / 2, y1 / 2, 0);

	glNormal3d(0.0, -atan2(h, deltay), atan2(deltay, h));			// -y side
	glVertex3d(-x1 / 2, -y1/ 2, 0);
	glVertex3d(x1 / 2, -y1 / 2, 0);
	glVertex3d(x2 / 2, -y2 / 2, -h);
	glVertex3d(-x2 / 2, -y2 / 2, -h);

	glNormal3d(0.0, -atan2(h, deltay), atan2(deltay, h));			// +y side
	glVertex3d(-x1 / 2, y1 / 2, 0);
	glVertex3d(x1 / 2, y1 / 2, 0);
	glVertex3d(x2 / 2, y2 / 2, -h);
	glVertex3d(-x2 / 2, y2 / 2, -h);

	glEnd();
}
