#include "Palette.h"

const int Palette::PALETTE_COLUMNS = 16;
const int Palette::COLORS_PER_COLUMN = 16;
const int Palette::PALETTE_COLORS = 256;

Palette::Palette(Reader &reader) {
	columns_bitmap = reader.read_uint_16();
	for (unsigned int i = 0; i < PALETTE_COLUMNS; ++i) {
		if ((columns_bitmap & (1 << i)) != 0) {
			std::vector<std::shared_ptr<PaletteColor> > color_vector;
			if (!Colors[i].empty()) {
				color_vector = Colors[i];
			}
			for (unsigned int j = 0; j < COLORS_PER_COLUMN; ++j) {
				std::shared_ptr<PaletteColor> ptr(new PaletteColor(reader));
				color_vector.push_back(std::move(ptr));
			}
			color_vector.shrink_to_fit();
			if (Colors[i].empty()) {
				Colors[i] = color_vector;
			}
		}
	}
}

Palette::~Palette() {

}

void Palette::print_palette_colors() {
	std::cout << "{";
	for (auto &it : Colors) {
		std::cout << "[";
		std::vector<std::shared_ptr<PaletteColor> > color_vector = it.second;
		for (int j = 0; j < color_vector.size(); ++j) {
			std::cout << "(";
			uint8_t r = color_vector.at(j).get()->get_r();
			std::cout << uint_least8_t(r) << ", ";
			uint8_t g = color_vector.at(j).get()->get_g();
			std::cout << uint_least8_t(g) << ", ";
			uint8_t b = color_vector.at(j).get()->get_b();
			std::cout << uint_least8_t(b);
			std::cout << ") ";
		}
		std::cout << "]";
	}
	std::cout << "}";
	std::cout << "\n";
	std::cout << std::endl;
}

void Palette::write(Writer &writer) {
	columns_bitmap = 0;
	if (!Colors.empty()) {
		for (int i = 0; i < PALETTE_COLUMNS; ++i) {
			if (!Colors[i].empty()) {
				columns_bitmap |= (1 << i);
			}
		}
		if (columns_bitmap != 0xFFFF) {
			writer.write_uint_16(columns_bitmap);
		} else {
			// A fallback.
			writer.write_uint_16(0x00);
		}
		for (auto &it : Colors) {
			std::vector<std::shared_ptr<PaletteColor> > color_vector = it.second;
			for (int j = 0; j < color_vector.size(); ++j) {
				color_vector.at(j).get()->write(writer);
			}
		}
	}
}