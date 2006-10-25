/*
 * Command line parsing utility library
 *
 * Copyright (c) 2006 Luben Tuikov
 *
 * This file is licensed under GPLv2.
 *
 * This file is part of the clparse utility library.
 *
 * The clparse utility library is free software; you can redistribute
 * it and/or modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; version 2 of
 * the License.
 *
 * The clparse utility library is distributed in the hope that it will
 * be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with the clparse utility library; if not, write to the Free
 * Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA
 *
 */

#include <stdio.h>
#include <string.h>
#include "clparse.h"

/**
 * cl_get_prog_opts -- get program options
 * index_last if non-null will be set to the index of the last
 * argv which didn't belong to an argument.
 * po is passed as is to the 2nd argument of the action callback.
 */
int cl_get_prog_opts(int argc, char *argv[],
		     const struct clparse_opt *opts, const int num_opts,
		     void *po, int *index_last, int silent)
{
	int i;
	const char *prog = NULL;

	if (argc <= 1)
		return CL_NO_ARGS;
	if (!argv)
		return CL_NO_ARGS;

	prog = strrchr(argv[0], '/');
	if (prog)
		prog++;
	else
		prog = argv[0];

	for (i = 1; i < argc; i++) {
		int long_opt = 0;
		char *op = NULL;
		char *value = NULL;
		int k;

		if (!argv[i])
			continue;
		if (argv[i][0] != '-') {
			if (index_last)
				*index_last = i;
			continue;
		}
		if (argv[i][1] == '-') {
			long_opt = 1;
			op = &argv[i][2];
		} else
			op = &argv[i][1];
		for (k = 0; k < num_opts; k++) {
			if (long_opt) {
				if (strncmp(opts[k].long_opt, op, strlen(opts[k].long_opt)) != 0)
					continue;
			} else if (opts[k].short_opt != *op || *(op+1) != '\0')
				continue;
			if (opts[k].has_value) {
				if (long_opt) {
					value = strchr(op, '=');
					if (value) {
						value++;
						if (!*value) {
							if (!silent)
								fprintf(stderr,
									"%s: argument %s needs a "
									"value\n", prog, argv[i]);
							if (index_last)
								*index_last = i;
							return CL_NO_ARG_VAL;
						}
					}
				}
				if (!value) {
					if (i + 1 >= argc) {
						if (!silent)
							fprintf(stderr,
								"%s: argument %s needs a "
								"value\n", prog, argv[i]);
						if (index_last)
							*index_last = i;
						return CL_NO_ARG_VAL;
					} else {
						i++;
						value = argv[i];
						if (!value || !*value) {
							if (!silent)
								fprintf(stderr,
									"%s: argument %s needs a "
									"value\n", prog, argv[i-1]);
							if (index_last)
								*index_last = i;
							return CL_NO_ARG_VAL;
						}
					}
				}
			}
			if (opts[k].action(value, po))
				return CL_EXIT_REQ;
			else
				break;
		}
		if (k >= num_opts) {
			if (!silent)
				fprintf(stderr, "%s: no such argument \"%s\"\n",
					prog, argv[i]);
		}
	}
	return 0;
}

void cl_print_opts_help(const struct clparse_opt *opts, const int num_opts)
{
	int i;
	for (i = 0; i < num_opts; i++) {
		printf("  -%c%s or --%s%s\t%s\n",
		       opts[i].short_opt,
		       opts[i].has_value ? " <argument>" : "",
		       opts[i].long_opt,
		       opts[i].has_value ? "[=| ]<argument>" : "",
		       opts[i].description);
	}
}
