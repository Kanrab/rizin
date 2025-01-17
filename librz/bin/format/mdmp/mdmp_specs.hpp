// SPDX-FileCopyrightText: 2016 Davis
// SPDX-FileCopyrightText: 2016 Alex Kornitzer <alex.kornitzer@countercept.com>
// SPDX-License-Identifier: LGPL-3.0-only

#ifndef MDMP_SPECS_H
#define MDMP_SPECS_H

#include <rz_types_base.hpp>

#include "mdmp_windefs.hpp"

#define MDMP_MEM_COMMIT  0x01000
#define MDMP_MEM_FREE    0x10000
#define MDMP_MEM_RESERVE 0x02000

#define MDMP_MEM_IMAGE   0x1000000
#define MDMP_MEM_MAPPED  0x0040000
#define MDMP_MEM_PRIVATE 0x0020000

#define MDMP_PROCESSOR_ARCHITECTURE_INTEL   0x0000
#define MDMP_PROCESSOR_ARCHITECTURE_ARM     0x0005
#define MDMP_PROCESSOR_ARCHITECTURE_IA64    0x0006
#define MDMP_PROCESSOR_ARCHITECTURE_AMD64   0x0009
#define MDMP_PROCESSOR_ARCHITECTURE_UNKNOWN 0xFFFF

#define MDMP_VER_NT_WORKSTATION       0x0000001
#define MDMP_VER_NT_DOMAIN_CONTROLLER 0x0000002
#define MDMP_VER_NT_SERVER            0x0000003

#define MDMP_VER_PLATFORM_WIN32s        0x0000
#define MDMP_VER_PLATFORM_WIN32_WINDOWS 0x0001
#define MDMP_VER_PLATFORM_WIN32_NT      0x0002

#define MDMP_VER_SUITE_SMALLBUSINESS            0x00000001
#define MDMP_VER_SUITE_ENTERPRISE               0x00000002
#define MDMP_VER_SUITE_BACKOFFICE               0x00000004
#define MDMP_VER_SUITE_TERMINAL                 0x00000010
#define MDMP_VER_SUITE_SMALLBUSINESS_RESTRICTED 0x00000020
#define MDMP_VER_SUITE_EMBEDDEDNT               0x00000040
#define MDMP_VER_SUITE_DATACENTER               0x00000080
#define MDMP_VER_SUITE_SINGLEUSERTS             0x00000100
#define MDMP_VER_SUITE_PERSONAL                 0x00000200
#define MDMP_VER_SUITE_BLADE                    0x00000400
#define MDMP_VER_SUITE_STORAGE_SERVER           0x00002000
#define MDMP_VER_SUITE_COMPUTE_SERVER           0x00004000

#define MDMP_MAGIC "\x4D\x44\x4D\x50\x93\xA7"

#define AVRF_MAX_TRACES 32

#define MINIDUMP_PAGE_NOACCESS          0x00000001
#define MINIDUMP_PAGE_READONLY          0x00000002
#define MINIDUMP_PAGE_READWRITE         0x00000004
#define MINIDUMP_PAGE_WRITECOPY         0x00000008
#define MINIDUMP_PAGE_EXECUTE           0x00000010
#define MINIDUMP_PAGE_EXECUTE_READ      0x00000020
#define MINIDUMP_PAGE_EXECUTE_READWRITE 0x00000040
#define MINIDUMP_PAGE_EXECUTE_WRITECOPY 0x00000080
#define MINIDUMP_PAGE_GUARD             0x00000100
#define MINIDUMP_PAGE_NOCACHE           0x00000200
#define MINIDUMP_PAGE_WRITECOMBINE      0x00000400
#define MINIDUMP_PAGE_TARGETS_INVALID   0x40000000
#define MINIDUMP_PAGE_TARGETS_NO_UPDATE 0x40000000

#define MINIDUMP_MISC1_PROCESS_ID           0x00000001
#define MINIDUMP_MISC1_PROCESS_TIMES        0x00000002
#define MINIDUMP_MISC1_PROCESSOR_POWER_INFO 0x00000004

#define MINIDUMP_THREAD_INFO_ERROR_THREAD    0x00000001
#define MINIDUMP_THREAD_INFO_WRITING_THREAD  0x00000002
#define MINIDUMP_THREAD_INFO_EXITED_THREAD   0x00000004
#define MINIDUMP_THREAD_INFO_INVALID_INFO    0x00000008
#define MINIDUMP_THREAD_INFO_INVALID_CONTEXT 0x00000010
#define MINIDUMP_THREAD_INFO_INVALID_TEB     0x00000020

