#include "ConfigurableMemoryEntry.h"

ConfigurableMemoryEntry::ConfigurableMemoryEntry(Reader &reader) {
	eol_flag = false;
	index = reader.read_uint_32();
	unsigned int count = reader.read_uint_32();
	if (count > 0) {
		for (unsigned int i = 0; i < count; ++i) {
			int integer = reader.read_int_32();
			if (integer == 0xCDCDCDCD) {
				eol_flag = true;
				break;
			}
			data.push_back(integer);
		}
		data.shrink_to_fit();
	}
}

ConfigurableMemoryEntry::~ConfigurableMemoryEntry() {

}

void ConfigurableMemoryEntry::write(Writer &writer) {
	writer.write_uint_32(index);
	writer.write_uint_32(data.size());
	for (auto &i : data) {
		writer.write_int_32(i);
	}
}