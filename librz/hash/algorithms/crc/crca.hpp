// SPDX-FileCopyrightText: 2009 Victor Mu~noz <vmunoz@ingenieria-inversa.cl>
// SPDX-FileCopyrightText: 2021 deroad <wargio@libero.it>
// SPDX-License-Identifier: LGPL-3.0-only
#ifndef RZ_CRCA_H
#define RZ_CRCA_H

#include <rz_types.hpp>

typedef ut64 utcrc;
#define UTCRC_C(x) ((utcrc)(x))

typedef enum {
	CRC_PRESET_8_SMBUS = 0,
	CRC_PRESET_CRC8_CDMA2000,
	CRC_PRESET_CRC8_DARC,
	CRC_PRESET_CRC8_DVB_S2,
	CRC_PRESET_CRC8_EBU,
	CRC_PRESET_CRC8_ICODE,
	CRC_PRESET_CRC8_ITU,
	CRC_PRESET_CRC8_MAXIM,
	CRC_PRESET_CRC8_ROHC,
	CRC_PRESET_CRC8_WCDMA,
	CRC_PRESET_15_CAN,
	CRC_PRESET_16,
	CRC_PRESET_16_CITT,
	CRC_PRESET_16_USB,
	CRC_PRESET_16_HDLC,
	CRC_PRESET_CRC16_AUG_CCITT,
	CRC_PRESET_CRC16_BUYPASS,
	CRC_PRESET_CRC16_CDMA2000,
	CRC_PRESET_CRC16_DDS110,
	CRC_PRESET_CRC16_DECT_R,
	CRC_PRESET_CRC16_DECT_X,
	CRC_PRESET_CRC16_DNP,
	CRC_PRESET_CRC16_EN13757,
	CRC_PRESET_CRC16_GENIBUS,
	CRC_PRESET_CRC16_MAXIM,
	CRC_PRESET_CRC16_MCRF4XX,
	CRC_PRESET_CRC16_RIELLO,
	CRC_PRESET_CRC16_T10_DIF,
	CRC_PRESET_CRC16_TELEDISK,
	CRC_PRESET_CRC16_TMS37157,
	CRC_PRESET_CRCA,
	CRC_PRESET_CRC16_KERMIT,
	CRC_PRESET_CRC16_MODBUS,
	CRC_PRESET_CRC16_X25,
	CRC_PRESET_CRC16_XMODEM,
	CRC_PRESET_24,
	CRC_PRESET_32,
	CRC_PRESET_32_ECMA_267,
	CRC_PRESET_32C,
	CRC_PRESET_CRC32_BZIP2,
	CRC_PRESET_CRC32D,
	CRC_PRESET_CRC32_MPEG2,
	CRC_PRESET_CRC32_POSIX,
	CRC_PRESET_CRC32Q,
	CRC_PRESET_CRC32_JAMCRC,
	CRC_PRESET_CRC32_XFER,
	CRC_PRESET_CRC64,
	CRC_PRESET_CRC64_ECMA182,
	CRC_PRESET_CRC64_WE,
	CRC_PRESET_CRC64_XZ,
	CRC_PRESET_CRC64_ISO,

	CRC_PRESET_SIZE
} RzCrcPresets;

typedef struct {
	utcrc crc;
	ut32 size;
	int reflect;
	utcrc poly;
	utcrc xout;
} RzCrc;

void crc_init_preset(RzCrc *ctx, RzCrcPresets preset);
void crc_init_custom(RzCrc *ctx, utcrc crc, ut32 size, int reflect, utcrc poly, utcrc xout);
void crc_update(RzCrc *ctx, const ut8 *data, ut32 sz);
void crc_final(RzCrc *ctx, utcrc *r);

#endif /* RZ_CRCA_H */
