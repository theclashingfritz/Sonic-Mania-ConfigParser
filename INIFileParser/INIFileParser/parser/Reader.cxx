#include "Reader.h"

Reader::Reader(std::string string) : stream(new std::stringbuf(string, (std::stringstream::in | std::stringstream::out | std::stringstream::binary))) {
#ifdef _DEBUG
	module_name = "Reader";
#endif
}

Reader::Reader(std::iostream io_stream) : stream(io_stream.rdbuf()) {
#ifdef _DEBUG
	module_name = "Reader";
#endif
}

Reader::Reader(std::fstream file_stream) : stream(file_stream.rdbuf()) {
#ifdef _DEBUG
	module_name = "Reader";
#endif
}

Reader::Reader(std::stringstream &string_stream) : stream(string_stream.rdbuf()) {
#ifdef _DEBUG
	module_name = "Reader";
#endif
}

Reader::Reader(std::streambuf *stream_buff) : stream(stream_buff) {
#ifdef _DEBUG
	module_name = "Reader";
#endif
}

Reader::Reader(std::stringbuf &string_buff) : stream(&string_buff) {
#ifdef _DEBUG
	module_name = "Reader";
#endif
}

Reader::Reader(std::filebuf *file_buff) : stream(file_buff) {
#ifdef _DEBUG
	module_name = "Reader";
#endif
}

Reader::Reader(Reader &reader) : stream(reader.stream.rdbuf()) {
#ifdef _DEBUG
	module_name = "Reader";
#endif
}

Reader::~Reader() {
	
}

Reader &Reader::operator=(Reader &reader) {
#ifdef _DEBUG
	module_name = "Reader";
	function = "operator=";
	line_number = "55 - 63";
#endif
	Reader r = *new Reader(reader);
	return r;
}

Reader Reader::get_compressed_stream() {
#ifdef _DEBUG
	module_name = "Reader";
	function = "get_compressed_stream";
	line_number = "65 - 74";
#endif
	try {
		std::string decompressed_data = *new std::string(read_compressed());
		Reader decompressed_reader = *new Reader(decompressed_data);
		return decompressed_reader;
	} catch (const std::runtime_error& e) {
		throw std::exception(e.what());
	} catch (const std::exception& e) {
		throw std::exception(e.what());
	} catch (...) {
		throw std::exception("Unknown Exception!");
	}
}

void Reader::extract_bytes(char *&char_pointer, std::streamsize n) {
#ifdef _DEBUG
	module_name = "Reader";
	function = "extract_bytes";
	line_number = "76 - 97";
#endif
	if (is_eof()) {
		return;
	}

	try {
		stream.read(char_pointer, n);
	} catch (const std::runtime_error& e) {
		std::cout << "An Runtime Exception has occured: " << e.what() << "." << std::endl;
		std::cout << "Reader(error): Byte Extraction has stopped." << std::endl;
	} catch (const std::exception& e) {
		std::cout << "An Exception has occured: " << e.what() << "." << std::endl;
		std::cout << "Reader(error): Byte Extraction has stopped." << std::endl;
	} catch (...) {
		std::cout << "Unhandled exception was caught!" << std::endl;
		std::cout << "Reader(error): Byte Extraction has stopped." << std::endl;
	}
}

void Reader::extract_bytes(std::string &string, std::streamsize n) {
#ifdef _DEBUG
	module_name = "Reader";
	function = "extract_bytes";
	line_number = "100 - 124";
#endif
	if (is_eof()) {
		return;
	}

	try {
		char *byte_string = new char[n + 1];
		byte_string[n] = '\0';
		stream.read(byte_string, n);
		string = std::string(byte_string);
	} catch (const std::runtime_error& e) {
		std::cout << "An Runtime Exception has occured: " << e.what() << "." << std::endl;
		std::cout << "Reader(error): Byte Extraction has stopped." << std::endl;
	} catch (const std::exception& e) {
		std::cout << "An Exception has occured: " << e.what() << "." << std::endl;
		std::cout << "Reader(error): Byte Extraction has stopped." << std::endl;
	} catch (...) {
		std::cout << "Unhandled exception was caught!" << std::endl;
		std::cout << "Reader(error): Byte Extraction has stopped." << std::endl;
	}
}

inline void Reader::seek(int position) {
#ifdef _DEBUG
	module_name = "Reader";
	function = "seek";
	line_number = "127 - 134";
#endif
    stream.seekg(0, position);  
}

inline void Reader::seek(int position, int origin) {
#ifdef _DEBUG
	module_name = "Reader";
	function = "seek";
	line_number = "136 - 143";
#endif
    stream.seekg(origin, position);  
}

