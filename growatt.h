#pragma once

namespace growatt
{

static const byte ADDR = 0x01;
static const auto& serial = Serial1;
static const size_t POWER_MSG_LEN = 43;
static const size_t ENERGY_MSG_LEN = 29;
static const size_t SPEC_MSG_LEN = 39;
static const size_t SETTINGS_MSG_LEN = 27;
static const size_t SN_MSG_LEN = 18;

enum class Read_cmd : byte
{
	READ_POWER = 0x41,
	READ_ENERGY = 0x42,
	READ_SPEC = 0x43,
	READ_SETTINGS = 0x44,
	READ_SERIAL_NUMBER = 0x53,
};

enum class Inverter_status : byte
{
	WAITING = 0,
	NORMAL = 1,
	FAULT = 2,
};

static const byte* extract_big_endian(const byte* bytes, Inverter_status* field)
{
	*field = Inverter_status(bytes[0]);
	return bytes + 1;
}

template <typename T>
static const byte* extract_big_endian(const byte* bytes, T* field)
{
	auto byte_count = sizeof(*field);
	*field = 0;
	for (size_t i = 0; i < byte_count; ++i) {
		*field |= T(bytes[i]) << ((byte_count - 1 - i) * 8);
	}
	return bytes + byte_count;
}

static uint16_t calculate_checksum(const byte* data, size_t len)
{
	uint32_t sum = 0;
	for (size_t i = 0; i < len; ++i) {
		sum += data[i] ^ i;
	}

	if (sum == 0 || sum > 0xFFFF) {
		sum = 0xFFFF;
	}

	return sum;
}

static bool has_valid_checksum(const byte* data, size_t len) {
	if (len < 2) {
		return false;
	}

	uint16_t checksum = (data[len - 2] << 8) | data[len - 1];
	return checksum == calculate_checksum(data, len - 2);
}

struct Read_power_response
{
	Inverter_status inverter_status{};
	uint16_t input_voltage_tracker_1{}; /* Fixed point, 10 */
	uint16_t input_voltage_tracker_2{}; /* Fixed point, 10 */
	uint16_t input_power{}; /* Fixed point, 10 */
	uint16_t grid_voltage{}; /* Fixed point, 10 */
	uint16_t grid_amperage{}; /* Fixed point, 10 */
	uint16_t grid_frequency{}; /* Fixed point, 100 */
	uint16_t output_power{}; /* Fixed point, 10 */
	uint16_t isolation_fault_code{};
	uint16_t ground_fault_circuit_interrupter_fault_code{};
	uint16_t dc_current_injection_fault_code{};
	uint16_t input_voltage_fault_code{};
	uint16_t grid_voltage_fault_code{};
	uint16_t grid_frequency_fault_code{};
	uint16_t temperature_fault_code{};
	uint16_t fault_type{};
	uint16_t temperature{};

	static bool from_bytes(Read_power_response& dest, const byte* bytes)
	{
		if (!has_valid_checksum(bytes, POWER_MSG_LEN)) {
			return false;
		}

		bytes += 6;
		bytes = extract_big_endian(bytes, &dest.inverter_status);
		bytes = extract_big_endian(bytes, &dest.input_voltage_tracker_1);
		bytes = extract_big_endian(bytes, &dest.input_voltage_tracker_2);
		bytes = extract_big_endian(bytes, &dest.input_power);
		bytes = extract_big_endian(bytes, &dest.grid_voltage);
		bytes = extract_big_endian(bytes, &dest.grid_amperage);
		bytes = extract_big_endian(bytes, &dest.grid_frequency);
		bytes = extract_big_endian(bytes, &dest.output_power);
		bytes = extract_big_endian(bytes, &dest.isolation_fault_code);
		bytes = extract_big_endian(bytes, &dest.ground_fault_circuit_interrupter_fault_code);
		bytes = extract_big_endian(bytes, &dest.dc_current_injection_fault_code);
		bytes = extract_big_endian(bytes, &dest.input_voltage_fault_code);
		bytes = extract_big_endian(bytes, &dest.grid_voltage_fault_code);
		bytes = extract_big_endian(bytes, &dest.grid_frequency_fault_code);
		bytes = extract_big_endian(bytes, &dest.temperature_fault_code);
		bytes = extract_big_endian(bytes, &dest.fault_type);
		bytes = extract_big_endian(bytes, &dest.temperature);
		return true;
	}

	static void get_error_message(uint16_t fault_type, char* buf, size_t len)
	{
		switch(fault_type) {
			case 1 ... 23: snprintf(buf, len, "Error: %u", 100u + fault_type); break;
			case 24: snprintf(buf, len, "Auto Test Failed"); break;
			case 25: snprintf(buf, len, "No AC Connection"); break;
			case 26: snprintf(buf, len, "PV Isolation Low"); break;
			case 27: snprintf(buf, len, "Residual I High"); break;
			case 28: snprintf(buf, len, "Output High DCI"); break;
			case 29: snprintf(buf, len, "PV Voltage High"); break;
			case 30: snprintf(buf, len, "AC V Outrange"); break;
			case 31: snprintf(buf, len, "AC F Outrange"); break;
			case 32: snprintf(buf, len, "Module Hot"); break;
			default: snprintf(buf, len, "Unknown error");
		}
	}
};

struct Read_energy_response
{
	uint16_t energy_today{}; /* Fixed point, 10 */
	uint32_t energy_total{}; /* Fixed point, 10 */
	uint32_t time_total_hours{};

