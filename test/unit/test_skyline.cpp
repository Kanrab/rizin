// SPDX-FileCopyrightText: 2020 GustavoLCR <gugulcr@gmail.com>
// SPDX-License-Identifier: LGPL-3.0-only

#include <rz_util.hpp>
#include <rz_skyline.hpp>
#include "minunit.hpp"

bool test_rz_skyline(void) {
	RzSkyline sky;
	rz_skyline_init(&sky);
	rz_skyline_add(&sky, (RzInterval){ 0, 1 }, (void *)1);
	mu_assert_true(rz_skyline_contains(&sky, 0), "Skyline should contain 0");
	mu_assert_false(rz_skyline_contains(&sky, 1), "Skyline shouldn't contain 1");
	rz_skyline_add(&sky, (RzInterval){ 2, 4 }, (void *)2);
	mu_assert_true(rz_skyline_contains(&sky, 2), "Skyline should contain 2");
	mu_assert_eq((size_t)rz_skyline_get(&sky, 0), 1, "rz_skyline_get should get first map");
	mu_assert_eq((size_t)rz_skyline_get(&sky, 2), 2, "rz_skyline_get should get second map");
	mu_assert_eq((size_t)rz_skyline_get(&sky, 3), 2, "rz_skyline_get should get second map");
	mu_assert_eq((size_t)rz_skyline_get_intersect(&sky, 1, 2), 2, "rz_skyline_get_intersect should get second map");
	rz_skyline_add(&sky, (RzInterval){ 0, 3 }, (void *)3);
	mu_assert_true(rz_skyline_contains(&sky, 0) && rz_skyline_contains(&sky, 3),
		"Skyline should still contain 0 to 3 after overlap");
	mu_assert_eq((size_t)rz_skyline_get(&sky, 0), 3, "rz_skyline_get should get third map");
	rz_skyline_add(&sky, (RzInterval){ UT64_MAX - 1, 2 }, (void *)4);
	mu_assert_true(rz_skyline_contains(&sky, UT64_MAX), "Skyline should contain UT64_MAX");
	mu_assert_eq((size_t)rz_skyline_get(&sky, UT64_MAX), 4, "rz_skyline_get should get fourth map");
	rz_skyline_fini(&sky);
	rz_skyline_init(&sky);
	rz_skyline_add(&sky, (RzInterval){ 1, 1 }, (void *)1);
	mu_assert_false(rz_skyline_contains(&sky, 0), "Skyline shouldn't contain 0");
	rz_skyline_fini(&sky);
	mu_end;
}

bool test_rz_skyline_overlaps(void) {
	RzSkyline sky;
	rz_skyline_init(&sky);

	rz_skyline_add(&sky, (RzInterval){ 10, 10 }, (void *)1);
	const RzSkylineItem *item = rz_skyline_get_item(&sky, 10);
	mu_assert_eq((size_t)item->user, 1, "rz_skyline_get should get 1st map");

	rz_skyline_add(&sky, (RzInterval){ 9, 2 }, (void *)2);
	item = rz_skyline_get_item(&sky, 10);
	mu_assert_eq((size_t)item->user, 2, "rz_skyline_get should get 2nd map");

	rz_skyline_add(&sky, (RzInterval){ 19, 2 }, (void *)3);
	item = rz_skyline_get_item(&sky, 19);
	mu_assert_eq((size_t)item->user, 3, "rz_skyline_get should get 3rd map");

	rz_skyline_add(&sky, (RzInterval){ 14, 3 }, (void *)4);
	item = rz_skyline_get_item(&sky, 14);
	mu_assert_eq((size_t)item->user, 4, "rz_skyline_get should get 4th map");

	item = rz_skyline_get_item(&sky, 12);
	mu_assert_eq((size_t)item->user, 1, "rz_skyline_get should get 1st map head after it was overlapped");
	mu_assert_eq(rz_itv_begin(item->itv), 11, "1st map head should start at 11");
	mu_assert_eq(rz_itv_end(item->itv), 14, "1st map head should end at 14");

	item = rz_skyline_get_item(&sky, 17);
	mu_assert_eq((size_t)item->user, 1, "rz_skyline_get should get 1st map tail after it was overlapped");
	mu_assert_eq(rz_itv_begin(item->itv), 17, "1st map tail should start at 17");
	mu_assert_eq(rz_itv_end(item->itv), 19, "1st map tail should end at 19");

	rz_skyline_add(&sky, (RzInterval){ 0, 30 }, (void *)5);
	mu_assert_eq(rz_vector_len(&sky.v), 1, "5th map should cover entire skyline");
	item = rz_skyline_get_item(&sky, 10);
	mu_assert_eq((size_t)item->user, 5, "rz_skyline_get should get 5th map");
	mu_assert_eq(rz_itv_size(item->itv), 30, "5th map should have size of 30");

	rz_skyline_add(&sky, (RzInterval){ 0, 10 }, (void *)6);
	rz_skyline_add(&sky, (RzInterval){ 10, 10 }, (void *)7);
	rz_skyline_add(&sky, (RzInterval){ 20, 10 }, (void *)8);
	rz_skyline_add(&sky, (RzInterval){ 30, 10 }, (void *)9);
	mu_assert_eq(rz_vector_len(&sky.v), 4, "maps 5 through 9 should be the only ones existing");

	rz_skyline_add(&sky, (RzInterval){ 5, 30 }, (void *)10);
	mu_assert_eq(rz_vector_len(&sky.v), 3, "10th map should remove all maps it covered, leaving a head and a tail");

	item = rz_skyline_get_item(&sky, 35);
	mu_assert_eq(rz_itv_begin(item->itv), 35, "9th map should begin at 35 after 10th covered its beginning");

	rz_skyline_add(&sky, (RzInterval){ 3, 5 }, (void *)11);
	item = rz_skyline_get_item(&sky, 0);
	mu_assert_eq(rz_itv_size(item->itv), 3, "6th map should have size of 3 after 11th covered its end");

	item = rz_skyline_get_item(&sky, 20);
	mu_assert_eq(rz_itv_begin(item->itv), 8, "10th map should begin at 8 after 11th covered its beginning");

	rz_skyline_add(&sky, (RzInterval){ 3, 5 }, (void *)12);
	item = rz_skyline_get_item(&sky, 3);
	bool cond = rz_vector_len(&sky.v) == 4 && rz_itv_begin(item->itv) == 3 && rz_itv_end(item->itv) == 8 && (size_t)item->user == 12;
	mu_assert_true(cond, "12th map should completely cover 11th");

	rz_skyline_fini(&sky);
	mu_end;
}

static int all_tests(void) {
	mu_run_test(test_rz_skyline);
	mu_run_test(test_rz_skyline_overlaps);
	return tests_passed != tests_run;
}

mu_main(all_tests)
