rz_socket_sources = [
  'socket.cpp',
  'socket_http.cpp',
  'socket_http_server.cpp',
  'socket_serial.cpp',
  'socket_proc.cpp',
  'rzpipe.cpp',
  'socket_rap_client.cpp',
  'socket_rap_server.cpp',
  'run.cpp',
]

dependencies = [utl, rz_util_dep, platform_deps]
rz_socket_deps = []

if sys_openssl.found()
  dependencies += [sys_openssl]
endif

if host_machine.system() == 'haiku'
  dependencies += [
    cc.find_library('network')
  ]
endif

rz_socket = library('rz_socket', rz_socket_sources,
  include_directories: [platform_inc],
  dependencies: dependencies,
  install: true,
  implicit_include_directories: false,
  install_rpath: rpath_lib,
  soversion: rizin_libversion,
  version: rizin_version,
  name_suffix: lib_name_suffix,
  name_prefix: lib_name_prefix,
)

rz_socket_dep = declare_dependency(link_with: rz_socket,
  dependencies: [rz_util_dep],
  include_directories: [platform_inc])
meson.override_dependency('rz_socket', rz_socket_dep)

modules += { 'rz_socket': {
    'target': rz_socket,
    'dependencies': ['rz_util']
}}
