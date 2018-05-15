#pragma once

#include "INIFileParser.h"
#include "zstr.hpp"

#include <intrin.h>

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cctype>
#include <memory>

#include <zlib.h>

class EXPORT Writer {

    public:
		Writer(std::string string);
		Writer(std::iostream io_stream);
		Writer(std::fstream file_stream);
		Writer(std::stringstream &string_stream);
		Writer(std::streambuf *stream_buff);
		Writer(std::stringbuf &string_buff);
		Writer(std::filebuf *file_buff);
		Writer(Writer &writer);
        virtual ~Writer();

		Writer &operator=(Writer &writer);
        
        inline void seek(int position);
        inline void seek(int position, int origin);
		inline void seek(unsigned int position);
		inline void seek(unsigned int position, unsigned int origin);
		inline void seek(std::streampos position);
		inline void seek(std::streampos position, std::streampos origin);

		void write(char *bytes);
		void write(unsigned char *bytes);

		void write_int_8(int8_t value);

		void write_uint_8(uint8_t value);

		void write_int_16(int16_t val);
		void write_int_16_be(int16_t val);

		void write_uint_16(uint16_t val);
		void write_uint_16_be(uint16_t val);
        
        void write_int_32(int value);
        void write_int_32_be(int value);
        
        void write_uint_32(unsigned int value);
        void write_uint_32_be(unsigned int value);
        
        void write_rsdk_string(char *string);
		void write_rsdk_string(std::string string);

        void write_rsdk_unicode_string(char *string);
		void write_rsdk_unicode_string(std::string string);

		void write_padding(unsigned int amount);

		void write_byte(__int8 byte);
		void write_byte(uint8_t byte);
		void write_byte(unsigned short byte);

        void write_bytes(char *bytes);
		void write_bytes(unsigned char *bytes);

        void write_compressed(std::string bytes);
		void write_compressed(unsigned char *bytes);

		std::iostream &get_stream();
        
        bool is_eof();
        
		unsigned int size();
		inline std::streampos pos();
        
    private:
        std::iostream stream;
	
};