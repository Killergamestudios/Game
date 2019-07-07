#pragma once
#include "../../Header Files/Core/Controller.h"
#include <assert.h>
#include <windows.h>

using namespace sf;

Controller* Controller::m_s_Instance = nullptr;
Controller::Controller()
{
	
	assert(m_s_Instance == nullptr);
	m_s_Instance = this;
	tmpCurrentState = State::Booting;
	saveFileDirectory = "";

	char full_path[MAX_PATH];
	GetFullPathNameA("options.ini", MAX_PATH, full_path, NULL);
	iniReader = new IniReader(full_path);
	iniWriter = new IniWriter(full_path);
	loadVars();
}

// switch to new State
// use the static constants of class Controller
void Controller::setState(State newState)
{
	m_s_Instance->tmpCurrentState = newState;
}

// Returns current State of Game
// 0 - Booting
// 1 - InMenu
// 2 - Loading
// 3 - Playing
// 4 - InCutScene
int Controller::getState()
{
		return m_s_Instance->currentState;
}

void Controller::setSecondaryInitialized(SecondaryState state, bool flag)
{
	m_s_Instance->tmpSecondaryInitialized[state] = flag;
}

bool Controller::isSecondaryInitialized(SecondaryState state)
{
	return m_s_Instance->tmpSecondaryInitialized[state];
}

void Controller::setExecuteSecondary(SecondaryState state, bool flag)
{
	m_s_Instance->tmpExecuteSecondary[state] = flag;
}

bool Controller::isExecuteSecondary(SecondaryState state)
{
	return m_s_Instance->tmpExecuteSecondary[state];
}

void Controller::setRunning(bool state)
{
		m_s_Instance->tmpRunning = state;
}

bool Controller::isRunning()
{
	return m_s_Instance->running;
}

void Controller::setInitialized(bool state)
{
	m_s_Instance->tmpInitialized = state;
}

bool Controller::isInitialized()
{
	return m_s_Instance->initialized;
}

void Controller::setLoadFile(bool state)
{
	m_s_Instance->tmpLoadFile = state;
}

bool Controller::isLoadFile()
{
	return m_s_Instance->loadFile;
}

void Controller::setSaveFileDirectory(string path)
{
	m_s_Instance->tmpSaveFileDirectory = path;
}

string Controller::getSaveFileDirectory()
{
	return m_s_Instance->saveFileDirectory;
}

// Applies all changes during the current gmae loop
// Transfers the value from tmp variables to controller variables.
void Controller::applyChanges()
{

	m_s_Instance->currentState = m_s_Instance->tmpCurrentState;

	m_s_Instance->initialized = m_s_Instance->tmpInitialized;

	m_s_Instance->running = m_s_Instance->tmpRunning;

	m_s_Instance->loadFile = m_s_Instance->tmpLoadFile;

	m_s_Instance->saveFileDirectory = m_s_Instance->tmpSaveFileDirectory;

	for (int i = 0; i < m_s_Instance->numberOfSecondaryStates; i++)
	{
		m_s_Instance->secondaryInitialized[i] = m_s_Instance->tmpSecondaryInitialized[i];
		m_s_Instance->executeSecondary[i] = m_s_Instance->tmpExecuteSecondary[i];
	}

}

void Controller::clearState(bool hardFlush, bool secondary, SecondaryState state)
{
	if (hardFlush)
	{
		m_s_Instance->tmpCurrentState = m_s_Instance->currentState;
		m_s_Instance->initialized = m_s_Instance->tmpInitialized = false;
		m_s_Instance->running = m_s_Instance->tmpRunning = false;
		m_s_Instance->loadFile = m_s_Instance->tmpLoadFile = false;
		m_s_Instance->saveFileDirectory = m_s_Instance->tmpSaveFileDirectory = "";

		for (int i = 0; i < m_s_Instance->numberOfSecondaryStates; i++)
		{
			m_s_Instance->secondaryInitialized[i] = m_s_Instance->tmpSecondaryInitialized[i] = false;
			m_s_Instance->executeSecondary[i] = m_s_Instance->tmpExecuteSecondary[i] = false;
		}
		return;
	}

	
	if (secondary) {
		m_s_Instance->secondaryInitialized[state] = m_s_Instance->tmpSecondaryInitialized[state] = false;
		m_s_Instance->executeSecondary[state] = m_s_Instance->tmpExecuteSecondary[state] = false;
		return;
	}

	m_s_Instance->initialized = m_s_Instance->tmpInitialized = false;
	m_s_Instance->running = m_s_Instance->tmpRunning = false;

}

