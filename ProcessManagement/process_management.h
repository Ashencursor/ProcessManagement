#pragma once
#include "pch.h"


class Process
{
	std::uint32_t		pid{};
	void*				handle{};
	std::wstring		name{};// wstring so name can be stored as a wstring and used from getID. If needed to convert ill make a converter or use some windows conversion

public:
	const std::wstring& getName() const {
		return name;
	}
	void* getHandle() const {
		return handle;
	}
	std::uint32_t getID() const {
		return pid;
	}

	void initialize(const wchar_t* proc_name);
	
	// Put functions here
	std::uint32_t	resolveID();
	void*			getHandle();

	void*			getModuleHandle();
	uintptr_t		getModuleAddress();
	uintptr_t		getModuleFuncAddress();
};
