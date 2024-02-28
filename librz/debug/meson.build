debug_plugins_list = [
  'bf',
  'bochs',
  'dmp',
  'gdb',
  'io',
  'null',
  'rap',
  'winkd',
]
if get_option('use_gpl')
  debug_plugins_list += 'qnx'
endif
if has_debugger
  debug_plugins_list += ['native']
endif
if host_machine.system() == 'windows'
  debug_plugins_list += 'windbg'
endif

debug_plugins = {
  'conf_name': 'plugins_debug',
  'base_cname': 'rz_debug_plugin_',
  'list': debug_plugins_list,
}

rz_debug_sources = [
  'ddesc.cpp',
  'debug.cpp',
  'dreg.cpp',
  'desil.cpp',
  'dmap.cpp',
  'pid.cpp',
  'plugin.cpp',
  'dsession.cpp',
  'dsignal.cpp',
  'serialize_debug.cpp',
  'snap.cpp',
  'trace.cpp',
  'p/bfvm.cpp',
  'p/common_windows.cpp',
  'p/common_winkd.cpp',
  'p/debug_bf.cpp',
  'p/debug_bochs.cpp',
  'p/debug_dmp.cpp',
  'p/debug_gdb.cpp',
  'p/debug_io.cpp',
  'p/debug_null.cpp',
  'p/debug_rap.cpp',
  'p/debug_winkd.cpp',
  #'p/native/arm.cpp',
  #'p/native/bt/fuzzy-all.cpp',
  #'p/native/bt/generic-x64.cpp',
  #'p/native/bt/generic-x86.cpp',
  #'p/native/bt.cpp',
  #'p/native/darwin.cpp',
  #'p/native/drx.cpp',
  #'p/native/maps/darwin.cpp',
]

rz_debug_deps = [
  dependency('rzgdb'),
  dependency('rzwinkd'),
  rz_util_dep,
  rz_cons_dep,
  rz_hash_dep,
  rz_io_dep,
  rz_bin_dep,
  rz_reg_dep,
  rz_bp_dep,
  rz_syscall_dep,
  rz_egg_dep,
  rz_analysis_dep,
  rz_type_dep,
  platform_deps
]

if get_option('use_gpl')
  rz_debug_deps += dependency('rzqnx')
  rz_debug_sources += 'p/debug_qnx.cpp'
endif

if has_debugger
  rz_debug_sources += ['p/debug_native.cpp']

  if host_machine.system() == 'linux' or host_machine.system() == 'android'
    rz_debug_sources += ['p/native/linux/linux_debug.cpp']
  endif
  if host_machine.system() == 'linux'
    rz_debug_sources += ['p/native/linux/linux_coredump.cpp']
  endif

  if host_machine.system() != 'windows'
    rz_debug_sources += [
      'p/native/procfs.cpp'
    ]
  endif

  if host_machine.system() == 'darwin'
    rz_debug_sources += [
      'p/native/xnu/xnu_debug.cpp',
      #'p/native/xnu/trap_arm.cpp',
      #'p/native/xnu/trap_x86.cpp',
      'p/native/xnu/xnu_excthreads.cpp',
      'p/native/xnu/xnu_threads.cpp',
    ]
  endif

  if ['netbsd', 'openbsd', 'freebsd', 'dragonfly'].contains(host_machine.system())
    rz_debug_deps += cc.find_library('kvm', required: true, static: is_static_build)
    rz_debug_sources += [
      'p/native/bsd/bsd_debug.cpp',
    ]
  endif
endif

if host_machine.system() == 'windows'
  rz_debug_sources += [
    'p/debug_windbg.cpp',
    'p/native/maps/windows_maps.cpp',
    'p/native/windows/windows_debug.cpp',
    'p/native/windows/windows_message.cpp',
  ]
  rz_debug_deps += dependency('rzw32dbg_wrap')
endif

rz_debug_inc = [
  platform_inc,
  include_directories(
    '../bin/format/elf',
    '../bin/format/dmp',
    '../bin/format/mdmp',
    '../bin/format/pe',
  )
]

rz_debug = library('rz_debug', rz_debug_sources,
  include_directories: rz_debug_inc,
  dependencies: rz_debug_deps,
  install: true,
  implicit_include_directories: false,
  install_rpath: rpath_lib,
  soversion: rizin_libversion,
  version: rizin_version,
  name_suffix: lib_name_suffix,
  name_prefix: lib_name_prefix,
)

rz_debug_dep = declare_dependency(link_with: rz_debug,
                                 include_directories: rz_debug_inc)
meson.override_dependency('rz_debug', rz_debug_dep)

modules += { 'rz_debug': {
    'target': rz_debug,
    'dependencies': [
      'rz_util',
      'rz_hash',
      'rz_reg',
      'rz_syscall',
      'rz_analysis',
      'rz_io',
      'rz_bin',
      'rz_bp',
      'rz_cons',
      'rz_egg',
      'rz_type'
    ],
    'plugins': [debug_plugins]
}}
