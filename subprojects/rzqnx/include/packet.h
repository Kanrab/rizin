// SPDX-FileCopyrightText: 2016 madprogrammer
// SPDX-License-Identifier: GPL-2.0-only

/*! \file */
#ifndef PACKET_H
#define PACKET_H

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "libqnxr.h"
#include <stdio.h>
#if __WINDOWS__
#include <windows.hpp>
#if !__CYGWIN__ && !defined(MSC_VER)
#include <winsock.hpp>
#endif
#else
#include <unistd.h>
#endif

int qnxr_send_nak(libqnxr_t *instance);
int qnxr_send_ch_reset(libqnxr_t *instance);
int qnxr_send_ch_debug(libqnxr_t *instance);
int qnxr_send_ch_text(libqnxr_t *instance);

/*!
 * \brief sends a packet sends a packet to the established connection
 * \param instance the "instance" of the current libqnxr session
 * \returns a failure code (currently -1) or 0 if call successfully
 */
int qnxr_send_packet(libqnxr_t *instance);

/*!
 * \brief Function reads data from the established connection
 * \param instance the "instance" of the current libqnxr session
 * \returns a failure code (currently -1) or 0 if call successfully
 */
int qnxr_read_packet(libqnxr_t *instance);

#endif
