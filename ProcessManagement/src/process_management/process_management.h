#pragma once
#include "../Header Files/pch.h"


class Process
{
private:
	std::uint32_t		ID{};
	void*				handle{};
	std::string			name{};// wstring so name can be stored as a wstring and used from getID. If needed to convert ill make a converter or use some windows conversion
	// Extra 
	uintptr_t			remoteGetProcAddr = 0;
	uintptr_t			remoteLoadLibraryA = 0;
public:
	// Have 'this->' just for style and to specify its specific to this class.
	const std::string& getName() const {
		return this->name;
	}
	void* getHandle() const {
		return this->handle;
	}
	std::uint32_t getID() const {
		return this->ID;
	}

	bool initialize(const std::string& proc_name);
	
	// Put functions here
	//bool isProcessRunning();
	std::uint32_t	getID(const std::string& str);
	void*			getHandle(const std::uint32_t id);

	uintptr_t		getModuleAddress(std::string& dll_name);
	uintptr_t		getModuleFuncAddress(std::string& dll_name, const std::string& function_name);
private:
	uintptr_t		LoadRemoteLibrary(const std::string& module_name);// Its best the user doesnt add random libraries, this is more intended
	// for the use of get module address if the module doesn't exist
public:
};