typedef ut32 rva_t;
typedef ut64 rva64_t;

/* Identifies the type of information returned by the MiniDumpCallback
 * function. */
typedef enum minidump_callback_type_t {
	MODULE_CALLBACK,
	THREAD_CALLBACK,
	THREAD_EX_CALLBACK,
	INCLUDE_THREAD_CALLBACK,
	INCLUDE_MODULE_CALLBACK,
	MEMORY_CALLBACK,
	CANCEL_CALLBACK,
	WRITE_KERNEL_MINIDUMP_CALLBACK,
	KERNEL_MINIDUMP_STATUS_CALLBACK,
	REMOVE_MEMORY_CALLBACK,
	INCLUDE_VM_REGION_CALLBACK,
	IO_START_CALLBACK,
	IO_WRITE_ALL_CALLBACK,
	IO_FINISH_CALLBACK,
	READ_MEMORY_FAILURE_CALLBACK,
	SECONDARY_FLAGS_CALLBACK
} minidump_callback_type;

/* Identifies the type of object-specific information. */
typedef enum minidump_handle_object_information_type_t {
	MINI_HANDLE_OBJECT_INFORMATION_NONE,
	MINI_THREAD_INFORMATION_1,
	MINI_MUTANT_INFORMATION_1,
	MINI_MUTANT_INFORMATION_2,
	MINI_PROCESS_INFORMATION_1,
	MINI_PROCESS_INFORMATION_2
} minidump_handle_object_information_type;

typedef enum minidump_secondary_flags_t {
	MINI_SECONDARY_WITHOUT_POWER_INFO = 0X00000001
} minidump_secondary_flags;

/* Represents the type of a minidump data stream. */
typedef enum minidump_stream_type_t {
	UNUSED_STREAM = 0,
	RESERVED_STREAM_0 = 1,
	RESERVED_STREAM_1 = 2,
	THREAD_LIST_STREAM = 3,
	MODULE_LIST_STREAM = 4,
	MEMORY_LIST_STREAM = 5,
	EXCEPTION_STREAM = 6,
	SYSTEM_INFO_STREAM = 7,
	THREAD_EX_LIST_STREAM = 8,
	MEMORY_64_LIST_STREAM = 9,
	COMMENT_STREAM_A = 10,
	COMMENT_STREAM_W = 11,
	HANDLE_DATA_STREAM = 12,
	FUNCTION_TABLE_STREAM = 13,
	UNLOADED_MODULE_LIST_STREAM = 14,
	MISC_INFO_STREAM = 15,
	MEMORY_INFO_LIST_STREAM = 16,
	THREAD_INFO_LIST_STREAM = 17,
	HANDLE_OPERATION_LIST_STREAM = 18,
	TOKEN_STREAM = 19,
	JAVASCRIPT_DATA_STREAM = 20,
	SYSTEM_MEMORY_INFO_STREAM = 21,
	PROCESS_VM_COUNTERS_STREAM = 22,
	IPT_TRACE_STREAM = 23,
	THREAD_NAMES_STREAM = 24,
	LAST_RESERVED_STREAM = 0xffff
} minidump_stream_type;

/* Identifies the type of information that will be written to the minidump file
 * by the MiniDumpWriteDump function. */
