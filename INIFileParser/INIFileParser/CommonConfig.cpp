#include "CommonConfig.h"

char CommonConfig::MAGIC[] = {'C', 'F', 'G', '\0'};
const int CommonConfig::PALETTES_COUNT = 8;

CommonConfig::CommonConfig() {
	object_list.reserve(40);
	palette_list.reserve(40);
}

CommonConfig::~CommonConfig() {

}

void CommonConfig::read_magic(Reader &reader) {
	char *read_bytes = reader.read_bytes(4);
	if (read_bytes == "EOF") {
		return;
	}
	if (read_bytes == nullptr) {
#ifdef _DEBUG
		std::cout << "Read Magic was a nullptr!" << std::endl;
#endif
		throw std::runtime_error("Read Magic was a nullptr!");
	}
	if ((std::string(read_bytes).compare(std::string(MAGIC)) != 0)) {
#ifdef _DEBUG
		std::cout << "Invalid Magic! (" << read_bytes << " != " << MAGIC << ")" << std::endl;
#endif
		throw std::runtime_error("Invalid Magic!");
	}
}

void CommonConfig::write_magic(Writer &writer) {
	writer.write(MAGIC);
	writer.write_byte(__int8(0x00));
}

void CommonConfig::read_common_config(Reader &reader) {
	read_objects_names(reader);
	read_palettes(reader);
	read_WAV_configuration(reader);
}

void CommonConfig::write_common_config(Writer &writer) {
	write_objects_names(writer);
	write_palettes(writer);
	write_WAV_configuration(writer);
}

void CommonConfig::read_objects_names(Reader &reader) {
	uint8_t objects_count = reader.read_byte();
	for (uint16_t i = 0; i < objects_count; ++i) {
		char *object_string = reader.read_rsdk_string();
		object_list.push_back(std::string(object_string));
		delete object_string;
	}
	object_list.shrink_to_fit();
}

void CommonConfig::write_objects_names(Writer &writer) {
	writer.write_uint_8(object_list.size());
	for (auto &i : object_list) {
		writer.write_rsdk_string(i);
	}
}

void CommonConfig::read_palettes(Reader &reader) {
	for (unsigned int i = 0; i < PALETTES_COUNT; ++i) {
		palette_list.push_back(Palette(reader));
	}
	palette_list.shrink_to_fit();
}

void CommonConfig::write_palettes(Writer &writer) {
	for (unsigned int i = 0; i < palette_list.size(); ++i) {
		palette_list.at(i).write(writer);
	}
}

void CommonConfig::read_WAV_configuration(Reader &reader) {
	wav_count = uint8_t(reader.read_byte());
	for (unsigned int i = 0; i < wav_count; ++i) {
		wav_list.push_back(WAVConfiguration(reader));
	}
	wav_list.shrink_to_fit();
}

void CommonConfig::write_WAV_configuration(Writer &writer) {
	writer.write_uint_8(wav_list.size());
	for (unsigned int i = 0; i < wav_list.size(); ++i) {
		wav_list.at(i).write(writer);
	}
}