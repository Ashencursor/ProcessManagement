#pragma once
#include "pch.h"
#include <algorithm>


namespace utils
{
	std::string wideToNarrow(std::wstring_view wide_str);
	std::wstring narrowToWide(std::string_view narrow_str);
	void toLower(std::string& str);
	void toLower(std::wstring& str);
	void toLower(wchar_t* str);
	void toLower(char* str);

}