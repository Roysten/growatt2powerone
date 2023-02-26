CPPFLAGS += --std=c++17

ifeq ($(trace), 1)
	CPPFLAGS += -DTRACE -Wall -Wextra -Wpedantic
endif

build:
	arduino-cli compile --build-property compiler.cpp.extra_flags="$(CPPFLAGS)" --fqbn arduino:avr:mega .

upload:
	arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:mega .

monitor:
	arduino-cli monitor -p /dev/ttyACM0
