#pragma once

#include "INIFileParser.h"
#include "Reader.h"
#include "Writer.h"


class EXPORT PaletteColor {

	public:
		PaletteColor();
		PaletteColor(uint8_t c_r, uint8_t c_g, uint8_t c_b);
		PaletteColor(Reader &reader);
		~PaletteColor();

		void read(Reader &reader);
		void write(Writer &writer);

		uint8_t get_r();
		uint8_t get_g();
		uint8_t get_b();

	protected:
		uint8_t r, g, b;

};
