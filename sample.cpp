// The sample box model.  You should build a file
// very similar to this for when you make your model in
// order to plug in to the animator project.

#pragma warning (disable : 4305)
#pragma warning (disable : 4244)
#pragma warning (disable : 4786)
#pragma warning (disable : 4312)


#include "modelerview.h"
#include "modelerdraw.h"
#include "modelerui.h"
#include "vault.h"
#include "FL/glut.H"
#include "model.h"
#include "cameras.h"
#include <cmath>
#include <time.h>
#include "r2d2.h"


void ground(float h);
void base(float h);
void rotation_base(float h);
void lower_arm(float h);
void upper_arm(float h);
void claw(float h);
void y_box(float h);

class RobotArm : public Model
{
	RangeProperty baseRotation, lowerTilt, upperTilt, clawRotation, baseLength,
		lowerLength, upperLength;

public:
    RobotArm() :
		Model("Orig Model"),
		baseRotation("body rotation (theta)", -180, 180, 0,0.1),
		lowerTilt("lower arm tilt (phi)", 15, 95, 55, .1),
		upperTilt("upper arm tilt (psi)", 0, 135, 30, .1),
		clawRotation("claw rotation (cr)", -30, 180, 0, .1),
		baseLength("base height (h1)", .5, 10, .8, .1),
		lowerLength("lower arm length (h2)", 1, 10, 2.5, .1),
		upperLength("upper arm length (h3)", 1, 10, 2.5, .1)
	{
		properties.add(&baseRotation)
				  .add(&lowerTilt)
				  .add(&upperTilt)
				  .add(&clawRotation)
				  .add(&baseLength)
				  .add(&lowerLength)
				  .add(&upperLength);
	}
	virtual void draw();
};


// We are going to override (is that the right word?) the draw()
// method of ModelerView to draw out RobotArm
void RobotArm::draw()
{
	/* pick up the slider values */
	float theta = baseRotation.getValue();
	float phi = lowerTilt.getValue();
	float psi = upperTilt.getValue();
	float cr = clawRotation.getValue();
	float h1 = baseLength.getValue();
	float h2 = lowerLength.getValue();
	float h3 = upperLength.getValue();




	static GLfloat lmodel_ambient[] = {0.4,0.4,0.4,1.0};

	// define the model
	glPushMatrix();
		ground(-0.2);

		base(0.8);

		glTranslatef( 0.0, 0.8, 0.0 );			// move to the top of the base
		glRotatef( theta, 0.0, 1.0, 0.0 );		// turn the whole assembly around the y-axis. 
		rotation_base(h1);						// draw the rotation base

		glTranslatef( 0.0, h1, 0.0 );			// move to the top of the base
		glRotatef( phi, 0.0, 0.0, 1.0 );		// rotate around the z-axis for the lower arm
		glTranslatef( -0.1, 0.0, 0.4 );
		lower_arm(h2);							// draw the lower arm

		glTranslatef( 0.0, h2, 0.0 );			// move to the top of the lower arm
		glRotatef( psi, 0.0, 0.0, 1.0 );		// rotate  around z-axis for the upper arm
		upper_arm(h3);							// draw the upper arm

		glTranslatef( 0.0, h3, 0.0 );
		glRotatef( cr, 0.0, 0.0, 1.0 );
		claw(1.0);

	glPopMatrix();
}

void ground(float h) 
{
	//glDisable(GL_LIGHTING);
	//glColor3f(0.65,0.45,0.2);
	setDiffuseColor(0.65,0.45,0.2);
	setAmbientColor(0.65,0.45,0.2);
	glPushMatrix();
		glScalef(30,0,30);
		y_box(h);
	glPopMatrix();
	//glEnable(GL_LIGHTING);
}

