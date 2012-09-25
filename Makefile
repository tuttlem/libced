# Generic Makefile for compiling a shared library.

CC := clang
# PKGS := ...
LIBNAME := ced
SRCDIR := src
BUILDDIR := build
# CFLAGS := -g -Wall `pkg-config --cflags $(PKGS)`
CFLAGS := -g -Wall -fPIC
# LIBS := `pkg-config --libs $(PKGS)`
LIBS :=
TARGET := bin/lib$(LIBNAME).so
LDFLAGS := -shared -Wl,-soname=$(TARGET)

SRCEXT = c
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
DEPS := $(OBJECTS:.o=.deps)

$(TARGET): $(OBJECTS)
	@echo " Linking..."; $(CC) $(LDFLAGS) $^ -o $(TARGET) $(LIBS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " CC $<"; $(CC) $(CFLAGS) -MD -MF $(@:.o=.deps) -c -o $@ $<

clean:
	@echo " Cleaning..."; $(RM) -r $(BUILDDIR) $(TARGET)

-include $(DEPS)

.PHONY: clean
