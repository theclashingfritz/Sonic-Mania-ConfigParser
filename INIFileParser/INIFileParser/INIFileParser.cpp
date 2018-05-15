#include "INIFileParser.h"
#include <zlib.h>
#include <assert.h>

#ifdef _DEBUG
void debug_term_func() {

	if (module_name != "NO_MODULE" || (function != "NO_FUNCTION" && line_number != "NO_LINE_NUMBER")) {
		std::cout << "WARNING: The line number area may be off due to code changes and a lack of code cleanups." << std::endl;
		std::cout << "Along with that, The module name and function can be completely wrong if the exception was thrown in a area with" << std::endl;
		std::cout << "no support for this custom exception handler. So take the info here as a good starting point and not a definite answer.\n" << std::endl;

		std::cout << "An exception occurred in '" << module_name << "' at function '" << function << "' and close to line number " << line_number << "!" << std::endl;
	}

	exit(-1);
}
#endif

size_t __cdecl strlen(const unsigned char *str) {
	const unsigned char* eos = str;

	while (*eos++);

	return (eos - str - 1);
}

size_t __cdecl strlcpy(char *dst, const char *src, size_t siz) {
	register char *d = dst;
	register const char *s = src;
	register size_t n = siz;

	/* Copy as many bytes as will fit */
	if (n != 0 && --n != 0) {
		do {
			if ((*d++ = *s++) == 0)
				break;
		} while (--n != 0);
	}

	/* Not enough room in dst, add NUL and traverse rest of src */
	if (n == 0) {
		if (siz != 0)
			*d = '\0';		/* NUL-terminate dst */
		while (*s++)
			;
	}

	return(s - src - 1);	/* count does not include NUL */
}

size_t __cdecl strlcpy(unsigned char *dst, unsigned const char *src, size_t siz) {
	register unsigned char *d = dst;
	register unsigned const char *s = src;
	register size_t n = siz;

	/* Copy as many bytes as will fit */
	if (n != 0 && --n != 0) {
		do {
			if ((*d++ = *s++) == 0)
				break;
		} while (--n != 0);
	}

	/* Not enough room in dst, add NUL and traverse rest of src */
	if (n == 0) {
		if (siz != 0)
			*d = '\0';		/* NUL-terminate dst */
		while (*s++)
			;
	}

	return(s - src - 1);	/* count does not include NUL */
}

/** Compress a STL string using zlib with given compression level and return
* the binary data. */
EXPORT std::string compress_string(const std::string& str, int compressionlevel) {
	z_stream zs;                        // z_stream is zlib's control structure
	memset(&zs, 0, sizeof(zs));

	zs.next_in = (Bytef*)str.data();
	zs.avail_in = str.size();           // set the z_stream's input

	int retval = 0;
	int ret;
	std::string result = std::string();
	std::string input = std::string(str);

	char *in_ = new char[ZLIB_COMPLETE_CHUNK];
	char *out_ = new char[ZLIB_COMPLETE_CHUNK];
	out_[0] = '\0';

	z_stream strm_ = zs;

	strm_.zalloc = Z_NULL;
	strm_.zfree = Z_NULL;
	strm_.opaque = Z_NULL;
	strm_.avail_in = 0;
	strm_.next_in = Z_NULL;

	int level = compressionlevel;

	if (level < 1 || level > 9) {
		level = 9;
	}
	const int memLevel = 9;
	retval = deflateInit2(&strm_, level, Z_DEFLATED, 10, memLevel, Z_DEFAULT_STRATEGY);
	if (retval != Z_OK) {
		throw(std::runtime_error("deflateInit failed while compressing."));
	}

	bool autoFlush_ = true;

	for (uint32_t i = 0; i < input.length(); i += ZLIB_COMPLETE_CHUNK) {
		int howManyLeft = input.length() - i;
		bool isLastRound = (howManyLeft <= ZLIB_COMPLETE_CHUNK);
		int howManyWanted = (howManyLeft > ZLIB_COMPLETE_CHUNK) ?
			ZLIB_COMPLETE_CHUNK : howManyLeft;
		memcpy(in_, input.data() + i, howManyWanted);
		strm_.avail_in = howManyWanted;
		strm_.next_in = (Bytef *)in_;
		do {
			int have;
			strm_.avail_out = ZLIB_COMPLETE_CHUNK;
			strm_.next_out = (Bytef *)out_;
			retval = deflate(&strm_, (autoFlush_ && isLastRound) ? Z_SYNC_FLUSH : Z_NO_FLUSH);
			if (retval == Z_STREAM_ERROR) {
				throw std::bad_alloc();
			}
			have = ZLIB_COMPLETE_CHUNK - strm_.avail_out;
			result += std::string(out_, have);
		} while (strm_.avail_out == 0);
	}
	std::string outstring = std::string(result);

	ret = retval;

	deflateEnd(&strm_);

	delete[] in_;
	delete[] out_;

	if (ret != Z_OK) {          // an error occurred
		std::string error_msg = "Exception during zlib compression: ";
		error_msg.append(zs.msg);
		throw(std::runtime_error(error_msg));
	}

	return outstring;
}