void base(float h) {
	setDiffuseColor( 0.85, 0.75, 0.25 );
	setAmbientColor( 0.25, 0.25, 0.25 );
	glPushMatrix();
		glPushMatrix();
			glTranslatef(1.0, h / 2.0, 0.75);
			drawCylinder(0.25, h / 2.0, h / 2.0);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(1.0, h / 2.0, -1.0);
			drawCylinder(0.25, h / 2.0, h / 2.0);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-1.0, h / 2.0, 0.75);
			drawCylinder(0.25, h / 2.0, h / 2.0);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-1.0, h / 2.0, -1.0);
			drawCylinder(0.25, h / 2.0, h / 2.0);
		glPopMatrix();
	glScalef(4.0f, h, 4.0f);
	y_box(1.0f);
	glPopMatrix();
}

void rotation_base(float h) {
	setDiffuseColor( 0.85, 0.75, 0.25 );
	setAmbientColor( 0.95, 0.75, 0.25 );
	glPushMatrix();
		glPushMatrix();
			glScalef(4.0, h, 4.0);
			y_box(1.0f); // the rotation base
		glPopMatrix();
		setDiffuseColor( 0.15, 0.15, 0.65 );
		setAmbientColor( 0.15, 0.15, 0.65 );
		glPushMatrix();
			glTranslatef(-0.5, h, -0.6);
			glScalef(2.0, h, 1.6);
			y_box(1.0f); // the console
		glPopMatrix();
		setDiffuseColor( 0.65, 0.65, 0.65 );
		setAmbientColor( 0.65, 0.65, 0.65 );
		glPushMatrix();
			glTranslatef( 0.5, h, 0.6 );
			glRotatef( -90.0, 1.0, 0.0, 0.0 );
			drawCylinder( h, 0.05, 0.05 ); // the pipe
		glPopMatrix();
	glPopMatrix();
}

void lower_arm(float h) {					// draw the lower arm
	setDiffuseColor( 0.85, 0.75, 0.25 );
	setAmbientColor( 0.95, 0.75, 0.25 );
	y_box(h);
}

void upper_arm(float h) {					// draw the upper arm
	setDiffuseColor( 0.85, 0.75, 0.25 );
	setAmbientColor( 0.95, 0.75, 0.25 );
	glPushMatrix();
	glScalef( 1.0, 1.0, 0.7 );
	y_box(h);
	glPopMatrix();
}

void claw(float h) {
	setDiffuseColor( 0.25, 0.25, 0.85 );
	setAmbientColor( 0.25, 0.25, 0.85 );

	glBegin( GL_TRIANGLES );

	glNormal3d( 0.0, 0.0, 1.0);		// +z side
	glVertex3d( 0.5, 0.0, 0.5);
	glVertex3d(-0.5, 0.0, 0.5);
	glVertex3d( 0.5,   h, 0.5);

	glNormal3d( 0.0, 0.0, -1.0);	// -z side
	glVertex3d( 0.5, 0.0, -0.5);
	glVertex3d(-0.5, 0.0, -0.5);
	glVertex3d( 0.5,   h, -0.5);

	glEnd();

	glBegin( GL_QUADS );

	glNormal3d( 1.0,  0.0,  0.0);	// +x side
	glVertex3d( 0.5, 0.0,-0.5);
	glVertex3d( 0.5, 0.0, 0.5);
	glVertex3d( 0.5,   h, 0.5);
	glVertex3d( 0.5,   h,-0.5);

	glNormal3d( 0.0,-1.0, 0.0);		// -y side
	glVertex3d( 0.5, 0.0, 0.5);
	glVertex3d( 0.5, 0.0,-0.5);
	glVertex3d(-0.5, 0.0,-0.5);
	glVertex3d(-0.5, 0.0, 0.5);

	glEnd();
}

