subdir('sdb/src')

rz_util_common_sources = [
  'alloc.cpp',
  'annotated_code.cpp',
  'ascii_table.cpp',
  'asn1.cpp',
  'assert.cpp',
  'astr.cpp',
  'axml.cpp',
  'base85.cpp',
  'base91.cpp',
  'bitvector.cpp',
  'buf.cpp',
  'calc.cpp',
  'chmod.cpp',
  'compression.cpp',
  'debruijn.cpp',
  'ebcdic.cpp',
  'event.cpp',
  'file.cpp',
  'float/float.cpp',
  'getopt.cpp',
  'graph.cpp',
  'graph_drawable.cpp',
  'hex.cpp',
  'idpool.cpp',
  'intervaltree.cpp',
  'json_indent.cpp',
  'json_parser.cpp',
  'lang_byte_array.cpp',
  'lib.cpp',
  'list.cpp',
  'log.cpp',
  'luhn.cpp',
  'mem.cpp',
  'name.cpp',
  'path.cpp',
  'pj.cpp',
  'pkcs7.cpp',
  'print.cpp',
  'protobuf.cpp',
  'punycode.cpp',
  'range.cpp',
  'rbtree.cpp',
  'regex.cpp',
  'iterator.cpp',
  'serialize_spaces.cpp',
  'signal.cpp',
  'skiplist.cpp',
  'skyline.cpp',
  'spaces.cpp',
  'stack.cpp',
  'str.cpp',
  'str_constpool.cpp',
  'str_search.cpp',
  'str_trim.cpp',
  'strbuf.cpp',
  'strpool.cpp',
  'subprocess.cpp',
  'sys.cpp',
  'syscmd.cpp',
  'table.cpp',
  'thread.cpp',
  'thread_cond.cpp',
  'thread_hash_table.cpp',
  'thread_iterators.cpp',
  'thread_lock.cpp',
  'thread_pool.cpp',
  'thread_queue.cpp',
  'thread_sem.cpp',
  'thread_types.cpp',
  'time.cpp',
  'tree.cpp',
  'ubase64.cpp',
  'uleb128.cpp',
  'unum.cpp',
  'utf16.cpp',
  'utf32.cpp',
  'utf8.cpp',
  'vector.cpp',
  'version.cpp',
  'w32-sys.cpp',
  'x509.cpp',
  'ht/ht_uu.cpp',
  'ht/ht_pp.cpp',
  'ht/ht_up.cpp',
  'ht/ht_pu.cpp',
  'set.cpp',
]
rz_util_sources = rz_util_common_sources

rz_util_deps = [ldl, lrt, mth, th, utl, pcre2_dep] + platform_deps
if zlib_dep.found()
  rz_util_deps += [zlib_dep]
endif
if liblzma_dep.found()
  rz_util_deps += [liblzma_dep]
endif
if ['freebsd', 'netbsd', 'haiku', 'dragonfly'].contains(host_machine.system())
  # backtrace_symbols_fd requires -lexecinfo
  rz_util_deps += [cc.find_library('execinfo', static: is_static_build)]
endif
if meson.is_cross_build()
  execinfo_native = disabler()
  if ['freebsd', 'netbsd', 'haiku', 'dragonfly'].contains(build_machine.system())
    # backtrace_symbols_fd requires -lexecinfo
    execinfo_native = cc_native.find_library('execinfo', static: is_static_build)
  endif
endif

if sys_openssl.found()
  rz_util_deps += [sys_openssl]
  rz_util_sources += ['big-ssl.cpp']
else
  rz_util_sources += ['big.cpp']
endif

rz_util_includes = [platform_inc, include_directories('sdb/src')]

rz_util = library('rz_util', rz_util_sources, libsdb_sources,
  include_directories: rz_util_includes,
  dependencies: rz_util_deps,
  install: true,
  implicit_include_directories: false,
  install_rpath: rpath_lib,
  soversion: rizin_libversion,
  version: rizin_version,
  name_suffix: lib_name_suffix,
  name_prefix: lib_name_prefix,
)

rz_util_dep = declare_dependency(
  link_with: rz_util,
  include_directories: rz_util_includes,
)
meson.override_dependency('rz_util', rz_util_dep)

if meson.is_cross_build()
  # this is a bit messy, it duplicates most of the code required to get the
  # regular dependencies but for the build_system. This is required to build
  # sdb_native, used at build time to compile .sdb.txt files into .sdb ones.
  platform_native_deps = []
  if build_machine.system() == 'windows'
    platform_native_deps = [
      cc_native.find_library('ws2_32'),
      cc_native.find_library('wininet'),
      cc_native.find_library('psapi'),
    ]
  endif
  rz_util_native_deps = [ldl_native, lrt_native, mth_native, th_native, utl_native, pcre2_native_dep] + platform_native_deps
  if execinfo_native.found()
    rz_util_native_deps += [execinfo_native]
  endif
  # do not use external libs, we do not need them
  userconf_native.set10('HAVE_LIB_MAGIC', false)
  userconf_native.set10('USE_LIB_MAGIC', false)
  userconf_native.set10('HAVE_LIB_XXHASH', false)
  userconf_native.set10('USE_LIB_XXHASH', false)
  userconf_native.set10('HAVE_OPENSSL', false)
  userconf_native.set10('HAVE_LZMA', false)
  userconf_native.set10('HAVE_ZLIB', false)

  rz_userconf_native_h = configure_file(
    input: rz_userconf_h_in,
    output: 'rz_userconf.h',
    configuration: userconf_native,
    install_dir: rizin_incdir
  )
  rz_util_native_includes = [include_directories('.'), rz_util_includes]
  rz_util_native_sources = rz_util_common_sources + ['big.cpp']

  rz_util_native = static_library('rz_util_native', rz_util_native_sources, libsdb_sources,
    include_directories: rz_util_native_includes,
    dependencies: rz_util_native_deps,
    implicit_include_directories: false,
    install_rpath: rpath_lib,
    install: false,
    native: true,
  )

  rz_util_native_dep = declare_dependency(
    link_with: rz_util_native,
    include_directories: rz_util_native_includes,
  )
else
  rz_util_native_dep = rz_util_dep
endif

modules += { 'rz_util': {
    'target': rz_util,
    'dependencies': [],
    'include_subdirs_extra': ['librz/sdb']
}}

sdb_exe = executable('sdb_native', 'sdb/src/main.cpp',
  dependencies: rz_util_native_dep,
  install: false,
  native: true,
  implicit_include_directories: false,
  install_rpath: rpath_exe,
)

sdb_gen_cmd = [
  sdb_exe,
  '@OUTPUT@',
  '==',
  '@INPUT@'
]
