#pragma once



#ifdef __cplusplus
extern "C" 
{  
#endif

	__declspec(dllimport) void base64_encode(const void* in_data, int in_length, char** out_data, int& out_length);
	__declspec(dllimport) void base64_decode(const void* in_data, int in_length, unsigned char** out_data, int& out_length);

	__declspec(dllimport) bool base64_encode_text_file(const char* in_filename, const char* out_filename);
	__declspec(dllimport) bool base64_decode_text_file(const char* in_filename, const char* out_filename);

	__declspec(dllimport) bool aes_cbc_create_key(const char* out_filename);
	__declspec(dllimport) bool aes_cbc_encode_to_file(const char* in_filename_data, const char* in_filename_key, const char* out_filename_data);
	__declspec(dllimport) bool aes_cbc_decode_to_file(const char* in_filename_data, const char* in_filename_key, const char* out_filename_data);
	__declspec(dllimport) int  aes_cbc_decode_to_str(const char* in_filename_data, const char* in_filename_key, char* out_decoded_data);

#ifdef __cplusplus
}
#endif