inline void Reader::seek(unsigned int position) {
#ifdef _DEBUG
	module_name = "Reader";
	function = "seek";
	line_number = "145 - 152";
#endif
	stream.seekg(0, position);
}

inline void Reader::seek(unsigned int position, unsigned int origin) {
#ifdef _DEBUG
	module_name = "Reader";
	function = "seek";
	line_number = "154 - 161";
#endif
	stream.seekg(origin, position);
}

inline void Reader::seek(std::streampos position) {
#ifdef _DEBUG
	module_name = "Reader";
	function = "seek";
	line_number = "163 - 170";
#endif
	stream.seekg(0, position);
}

inline void Reader::seek(std::streampos position, std::streampos origin) {
#ifdef _DEBUG
	module_name = "Reader";
	function = "seek";
	line_number = "172 - 179";
#endif
	stream.seekg(origin, position);
}

bool Reader::is_eof() {
#ifdef _DEBUG
	module_name = "Reader";
	function = "is_eof";
	line_number = "181 - 188";
#endif
    return (stream.eof() || stream.bad());
}

bool Reader::read_boolean() {
#ifdef _DEBUG
	module_name = "Reader";
	function = "read_boolean";
	line_number = "190 - 203";
#endif
	if (is_eof()) {
		return false;
	}

	char *buffer = new char[2];
	stream.read(buffer, 1);
	return bool(buffer[0]);
}

inline std::streampos Reader::pos() {
#ifdef _DEBUG
	module_name = "Reader";
	function = "pos";
	line_number = "205 - 212";
#endif
    return stream.tellg();
}

unsigned int Reader::size() { 
#ifdef _DEBUG
	module_name = "Reader";
	function = "size";
	line_number = "214 - 226";
#endif
    std::streampos original_position = pos();
    seek(stream.end);
	std::streampos stream_length = pos();
	seek(original_position);
    
    return stream_length;
}

std::streampos Reader::distance_from_eof() {
	std::streampos pos = this->pos();
	seek(stream.end);
	std::streampos stream_length = this->pos();
	seek(pos);

	return (stream_length - pos);
}

short Reader::read_int_16() {
#ifdef _DEBUG
	module_name = "Reader";
	function = "read_int_16";
	line_number = "228 - 244";
#endif
	if (is_eof()) {
		return 0;
	}

	unsigned char *int16_char = (unsigned char *)read_bytes(2);
    short value = static_cast<int16_t>(static_cast<unsigned char>(int16_char[0]) << 0 |
            static_cast<unsigned char>(int16_char[1]) << 8);
    
    delete int16_char;
    return value;
}

short Reader::read_int_16_be() {
#ifdef _DEBUG
	module_name = "Reader";
	function = "read_int_16_be";
	line_number = "246 - 262";
#endif
	if (is_eof()) {
		return 0;
	}

    unsigned char *int16_char = (unsigned char *)read_bytes(2);
    short value = static_cast<int16_t>(static_cast<unsigned char>(int16_char[0]) << 8 |
            static_cast<unsigned char>(int16_char[1]) << 0);
    
    delete int16_char;
    return value;
}

unsigned short Reader::read_uint_16() {
#ifdef _DEBUG
	module_name = "Reader";
	function = "read_uint_16";
	line_number = "264 - 293";
#endif
	if (is_eof()) {
		return 0;
	}

    unsigned char *uint16_char = (unsigned char *)read_bytes(2);
    unsigned short value = static_cast<uint16_t>(static_cast<unsigned char>(uint16_char[0]) << 0 |
            static_cast<unsigned char>(uint16_char[1]) << 8);
    
    delete uint16_char;
    return value;
}

unsigned short Reader::read_uint_16_be() {
#ifdef _DEBUG
	module_name = "Reader";
	function = "read_uint_16_be";
	line_number = "282 - 298";
#endif
	if (is_eof()) {
		return 0;
	}

    unsigned char *uint16_char = (unsigned char *)read_bytes(2);
    unsigned short value = static_cast<uint16_t>(static_cast<unsigned char>(uint16_char[0]) << 8 |
            static_cast<unsigned char>(uint16_char[1]) << 0);
    
    delete uint16_char;
    return value;
}

int Reader::read_int_32() {
#ifdef _DEBUG
	module_name = "Reader";
	function = "read_int_32";
	line_number = "300 - 318";
#endif
	if (is_eof()) {
		return 0;
	}

	unsigned char *int32_char = (unsigned char *)read_bytes(4);
    int value = static_cast<int32_t>(int32_char[0] << 0 |
									int32_char[1] << 8 |
									int32_char[2] << 16 |
									int32_char[3] << 24);
    
    delete int32_char;
    return value;
}

