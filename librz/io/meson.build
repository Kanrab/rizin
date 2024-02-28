io_plugins_list = [
  'ar',
  'fd',
  'bfdbg',
  'bochs',
  'debug',
  'default',
  'dmp',
  'gdb',
  'gzip',
  'http',
  'ihex',
  'srec',
  'mach',
  'malloc',
  'null',
  'procpid',
  'ptrace',
  'rzpipe',
  'rzweb',
  'rap',
  'self',
  'shm',
  'sparse',
  'tcp',
  'winkd',
  'winedbg',
  'zip'
]

if get_option('use_gpl')
  io_plugins_list += 'qnx'
endif

if host_machine.system() == 'windows'
  io_plugins_list+= [
    'windbg',
    'w32dbg',
    'w32',
  ]
endif

io_plugins = {
  'conf_name': 'plugins_io',
  'base_cname': 'rz_io_plugin_',
  'list': io_plugins_list,
}

rz_io_sources = [
  'io.cpp',
  'io_fd.cpp',
  'io_map.cpp',
  'io_memory.cpp',
  'io_cache.cpp',
  'io_desc.cpp',
  'io_plugin.cpp',
  'ioutils.cpp',
  'p_cache.cpp',
  'serialize_io.cpp',
  'p/io_ar.cpp',
  'p/io_fd.cpp',
  'p/io_bfdbg.cpp',
  'p/io_bochs.cpp',
  'p/io_debug.cpp',
  'p/io_dmp.cpp',
  'p/io_default.cpp',
  'p/io_gdb.cpp',
  'p/io_gzip.cpp',
  'p/io_http.cpp',
  'p/io_ihex.cpp',
  'p/io_mach.cpp',
  'p/io_malloc.cpp',
  'p/io_null.cpp',
  'p/io_procpid.cpp',
  'p/io_ptrace.cpp',
  'p/io_rzpipe.cpp',
  'p/io_rzweb.cpp',
  'p/io_rap.cpp',
  'p/io_self.cpp',
  'p/io_shm.cpp',
  'p/io_sparse.cpp',
  'p/io_srec.cpp',
  'p/io_tcp.cpp',
  'p/io_winkd.cpp',
  'p/io_winedbg.cpp',
  'p/io_zip.cpp',
]

if host_machine.system() == 'windows'
  rz_io_sources += [
    'p/io_windbg.cpp',
    'p/io_w32.cpp',
    'p/io_w32dbg.cpp',
  ]
endif

rz_io_deps = [
  dependency('rzgdb'),
  dependency('rzwinkd'),
  libzip_dep,
  dependency('rzar'),
  th,
  lrt,
  rz_util_dep,
  rz_socket_dep,
  rz_hash_dep,
  rz_crypto_dep,
  rz_cons_dep,
  platform_deps,
]

if get_option('use_gpl')
  rz_io_deps += dependency('rzqnx')
  rz_io_sources += 'p/io_qnx.cpp'
endif

if host_machine.system() == 'windows'
  rz_io_deps += dependency('rzw32dbg_wrap')
endif

if use_ptrace_wrap
  rz_io_deps += dependency('ptrace-wrap', default_options: ['is_static_build=' + is_static_build.to_string()])
endif

rz_io = library('rz_io', rz_io_sources,
  include_directories: platform_inc,
  dependencies: rz_io_deps,
  install: true,
  implicit_include_directories: false,
  install_rpath: rpath_lib,
  soversion: rizin_libversion,
  version: rizin_version,
  name_suffix: lib_name_suffix,
  name_prefix: lib_name_prefix,
)

rz_io_dep = declare_dependency(link_with: rz_io,
                              include_directories: platform_inc)
meson.override_dependency('rz_io', rz_io_dep)

modules += { 'rz_io': {
    'target': rz_io,
    'dependencies': ['rz_util', 'rz_socket', 'rz_hash', 'rz_crypto', 'rz_cons'],
    'plugins': [io_plugins]
}}
