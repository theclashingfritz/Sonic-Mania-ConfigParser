#include "TileConfig.h"
#include "TilesConfig.h"

TileConfig::TileConfig(Reader &reader) : parser(reader) {
	read(parser);
}

TileConfig::TileConfig(std::fstream file_stream) : parser(Reader(file_stream.rdbuf())) {
	read(parser);
}

TileConfig::~TileConfig() {

}

void TileConfig::read(Reader &reader) {
	for (unsigned int i = 0; i < 16; ++i) {
		if (!reader.is_eof()) {
			collision.push_back(std::move(reader.read_byte()));
		}
	}
	for (unsigned int i = 0; i < 16; ++i) {
		if (!reader.is_eof()) {
			has_collision.push_back(std::move(reader.read_byte()));
		}
	}
	if (!reader.is_eof()) {
		is_ceiling = reader.read_byte();
	}
	for (unsigned int i = 0; i < 5; ++i) {
		if (!reader.is_eof()) {
			config.push_back(std::move(reader.read_byte()));
		}
	}

}

void TileConfig::write(Writer &writer) {
	for (unsigned int i = 0; i < collision.size(); ++i) {
		writer.write_byte(collision.at(i));
	}
	for (unsigned int i = 0; i < has_collision.size(); ++i) {
		writer.write_byte(unsigned char(has_collision.at(i)));
	}
	writer.write_byte(unsigned char(is_ceiling));
	for (unsigned int i = 0; i < config.size(); ++i) {
		if (i >= 5) {
			break;
		}
		writer.write_byte(config.at(i));
	}
}

