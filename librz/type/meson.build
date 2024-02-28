rz_type_sources = [
  'base.cpp',
  'format.cpp',
  'function.cpp',
  'helpers.cpp',
  'path.cpp',
  'serialize_functions.cpp',
  'serialize_types.cpp',
  'type.cpp',
  'typeclass.cpp',
  'parser/c_cpp_parser.cpp',
  'parser/types_parser.cpp',
  'parser/types_storage.cpp',
]

r = run_command(py3_exe, check_meson_subproject_py, 'tree-sitter-c', check: false)
if r.returncode() == 1 and get_option('subprojects_check')
  error('Subprojects are not updated. Please run `git clean -dxff subprojects/` to delete all local subprojects directories. If you want to compile against current subprojects then set option `subprojects_check=false`.')
endif

tree_sitter_c_dep = dependency('tree-sitter-c')

rz_type_inc = [
  platform_inc,
  'parser',
]

rz_type = library('rz_type', rz_type_sources,
  include_directories: rz_type_inc,
  dependencies: [
    rz_util_dep,
    tree_sitter_c_dep,
    lrt
  ],
  install: true,
  implicit_include_directories: false,
  install_rpath: rpath_lib,
  soversion: rizin_libversion,
  version: rizin_version,
  name_suffix: lib_name_suffix,
  name_prefix: lib_name_prefix,
)

rz_type_dep = declare_dependency(link_with: rz_type,
                                include_directories: rz_type_inc)
meson.override_dependency('rz_type', rz_type_dep)

modules += { 'rz_type': {
    'target': rz_type,
    'dependencies': ['rz_util']
}}
