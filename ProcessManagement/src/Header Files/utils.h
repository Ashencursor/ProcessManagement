#pragma once
#include "pch.h"
#include <algorithm>
#include <string>
#include <type_traits>
#include <fstream>
#include <cwctype>   

namespace utils
{
	std::string wideToNarrow(std::wstring_view wide_str);
	std::wstring narrowToWide(std::string_view narrow_str);

	// Could declare them, didnt find much online about that though. I can always change it though.
	// Could be std::ranges but whatever. StringType::value_type for the char type, should be to be excplicit in template::value_type
	template <typename StringType>
	StringType toLower(StringType str);

	template <typename CharType>
	std::basic_string<CharType> toLower(const CharType* str);

	template <typename CharType>
	std::basic_string<CharType> toLower(const std::basic_string_view<CharType> str);
}