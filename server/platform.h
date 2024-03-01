#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#include <stdint.h>

#if defined(__unix__) || defined(__unix) || defined(__APPLE__) || defined(__MACH__)

extern uint64_t PAGE_SIZE;

#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>

#define ftrunc(fd, len) ftruncate(fd, len)

#define mem_map(addr, len, prot, flags, fd, offset) mmap(addr, len, prot, flags, fd, offset)
#define mem_unmap(addr, len) munmap(addr, len)

#define find_page_size(){\
	PAGE_SIZE = sysconf(_SC_PAGE_SIZE);\
}
	




#elif defined(_WIN64)
#include <io.h>
#include <windows.h>
#include <memoryapi.h>

#define ftrunc(fd, len) _chsize_s(fd, len)

#define mem_map(addr, len, prot, flags, fd, offset) MapViewOfFile(fd, FILE_MAP_ALL_ACCESS, offset&0xFFFFFFFF00000000, offset&0x00000000FFFFFFFF, len)
#define mem_unmap(addr, len) UnmapViewOfFile(addr)

#define find_page_size(){\
	SYSTEM_INFO sysInfo;\
	GetSystemInfo(&sysInfo);\
	PAGE_SIZE = sysInfo.dwPageSize;\
}


#endif



#endif