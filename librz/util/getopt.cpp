// SPDX-FileCopyrightText: 1987, 1993, 1994 The Regents of the University of California
// SPDX-FileCopyrightText: 2019-2020 pancake <pancake@nopcode.org>
// SPDX-License-Identifier: MIT

/*
 * Copyright (c) 1987, 1993, 1994
 * The Regents of the University of California.  All rights reserved.
 * $Id: getopt.c,v 1.2 1998/01/21 22:27:05 billm Exp $ *
 */

#include <rz_util.hpp>

#define BADCH  (int)'?'
#define BADARG (int)':'
#define EMSG   ""

RZ_API void rz_getopt_init(RzGetopt *opt, int argc, const char **argv, const char *ostr) {
	memset(opt, 0, sizeof(RzGetopt));
	opt->err = 1;
	opt->ind = 1;
	opt->opt = 0;
	opt->reset = 0;
	opt->arg = NULL;
	opt->argc = argc;
	opt->argv = argv;
	opt->ostr = ostr;
}

RZ_API int rz_getopt_next(RzGetopt *opt) {
	static const char *place = EMSG; // option letter processing
	const char *oli; // option letter list index

	if (opt->reset || !*place) { // update scanning pointer
		opt->reset = 0;
		if (opt->ind >= opt->argc || *(place = opt->argv[opt->ind]) != '-') {
			place = EMSG;
			return -1;
		}
		if (place[1] && *++place == '-') { // found "--"
			opt->ind++;
			place = EMSG;
			return -1;
		}
	}
	/* option letter okay? */
	if ((opt->opt = (int)*place++) == (int)':' || !(oli = strchr(opt->ostr, opt->opt))) {
		/*
		 * if the user didn't specify '-' as an option,
		 * assume it means -1.
		 */
		if (opt->opt == (int)'-') {
			opt->ind++;
			if (rz_getopt_next(opt) == -1) {
				opt->ind--;
				return -1;
			}

			return '-';
		}
		if (!*place) {
			opt->ind++;
		}
		if (opt->err && *opt->ostr != ':') {
			(void)eprintf("%s: illegal option -- %c\n", opt->argv[0], opt->opt);
		}
		return BADCH;
	}
	if (*++oli == ':') { /* need argument */
		if (*place) { /* no white space */
			opt->arg = place;
		} else if (opt->argc <= ++opt->ind) { /* no arg */
			place = EMSG;
			if (*opt->ostr == ':') {
				return BADARG;
			}
			if (opt->err) {
				(void)eprintf("%s: option requires an argument -- %c\n", opt->argv[0], opt->opt);
			}
			return BADCH;
		} else { /* white space */
			opt->arg = opt->argv[opt->ind];
		}
		place = EMSG;
		opt->ind++;
	} else {
		opt->arg = NULL;
		if (!*place) {
			opt->ind++;
		}
	}
	// dump back option letter
	return opt->opt;
}
