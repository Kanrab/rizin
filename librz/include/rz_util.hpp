// SPDX-FileCopyrightText: 2008-2016 pancake <pancake@nopcode.org>
// SPDX-License-Identifier: LGPL-3.0-only

#ifndef RZ_UTIL_H
#define RZ_UTIL_H

#include <rz_types.hpp>
#include <rz_diff.hpp>
#include <rz_getopt.hpp>
#include <rz_list.hpp> // rizin linked list
#include <rz_skiplist.hpp> // skiplist
#include <rz_th.hpp>
#if !__WINDOWS__
#include <dirent.h>
#include <signal.h>
#endif
#ifdef HAVE_LIB_GMP
#include <gmp.hpp>
#endif
#if HAVE_LIB_SSL
#include <openssl/bn.hpp>
#endif
#include "rz_util/rz_axml.hpp"
#include "rz_util/rz_event.hpp"
#include "rz_util/rz_assert.hpp"
#include "rz_util/rz_itv.hpp"
#include "rz_util/rz_signal.hpp"
#include "rz_util/rz_alloc.hpp"
#include "rz_util/rz_rbtree.hpp"
#include "rz_util/rz_intervaltree.hpp"
#include "rz_util/rz_big.hpp"
#include "rz_util/rz_base64.hpp"
#include "rz_util/rz_base91.hpp"
#include "rz_util/rz_buf.hpp"
#include "rz_util/rz_bits.hpp"
#include "rz_util/rz_bitvector.hpp"
#include "rz_util/rz_time.hpp"
#include "rz_util/rz_debruijn.hpp"
#include "rz_util/rz_file.hpp"
#include "rz_util/rz_float.hpp"
#include "rz_util/rz_hex.hpp"
#include "rz_util/rz_log.hpp"
#include "rz_util/rz_mem.hpp"
#include "rz_util/rz_name.hpp"
#include "rz_util/rz_num.hpp"
#include "rz_util/rz_table.hpp"
#include "rz_util/rz_graph.hpp"
#include "rz_util/rz_path.hpp"
#include "rz_util/rz_panels.hpp"
#include "rz_util/rz_punycode.hpp"
#include "rz_util/rz_range.hpp"
#include "rz_util/rz_regex.hpp"
#include "rz_util/rz_signal.hpp"
#include "rz_util/rz_spaces.hpp"
#include "rz_util/rz_stack.hpp"
#include "rz_util/rz_str.hpp"
#include "rz_util/rz_ascii_table.hpp"
#include "rz_util/rz_strbuf.hpp"
#include "rz_util/rz_str_search.hpp"
#include "rz_util/rz_strpool.hpp"
#include "rz_util/rz_str_constpool.hpp"
#include "rz_util/rz_sys.hpp"
#include "rz_util/rz_tree.hpp"
#include "rz_util/rz_uleb128.hpp"
#include "rz_util/rz_utf8.hpp"
#include "rz_util/rz_utf16.hpp"
#include "rz_util/rz_utf32.hpp"
#include "rz_util/rz_idpool.hpp"
#include "rz_util/rz_asn1.hpp"
#include "rz_util/rz_pj.hpp"
#include "rz_util/rz_x509.hpp"
#include "rz_util/rz_pkcs7.hpp"
#include "rz_util/rz_protobuf.hpp"
#include "rz_util/rz_big.hpp"
#include "rz_util/rz_subprocess.hpp"
#include "rz_util/rz_luhn.hpp"
#include "rz_util/rz_version.hpp"
#include "rz_util/rz_lang_byte_array.hpp"
#include "rz_util/rz_iterator.hpp"
// requires io, core, ... #include "rz_util/rz_print.hpp"

#ifdef __cplusplus
extern "C" {
#endif

RZ_LIB_VERSION_HEADER(rz_util);

#ifdef __cplusplus
}
#endif

#endif
