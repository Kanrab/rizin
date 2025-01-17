// SPDX-FileCopyrightText: 2020 condret <condr3t@protonmail.com>
// SPDX-License-Identifier: LGPL-3.0-only

#include <rz_util.hpp>
#include "minunit.hpp"

static bool test_rz_id_storage_toomany(void) {
	bool r;
	ut32 id0, id1, id2;
	RzIDStorage *ids = rz_id_storage_new(20, 22);
	r = rz_id_storage_add(ids, "aaa", &id0);
	mu_assert_true(r, "id0");
	r = rz_id_storage_add(ids, "bbb", &id1);
	mu_assert_true(r, "id1");
	r = rz_id_storage_add(ids, "ccc", &id2);
	mu_assert_false(r, "id2");
	rz_id_storage_free(ids);
	mu_end;
}

static bool test_rz_id_storage_wrong(void) {
	bool r;
	ut32 id0;
	RzIDStorage *ids = rz_id_storage_new(20, 10);
	r = rz_id_storage_add(ids, "aaa", &id0);
	mu_assert_false(r, "id0");
	rz_id_storage_free(ids);
	mu_end;
}

static bool test_rz_id_storage_prev_next_eq_0(void) {
	// test if next reverts prev
	bool r;
	ut32 id0, id1, id2;
	RzIDStorage *ids = rz_id_storage_new(1, 15);
	r = rz_id_storage_add(ids, "aaa", &id0);
	mu_assert_true(r, "id0");
	mu_assert_eq(id0, 1, "id0");
	r = rz_id_storage_add(ids, "bbb", &id1);
	mu_assert_true(r, "id1");
	mu_assert_eq(id1, 2, "id1");
	r = rz_id_storage_add(ids, "ccc", &id2);
	mu_assert_true(r, "id2");
	mu_assert_eq(id2, 3, "id2");
	ut32 id = id1;
	rz_id_storage_get_prev(ids, &id);
	rz_id_storage_get_next(ids, &id);
	rz_id_storage_free(ids);

	mu_assert_eq(id, id1, "rz_id_storage_{next/prev} reversal 0");
	mu_end;
}

static bool test_rz_id_storage_prev_next_eq_1(void) {
	// test if next reverts prev (modulo wrap 1)
	bool r;
	ut32 id, id0, id1, id2;
	RzIDStorage *ids = rz_id_storage_new(0, 15);
	rz_id_storage_add(ids, "bbb", &id0);
	rz_id_storage_add(ids, "aaa", &id1);
	rz_id_storage_add(ids, "ccc", &id2);
	id = id0;
	r = rz_id_storage_get_prev(ids, &id);
	mu_assert_false(r, "get_prev(0) doesnt exist");
	id = id1;
	r = rz_id_storage_get_prev(ids, &id);
	mu_assert_true(r, "get_prev(1) must exist");
	r = rz_id_storage_get_next(ids, &id);
	mu_assert_true(r, "get_prev(1) must exist");
	rz_id_storage_free(ids);

	mu_assert_eq(id, id1, "rz_id_storage_{next/prev} reversal 1");
	mu_end;
}

static bool test_rz_id_storage_prev_next_min(void) {
	// test if next reverts prev (modulo wrap 1)
	bool r;
	ut32 id, id0, id1, id2;
	RzIDStorage *ids = rz_id_storage_new(3, 15);
	rz_id_storage_add(ids, "bbb", &id0);
	rz_id_storage_add(ids, "aaa", &id1);
	rz_id_storage_add(ids, "ccc", &id2);
	id = id0;
	r = rz_id_storage_get_prev(ids, &id);
	mu_assert_false(r, "get_prev(0) doesnt exist");
	id = id1;
	r = rz_id_storage_get_prev(ids, &id);
	mu_assert_true(r, "get_prev(1) must exist");
	r = rz_id_storage_get_next(ids, &id);
	mu_assert_true(r, "get_prev(1) must exist");
	rz_id_storage_free(ids);
	mu_assert_eq(id, id1, "rz_id_storage_{next/prev} reversal 1");
	mu_end;
}