void y_box(float h) {

	glBegin( GL_QUADS );

	glNormal3d( 1.0 ,0.0, 0.0);			// +x side
	glVertex3d( 0.25,0.0, 0.25);
	glVertex3d( 0.25,0.0,-0.25);
	glVertex3d( 0.25,  h,-0.25);
	glVertex3d( 0.25,  h, 0.25);

	glNormal3d( 0.0 ,0.0, -1.0);		// -z side
	glVertex3d( 0.25,0.0,-0.25);
	glVertex3d(-0.25,0.0,-0.25);
	glVertex3d(-0.25,  h,-0.25);
	glVertex3d( 0.25,  h,-0.25);

	glNormal3d(-1.0, 0.0, 0.0);			// -x side
	glVertex3d(-0.25,0.0,-0.25);
	glVertex3d(-0.25,0.0, 0.25);
	glVertex3d(-0.25,  h, 0.25);
	glVertex3d(-0.25,  h,-0.25);

	glNormal3d( 0.0, 0.0, 1.0);			// +z side
	glVertex3d(-0.25,0.0, 0.25);
	glVertex3d( 0.25,0.0, 0.25);
	glVertex3d( 0.25,  h, 0.25);
	glVertex3d(-0.25,  h, 0.25);

	glNormal3d( 0.0, 1.0, 0.0);			// top (+y)
	glVertex3d( 0.25,  h, 0.25);
	glVertex3d( 0.25,  h,-0.25);
	glVertex3d(-0.25,  h,-0.25);
	glVertex3d(-0.25,  h, 0.25);

	glNormal3d( 0.0,-1.0, 0.0);			// bottom (-y)
	glVertex3d( 0.25,0.0, 0.25);
	glVertex3d(-0.25,0.0, 0.25);
	glVertex3d(-0.25,0.0,-0.25);
	glVertex3d( 0.25,0.0,-0.25);

	glEnd();
}

float GLOBAL_restitution = 0.0;

/** The scene, which includes the lights and models. */


class Scene : public Model {
protected:
	///////////////////////////////// TEXTURES ////////////////////////////////////
	Texture2D texture;

	///////////////////////////////// SHADERS /////////////////////////////////////
	ShaderProgram blinnPhong, textureBP, cartoon;

	//////////////////////////////// PROPERTIES ///////////////////////////////////
	// Switches for spheres
	BooleanProperty useTexture;
	// Switch for showing/hiding reference unit sphere
	BooleanProperty showReferenceUnitSphere;

	// Lets you pick what shapes to use for the default model!
	ChoiceProperty shapeChoice;

	ChoiceProperty shaderChoice;

	// Some slider properties
	RangeProperty rotateX, rotateY;
	RangeProperty brightness;

	// Diffuse color picker
	RGBProperty diffuse;

  RangeProperty restitution;


	// Scene lights
	PointLight pointLight;
	DirectionalLight directionalLight;

	// A robot arm model
	RobotArm robotArm;
	RobotR2D2 R2D2;

public:
  ParticleSystem ps;

	/** Modeler calls this to get our particle system. */
	ParticleSystem* getParticleSystem() {
		return &ps;
	}

	RangeProperty sphereCenterX, sphereCenterY, sphereCenterZ;


	/** Construct the scene */
	Scene() :
		// You have to call the parent class's constructor, to provide a
		// name for the model.
		Model("Scene"),

		// Construct textures and shaders. 
		// They won't be loaded until the model is drawn for the first time.
		texture("checkers.png"),
		blinnPhong("shader.vert", "shader.frag", NULL),
		textureBP("shader.vert", "texture_shader.frag", NULL),
		cartoon("shader.vert", "cartoon.frag", NULL),

		// Call the constructors for the lights
		pointLight("Point Light", GL_LIGHT1, /**direction part**/ -5, 5, 5, /**diffuse part**/ 1.0, 0.5, 0.5,
		/**specular part**/ 1.0, 0.5, 0.5, /**ambient part**/ .2f, 0.1, 0.1 /**attenuation part**/, 0.4, 0.7, 0),
		directionalLight("Directional Light", GL_LIGHT0, /**direction part**/ 5, 5, 5, /**diffuse part**/ 0.0f, 0.5, 0.5f,
		/**specular part**/ 0.0f, 0.5f, 0.5f)

