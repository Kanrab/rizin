// SPDX-FileCopyrightText: 2009-2020 pancake <pancake@nopcode.org>
// SPDX-FileCopyrightText: 2009-2020 nibble <nibble.ds@gmail.com>
// SPDX-License-Identifier: LGPL-3.0-only

#include <rz_cons.hpp>
#include <rz_util/rz_print.hpp>
#include <sdb.hpp>

#define I(x) rz_cons_singleton()->x

static char *strchr_ns(char *s, const char ch) {
	char *p = strchr(s, ch);
	if (p && p > s) {
		char *prev = p - 1;
		if (*prev == '\\') {
			memmove(prev, p, strlen(p) + 1);
			return strchr_ns(p, ch);
		}
	}
	return p;
}

static const char *help_detail_tilde[] = {
	"Usage: [command]~[modifier][word,word][endmodifier][[column]][:line]\n"
	"modifier:",
	"", "",
	" &", "", "all words must match to grep the line",
	" $[n]", "", "sort numerically / alphabetically the Nth column",
	" $!", "", "sort in inverse order",
	" ,", "", "token to define another keyword",
	" +", "", "case insensitive grep (grep -i)",
	" ^", "", "words must be placed at the beginning of line",
	" <", "", "perform zoom operation on the buffer",
	" !", "", "negate grep",
	" ?", "", "count number of matching lines",
	" ?.", "", "count number chars",
	" ??", "", "show this help message",
	" :s..e", "", "show lines s-e",
	" ..", "", "internal 'less'",
	" ...", "", "internal 'hud' (like V_)",
	" {:", "", "human friendly indentation (yes, it's a smiley)",
	" {:..", "", "less the output of {:",
	" {:...", "", "hud the output of {:",
	" {}", "", "json indentation",
	" {}..", "", "less json indentation",
	" {}...", "", "hud json indentation",
	" {path}", "", "json path grep",
	"endmodifier:", "", "",
	" $", "", "words must be placed at the end of line",
	"column:", "", "",
	" [n]", "", "show only column n",
	" [n-m]", "", "show column n to m",
	" [n-]", "", "show all columns starting from column n",
	" [i,j,k]", "", "show the columns i, j and k",
	"Examples:", "", "",
	" i~:0", "", "show first line of 'i' output",
	" i~:-2", "", "show the second to last line of 'i' output",
	" i~:0..3", "", "show first three lines of 'i' output",
	" pd~mov", "", "disasm and grep for mov",
	" pi~[0]", "", "show only opcode",
	" i~0x400$", "", "show lines ending with 0x400",
	NULL
};

RZ_API void rz_cons_grep_help(void) {
	rz_cons_cmd_help(help_detail_tilde, true);
}

#define RZ_CONS_GREP_BUFSIZE 4096

