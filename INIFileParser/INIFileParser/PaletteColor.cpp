#include "PaletteColor.h"

PaletteColor::PaletteColor() {
	r = 0;
	g = 0;
	b = 0;
}

PaletteColor::PaletteColor(uint8_t c_r, uint8_t c_g, uint8_t c_b) {
	r = c_r;
	g = c_g;
	b = c_b;
}

PaletteColor::PaletteColor(Reader &reader) {
	read(reader);
}

PaletteColor::~PaletteColor() {

}

void PaletteColor::read(Reader &reader) {
	r = uint8_t(reader.read_byte());
	g = uint8_t(reader.read_byte());
	b = uint8_t(reader.read_byte());
}

void PaletteColor::write(Writer &writer) {
	writer.write_byte(r);
	writer.write_byte(g);
	writer.write_byte(b);
}

uint8_t PaletteColor::get_r() {
	return r;
}

uint8_t PaletteColor::get_g() {
	return g;
}

uint8_t PaletteColor::get_b() {
	return b;
}