crypto_plugins = {
  'conf_name': 'plugins_crypto',
  'base_cname': 'rz_crypto_plugin_',
  'list': [
    'aes',
    'aes_cbc',
    'base64',
    'base91',
    'blowfish',
    'cps2',
    'des',
    'punycode',
    'rc2',
    'rc4',
    'rc6',
    'rol',
    'ror',
    'rot',
    'serpent',
    'xor',
    'sm4_ecb'
  ],
}

rz_crypto_sources = [
  'des.cpp',
  'crypto.cpp',
  'p/crypto_aes.cpp',
  'p/crypto_aes_cbc.cpp',
  'p/crypto_base64.cpp',
  'p/crypto_base91.cpp',
  'p/crypto_blowfish.cpp',
  'p/crypto_cps2.cpp',
  'p/crypto_des.cpp',
  'p/crypto_punycode.cpp',
  'p/crypto_rc2.cpp',
  'p/crypto_rc4.cpp',
  'p/crypto_rc6.cpp',
  'p/crypto_rol.cpp',
  'p/crypto_ror.cpp',
  'p/crypto_rot.cpp',
  'p/crypto_serpent.cpp',
  'p/crypto_serpent_algo.cpp',
  'p/crypto_xor.cpp',
  'p/crypto_sm4_ecb.cpp'
]

nettle_proj = subproject('nettle')
aes_dep = nettle_proj.get_variable('aes_dep')

rz_crypto = library('rz_crypto', rz_crypto_sources,
  include_directories: [platform_inc],
  dependencies: [rz_util_dep, aes_dep],
  install: true,
  implicit_include_directories: false,
  install_rpath: rpath_lib,
  soversion: rizin_libversion,
  version: rizin_version,
  name_suffix: lib_name_suffix,
  name_prefix: lib_name_prefix,
)

rz_crypto_dep = declare_dependency(link_with: rz_crypto,
                                  include_directories: [platform_inc])
meson.override_dependency('rz_crypto', rz_crypto_dep)

modules += { 'rz_crypto': {
    'target': rz_crypto,
    'dependencies': ['rz_util'],
    'plugins': [crypto_plugins]
}}
