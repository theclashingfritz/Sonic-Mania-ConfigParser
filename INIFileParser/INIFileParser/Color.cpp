#include "Color.h"

Color::Color() {
	r = 0;
	g = 0;
	b = 0;
	a = 0;
}

Color::Color(uint8_t c_r, uint8_t c_g, uint8_t c_b, uint8_t c_a) {
	r = c_r;
	g = c_g;
	b = c_b;
	a = c_a;
}

Color::Color(Reader &reader) {
	read(reader);
}

Color::~Color() {

}

void Color::read(Reader &reader) {
	r = uint8_t(reader.read_byte());
	g = uint8_t(reader.read_byte());
	b = uint8_t(reader.read_byte());
	a = uint8_t(reader.read_byte());
}

void Color::write(Writer &writer) {
	writer.write_uint_8(r);
	writer.write_uint_8(g);
	writer.write_uint_8(b);
	writer.write_uint_8(a);
}