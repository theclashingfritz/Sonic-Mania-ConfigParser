#include "TilesConfig.h"

char TilesConfig::MAGIC[] = { 'T', 'I', 'L', '\0' };

// 96 tiles exactly. Dunno why koolkdev put over 400! He put 1024 in decimal aka 0x400
const int TilesConfig::TILES_COUNT = 96;

TilesConfig::TilesConfig(Reader &reader, bool isCompressed, bool directDump) : parser(reader) {
#ifdef _DEBUG
	module_name = "TilesConfig";
#endif
	read_magic(parser);
	if (!directDump) {
		isDirectDumping = false;
		if (isCompressed) {
			read_tiles_config(parser);
		} else {
			read_uncompressed_tiles_config(parser);
		}
	} else {
		isDirectDumping = true;
		decompressed_dump_data = reader.read_compressed();
	}
}

TilesConfig::~TilesConfig() {

}

void TilesConfig::read_tiles_config(Reader &reader) {
	if (isDirectDumping) {
#ifdef _DEBUG
		std::cout << "Tiles config tried to read config normally while direct dumping!" << std::endl;
		module_name = "TilesConfig";
		function = "read_tiles_config";
		line_number = "28 - 36";
#endif
		throw std::runtime_error("Tried to read config normally while direct dumping!");
	}

	Reader *decompressed_reader_pointer;
	try {
		Reader &decompressed_reader_store = reader.get_compressed_stream();
		decompressed_reader_pointer = &decompressed_reader_store;
	} catch (const std::runtime_error& e) {
		throw std::exception(e.what());
	} catch (const std::exception& e) {
		throw std::exception(e.what());
	} catch (...) {
		throw std::exception("Unknown Exception!");
	}

	Reader decompressed_reader = *decompressed_reader_pointer;

	while (!decompressed_reader.is_eof()) {
		collision_paths.push_back(std::move(TileConfig(decompressed_reader)));
	}
	// We pop the back because some crud is picked up from memory. This will get rid of it.
	collision_paths.pop_back();
#ifdef _DEBUG
	std::cout << "Tiles Config reading is complete!" << std::endl;
#endif
}

void TilesConfig::read_uncompressed_tiles_config(Reader &reader) {
	if (isDirectDumping) {
#ifdef _DEBUG
		std::cout << "Tiles config tried to read uncompressed config normally while direct dumping!" << std::endl;
		module_name = "TilesConfig";
		function = "read_uncompressed_tiles_config";
		line_number = "48 - 56";
#endif
		throw std::runtime_error("Tried to read uncompressed config normally while direct dumping!");
	}

	while (!reader.is_eof()) {
		collision_paths.push_back(std::move(TileConfig(reader)));
	}
	// We pop the back because some crud is picked up from memory. This will get rid of it.
	collision_paths.pop_back();
#ifdef _DEBUG
	std::cout << "Uncompressed Tiles Config reading is complete!" << std::endl;
#endif
}

void TilesConfig::write_tiles_config(Writer &writer) {
	if (isDirectDumping) {
#ifdef _DEBUG
		std::cout << "Tiles config tried to write config normally while direct dumping!" << std::endl;
		module_name = "TilesConfig";
		function = "write_tiles_config";
		line_number = "71 - 77";
#endif
		throw std::runtime_error("Tried to write config normally while direct dumping!");
	}

	write_magic(writer);
	std::stringbuf string_stream = std::stringbuf();
	Writer compression_writer = Writer(string_stream);
	for (int i = 0; i < collision_paths.size(); ++i) {
		collision_paths.at(i).write(compression_writer);
	}
	std::string compressed_string = string_stream.str();
	writer.write_compressed(compressed_string);
}

void TilesConfig::write_uncompressed_tiles_config(Writer &writer) {
	if (isDirectDumping) {
#ifdef _DEBUG
		std::cout << "Tiles config tried to write uncompressed config normally while direct dumping!" << std::endl;
		module_name = "TilesConfig";
		function = "write_uncompressed_tiles_config";
		line_number = "95 - 101";
#endif
		throw std::runtime_error("Tried to write uncompressed config normally while direct dumping!");
	}

	write_magic(writer);
	for (int i = 0; i < collision_paths.size(); ++i) {
		collision_paths.at(i).write(writer);
	}
}

void TilesConfig::write_direct_dump(Writer &writer) {
	if (!isDirectDumping) {
#ifdef _DEBUG
		std::cout << "Tiles config tried to perform direct dump while direct dumping isn't enabled!" << std::endl;
		module_name = "TilesConfig";
		function = "write_direct_dump";
		line_number = "115 - 120";
#endif
		throw std::runtime_error("Tried to perform direct dump while direct dumping isn't enabled!");
	}

	write_magic(writer);
	for (size_t i = 0; i < decompressed_dump_data.length(); ++i) {
		writer.write_byte(unsigned char(decompressed_dump_data.at(i)));
	}
}

void TilesConfig::read_magic(Reader &reader) {
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

void TilesConfig::write_magic(Writer &writer) {
	writer.write(MAGIC);
	writer.write_byte(__int8(0x00));
}