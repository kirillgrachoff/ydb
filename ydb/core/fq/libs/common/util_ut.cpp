#include "util.cpp"

#include <library/cpp/testing/unittest/registar.h>

namespace NFq {

Y_UNIT_TEST_SUITE(EscapingBasics) {
    Y_UNIT_TEST(EncloseSecretShouldWork) {
        UNIT_ASSERT_VALUES_EQUAL(EncloseSecret("some_secret1"), "/* 51a91b5d91a99eb7 */some_secret1/* e87c9b191b202354 */");
    }

    Y_UNIT_TEST(HideSecretsShouldWork) {
        UNIT_ASSERT_VALUES_EQUAL(HideSecrets("some text"), "some text");
        UNIT_ASSERT_VALUES_EQUAL(HideSecrets("/* 51a91b5d91a99eb7 */some_secret1/* e87c9b191b202354 */"), "/*SECRET*/");
        UNIT_ASSERT_VALUES_EQUAL(HideSecrets("/* 51a91b5d91a99eb7 */some_secret1/* e87c9b191b202354 */\n/* 51a91b5d91a99eb7 */some_secret2/* e87c9b191b202354 */"), "/*SECRET*/\n/*SECRET*/");
    }

    Y_UNIT_TEST(HideSecretsOverEncloseSecretShouldWork) {
        UNIT_ASSERT_VALUES_EQUAL(HideSecrets(EncloseSecret("some_secret1")), "/*SECRET*/");
    }

    Y_UNIT_TEST(EscapeStringShouldWork) {
        UNIT_ASSERT_VALUES_EQUAL(EscapeString("some_secret1", '"'), "some_secret1");
        UNIT_ASSERT_VALUES_EQUAL(EscapeString("some_secret1", "}+{", "[*]"), "some_secret1");
        UNIT_ASSERT_VALUES_EQUAL(EscapeString("some\"_\"secret1", '"'), "some\\\"_\\\"secret1");
        UNIT_ASSERT_VALUES_EQUAL(EscapeString("some}+{_}+{secret1", "}+{", "[*]"), "some[*]_[*]secret1");
    }

    Y_UNIT_TEST(EncloseAndEscapeStringShouldWork) {
        UNIT_ASSERT_VALUES_EQUAL(EncloseAndEscapeString("some_secret1", '"'), "\"some_secret1\"");
        UNIT_ASSERT_VALUES_EQUAL(EncloseAndEscapeString("some_secret1\nsome_secret2", "}+{", "[*]"), "}+{some_secret1\nsome_secret2}+{");

        UNIT_ASSERT_VALUES_EQUAL(EncloseAndEscapeString("some\"_\"secret1", '"'), "\"some\\\"_\\\"secret1\"");
        UNIT_ASSERT_VALUES_EQUAL(EncloseAndEscapeString("some_secret1}+{\n}+{some_secret2", "}+{", "[*]"), "}+{some_secret1[*]\n[*]some_secret2}+{");
    }
}
} // NFq
