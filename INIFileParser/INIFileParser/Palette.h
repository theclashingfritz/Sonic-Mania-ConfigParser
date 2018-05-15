#pragma once

#include <map>
#include <memory>

#include "INIFileParser.h"
#include "Reader.h"
#include "Writer.h"
#include "PaletteColor.h"


class EXPORT Palette {

	public:
		Palette(Reader &reader);
		~Palette();

		void print_palette_colors();

		void write(Writer &writer);

	protected:
		static const int PALETTE_COLUMNS;
		static const int COLORS_PER_COLUMN;
		static const int PALETTE_COLORS;
		std::map<int, std::vector<std::shared_ptr<PaletteColor> > > Colors;
		uint16_t columns_bitmap;
};