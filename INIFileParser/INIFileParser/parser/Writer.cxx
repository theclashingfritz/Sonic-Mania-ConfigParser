#include "Writer.h"

Writer::Writer(std::string string) : stream(new std::stringbuf(string, (std::stringstream::in | std::stringstream::out | std::stringstream::binary))) {
#ifdef _DEBUG
	module_name = "Writer";
#endif
}

Writer::Writer(std::iostream io_stream) : stream(io_stream.rdbuf()) {
#ifdef _DEBUG
	module_name = "Writer";
#endif
}

Writer::Writer(std::fstream file_stream) : stream(file_stream.rdbuf()) {
#ifdef _DEBUG
	module_name = "Writer";
#endif
}

Writer::Writer(std::stringstream &string_stream) : stream(string_stream.rdbuf()) {
#ifdef _DEBUG
	module_name = "Writer";
#endif
}

Writer::Writer(std::streambuf *stream_buff) : stream(stream_buff) {
#ifdef _DEBUG
	module_name = "Writer";
#endif
}

Writer::Writer(std::stringbuf &string_buff) : stream(&string_buff) {
#ifdef _DEBUG
	module_name = "Writer";
#endif
}

Writer::Writer(std::filebuf *file_buff) : stream(file_buff) {
#ifdef _DEBUG
	module_name = "Writer";
#endif
}

Writer::Writer(Writer &writer) : stream(writer.stream.rdbuf()) {
#ifdef _DEBUG
	module_name = "Writer";
#endif
}

Writer::~Writer() {
	
}

Writer &Writer::operator=(Writer &writer) {
#ifdef _DEBUG
	module_name = "Writer";
	function = "operator=";
	line_number = "55 - 63";
#endif
	Writer w =  *new Writer(writer);
	return w;
}

inline void Writer::seek(int position) {
#ifdef _DEBUG
	module_name = "Writer";
	function = "seek";
	line_number = "65 - 72";
#endif
    stream.seekp(0, position);  
}

inline void Writer::seek(int position, int origin) {
#ifdef _DEBUG
	module_name = "Writer";
	function = "seek";
	line_number = "74 - 81";
#endif
    stream.seekp(origin, position);  
}

inline void Writer::seek(unsigned int position) {
#ifdef _DEBUG
	module_name = "Writer";
	function = "seek";
	line_number = "83 - 90";
#endif
	stream.seekp(0, position);
}

inline void Writer::seek(unsigned int position, unsigned int origin) {
#ifdef _DEBUG
	module_name = "Writer";
	function = "seek";
	line_number = "92 - 99";
#endif
	stream.seekp(origin, position);
}

inline void Writer::seek(std::streampos position) {
#ifdef _DEBUG
	module_name = "Writer";
	function = "seek";
	line_number = "101 - 108";
#endif
	stream.seekp(0, position);
}

inline void Writer::seek(std::streampos position, std::streampos origin) {
#ifdef _DEBUG
	module_name = "Writer";
	function = "seek";
	line_number = "110 - 117";
#endif
	stream.seekp(origin, position);
}

void Writer::write(char *bytes) {
#ifdef _DEBUG
	module_name = "Writer";
	function = "write";
	line_number = "119 - 126";
#endif
	stream.write(bytes, strlen(bytes));
}

void Writer::write(unsigned char *bytes) {
#ifdef _DEBUG
	module_name = "Writer";
	function = "write";
	line_number = "128 - 135";
#endif
	stream.write(reinterpret_cast<char *>(bytes), strlen(reinterpret_cast<char *>(bytes)));
}

void Writer::write_int_8(int8_t value) {
#ifdef _DEBUG
	module_name = "Writer";
	function = "write_int_8";
	line_number = "137 - 144";
#endif
	stream.put(value & 0xFF);
}

void Writer::write_uint_8(uint8_t value) {
#ifdef _DEBUG
	module_name = "Writer";
	function = "write_uint_8";
	line_number = "146 - 153";
#endif
	stream.put(value & 0xFF);
}

void Writer::write_int_16(int16_t val) {
#ifdef _DEBUG
	module_name = "Writer";
	function = "write_int_16";
	line_number = "155 - 171";
#endif
	// We'll have it write byte by byte as it's easier then sorting out a array.
	if (val <= 9) {
		write_byte(unsigned char(0x01));
		write_byte(unsigned char(0x00));
	} else {
		unsigned char uchar1 = unsigned char((val >> 0) & 0xFF);
		write_byte(uchar1);
		unsigned char uchar2 = unsigned char((val >> 8) & 0xFF);
		write_byte(uchar2);
	}
}

void Writer::write_int_16_be(int16_t val) {
#ifdef _DEBUG
	module_name = "Writer";
	function = "write_int_16_be";
	line_number = "173 - 188";
#endif
	if (val == 1) {
		write_byte(unsigned char(0x00));
		write_byte(unsigned char(0x01));
	} else {
		unsigned char uchar1 = unsigned char((val >> 8) & 0xFF);
		write_byte(uchar1);
		unsigned char uchar2 = unsigned char((val >> 0) & 0xFF);
		write_byte(uchar2);
	}
}

