#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "IniReader.h"
#include "IniWriter.h"
#include "Map.h"


using namespace sf;
using namespace std;

class Controller
{
private:
	enum State { Booting, InMenu, Playing, Loading, Incutscene };
	enum SecondaryState { InGameMainMenu, CharacterMenu, None };
	static Controller* m_s_Instance;

	
	// Primary Variables
	const int numberOfSecondaryStates = 2;
	State currentState, tmpCurrentState;
	bool initialized, tmpInitialized;
	bool running, tmpRunning;
	bool loadFile, tmpLoadFile; // TODO: change them to secondary
	string saveFileDirectory, tmpSaveFileDirectory; // TODO: change them to secondary

	bool executeSecondary[2], tmpExecuteSecondary[2];
	bool secondaryInitialized[2], tmpSecondaryInitialized[2];
	// --------------
	// Secondary Variables
	RenderWindow * window;
	Map *map;
	int resolutionID;
	int musicVolume;
	int soundVolume;
	IniReader* iniReader;
	IniWriter* iniWriter;
	unsigned int restrictResolutions;
	vector<Vector2u> availableResolutions =
	{
		Vector2u(800,600),
		Vector2u(1024,768),
		Vector2u(1366,768),
		Vector2u(1600,900),
		Vector2u(1600,1200),
		Vector2u(1680,1050),
		Vector2u(1920,1080),
		Vector2u(1920,1200)
	};

	// --------------

public: 
	Controller();
	static void setState(State);
	static int getState();
	static void setSecondaryInitialized(SecondaryState, bool);
	static bool isSecondaryInitialized(SecondaryState);
	static void setExecuteSecondary(SecondaryState, bool);
	static bool isExecuteSecondary(SecondaryState);
	static void setRunning(bool);
	static bool isRunning();
	static void setInitialized(bool);
	static bool isInitialized();
	static void setLoadFile(bool);
	static bool isLoadFile();
	static void setSaveFileDirectory(string);
	static string getSaveFileDirectory();
	
	static void applyChanges();
	static void clearState(bool hardFlush = false, bool secondary = false, SecondaryState state = SecondaryState::None);
	
	static Vector2f getViewSize();
	static Vector2f getCameraCenter();
	static Vector2f getCameraOffset();
	static void setWindow(RenderWindow * window);
	static Map * getMap();
	static void setMap(Map *mp);

	static void setResolutionID(int);
	static int getResolutionID();
	static int getResolutionWidth();
	static int getResolitionHeight();
	static void setMusicVolume(int);
	static int getMusicVolume();
	static void setSoundVolume(int);
	static int getSoundVolume();
	static vector<Vector2u> getAvailableResolutions();
	static void quit();
	static void loadVars();
	static void saveVars();

	static const State BOOTING = State::Booting;
	static const State IN_MENU = State::InMenu;
	static const State LOADING = State::Loading;
	static const State PLAYING = State::Playing;
	static const State IN_CUT_SCENE = State::Incutscene;
	static const SecondaryState IN_GAME_MAIN_MENU = SecondaryState::InGameMainMenu;
	static const SecondaryState CHARACTER_MENU = SecondaryState::CharacterMenu;
	static const SecondaryState NONE = SecondaryState::None;

private:
	void checkVars();
};


