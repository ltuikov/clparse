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

struct clparse_opts {
	char short_opt;
	char *long_opt;
	int  has_value;
	int (*action)(char *value, void *po);
	char *description;
};

#endif /* __CLPARSE_H__ */
