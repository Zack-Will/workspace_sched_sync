/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2010-2014 Intel Corporation
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>

#include <rte_memory.h>
#include <rte_launch.h>
#include <rte_eal.h>
#include <rte_per_lcore.h>
#include <rte_lcore.h>
#include <rte_debug.h>

#include <uk/print.h>

static int
lcore_hello(__attribute__((unused)) void *arg)
{
	// unsigned lcore_id;
	// lcore_id = rte_lcore_id();
	// printf("hello from core %u\n", lcore_id);
	// return 0;
        unsigned lcore_id;
        lcore_id = rte_lcore_id();
        FILE *file;
        char name[6];
        snprintf(name, 6, "core%d", lcore_id);
        file = fopen(name, "w");
        char hello[18];
        snprintf(hello, 18, "hello from core %d", lcore_id);
        fputs(hello, file);
        fclose(file);
        uk_pr_debug("finish first hello from core %d\n", lcore_id);
}

static int
lcore_another_hello(__attribute__((unused)) void *arg)
{
	// unsigned lcore_id;
	// lcore_id = rte_lcore_id();
	// printf("hello from core %u\n", lcore_id);
	// return 0;
        unsigned lcore_id;
        lcore_id = rte_lcore_id();
        FILE *file;
        char name[7];
        snprintf(name, 7, "acore%d", lcore_id);
        file = fopen(name, "w");
        char hello[25];
        snprintf(hello, 25, "another hello from core %d", lcore_id);
        fputs(hello, file);
        fclose(file);
}

int
main(int argc, char **argv)
{
	int ret;
	unsigned lcore_id;

	ret = rte_eal_init(argc, argv);
	if (ret < 0)
		rte_panic("Cannot init EAL\n");

	RTE_LCORE_FOREACH_SLAVE(lcore_id) {
		rte_eal_remote_launch(lcore_hello, NULL, lcore_id);
	}

        //rte_eal_mp_wait_lcore();
        RTE_LCORE_FOREACH_SLAVE(lcore_id) {
		rte_eal_remote_launch(lcore_another_hello, NULL, lcore_id);
	}

	//lcore_hello(NULL);

	rte_eal_mp_wait_lcore();
	return 0;
}