/** Decompress an STL string using zlib and return the original data. */
EXPORT std::string decompress_string(const std::string& str) {
	z_stream zs;                        // z_stream is zlib's control structure
	memset(&zs, 0, sizeof(zs));

	int retval = 0;
	int ret;
	std::string result = std::string();
	std::string input = std::string(str);

	char *in_ = new char[ZLIB_COMPLETE_CHUNK];
	char *out_ = new char[ZLIB_COMPLETE_CHUNK];
	out_[0] = '\0';

	z_stream strm_ = zs;

	strm_.zalloc = Z_NULL;
	strm_.zfree = Z_NULL;
	strm_.opaque = Z_NULL;
	strm_.avail_in = 0;
	strm_.next_in = Z_NULL;

	retval = inflateInit2(&strm_, 0);
	if (retval != Z_OK) {
		throw(std::runtime_error("inflateInit failed while decompressing."));
	}

	for (uint32_t i = 0; i < input.length(); i += ZLIB_COMPLETE_CHUNK) {
		int howManyLeft = input.length() - i;
		int howManyWanted = (howManyLeft > ZLIB_COMPLETE_CHUNK) ?
			ZLIB_COMPLETE_CHUNK : howManyLeft;
		memcpy(in_, input.data() + i, howManyWanted);
		strm_.avail_in = howManyWanted;
		strm_.next_in = (Bytef *)in_;
		if (strm_.avail_in == 0) {
			break;
		}
		do {
			int have;
			strm_.avail_out = ZLIB_COMPLETE_CHUNK;
			strm_.next_out = (Bytef *)out_;
			retval = inflate(&strm_, 0);
			if (retval == Z_STREAM_ERROR) {
				throw std::bad_alloc();
			}
			have = ZLIB_COMPLETE_CHUNK - strm_.avail_out;
			result += std::string(out_, have);
		} while (strm_.avail_out == 0);
	}
	std::string outstring = std::string(result);

	ret = retval;

	inflateEnd(&zs);

	delete[] in_;
	delete[] out_;

	if (ret != Z_OK && ret != Z_STREAM_END) {          // an error occurred
		std::string error_msg;
		if (zs.msg != nullptr) {
			error_msg = "Exception during zlib decompression: ";
			error_msg.append(zs.msg);
		} else {
			error_msg = "Exception during zlib decompression! Error code is: ";
			error_msg.append(std::to_string(ret));
		}
		throw(std::runtime_error(error_msg));
	}

	return outstring;
}

EXPORT inline char *stringtochar(const std::string& str) {
	size_t size = str.size();
	char *char_string = new char[size + 1];
	memcpy(char_string, str.data(), size);
	char_string[size] = '\0';
	return char_string;
}

EXPORT inline unsigned char *stringtouchar(const std::string& str) {
	size_t size = str.size();
	unsigned char *uchar_string = new unsigned char[size + 1];
	memcpy((char *)uchar_string, str.data(), size);
	uchar_string[size] = '\0';
	return uchar_string;
}


#ifdef _WIN32
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
	switch (ul_reason_for_call) {
		case DLL_PROCESS_ATTACH:
#ifdef _DEBUG
			std::set_terminate(debug_term_func);
#endif
			break;
		case DLL_PROCESS_DETACH:
			break;
	}
	return TRUE;
}
#endif