#pragma once

#include "INIFileParser.h"
#include "zstr.hpp"
#include "Reader.h"
#include "Writer.h"
#include "Palette.h"
#include "WAVConfiguration.h"

class EXPORT CommonConfig {

	public:
		CommonConfig();
		virtual ~CommonConfig();

		virtual void read_magic(Reader &reader);
		virtual void write_magic(Writer &writer);

		void read_common_config(Reader &reader);
		void write_common_config(Writer &writer);

		void read_objects_names(Reader &reader);
		void write_objects_names(Writer &writer);

		void read_palettes(Reader &reader);
		void write_palettes(Writer &writer);

		void read_WAV_configuration(Reader &reader);
		void write_WAV_configuration(Writer &writer);

	protected:
		std::vector<std::string> object_list;
		std::vector<Palette> palette_list;
		std::vector<WAVConfiguration> wav_list;
		uint8_t wav_count;
		static char MAGIC[];
		static const int PALETTES_COUNT;
};