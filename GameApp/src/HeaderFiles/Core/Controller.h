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
	enum SecondaryState { InGameMainMenu, None };
	static Controller* m_s_Instance;

	Map *map;

	const int numberOfSecondaryStates = 1;
	State currentState, tmpCurrentState;
	bool initialized, tmpInitialized;
	bool running, tmpRunning;
	bool loadFile, tmpLoadFile;
	string saveFileDirectory, tmpSaveFileDirectory;

	bool executeSecondary[1], tmpExecuteSecondary[1];
	bool secondaryInitialized[1], tmpSecondaryInitialized[1];
	
	int resolutionID;
	int musicVolume;
	int soundVolume;
	IniReader* iniReader;
	IniWriter* iniWriter;

	vector<Vector2i> availableResolutions =
	{
		Vector2i(800,600),
		Vector2i(1024,768),
		Vector2i(1280,1024),
		Vector2i(1366,768),
		Vector2i(1600,900),
		Vector2i(1600,1200),
		Vector2i(1680,1050),
		Vector2i(1920,1080),
		Vector2i(1920,1200)
	};

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
	
	static Map * getMap();
	void setMap(Map *mp);

	static void setResolutionID(int);
	static int getResolutionID();
	static int getResolutionWidth();
	static int getResolitionHeight();
	static void setMusicVolume(int);
	static int getMusicVolume();
	static void setSoundVolume(int);
	static int getSoundVolume();
	static vector<Vector2i> getAvailableResolutions();

	static void loadVars();
	static void saveVars();

	static const State BOOTING = State::Booting;
	static const State IN_MENU = State::InMenu;
	static const State LOADING = State::Loading;
	static const State PLAYING = State::Playing;
	static const State IN_CUT_SCENE = State::Incutscene;
	static const SecondaryState IN_GAME_MAIN_MENU = SecondaryState::InGameMainMenu;
	static const SecondaryState NONE = SecondaryState::None;

};

