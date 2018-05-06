#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofBackground(39);
	ofSetWindowTitle("Insta");

	ofEnableDepthTest();
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(270);
	ofRotateZ(230);

	for (int i = 0; i < 200; i++) {

		vector<ofPoint> points;
		int z_param = ofRandom(250);
		int deg_param = ofRandom(360);
		ofColor color;
		color.setHsb(ofRandom(255), 255, 255);

		for (int i = 0; i < 15; i++) {
			
			int z = (z_param + ((ofGetFrameNum() + i) * 5)) % 500 - 250;
			int deg = deg_param + (ofGetFrameNum() + i) * 5;
			ofPoint point = this->make_rect_point(250, deg, z);
			points.push_back(point);
		}
		
		for (int i = 1; i < points.size(); i++) {

			if (points[i - 1].distance(points[i]) < 100) {
			
				ofSetColor(color, ofMap(points[i - 1].y + points[i - 1].x, -500, 500, 64, 255));
				ofDrawLine(points[i - 1], points[i]);
			}
		}

	}

	this->cam.end();
}

//--------------------------------------------------------------
ofPoint ofApp::make_rect_point(float half_len, int deg, int z) {

	int param = (deg + 45) / 90;
	ofPoint point;

	switch (param % 4) {

	case 0:

		return ofPoint(half_len, ofMap((deg + 45) % 90, 0, 89, -half_len, half_len),z);
	case 1:

		return  ofPoint(ofMap((deg + 45) % 90, 0, 89, half_len, -half_len), half_len, z);
	case 2:

		return ofPoint(-half_len, ofMap((deg + 45) % 90, 0, 89, half_len, -half_len), z);
	case 3:

		return ofPoint(ofMap((deg + 45) % 90, 0, 89, -half_len, half_len), -half_len, z);
	default:

		return ofPoint();
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}