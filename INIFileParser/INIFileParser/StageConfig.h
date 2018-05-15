#pragma once

#include "INIFileParser.h"
#include "zstr.hpp"
#include "Reader.h"
#include "Writer.h"
#include "CommonConfig.h"

class EXPORT StageConfig : public CommonConfig {

	public:
		StageConfig(Reader &reader);
		~StageConfig();

		void add_object_name(std::string name);

		void print_object_list();
		void print_palettes();
		void print_wave_configurations();

		void write_stage_config(Writer &writer);

	protected:
		Reader *r_parser;
		bool use_game_objects;
};