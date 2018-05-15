#include "GameConfig.h"

GameConfig::GameConfig(Reader &reader) {
	read_magic(reader);

	game_name = std::string(reader.read_rsdk_string());
	game_subname = std::string(reader.read_rsdk_string());
	version = std::string(reader.read_rsdk_string());

	start_scene_category_index = reader.read_byte();
	start_scene_index = reader.read_uint_16();

	read_objects_names(reader);
	read_palettes(reader);
	read_WAV_configuration(reader);

	uint16_t total_scenes = reader.read_uint_16();

	uint8_t categories_count = reader.read_byte();
	for (unsigned int i = 0; i < categories_count; ++i) {
		categories.push_back(Category(reader));
	}

	uint8_t config_memory_count = reader.read_byte();
	for (unsigned int i = 0; i < config_memory_count; ++i) {
		ConfigurableMemoryEntry entry = ConfigurableMemoryEntry(reader);
		configurable_memory_entries.push_back(entry);
		if (entry.eol_flag) {
			break;
		}
	}
}

GameConfig::~GameConfig() {

}

void GameConfig::write(Writer& writer) {
	write_magic(writer);

	writer.write_rsdk_string(game_name);
	writer.write_rsdk_string(game_subname);
	writer.write_rsdk_string(version);

	writer.write_uint_8(start_scene_category_index);
	writer.write_uint_16(start_scene_index);

	write_objects_names(writer);
	write_palettes(writer);
	writer.write_padding(14);
	write_WAV_configuration(writer);

	uint16_t total_scenes = 0;
	for (auto &i : categories) {
		total_scenes += i.info_list.size();
	}
	writer.write_uint_16(total_scenes);

	writer.write_uint_8(categories.size());
	for (auto &i : categories) {
		i.write(writer);
	}

	//std::string config_memory_vector_size = std::to_string(configurable_memory_entries.size());
	//std::reverse(config_memory_vector_size.begin(), config_memory_vector_size.end());

	//uint8_t size = uint8_t(std::stoul(config_memory_vector_size));
	//writer.write_uint_8(size);
	
	//In till i figure out how the size is caculated i'm going to just write the
	//original default value.
	writer.write_byte('1');

	for (auto &i : configurable_memory_entries) {
		i.write(writer);
	}
}

void GameConfig::write_game_config(Writer& writer) {
	write(writer);
}

Category &GameConfig::get_category(std::string name) {
	auto it = std::find_if(categories.begin(), categories.end(), [&name](Category& obj) {return obj.get_name() == name; });
	if (it != categories.end()) {
		return *it;
	} else {
		throw std::runtime_error("Name input was not equal to any Category names!");
	}
}