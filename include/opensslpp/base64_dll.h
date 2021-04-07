#pragma once



#ifdef __cplusplus
extern "C" 
{  
#endif

	__declspec(dllimport) void base64_encode(const void* in_data, int in_length, char** out_data, int& out_length);
	__declspec(dllimport) void base64_decode(const void* in_data, int in_length, unsigned char** out_data, int& out_length);

#ifdef __cplusplus
}
#endif
