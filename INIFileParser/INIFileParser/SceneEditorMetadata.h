#pragma once

#include "INIFileParser.h"
#include "Reader.h"
#include "Writer.h"
#include "Color.h"

class EXPORT SceneEditorMetadata {

	public:
        SceneEditorMetadata();
		SceneEditorMetadata(Reader &reader);
		virtual ~SceneEditorMetadata();

		void write(Writer &writer);
        
        Color background_color_1;
        Color background_color_2;

	private:
        unsigned char unknown_byte, unknown_byte_2;
		std::string bin_name;
        unsigned char unknown_bytes[8];
};