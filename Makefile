CPPFLAGS += --std=c++17

ifeq ($(trace), 1)
	CPPFLAGS += -DTRACE -Wall -Wextra
endif

build:
	../arduino-cli compile --build-property compiler.cpp.extra_flags="$(CPPFLAGS)" --fqbn arduino:avr:mega growatt2powerone

upload:
	../arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:mega growatt2powerone

monitor:
	../arduino-cli monitor -p /dev/ttyACM0
