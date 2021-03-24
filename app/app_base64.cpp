
#include <opensslpp/base64.h>
// uncomment to disable assert()
// #define NDEBUG
#include <cassert>
#include <iostream>

int main()
{
    const std::vector<uint8_t> data = { 1, 2, 3, 4, 5 };

    {
        const auto encoded = opensslpp::Base64::encode(data);
        const auto decoded = opensslpp::Base64::decode(encoded);

        assert(data == decoded);

        std::cout << "data   : ";
		for (auto v : data) std::cout << v;
		std::cout << std::endl;

		std::cout << "encoded: ";
		for (auto v : encoded) std::cout << v;
		std::cout << std::endl;

		std::cout << "decoded: ";
		for (auto v : decoded) std::cout << v;
		std::cout << std::endl;
    }

    {
        std::vector<uint8_t> decoded(data.size());

        const auto encoded = opensslpp::Base64::encode(data.data(), data.size());
        const auto size = opensslpp::Base64::decode(encoded, decoded.data(), decoded.size());

        assert(size == decoded.size());
        assert(data == decoded);

		std::cout << "decoded: ";
		for (auto v : decoded) std::cout << v;
		std::cout << std::endl;

		std::cout << "encoded: ";
		for (auto v : encoded) std::cout << v;
		std::cout << std::endl;

		std::cout << "size   : " << size << std::endl;
    }

    return EXIT_SUCCESS;
}
