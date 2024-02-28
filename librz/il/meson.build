rz_il_sources = [
   'definitions/bool.cpp',
   'definitions/float.cpp',
   'definitions/label.cpp',
   'definitions/mem.cpp',
   'definitions/value.cpp',
   'definitions/variable.cpp',
   'theory_bitv.cpp',
   'theory_bool.cpp',
   'theory_effect.cpp',
   'theory_fbasic.cpp',
   'theory_init.cpp',
   'theory_mem.cpp',
   'il_events.cpp',
   'il_export_string.cpp',
   'il_export_json.cpp',
   'il_graph.cpp',
   'il_opcodes.cpp',
   'il_routines.cpp',
   'il_reg.cpp',
   'il_validate.cpp',
   'il_vm.cpp',
   'il_vm_eval.cpp',
]

rz_il_inc = [
  platform_inc,
]

rz_il = library('rz_il', rz_il_sources,
  include_directories: rz_il_inc,
  dependencies: [
    rz_util_dep,
    rz_reg_dep
  ],
  install: true,
  implicit_include_directories: false,
  install_rpath: rpath_lib,
  soversion: rizin_libversion,
  version: rizin_version,
  name_suffix: lib_name_suffix,
  name_prefix: lib_name_prefix,
)

rz_il_dep = declare_dependency(link_with: rz_il,
                                include_directories: rz_il_inc)
meson.override_dependency('rz_il', rz_il_dep)

modules += { 'rz_il': {
    'target': rz_il,
    'dependencies': ['rz_util', 'rz_reg']
}}
