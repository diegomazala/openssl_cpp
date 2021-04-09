cmake_minimum_required(VERSION 3.4)

project(openssl_cpp_crypto)

set(CMAKE_CXX_STANDARD 14)

if(MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /W4")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /W4")
    set(OPENSSLPP_ADDITIONAL_LIBS Ws2_32 crypt32)
else()
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Wpedantic")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wpedantic")
endif()

get_filename_component(OPENSSLPP_ROOT "${CMAKE_CURRENT_LIST_DIR}" ABSOLUTE)

set(OPENSSLPP_INCLUDE "${OPENSSLPP_ROOT}/include")
include_directories(${OPENSSLPP_INCLUDE})

set(OPENSSL_MSVC_STATIC_RT ON)
set(OPENSSL_USE_STATIC_LIBS ON)


find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})



find_package(Threads)
if (NOT Threads_FOUND)
    message(Warning " Threads was not found. Some projects will not be built")
endif()



set(OPENSSLPP_HEADERS "${OPENSSLPP_INCLUDE}/opensslpp")

set(HEADERS
    ${OPENSSLPP_HEADERS}/aes_cbc.h
    ${OPENSSLPP_HEADERS}/aes_gcm.h
    ${OPENSSLPP_HEADERS}/rsa.h
    ${OPENSSLPP_HEADERS}/sha.h

    ${OPENSSLPP_HEADERS}/base64.h
    ${OPENSSLPP_HEADERS}/random.h

    ${OPENSSLPP_HEADERS}/details/common.h

    ${OPENSSLPP_HEADERS}/crypto.h
    ${OPENSSLPP_HEADERS}/crypto.cpp
    )

add_library(${PROJECT_NAME} SHARED ${HEADERS})
target_link_libraries(${PROJECT_NAME} ${OPENSSLPP_ADDITIONAL_LIBS} ${OPENSSL_CRYPTO_LIBRARY})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)




###########################################################################
#
# build lib
#
set(LIB_NAME openssl_cpp)
add_library(${LIB_NAME} INTERFACE)
target_include_directories(${LIB_NAME} INTERFACE ${OPENSSL_INCLUDE_DIR})
target_sources(${LIB_NAME} INTERFACE ${HEADERS})



###########################################################################
#
# build apps with usage sample code
#
add_subdirectory(app)


