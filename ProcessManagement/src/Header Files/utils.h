#pragma once
#include "pch.h"



namespace utils
{
	// Functions that will most likely be used
	inline HANDLE		geHandle();
	inline DWORD		getID();
	inline HANDLE		getModuleHandle();
	inline uintptr_t	getModuleAddress();
	inline uintptr_t	getModuleFuncAddress();
}