#include <stdio.h>
#include <Windows.h>

void main() /*Load a DLL and manually jump to one of its functions. Currently 32 bit only*/
{
	HMODULE hTargetDll = LoadLibraryA("code - dll - patched entry.exe");
	if (!hTargetDll)
	{
		printf("[!] LoadLibraryA failed. Error: %d\n", GetLastError());
		return;
	}
	printf("[+] Target DLL base address: 0x%p\n", hTargetDll);
	
	// precalculated RVA
	DWORD target_fucntion_rva = 0x1040;

	// the absolute address of our target function is the sum
	// of the Dll's base address + the precalculated offset
	// from that base address
	DWORD target_fucntion_absolute_address = ((DWORD)hTargetDll + target_fucntion_rva);

	// create a C function pointer pointing to our target function (w/C function pointer cast).
	// this way we can call the target function from C (w/out assembly)
	void (*target_function_pointer)(char*) = (void(__cdecl*)(char*))target_fucntion_absolute_address;

	// call our target function w/variables we control
	char str[0x100] = { 0 };
	memcpy(str, "\x38\x4a\x14\x4b\x1d\x5e\x0e\x4b\x0f\x52\x02\x47\x1f\x41\x1e\x5c\x4c\x5d"
				"\x35\x6b\x2f\x3e\x6b\x3f\x6d\x33\x66\x32\x23\x66\x3f\x6b\x7a\x38\x7d\x3e"
				"\x66\x39\x6f\x7e\x75\x00", 41);
	target_function_pointer(str); // if the function had a return value we could inspect it too
	printf("[+] target function output: %s\n", str);
	printf("[+] done\n");
}