void Writer::write_uint_16(uint16_t val) {
	// We'll have it write byte by byte as it's easier then sorting out a array.
#ifdef _DEBUG
	module_name = "Writer";
	function = "write_uint_16";
	line_number = "190 - 207";
#endif
	if (val <= 9 && val >= 0) {
		unsigned char uchar1 = unsigned char(val);
		write_byte(uchar1);
		write_byte(unsigned char(0x00));
	} else {
		unsigned char uchar1 = unsigned char((val >> 0) & 0xFF);
		write_byte(uchar1);
		unsigned char uchar2 = unsigned char((val >> 8) & 0xFF);
		write_byte(uchar2);
	}
}

void Writer::write_uint_16_be(uint16_t val) {
	// We'll have it write byte by byte as it's easier then sorting out a array.
#ifdef _DEBUG
	module_name = "Writer";
	function = "write_uint_16_be";
	line_number = "209 - 226";
#endif
	if (val <= 9 && val >= 0) {
		write_byte(unsigned char(0x00));
		unsigned char uchar1 = unsigned char(val);
		write_byte(uchar1);
	} else {
		unsigned char uchar1 = unsigned char((val >> 8) & 0xFF);
		write_byte(uchar1);
		unsigned char uchar2 = unsigned char((val >> 0) & 0xFF);
		write_byte(uchar2);
	}
}

void Writer::write_int_32(int val) {
	// We'll have it write byte by byte as it's easier then sorting out a array.
#ifdef _DEBUG
	module_name = "Writer";
	function = "write_int_32";
	line_number = "228 - 250";
#endif
	if (val == 1) {
		write_byte(unsigned char(0x01));
		write_byte(unsigned char(0x00));
		write_byte(unsigned char(0x00));
		write_byte(unsigned char(0x00));
	} else {
		unsigned char uchar1 = unsigned char((val >> 0) & 0xFF);
		write_byte(uchar1);
		unsigned char uchar2 = unsigned char((val >> 8) & 0xFF);
		write_byte(uchar2);
		unsigned char uchar3 = unsigned char((val >> 16) & 0xFF);
		write_byte(uchar3);
		unsigned char uchar4 = unsigned char((val >> 24) & 0xFF);
		write_byte(uchar4);
	}
}

void Writer::write_int_32_be(int val) {
#ifdef _DEBUG
	module_name = "Writer";
	function = "write_int_32_be";
	line_number = "252 - 273";
#endif
	if (val == 1) {
		write_byte(unsigned char(0x00));
		write_byte(unsigned char(0x00));
		write_byte(unsigned char(0x00));
		write_byte(unsigned char(0x01));
	} else {
		unsigned char uchar1 = unsigned char((val >> 24) & 0xFF);
		write_byte(uchar1);
		unsigned char uchar2 = unsigned char((val >> 16) & 0xFF);
		write_byte(uchar2);
		unsigned char uchar3 = unsigned char((val >> 8) & 0xFF);
		write_byte(uchar3);
		unsigned char uchar4 = unsigned char((val >> 0) & 0xFF);
		write_byte(uchar4);
	}
}

void Writer::write_uint_32(unsigned int val) {
	// We'll have it write byte by byte as it's easier then sorting out a array.
#ifdef _DEBUG
	module_name = "Writer";
	function = "write_uint_32";
	line_number = "275 - 298";
#endif
	if (val <= 9 && val >= 0) {
		unsigned char uchar1 = unsigned char(val);
		write_byte(uchar1);
		write_byte(unsigned char(0x00));
		write_byte(unsigned char(0x00));
		write_byte(unsigned char(0x00));
	} else {
		unsigned char uchar1 = unsigned char((val >> 0) & 0xFF);
		write_byte(uchar1);
		unsigned char uchar2 = unsigned char((val >> 8) & 0xFF);
		write_byte(uchar2);
		unsigned char uchar3 = unsigned char((val >> 16) & 0xFF);
		write_byte(uchar3);
		unsigned char uchar4 = unsigned char((val >> 24) & 0xFF);
		write_byte(uchar4);
	}
}

void Writer::write_uint_32_be(unsigned int val) {
	// We'll have it write byte by byte as it's easier then sorting out a array.
#ifdef _DEBUG
	module_name = "Writer";
	function = "write_uint_32_be";
	line_number = "300 - 323";
#endif
	if (val <= 9 && val >= 0) {
		write_byte(unsigned char(0x00));
		write_byte(unsigned char(0x00));
		write_byte(unsigned char(0x00));
		unsigned char uchar1 = unsigned char(val);
		write_byte(uchar1);
	} else {
		unsigned char uchar1 = unsigned char((val >> 24) & 0xFF);
		write_byte(uchar1);
		unsigned char uchar2 = unsigned char((val >> 16) & 0xFF);
		write_byte(uchar2);
		unsigned char uchar3 = unsigned char((val >> 8) & 0xFF);
		write_byte(uchar3);
		unsigned char uchar4 = unsigned char((val >> 0) & 0xFF);
		write_byte(uchar4);
	}
}

