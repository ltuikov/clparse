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

#ifndef __CLPARSE_H__
#define __CLPARSE_H__

#define CL_NO_ARGS	1
#define CL_EXIT_REQ	2
#define CL_NO_ARG_VAL   3

struct clparse_opt {
	char short_opt;
	char *long_opt;
	int  has_value;		  /* 0 - no, 1 - yes */
	int (*action)(char *value, void *po);
	char *description;
};

/**
 * cl_get_prog_opts -- get program options
 * index_last if non-null will be set to the index of the last
 * argv which didn't belong to an argument.
 * po is passed as is to the 2nd argument of the action callback.
 */
int cl_get_prog_opts(int argc, char *argv[],
		     const struct clparse_opt *opts, const int num_opts,
		     void *po, int *index_last, int silent);
/**
 * cl_print__args_help -- Print the options in a "help" format
 * as described by the struct clparse_opt array.
 */
void cl_print_opts_help(const struct clparse_opt *opts, const int num_opts);

#endif /* __CLPARSE_H__ */
