/*
 * Command line parsing utility library
 * Copyright (C) 2006, 2007 Luben Tuikov
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <string.h>
#include "clparse.h"

/**
 * cl_get_prog_opts -- get program options
 * index_first if non-null will be set to the index of the first
 * argv which didn't belong to an argument.
 * po is passed as is to the 2nd argument of the action callback.
 * For more details see the header file.
 * Returns one of the macros above.
 */
int cl_get_prog_opts(int argc, char *argv[],
		     const struct clparse_opt *opts, const int num_opts,
		     void *po, int *index_first, int silent, FILE *out)
{
	int i, res;
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
			if (index_first)
				*index_first = i;
			return 0;
		}
		if (argv[i][1] == '-') {
			long_opt = 1;
			op = &argv[i][2];
		} else
			op = &argv[i][1];
	Again:
		for (k = 0; k < num_opts; k++) {
			if (long_opt && opts[k].long_opt) {
				if (strncmp(opts[k].long_opt, op, strlen(opts[k].long_opt)) != 0)
					continue;
			} else if (opts[k].short_opt != *op)
				continue;
			if (opts[k].has_value) {
				value = strchr(op, '=');
				if (value) {
					value++;
					if (!*value) {
						if (!silent)
							fprintf(out,
								"%s: option %s needs a "
								"value\n", prog, argv[i]);
						if (index_first)
							*index_first = i;
						return CL_NO_OPT_VAL;
					}
				}
				if (!value) {
					if (i + 1 >= argc) {
						if (!silent)
							fprintf(out,
								"%s: option %s needs a "
								"value\n", prog, argv[i]);
						if (index_first)
							*index_first = i;
						return CL_NO_OPT_VAL;
					} else {
						i++;
						value = argv[i];
						if (!value || !*value) {
							if (!silent)
								fprintf(out,
									"%s: option %s needs a "
									"value\n", prog, argv[i-1]);
							if (index_first)
								*index_first = i;
							return CL_NO_OPT_VAL;
						}
					}
				}
			}
			if ((res = opts[k].action(value, po)) != 0)
				return res;
			if (!long_opt && !opts[k].has_value) {
				/* Option has no value and is a short option.
				 * Check if another option is right after it,
				 * i.e. -abcd... */
				op++;
				if (*op)
					goto Again;
				else
					break;
			} else
				break;
		}
		if (k >= num_opts) {
			if (!silent) {
				if (long_opt)
					fprintf(out, "%s: no such option \"%s\"\n",
						prog, op);
				else
					fprintf(out, "%s: no such option \"%c\"\n",
						prog, *op);
			}
			return CL_UNKNWN_OPT;
		}
	}
	return 0;
}

void cl_print_opts_help(const struct clparse_opt *opts, const int num_opts,
			FILE *out)
{
	int i;
	for (i = 0; i < num_opts; i++) {
		if (opts[i].short_opt != '\0' && opts[i].long_opt != NULL) {
			fprintf(out, "  -%c%s or --%s%s\t%s\n",
				opts[i].short_opt,
				opts[i].has_value ? "[=| ]<argument>" : "",
				opts[i].long_opt,
				opts[i].has_value ? "[=| ]<argument>" : "",
				opts[i].description);
		} else if (opts[i].long_opt != NULL) {
			fprintf(out, "  --%s%s\t%s\n",
				opts[i].long_opt,
				opts[i].has_value ? "[=| ]<argument>" : "",
				opts[i].description);
		} else if (opts[i].short_opt != '\0') {
			fprintf(out, "  -%c%s\t%s\n",
				opts[i].short_opt,
				opts[i].has_value ? "[=| ]<argument>" : "",
				opts[i].description);
		}
	}
}
