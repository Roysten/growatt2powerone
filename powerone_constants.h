#pragma once

namespace powerone
{

enum Transmission_state : byte
{
	OK = 0,
	NOT_IMPLEMENTED = 51,
	VARIABLE_DOES_NOT_EXIST = 52,
	VARIABLE_OUT_OF_RANGE = 53,
	EEPROM_NOT_ACCESSIBLE = 54,
	NOT_TOGGLED_SERVICE_MODE = 55, 
	CANNOT_SEND_COMMAND_TO_INTERNAL_MICRO = 56,
	COMMAND_NOT_EXECUTED = 57,
	VARIABLE_NOT_AVAILABLE_RETRY = 58,
};

enum Read_cmd : byte
{
	STATE = 50,
	PN = 52,
	VERSION = 58,
	MEASURE_DSP = 59,
	SERIAL_NUMBER = 63,
	MANUFACTORING_DATE = 65,
	FLAGS = 67,
	CUMULATIVE_FLOAT_ENERGY = 68,
	TIME_DATE = 70,
	FIRMWARE_RELEASE = 72,
	AURORA_GRID_CUMULATIVE_ENERGY = 78,
	BAUD_RATE = 85,
	LAST_FOUR_ALARMS = 86,
	AURORA_CENTRAL_SYSTEM_INFO = 101,
	AURORA_CENTRAL_JUNCTION_BOX = 103,
	AURORA_CENTRAL_SYSTEM_PN = 105,
	AURORA_CENTRAL_SYSTEM_SERIAL_NUMBER = 107,
	JUNCTION_BOX_STATE = 200,
	JUNCTION_BOX_VAL = 201,
};

enum class Global_state : byte
{
	SENDING_PARAMETERS = 0,
	WAIT_SUN_GRID = 1,
	CHECKING_GRID = 2,
	MEASURING_RISO = 3,
	DCDC_START = 4,
	INVERTER_START = 5,
	RUN = 6,
	RECOVERY = 7,
	PAUSE = 8,
	GROUND_FAULT = 9,
	OTH_FAULT = 10,
	ADDRESS_SETTING = 11,
	SELF_TEST = 12,
	SELF_TEST_FAIL = 13,
	SENSOR_TEST_MEASURE_RISO = 14,
	LEAK_FAULT = 15,
	WAITING_FOR_MANUAL_RESET = 16,
	INTERNAL_ERROR_E026 = 17,
	INTERNAL_ERROR_E027 = 18,
	INTERNAL_ERROR_E028 = 19,
	INTERNAL_ERROR_E029 = 20,
	INTERNAL_ERROR_E030 = 21,
	SENDING_WIND_TABLE = 22,
	FAILED_SENDING_TABLE = 23,
	UTH_FAULT = 24,
	REMOTE_OFF = 25,
	INTERLOCK_FAIL = 26,
	EXECUTING_AUTOTEST = 27,
	WAITING_SUN = 30,
	TEMPERATURE_FAULT = 31,
	FAN_STAUCKED = 32,
	INTERNAL_COMMUNICATION_FAULT = 33,
	SLAVE_INSERTION = 34,
	DC_SWITCH_OPEN = 35,
	TRAS_SWITCH_OPEN = 36,
	MASTER_EXCLUSION = 37,
	AUTO_EXCLUSION = 38,
	ERASING_INTERNAL_EEPROM = 98,
	ERASING_EXTERNAL_EEPROM = 99,
	COUNTING_EEPROM = 100,
	FREEZE = 101,
};

enum class Dc_dc_state : byte
{
	OFF = 0,
	RAMP_START = 1,
	MPPT = 2,
	INPUT_OC = 4,
	INPUT_UV = 5,
	INPUT_OV = 6,
	INPUT_LOW = 7,
	NO_PARAMETERS = 8,
	BULK_OV = 9,
	COMMUNICATION_ERROR = 10,
	RAMP_FAIL = 11,
	INTERNAL_ERROR = 12,
	INPUT_MODE_ERROR = 13,
	GROUND_FAULT = 14,
	INVERTER_FAIL = 15,
	DCDC_IGBT_SAT = 16,
	DCDC_ILEAK_FAIL = 17,
	DCDC_GRID_FAIL = 18,
	DCDC_COMMUNICATION_ERROR = 19,
};

enum class Inverter_state : byte
{
	STANDBY = 0,
	CHECKING_GRID = 1,
	RUN = 2,
	BULK_OV = 3,
	OUT_OC = 4,
	IGBT_SAT = 5,
	BULK_UV = 6,
	DEGAUSS_ERROR = 7,
	NO_PARAMETERS = 8,
	BULK_LOW = 9,
	GRID_OV = 10,
	COMMUNICATION_ERROR = 11,
	DEGAUSSING = 12,
	STARTING = 13,
	BULK_CAP_FAIL = 14,
	LEAK_FAIL = 15,
	DCDC_FAIL = 16,
	ILEAK_SENSOR_FAIL = 17,
	SELF_TEST_RELAY_INVERTERY = 18,
	SELF_TEST_WAIT_FOR_SENSOR_TEST = 19,
	SELF_TEST_TEST_RELAY_DCDC_SENSOR = 20,
	SELF_TEST_RELAY_INVERTER_FAIL = 21,
	SELF_TEST_TIMEOUT_FAIL = 22,
	SELF_TEST_RELAY_DCDC_FAIL = 23,
	SELF_TEST_1 = 24,
	WAITING_SELF_TEST_START = 25,
	DC_INJECTION = 26,
	SELF_TEST_2 = 27,
	SELF_TEST_3 = 28,
	SELF_TEST_4 = 29,
	INTERNAL_ERROR_A = 30,
	INTERNAL_ERROR_B = 31,
	FORBIDDEN_STATE = 40,
	INPUT_UC = 41,
	ZERO_POWER = 42,
	GRID_NOT_PRESENT = 43,
	WAITING_START = 44,
	MPPT = 45,
	GRID_FAIL = 46,
	INPUT_OC = 47,
};

enum class Alarm_state : byte
{
	NO_ALARM = 0,
	SUN_LOW_W001 = 1,
	INPUT_OC_E001 = 2,
	INPUT_UV_W002 = 3,
	INPUT_OV_E002 = 4,
	SUN_LOW_W001_2 = 5,
	NO_PARAMETERS_E003 = 6,
	BULK_OV_E004 = 7,
	COMM_ERROR_E005 = 8,
	OUTPUT_OC_E006 = 9,
	IGBT_SAT_E007 = 10,
	BULK_UV_W011 = 11,
	INTERNAL_ERROR_E009 = 12,
	GRID_FAIL_W003 = 13,
	BULK_LOW_E010 = 14,
	RAMP_FAIL_E011 = 15,
	DCDC_FAIL_E012 = 16,
	WRONG_MODE_E013 = 17,
	GROUND_FAULT = 18,
	OVER_TEMP_E014 = 19,
	BULK_CAP_FAIL_E015 = 20,
	INVERTER_FAIL_E016 = 21,
	START_TIMEOUT_E017 = 22,
	GROUND_FAULT_E018 = 23,
	DEGAUSS_ERROR = 24,
	ILEAK_SENS_FAIL_E019 = 25,
	DCDC_FAIL_E012_2 = 26,
	SELF_TEST_ERROR_1_E020 = 27,
	SELF_TEST_ERROR_2_E021 = 28,
	SELF_TEST_ERROR_3_E019 = 29,
	SELF_TEST_ERROR_4_E022 = 30,
	DC_INJ_ERROR_E023 = 31,
	GRID_OV_W004 = 32,
	GRID_UV_W005 = 33,
	GRID_OF_W006 = 34,
	GRID_UF_W007 = 35,
	Z_GRID_HI_W008 = 36,
	INTERNAL_ERROR_E024 = 37,
	RISO_LOW_E025 = 38,
	VREF_ERROR_E026 = 39,
	ERROR_MEAS_V_E027 = 40,
	ERROR_MEAS_F_E028 = 41,
	ERROR_MEAS_Z_E029 = 42,
	ERROR_MEAS_ILEAK_E030 = 43,
	ERROR_READ_V_E031 = 44,
	ERROR_READ_I_E032 = 45,
	TABLE_FAIL_W009 = 46,
	FAN_FAIL_W010 = 47,
	UTH_E033 = 48,
	INTERLOCK_FAIL_E034 = 49,
	REMOTE_OFF_E035 = 50,
	VOUT_AVG_ERRROR_E036 = 51,
	BATTERY_LOW_W012 = 52,
	CLK_FAIL_W013 = 53,
	INPUT_UC_E037 = 54,
	ZERO_POWER_W014 = 55,
	FAN_STUCKED_E038 = 56,
	DC_SWITCH_OPEN_E039 = 57,
	TRAS_SWITCH_OPEN_E040 = 58,
	AC_SWITCH_OPEN_E041 = 59,
	BULK_UV_E042 = 60,
	AUTOEXCLUSION_E043 = 61,
	GRID_DF_DT_W015 = 62,
	DEN_SWITCH_OPEN_W016 = 63,
	JBOX_FAIL_W017 = 64,
};

enum class Measure_dsp_type : byte
{
	GRID_VOLTAGE = 1,
	GRID_CURRENT = 2,
	GRID_POWER = 3,
	FREQUENCY = 4,
	VBULK = 5,
	ILEAK_DCDC = 6,
	ILEAK_INVERTER = 7,
	PIN_1 = 8,
	PIN_2 = 9,
	INVERTER_TEMPERATURE = 21,
	BOOSTER_TEMPERATURE = 22,
	INPUT1_VOLTAGE = 23,
	INPUT1_CURRENT = 25,
	INPUT2_VOLTAGE = 26,
	INPUT2_CURRENT = 27,
	GRID_VOLTAGE_DCDC = 28,
	GRID_FREQUENCY = 29,
	ISOLATION_RESISTANCE = 30,
	VBULK_DCDC = 31,
	AVERAGE_GRID_VOLTAGE = 32,
	VBULK_MID = 33,
	POWER_PEAK = 34,
	POWER_PEAK_TODAY = 35,
	GRID_VOLTAGE_NEUTRAL = 36,
	WIND_GENERATOR_FREQUENCY = 37,
	GRID_VOLTAGE_NEUTRAL_PHASE = 38,
	GRID_CURRENT_PHASE_R = 39,
	GRID_CURRENT_PHASE_S = 40,
	GRID_CURRENT_PHASE_T = 41,
	FREQUENCY_PHASE_R = 42,
	FREQUENCY_PHASE_S = 43,
	FREQUENCY_PHASE_T = 44,
	VBULK_PLUS = 45,
	VBULK_MINUS = 46,
	SUPERVISOR_TEMPERATURE = 47,
	ALIM_TEMPERATURE = 48,
	HEAT_SINK_TEMPERATURE = 49,
	TEMPERATURE1 = 50,
	TEMPERATURE2 = 51,
	TEMPERATURE3 = 52,
	FAN1_SPEED = 53,
	FAN2_SPEED = 54,
	FAN3_SPEED = 55,
	FAN4_SPEED = 56,
	FAN5_SPEED = 57,
	POWER_SATURATION_LIMIT = 58,
	RIFERAMENTO_ANELLO_BULK = 59,
	VPANEL_MICRO = 60,
	GRID_VOLTAGE_PHASE_R = 61,
	GRID_VOLTAGE_PHASE_S = 62,
	GRID_VOLTAGE_PHASE_T = 63,
};

enum class Cumulative_energy_read_type : byte {
	DAY = 0,
	WEEK = 1,
	MONTH = 3,
	YEAR = 4,
	TOTAL = 5,
	PARTIAL = 6,
};

Measure_dsp_type measure_dsp_type_from_byte(byte val) {
	switch(val) {
		case byte(Measure_dsp_type::GRID_VOLTAGE):
			return Measure_dsp_type::GRID_VOLTAGE;
		case byte(Measure_dsp_type::GRID_CURRENT):
			return Measure_dsp_type::GRID_CURRENT;
		case byte(Measure_dsp_type::GRID_POWER):
			return Measure_dsp_type::GRID_POWER;
		case byte(Measure_dsp_type::FREQUENCY):
			return Measure_dsp_type::FREQUENCY;
		case byte(Measure_dsp_type::VBULK):
			return Measure_dsp_type::VBULK;
		case byte(Measure_dsp_type::ILEAK_DCDC):
			return Measure_dsp_type::ILEAK_DCDC;
		case byte(Measure_dsp_type::ILEAK_INVERTER):
			return Measure_dsp_type::ILEAK_INVERTER;
		case byte(Measure_dsp_type::PIN_1):
			return Measure_dsp_type::PIN_1;
		case byte(Measure_dsp_type::PIN_2):
			return Measure_dsp_type::PIN_2;
		case byte(Measure_dsp_type::INVERTER_TEMPERATURE):
			return Measure_dsp_type::INVERTER_TEMPERATURE;
		case byte(Measure_dsp_type::BOOSTER_TEMPERATURE):
			return Measure_dsp_type::BOOSTER_TEMPERATURE;
		case byte(Measure_dsp_type::INPUT1_VOLTAGE):
			return Measure_dsp_type::INPUT1_VOLTAGE;
		case byte(Measure_dsp_type::INPUT1_CURRENT):
			return Measure_dsp_type::INPUT1_CURRENT;
		case byte(Measure_dsp_type::INPUT2_VOLTAGE):
			return Measure_dsp_type::INPUT2_VOLTAGE;
		case byte(Measure_dsp_type::INPUT2_CURRENT):
			return Measure_dsp_type::INPUT2_CURRENT;
		case byte(Measure_dsp_type::GRID_VOLTAGE_DCDC):
			return Measure_dsp_type::GRID_VOLTAGE_DCDC;
		case byte(Measure_dsp_type::GRID_FREQUENCY):
			return Measure_dsp_type::GRID_FREQUENCY;
		case byte(Measure_dsp_type::ISOLATION_RESISTANCE):
			return Measure_dsp_type::ISOLATION_RESISTANCE;
		case byte(Measure_dsp_type::VBULK_DCDC):
			return Measure_dsp_type::VBULK_DCDC;
		case byte(Measure_dsp_type::AVERAGE_GRID_VOLTAGE):
			return Measure_dsp_type::AVERAGE_GRID_VOLTAGE;
		case byte(Measure_dsp_type::VBULK_MID):
			return Measure_dsp_type::VBULK_MID;
		case byte(Measure_dsp_type::POWER_PEAK):
			return Measure_dsp_type::POWER_PEAK;
		case byte(Measure_dsp_type::POWER_PEAK_TODAY):
			return Measure_dsp_type::POWER_PEAK_TODAY;
		case byte(Measure_dsp_type::GRID_VOLTAGE_NEUTRAL):
			return Measure_dsp_type::GRID_VOLTAGE_NEUTRAL;
		case byte(Measure_dsp_type::WIND_GENERATOR_FREQUENCY):
			return Measure_dsp_type::WIND_GENERATOR_FREQUENCY;
		case byte(Measure_dsp_type::GRID_VOLTAGE_NEUTRAL_PHASE):
			return Measure_dsp_type::GRID_VOLTAGE_NEUTRAL_PHASE;
		case byte(Measure_dsp_type::GRID_CURRENT_PHASE_R):
			return Measure_dsp_type::GRID_CURRENT_PHASE_R;
		case byte(Measure_dsp_type::GRID_CURRENT_PHASE_S):
			return Measure_dsp_type::GRID_CURRENT_PHASE_S;
		case byte(Measure_dsp_type::GRID_CURRENT_PHASE_T):
			return Measure_dsp_type::GRID_CURRENT_PHASE_T;
		case byte(Measure_dsp_type::FREQUENCY_PHASE_R):
			return Measure_dsp_type::FREQUENCY_PHASE_R;
		case byte(Measure_dsp_type::FREQUENCY_PHASE_S):
			return Measure_dsp_type::FREQUENCY_PHASE_S;
		case byte(Measure_dsp_type::FREQUENCY_PHASE_T):
			return Measure_dsp_type::FREQUENCY_PHASE_T;
		case byte(Measure_dsp_type::VBULK_PLUS):
			return Measure_dsp_type::VBULK_PLUS;
		case byte(Measure_dsp_type::VBULK_MINUS):
			return Measure_dsp_type::VBULK_MINUS;
		case byte(Measure_dsp_type::SUPERVISOR_TEMPERATURE):
			return Measure_dsp_type::SUPERVISOR_TEMPERATURE;
		case byte(Measure_dsp_type::ALIM_TEMPERATURE):
			return Measure_dsp_type::ALIM_TEMPERATURE;
		case byte(Measure_dsp_type::HEAT_SINK_TEMPERATURE):
			return Measure_dsp_type::HEAT_SINK_TEMPERATURE;
		case byte(Measure_dsp_type::TEMPERATURE1):
			return Measure_dsp_type::TEMPERATURE1;
		case byte(Measure_dsp_type::TEMPERATURE2):
			return Measure_dsp_type::TEMPERATURE2;
		case byte(Measure_dsp_type::TEMPERATURE3):
			return Measure_dsp_type::TEMPERATURE3;
		case byte(Measure_dsp_type::FAN1_SPEED):
			return Measure_dsp_type::FAN1_SPEED;
		case byte(Measure_dsp_type::FAN2_SPEED):
			return Measure_dsp_type::FAN2_SPEED;
		case byte(Measure_dsp_type::FAN3_SPEED):
			return Measure_dsp_type::FAN3_SPEED;
		case byte(Measure_dsp_type::FAN4_SPEED):
			return Measure_dsp_type::FAN4_SPEED;
		case byte(Measure_dsp_type::FAN5_SPEED):
			return Measure_dsp_type::FAN5_SPEED;
		case byte(Measure_dsp_type::POWER_SATURATION_LIMIT):
			return Measure_dsp_type::POWER_SATURATION_LIMIT;
		case byte(Measure_dsp_type::RIFERAMENTO_ANELLO_BULK):
			return Measure_dsp_type::RIFERAMENTO_ANELLO_BULK;
		case byte(Measure_dsp_type::VPANEL_MICRO):
			return Measure_dsp_type::VPANEL_MICRO;
		case byte(Measure_dsp_type::GRID_VOLTAGE_PHASE_R):
			return Measure_dsp_type::GRID_VOLTAGE_PHASE_R;
		case byte(Measure_dsp_type::GRID_VOLTAGE_PHASE_S):
			return Measure_dsp_type::GRID_VOLTAGE_PHASE_S;
		case byte(Measure_dsp_type::GRID_VOLTAGE_PHASE_T):
			return Measure_dsp_type::GRID_VOLTAGE_PHASE_T;
	}
}

const char* to_string(Read_cmd cmd)
{
	switch(cmd) {
		case Read_cmd::STATE:
			return "STATE";
		case Read_cmd::PN:
			return "PN";
		case VERSION:
			return "VERSION";
		case MEASURE_DSP:
			return "MEASURE_DSP";
		case SERIAL_NUMBER:
			return "SERIAL_NUMBER";
		case MANUFACTORING_DATE:
			return "MANUFACTORING_DATE";
		case FLAGS:
			return "FLAGS";
		case CUMULATIVE_FLOAT_ENERGY:
			return "CUMULATIVE_FLOAT_ENERGY";
		case TIME_DATE:
			return "TIME_DATE";
		case FIRMWARE_RELEASE:
			return "FIRMWARE_RELEASE";
		case AURORA_GRID_CUMULATIVE_ENERGY:
			return "AURORA_GRID_CUMULATIVE_ENERGY";
		case BAUD_RATE:
			return "BAUD_RATE";
		case LAST_FOUR_ALARMS:
			return "LAST_FOUR_ALARMS";
		case AURORA_CENTRAL_SYSTEM_INFO:
			return "AURORA_CENTRAL_SYSTEM_INFO ";
		case AURORA_CENTRAL_JUNCTION_BOX:
			return "AURORA_CENTRAL_JUNCTION_BOX ";
		case AURORA_CENTRAL_SYSTEM_PN:
			return "AURORA_CENTRAL_SYSTEM_PN ";
		case AURORA_CENTRAL_SYSTEM_SERIAL_NUMBER:
			return "AURORA_CENTRAL_SYSTEM_SERIAL_NUMBER ";
		case JUNCTION_BOX_STATE:
			return "JUNCTION_BOX_STATE ";
		case JUNCTION_BOX_VAL:
			return "JUNCTION_BOX_VAL ";
	}
	return "UNKNOWN";
}

Cumulative_energy_read_type cumulative_energy_read_type_from_byte(byte val) {
	switch (val) {
		case byte(Cumulative_energy_read_type::DAY):
			return Cumulative_energy_read_type::DAY;
		case byte(Cumulative_energy_read_type::WEEK):
			return Cumulative_energy_read_type::WEEK;
		case byte(Cumulative_energy_read_type::MONTH):
			return Cumulative_energy_read_type::MONTH;
		case byte(Cumulative_energy_read_type::YEAR):
			return Cumulative_energy_read_type::YEAR;
		case byte(Cumulative_energy_read_type::TOTAL):
			return Cumulative_energy_read_type::TOTAL;
		case byte(Cumulative_energy_read_type::PARTIAL):
			return Cumulative_energy_read_type::PARTIAL;
	}
}

}