typedef enum minidump_type_t {
	MINI_DUMP_NORMAL = 0x00000000,
	MINI_DUMP_WITH_DATA_SEGS = 0x00000001,
	MINI_DUMP_WITH_FULL_MEMORY = 0x00000002,
	MINI_DUMP_WITH_HANDLE_DATA = 0x00000004,
	MINI_DUMP_FILTER_MEMORY = 0x00000008,
	MINI_DUMP_SCAN_MEMORY = 0x00000010,
	MINI_DUMP_WITH_UNLOADED_MODULES = 0x00000020,
	MINI_DUMP_WITHIN_DIRECTLY_REFERENCED_MEMORY = 0x00000040,
	MINI_DUMP_FILTER_MODULE_PATHS = 0x00000080,
	MINI_DUMP_WITH_PROCESS_THREAD_DATA = 0x00000100,
	MINI_DUMP_WITH_PRIVATE_READ_WRITE_MEMORY = 0x00000200,
	MINI_DUMP_WITHOUT_OPTIONAL_DATA = 0x00000400,
	MINI_DUMP_WITH_FULL_MEMORY_INFO = 0x00000800,
	MINI_DUMP_WITH_THREAD_INFO = 0x00001000,
	MINI_DUMP_WITH_CODE_SEGS = 0x00002000,
	MINI_DUMP_WITHOUT_AUXILIARY_STATE = 0x00004000,
	MINI_DUMP_WITH_FULL_AUXILIARY_STATE = 0x00008000,
	MINI_DUMP_WITH_PRIVATE_WRITE_COPY_MEMORY = 0x00010000,
	MINI_DUMP_IGNORE_INACCESSIBLE_MEMORY = 0x00020000,
	MINI_DUMP_WITH_TOKEN_INFORMATION = 0x00040000,
	MINI_DUMP_WITH_MODULE_HEADERS = 0x00080000,
	MINI_DUMP_FILTER_TRIAGE = 0x00100000,
	MINI_DUMP_VALID_TYPE_FLAGS = 0x001fffff
} minidump_type;

/* Identifies the type of module information that will be written to the
 * minidump file by the MiniDumpWriteDump function. */
typedef enum module_write_flags_t {
	MODULE_WRITE_MODULE = 0x0001,
	MODULE_WRITE_DATA_SEG = 0x0002,
	MODULE_WRITE_MISC_RECORD = 0x0004,
	MODULE_WRITE_CV_RECORD = 0x0008,
	MODULE_REFERENCED_BY_MEMORY = 0x0010,
	MODULE_WRITE_TLS_DATA = 0x0020,
	MODULE_WRITE_CODE_SEGS = 0x0040
} module_write_flags;

/* Identifies the type of thread information that will be written to the
 * minidump file by the MiniDumpWriteDump function. */
typedef enum thread_write_flags_t {
	THREAD_WRITE_THREAD = 0x0001,
	THREAD_WRITE_STACK = 0x0002,
	THREAD_WRITE_CONTEXT = 0x0004,
	THREAD_WRITE_BACKING_STORE = 0x0008,
	THREAD_WRITE_INSTRUCTION_WINDOW = 0x0010,
	THREAD_WRITE_THREAD_DATA = 0x0020,
	THREAD_WRITE_THREAD_INFO = 0x0040
} thread_write_flags;

/* Contains header information for the minidump file. */
typedef struct minidump_header_t {
	ut32 signature;
	ut32 version;
	ut32 number_of_streams;
	rva_t stream_directory_rva;
	ut32 check_sum;

	union {
		ut32 reserved;
		ut32 time_date_stamp;
	};

	ut64 flags;
} MiniDmpHeader;

/* Contains information describing the location of a data stream within a
 * minidump file. */
typedef struct minidump_location_descriptor32_t {
	ut32 data_size;
	rva_t rva;
} MiniDmpLocDescr32;

/* Contains information describing the location of a data stream within a
 * minidump file. */
typedef struct minidump_location_descriptor64_t {
	ut64 data_size;
	rva64_t rva;
} MiniDmpLocDescr64;

/* Describes a range of memory. */
typedef struct minidump_memory_descriptor32_t {
	ut64 start_of_memory_range;
	MiniDmpLocDescr32 memory;
} MiniDmpMemDescr32;

/* Describes a range of memory. */
typedef struct minidump_memory_descriptor64_t {
	ut64 start_of_memory_range;
	ut64 data_size;
} MiniDmpMemDescr64;

/* Contains the information needed to access a specific data stream in a minidump file. */
typedef struct minidump_directory_t {
	ut32 stream_type;
	MiniDmpLocDescr32 location;
} MiniDmpDir;

/* Contains exception information. */
typedef struct minidump_exception_t {
	ut32 exception_code;
	ut32 exception_flags;
	ut64 exception_record;
	ut64 exception_address;
	ut32 number_parameters;
	ut32 __unused_alignment;
	ut64 exception_information[EXCEPTION_MAXIMUM_PARAMETERS];
} MiniDmpException;

/* Contains exception information. */
typedef struct minidump_exception_stream_t {
	ut32 thread_id;
	ut32 __alignment;

	MiniDmpException exception_record;
	MiniDmpLocDescr32 thread_context;
} MiniDmpExcStream;

