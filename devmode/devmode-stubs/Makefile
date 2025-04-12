ifdef VITASDK
PREFIX = $(VITASDK)/bin/
endif

ARCH ?= $(PREFIX)arm-vita-eabi
AS = $(ARCH)-as
AR = $(ARCH)-ar
RANLIB = $(ARCH)-ranlib

TARGETS = libdevmode_stub.a
TARGETS_WEAK = libdevmode_stub_weak.a

devmode_OBJS =
devmode_weak_OBJS =
SceKernel_OBJS =
ALL_OBJS=

all: $(TARGETS) $(TARGETS_WEAK)

define LIBRARY_template
 $(1): $$($(1:lib%_stub.a=%)_OBJS)
 ALL_OBJS += $$($(1:lib%_stub.a=%)_OBJS)
endef
define LIBRARY_WEAK_template
 $(1): $$($(1:lib%_stub_weak.a=%)_weak_OBJS)
 ALL_OBJS += $$($(1:lib%_stub_weak.a=%)_weak_OBJS)
endef

$(foreach library,$(TARGETS),$(eval $(call LIBRARY_template,$(library))))
$(foreach library,$(TARGETS_WEAK),$(eval $(call LIBRARY_WEAK_template,$(library))))

install: $(TARGETS) $(TARGETS_WEAK)
	cp $(TARGETS) $(VITASDK)/arm-vita-eabi/lib
	cp $(TARGETS_WEAK) $(VITASDK)/arm-vita-eabi/lib

clean:
	rm -f $(TARGETS) $(TARGETS_WEAK) $(ALL_OBJS)

$(TARGETS) $(TARGETS_WEAK):
	@echo "$?" > $@-objs
	$(AR) cru $@ @$@-objs
	$(RANLIB) $@

%.o: %.S
	$(AS) --defsym GEN_WEAK_EXPORTS=0 $< -o $@

%.wo: %.S
	$(AS) --defsym GEN_WEAK_EXPORTS=1 $< -o $@
