#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(255);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);
	
	auto span = 15;
	for (auto radius = 50; radius <= 720; radius += 30) {

		for (auto deg = 0; deg < 720; deg += span - 3) {

			auto location = glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));
			auto noise_location = glm::vec2(cos(deg * DEG_TO_RAD), sin(deg * DEG_TO_RAD));
			auto target_deg = ofMap(ofNoise(glm::vec3(noise_location, ofGetFrameNum() * 0.03 + radius * 0.03)), 0, 1, span * -0.5, span * 0.5);
			auto target = glm::vec2(radius * cos((deg + target_deg) * DEG_TO_RAD), radius * sin((deg + target_deg) * DEG_TO_RAD));

			this->draw_arrow(location, target, ofMap(radius, 150, 300, 8, 15), ofColor(0));

		}
	}
}

//--------------------------------------------------------------
void ofApp::draw_arrow(glm::vec2 location, glm::vec2 target, float size, ofColor color) {

	auto angle = std::atan2(target.y - location.y, target.x - location.x);
	auto distance = glm::distance(target, location);

	if (glm::length(distance) > size * 0) {

		ofPushMatrix();
		ofTranslate(target);

		ofSetColor(color);
		ofFill();
		ofBeginShape();
		ofVertex(glm::vec2(size * cos(angle), size * sin(angle)));
		ofVertex(glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)));
		ofVertex(glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)));
		ofEndShape();

		ofBeginShape();
		ofVertex(glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.25);
		ofVertex(glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.25 - glm::vec2(distance * cos(angle), distance * sin(angle)));
		ofVertex(glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.25 - glm::vec2(distance * cos(angle), distance * sin(angle)));
		ofVertex(glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.25);
		ofEndShape();

		ofPopMatrix();
	}

	ofDrawCircle(location, size * 0.3);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}