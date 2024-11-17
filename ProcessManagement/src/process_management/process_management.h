#pragma once
#include "../Header Files/pch.h"


class Process
{
	std::uint32_t		ID{};
	void*				handle{};
	std::wstring		name{};// wstring so name can be stored as a wstring and used from getID. If needed to convert ill make a converter or use some windows conversion

public:
	// Have 'this->' just for style and to specify its specific to this class.
	const std::wstring& getName() const {
		return this->name;
	}
	void* getHandle() const {
		return this->handle;
	}
	std::uint32_t getID() const {
		return this->ID;
	}

	bool initialize(const wchar_t* proc_name);
	
	// Put functions here
	std::uint32_t	getID(std::wstring str);
	void*			getHandle(std::uint32_t id);

	void*			getModuleHandle();
	uintptr_t		getModuleAddress();
	uintptr_t		getModuleFuncAddress();
};
