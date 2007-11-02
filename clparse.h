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

#ifndef __CLPARSE_H__
#define __CLPARSE_H__

#include <stdio.h>

#define CL_NO_ARGS	1
#define CL_NO_OPT_VAL   2
#define CL_UNKNWN_OPT	3

#define SILENT		0
#define NOT_SILENT	1

struct clparse_opt {
	char short_opt;
	char *long_opt;
	int  has_value;		  /* 0 - no, 1 - yes */
	int (*action)(char *value, void *po);
	char *description;
};

/**
 * cl_get_prog_opts -- get program options
 * @opts: an array of struct clparse_opt, i.e. options
 * @num_opts: number of elements in @opts
 * @po is passed as is to the 2nd argument of the clparse_opt::action callback.
 * @index_first: if non-null will be set to the index of the first
 *      argv which didn't belong to an argument.
 * @out: a standard I/O stream where output is to be printed to.
 * Returns one of the macros above.
 */
int cl_get_prog_opts(int argc, char *argv[],
		     const struct clparse_opt *opts, const int num_opts,
		     void *po, int *index_first, int silent, FILE *out);
/**
 * cl_print__args_help -- Print the options in a "help" format
 * as described by the struct clparse_opt array.
 */
void cl_print_opts_help(const struct clparse_opt *opts, const int num_opts,
			FILE *out);

#endif /* __CLPARSE_H__ */