		// Now, call the constructors for each Property:
		, useTexture("Use Checkered Texture", true),
		showReferenceUnitSphere("Show Reference Unit Sphere", false),
		shapeChoice("Model Shape:", "Sphere|Cube|Cylinder|Torus|Icosahedron|Teapot|Revolution|Orig Model|R2D2", 0), //557 animator UI allows shapes + Model
		//useShader("Use My Shader", true),
		shaderChoice("Shader", "None|Blinn-Phong|Blinn-Phong+Texture|Cartoon", 0),
		rotateX("Rotate Basic Shape X", -180, 180, 0, 1),
		rotateY("Rotate Basic Shape Y", -180, 180, 0, 1),
		brightness("Brightness", 0.0f, 1.0f, 1.0f, 0.1f),
		diffuse("Diffuse Color", 1.0, 0.7, .4),
	  restitution("Restituion", 0.0f, 1.0f, 0.5f, 0.01f),
		sphereCenterX("Collision Sphere Center (X)", -6.0, 6.0, -5.0, 0.1),
		sphereCenterY("Collision Sphere Center (Y)", -6.0, 6.0, 0, 0.1),
		sphereCenterZ("Collision Sphere Center (Z)", -6.0, 6.0, 0, 0.1)

	{
		// If you have child Models, like the MobileLight model from model.h,
		// you can add their property groups, and they will appear in the list
		// in the top left corner of Modeler, under this model's entry:
		properties.add(pointLight.getProperties())
			.add(directionalLight.getProperties())
			;
		properties.add(robotArm.getProperties());
		properties.add(R2D2.getProperties());

		// Finally, add all the properties to this model's PropertyGroup.
		properties.add(&useTexture);
		properties.add(&showReferenceUnitSphere)
			.add(&shapeChoice);
		properties.add(&shaderChoice)
			.add(&rotateX)
			.add(&rotateY);
		properties.add(&sphereCenterX)
			.add(&sphereCenterY)
			.add(&sphereCenterZ);
		properties.add(&brightness)
		  .add(&diffuse).add(&restitution);
	}



	/**
	 * Modeler calls this method once an OpenGL context becomes available,
	 * (which happens before the first time draw() is called), and whenever
	 * you click the "Reload Textures and Shaders" menu option.
	 *
	 * Make sure you call the load() methods of each of your textures and
	 * shaders here.
	 */
	void load() {
		texture.load();
		blinnPhong.load();
		textureBP.load();
		cartoon.load();
	}

	/**
	 * Modeler calls this method many times a second when the Animate
	 * checkbox is checked.
	 */
	void tick() {
		// You can put code here to increment animation counters for
		// extra credit.
	}

