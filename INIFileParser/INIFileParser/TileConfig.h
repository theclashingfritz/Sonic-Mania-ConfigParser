#pragma once

#include "INIFileParser.h"
#include "Reader.h"
#include "Writer.h"

#include <intrin.h>

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cctype>
#include <memory>

class TilesConfig;

class EXPORT TileConfig {
	friend class TilesConfig;

	public:
		TileConfig(Reader &reader);
		TileConfig(std::fstream file_stream);
		virtual ~TileConfig();

	protected:
		virtual void read(Reader &reader);
	    
		virtual void write(Writer &writer);

	private:
		Reader &parser;

		// Collision position for each pixel
		std::vector<uint8_t> collision;

		// If said pixel has collision
		std::vector<uint8_t> has_collision;

		// If it is a celing, the collision is from below
		uint8_t is_ceiling;

		// Unknown 5 bytes config
		std::vector<uint8_t> config;
};

