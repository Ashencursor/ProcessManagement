#pragma once
#include "pch.h"
#include <algorithm>


namespace utils
{
	std::string wideToNarrow(wchar_t* str);
	std::string toLower(std::string str);
}