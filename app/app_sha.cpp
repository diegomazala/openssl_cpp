#include <opensslpp/sha.h>
// uncomment to disable assert()
// #define NDEBUG
#include <cassert>
#include <iostream>

void test_sha256()
{
    opensslpp::Sha256::Digest digest1;
    assert(opensslpp::Sha256::calculate("test1", digest1));

    opensslpp::Sha256::Digest digest2;
    assert(opensslpp::Sha256::calculate("test2", digest2));

    opensslpp::Sha256::Digest digest3;
    assert(opensslpp::Sha256::calculate("test1", digest3));

    assert(digest1 == digest3);
    assert(digest1 != digest2);

    auto base1 = opensslpp::Sha256::toBase64(digest1);
    auto base2 = opensslpp::Sha256::toBase64(digest2);
    auto base3 = opensslpp::Sha256::toBase64(digest3);

    assert(base1 == base3);
    assert(base1 != base2);

    auto d1 = opensslpp::Sha256::fromBase64(base1);
    auto d2 = opensslpp::Sha256::fromBase64(base2);
    auto d3 = opensslpp::Sha256::fromBase64(base3);

    assert(d1 == d3);
    assert(d1 != d2);
}

void test_sha512()
{
    opensslpp::Sha512::Digest digest1;
    assert(opensslpp::Sha512::calculate("test1", digest1));

    opensslpp::Sha512::Digest digest2;
    assert(opensslpp::Sha512::calculate("test2", digest2));

    opensslpp::Sha512::Digest digest3;
    assert(opensslpp::Sha512::calculate("test1", digest3));

    assert(digest1 == digest3);
    assert(digest1 != digest2);

    auto base1 = opensslpp::Sha512::toBase64(digest1);
    auto base2 = opensslpp::Sha512::toBase64(digest2);
    auto base3 = opensslpp::Sha512::toBase64(digest3);

    assert(base1 == base3);
    assert(base1 != base2);

    auto d1 = opensslpp::Sha512::fromBase64(base1);
    auto d2 = opensslpp::Sha512::fromBase64(base2);
    auto d3 = opensslpp::Sha512::fromBase64(base3);

    assert(d1 == d3);
    assert(d1 != d2);
}

int main()
{
    test_sha256();
    test_sha512();
    return EXIT_SUCCESS;
}