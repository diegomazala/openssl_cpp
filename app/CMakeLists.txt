cmake_minimum_required(VERSION 3.9)

if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

include_directories(${OPENSSLPP_INCLUDE})

set(LINK_LIBRARIES 
	openssl_cpp 
    ${OPENSSLPP_ADDITIONAL_LIBS}
    ${OPENSSL_CRYPTO_LIBRARY})


###########################################################################
#
# app_aes_cbc
#
project(app_aes_cbc)
add_executable(${PROJECT_NAME} app_aes_cbc.cpp)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_link_libraries(${PROJECT_NAME} ${LINK_LIBRARIES})


###########################################################################
#
# app_aes_gcm
#
project(app_aes_gcm)
add_executable(${PROJECT_NAME} app_aes_gcm.cpp)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_link_libraries(${PROJECT_NAME} ${LINK_LIBRARIES})


###########################################################################
#
# app_base64
#
project(app_base64)
add_executable(${PROJECT_NAME} app_base64.cpp)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_link_libraries(${PROJECT_NAME} ${LINK_LIBRARIES})


###########################################################################
#
# app_rsa
#
project(app_rsa)
add_executable(${PROJECT_NAME} app_rsa.cpp)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_link_libraries(${PROJECT_NAME} ${LINK_LIBRARIES})


###########################################################################
#
# app_sha
#
project(app_sha)
add_executable(${PROJECT_NAME} app_sha.cpp)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_link_libraries(${PROJECT_NAME} ${LINK_LIBRARIES})
