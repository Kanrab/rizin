// SPDX-FileCopyrightText: 2014-2017 LemonBoy <thatlemon@gmail.com>
// SPDX-License-Identifier: LGPL-3.0-only

#ifndef _TRANSPORT_H_
#define _TRANSPORT_H_

#include <rz_types.hpp>
#include <stdint.h>

#ifndef HAVE_EPRINTF
#include <stdio.h>
#define eprintf(...) \
	{ fprintf(stderr, ##__VA_ARGS__); }
#define HAVE_EPRINTF 1
#endif

#define KD_IO_PIPE 0
#define KD_IO_NET  1

enum {
	E_OK = 0,
	E_TIMEOUT = -1,
	E_ERROR = -2,
	E_NOIF = -3,
};

typedef struct io_backend_t {
	const char *name;
	int type;
	int (*init)(void);
	int (*deinit)(void);
	void *(*open)(const char *path);
	bool (*close)(void *);
	int (*config)(void *, void *);
	int (*read)(void *, uint8_t *buf, const uint64_t count, const int timeout);
	int (*write)(void *, const uint8_t *buf, const uint64_t count, const int timeout);
} io_backend_t;

typedef struct io_desc_t {
	void *fp;
	io_backend_t *iob;
} io_desc_t;

io_desc_t *io_desc_new(io_backend_t *iob, void *fp);
int iob_write(io_desc_t *desc, const uint8_t *buf, const uint32_t buf_len);
int iob_read(io_desc_t *desc, uint8_t *buf, const uint32_t buf_len);

extern io_backend_t iob_pipe;
extern io_backend_t iob_net;

#endif