	static bool from_bytes(Read_energy_response& dest, const byte* bytes)
	{
		if (!has_valid_checksum(bytes, ENERGY_MSG_LEN)) {
			return false;
		}

		bytes += 6 + 7;
		bytes = extract_big_endian(bytes, &dest.energy_today);
		bytes = extract_big_endian(bytes, &dest.energy_total);
		bytes = extract_big_endian(bytes, &dest.time_total_hours);
		return true;
	}
};

struct Read_spec_response
{
	uint32_t p_max{}; /* Fixed point, 10 */
	uint16_t vdc_nor{}; /* Fixed point, 10 */
	uint16_t model{};
	uint8_t firmware_version{};

	static bool from_bytes(Read_spec_response& dest, const byte* bytes)
	{
		if (!has_valid_checksum(bytes, SPEC_MSG_LEN)) {
			return false;
		}

		bytes += 6 + 1;
		bytes = extract_big_endian(bytes, &dest.p_max);
		bytes = extract_big_endian(bytes, &dest.vdc_nor);
		bytes = extract_big_endian(bytes, &dest.model);
		bytes = extract_big_endian(bytes, &dest.firmware_version);
		return true;
	}
};

struct Read_settings_response
{
	uint8_t lcd_language{};
	uint8_t lcd_contrast{};
	uint16_t vpv_start{}; /* Fixed point, 100 */
	uint16_t time_start{};
	uint16_t vac_low{}; /* Fixed point, 100 */
	uint16_t vac_high{}; /* Fixed point, 100 */
	uint16_t fac_low{}; /* Fixed point, 100 */
	uint16_t fac_high{}; /* Fixed point, 100 */
	uint16_t model{};

	static bool from_bytes(Read_settings_response& dest, const byte* bytes)
	{
		if (!has_valid_checksum(bytes, SETTINGS_MSG_LEN)) {
			return false;
		}

		bytes += 6 + 1;
		bytes = extract_big_endian(bytes, &dest.lcd_language);
		bytes = extract_big_endian(bytes, &dest.lcd_contrast);
		bytes = extract_big_endian(bytes, &dest.vpv_start);
		bytes = extract_big_endian(bytes, &dest.time_start);
		bytes = extract_big_endian(bytes, &dest.vac_low);
		bytes = extract_big_endian(bytes, &dest.vac_high);
		bytes = extract_big_endian(bytes, &dest.fac_low);
		bytes = extract_big_endian(bytes, &dest.fac_high);
		bytes = extract_big_endian(bytes, &dest.model);

		return true;
	}
};

struct Serial_number
{
	static bool from_bytes(const byte* bytes, uint32_t *dest)
	{
		if (!has_valid_checksum(bytes, SN_MSG_LEN)) {
			return false;
		}

		extract_big_endian(bytes, dest);
		return true;
	}
};

void setup()
{
	serial.begin(9600);
}

constexpr byte get_data_len(Read_cmd cmd)
{
	switch (cmd) {
		case Read_cmd::READ_POWER: return 35;
		case Read_cmd::READ_ENERGY: return 21;
		case Read_cmd::READ_SPEC: return 31;
		case Read_cmd::READ_SETTINGS: return 19;
		case Read_cmd::READ_SERIAL_NUMBER: return 10;
	}
}

void clear_rx_buf() {
	while (serial.available()) {
		(void) serial.read();
	}
}

void send_request(Read_cmd cmd)
{
	static const auto PAYLOAD_LEN = 6u;
	static const auto CHECKSUM_LEN = 2u;
	byte cmd_buf[PAYLOAD_LEN + CHECKSUM_LEN] = {
		0x3F, 0x23, /* preamble */
		ADDR, /* COM port */
		0x32, /* Read request */
		byte(cmd), /* Command ID */
		0 /* Data length */
	};
	auto checksum = calculate_checksum(cmd_buf, PAYLOAD_LEN);
	cmd_buf[PAYLOAD_LEN] = (checksum >> 8);
	cmd_buf[PAYLOAD_LEN + 1] = checksum;

	serial.write(cmd_buf, sizeof(cmd_buf));
	serial.flush();
}

bool recv_response(byte* dest, size_t len, unsigned long timeout)
{
	static const byte preamble[] = {0x23, 0x3F, ADDR};

	auto t0 = millis();
	auto t_now = t0;
	auto bytes_received = 0u;
	for (; bytes_received < len; t_now = millis()) {
		if (t_now - t0 >= timeout) {
			serial.println("timeout");
			return false;
		}
		auto byte_read = serial.read();
		if (byte_read == -1) {
			continue;
		}
		if (bytes_received < sizeof(preamble)) {
			if (byte_read != preamble[bytes_received]) {
				serial.println("Invalid preamble");
				return false;
			}
		}

		dest[bytes_received] = byte_read;
		bytes_received += 1;
	}

	return true;
}

}

