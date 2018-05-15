#include "WAVConfiguration.h"

WAVConfiguration::WAVConfiguration(Reader &reader) {
	char *c_name = reader.read_rsdk_string();
	name = std::string(c_name);
	delete c_name;
	max_concurrent_play = reader.read_byte();
}

WAVConfiguration::~WAVConfiguration() {

}

void WAVConfiguration::write(Writer &writer) {
	writer.write_rsdk_string(name);
	writer.write_uint_8(max_concurrent_play);
}

std::string WAVConfiguration::get_wav_name() {
	return name;
}

uint8_t WAVConfiguration::get_max_concurrent_play() {
	return max_concurrent_play;
}