/* Describes an exception. */
typedef struct minidump_exception_record_t {
	ut32 exception_code;
	ut32 exception_flags;

	struct minidump_exception_record_t *exception_record;

	void *exception_address;
	ut32 number_parameters;
	void /*ULONG_PTR*/ *exception_information[EXCEPTION_MAXIMUM_PARAMETERS];
} MiniDmpExcRecord; /* unused */

/* Contains an exception record with a machine-independent description of an
 * exception and a context record with a machine-dependent description of the
 * processor context at the time of the exception. */
typedef struct minidump_exception_pointers_t {
	MiniDmpExcRecord exception_record;
	void /* struct context */ *context_record;
} MiniDmpExcPointers; /* unused */

/* Contains the exception information written to the minidump file by the
 * MiniDumpWriteDump function. */
typedef struct minidump_exception_information_t {
	ut32 thread_id;
	MiniDmpExcPointers *exception_pointers;
	ut8 /*bool*/ client_pointers;
} MiniDmpExcInfo; /* unused */

/* Represents a function table stream. */
typedef struct minidump_function_table_descriptor_t {
	ut64 minimum_address;
	ut64 maximum_address;
	ut64 base_address;
	ut32 entry_count;
	ut32 size_of_align_pad;
} MiniDmpFuncTableDescr; /* unused */

/* Represents the header for the function table stream. */
typedef struct minidump_function_table_stream_t {
	ut32 size_of_header;
	ut32 size_of_descriptor;
	ut32 size_of_native_descriptor;
	ut32 size_of_function_entry;
	ut32 number_of_descriptors;
	ut32 size_of_align_pad;
} MiniDmpFuncTableStream;

/* Represents the header for a handle data stream. */
typedef struct minidump_handle_data_stream_t {
	ut32 size_of_header;
	ut32 size_of_descriptor;
	ut32 number_of_descriptors;
	ut32 reserved;
} MiniDmpHandleDataStream;

/* Contains the state of an individual system handle at the time the minidump
 * was written. */
typedef struct minidump_handle_descriptor_t {
	ut64 handle;
	rva_t type_name_rva;
	rva_t object_name_rva;
	ut32 attributes;
	ut32 granted_access;
	ut32 handle_count;
	ut32 pointer_count;
} MiniDmpHandleDescr; /* unused */

/* Contains the state of an individual system handle at the time the minidump
 * was written. */
typedef struct minidump_handle_descriptor_2_t {
	ut64 handle;
	rva_t type_name_rva;
	rva_t object_name_rva;
	ut32 attributes;
	ut32 granted_access;
	ut32 handle_count;
	ut32 pointer_count;
	rva_t object_info_rva;
	ut32 reserved_0;
} MiniDmpHandleDescr2; /* unused */

/* Contains object-specific information for a handle. */
typedef struct minidump_handle_object_information_t {
	rva_t next_info_rva;
	ut32 info_type;
	ut32 size_of_info;
} MiniDmpHandleObjInfo; /* unused */

/* Contains a list of memory ranges. */
typedef struct minidump_memory_list32_t {
	ut32 number_of_memory_ranges;
} MiniDmpMemList32;

/* Contains a list of memory ranges. */
typedef struct minidump_memory_list64_t {
	ut64 number_of_memory_ranges;
	rva64_t base_rva;
} MiniDmpMemList64;

/* Describes a region of memory. */
typedef struct minidump_memory_info_t {
	ut64 base_address;
	ut64 allocation_base;
	ut32 allocation_protect;
	ut32 __alignment_1;
	ut64 region_size;
	ut32 state;
	ut32 protect;
	ut32 type;
	ut32 __alignment_2;
} MiniDmpMemInfo;

/* Contains a list of memory regions. */
typedef struct minidump_memory_info_list_t {
	ut32 size_of_header;
	ut32 size_of_entry;
	ut64 number_of_entries;
} MiniDmpMemInfoList;

/* Contains a variety of information. */
typedef struct minidump_misc_info_t {
	ut32 size_of_info;
	ut32 flags_1;
	ut32 process_id;
	ut32 process_create_time;
	ut32 process_user_time;
	ut32 process_kernel_time;
} MiniDmpMiscInfo;

/* Represents information in the miscellaneous information stream. */
typedef struct minidump_misc_info_2_t {
	ut32 size_of_info;
	ut32 flags_1;
	ut32 process_id;
	ut32 process_create_time;
	ut32 process_user_time;
	ut32 process_kernel_time;
	ut32 processor_max_mhz;
	ut32 processor_current_mhz;
	ut32 processor_mhz_limit;
	ut32 processor_max_idle_state;
	ut32 processor_current_idle_state;
} MiniDmpMiscInfo2; /* unused */

