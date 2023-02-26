#pragma once

#include "growatt.h"
#include "powerone_constants.h"
#include "util.h"

namespace powerone
{

static const byte ADDR = 0x03;
static const size_t PAYLOAD_LEN = 8;
static const size_t CHECKSUM_LEN = 2;
static const size_t MSG_LEN = PAYLOAD_LEN + CHECKSUM_LEN;
static const size_t RESPONSE_PAYLOAD_LEN = 6;
static const size_t RESPONSE_MSG_LEN = RESPONSE_PAYLOAD_LEN + CHECKSUM_LEN;
static const byte OFFSET_MSG_TYPE = 1;

static const auto& serial = Serial2;

void setup()
{
	serial.begin(19200);
	pinMode(A7, OUTPUT);
	digitalWrite(A7, LOW);
}

uint16_t calculate_checksum(byte* data, size_t len)
{
	byte bcc_lo = 0xFF;
	byte bcc_hi = 0xFF;
	for (size_t i = 0; i < len; ++i) {
		byte vnew = data[i] ^ bcc_lo;
		byte tmp = vnew << 4;
		vnew = tmp ^ vnew;
		tmp = vnew >> 5;
		bcc_lo = bcc_hi;
		bcc_hi = vnew ^ tmp;
		tmp = vnew << 3;
		bcc_lo = bcc_lo ^ tmp;
		tmp = vnew >> 4;
		bcc_lo = bcc_lo ^ tmp;
	}

	return ((~bcc_hi) << 8) | byte(~bcc_lo);
}

void clear_rx_buf() {
	while (serial.available()) {
		(void) serial.read();
	}
}

bool recv_request(byte* dest)
{
	clear_rx_buf();
	size_t bytes_received = 0;
	while (bytes_received < MSG_LEN) {
		auto byte_read = serial.read();
		if (byte_read == -1) {
			continue;
		}

		if (bytes_received == 0 && byte_read != ADDR) {
			// We are only interested in requests addressed to
			// ourselves. Ignoring all incoming data until we
			// see our own address simplifies the detection of
			// the start of a message.
			continue;
		}

		dest[bytes_received] = byte_read;
		bytes_received += 1;
	}
	uint16_t received_checksum = (dest[PAYLOAD_LEN + 1] << 8) | dest[PAYLOAD_LEN];
	uint16_t calculated_checksum = calculate_checksum(dest, PAYLOAD_LEN);
	return calculated_checksum == received_checksum;
}

Global_state get_global_state(const growatt::Read_power_response& growatt_power_data)
{
	switch (growatt_power_data.inverter_status) {
		case growatt::Inverter_status::WAITING:
			return Global_state::WAIT_SUN_GRID;
		case growatt::Inverter_status::NORMAL:
			return Global_state::RUN;
		case growatt::Inverter_status::FAULT:
			return Global_state::INTERNAL_ERROR_E026;
		default:
			return Global_state::WAIT_SUN_GRID;
	}
}

void send_response(byte* msg_buf)
{
	auto checksum = calculate_checksum(msg_buf, RESPONSE_PAYLOAD_LEN);
	msg_buf[RESPONSE_PAYLOAD_LEN] = checksum;
	msg_buf[RESPONSE_PAYLOAD_LEN + 1] = checksum >> 8;
	digitalWrite(A7, HIGH);
	serial.write(msg_buf, RESPONSE_MSG_LEN);
	serial.flush();
	digitalWrite(A7, LOW);
}

void send_state_response(const growatt::Read_power_response& growatt_power_data)
{
	TRACE_FN();

	Dc_dc_state dcdc1_state{};
	Dc_dc_state dcdc2_state{};
	Inverter_state inverter_state{};
	Alarm_state alarm_state{};

	switch (growatt_power_data.inverter_status) {
		case growatt::Inverter_status::WAITING:
			dcdc1_state = Dc_dc_state::OFF;
			dcdc2_state = Dc_dc_state::OFF;
			inverter_state = Inverter_state::STANDBY;
			alarm_state = Alarm_state::NO_ALARM;
			break;
		case growatt::Inverter_status::NORMAL:
			dcdc1_state = Dc_dc_state::MPPT;
			dcdc2_state = Dc_dc_state::OFF;
			inverter_state = Inverter_state::RUN;
			alarm_state = Alarm_state::NO_ALARM;
			break;
		case growatt::Inverter_status::FAULT:
			dcdc1_state = Dc_dc_state::INVERTER_FAIL;
			dcdc2_state = Dc_dc_state::OFF;
			inverter_state = Inverter_state::INTERNAL_ERROR_A;
			alarm_state = Alarm_state::INTERNAL_ERROR_E009;
			break;
	}

	byte msg_buf[RESPONSE_MSG_LEN] = {
		Transmission_state::OK,
		byte(get_global_state(growatt_power_data)),
		byte(inverter_state),
		byte(dcdc1_state),
		byte(dcdc2_state),
		byte(alarm_state),
	};
	send_response(msg_buf);
}

void send_version_response(const growatt::Read_power_response& growatt_power_data)
{
	TRACE_FN();

	byte msg_buf[RESPONSE_MSG_LEN] = {
		Transmission_state::OK,
		byte(get_global_state(growatt_power_data)),
		byte('4'),
		byte('E'),
		byte('T'),
		byte('N'),
	};
	send_response(msg_buf);
}

void send_measure_dsp_response(Measure_dsp_type type, const growatt::Read_power_response& growatt_power_data)
{
	TRACE_FN();

	float val = 0.0;
	switch(type) {
		case Measure_dsp_type::GRID_VOLTAGE:
		case Measure_dsp_type::GRID_VOLTAGE_DCDC:
			val = growatt_power_data.grid_voltage / 10.0;
			break;
		case Measure_dsp_type::GRID_CURRENT:
			val = growatt_power_data.grid_amperage / 10.0;
			break;
		case Measure_dsp_type::FREQUENCY:
		case Measure_dsp_type::GRID_FREQUENCY:
			val = growatt_power_data.grid_frequency / 100.0;
			break;
		case Measure_dsp_type::INVERTER_TEMPERATURE:
			val = growatt_power_data.temperature / 10.0;
			break;
		case Measure_dsp_type::INPUT1_VOLTAGE:
			val = growatt_power_data.input_voltage_tracker_1;
			break;
		case Measure_dsp_type::INPUT2_VOLTAGE:
			val = growatt_power_data.input_voltage_tracker_2;
			break;
		case Measure_dsp_type::PIN_1:
		case Measure_dsp_type::PIN_2:
			val = growatt_power_data.output_power / 10.0;
			break;
		case Measure_dsp_type::GRID_POWER:
		case Measure_dsp_type::VBULK:
		case Measure_dsp_type::ILEAK_DCDC:
		case Measure_dsp_type::ILEAK_INVERTER:
		case Measure_dsp_type::BOOSTER_TEMPERATURE:
		case Measure_dsp_type::INPUT1_CURRENT:
		case Measure_dsp_type::INPUT2_CURRENT:
		case Measure_dsp_type::ISOLATION_RESISTANCE:
		case Measure_dsp_type::VBULK_DCDC:
		case Measure_dsp_type::AVERAGE_GRID_VOLTAGE:
		case Measure_dsp_type::VBULK_MID:
		case Measure_dsp_type::POWER_PEAK:
		case Measure_dsp_type::POWER_PEAK_TODAY:
		case Measure_dsp_type::GRID_VOLTAGE_NEUTRAL:
		case Measure_dsp_type::WIND_GENERATOR_FREQUENCY:
		case Measure_dsp_type::GRID_VOLTAGE_NEUTRAL_PHASE:
		case Measure_dsp_type::GRID_CURRENT_PHASE_R:
		case Measure_dsp_type::GRID_CURRENT_PHASE_S:
		case Measure_dsp_type::GRID_CURRENT_PHASE_T:
		case Measure_dsp_type::FREQUENCY_PHASE_R:
		case Measure_dsp_type::FREQUENCY_PHASE_S:
		case Measure_dsp_type::FREQUENCY_PHASE_T:
		case Measure_dsp_type::VBULK_PLUS:
		case Measure_dsp_type::VBULK_MINUS:
		case Measure_dsp_type::SUPERVISOR_TEMPERATURE:
		case Measure_dsp_type::ALIM_TEMPERATURE:
		case Measure_dsp_type::HEAT_SINK_TEMPERATURE:
		case Measure_dsp_type::TEMPERATURE1:
		case Measure_dsp_type::TEMPERATURE2:
		case Measure_dsp_type::TEMPERATURE3:
		case Measure_dsp_type::FAN1_SPEED:
		case Measure_dsp_type::FAN2_SPEED:
		case Measure_dsp_type::FAN3_SPEED:
		case Measure_dsp_type::FAN4_SPEED:
		case Measure_dsp_type::FAN5_SPEED:
		case Measure_dsp_type::POWER_SATURATION_LIMIT:
		case Measure_dsp_type::RIFERAMENTO_ANELLO_BULK:
		case Measure_dsp_type::VPANEL_MICRO:
		case Measure_dsp_type::GRID_VOLTAGE_PHASE_R:
		case Measure_dsp_type::GRID_VOLTAGE_PHASE_S:
		case Measure_dsp_type::GRID_VOLTAGE_PHASE_T:
			// ???
			break;
	}

	auto val_ptr = reinterpret_cast<byte*>(&val);
	byte msg_buf[RESPONSE_MSG_LEN] = {
		Transmission_state::OK,
		byte(get_global_state(growatt_power_data)),
		val_ptr[3],
		val_ptr[2],
		val_ptr[1],
		val_ptr[0],
	};
	send_response(msg_buf);
}

void send_cumulative_energy_response(Cumulative_energy_read_type type,
		const growatt::Read_power_response& growatt_power_data,
		const growatt::Read_energy_response& growatt_energy_data)
{
	TRACE_FN();

	// Growatt uses fixed point kWh, but PowerOne expects Wh floats
	float val = growatt_energy_data.energy_total * 100.0;
	auto val_ptr = reinterpret_cast<byte*>(&val);
	byte msg_buf[RESPONSE_MSG_LEN] = {
		Transmission_state::OK,
		byte(get_global_state(growatt_power_data)),
		val_ptr[3],
		val_ptr[2],
		val_ptr[1],
		val_ptr[0],
	};
	send_response(msg_buf);
}

void send_serial_number_response(const growatt::Read_power_response& growatt_power_data)
{
	TRACE_FN();

	byte msg_buf[RESPONSE_MSG_LEN] = {
		Transmission_state::OK,
		byte(get_global_state(growatt_power_data)),
		'6', '5', '4', '3', '2', '1',
	};
	send_response(msg_buf);
}

void send_empty_response(const growatt::Read_power_response& growatt_power_data)
{
	TRACE_FN();

	byte msg_buf[RESPONSE_MSG_LEN] = {
		Transmission_state::OK,
		byte(get_global_state(growatt_power_data)),
	};
	send_response(msg_buf);
}

}
