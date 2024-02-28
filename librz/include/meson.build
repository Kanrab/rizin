include_files = [
  'rz_agraph.hpp',
  'rz_analysis.hpp',
  'rz_asm.hpp',
  'rz_basefind.hpp',
  'rz_bin.hpp',
  'rz_bin_dwarf.hpp',
  'rz_bin_source_line.hpp',
  'rz_bind.hpp',
  'rz_bp.hpp',
  'rz_cmd.hpp',
  'rz_cmp.hpp',
  'rz_config.hpp',
  'rz_cons.hpp',
  'rz_constructor.hpp',
  'rz_core.hpp',
  'rz_crypto.hpp',
  'rz_debug.hpp',
  'rz_demangler.hpp',
  'rz_diff.hpp',
  'rz_egg.hpp',
  'rz_endian.hpp',
  'rz_flag.hpp',
  'rz_flirt.hpp',
  'rz_getopt.hpp',
  'rz_heap_glibc.hpp',
  'rz_heap_jemalloc.hpp',
  'rz_il.hpp',
  'rz_io.hpp',
  'rz_lang.hpp',
  'rz_lib.hpp',
  'rz_list.hpp',
  'rz_magic.hpp',
  'rz_main.hpp',
  'rz_hash.hpp',
  'rz_parse.hpp',
  'rz_pdb.hpp',
  'rz_platform.hpp',
  'rz_project.hpp',
  'rz_reg.hpp',
  'rz_search.hpp',
  'rz_sign.hpp',
  'rz_skiplist.hpp',
  'rz_skyline.hpp',
  'rz_socket.hpp',
  'rz_syscall.hpp',
  'rz_th.hpp',
  'rz_type.hpp',
  'rz_types.hpp',
  'rz_types_base.hpp',
  'rz_types_overflow.hpp',
  'rz_util.hpp',
  'rz_vector.hpp',
  'rz_windows.hpp',
  'rz_windows_heap.hpp',
]
install_headers(include_files, install_dir: rizin_incdir)

rz_util_files = [
  'rz_util/rz_alloc.hpp',
  'rz_util/rz_annotated_code.hpp',
  'rz_util/rz_ascii_table.hpp',
  'rz_util/rz_asn1.hpp',
  'rz_util/rz_assert.hpp',
  'rz_util/rz_axml.hpp',
  'rz_util/rz_base64.hpp',
  'rz_util/rz_base91.hpp',
  'rz_util/rz_big.hpp',
  'rz_util/rz_bits.hpp',
  'rz_util/rz_bitvector.hpp',
  'rz_util/rz_buf.hpp',
  'rz_util/rz_debruijn.hpp',
  'rz_util/rz_event.hpp',
  'rz_util/rz_file.hpp',
  'rz_util/rz_float.hpp',
  'rz_util/rz_graph.hpp',
  'rz_util/rz_graph_drawable.hpp',
  'rz_util/rz_hex.hpp',
  'rz_util/rz_idpool.hpp',
  'rz_util/rz_intervaltree.hpp',
  'rz_util/rz_itv.hpp',
  'rz_util/rz_json.hpp',
  'rz_util/rz_lang_byte_array.hpp',
  'rz_util/rz_log.hpp',
  'rz_util/rz_luhn.hpp',
  'rz_util/rz_mem.hpp',
  'rz_util/rz_name.hpp',
  'rz_util/rz_num.hpp',
  'rz_util/rz_panels.hpp',
  'rz_util/rz_path.hpp',
  'rz_util/rz_pj.hpp',
  'rz_util/rz_pkcs7.hpp',
  'rz_util/rz_print.hpp',
  'rz_util/rz_protobuf.hpp',
  'rz_util/rz_punycode.hpp',
  'rz_util/rz_range.hpp',
  'rz_util/rz_rbtree.hpp',
  'rz_util/rz_regex.hpp',
  'rz_util/rz_iterator.hpp',
  'rz_util/rz_serialize.hpp',
  'rz_util/rz_signal.hpp',
  'rz_util/rz_spaces.hpp',
  'rz_util/rz_stack.hpp',
  'rz_util/rz_str.hpp',
  'rz_util/rz_str_constpool.hpp',
  'rz_util/rz_str_search.hpp',
  'rz_util/rz_str_util.hpp',
  'rz_util/rz_strbuf.hpp',
  'rz_util/rz_strpool.hpp',
  'rz_util/rz_subprocess.hpp',
  'rz_util/rz_sys.hpp',
  'rz_util/rz_table.hpp',
  'rz_util/rz_th_ht.hpp',
  'rz_util/rz_time.hpp',
  'rz_util/rz_tree.hpp',
  'rz_util/rz_uleb128.hpp',
  'rz_util/rz_utf16.hpp',
  'rz_util/rz_utf32.hpp',
  'rz_util/rz_utf8.hpp',
  'rz_util/rz_version.hpp',
  'rz_util/rz_x509.hpp',
  'rz_util/ht_inc.hpp',
  'rz_util/ht_pp.hpp',
  'rz_util/ht_pu.hpp',
  'rz_util/ht_up.hpp',
  'rz_util/ht_uu.hpp',
  'rz_util/set.hpp',
]
install_headers(rz_util_files, install_dir: join_paths(rizin_incdir, 'rz_util'))

rz_il_definitions_files = [
  'rz_il/definitions/bool.hpp',
  'rz_il/definitions/definitions.hpp',
  'rz_il/definitions/label.hpp',
  'rz_il/definitions/mem.hpp',
  'rz_il/definitions/sort.hpp',
  'rz_il/definitions/value.hpp',
  'rz_il/definitions/variable.hpp',
  'rz_il/definitions/float.hpp',
]
install_headers(rz_il_definitions_files, install_dir: join_paths(rizin_incdir, 'rz_il', 'definitions'))

rz_il_files = [
  'rz_il/rz_il_opcodes.hpp',
  'rz_il/rz_il_opbuilder_begin.hpp',
  'rz_il/rz_il_opbuilder_end.hpp',
  'rz_il/rz_il_events.hpp',
  'rz_il/rz_il_reg.hpp',
  'rz_il/rz_il_validate.hpp',
  'rz_il/rz_il_vm.hpp'
]
install_headers(rz_il_files, install_dir: join_paths(rizin_incdir, 'rz_il'))

rz_crypto_files = [
  'rz_crypto/rz_des.hpp'
]
install_headers(rz_crypto_files, install_dir: join_paths(rizin_incdir, 'rz_crypto'))

if get_option('use_gpl')
  sflib_common_files = [
    'sflib/common/sftypes.hpp',
    'sflib/common/sfsocketcall.hpp'
  ]

  sflib_arch = [
    'linux-x86-64',
    'linux-x86-32',
    'linux-arm-64',
    'linux-arm-32',
    'darwin-x86-64',
    'darwin-x86-32',
    'darwin-arm-64'
  ]

  sflib_arch_files = [
    'sflib.hpp',
    'sfsyscall.hpp',
    'sfsysnr.hpp'
  ]

  install_headers(sflib_common_files, install_dir: join_paths(rizin_incdir, 'sflib/common'))
  foreach arch : sflib_arch
    foreach file : sflib_arch_files
      install_headers(join_paths('sflib', arch, file), install_dir: join_paths(rizin_incdir, 'sflib', arch))
    endforeach
  endforeach
endif
