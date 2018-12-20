#pragma once
#include "pch.h"
#include "Controller.h"
#include <assert.h>

Controller* Controller::m_s_Instance = nullptr;
Controller::Controller()
{
	assert(m_s_Instance == nullptr);
	m_s_Instance = this;
	tmpCurrentState = State::Booting;
	saveFileDirectory = "";
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
