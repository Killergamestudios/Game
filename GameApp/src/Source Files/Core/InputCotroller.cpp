#include "../../Header Files/Core/InputCotroller.h"
#include <assert.h>
#include <windows.h>

InputCotroller* InputCotroller::m_s_Instance = nullptr;

InputCotroller::InputCotroller()
{
	assert(m_s_Instance == nullptr);
	m_s_Instance = this;
}