void Writer::write_rsdk_string(char *string) {
#ifdef _DEBUG
	module_name = "Writer";
	function = "write_rsdk_string";
	line_number = "325 - 333";
#endif
	write_byte(__int8(strlen(string)));
    stream.write(string, strlen(string));
}

void Writer::write_rsdk_string(std::string string) {
#ifdef _DEBUG
	module_name = "Writer";
	function = "write_rsdk_string";
	line_number = "335 - 346";
#endif
	unsigned int size = string.size();
	char *n_char = new char[size + 1];
	std::strcpy(n_char, string.c_str());
	write_rsdk_string(n_char);
	delete[] n_char;
}

void Writer::write_rsdk_unicode_string(char *string) {
#ifdef _DEBUG
	module_name = "Writer";
	function = "write_rsdk_unicode_string";
	line_number = "348 - 356";
#endif
	write_byte(__int8(strlen(string)));
    stream.write(string, strlen(string));
}

void Writer::write_rsdk_unicode_string(std::string string) {
#ifdef _DEBUG
	module_name = "Writer";
	function = "write_rsdk_unicode_string";
	line_number = "358 - 369";
#endif
	unsigned int size = string.size();
	char *n_char = new char[size + 1];
	std::strcpy(n_char, string.c_str());
	write_rsdk_unicode_string(n_char);
	delete[] n_char;
}

void Writer::write_padding(unsigned int amount) {
#ifdef _DEBUG
	module_name = "Writer";
	function = "write_padding";
	line_number = "371 - 380";
#endif
	for (unsigned int i = 0; i < amount; ++i) {
		write_byte(uint8_t(0x00));
	}
}

void Writer::write_byte(__int8 byte) {
#ifdef _DEBUG
	module_name = "Writer";
	function = "write_byte";
	line_number = "382 - 389";
#endif
	stream.put(byte);
}

void Writer::write_byte(uint8_t byte) {
#ifdef _DEBUG
	module_name = "Writer";
	function = "write_byte";
	line_number = "391 - 397";
#endif
	stream.put(byte);
}

void Writer::write_byte(unsigned short byte) {
#ifdef _DEBUG
	module_name = "Writer";
	function = "write_byte";
	line_number = "400 - 407";
#endif
	stream.put(byte);
}

void Writer::write_bytes(char *bytes) {
#ifdef _DEBUG
	module_name = "Writer";
	function = "write_bytes";
	line_number = "409 - 418";
#endif
	for (unsigned int i = 0; i < strlen(bytes); ++i) {
		stream.put(unsigned char(bytes[i]));
	}
}

void Writer::write_bytes(unsigned char *bytes) {
#ifdef _DEBUG
	module_name = "Writer";
	function = "write_bytes";
	line_number = "420 - 429";
#endif
	for (unsigned int i = 0; i < strlen(bytes); ++i) {
		stream.put(unsigned char(bytes[i]));
	}
}

void Writer::write_compressed(std::string bytes) {
#ifdef _DEBUG
	module_name = "Writer";
	function = "write_compressed";
	line_number = "431 - 443";
#endif
	std::string compressed_data = compress_string(bytes, Z_DEFAULT_STRATEGY);
	char *compressed_bytes = stringtochar(compressed_data);
	write_uint_32(compressed_data.length());
	write_uint_32_be(bytes.length());
	stream.write(compressed_bytes, compressed_data.length());
    delete[] compressed_bytes;
}

void Writer::write_compressed(unsigned char *bytes) {
#ifdef _DEBUG
	module_name = "Writer";
	function = "write_compressed";
	line_number = "445 - 451";
#endif
	write_compressed(reinterpret_cast<char *>(bytes));
}

std::iostream &Writer::get_stream() {
#ifdef _DEBUG
	module_name = "Writer";
	function = "get_stream";
	line_number = "454 - 461";
#endif
	return stream;
}

bool Writer::is_eof() {
#ifdef _DEBUG
	module_name = "Writer";
	function = "is_eof";
	line_number = "463 - 470";
#endif
    return stream.eof();
}

inline std::streampos Writer::pos() {
#ifdef _DEBUG
	module_name = "Writer";
	function = "pos";
	line_number = "472 - 479";
#endif
    return stream.tellp();
}

unsigned int Writer::size() { 
#ifdef _DEBUG
	module_name = "Writer";
	function = "size";
	line_number = "481 - 493";
#endif
	std::streampos original_position = pos();
    seek(0, stream.end);
	std::streampos stream_length = pos();
    seek(original_position);
    
    return stream_length;
}