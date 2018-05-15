#pragma once

#include "INIFileParser.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cctype>
#include <intrin.h>
#include <zlib.h>
#include <memory>

class EXPORT Reader {

    public:
		Reader(std::string string);
		Reader(std::iostream io_stream);
		Reader(std::fstream file_stream);
		Reader(std::stringstream &string_stream);
		Reader(std::streambuf *stream_buff);
		Reader(std::stringbuf &string_buff);
		Reader(std::filebuf *file_buff);
		Reader(Reader &reader);
        virtual ~Reader();

		Reader &operator=(Reader &reader);
		Reader get_compressed_stream();

		void extract_bytes(char *&char_pointer, std::streamsize n);
		void extract_bytes(std::string &string, std::streamsize n);
        
        inline void seek(int position);
		inline void seek(int position, int origin);
		inline void seek(unsigned int position);
		inline void seek(unsigned int position, unsigned int origin);
		inline void seek(std::streampos position);
		inline void seek(std::streampos position, std::streampos origin);
        
        bool is_eof();

		bool read_boolean();
        
        short read_int_16();
        short read_int_16_be();
        
        unsigned short read_uint_16();
        unsigned short read_uint_16_be();

        int read_int_32();
        int read_int_32_be();

		unsigned int size();

		std::streampos distance_from_eof();
        
        unsigned int read_uint_32();
        unsigned int read_uint_32_be();

		char read_byte();
        
        char *read_rsdk_string();
        char *read_rsdk_unicode_string();
        char *read_bytes(int count);
        std::string read_compressed();

		inline std::streampos pos();
        
    private:
        std::iostream stream;
	
};