static bool test_rz_id_storage_empty(void) {
	// test if next reverts prev (modulo wrap 2)
	ut32 _id = 0;
	RzIDStorage *ids = rz_id_storage_new(0, 15);
	bool r = rz_id_storage_get_prev(ids, &_id);
	mu_assert_false(r, "get prev from none");
	r = rz_id_storage_get_next(ids, &_id);
	mu_assert_false(r, "get next from none");
	r = rz_id_storage_get_highest(ids, &_id);
	mu_assert_false(r, "get high from none");
	r = rz_id_storage_get_lowest(ids, &_id);
	mu_assert_false(r, "get low from none");
	rz_id_storage_free(ids);

	mu_end;
}

static bool test_rz_id_storage_prev_next_eq_2(void) {
	// test if next reverts prev (modulo wrap 2)
	ut32 id, _id;
	RzIDStorage *ids = rz_id_storage_new(0, 15);
	rz_id_storage_add(ids, "aaa", &_id);
	rz_id_storage_add(ids, "ccc", &_id);
	rz_id_storage_add(ids, "bbb", &id);
	_id = id;
	rz_id_storage_get_prev(ids, &_id);
	rz_id_storage_get_next(ids, &_id);
	rz_id_storage_free(ids);

	mu_assert_eq(id, _id, "rz_id_storage_{next/prev} reversal 2");
	mu_end;
}

static bool test_prevnext(void) {
	RzIDStorage *ids = rz_id_storage_new(5, 10);
	ut32 id[3];
	rz_id_storage_add(ids, "a", &id[0]);
	rz_id_storage_add(ids, "b", &id[1]);
	rz_id_storage_add(ids, "c", &id[2]);

	RzList *ids_list = rz_id_storage_list(ids);
	const char *val0list = rz_list_get_n(ids_list, 0);
	ut32 id0list = id[*val0list - 'a'];
	const char *val1list = rz_list_get_n(ids_list, 1);
	ut32 id1list = id[*val1list - 'a'];
	const char *val2list = rz_list_get_n(ids_list, 2);
	ut32 id2list = id[*val2list - 'a'];

	bool idw;
	ut32 idi = id0list;
	rz_id_storage_get_next(ids, &idi);
	mu_assert_eq(idi, id1list, "next of id0 should be id1");
	rz_id_storage_get_next(ids, &idi);
	mu_assert_eq(idi, id2list, "next of id1 should be id2");
	idw = rz_id_storage_get_next(ids, &idi);
	mu_assert_eq(idw, false, "next of id2 (last) should not exist (-1)");

	rz_id_storage_get_prev(ids, &idi);
	mu_assert_eq(idi, id1list, "prev of id2 should be id1");
	rz_id_storage_get_prev(ids, &idi);
	mu_assert_eq(idi, id0list, "prev of id1 should be id0");
	idw = rz_id_storage_get_prev(ids, &id0list);
	mu_assert_eq(idw, false, "prev of id0 (first) should not exist (-1)");

	ut32 lowid;
	bool l = rz_id_storage_get_lowest(ids, &lowid);
	mu_assert_true(l, "get-lowest must return true");
	mu_assert_eq(lowid, id0list, "lowest should be id0");

	bool h = rz_id_storage_get_highest(ids, &lowid);
	mu_assert_true(h, "get-highest must return true");
	mu_assert_eq(lowid, id2list, "highest should be id2");

	rz_list_free(ids_list);
	rz_id_storage_free(ids);

	mu_end;
}

static int all_tests(void) {
	mu_run_test(test_rz_id_storage_prev_next_eq_0);
	mu_run_test(test_rz_id_storage_prev_next_eq_1);
	mu_run_test(test_rz_id_storage_prev_next_eq_2);
	mu_run_test(test_rz_id_storage_prev_next_min);
	mu_run_test(test_rz_id_storage_toomany);
	mu_run_test(test_prevnext);
	mu_run_test(test_rz_id_storage_empty);
	mu_run_test(test_rz_id_storage_wrong);
	return tests_passed != tests_run;
}

mu_main(all_tests)
