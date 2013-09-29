#pragma once
#include "ofMain.h"
#include "ofxBox2d.h"
#include "player.h"


// -------------------------------------------------

class bicicletorama : public ofBaseApp {
	
public:
	
	void setup();
	void update();
	void draw();
	
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void resized(int w, int h);
	
	int	kk;//debug para ultima tecla apertada
	
	ofxBox2d							box2d;			//	the box2d world
	vector			<ofxBox2dRect>		obstaculos;		//	obstáculos adicionados na mesa
	vector			<player>			jogadores;		//	players extendem box2d rects
	//vector		<ofxBox2dCircle>	circles;		//	default box2d circles
	//vector		<ofxBox2dRect>		boxes;			//	defalut box2d rects
	
};

