/**********************************************************************
 * Copyright (c) 2019 Marko Bencun                                    *
 * Distributed under the MIT software license, see the accompanying   *
 * file COPYING or http://www.opensource.org/licenses/mit-license.php.*
 **********************************************************************/

#ifndef SECP256K1_MODULE_ECDSA_SIGN_TO_CONTRACT_TESTS_H
#define SECP256K1_MODULE_ECDSA_SIGN_TO_CONTRACT_TESTS_H

static int nonce_function_non_rfc6979(unsigned char *nonce32, const unsigned char *msg32, const unsigned char *key32, const unsigned char *algo16, void *data, unsigned int counter) {
    (void)msg32;
    (void)key32;
    (void)algo16;
    (void)data;
    (void)counter;
    memset(nonce32, 0x55, 32);
    return 1;
}

typedef struct {
    unsigned char s2c_data[32];
    unsigned char ndata[32];
    int use_ndata;
    /* host_commitment = sha256(<s2c_data><ndata>) */
    unsigned char host_commitment[32];
    /* expected_pubnonce = host_commitment*G */
    unsigned char expected_pubnonce[33];
} ecdsa_s2c_test;

/* When using sign-to-contract commitments, the nonce function is fixed, so we can use fixtures to test. */
static ecdsa_s2c_test ecdsa_s2c_tests[] = {
    {
        "\x1b\xf6\xfb\x42\xf4\x1e\xb8\x76\xc4\xd7\xaa\x0d\x67\x24\x2b\x00\xba\xab\x99\xdc\x20\x84\x49\x3e\x4e\x63\x27\x7f\xa1\xf7\x7f\x22",
        "\x2a\xb1\x69\x23\x8a\x31\x7c\xc1\x15\xa3\x67\xd2\x38\x7b\x69\x4d\xe8\xc7\x6c\x59\xd4\x93\xf5\xb3\x88\xf9\xdd\x6e\xd0\xa3\x5a\x4d",
        1,
        "\x73\xcf\xba\xfa\x5d\x58\x0b\xe6\xf1\x63\x30\x51\x30\x9b\x27\x02\x7d\x00\xe3\x36\x44\xac\x5c\x04\xea\x12\x6e\xb6\xae\xc2\x45\x8e",
        "\x03\x18\xad\xda\xa7\x6f\x72\x65\xe2\x74\x95\x0b\xca\x10\x43\x52\x51\x67\xd1\x19\x17\x34\x4f\xce\x4e\xa0\x05\x17\x63\x8a\x88\x04\xf6",
    },
    {
        "\x1b\xf6\xfb\x42\xf4\x1e\xb8\x76\xc4\xd7\xaa\x0d\x67\x24\x2b\x00\xba\xab\x99\xdc\x20\x84\x49\x3e\x4e\x63\x27\x7f\xa1\xf7\x7f\x22",
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00",
        0,
        "\xcd\xfe\xb3\xad\x27\x00\x21\x9e\xf7\xe1\xd3\x48\x3e\x31\xe0\xbf\x19\x34\x50\xb3\x77\x41\x58\xaa\x5d\x0f\x95\xb9\xb6\x5b\xaf\xc2",
        "\x02\x3d\xce\xb4\xef\x0d\x4f\x59\x98\xf2\xd3\x02\xdb\xfb\x17\x86\x24\xf6\x3e\x17\x5c\xd2\x13\xf5\xf8\x9a\x30\xce\xe4\x50\x17\x4c\x07",
    },
    {
        "\x35\x19\x9a\x8f\xbf\x84\xad\x6e\xf6\x9a\x18\x4c\x1b\x19\x28\x5b\xef\xbe\x06\xe6\x0b\x62\x64\xe6\xd3\x73\x89\x3f\x68\x55\xe2\x4a",
        "\x8b\x52\x2b\x64\x5e\xf8\x68\x9e\x78\xec\xe6\x5a\x9d\x44\xfc\x83\xe0\x8e\x16\x0d\xe5\x30\x92\xeb\x94\x0d\xc1\x2f\xa5\xb5\xef\x6b",
        1,
        "\x17\x34\x99\x44\x6c\xae\x65\xcf\x66\xfa\x8c\xb8\x41\x1d\xc6\xe9\x9b\x5e\xac\x96\x3c\x39\x70\x0b\x27\xe5\x1f\xea\x78\x93\x0a\x8e",
        "\x03\x45\x7e\xe7\xb1\x82\x5b\xc4\x10\x21\xda\x85\x59\x0b\x46\xd9\xc6\xfa\x04\x98\x74\xbd\x9d\x8b\x2e\x60\x7a\x42\x98\x54\xac\x23\x57",
    },
    {
        "\x35\x19\x9a\x8f\xbf\x84\xad\x6e\xf6\x9a\x18\x4c\x1b\x19\x28\x5b\xef\xbe\x06\xe6\x0b\x62\x64\xe6\xd3\x73\x89\x3f\x68\x55\xe2\x4a",
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00",
        0,
        "\x87\x62\x71\xd6\xfd\xc7\x57\x5a\x44\xb9\x81\x0a\xb2\xea\x8f\x54\xb5\x77\xe3\x35\x86\xb3\x4c\x0d\xc5\xf3\x5f\xf6\xbd\xb8\xeb\x6c",
        "\x02\x61\x10\x22\x34\xd2\x03\xe6\x11\xaa\xe7\x1e\x4e\x04\x30\xc2\xf1\x28\x6d\x9c\x2f\x4c\x96\x4f\x54\x0d\x03\x5c\xed\x94\xd7\x42\x6f",
    },
};

