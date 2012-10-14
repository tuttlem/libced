# Generic Makefile for compiling a shared library.

UNAME := $(shell uname)

CC := clang
LIBNAME := ced
SRCDIR := src
BUILDDIR := build
CFLAGS := -g -Wall -fPIC -g
LIBS :=
TARGET := lib$(LIBNAME).so
LDFLAGS := -shared -Wl,-soname=$(TARGET)

# check if we're compiling on Darwin, as their linked doesn't
# support the "soname" switch. Need to change this conditionally
ifeq ($(UNAME), Darwin)
   LDFLAGS := -shared -Wl,-install_name,$(TARGET)
endif

SRCEXT = c
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
DEPS := $(OBJECTS:.o=.deps)

$(TARGET): $(OBJECTS)
	@echo " Linking..."; $(CC) $(LDFLAGS) $^ -o $(TARGET) $(LIBS)
	@mv $(TARGET) bin/$(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " CC $<"; $(CC) $(CFLAGS) -MD -MF $(@:.o=.deps) -c -o $@ $<

clean:
	@echo " Cleaning..."; $(RM) -r $(BUILDDIR) $(TARGET)

-include $(DEPS)

.PHONY: clean
