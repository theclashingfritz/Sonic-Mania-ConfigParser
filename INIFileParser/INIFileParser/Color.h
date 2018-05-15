#pragma once

#include "INIFileParser.h"
#include "Reader.h"
#include "Writer.h"


class EXPORT Color {

	public:
		Color();
		Color(uint8_t c_r, uint8_t c_g, uint8_t c_b, uint8_t c_a);
		Color(Reader &reader);
		~Color();

		void read(Reader &reader);
		void write(Writer &writer);

    protected:
		uint8_t r, g, b, a;

};