static void test_ecdsa_s2c_original_pubnonce(void) {
    size_t i;
    unsigned char privkey[32] = {
        0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
        0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
    };
    unsigned char message[32] = {
        0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88,
        0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88,
    };
    secp256k1_ecdsa_signature signature;
    secp256k1_s2c_opening s2c_opening;
    unsigned char pubnonce[33];
    /*
      Check that original pubnonce is derived from s2c_data and ndata.
    */
    for (i = 0; i < sizeof(ecdsa_s2c_tests) / sizeof(ecdsa_s2c_tests[0]); i++) {
        size_t pubnonce_size = 33;
        const ecdsa_s2c_test *test = &ecdsa_s2c_tests[i];
        CHECK(secp256k1_ecdsa_s2c_sign(ctx, &signature, &s2c_opening, message, privkey, NULL, test->use_ndata ? test->ndata : NULL, test->s2c_data) == 1);
        CHECK(secp256k1_ec_pubkey_serialize(ctx, pubnonce, &pubnonce_size, &s2c_opening.original_pubnonce, SECP256K1_EC_COMPRESSED) == 1);
        CHECK(memcmp(test->expected_pubnonce, pubnonce, pubnonce_size) == 0);
    }
}

static void test_ecdsa_s2c_anti_nonce_covert_channel_client_commit(void) {
    size_t i;
    unsigned char privkey[32] = {
        0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
        0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
    };
    unsigned char message[32] = {
        0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88,
        0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88,
    };
    secp256k1_pubkey client_commit;
    unsigned char pubnonce[33];
    /*
      Check that original pubnonce is derived from s2c_data and ndata.
    */
    for (i = 0; i < sizeof(ecdsa_s2c_tests) / sizeof(ecdsa_s2c_tests[0]); i++) {
        size_t pubnonce_size = 33;
        const ecdsa_s2c_test *test = &ecdsa_s2c_tests[i];
        CHECK(secp256k1_ecdsa_s2c_anti_nonce_covert_channel_client_commit(ctx, &client_commit, message, privkey, (unsigned char*)test->host_commitment) == 1);
        CHECK(secp256k1_ec_pubkey_serialize(ctx, pubnonce, &pubnonce_size, &client_commit, SECP256K1_EC_COMPRESSED) == 1);
        CHECK(memcmp(test->expected_pubnonce, pubnonce, pubnonce_size) == 0);
    }
}