static void parse_grep_expression(const char *str) {
	static char buf[RZ_CONS_GREP_BUFSIZE];
	int wlen, len, is_range, num_is_parsed, fail = 0;
	char *ptr, *optr, *ptr2, *ptr3, *end_ptr = NULL, last;
	ut64 range_begin, range_end;

	if (!str || !*str) {
		return;
	}
	RzCons *cons = rz_cons_singleton();
	RzConsGrep *grep = &cons->context->grep;
	grep->sorted_column = 0;
	bool first = true;

	// setup cons->context->grep.icase according to cons->grep_icase
	if (cons->grep_icase == RZ_CONS_SEARCH_CASE_SMART) {
		// smartcase - when the search term is all lowercase, ignore the case,
		// instead if the search term is uppercase or a mix, do a case-sensitive search.
		bool has_upper = false;
		const char *grep_str = str;
		while (*grep_str) {
			if (isupper(*grep_str)) {
				has_upper = true;
				break;
			}
			grep_str++;
		}

		cons->context->grep.icase = has_upper ? RZ_CONS_SEARCH_CASE_SENSITIVE : RZ_CONS_SEARCH_CASE_INSENSITIVE;
	} else {
		cons->context->grep.icase = cons->grep_icase;
	}

	while (*str) {
		switch (*str) {
		case '.':
			if (str[1] == '.') {
				if (str[2] == '.') {
					grep->less = 2;
				} else {
					grep->less = 1;
				}
				return;
			}
			str++;
			break;
		case '{':
			if (str[1] == ':') {
				grep->human = true; // human friendly indentation ij~{:
				grep->json = 1;
				if (!strncmp(str, "{:...", 5)) {
					grep->hud = true;
				} else if (!strncmp(str, "{:..", 4)) {
					grep->less = 1;
				}
			} else if (str[1] == '}') {
				// standard json indentation
				grep->json = 1;
				if (!strncmp(str, "{}...", 5)) {
					grep->hud = true;
				} else if (!strncmp(str, "{}..", 4)) {
					grep->less = 1;
				}
			} else {
				char *jsonPath = strdup(str + 1);
				char *jsonPathEnd = strchr(jsonPath, '}');
				if (jsonPathEnd) {
					*jsonPathEnd = 0;
					free(grep->json_path);
					grep->json_path = jsonPath;
					grep->json = 1;
				} else {
					free(jsonPath);
				}
				return;
			}
			str++;
			break;
		case '$':
			str++;
			if (*str == '!') {
				grep->sort_invert = true;
				str++;
			} else {
				grep->sort_invert = false;
			}
			grep->sort = atoi(str);
			while (IS_DIGIT(*str)) {
				str++;
			}
			if (*str == ':') {
				grep->sort_row = atoi(++str);
				str++;
			}
			break;
		case '&':
			str++;
			grep->amp = 1;
			break;
		case '<':
			grep->zoom = atoi(++str);
			// grep->zoomy = atoi (arg);
			break;
		case '+':
			if (first) {
				str++;
				grep->icase = grep->icase ? 0 : 1;
			} else {
				goto while_end;
			}
			break;
		case '^':
			str++;
			grep->begin = 1;
			break;
		case '!':
			str++;
			grep->neg = 1;
			break;
		case '?':
			str++;
			grep->counter = 1;
			if (*str == '.') {
				grep->charCounter = true;
				str++;
			} else if (*str == '?') {
				cons->filter = true;
				rz_cons_grep_help();
				return;
			}
			break;
		default:
			goto while_end;
		}
		first = false;
	}
while_end:

	len = strlen(str) - 1;
	if (len > RZ_CONS_GREP_BUFSIZE - 1) {
		eprintf("rz_cons_grep: too long!\n");
		return;
	}
	if (len > 0 && str[len] == '?') {
		grep->counter = 1;
		strncpy(buf, str, RZ_MIN(len, sizeof(buf) - 1));
		buf[len] = 0;
		len--;
	} else {
		strncpy(buf, str, sizeof(buf) - 1);
	}

	ptr = buf;
	ptr2 = strchr(ptr, '[');
	ptr3 = strchr(ptr, ']');
	is_range = 0;
	num_is_parsed = 0;
	fail = 0;
	range_begin = range_end = -1;

	if (ptr2 && ptr3) {
		end_ptr = ptr2;
		last = ptr3[1];
		ptr3[1] = '\0';
		ptr2++;
		for (; ptr2 <= ptr3; ptr2++) {
			if (fail) {
				ZERO_FILL(grep->tokens);
				grep->tokens_used = 0;
				break;
			}
			switch (*ptr2) {
			case '-':
				is_range = 1;
				num_is_parsed = 0;
				range_end = -1;
				break;
			case ']': // fallthrough to handle ']' like ','
			case ',':
				for (; range_begin <= range_end; range_begin++) {
					if (range_begin >= RZ_CONS_GREP_TOKENS) {
						fail = 1;
						break;
					}
					grep->tokens[range_begin] = 1;
					grep->tokens_used = 1;
				}
				// case of [n-]
				if (*ptr2 == ']' && is_range && !num_is_parsed) {
					num_is_parsed = 1;
					range_end = -1;
				} else {
					is_range = 0;
					num_is_parsed = 0;
				}
				break;
			default:
				if (!num_is_parsed) {
					if (is_range) {
						range_end = rz_num_get(cons->num, ptr2);
						// check for bad value, if range_end == 0, we check if ptr2 == '0'
						if (range_end == 0 && *ptr != '0') {
							range_end = -1; // this allow [n- ]
						}
					} else {
						range_begin = range_end = rz_num_get(cons->num, ptr2);
					}
					num_is_parsed = 1;
				}
			}
		}
		ptr3[1] = last;
	}

	ptr2 = strchr_ns(ptr, ':'); // line number
	grep->range_line = 2; // there is not :
	if (ptr2 && ptr2[1] != ':' && ptr2[1] && (IS_DIGIT(ptr2[1]) || ptr2[1] == '-' || ptr2[1] == '.')) {
		end_ptr = end_ptr ? RZ_MIN(end_ptr, ptr2) : ptr2;
		char *p, *token = ptr2 + 1;
		p = strstr(token, "..");
		if (!p) {
			grep->line = rz_num_get(cons->num, ptr2 + 1);
			grep->range_line = 0;
		} else {
			*p = '\0';
			grep->range_line = 1;
			if (*token) {
				grep->f_line = rz_num_get(cons->num, token);
			} else {
				grep->f_line = 0;
			}
			if (p[2]) {
				grep->l_line = rz_num_get(cons->num, p + 2);
			} else {
				grep->l_line = 0;
			}
		}
	}
	if (end_ptr) {
		*end_ptr = '\0';
	}

	len = strlen(buf) - 1;
	if (len > 1 && buf[len] == '$' && buf[len - 1] != '\\') {
		grep->end = 1;
		buf[len] = '\0';
	}

	free(grep->str);
	if (*ptr) {
		grep->str = (char *)strdup(ptr);
		do {
			optr = ptr;
			ptr = strchr(ptr, ','); // grep keywords
			if (ptr) {
				*ptr++ = '\0';
			}
			wlen = strlen(optr);
			if (!wlen) {
				continue;
			}
			if (wlen >= RZ_CONS_GREP_WORD_SIZE - 1) {
				eprintf("grep string too long\n");
				continue;
			}
			grep->nstrings++;
			if (grep->nstrings > RZ_CONS_GREP_WORDS - 1) {
				eprintf("too many grep strings\n");
				break;
			}
			rz_str_ncpy(grep->strings[grep->nstrings - 1],
				optr, RZ_CONS_GREP_WORD_SIZE);
		} while (ptr);
	} else {
		grep->str = strdup(ptr);
		grep->nstrings++;
		grep->strings[0][0] = 0;
	}
}

