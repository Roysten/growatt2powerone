#include "growatt.h"
#include "growatt_cache.h"
#include "powerone.h"
#include "powerone_constants.h"

growatt::Cache growatt_cache{};

void setup()
{
	Serial.begin(9600);
	growatt::setup();
	powerone::setup();
}

void loop() {
	byte msg_buf[powerone::MSG_LEN] = {};
	auto msg_ok = powerone::recv_request(msg_buf);
	if (!msg_ok) {
		return;
	}

	if (!growatt_cache.update()) {
		Serial.println("Growatt error");
		return;
	}

	auto request_type = msg_buf[powerone::OFFSET_MSG_TYPE];
	Serial.print("Request type: ");
	Serial.println(powerone::to_string(request_type));
	switch (request_type) {
		case powerone::Read_cmd::STATE:
			powerone::send_state_response(growatt_cache.power_data);
			break;
		case powerone::Read_cmd::SERIAL_NUMBER:
			powerone::send_serial_number_response(growatt_cache.power_data);
			break;
		case powerone::Read_cmd::PN:
		case powerone::Read_cmd::MANUFACTORING_DATE:
			powerone::send_empty_response(growatt_cache.power_data);
			break;
		case powerone::Read_cmd::VERSION:
			powerone::send_version_response(growatt_cache.power_data);
			break;
		case powerone::Read_cmd::MEASURE_DSP:
			powerone::send_measure_dsp_response(
				powerone::measure_dsp_type_from_byte(msg_buf[2]),
				growatt_cache.power_data
			);
			break;
		case powerone::Read_cmd::AURORA_GRID_CUMULATIVE_ENERGY:
			powerone::send_cumulative_energy_response(
				powerone::cumulative_energy_read_type_from_byte(msg_buf[2]),
				growatt_cache.power_data,
				growatt_cache.energy_data
			);
			break;
		case powerone::Read_cmd::FLAGS:
		case powerone::Read_cmd::CUMULATIVE_FLOAT_ENERGY:
		case powerone::Read_cmd::TIME_DATE:
		case powerone::Read_cmd::FIRMWARE_RELEASE:
		case powerone::Read_cmd::BAUD_RATE:
		case powerone::Read_cmd::LAST_FOUR_ALARMS:
		case powerone::Read_cmd::AURORA_CENTRAL_SYSTEM_INFO:
		case powerone::Read_cmd::AURORA_CENTRAL_JUNCTION_BOX:
		case powerone::Read_cmd::AURORA_CENTRAL_SYSTEM_PN:
		case powerone::Read_cmd::AURORA_CENTRAL_SYSTEM_SERIAL_NUMBER:
		case powerone::Read_cmd::JUNCTION_BOX_STATE:
		case powerone::Read_cmd::JUNCTION_BOX_VAL:
			Serial.println("Not implemented");
			break;
		default:
			Serial.println("Got unknown command");
	}
}

