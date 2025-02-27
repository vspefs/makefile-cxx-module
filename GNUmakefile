#   Copyright (C) 2025  vspefs
#
#   This program is free software: you can redistribute it and/or modify
#   it under the terms of the GNU Affero General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU Affero General Public License for more details.
#
#   You should have received a copy of the GNU Affero General Public License
#   along with this program.  If not, see <https://www.gnu.org/licenses/>.

CXX := g++
ALL_CXXFLAGS := -std=c++26 -fmodules $(CXXFLAGS)

CXX_STDMODULE := /usr/include/c++/15.0.1/bits/std.cc
SRCS := a.cc b.cc c.cc ba.cc
HEADER_UNITS := inc/a.h e.hh d.hh

all: exe

OBJS := $(SRCS:.cc=.o)
DEPS := $(SRCS:.cc=.d)

HEADER_UNIT_CMIS := $(foreach unit,$(HEADER_UNITS),gcm.cache/,/$(unit).gcm)
$(HEADER_UNIT_CMIS): gcm.cache/,/%.gcm: %
	$(CXX) -c $(CPPFLAGS) $(ALL_CXXFLAGS) $<
$(foreach i, $(shell seq 2 $(words $(HEADER_UNIT_CMIS))), \
    $(eval $(word $(i), $(HEADER_UNIT_CMIS)): $(word $(shell expr $(i) - 1), $(HEADER_UNIT_CMIS))) \
)
$(DEPS): $(HEADER_UNIT_CMIS)

OBJS += std.o
std.o: $(CXX_STDMODULE)
	$(CXX) -c $(CPPFLAGS) $(ALL_CXXFLAGS) $^ -o $@
gcm.cache/std.gcm: std.o ;

exe: $(OBJS)
	$(CXX) $(LDFLAGS) $^ $(LOADLIBS) $(LDLIBS) -o $@
clean:
	$(RM) $(OBJS) $(DEPS)
	$(RM) exe
	$(RM) -r gcm.cache
.PHONY: all clean

ifneq ($(filter clean,$(MAKECMDGOALS)),clean)
-include $(DEPS)
endif

%.d: %.cc
	@set -e; rm -f $@; \
	$(CXX) -std=c++26 -fmodules $(CPPFLAGS) -MM $< > $@.$$$$; \
	sed 's,\($*\)\.o,\1.o $@,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

%.o: %.cc
	$(CXX) -c $(CPPFLAGS) $(ALL_CXXFLAGS) $<

%.gcm:
	$(CXX) -c -fmodule-only $(CPPFLAGS) $(ALL_CXXFLAGS) $<