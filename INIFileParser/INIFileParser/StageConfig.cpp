#include "StageConfig.h"

StageConfig::StageConfig(Reader &reader) {
	read_magic(reader);
	use_game_objects = reader.read_boolean();
	read_common_config(reader);
	r_parser = &reader;
	object_list.reserve(400);
}

StageConfig::~StageConfig() {

}

void StageConfig::add_object_name(std::string name) {
	object_list.push_back(name);
}

void StageConfig::print_object_list() {
	for (auto &i : object_list) {
		std::cout << i << "\n" << std::endl;
	}
}

void StageConfig::print_palettes() {
	for (auto &i : palette_list) {
		i.print_palette_colors();
	}
}

void StageConfig::print_wave_configurations() {
	for (auto &i : wav_list) {
		std::cout << "(" << i.get_wav_name() << ", " << std::to_string(i.get_max_concurrent_play()) << ")" << "\n" << std::endl;
	}
}

void StageConfig::write_stage_config(Writer &writer) {
	write_magic(writer);
	writer.write_uint_8(use_game_objects);
	write_objects_names(writer);
	writer.write_byte(unsigned char(0x00));
	writer.write_byte(unsigned char(0x00));
	write_palettes(writer);
	writer.write_padding(8);
	write_WAV_configuration(writer);
}