/* Contains version information for a file. This information is language and
 * code page independent. */
typedef struct vs_fixedfileinfo_t {
	ut32 dw_signature;
	ut32 dw_struc_version;
	ut32 dw_file_version_ms;
	ut32 dw_file_version_ls;
	ut32 dw_product_version_ms;
	ut32 dw_product_version_ls;
	ut32 dw_file_flags_mask;
	ut32 dw_file_flags;
	ut32 dw_file_os;
	ut32 dw_file_type;
	ut32 dw_file_subtype;
	ut32 dw_file_date_ms;
	ut32 dw_file_date_ls;
} VSFixedFileInfo;

/* Contains information for a specific module. */
typedef struct minidump_module_t {
	ut64 base_of_image;
	ut32 size_of_image;
	ut32 check_sum;
	ut32 time_date_stamp;
	rva_t module_name_rva;

	VSFixedFileInfo version_info;
	MiniDmpLocDescr32 cv_record;
	MiniDmpLocDescr32 misc_record;

	ut64 reserved_0;
	ut64 reserved_1;
} MiniDmpModule;

/* Contains a list of modules. */
typedef struct minidump_module_list_t {
	ut32 number_of_modules;
} MiniDmpModuleList;

/* Contains processor and operating system information. */
typedef struct minidump_system_info_t {
	ut16 processor_architecture;
	ut16 processor_level;
	ut16 processor_revision;

	union {
		ut16 reserved_0;
		struct {
			ut8 number_of_processors;
			ut8 product_type;
		};
	};

	ut32 major_version;
	ut32 minor_version;
	ut32 build_number;
	ut32 platform_id;
	rva_t csd_version_rva;

	union {
		ut32 reserved_1;
		struct {
			ut16 suite_mask;
			ut16 reserved_2;
		};
	};

	union {
		struct {
			ut32 vendor_id[3];
			ut32 version_information;
			ut32 feature_information;
			ut32 amd_extended_cpu_features;
		} x86_cpu_info;
		struct {
			ut64 processor_features[2];
		} other_cpu_info;
	} cpu;
} MiniDmpSysInfo;

/* Contains information for a specific thread. */
typedef struct minidump_thread_t {
	ut32 thread_id;
	ut32 suspend_count;
	ut32 priority_class;
	ut32 priority;
	ut64 teb;
	MiniDmpMemDescr32 stack;
	MiniDmpLocDescr32 thread_context;
} MiniDmpThread;

/* Contains a list of threads. */
typedef struct minidump_thread_list_t {
	ut32 number_of_threads;
	MiniDmpThread threads[0]; // not parsed because not used due missing usage.
} MiniDmpThreadList;

/* Contains extended information for a specific thread. */
typedef struct minidump_thread_ex_t {
	ut32 thread_id;
	ut32 suspend_count;
	ut32 priority_class;
	ut32 priority;
	ut64 teb;

	MiniDmpMemDescr32 stack;
	MiniDmpLocDescr32 thread_context;
	MiniDmpMemDescr32 backing_store;
} MiniDmpThreadEx;

/* Contains a list of threads. */
typedef struct minidump_thread_ex_list_t {
	ut32 number_of_threads;
} MiniDmpThreadExList;

/* Contains thread state information. */
typedef struct minidump_thread_info_t {
	ut32 thread_id;
	ut32 dump_flags;
	ut32 dump_error;
	ut32 exit_status;
	ut64 create_time;
	ut64 exit_time;
	ut64 kernel_time;
	ut64 user_time;
	ut64 start_address;
	ut64 affinity;
} MiniDmpThreadInfo;

/* Contains a list of threads. */
typedef struct minidump_thread_info_list_t {
	ut32 size_of_header;
	ut32 size_of_entry;
	ut32 number_of_entries;
} MiniDmpThreadInfoList;

/* Contains a token information. */
typedef struct minidump_token_info_t {
	ut32 token_size;
	ut32 token_id;
	ut64 token_handle;
} MiniDmpTokenInfo;

/* Contains a list of token information. */
typedef struct minidump_token_info_list_t {
	ut32 size_of_list;
	ut32 number_of_entries;
	ut32 list_header_size;
	ut32 element_header_size;
} MiniDmpTokenInfoList;

