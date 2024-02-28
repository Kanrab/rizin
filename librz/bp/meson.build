bp_plugins = {
  'conf_name': 'plugins_bp',
  'base_cname': 'rz_bp_plugin_',
  'list': [
    'arm',
    'bf',
    'mips',
    'ppc',
    'sh',
    'x86'
  ],
}

rz_bp_sources = [
  'bp.cpp',
  'bp_io.cpp',
  'bp_plugin.cpp',
  'bp_traptrace.cpp',
  'bp_watch.cpp',
  'serialize_bp.cpp',
  'p/bp_arm.cpp',
  'p/bp_bf.cpp',
  'p/bp_mips.cpp',
  'p/bp_ppc.cpp',
  'p/bp_sh.cpp',
  'p/bp_x86.cpp'
]

rz_bp = library('rz_bp', rz_bp_sources,
  include_directories: [platform_inc],
  dependencies: [rz_util_dep],
  install: true,
  implicit_include_directories: false,
  install_rpath: rpath_lib,
  soversion: rizin_libversion,
  version: rizin_version,
  name_suffix: lib_name_suffix,
  name_prefix: lib_name_prefix,
)

rz_bp_dep = declare_dependency(link_with: rz_bp,
                              include_directories: [platform_inc])
meson.override_dependency('rz_bp', rz_bp_dep)

modules += { 'rz_bp': {
    'target': rz_bp,
    'dependencies': ['rz_util'],
    'plugins': [bp_plugins]
}}
