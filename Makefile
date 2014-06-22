# Generic Makefile for compiling a shared library.

UNAME := $(shell uname)

CC := gcc
LIBNAME := ced
SRCDIR := src
BUILDDIR := build
CFLAGS := -g -Wall -fPIC -g
LIBS :=
TARGET := lib$(LIBNAME).a
LDFLAGS := -shared -Wl,-soname=$(TARGET)
AR := ar
ARFLAGS := rcs

# check if we're compiling on Darwin, as their linked doesn't
# support the "soname" switch. Need to change this conditionally
ifeq ($(UNAME), Darwin)
   LDFLAGS := -shared -Wl,-install_name,$(TARGET)
endif

SRCEXT = c
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
DEPS := $(OBJECTS:.o=.deps)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " CC $<"; $(CC) $(CFLAGS) -MD -MF $(@:.o=.deps) -c -o $@ $<

$(TARGET): $(OBJECTS)
	@echo " Making Static Library..."; $(AR) $(ARFLAGS) $(TARGET) $(OBJECTS)
	@mv $(TARGET) bin/$(TARGET)
clean:
	@echo " Cleaning..."; $(RM) -r $(BUILDDIR) $(TARGET)

-include $(DEPS)

.PHONY: clean
