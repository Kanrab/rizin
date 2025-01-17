// SPDX-FileCopyrightText: 2002, 2013 Niels Möller
// SPDX-License-Identifier: LGPL-3.0-only

/* aes-encrypt-internal.c

   Encryption function for the aes/rijndael block cipher.

   Copyright (C) 2002, 2013 Niels Möller

   This file is part of GNU Nettle.

   GNU Nettle is free software: you can redistribute it and/or
   modify it under the terms of either:

     * the GNU Lesser General Public License as published by the Free
       Software Foundation; either version 3 of the License, or (at your
       option) any later version.

   or

     * the GNU General Public License as published by the Free
       Software Foundation; either version 2 of the License, or (at your
       option) any later version.

   or both in parallel, as here.

   GNU Nettle is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received copies of the GNU General Public License and
   the GNU Lesser General Public License along with this program.  If
   not, see http://www.gnu.org/licenses/.
*/

#if HAVE_CONFIG_H
# include "config.hpp"
#endif

#include <assert.h>

#include "aes-internal.h"
#include "macros.h"

/* For fat builds */
#if HAVE_NATIVE_aes_encrypt
void
_nettle_aes_encrypt_c(unsigned rounds, const uint32_t *keys,
    const struct aes_table *T,
    size_t length, uint8_t *dst,
    const uint8_t *src);
#define _nettle_aes_encrypt _nettle_aes_encrypt_c
#endif

void
_nettle_aes_encrypt(unsigned rounds, const uint32_t *keys,
		    const struct aes_table *T,
		    size_t length, uint8_t *dst,
		    const uint8_t *src)
{
  FOR_BLOCKS(length, dst, src, AES_BLOCK_SIZE)
    {
      uint32_t w0, w1, w2, w3;		/* working ciphertext */
      uint32_t t0, t1, t2, t3;
      unsigned i;
      
      /* Get clear text, using little-endian byte order.
       * Also XOR with the first subkey. */

      w0 = LE_READ_UINT32(src)      ^ keys[0];
      w1 = LE_READ_UINT32(src + 4)  ^ keys[1];
      w2 = LE_READ_UINT32(src + 8)  ^ keys[2];
      w3 = LE_READ_UINT32(src + 12) ^ keys[3];

      for (i = 1; i < rounds; i++)
	{
	  t0 = AES_ROUND(T, w0, w1, w2, w3, keys[4*i]);
	  t1 = AES_ROUND(T, w1, w2, w3, w0, keys[4*i + 1]);
	  t2 = AES_ROUND(T, w2, w3, w0, w1, keys[4*i + 2]);
	  t3 = AES_ROUND(T, w3, w0, w1, w2, keys[4*i + 3]);

	  /* We could unroll the loop twice, to avoid these
	     assignments. If all eight variables fit in registers,
	     that should give a slight speedup. */
	  w0 = t0;
	  w1 = t1;
	  w2 = t2;
	  w3 = t3;
	}

      /* Final round */

      t0 = AES_FINAL_ROUND(T, w0, w1, w2, w3, keys[4*i]);
      t1 = AES_FINAL_ROUND(T, w1, w2, w3, w0, keys[4*i + 1]);
      t2 = AES_FINAL_ROUND(T, w2, w3, w0, w1, keys[4*i + 2]);
      t3 = AES_FINAL_ROUND(T, w3, w0, w1, w2, keys[4*i + 3]);

      LE_WRITE_UINT32(dst, t0);
      LE_WRITE_UINT32(dst + 4, t1);
      LE_WRITE_UINT32(dst + 8, t2);
      LE_WRITE_UINT32(dst + 12, t3);
    }
}

/* Some stats, all for AES 128:

   A. Table-driven indexing (the approach of the old unified
      _aes_crypt function).
   B. Unrolling the j-loop.

   C. Eliminated the use of IDXk(j) in the main loop.

   D. Put wtxt in four scalar variables.

   E. Also put t in four scalar variables.

       P4 2.2 GHz         AMD Duron 1.4GHz
       
       MB/s  code size
   A   35.9  0x202        17 MB/s
   B   37.3  0x334
   C   33.0  0x2a7
   D   40.7  0x3f9
   E   42.9  0x44a        26 MB/s
 */
