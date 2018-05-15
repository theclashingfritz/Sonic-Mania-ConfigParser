#pragma once

// Windows Header Files:

#ifdef _WIN32
#include <windows.h>
#endif

#include <eh.h>  
#include <process.h>  
#include <string>
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <exception>

#define ZLIB_COMPLETE_CHUNK 16384
#define MAX_SIZE 16384

#include <zlib.h>

#ifdef _DEBUG
	#pragma warning( disable : 4251 4154 4244 4267 4018)
#else
	#pragma warning( disable : 4154 4244 4267 4018)
#endif

#ifdef INIFileParser_Building
	#define EXPORT __declspec( dllexport )
#else 
	#define EXPORT __declspec( dllimport ) 
#endif 

#ifdef _DEBUG
static std::string module_name = "NO_MODULE";
static std::string function = "NO_FUNCTION";
static std::string line_number = "NO_LINE_NUMBER";

EXPORT void debug_term_func();
#endif

size_t __cdecl strlen(const unsigned char *str);
size_t __cdecl strlcpy(char *dst, const char *src, size_t siz);
size_t __cdecl strlcpy(unsigned char *dst, unsigned const char *src, size_t siz);

EXPORT std::string compress_string(const std::string& str, int compressionlevel);
EXPORT std::string decompress_string(const std::string& str);

EXPORT inline char *stringtochar(const std::string& str);
EXPORT inline unsigned char *stringtouchar(const std::string& str);