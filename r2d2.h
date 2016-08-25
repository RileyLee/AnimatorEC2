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


class RobotR2D2 : public Model
{
  RangeProperty bodyPositionX, bodyPositionY, bodyPositionZ, bodyTilt, bodyRotation, headRotation, armTilt, footTilt, armLength, footPosition;
	
  Texture2D bodyTexture, batteryTexture, frontierTexture;
public:
	RobotR2D2() :
		Model("R2D2 Robot"),
		bodyPositionX("Robot Position X",-20,20,0,0.1),
		bodyPositionY("Robot Position Z",-20,20,0,0.1),
		bodyPositionZ("Robot Position Y",-20,20,0,0.1),
		bodyRotation("Body Rotation", -180, 180, 0, 0.1),
		bodyTilt("Body Tilt", -90, 90, 0, 0.1),
		headRotation("Head Rotation", -180, 180, 0, .1),
		armTilt("Arm tilt", -90, 90, 30, .1),
		footTilt("Foot Tilt", -30, 30, 0, .1),
		armLength("Arm Length", 1, 10, 3, .1),
		  footPosition("Foot length", -0.8, 0.8, 0.6, .01),

		  bodyTexture("r2d2bodycropped.bmp"),
		  batteryTexture("battery.bmp"),
		  frontierTexture("frontier.bmp"),
		  loaded(false)
	{
		properties.add(&bodyPositionX)
			.add(&bodyPositionZ)
			.add(&bodyPositionY)
			.add(&bodyRotation)
			.add(&bodyTilt)
			.add(&headRotation)
			.add(&armTilt)
			.add(&footTilt)
			.add(&armLength)
		  .add(&footPosition);
		
	}
	virtual void draw();
	virtual void ground(float h);
	virtual void body(float x, float y, float h, float theta, float alpha);
	virtual void head(float phi);
	virtual void flame();
	virtual void upper_arm(float h, float psi);
	virtual void left_arm(float h1, float psi);
	virtual void right_arm(float h1, float psi);
	virtual void y_box(float h);
	virtual void foot(float h, float l1, float w1, float l2, float w2);


	bool loaded;
};

