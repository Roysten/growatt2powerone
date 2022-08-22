#pragma once

#include "growatt.h"

namespace growatt
{

struct Cache
{
	static const unsigned long MAX_CACHE_AGE = 5000;

	bool update();

	Read_power_response power_data{};
	Read_energy_response energy_data{};
	unsigned long response_timestamp{};
};

bool Cache::update()
{
	static const unsigned long RESPONSE_TIMEOUT = 1000;
	static const unsigned long RETRY_INTERVAL = 1000;

	auto now = millis();
	if (now - response_timestamp > MAX_CACHE_AGE || response_timestamp == 0) {
		byte msg_buf[POWER_MSG_LEN] = {};
		growatt::clear_rx_buf();
		growatt::send_request(Read_cmd::READ_POWER);
		if (!growatt::recv_response(msg_buf, POWER_MSG_LEN, RESPONSE_TIMEOUT)) {
			return false;
		}

		if (!growatt::Read_power_response::from_bytes(power_data, msg_buf)) {
			Serial.println("E: chk power");
			return false;
		}

		growatt::clear_rx_buf();
		growatt::send_request(Read_cmd::READ_ENERGY);
		if (!growatt::recv_response(msg_buf, ENERGY_MSG_LEN, RESPONSE_TIMEOUT)) {
			return false;
		}
		if (!growatt::Read_energy_response::from_bytes(energy_data, msg_buf)) {
			Serial.println("E: chk energy");
			return false;
		}
		response_timestamp = now;
	}
	return true;
}

};
