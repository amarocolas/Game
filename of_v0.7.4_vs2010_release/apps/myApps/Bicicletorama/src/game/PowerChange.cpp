#include "PowerChange.h"

void PowerChange::setup(b2World * b2dworld, float isPowerUp)
{
	enabled = false;

	box.fixture.isSensor = true;
	if (isPowerUp) {
		//power up
		value = 3.f;
		box.setup(b2dworld, 0, 0, 50, 20);
	} 
	else {
		//power down
		value = 1/4.f;
		box.setup(b2dworld, 0, 0, 30, 30);
	}

	box.setData(new GenericData("powerChange", &value));
}

void PowerChange::update() 
{
	if (enabled && ofGetElapsedTimeMillis() - millis > POWER_CHANGE_LIFE_TIME) {
		box.setPosition(-9999,-9999); //leave it outside the window to remove //TODO trabalhar com b2Body->SetAwake()
		enabled = false;
	}
}

void PowerChange::draw() 
{
	if (enabled) {
		box.draw();
	}
}

void PowerChange::showAt(float x, float y) 
{
	box.body->SetTransform(b2Vec2(b2dNum(x), b2dNum(y)), ofRandom(PI));
	millis = ofGetElapsedTimeMillis();
	enabled = true;
}