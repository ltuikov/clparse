#
# Command line parsing utility library
#
# Copyright (c) 2006 Luben Tuikov
#
# This file is licensed under GPLv2.
#
# This file is part of the clparse utility library.
#
# The clparse utility library is free software; you can redistribute
# it and/or modify it under the terms of the GNU General Public
# License as published by the Free Software Foundation; version 2 of
# the License.
#
# The clparse utility library is distributed in the hope that it will
# be useful, but WITHOUT ANY WARRANTY; without even the implied
# warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with the clparse utility library; if not, write to the Free
# Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
# 02110-1301 USA
#

.PHONY: clean so ar

CLPARSE_H=clparse.h
CLPARSE_OBJ=clparse.o

all: lib$(CLPARSE_OBJ:.o=.so) $(CLPARSE_OBJ:.o=.a)

$(CLPARSE_OBJ): $(CLPARSE_H)

lib%.so: %.c %.h
	$(CC) -shared -fpic $< -o $@

%.a: %.o
	$(AR) rc $@ $<

clean:
	$(RM) *~ $(CLPARSE_OBJ) lib$(CLPARSE_OBJ:.o=.so) $(CLPARSE_OBJ:.o=.a)
