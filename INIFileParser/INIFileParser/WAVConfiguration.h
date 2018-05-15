#pragma once

#include "INIFileParser.h"
#include "Reader.h"
#include "Writer.h"

class EXPORT WAVConfiguration {

	public:
		WAVConfiguration(Reader &reader);
		~WAVConfiguration();

		void write(Writer &writer);

		std::string get_wav_name();

		uint8_t get_max_concurrent_play();

	protected:
		std::string name;
		uint8_t max_concurrent_play;
};