// Finds and returns next intgerp expression,
// unescapes escaped twiddles
static char *find_next_intgrep(char *cmd, const char *quotes) {
	char *p;
	do {
		p = (char *)rz_str_firstbut(cmd, '~', quotes);
		if (!p) {
			break;
		}
		if (p == cmd || *(p - 1) != '\\') {
			return (char *)p;
		}
		// twiddle unescape
		memmove(p - 1, p, strlen(p) + 1);
		cmd = p + 1;
	} while (*cmd);
	return NULL;
}

/*
 * Removes grep part from *cmd* and returns newly allocated string
 * with reshaped grep expression.
 *
 * Function converts multiple twiddle expressions into internal representation.
 * For example:
 * converts "~str1~str2~str3~?" into "?&str1,str2,str3"
 */
static char *preprocess_filter_expr(char *cmd, const char *quotes) {
	char *p1, *p2, *ns = NULL;
	const char *strsep = "&";
	int len;
	int i;

	p1 = find_next_intgrep(cmd, quotes);
	if (!p1) {
		return NULL;
	}

	len = strlen(p1);
	if (len > 4 && rz_str_endswith(p1, "~?") && p1[len - 3] != '\\') {
		p1[len - 2] = '\0';
		ns = rz_str_append(ns, "?");
	}

	*p1 = '\0'; // remove grep part from cmd

	i = 0;
	// parse words between '~'
	while ((p2 = find_next_intgrep(p1 + 1, quotes))) {
		ns = rz_str_append(ns, strsep);
		ns = rz_str_appendlen(ns, p1 + 1, (int)(p2 - p1 - 1));
		p1 = p2;
		strsep = ",";
		i++;
	}

	if (i > 0) {
		ns = rz_str_append(ns, ",");
	}

	ns = rz_str_append(ns, p1 + 1);

	return ns;
}

RZ_API void rz_cons_grep_parsecmd(char *cmd, const char *quotestr) {
	rz_return_if_fail(cmd && quotestr);
	char *ptr = preprocess_filter_expr(cmd, quotestr);
	if (ptr) {
		rz_str_trim(cmd);
		parse_grep_expression(ptr);
		free(ptr);
	}
}

RZ_API char *rz_cons_grep_strip(char *cmd, const char *quotestr) {
	char *ptr = NULL;

	if (cmd) {
		ptr = preprocess_filter_expr(cmd, quotestr);
		rz_str_trim(cmd);
	}
	return ptr;
}

RZ_API void rz_cons_grep_process(RZ_OWN char *grep) {
	if (!grep) {
		return;
	}
	rz_str_trim_tail(grep);
	parse_grep_expression(grep);
	free(grep);
}

