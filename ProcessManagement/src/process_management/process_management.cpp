#include "../Header Files/pch.h"
#include "process_management.h"
#include <Tlhelp32.h>



bool Process::initialize(const wchar_t* proc_name)
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

std::uint32_t Process::getID(std::wstring str)
{
	PROCESSENTRY32 ProcessInfoPE;
	ProcessInfoPE.dwSize = sizeof(PROCESSENTRY32);
	HANDLE hSnapshot = CreateToolhelp32Snapshot(15, 0);
	Process32First(hSnapshot, &ProcessInfoPE);
	do {
		if (ProcessInfoPE.szExeFile == str)
		{
			CloseHandle(hSnapshot);
			return ProcessInfoPE.th32ProcessID;
		}
	} while (Process32Next(hSnapshot, &ProcessInfoPE));
	CloseHandle(hSnapshot);
	return 0;
}

void* Process::getHandle(std::uint32_t id)
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

void* Process::getModuleHandle()
{
	return nullptr;
}

uintptr_t Process::getModuleAddress()
{
	return uintptr_t();
}

uintptr_t Process::getModuleFuncAddress()
{
	return uintptr_t();
}
