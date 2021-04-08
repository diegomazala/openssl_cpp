#pragma once



#ifdef __cplusplus
extern "C" 
{  
#endif

	__declspec(dllimport) void base64_encode(const void* in_data, int in_length, char** out_data, int& out_length);
	__declspec(dllimport) void base64_decode(const void* in_data, int in_length, unsigned char** out_data, int& out_length);

	__declspec(dllimport) bool base64_encode_text_file(const char* in_filename, const char* out_filename);
	__declspec(dllimport) bool base64_decode_text_file(const char* in_filename, const char* out_filename);

#ifdef __cplusplus
}
#endif