int Reader::read_int_32_be() {
#ifdef _DEBUG
	module_name = "Reader";
	function = "read_int_32_be";
	line_number = "320 - 338";
#endif
	if (is_eof()) {
		return 0;
	}

	unsigned char *int32_char = (unsigned char *)read_bytes(4);
	int value = static_cast<int32_t>(int32_char[0] << 24 |
									int32_char[1] << 16 |
									int32_char[2] << 8 |
									int32_char[3] << 0);
    
    delete int32_char;
    return value;
}

unsigned int Reader::read_uint_32() {
#ifdef _DEBUG
	module_name = "Reader";
	function = "read_uint_32";
	line_number = "340 - 358";
#endif
	if (is_eof()) {
		return 0;
	}

    unsigned char *uint32_char = (unsigned char *)read_bytes(4);
    unsigned int value = static_cast<uint32_t>(uint32_char[0] << 0 |
											uint32_char[1] << 8 |
											uint32_char[2] << 16 |
											uint32_char[3] << 24);
    
    delete uint32_char;
    return value;
}

unsigned int Reader::read_uint_32_be() {
#ifdef _DEBUG
	module_name = "Reader";
	function = "read_uint_32_be";
	line_number = "360 - 378";
#endif
	if (is_eof()) {
		return 0;
	}

    unsigned char *uint32_char = (unsigned char *)read_bytes(4);
	unsigned int value = static_cast<uint32_t>(uint32_char[0] << 24 |
											uint32_char[1] << 16 |
											uint32_char[2] << 8 |
											uint32_char[3] << 0);
    
    delete uint32_char;
    return value;
}

char *Reader::read_rsdk_string() {
#ifdef _DEBUG
	module_name = "Reader";
	function = "read_rsdk_string";
	line_number = "380 - 396";
#endif
    if (is_eof()) {
        char *c_char = new char[5];
        c_char = "EOF";
        return c_char;
    }
    uint8_t size = read_byte();
	char *string = read_bytes(size);
	// Just to guarantee it's null terminated.
	string[size] = '\0';
    return string;
}

char *Reader::read_rsdk_unicode_string() {
#ifdef _DEBUG
	module_name = "Reader";
	function = "read_rsdk_unicode_string";
	line_number = "398 - 414";
#endif
    if (is_eof()) {
        char *c_char = new char[5];
        c_char = "EOF";
        return c_char;
    }
    unsigned int size = atoi(read_bytes(read_uint_16() * 2));
	char *string = read_bytes(size);
	// Just to guarantee it's null terminated.
	string[size] = '\0';
	return string;
}

char Reader::read_byte() {
#ifdef _DEBUG
	module_name = "Reader";
	function = "read_byte";
	line_number = "416 - 431";
#endif
	if (is_eof()) {
		return char(0x00);
	}

	char *buffer = new char[2];
	stream.read(buffer, 1);
	char byte = char(buffer[0]);
	delete[] buffer;
	return byte;
}

char *Reader::read_bytes(int count) { 
#ifdef _DEBUG
	module_name = "Reader";
	function = "read_byte";
	line_number = "433 - 453";
#endif
    if (is_eof()) {
        char *c_char = new char[5];
        c_char = "EOF";
        return c_char;
    }
    
    int new_count = count + 1;
	char *buffer = new char[new_count];
    stream.read(buffer, count);
	char *terminator_check = strrchr(buffer, char('\0'));
	if (!terminator_check || terminator_check == nullptr) {
		buffer[count] = '\0';
	}
    return buffer;
}

std::string Reader::read_compressed() {
#ifdef _DEBUG
	module_name = "Reader";
	function = "read_compressed";
	line_number = "455 - 470";
#endif
    unsigned int compressed_size = read_uint_32();
    unsigned int uncompressed_size = read_uint_32_be();
    
    unsigned char *buff = new unsigned char[compressed_size + 1027];
	buff[compressed_size + 1026] = '\0';
	stream.read((char *)buff, compressed_size);
	std::string out_string;
	try {
		out_string = decompress_string((char *)buff);
	} catch (const std::runtime_error& e) {
		throw std::exception(e.what());
	} catch (const std::exception& e) {
		throw std::exception(e.what());
	} catch (...) {
		throw std::exception("Unknown Exception!");
	}
	delete[] buff;
    return out_string;
}