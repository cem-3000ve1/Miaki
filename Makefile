VITASDK ?= /usr/local/vitasdk
PATH := $(VITASDK)/bin:$(PATH)

all: build_all move_plugins build_final_app

build_all:
	cd kernel && cmake . && make install
	cd spoofer_vita/TOOL && make clean && make
	cd spoofer_vita/TEST && make clean && make
	cd spoofer_vita && make clean && make
	cd user && cmake . && make install
	cd devmode && cmake . && make install
	cd kmspico/src/yellowmsg && cmake . && make install
	cd kmspico/src/lowact && cmake . && make install
	cd kmspico/src/kms && cmake . && make install
	cd kmspico && cmake . && make install

move_plugins:
	cd app && \
	mv ../kmspico/src/lowact/lowact.skprx lowkmspico.skprx && \
	mv ../kmspico/src/yellowmsg/yellowmsg.skprx ykmspico.skprx && \
	mv ../kmspico/src/kms/kmspico.skprx kmspico.skprx && \
	mv ../kmspico/dkmspico.skprx dkmspico.skprx && \
	mv ../spoofer_vita/TOOL/kDump.skprx dev_vita.skprx && \
	mv ../spoofer_vita/TEST/kDump.skprx pro_vita.skprx && \
	mv ../spoofer_vita/kDump.skprx testkit_vita.skprx && \
	mv ../devmode/devmode.skprx devmode.skprx && \
	mv ../kernel/kernel.skprx kernel.skprx && \
	mv ../user/user.suprx user.suprx

build_final_app:
	cd app && cmake . && make

clean:
	cd kernel && make clean || true
	cd spoofer_vita && make clean || true
	cd spoofer_vita/TOOL && make clean || true
	cd spoofer_vita/TEST && make clean || true
	cd user && make clean || true
	cd devmode && make clean || true
	cd kmspico/src/yellowmsg && make clean || true
	cd kmspico/src/lowact && make clean || true
	cd kmspico && make clean || true
	cd app && make clean || true
