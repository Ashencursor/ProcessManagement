#include "../Header Files/pch.h"
#include "process_management.h"
#include <Tlhelp32.h>
#include <vector>
#include "../Header Files/utils.h"

bool Process::initialize(const std::string& proc_name)
{
	this->ID = getID(proc_name);
	this->handle = getHandle(this->ID);

	if (!this->ID) {
		std::cout << "invalid ID\n";
		return false;
	}
	if (!this->handle) {
		std::cout << "invalid handle\n";
		return false;
	}
	return true;
}

std::uint32_t Process::getID(const std::string& str)
{
	PROCESSENTRY32 ProcessInfoPE;
	ProcessInfoPE.dwSize = sizeof(PROCESSENTRY32);
	HANDLE hSnapshot = CreateToolhelp32Snapshot(15, 0);
	Process32First(hSnapshot, &ProcessInfoPE);
	do {
		if (utils::wideToNarrow(ProcessInfoPE.szExeFile) == str)
		{
			CloseHandle(hSnapshot);
			return ProcessInfoPE.th32ProcessID;
		}
	} while (Process32Next(hSnapshot, &ProcessInfoPE));
	CloseHandle(hSnapshot);
	return 0;
}

void* Process::getHandle(const std::uint32_t id)
{
	if (this->handle) {
		CloseHandle(this->handle);
		this->handle = nullptr;
	}

	this->handle = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, id);
	if (!this->handle) 
		return nullptr;

	return this->handle;
}

uintptr_t Process::getModuleAddress(std::string& dll_name)
{
	uintptr_t moduleBaseAddress = 0;
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, this->ID);
	utils::toLower(dll_name);
	// For conversion

	if (snapshot != INVALID_HANDLE_VALUE) {
		MODULEENTRY32 moduleEntry;
		moduleEntry.dwSize = sizeof(MODULEENTRY32);

		if (Module32First(snapshot, &moduleEntry)) {
			do {
				utils::toLower(moduleEntry.szModule);
				if (utils::wideToNarrow(moduleEntry.szModule) == dll_name) {// wcscmp(moduleEntry.szModule, dll_name) or moduleEntry.szModule == dll_name
					return reinterpret_cast<uintptr_t>(moduleEntry.modBaseAddr);
				}
			} while (Module32Next(snapshot, &moduleEntry));
		}

		CloseHandle(snapshot);
	}

	// Module not found, so load it into the remote process
	moduleBaseAddress = LoadRemoteLibrary(dll_name);
	// Verify if LoadRemoteLibrary succeeded in loading the module
	if (moduleBaseAddress == 0) {
		//std::cout << "Failed to load module: " << dll_name << " in the target process.\n";
	}
	return moduleBaseAddress;
}

uintptr_t Process::getModuleFuncAddress(std::string& dll_name, const std::string& function_name)
{
	// Get remote module address
	uintptr_t remoteModuleAddress{ getModuleAddress(dll_name) };
	if (remoteModuleAddress == 0) {
		std::cerr << "[-] Module not found in the target process: " << dll_name << std::endl;
		return 0;
	}
	// Get the local module handle
	HMODULE localModuleAddress{ GetModuleHandleA(dll_name.data()) };
	if (localModuleAddress == nullptr) {
		localModuleAddress = LoadLibraryA(dll_name.data());
		if (localModuleAddress == nullptr) {
			std::cerr << "[-] Failed to load library: " << dll_name << std::endl;
			return 0;
		}
	}
	// Get the address of the function in the local module
	FARPROC  localModuleFunctionAddress{ GetProcAddress(localModuleAddress, function_name.data()) };
	if (localModuleFunctionAddress == nullptr) {
		std::cerr << "[-] Failed to get function address: " << function_name << std::endl;
		return 0;
	}
	// Calculate the function offset
	uintptr_t functionOffset = reinterpret_cast<uintptr_t>(localModuleFunctionAddress) - reinterpret_cast<uintptr_t>(localModuleAddress);

	// Return the remote function address
	return remoteModuleAddress + functionOffset;
}

// This is kinda weird because loading a library into the target process in this function below uses create remote thread
// and the remoteLoadLibraryA so it does what my manual mapper is avoiding(using loadLibrary). It doesnt totaly matter for 
// the simple games I'm making cheats for now but it will when I get to ac. Just something to worry and think about.
uintptr_t Process::LoadRemoteLibrary(const std::string& module_name)
{
	void* remoteMemory = VirtualAllocEx(handle, nullptr, strlen(module_name.data()) + 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	if (!remoteMemory) {
		return 0;  // Allocation failed
	}

	if (!WriteProcessMemory(handle, remoteMemory, module_name.data(), strlen(module_name.data()) + 1, nullptr)) {
		VirtualFreeEx(handle, remoteMemory, 0, MEM_RELEASE);
		return 0;  // Writing failed
	}

	HANDLE hThread = CreateRemoteThread(handle, nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(remoteLoadLibraryA), remoteMemory, 0, nullptr);
	if (!hThread) {
		VirtualFreeEx(handle, remoteMemory, 0, MEM_RELEASE);
		return 0;  // Failed to create thread
	}

	WaitForSingleObject(hThread, INFINITE);

	uintptr_t hModule = 0;
	GetExitCodeThread(hThread, (LPDWORD)&hModule);

	VirtualFreeEx(handle, remoteMemory, 0, MEM_RELEASE);
	CloseHandle(hThread);

	return hModule;
}
