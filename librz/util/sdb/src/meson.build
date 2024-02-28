libsdb_sources = files(
  'array.cpp',
  'base64.cpp',
  'buffer.cpp',
  'cdb.cpp',
  'cdb_make.cpp',
  'diff.cpp',
  'disk.cpp',
  'fmt.cpp',
  'lock.cpp',
  'ls.cpp',
  'match.cpp',
  'ns.cpp',
  'num.cpp',
  'query.cpp',
  'sdb.cpp',
  'sdbht.cpp',
  'util.cpp',
  'text.cpp'
)

libsdb_inc = [platform_inc, include_directories(['..', '.'])]

include_files = files(
  'buffer.hpp',
  'cdb.hpp',
  'cdb_make.hpp',
  'ls.hpp',
  'sdb.hpp',
  'sdbht.hpp',
)

install_headers(include_files, install_dir: join_paths(rizin_incdir, 'sdb'))