static int cmp(const void *a, const void *b, void *user) {
	char *da = NULL;
	char *db = NULL;
	const char *ca = rz_str_trim_head_ro(a);
	const char *cb = rz_str_trim_head_ro(b);
	if (!a || !b) {
		return (int)(size_t)((char *)a - (char *)b);
	}
	RzConsGrep *grep = user;
	if (grep->sorted_column > 0) {
		da = strdup(ca);
		db = strdup(cb);
		int colsa = rz_str_word_set0(da);
		int colsb = rz_str_word_set0(db);
		ca = (colsa > grep->sorted_column) ? rz_str_word_get0(da, grep->sorted_column) : "";
		cb = (colsb > grep->sorted_column) ? rz_str_word_get0(db, grep->sorted_column) : "";
	}
	if (IS_DIGIT(*ca) && IS_DIGIT(*cb)) {
		ut64 na = rz_num_get(NULL, ca);
		ut64 nb = rz_num_get(NULL, cb);
		int ret = (na > nb) - (na < nb);
		free(da);
		free(db);
		return ret;
	}
	if (da && db) {
		int ret = strcmp(ca, cb);
		free(da);
		free(db);
		return ret;
	}
	free(da);
	free(db);
	return strcmp(a, b);
}

RZ_API void rz_cons_grepbuf(void) {
	RzCons *cons = rz_cons_singleton();
	cons->context->row = 0;
	cons->context->col = 0;
	cons->context->rowcol_calc_start = 0;
	const char *buf = cons->context->buffer;
	const int len = cons->context->buffer_len;
	RzConsGrep *grep = &cons->context->grep;
	const char *in = buf;
	int ret, total_lines = 0, l = 0, tl = 0;
	bool show = false;
	if (cons->filter) {
		cons->context->buffer_len = 0;
		RZ_FREE(cons->context->buffer);
		return;
	}

	if ((!len || !buf || buf[0] == '\0') && (grep->json || grep->less)) {
		grep->json = 0;
		grep->less = 0;
		grep->hud = 0;
		return;
	}

	if (grep->zoom) {
		char *in = calloc(cons->context->buffer_len + 2, 4);
		strcpy(in, cons->context->buffer);
		char *out = rz_str_scale(in, grep->zoom * 2, grep->zoomy ? grep->zoomy : grep->zoom);
		if (out) {
			free(cons->context->buffer);
			cons->context->buffer = out;
			cons->context->buffer_len = strlen(out);
			cons->context->buffer_sz = cons->context->buffer_len;
		}
		grep->zoom = 0;
		grep->zoomy = 0;
		free(in);
		return;
	}
	if (grep->json) {
		if (grep->json_path) {
			RzJson *json = rz_json_parse(cons->context->buffer);
			if (!json) {
				RZ_FREE(grep->json_path);
				return;
			}
			const RzJson *excerpt;
			// To simplify grep syntax we omit brackets in `[0]` for JSON paths
			if (*grep->json_path != '[' && *grep->json_path != '.') {
				char *tmppath = rz_str_newf("[%s]", grep->json_path);
				excerpt = rz_json_get_path(json, tmppath);
				free(tmppath);
			} else {
				excerpt = rz_json_get_path(json, grep->json_path);
			}
			if (excerpt) {
				// When we receive the path, it's fetched with the key name
				// We should get only the value
				char *u = rz_json_as_string(excerpt, false);
				if (!u) {
					RZ_FREE(grep->json_path);
					rz_json_free(json);
					return;
				}
				free(cons->context->buffer);
				cons->context->buffer = u;
				cons->context->buffer_len = strlen(u);
				cons->context->buffer_sz = cons->context->buffer_len + 1;
				grep->json = 0;
				rz_cons_newline();
			}
			rz_json_free(json);
			RZ_FREE(grep->json_path);
		} else {
			const char *palette[] = {
				cons->context->pal.graph_false, // f
				cons->context->pal.graph_true, // t
				cons->context->pal.num, // k
				cons->context->pal.comment, // v
				Color_RESET,
				NULL
			};
			char *bb = strdup(buf);
			rz_str_ansi_filter(bb, NULL, NULL, -1);
			char *out = (cons->context->grep.hppuman)
				? rz_print_json_human(bb)
				: rz_print_json_indent(bb, I(context->color_mode), "  ", palette);
			free(bb);
			if (!out) {
				return;
			}
			free(cons->context->buffer);
			cons->context->buffer = out;
			cons->context->buffer_len = strlen(out);
			cons->context->buffer_sz = cons->context->buffer_len + 1;
			grep->json = 0;
			if (grep->hud) {
				grep->hud = false;
				rz_cons_hud_string(cons->context->buffer);
			} else if (grep->less) {
				grep->less = 0;
				rz_cons_less_str(cons->context->buffer, NULL);
			}
		}
		return;
		// cons->lines = ?? return 3;
	}
	if (grep->less) {
		int less = grep->less;
		grep->less = 0;
		if (less == 2) {
			char *res = rz_cons_hud_string(buf);
			if (res) {
				rz_cons_println(res);
				free(res);
			}
		} else {
			rz_cons_less_str(buf, NULL);
			cons->context->buffer_len = 0;
			if (cons->context->buffer) {
				cons->context->buffer[0] = 0;
			}
			RZ_FREE(cons->context->buffer);
		}
		return;
	}
	if (!cons->context->buffer) {
		cons->context->buffer_len = len + 20;
		cons->context->buffer = malloc(cons->context->buffer_len);
		cons->context->buffer[0] = 0;
	}
	RzStrBuf *ob = rz_strbuf_new("");
	// if we modify cons->lines we should update I.context->buffer too
	cons->lines = 0;
	// used to count lines and change negative grep.line values
	while ((int)(size_t)(in - buf) < len) {
		char *p = strchr(in, '\n');
		if (!p) {
			break;
		}
		l = p - in;
		if (l > 0) {
			in += l + 1;
		} else {
			in++;
		}
		total_lines++;
	}
	if (!grep->range_line && grep->line < 0) {
		grep->line = total_lines + grep->line;
	}
	if (grep->range_line == 1) {
		if (grep->f_line < 0) {
			grep->f_line = total_lines + grep->f_line;
		}
		if (grep->l_line <= 0) {
			grep->l_line = total_lines + grep->l_line;
		}
	}
	bool is_range_line_grep_only = grep->range_line != 2 && !*grep->str;
	in = buf;
	while ((int)(size_t)(in - buf) < len) {
		char *p = strchr(in, '\n');
		if (!p) {
			break;
		}
		l = p - in;
		if ((!l && is_range_line_grep_only) || l > 0) {
			char *tline = rz_str_ndup(in, l);
			if (cons->grep_color) {
				tl = l;
			} else {
				tl = rz_str_ansi_filter(tline, NULL, NULL, l);
			}
			if (tl < 0) {
				ret = -1;
			} else {
				ret = rz_cons_grep_line(tline, tl);
				if (!grep->range_line) {
					if (grep->line == cons->lines) {
						show = true;
					}
				} else if (grep->range_line == 1) {
					if (grep->f_line == cons->lines) {
						show = true;
					}
					if (grep->l_line == cons->lines) {
						show = false;
					}
				} else {
					show = true;
				}
			}
			if ((!ret && is_range_line_grep_only) || ret > 0) {
				if (show) {
					char *str = rz_str_ndup(tline, ret);
					if (cons->grep_highlight) {
						int i;
						for (i = 0; i < grep->nstrings; i++) {
							char *newstr = rz_str_newf(Color_INVERT "%s" Color_RESET, grep->strings[i]);
							if (str && newstr) {
								if (grep->icase) {
									str = rz_str_replace_icase(str, grep->strings[i], newstr, 1, 1);
								} else {
									str = rz_str_replace(str, grep->strings[i], newstr, 1);
								}
							}
							free(newstr);
						}
					}
					if (str) {
						rz_strbuf_append(ob, str);
						rz_strbuf_append(ob, "\n");
					}
					free(str);
				}
				if (!grep->range_line) {
					show = false;
				}
				cons->lines++;
			} else if (ret < 0) {
				free(tline);
				return;
			}
			free(tline);
			in += l + 1;
		} else {
			in++;
		}
	}

	cons->context->buffer_len = rz_strbuf_length(ob);
	if (grep->counter) {
		int cnt = grep->charCounter ? strlen(cons->context->buffer) : cons->lines;
		if (cons->context->buffer_len < 10) {
			cons->context->buffer_len = 10; // HACK
		}
		snprintf(cons->context->buffer, cons->context->buffer_len, "%d\n", cnt);
		cons->context->buffer_len = strlen(cons->context->buffer);
		cons->num->value = cons->lines;
		rz_strbuf_free(ob);
		return;
	}

	const int ob_len = rz_strbuf_length(ob);
	if (ob_len >= cons->context->buffer_sz) {
		cons->context->buffer_sz = ob_len + 1;
		cons->context->buffer = rz_strbuf_drain(ob);
	} else {
		memcpy(cons->context->buffer, rz_strbuf_getbin(ob, NULL), ob_len);
		cons->context->buffer[ob_len] = 0;
		rz_strbuf_free(ob);
	}
	cons->context->buffer_len = ob_len;

	if (grep->sort != -1) {
#define INSERT_LINES(list) \
	do { \
		rz_list_foreach (list, iter, str) { \
			int len = strlen(str); \
			memcpy(ptr, str, len); \
			memcpy(ptr + len, "\n", 2); \
			ptr += len + 1; \
			nl++; \
		} \
	} while (false)

		RzListIter *iter;
		int nl = 0;
		char *ptr = cons->context->buffer;
		char *str;
		grep->sorted_column = grep->sort;
		rz_list_sort(grep->sorted_lines, cmp, grep);
		if (grep->sort_invert) {
			rz_list_reverse(grep->sorted_lines);
		}
		INSERT_LINES(grep->unsorted_lines);
		INSERT_LINES(grep->sorted_lines);
		cons->lines = nl;
		rz_list_free(grep->sorted_lines);
		grep->sorted_lines = NULL;
		rz_list_free(grep->unsorted_lines);
		grep->unsorted_lines = NULL;
	}
}

