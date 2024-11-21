#pragma once
#include "../Header Files/pch.h"


class Process
{
private:
	std::uint32_t		ID{};
	void*				handle{};
	std::wstring		name{};// wstring so name can be stored as a wstring and used from getID. If needed to convert ill make a converter or use some windows conversion
	// Extra 
	uintptr_t			remoteGetProcAddr = 0;
	uintptr_t			remoteLoadLibraryA = 0;
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
	//bool isProcessRunning();
	std::uint32_t	getID(const std::wstring str);
	void*			getHandle(const std::uint32_t id);

	uintptr_t		getModuleAddress(const char* dll_name);
	uintptr_t		getModuleFuncAddress(const char* dll_name, const char* function_name);
private:
	uintptr_t		LoadRemoteLibrary(const char* module_name);
public:
};