static void test_ecdsa_s2c_sign_verify(void) {
    unsigned char privkey[32];
    secp256k1_pubkey pubkey;
    unsigned char message[32];
    unsigned char noncedata[32];
    unsigned char s2c_data[32];
    unsigned char s2c_data2[32];
    secp256k1_ecdsa_signature signature;
    secp256k1_ecdsa_signature signature2;
    secp256k1_s2c_opening s2c_opening;

    /* Generate a random key, message, noncedata and s2c_data. */
    {
        secp256k1_scalar key;
        random_scalar_order_test(&key);
        secp256k1_scalar_get_b32(privkey, &key);
        CHECK(secp256k1_ec_pubkey_create(ctx, &pubkey, privkey) == 1);

        secp256k1_rand256_test(message);
        secp256k1_rand256_test(noncedata);
        secp256k1_rand256_test(s2c_data);
        secp256k1_rand256_test(s2c_data2);
    }

    /* Check that sign-to-contract without any s2c_data results the same signature as normal sign. */
    {
        CHECK(secp256k1_ecdsa_s2c_sign(ctx, &signature, NULL, message, privkey, NULL, noncedata, NULL) == 1);
        CHECK(secp256k1_ecdsa_sign(ctx, &signature2, message, privkey, NULL, noncedata) == 1);
        CHECK(memcmp(&signature, &signature2, sizeof(signature)) == 0);
    }
    /* Check that we can only use a different nonce function if s2c_data is not provided. */
    {
        int ecount = 0;
        CHECK(secp256k1_ecdsa_s2c_sign(ctx, &signature, NULL, message, privkey, &nonce_function_non_rfc6979, NULL, NULL) == 1);
        secp256k1_context_set_illegal_callback(ctx, counting_illegal_callback_fn, &ecount);
        CHECK(secp256k1_ecdsa_s2c_sign(ctx, &signature, NULL, message, privkey, &nonce_function_non_rfc6979, NULL, s2c_data) == 0);
        CHECK(ecount == 1);
    }
    /* Check that the sign-to-contract signature is valid, without s2c_data */
    {
        CHECK(secp256k1_ecdsa_s2c_sign(ctx, &signature, NULL, message, privkey, NULL, NULL, NULL) == 1);
        CHECK(secp256k1_ecdsa_verify(ctx, &signature, message, &pubkey) == 1);
    }
    /* Check that the sign-to-contract signature is valid, with s2c_data. Also check the commitment. */
    {
        CHECK(secp256k1_ecdsa_s2c_sign(ctx, &signature, &s2c_opening, message, privkey, NULL, NULL, s2c_data) == 1);
        CHECK(secp256k1_ecdsa_verify(ctx, &signature, message, &pubkey) == 1);
        CHECK(secp256k1_ecdsa_s2c_verify_commit(ctx, &signature, s2c_data, &s2c_opening) == 1);

        CHECK(secp256k1_ecdsa_s2c_sign(ctx, &signature, &s2c_opening, message, privkey, NULL, noncedata, s2c_data) == 1);
        CHECK(secp256k1_ecdsa_verify(ctx, &signature, message, &pubkey) == 1);
        CHECK(secp256k1_ecdsa_s2c_verify_commit(ctx, &signature, s2c_data, &s2c_opening) == 1);
    }
}

/* This tests the full ECDSA Anti Nonce Covert Channel Protocol */
static void test_ecdsa_s2c_anti_nonce_covert_channel(void) {
    unsigned char client_privkey[32];
    unsigned char host_msg[32];
    unsigned char host_commitment[32];
    unsigned char host_nonce_contribution[32];
    secp256k1_pubkey client_commitment;
    secp256k1_ecdsa_signature signature;
    secp256k1_s2c_opening s2c_opening;

    /* Generate a random key, message. */
    {
        secp256k1_scalar key;
        random_scalar_order_test(&key);
        secp256k1_scalar_get_b32(client_privkey, &key);
        secp256k1_rand256_test(host_msg);
    }

    /* Protocol step 1. */
    CHECK(secp256k1_ecdsa_s2c_anti_nonce_covert_channel_host_commit(ctx, host_commitment, host_nonce_contribution) == 1);
    /* Protocol step 2. */
    CHECK(secp256k1_ecdsa_s2c_anti_nonce_covert_channel_client_commit(ctx, &client_commitment, host_msg, client_privkey, host_commitment) == 1);
    /* Protocol step 3: host_nonce_contribution send to client to be used in step 4. */
    /* Protocol step 4. */
    CHECK(secp256k1_ecdsa_s2c_sign(ctx, &signature, &s2c_opening, host_msg, client_privkey, NULL, NULL, host_nonce_contribution) == 1);
    /* Protocol step 5. */
    CHECK(secp256k1_ecdsa_s2c_anti_nonce_covert_channel_host_verify(ctx, &signature, host_nonce_contribution, &s2c_opening, &client_commitment) == 1);
}

static void run_ecdsa_sign_to_contract_tests(void) {
    int i;
    test_ecdsa_s2c_original_pubnonce();
    test_ecdsa_s2c_anti_nonce_covert_channel_client_commit();
    for (i = 0; i < count; i++) {
        test_ecdsa_s2c_sign_verify();
        test_ecdsa_s2c_anti_nonce_covert_channel();
    }
}

#endif /* SECP256K1_MODULE_RECOVERY_TESTS_H */
