#pragma once

#include "INIFileParser.h"
#include "Reader.h"
#include "Writer.h"

class EXPORT ConfigurableMemoryEntry {

	public:
		ConfigurableMemoryEntry(Reader &reader);
		virtual ~ConfigurableMemoryEntry();

		void write(Writer &writer);

		bool eol_flag;

	private:
		unsigned int index;
		std::vector<int> data;
};