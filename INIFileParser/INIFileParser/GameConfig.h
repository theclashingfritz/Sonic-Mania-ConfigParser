#pragma once

#include "INIFileParser.h"
#include "zstr.hpp"
#include "Reader.h"
#include "Writer.h"
#include "CommonConfig.h"
#include "Category.h"
#include "ConfigurableMemoryEntry.h"

#include <algorithm>
#include <vector>
#include <iterator>

class EXPORT GameConfig : public CommonConfig {

	public:
		GameConfig(Reader &reader);
		~GameConfig();

		virtual void write(Writer &writer);
		inline void write_game_config(Writer& writer);

		Category &get_category(std::string name);

	protected:
		Reader *r_parser;
		std::string game_name, game_subname, version;
		uint8_t start_scene_category_index;
		uint16_t start_scene_index;
		std::vector<Category> categories;
		std::vector<ConfigurableMemoryEntry> configurable_memory_entries;
};