	/** Draw the model. */
	void drawModel() {
		int divisions = 16;
		switch (ModelerDrawState::Instance()->m_quality)
		{
		case HIGH:
			divisions = 64; break;
		case MEDIUM:
			divisions = 20; break;
		case LOW:
			divisions = 12; break;
		case POOR:
			divisions = 8; break;
		}

		// Remember our current modelview matrix, which is in world space.
		glPushMatrix();

		// Rotate around the X-axis
		glRotatef(rotateX.getValue(), 1, 0, 0);

		// Rotate around the Y-axis
		glRotatef(rotateY.getValue(), 0, 1, 0);


		// Draw some object at the origin.
		switch (shapeChoice.getValue()) {
		case 0: // sphere
			glRotatef(-90.f, 1.f, 0.f, 0.f);
			glutSolidSphere(1.0, divisions, divisions);
			glRotatef(90.f, 1.f, 0.f, 0.f);
			break;
		case 1: // box
			glRotatef(-45.f, 0.f, 1.f, 0.f);
			glutSolidCube(2);
			glRotatef(45.f, 0.f, 1.f, 0.f);
			break;
		case 2: // cylinder
			glRotatef(90.f, 1.f, 0.f, 0.f);
			drawCylinder(1.8, 1.0, 1.8);
			glRotatef(-90.f, 1.f, 0.f, 0.f);
			break;
		case 3: // torus
			glutSolidTorus(.5, 1, divisions, divisions);
			break;
		case 4: // icosahedron
			glutSolidIcosahedron();
			break;
		case 5: // teapot
			glutSolidTeapot(1);
			break;
		case 6:
			drawRevolution(1);
			break;
		case 7:
			// Draw the default sphere for collision
			glPopMatrix();
			glPushMatrix();
			glTranslatef(sphereCenterX.getValue(), sphereCenterY.getValue(), sphereCenterZ.getValue());
			glutSolidSphere(1.0, 20, 20); // the 20's are arbitary
			glPopMatrix();
			robotArm.draw();
			break;
		case 8:
		  // Draw the default sphere for collision
		  glPopMatrix();
		  glPushMatrix();
		  glTranslatef(sphereCenterX.getValue(), sphereCenterY.getValue(), sphereCenterZ.getValue());
		  //glutSolidSphere(1.0, 20, 20); // the 20's are arbitary
		  glPopMatrix();
		  R2D2.draw();
		  break;
		}

		if (showReferenceUnitSphere.getValue()) {
			// Now go 1 units in the +y direction,
			// and 1 units in the NEGATIVE x direction.
			glTranslated(-2, -1, 0);
			// Now go 1 units in the +y direction,
			// and 1 units in the NEGATIVE x direction.
			glRotatef(-90.f, 1.f, 0.f, 0.f);
			drawSphere(.5);
			glRotatef(90.f, 1.f, 0.f, 0.f);
			glPopMatrix();
		}

		// Go back to "world space"
		glPopMatrix();

		if (shapeChoice.getValue() != 7 && shapeChoice.getValue() != 8)
		{

			// draw the floor.  here's a basic example of texture mapping.
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
		}
	}


	/** draw the scene. */
	void draw() {
		// the lights must be drawn first, so the other scene elements
		// can get lit!
		pointLight.draw();
		directionalLight.draw();
		//reset colors
		setDiffuseColor(
			diffuse.getRed(),
			diffuse.getGreen(),
			diffuse.getBlue());

		setAmbientColor(0.2, 0.2, 0.2);

		setSpecularColor(1,1,1);
		setShininess(pow(2.71828183f, 3));

		// use the texture if desired.
		if (useTexture.getValue()) {
			texture.use();
		} else {
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		switch(shaderChoice.getValue()) {
		  // none
		case 0:
		  if(glUseProgram) {
			glUseProgram(0);
		  }
		  break;
		  // Blinn-Phong
		case 1:
		  {
		  blinnPhong.use();
		  GLint brightnessVariableLocation = glGetUniformLocation( blinnPhong.getID(), "brightness" );
		  glUniform1f(brightnessVariableLocation, brightness.getValue());
		  break;
		  }
		case 2:
		  {
			textureBP.use();
			GLint brightnessVariableLocation = glGetUniformLocation( blinnPhong.getID(), "brightness" );
			glUniform1f(brightnessVariableLocation, brightness.getValue());
			break;
		  }
		case 3:
		  {
			cartoon.use();
			break;
		  }
		}

		GLOBAL_restitution = restitution.getValue();

		// call a class method that draws our model.
		drawModel();
		// stop applying shaders to objects.
		// this if-statement makes sure that gluseprogram is not a null
		// function pointer (which it will be if glew couldn't initialize).
		if (glUseProgram) {
			glUseProgram(0);
		}

		// stop applying textures to objects
		glBindTexture(GL_TEXTURE_2D, 0);
	}
};

/**
 * the program starts here.
 */

int main()
{
	// tell the fltk library to let us use opengl
	Fl::gl_visual(FL_RGB);

	init_load_curve_file();

	// instantiate modeler
	ModelerUserInterface ui;

	// give modeler your scene.
	// modeler will free this pointer when it exits.
	ui.setModel(new Scene());


	// run the application
    return ui.run();
}




// The sample box model.  You should build a file
// very similar to this for when you make your model in
// order to plug in to the animator project.

#pragma warning (disable : 4305)
#pragma warning (disable : 4244)
#pragma warning (disable : 4786)
#pragma warning (disable : 4312)
