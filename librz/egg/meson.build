egg_plugins = {
  'conf_name': 'plugins_egg',
  'base_cname': 'rz_egg_plugin_',
  'list': [
    'exec',
    #'shya',
    'xor'
  ],
}

rz_egg_sources = [
  'egg.cpp',
  'egg_Cfile.cpp',
  'egg_lang.cpp',
  'emit_arm.cpp',
  'emit_trace.cpp',
  'emit_x64.cpp',
  'emit_x86.cpp',
  #'p/egg_bind.cpp',
  #'p/egg_cb.cpp',
  'p/egg_exec.cpp',
  #'p/egg_reverse.cpp',
  #'p/egg_shya.cpp',
  'p/egg_xor.cpp'
]

rz_egg = library('rz_egg', rz_egg_sources,
  include_directories: [platform_inc],
  dependencies: [
    rz_util_dep,
    rz_syscall_dep,
    rz_asm_dep,
    mpc_dep
  ],
  install: true,
  implicit_include_directories: false,
  install_rpath: rpath_lib,
  soversion: rizin_libversion,
  version: rizin_version,
  name_suffix: lib_name_suffix,
  name_prefix: lib_name_prefix,
)

rz_egg_dep = declare_dependency(link_with: rz_egg,
                               include_directories: [platform_inc])
meson.override_dependency('rz_egg', rz_egg_dep)

modules += { 'rz_egg': {
    'target': rz_egg,
    'dependencies': ['rz_util', 'rz_asm', 'rz_syscall'],
    'plugins': [egg_plugins]
}}
