#include "utils.h"
#include <string>
#include <boost/nowide/convert.hpp>
#include <type_traits>
#include <fstream>
#include <cwctype>   


std::string utils::wideToNarrow(std::wstring_view wide_str) {
	return boost::nowide::narrow(wide_str);
}

std::wstring utils::narrowToWide(std::string_view narrow_str) {
	return boost::nowide::widen(narrow_str);
}

// Could be std::ranges but whatever. StringType::value_type for the char type, should be to be excplicit in template::value_type
template <typename StringType>
StringType toLower(StringType str) {
	std::transform(str.begin(), str.end(), str.begin(), [](auto c) {
		if constexpr (std::is_same_v<typename StringType::value_type, char>) {
			return std::tolower(c);
		}
		else if constexpr (std::is_same_v<typename StringType::value_type, wchar_t>) {
			return std::towlower(c);
		}
		else {
			std::cout << "[-] Unknown string type\n";
		}
		});
	return str;
}

template <typename CharType>
std::basic_string<CharType> toLower(const CharType* str)
{
	return toLower(std::basic_string<CharType>(str));
}
template <typename CharType>
std::basic_string<CharType> toLower(const std::basic_string_view<CharType> str)
{
	return toLower(std::basic_string<CharType>(str));
}