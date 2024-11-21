#include "utils.h"

std::string utils::wideToNarrow(wchar_t* str) {
	// Convert wchar_t* to char* safely
	size_t length = wcslen(str) + 1; // +1 for null-termination
	std::string converted_name(length, '\0'); // Pre-allocate std::string with space
	// Perform the conversion
	size_t converted_size;
	wcstombs_s(&converted_size, &converted_name[0], length, str, length - 1);
	return converted_name;
}

std::string utils::toLower(std::string str) {
	std::string result = str; // Create a copy of the input string
	std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c) {
		return std::tolower(c);
		});
	return result; // Return the lowercase string
}