RZ_API int rz_cons_grep_line(char *buf, int len) {
	RzCons *cons = rz_cons_singleton();
	RzConsGrep *grep = &cons->context->grep;
	const char *delims = " |,;=\t";
	char *tok = NULL;
	bool hit = grep->neg;
	int outlen = 0;
	bool use_tok = false;
	size_t i;

	char *in = calloc(1, len + 1);
	if (!in) {
		return 0;
	}
	char *out = calloc(1, len + 2);
	if (!out) {
		free(in);
		return 0;
	}
	memcpy(in, buf, len);

	if (grep->nstrings > 0) {
		int ampfail = grep->amp;
		for (i = 0; i < grep->nstrings; i++) {
			const char *p = rz_strstr_ansi(in, grep->strings[i], grep->icase);
			if (!p) {
				ampfail = 0;
				continue;
			}
			if (grep->begin) {
				hit = (p == in);
				if (grep->neg) {
					hit = !hit;
				}
			} else {
				hit = !grep->neg;
			}
			// TODO: optimize without strlen without breaking t/feat_grep (grep end)
			if (grep->end && (strlen(grep->strings[i]) != strlen(p))) {
				hit = 0;
			}
			if (!grep->amp) {
				break;
			}
		}
		if (grep->amp) {
			hit = ampfail;
		}
	} else {
		hit = 1;
	}

	if (hit) {
		if (!grep->range_line) {
			if (grep->line == cons->lines) {
				use_tok = true;
			}
		} else if (grep->range_line == 1) {
			use_tok = RZ_BETWEEN(grep->f_line, cons->lines, grep->l_line);
		} else {
			use_tok = true;
		}
		if (use_tok && grep->tokens_used) {
			for (i = 0; i < RZ_CONS_GREP_TOKENS; i++) {
				tok = strtok(i ? NULL : in, delims);
				if (tok) {
					if (grep->tokens[i]) {
						int toklen = strlen(tok);
						memcpy(out + outlen, tok, toklen);
						memcpy(out + outlen + toklen, " ", 2);
						outlen += toklen + 1;
						if (!(*out)) {
							free(in);
							free(out);
							return -1;
						}
					}
				} else {
					if ((*out)) {
						break;
					}
					free(in);
					free(out);
					return 0;
				}
			}
			outlen = outlen > 0 ? outlen - 1 : 0;
			if (outlen > len) { // should never happen
				eprintf("rz_cons_grep_line: how you have reached this?\n");
				free(in);
				free(out);
				return -1;
			}
			memcpy(buf, out, len);
			len = outlen;
		}
	} else {
		len = 0;
	}
	free(in);
	free(out);
	if (grep->sort != -1) {
		char ch = buf[len];
		buf[len] = 0;
		if (!grep->sorted_lines) {
			grep->sorted_lines = rz_list_newf(free);
		}
		if (!grep->unsorted_lines) {
			grep->unsorted_lines = rz_list_newf(free);
		}
		if (cons->lines >= grep->sort_row) {
			rz_list_append(grep->sorted_lines, strdup(buf));
		} else {
			rz_list_append(grep->unsorted_lines, strdup(buf));
		}
		buf[len] = ch;
	}

	return len;
}

RZ_API void rz_cons_grep(const char *grep) {
	parse_grep_expression(grep);
	rz_cons_grepbuf();
}
