
if get_option('enable_rz_test')
  executable('rz-test', ['rz-test.cpp', 'load.cpp', 'run.cpp'],
    include_directories: [platform_inc],
    dependencies: [
      rz_util_dep,
      rz_diff_dep,
      lrt,
    ],
    install: true,
    install_rpath: rpath_exe,
    implicit_include_directories: false,
  )
endif