Vector2f Controller::getViewSize() 
{
	return m_s_Instance->window->getView().getSize();
}

Vector2f Controller::getCameraOffset()
{
	return Vector2f(m_s_Instance->window->getView().getCenter().x - m_s_Instance->window->getView().getSize().x / 2.f,
		m_s_Instance->window->getView().getCenter().y - m_s_Instance->window->getView().getSize().y / 2.f);
}

Vector2f Controller::getCameraCenter()
{
	return m_s_Instance->window->getView().getCenter();
}

void Controller::setWindow(RenderWindow * window)
{
	m_s_Instance->window = window;
}

Map * Controller::getMap()
{
	return m_s_Instance->map;
}

void Controller::setMap(Map * mp)
{
	m_s_Instance->map = mp;
}

void Controller::setResolutionID(int value)
{
	m_s_Instance->resolutionID = value;
}

int Controller::getResolutionID()
{
	return m_s_Instance->resolutionID;
}

int Controller::getResolutionWidth()
{
	return m_s_Instance->availableResolutions[m_s_Instance->resolutionID].x;
}

int Controller::getResolitionHeight()
{
	return m_s_Instance->availableResolutions[m_s_Instance->resolutionID].y;
}

void Controller::setMusicVolume(int value)
{
	m_s_Instance->musicVolume = value;
}

int Controller::getMusicVolume()
{
	return m_s_Instance->musicVolume;
}

void Controller::setSoundVolume(int value)
{
	m_s_Instance->soundVolume = value;
}

int Controller::getSoundVolume()
{
	return m_s_Instance->soundVolume;
}

vector<Vector2u> Controller::getAvailableResolutions()
{
	return m_s_Instance->availableResolutions;
}

void Controller::quit()
{
	m_s_Instance->window->close();
	saveVars();
}

void Controller::loadVars()
{
	m_s_Instance->resolutionID = stoi(m_s_Instance->iniReader->ReadVar("Display", "resolutionID", ""));
	m_s_Instance->musicVolume = stoi(m_s_Instance->iniReader->ReadVar("Audio", "musicVolume", ""));
	m_s_Instance->soundVolume = stoi(m_s_Instance->iniReader->ReadVar("Audio", "soundVolume", ""));
	m_s_Instance->checkVars();
}

void Controller::checkVars() {
	// Check for overflows in music and sound
	if (musicVolume > 100) {
		musicVolume = 100;
	}
	else if (musicVolume < 0) {
		musicVolume = 0;
	}

	if (soundVolume > 100) {
		soundVolume = 100;
	}
	else if (soundVolume < 0) {
		soundVolume = 0;
	}

	// Check resolution ID. Must not surpass pc's resolution
	if (resolutionID >= (int)availableResolutions.size()) {
		resolutionID = (int)(availableResolutions.size()) - 1;
	}
	else if (resolutionID < 0) {
		resolutionID = 0;
	}

	Vector2u desktopRes (VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height);
	for (int i = resolutionID; i >= 0; i--) {
		if (availableResolutions[i].x <= desktopRes.x && availableResolutions[i].y <= desktopRes.y) {
			resolutionID = i;
			break;
		}
	}
}

void Controller::saveVars()
{
	m_s_Instance->iniWriter->WriteVar("Display", "resolutionID", to_string(m_s_Instance->resolutionID));
	m_s_Instance->iniWriter->WriteVar("Audio", "musicVolume", to_string(m_s_Instance->musicVolume));
	m_s_Instance->iniWriter->WriteVar("Audio", "soundVolume", to_string(m_s_Instance->soundVolume));
}

