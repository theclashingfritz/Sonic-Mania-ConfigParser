#pragma once

#include "INIFileParser.h"
#include "zstr.hpp"
#include "Reader.h"
#include "Writer.h"
#include "CommonConfig.h"
#include "TileConfig.h"

class EXPORT TilesConfig : public CommonConfig {

	public:
		TilesConfig(Reader &reader, bool isCompressed = true, bool directDump = false);
		virtual ~TilesConfig();

		void read_tiles_config(Reader &reader);

		void read_uncompressed_tiles_config(Reader &reader);

		void write_tiles_config(Writer &writer);

		void write_uncompressed_tiles_config(Writer &writer);

		void write_direct_dump(Writer &writer);

		virtual void read_magic(Reader &reader);

		virtual void write_magic(Writer &writer);

	protected:
		Reader &parser;

	private:
		bool isDirectDumping;

		static char MAGIC[];
		static const int TILES_COUNT;
		std::vector<TileConfig> collision_paths;

		std::string decompressed_dump_data;
};