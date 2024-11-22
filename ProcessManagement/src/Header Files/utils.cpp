#include "utils.h"
#include <string>
#include <fstream>
#include <boost/nowide/convert.hpp>


std::string utils::wideToNarrow(std::wstring_view wide_str) {
	return boost::nowide::narrow(wide_str);
}

std::wstring utils::narrowToWide(std::string_view narrow_str) {
	return boost::nowide::widen(narrow_str);
}


void utils::toLower(std::string& str) {
	std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) {
		return std::tolower(c);
	});
}
void utils::toLower(std::wstring& str)
{
	std::transform(str.begin(), str.end(), str.begin(), [](wchar_t c) {
		return std::tolower(c);
	});
}
void utils::toLower(wchar_t* str)
{
	std::transform(str, str + std::wcslen(str), str, [](wchar_t c) {
		return std::tolower(c);
	});
}
void utils::toLower(char* str)
{
	std::transform(str, str + std::strlen(str), str, [](unsigned char c) {
		return std::tolower(c);
	});
}