#pragma once
#include "pch.h"
#include "textureHolder.h"
#include <SFML/Graphics.hpp>
#include "object.h"
#include "Engine.h"
#include "fstream"
#include <iostream>

using namespace sf;
using namespace std;

CharacterObject* Engine::SpawnWarrior(Vector2i position) {

	Sprite sprite(TextureHolder::GetTexture("./graphics/Sprites/warrior.png"));
	CharacterObject* warrior = new CharacterObject("Nathan", m_window, "friendly", "warrior", position, sprite);
	
	ifstream myfile;
	myfile.open("./graphics/Characters/warrior.txt");
	
	int *a;
	a = new int[8];
	float *b;
	b = new float[4];
	for (int i = 0; i < 8; i++) {
		myfile >> a[i];
	}
	for (int i = 0; i < 4; i++) {
		myfile >> b[i];
	}
	Stats stats = {a[0],a[1],a[2],a[3],a[4],a[5],a[6],a[7],b[0],b[1],b[2],b[3] };
	delete a;
	delete b;

	//Loading Head Parameters
	a = new int[2];
	b = new float[3];
	
	for (int i = 0; i < 3; i++) {
		myfile >> b[i];
	}
	for (int i = 0; i < 2; i++) {
		myfile >> a[i];
	}
	Head head = {NULL, b[0],b[1],b[2],a[1],a[2]};
	delete a;
	delete b;

	// Loading Body Parameters
	a = new int[2];
	b = new float[3];

	
	for (int i = 0; i < 3; i++) {
		myfile >> b[i];
	}
	for (int i = 0; i < 2; i++) {
		myfile >> a[i];
	}
	Body body = { NULL, b[0],b[1],b[2],a[0],a[1]};
	delete a;
	delete b;

	//Loading Legs
	b = new float[5];
	a = new int[3];
	for (int i = 0; i < 3; i++) {
		myfile >> b[i];
	}
	for (int i = 0; i < 3; i++) {
		myfile >> a[i];
	}
	for (int i = 3; i < 5; i++) {
		myfile >> b[i];
	}
	Legs legs{ NULL, b[0],b[1],b[2],a[0],a[1],a[2],b[3],b[4]};
	delete a;
	delete b;

	//load Right Hand
	b = new float[5];
	a = new int[3];
	for (int i = 0; i < 3; i++) {
		myfile >> b[i];
	}
	for (int i = 0; i < 3; i++) {
		myfile >> a[i];
	}
	for (int i = 3; i < 5; i++) {
		myfile >> b[i];
	}
	RightHand righthand{ NULL, b[0],b[1],b[2],a[0],a[1],a[2],b[3],b[4] };
	delete a;
	delete b;

	//load Left Hand
	b = new float[5];
	a = new int[3];
	for (int i = 0; i < 3; i++) {
		myfile >> b[i];
	}
	for (int i = 0; i < 3; i++) {
		myfile >> a[i];
	}
	for (int i = 3; i < 5; i++) {
		myfile >> b[i];
	}
	leftHand lefthand{ NULL, b[0],b[1],b[2],a[0],a[1],a[2],b[3],b[4] };
	delete a;
	delete b;

	//load statgain
	b = new float[4];
	a = new int[3];

	for (int i = 0; i < 2; i++) {
		myfile >> a[i];
	}
	for (int i = 0; i < 4; i++) {
		myfile >> b[i];
	}
	myfile >> a[2];

	StatGain statgain{ a[0],a[1],b[0],b[1],b[2],b[3],a[2] };
	warrior->spawn(stats, head, body, legs, righthand, lefthand, statgain);
	myfile.close();
	return warrior;
}