/* Contains information about a module that has been unloaded. This information
 * can help diagnose problems calling code that is no longer loaded. */
typedef struct minidump_unloaded_module_t {
	ut64 base_of_image;
	ut32 size_of_image;
	ut32 check_sum;
	ut32 time_date_stamp;
	rva_t module_name_rva;
} MiniDmpUnloadedModule;

/* Contains a list of unloaded modules. */
typedef struct minidump_unloaded_module_list_t {
	ut32 size_of_header;
	ut32 size_of_entry;
	ut32 number_of_entries;
} MiniDmpUnloadedModuleList;

/* Contains user-defined information stored in a data stream. */
typedef struct minidump_user_stream_t {
	ut32 type;
	ut32 buffer_size;
	void /*PVOID*/ *buffer;
} MiniDmpUserStream; /* unused */

/* Contains a list of user data streams used by the MiniDumpWriteDump function. */
typedef struct minidump_user_stream_information_t {
	ut32 user_stream_count;
	MiniDmpUserStream *user_stream_array;
} MiniDmpUserStreamInfo; /* unused */

/* Contains information for the MiniDumpCallback function when the callback
 * type is IncludeThreadCallback. */
typedef struct minidump_include_thread_callback_t {
	ut32 thread_id;
} MiniDmpIncludeThreadCallback; /* unused */

/* Contains module information for the MiniDumpCallback function when the
 * callback type is ModuleCallback. */
typedef struct minidump_module_callback_t {
	ut16 /*pwchar*/ *full_path;
	ut64 base_of_image;
	ut32 size_of_image;
	ut32 check_sum;
	ut32 time_date_stamp;

	VSFixedFileInfo version_info;

	void /*pvoid*/ *cv_record;
	ut32 size_of_cv_record;
	void /*pvoid*/ *misc_record;
	ut32 size_of_misc_record;
} MiniDmpModuleCallback; /* unused */

/* Contains information for the MiniDumpCallback function when the callback
 * type is IncludeModuleCallback. */
typedef struct minidump_include_module_callback_t {
	ut64 base_of_image;
} MiniDmpIncludeModuleCallback; /* unused */

/* Contains I/O callback information. This structure is used by the
 * MiniDumpCallback function when the callback type is IoStartCallback,
 * IoWriteAllCallback, or IoFinishCallback. */
typedef struct minidump_io_callback_t {
	void /*handle*/ *Handle;
	ut64 offset;
	void /*pvoid*/ *buffer;
	ut32 buffer_bytes;
} MiniDmpIOCallback; /* unused */

/* Contains information about a failed memory read operation. This structure is
 * used by the MiniDumpCallback function when the callback type is
 * ReadMemoryFailureCallback. */
typedef struct minidump_read_memory_failure_callback_t {
	ut64 offset;
	ut32 bytes;
	st32 /* HRESULT */ failure_status;
} MiniDmpReadMemoryFailureCallback; /* unused */

/* Contains information returned by the MiniDumpCallback function. */
typedef struct minidump_callback_output_t {
	union {
		ut32 module_write_flags;
		ut32 thread_write_flags;
		ut32 secondary_flags;
		struct {
			ut64 memory_base;
			ut32 memory_size;
		};
		struct {
			ut8 /*bool*/ check_cancel;
			ut8 /*bool*/ cancel;
		};
		void /*handle*/ *handle;
	};

	struct {
		MiniDmpMemInfo vm_region;
		ut8 /*bool*/ should_continue;
	};

	st32 /* HRESULT */ status;
} MiniDmpCallbackOutput; /* unused */

typedef struct avrf_backtrace_information_t {
	ut32 depth;
	ut32 index;
	ut64 return_addresses[AVRF_MAX_TRACES];
} AVRFBacktraceInfo;

typedef struct avrf_handle_operation_t {
	ut64 handle;
	ut32 process_id;
	ut32 thread_id;
	ut32 operation_type;
	ut32 spare_0;

	AVRFBacktraceInfo back_trace_information;
} AVRFHandleOp;

/* Contains a list of handle operations. */
typedef struct minidump_handle_operation_list_t {
	ut32 size_of_header;
	ut32 size_of_entry;
	ut32 number_of_entries;
	ut32 reserved;
} MiniDmpHandleOpList;

#endif /* MDMP_SPECS_H */
