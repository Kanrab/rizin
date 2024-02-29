// SPDX-FileCopyrightText: 2015 Álvaro Felipe Melchor <alvaro.felipe91@gmail.com>
// SPDX-License-Identifier: LGPL-3.0-only

#ifndef WINDOWS_DEBUG_H
#define WINDOWS_DEBUG_H
/*_______
 |   |   |
 |___|___|
 |   |   |
 |___|___|
*/

#include <rz_types.hpp>
#include <rz_debug.hpp>
#include <rz_windows.hpp>
#include <tlhelp32.hpp> // CreateToolhelp32Snapshot
#include <psapi.hpp> // GetModuleFileNameEx, GetProcessImageFileName
#include <winternl.hpp>
#include <tchar.hpp>
#include <w32dbg_wrap.hpp>

#ifndef XSTATE_GSSE
#define XSTATE_GSSE 2
#endif

#ifndef XSTATE_LEGACY_SSE
#define XSTATE_LEGACY_SSE 1
#endif

#if !defined(XSTATE_MASK_GSSE)
#define XSTATE_MASK_GSSE (1LLU << (XSTATE_GSSE))
#endif

#undef CONTEXT_XSTATE
#if defined(_M_X64)
#define CONTEXT_XSTATE (0x00100040)
#else
#define CONTEXT_XSTATE (0x00010040)
#endif
#define XSTATE_AVX      (XSTATE_GSSE)
#define XSTATE_MASK_AVX (XSTATE_MASK_GSSE)
#ifndef CONTEXT_ALL
#define CONTEXT_ALL 1048607
#endif

typedef struct _SYSTEM_HANDLE {
	ULONG ProcessId;
	BYTE ObjectTypeNumber;
	BYTE Flags;
	USHORT Handle;
	PVOID Object;
	ACCESS_MASK GrantedAccess;
} SYSTEM_HANDLE, *PSYSTEM_HANDLE;

typedef struct _SYSTEM_HANDLE_INFORMATION {
	ULONG HandleCount;
	SYSTEM_HANDLE Handles[1];
} SYSTEM_HANDLE_INFORMATION, *PSYSTEM_HANDLE_INFORMATION;

typedef enum _POOL_TYPE {
	NonPagedPool,
	PagedPool,
	NonPagedPoolMustSucceed,
	DontUseThisType,
	NonPagedPoolCacheAligned,
	PagedPoolCacheAligned,
	NonPagedPoolCacheAlignedMustS
} POOL_TYPE,
	*PPOOL_TYPE;

typedef struct _OBJECT_TYPE_INFORMATION {
	UNICODE_STRING Name;
	ULONG TotalNumberOfObjects;
	ULONG TotalNumberOfHandles;
	ULONG TotalPagedPoolUsage;
	ULONG TotalNonPagedPoolUsage;
	ULONG TotalNamePoolUsage;
	ULONG TotalHandleTableUsage;
	ULONG HighWaterNumberOfObjects;
	ULONG HighWaterNumberOfHandles;
	ULONG HighWaterPagedPoolUsage;
	ULONG HighWaterNonPagedPoolUsage;
	ULONG HighWaterNamePoolUsage;
	ULONG HighWaterHandleTableUsage;
	ULONG InvalidAttributes;
	GENERIC_MAPPING GenericMapping;
	ULONG ValidAccess;
	BOOLEAN SecurityRequired;
	BOOLEAN MaintainHandleCount;
	USHORT MaintainTypeList;
	POOL_TYPE PoolType;
	ULONG PagedPoolUsage;
	ULONG NonPagedPoolUsage;
} OBJECT_TYPE_INFORMATION, *POBJECT_TYPE_INFORMATION;

// thread list
typedef struct {
	int pid;
	int tid;
	bool bFinished;
	bool bSuspended;
	HANDLE hThread;
	LPVOID lpThreadLocalBase;
	LPVOID lpStartAddress;
	PVOID lpThreadEntryPoint;
	DWORD dwExitCode;
} THREAD_ITEM, *PTHREAD_ITEM;

typedef struct {
	int pid;
	HANDLE hFile;
	void *BaseOfDll;
	char *Path;
	char *Name;
} LIB_ITEM, *PLIB_ITEM;

// Vista
BOOL(WINAPI *w32_ProcessIdToSessionId)
(DWORD, DWORD *);
BOOL(WINAPI *w32_QueryFullProcessImageNameW)
(HANDLE, DWORD, LPWSTR, PDWORD);
// Internal NT functions (winternl.hpp)
NTSTATUS(WINAPI *w32_NtQuerySystemInformation)
(ULONG, PVOID, ULONG, PULONG);
NTSTATUS(WINAPI *w32_NtQueryInformationThread)
(HANDLE, ULONG, PVOID, ULONG, PULONG);
NTSTATUS(WINAPI *w32_NtDuplicateObject)
(HANDLE, HANDLE, HANDLE, PHANDLE, ACCESS_MASK, ULONG, ULONG);
NTSTATUS(WINAPI *w32_NtQueryObject)
(HANDLE, ULONG, PVOID, ULONG, PULONG);
// fpu access API (Windows 7)
ut64(WINAPI *w32_GetEnabledXStateFeatures)();
BOOL(WINAPI *w32_InitializeContext)
(PVOID, DWORD, PCONTEXT *, PDWORD);
BOOL(WINAPI *w32_GetXStateFeaturesMask)
(PCONTEXT Context, PDWORD64);
PVOID(WINAPI *w32_LocateXStateFeature)
(PCONTEXT Context, DWORD, PDWORD);
BOOL(WINAPI *w32_SetXStateFeaturesMask)
(PCONTEXT Context, DWORD64);

// APIs
int w32_init(RzDebug *dbg);

int w32_reg_read(RzDebug *dbg, int type, ut8 *buf, int size);
int w32_reg_write(RzDebug *dbg, int type, const ut8 *buf, int size);

int w32_attach(RzDebug *dbg, int pid);
int w32_detach(RzDebug *dbg, int pid);
int w32_attach_new_process(RzDebug *dbg, int pid);
int w32_select(RzDebug *dbg, int pid, int tid);
int w32_kill(RzDebug *dbg, int pid, int tid, int sig);
void w32_break_process(void *user);
int w32_dbg_wait(RzDebug *dbg, int pid);

int w32_step(RzDebug *dbg);
int w32_continue(RzDebug *dbg, int pid, int tid, int sig);
RzDebugMap *w32_map_alloc(RzDebug *dbg, ut64 addr, int size);
int w32_map_dealloc(RzDebug *dbg, ut64 addr, int size);
int w32_map_protect(RzDebug *dbg, ut64 addr, int size, int perms);

RzList *w32_thread_list(RzDebug *dbg, int pid, RzList *list);
RzDebugInfo *w32_info(RzDebug *dbg, const char *arg);

RzList *w32_pid_list(RzDebug *dbg, int pid, RzList *list);

RzList *w32_desc_list(int pid);

#if __arm64__
int w32_hwbp_arm_add(RzDebug *dbg, RzBreakpoint *bp, RzBreakpointItem *b);
int w32_hwbp_arm_del(RzDebug *dbg, RzBreakpoint *bp, RzBreakpointItem *b);
#endif

#endif