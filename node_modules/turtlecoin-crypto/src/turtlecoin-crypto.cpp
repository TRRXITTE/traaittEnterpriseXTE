// Copyright (c) 2018-2020, The TurtleCoin Developers
//
// Please see the included LICENSE file for more information.

#include <StringTools.h>
#include <string.h>
#include <turtlecoin-crypto.h>

#ifndef NO_CRYPTO_EXPORTS
#ifdef _WIN32
#include <windows.h>
#ifdef _MANAGED
#pragma managed(push, off)
#endif

EXPORTDLL bool DllMain(
    HMODULE /*hModule*/,
    DWORD ul_reason_for_call,
    LPVOID /*lpReserved*/
)
{
    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
    }
    return true;
}

#ifdef _MANAGED
#pragma managed(pop)
#endif
#endif
#endif

namespace Core
{
    template<typename T> void toTypedVector(const std::vector<std::string> &stringVector, std::vector<T> &result)
    {
        result.clear();

        for (const auto element : stringVector)
        {
            T value = T();

            Common::podFromHex(element, value);

            result.push_back(value);
        }
    }

    template<typename T> void toStringVector(const std::vector<T> &typedVector, std::vector<std::string> &result)
    {
        result.clear();

        for (const auto element : typedVector)
        {
            if (sizeof(element) == sizeof(Crypto::Signature))
            {
                result.push_back(Common::toHex(&element, sizeof(element)));
            }
            else
            {
                result.push_back(Common::podToHex(element));
            }
        }
    }

    inline Crypto::BinaryArray toBinaryArray(const std::string input)
    {
        return Common::fromHex(input);
    }

    /* Hashing Methods */
    std::string Cryptography::cn_fast_hash(const std::string input)
    {
        Crypto::Hash hash = Crypto::Hash();

        Crypto::BinaryArray data = toBinaryArray(input);

        Crypto::cn_fast_hash(data.data(), data.size(), hash);

        return Common::podToHex(hash);
    }

    std::string Cryptography::cn_slow_hash_v0(const std::string input)
    {
        Crypto::Hash hash = Crypto::Hash();

        Crypto::BinaryArray data = toBinaryArray(input);

        Crypto::cn_slow_hash_v0(data.data(), data.size(), hash);

        return Common::podToHex(hash);
    }

    std::string Cryptography::cn_slow_hash_v1(const std::string input)
    {
        Crypto::Hash hash = Crypto::Hash();

        Crypto::BinaryArray data = toBinaryArray(input);

        Crypto::cn_slow_hash_v1(data.data(), data.size(), hash);

        return Common::podToHex(hash);
    }

    std::string Cryptography::cn_slow_hash_v2(const std::string input)
    {
        Crypto::Hash hash = Crypto::Hash();

        Crypto::BinaryArray data = toBinaryArray(input);

        Crypto::cn_slow_hash_v2(data.data(), data.size(), hash);

        return Common::podToHex(hash);
    }

    std::string Cryptography::cn_lite_slow_hash_v0(const std::string input)
    {
        Crypto::Hash hash = Crypto::Hash();

        Crypto::BinaryArray data = toBinaryArray(input);

        Crypto::cn_lite_slow_hash_v0(data.data(), data.size(), hash);

        return Common::podToHex(hash);
    }

    std::string Cryptography::cn_lite_slow_hash_v1(const std::string input)
    {
        Crypto::Hash hash = Crypto::Hash();

        Crypto::BinaryArray data = toBinaryArray(input);

        Crypto::cn_lite_slow_hash_v1(data.data(), data.size(), hash);

        return Common::podToHex(hash);
    }

    std::string Cryptography::cn_lite_slow_hash_v2(const std::string input)
    {
        Crypto::Hash hash = Crypto::Hash();

        Crypto::BinaryArray data = toBinaryArray(input);

        Crypto::cn_lite_slow_hash_v2(data.data(), data.size(), hash);

        return Common::podToHex(hash);
    }

    std::string Cryptography::cn_dark_slow_hash_v0(const std::string input)
    {
        Crypto::Hash hash = Crypto::Hash();

        Crypto::BinaryArray data = toBinaryArray(input);

        Crypto::cn_dark_slow_hash_v0(data.data(), data.size(), hash);

        return Common::podToHex(hash);
    }

    std::string Cryptography::cn_dark_slow_hash_v1(const std::string input)
    {
        Crypto::Hash hash = Crypto::Hash();

        Crypto::BinaryArray data = toBinaryArray(input);

        Crypto::cn_dark_slow_hash_v1(data.data(), data.size(), hash);

        return Common::podToHex(hash);
    }

    std::string Cryptography::cn_dark_slow_hash_v2(const std::string input)
    {
        Crypto::Hash hash = Crypto::Hash();

        Crypto::BinaryArray data = toBinaryArray(input);

        Crypto::cn_dark_slow_hash_v2(data.data(), data.size(), hash);

        return Common::podToHex(hash);
    }

    std::string Cryptography::cn_dark_lite_slow_hash_v0(const std::string input)
    {
        Crypto::Hash hash = Crypto::Hash();

        Crypto::BinaryArray data = toBinaryArray(input);

        Crypto::cn_dark_lite_slow_hash_v0(data.data(), data.size(), hash);

        return Common::podToHex(hash);
    }

    std::string Cryptography::cn_dark_lite_slow_hash_v1(const std::string input)
    {
        Crypto::Hash hash = Crypto::Hash();

        Crypto::BinaryArray data = toBinaryArray(input);

        Crypto::cn_dark_lite_slow_hash_v1(data.data(), data.size(), hash);

        return Common::podToHex(hash);
    }

    std::string Cryptography::cn_dark_lite_slow_hash_v2(const std::string input)
    {
        Crypto::Hash hash = Crypto::Hash();

        Crypto::BinaryArray data = toBinaryArray(input);

        Crypto::cn_dark_lite_slow_hash_v2(data.data(), data.size(), hash);

        return Common::podToHex(hash);
    }

    std::string Cryptography::cn_turtle_slow_hash_v0(const std::string input)
    {
        Crypto::Hash hash = Crypto::Hash();

        Crypto::BinaryArray data = toBinaryArray(input);

        Crypto::cn_turtle_slow_hash_v0(data.data(), data.size(), hash);

        return Common::podToHex(hash);
    }

    std::string Cryptography::cn_turtle_slow_hash_v1(const std::string input)
    {
        Crypto::Hash hash = Crypto::Hash();

        Crypto::BinaryArray data = toBinaryArray(input);

        Crypto::cn_turtle_slow_hash_v1(data.data(), data.size(), hash);

        return Common::podToHex(hash);
    }

    std::string Cryptography::cn_turtle_slow_hash_v2(const std::string input)
    {
        Crypto::Hash hash = Crypto::Hash();

        Crypto::BinaryArray data = toBinaryArray(input);

        Crypto::cn_turtle_slow_hash_v2(data.data(), data.size(), hash);

        return Common::podToHex(hash);
    }

    std::string Cryptography::cn_turtle_lite_slow_hash_v0(const std::string input)
    {
        Crypto::Hash hash = Crypto::Hash();

        Crypto::BinaryArray data = toBinaryArray(input);

        Crypto::cn_turtle_lite_slow_hash_v0(data.data(), data.size(), hash);

        return Common::podToHex(hash);
    }

    std::string Cryptography::cn_turtle_lite_slow_hash_v1(const std::string input)
    {
        Crypto::Hash hash = Crypto::Hash();

        Crypto::BinaryArray data = toBinaryArray(input);

        Crypto::cn_turtle_lite_slow_hash_v1(data.data(), data.size(), hash);

        return Common::podToHex(hash);
    }

    std::string Cryptography::cn_turtle_lite_slow_hash_v2(const std::string input)
    {
        Crypto::Hash hash = Crypto::Hash();

        Crypto::BinaryArray data = toBinaryArray(input);

        Crypto::cn_turtle_lite_slow_hash_v2(data.data(), data.size(), hash);

        return Common::podToHex(hash);
    }

    std::string Cryptography::cn_soft_shell_slow_hash_v0(const std::string input, const uint64_t height)
    {
        Crypto::Hash hash = Crypto::Hash();

        Crypto::BinaryArray data = toBinaryArray(input);

        Crypto::cn_soft_shell_slow_hash_v0(data.data(), data.size(), hash, height);

        return Common::podToHex(hash);
    }

    std::string Cryptography::cn_soft_shell_slow_hash_v1(const std::string input, const uint64_t height)
    {
        Crypto::Hash hash = Crypto::Hash();

        Crypto::BinaryArray data = toBinaryArray(input);

        Crypto::cn_soft_shell_slow_hash_v1(data.data(), data.size(), hash, height);

        return Common::podToHex(hash);
    }

    std::string Cryptography::cn_soft_shell_slow_hash_v2(const std::string input, const uint64_t height)
    {
        Crypto::Hash hash = Crypto::Hash();

        Crypto::BinaryArray data = toBinaryArray(input);

        Crypto::cn_soft_shell_slow_hash_v2(data.data(), data.size(), hash, height);

        return Common::podToHex(hash);
    }

    std::string Cryptography::chukwa_slow_hash(const std::string input)
    {
        Crypto::Hash hash = Crypto::Hash();

        Crypto::BinaryArray data = toBinaryArray(input);

        Crypto::chukwa_slow_hash(data.data(), data.size(), hash);

        return Common::podToHex(hash);
    }

    uint32_t Cryptography::tree_depth(const uint32_t count)
    {
        return Crypto::tree_depth(count);
    }

    std::string Cryptography::tree_hash(const std::vector<std::string> hashes)
    {
        std::vector<Crypto::Hash> treeHashes;

        toTypedVector(hashes, treeHashes);

        Crypto::Hash treeHash = Crypto::Hash();

        Crypto::tree_hash(treeHashes.data(), treeHashes.size(), treeHash);

        return Common::podToHex(treeHash);
    }

    std::vector<std::string> Cryptography::tree_branch(const std::vector<std::string> hashes)
    {
        std::vector<Crypto::Hash> _hashes;

        toTypedVector(hashes, _hashes);

        std::vector<Crypto::Hash> _branches(tree_depth(_hashes.size()));

        Crypto::tree_branch(_hashes.data(), _hashes.size(), _branches.data());

        std::vector<std::string> branches;

        toStringVector(_branches, branches);

        return branches;
    }

    std::string Cryptography::tree_hash_from_branch(
        const std::vector<std::string> branches,
        const std::string leaf,
        const std::string path)
    {
        std::vector<Crypto::Hash> _branches;

        toTypedVector(branches, _branches);

        Crypto::Hash _leaf = Crypto::Hash();

        Common::podFromHex(leaf, _leaf);

        Crypto::Hash _hash = Crypto::Hash();

        if (path != "0")
        {
            Crypto::Hash _path = Crypto::Hash();

            Common::podFromHex(path, _path);

            Crypto::tree_hash_from_branch(_branches.data(), branches.size(), _leaf, _path.data, _hash);
        }
        else
        {
            Crypto::tree_hash_from_branch(_branches.data(), branches.size(), _leaf, 0, _hash);
        }

        return Common::podToHex(_hash);
    }

    /* Crypto Methods */
    bool Cryptography::generateRingSignatures(
        const std::string prefixHash,
        const std::string keyImage,
        const std::vector<std::string> publicKeys,
        const std::string transactionSecretKey,
        const uint64_t realOutput,
        std::vector<std::string> &signatures)
    {
        Crypto::Hash _prefixHash = Crypto::Hash();

        Common::podFromHex(prefixHash, _prefixHash);

        Crypto::KeyImage _keyImage = Crypto::KeyImage();

        Common::podFromHex(keyImage, _keyImage);

        std::vector<Crypto::PublicKey> _publicKeys;

        toTypedVector(publicKeys, _publicKeys);

        Crypto::SecretKey _transactionSecretKey;

        Common::podFromHex(transactionSecretKey, _transactionSecretKey);

        std::vector<Crypto::Signature> _signatures;

        bool success = Crypto::crypto_ops::generateRingSignatures(
            _prefixHash, _keyImage, _publicKeys, _transactionSecretKey, realOutput, _signatures);

        if (success)
        {
            toStringVector(_signatures, signatures);
        }

        return success;
    }

    bool Cryptography::checkRingSignature(
        const std::string prefixHash,
        const std::string keyImage,
        const std::vector<std::string> publicKeys,
        const std::vector<std::string> signatures)
    {
        Crypto::Hash _prefixHash = Crypto::Hash();

        Common::podFromHex(prefixHash, _prefixHash);

        Crypto::KeyImage _keyImage = Crypto::KeyImage();

        Common::podFromHex(keyImage, _keyImage);

        std::vector<Crypto::PublicKey> _publicKeys;

        toTypedVector(publicKeys, _publicKeys);

        std::vector<Crypto::Signature> _signatures;

        toTypedVector(signatures, _signatures);

        return Crypto::crypto_ops::checkRingSignature(_prefixHash, _keyImage, _publicKeys, _signatures);
    }

    std::string Cryptography::generatePrivateViewKeyFromPrivateSpendKey(const std::string privateSpendKey)
    {
        Crypto::SecretKey _privateSpendKey = Crypto::SecretKey();

        Common::podFromHex(privateSpendKey, _privateSpendKey);

        Crypto::SecretKey privateViewKey = Crypto::SecretKey();

        Crypto::crypto_ops::generateViewFromSpend(_privateSpendKey, privateViewKey);

        return Common::podToHex(privateViewKey);
    }

    void Cryptography::generateViewKeysFromPrivateSpendKey(
        const std::string privateSpendKey,
        std::string &privateViewKey,
        std::string &publicViewKey)
    {
        Crypto::SecretKey _privateSpendKey = Crypto::SecretKey();

        Common::podFromHex(privateSpendKey, _privateSpendKey);

        Crypto::SecretKey _privateViewKey = Crypto::SecretKey();

        Crypto::PublicKey _publicViewKey = Crypto::PublicKey();

        Crypto::crypto_ops::generateViewFromSpend(_privateSpendKey, _privateViewKey, _publicViewKey);

        privateViewKey = Common::podToHex(_privateViewKey);

        publicViewKey = Common::podToHex(_publicViewKey);
    }

    void Cryptography::generateKeys(std::string &privateKey, std::string &publicKey)
    {
        Crypto::SecretKey _privateKey = Crypto::SecretKey();

        Crypto::PublicKey _publicKey = Crypto::PublicKey();

        Crypto::generate_keys(_publicKey, _privateKey);

        privateKey = Common::podToHex(_privateKey);

        publicKey = Common::podToHex(_publicKey);
    }

    bool Cryptography::checkKey(const std::string publicKey)
    {
        Crypto::PublicKey _publicKey = Crypto::PublicKey();

        Common::podFromHex(publicKey, _publicKey);

        return Crypto::check_key(_publicKey);
    }

    bool Cryptography::secretKeyToPublicKey(const std::string privateKey, std::string &publicKey)
    {
        Crypto::SecretKey _privateKey = Crypto::SecretKey();

        Common::podFromHex(privateKey, _privateKey);

        Crypto::PublicKey _publicKey = Crypto::PublicKey();

        bool success = Crypto::secret_key_to_public_key(_privateKey, _publicKey);

        if (success)
        {
            publicKey = Common::podToHex(_publicKey);
        }

        return success;
    }

    bool Cryptography::generateKeyDerivation(
        const std::string publicKey,
        const std::string privateKey,
        std::string &derivation)
    {
        Crypto::PublicKey _publicKey = Crypto::PublicKey();

        Common::podFromHex(publicKey, _publicKey);

        Crypto::SecretKey _privateKey = Crypto::SecretKey();

        Common::podFromHex(privateKey, _privateKey);

        Crypto::KeyDerivation _derivation = Crypto::KeyDerivation();

        bool success = Crypto::generate_key_derivation(_publicKey, _privateKey, _derivation);

        if (success)
        {
            derivation = Common::podToHex(_derivation);
        }

        return success;
    }

    bool Cryptography::derivePublicKey(
        const std::string derivation,
        const uint64_t outputIndex,
        const std::string publicKey,
        std::string &derivedKey)
    {
        Crypto::KeyDerivation _derivation = Crypto::KeyDerivation();

        Common::podFromHex(derivation, _derivation);

        Crypto::PublicKey _publicKey = Crypto::PublicKey();

        Common::podFromHex(publicKey, _publicKey);

        Crypto::PublicKey _derivedKey = Crypto::PublicKey();

        bool success = Crypto::derive_public_key(_derivation, outputIndex, _publicKey, _derivedKey);

        if (success)
        {
            derivedKey = Common::podToHex(_derivedKey);
        }

        return success;
    }

    std::string Cryptography::deriveSecretKey(
        const std::string derivation,
        const uint64_t outputIndex,
        const std::string privateKey)
    {
        Crypto::KeyDerivation _derivation = Crypto::KeyDerivation();

        Common::podFromHex(derivation, _derivation);

        Crypto::SecretKey _privateKey = Crypto::SecretKey();

        Common::podFromHex(privateKey, _privateKey);

        Crypto::SecretKey _derivedKey = Crypto::SecretKey();

        Crypto::derive_secret_key(_derivation, outputIndex, _privateKey, _derivedKey);

        return Common::podToHex(_derivedKey);
    }

    bool Cryptography::underivePublicKey(
        const std::string derivation,
        const uint64_t outputIndex,
        const std::string derivedKey,
        std::string &publicKey)
    {
        Crypto::KeyDerivation _derivation = Crypto::KeyDerivation();

        Common::podFromHex(derivation, _derivation);

        Crypto::PublicKey _derivedKey = Crypto::PublicKey();

        Common::podFromHex(derivedKey, _derivedKey);

        Crypto::PublicKey _publicKey = Crypto::PublicKey();

        bool success = Crypto::underive_public_key(_derivation, outputIndex, _derivedKey, _publicKey);

        if (success)
        {
            publicKey = Common::podToHex(_publicKey);
        }

        return success;
    }

    std::string Cryptography::generateSignature(
        const std::string prefixHash,
        const std::string publicKey,
        const std::string privateKey)
    {
        Crypto::Hash _prefixHash = Crypto::Hash();

        Common::podFromHex(prefixHash, _prefixHash);

        Crypto::PublicKey _publicKey = Crypto::PublicKey();

        Common::podFromHex(publicKey, _publicKey);

        Crypto::SecretKey _privateKey = Crypto::SecretKey();

        Common::podFromHex(privateKey, _privateKey);

        Crypto::Signature _signature = Crypto::Signature();

        Crypto::generate_signature(_prefixHash, _publicKey, _privateKey, _signature);

        return Common::podToHex(_signature);
    }

    bool Cryptography::checkSignature(
        const std::string prefixHash,
        const std::string publicKey,
        const std::string signature)
    {
        Crypto::Hash _prefixHash = Crypto::Hash();

        Common::podFromHex(prefixHash, _prefixHash);

        Crypto::PublicKey _publicKey = Crypto::PublicKey();

        Common::podFromHex(publicKey, _publicKey);

        Crypto::Signature _signature = Crypto::Signature();

        Common::podFromHex(signature, _signature);

        return Crypto::check_signature(_prefixHash, _publicKey, _signature);
    }

    std::string Cryptography::generateKeyImage(const std::string publicKey, const std::string privateKey)
    {
        Crypto::PublicKey _publicKey = Crypto::PublicKey();

        Common::podFromHex(publicKey, _publicKey);

        Crypto::SecretKey _privateKey = Crypto::SecretKey();

        Common::podFromHex(privateKey, _privateKey);

        Crypto::KeyImage _keyImage = Crypto::KeyImage();

        Crypto::generate_key_image(_publicKey, _privateKey, _keyImage);

        return Common::podToHex(_keyImage);
    }

    std::string Cryptography::scalarmultKey(const std::string keyImageA, const std::string keyImageB)
    {
        Crypto::KeyImage _keyImageA = Crypto::KeyImage();

        Common::podFromHex(keyImageA, _keyImageA);

        Crypto::KeyImage _keyImageB = Crypto::KeyImage();

        Common::podFromHex(keyImageB, _keyImageB);

        Crypto::KeyImage _keyImage = Crypto::scalarmultKey(_keyImageA, _keyImageB);

        return Common::podToHex(_keyImage);
    }

    std::string Cryptography::hashToEllipticCurve(const std::string hash)
    {
        Crypto::Hash _hash = Crypto::Hash();

        Common::podFromHex(hash, _hash);

        Crypto::PublicKey _ellipticCurve = Crypto::PublicKey();

        Crypto::hash_data_to_ec(_hash.data, sizeof(_hash.data), _ellipticCurve);

        return Common::podToHex(_ellipticCurve);
    }

    std::string Cryptography::scReduce32(const std::string data)
    {
        Crypto::EllipticCurveScalar _scalar;

        Common::podFromHex(data, _scalar);

        Crypto::scReduce32(_scalar);

        return Common::podToHex(_scalar);
    }

    std::string Cryptography::hashToScalar(const std::string hash)
    {
        Crypto::BinaryArray _hash = toBinaryArray(hash);

        Crypto::EllipticCurveScalar _scalar;

        Crypto::hashToScalar(_hash.data(), _hash.size(), _scalar);

        return Common::podToHex(_scalar);
    }

    bool Cryptography::generateDeterministicSubwalletKeys(
        const std::string basePrivateKey,
        const uint64_t walletIndex,
        std::string &privateKey,
        std::string &publicKey)
    {
        Crypto::SecretKey _basePrivateKey;

        Common::podFromHex(basePrivateKey, _basePrivateKey);

        Crypto::SecretKey _privateKey;

        Crypto::PublicKey _publicKey;

        if (Crypto::generate_deterministic_subwallet_keys(_basePrivateKey, walletIndex, _privateKey, _publicKey))
        {
            privateKey = Common::podToHex(_privateKey);

            publicKey = Common::podToHex(_publicKey);

            return true;
        }

        return false;
    }

    std::string Cryptography::restoreKeyImage(
        const std::string &publicEphemeral,
        const std::string &derivation,
        const size_t output_index,
        const std::vector<std::string> &partialKeyImages)
    {
        Crypto::PublicKey _publicEphemeral;

        Common::podFromHex(publicEphemeral, _publicEphemeral);

        Crypto::KeyDerivation _derivation;

        Common::podFromHex(derivation, _derivation);

        std::vector<Crypto::KeyImage> _partialKeyImages;

        toTypedVector(partialKeyImages, _partialKeyImages);

        Crypto::KeyImage _keyImage =
            Crypto::Multisig::restore_key_image(_publicEphemeral, _derivation, output_index, _partialKeyImages);

        return Common::podToHex(_keyImage);
    }

    bool Cryptography::restoreRingSignatures(
        const std::string &derivation,
        const size_t output_index,
        const std::vector<std::string> &partialSigningKeys,
        const uint64_t realOutput,
        const std::string &k,
        std::vector<std::string> &signatures)
    {
        Crypto::KeyDerivation _derivation;

        Common::podFromHex(derivation, _derivation);

        std::vector<Crypto::SecretKey> _partialSigningKeys;

        toTypedVector(partialSigningKeys, _partialSigningKeys);

        Crypto::EllipticCurveScalar _k;

        Common::podFromHex(k, _k);

        std::vector<Crypto::Signature> _signatures;

        toTypedVector(signatures, _signatures);

        const auto success = Crypto::Multisig::restore_ring_signatures(
            _derivation, output_index, _partialSigningKeys, realOutput, _k, _signatures);

        if (success)
        {
            toStringVector(_signatures, signatures);
        }

        return success;
    }

    std::string
        Cryptography::generatePartialSigningKey(const std::string &signature, const std::string &privateSpendKey)
    {
        Crypto::Signature _signature;

        Common::podFromHex(signature, _signature);

        Crypto::SecretKey _privateSpendKey;

        Common::podFromHex(privateSpendKey, _privateSpendKey);

        Crypto::SecretKey _key = Crypto::Multisig::generate_partial_signing_key(_signature, _privateSpendKey);

        return Common::podToHex(_key);
    }

    bool Cryptography::prepareRingSignatures(
        const std::string prefixHash,
        const std::string keyImage,
        const std::vector<std::string> publicKeys,
        const uint64_t realOutput,
        std::vector<std::string> &signatures,
        std::string &k)
    {
        Crypto::Hash _prefixHash;

        Common::podFromHex(prefixHash, _prefixHash);

        Crypto::KeyImage _keyImage;

        Common::podFromHex(keyImage, _keyImage);

        std::vector<Crypto::PublicKey> _publicKeys;

        toTypedVector(publicKeys, _publicKeys);

        std::vector<Crypto::Signature> _signatures;

        Crypto::EllipticCurveScalar _k;

        const auto success =
            Crypto::crypto_ops::prepareRingSignatures(_prefixHash, _keyImage, _publicKeys, realOutput, _signatures, _k);

        if (success)
        {
            toStringVector(_signatures, signatures);

            k = Common::podToHex(_k);
        }

        return success;
    }

    bool Cryptography::prepareRingSignatures(
        const std::string prefixHash,
        const std::string keyImage,
        const std::vector<std::string> publicKeys,
        const uint64_t realOutput,
        const std::string k,
        std::vector<std::string> &signatures)
    {
        Crypto::Hash _prefixHash;

        Common::podFromHex(prefixHash, _prefixHash);

        Crypto::KeyImage _keyImage;

        Common::podFromHex(keyImage, _keyImage);

        std::vector<Crypto::PublicKey> _publicKeys;

        toTypedVector(publicKeys, _publicKeys);

        std::vector<Crypto::Signature> _signatures;

        Crypto::EllipticCurveScalar _k;

        Common::podFromHex(k, _k);

        const auto success =
            Crypto::crypto_ops::prepareRingSignatures(_prefixHash, _keyImage, _publicKeys, realOutput, _k, _signatures);

        if (success)
        {
            toStringVector(_signatures, signatures);
        }

        return success;
    }

    bool Cryptography::completeRingSignatures(
        const std::string transactionSecretKey,
        const uint64_t realOutput,
        const std::string &k,
        std::vector<std::string> &signatures)
    {
        Crypto::SecretKey _transactionSecretKey;

        Common::podFromHex(transactionSecretKey, _transactionSecretKey);

        Crypto::EllipticCurveScalar _k;

        Common::podFromHex(k, _k);

        std::vector<Crypto::Signature> _signatures;

        toTypedVector(signatures, _signatures);

        const auto success =
            Crypto::crypto_ops::completeRingSignatures(_transactionSecretKey, realOutput, _k, _signatures);

        if (success)
        {
            toStringVector(_signatures, signatures);
        }

        return success;
    }

    std::vector<std::string> Cryptography::calculateMultisigPrivateKeys(
        const std::string &ourPrivateSpendKey,
        const std::vector<std::string> &publicKeys)
    {
        Crypto::SecretKey _ourPrivateSpendKey;

        Common::podFromHex(ourPrivateSpendKey, _ourPrivateSpendKey);

        std::vector<Crypto::PublicKey> _publicKeys;

        toTypedVector(publicKeys, _publicKeys);

        std::vector<Crypto::SecretKey> _multisigKeys =
            Crypto::Multisig::calculate_multisig_private_keys(_ourPrivateSpendKey, _publicKeys);

        std::vector<std::string> multisigKeys;

        toStringVector(_multisigKeys, multisigKeys);

        return multisigKeys;
    }

    std::string Cryptography::calculateSharedPrivateKey(const std::vector<std::string> &secretKeys)
    {
        std::vector<Crypto::SecretKey> _secretKeys;

        toTypedVector(secretKeys, _secretKeys);

        Crypto::SecretKey sharedPrivateKey = Crypto::Multisig::calculate_shared_private_key(_secretKeys);

        return Common::podToHex(sharedPrivateKey);
    }

    std::string Cryptography::calculateSharedPublicKey(const std::vector<std::string> &publicKeys)
    {
        std::vector<Crypto::PublicKey> _publicKeys;

        toTypedVector(publicKeys, _publicKeys);

        Crypto::PublicKey sharedPublicKey = Crypto::Multisig::calculate_shared_public_key(_publicKeys);

        return Common::podToHex(sharedPublicKey);
    }
} // namespace Core

inline void tree_hash(const char *hashes, const uint64_t hashesLength, char *&hash)
{
    const std::string *hashesBuffer = reinterpret_cast<const std::string *>(hashes);

    std::vector<std::string> _hashes(hashesBuffer, hashesBuffer + hashesLength);

    std::string result = Core::Cryptography::tree_hash(_hashes);

    hash = strdup(result.c_str());
}

inline void tree_branch(const char *hashes, const uint64_t hashesLength, char *&branch)
{
    const std::string *hashesBuffer = reinterpret_cast<const std::string *>(hashes);

    std::vector<std::string> _hashes(hashesBuffer, hashesBuffer + hashesLength);

    std::vector<std::string> _branch = Core::Cryptography::tree_branch(_hashes);

    branch = reinterpret_cast<char *>(_branch.data());
}

inline void tree_hash_from_branch(
    const char *branches,
    const uint64_t branchesLength,
    const char *leaf,
    const char *path,
    char *&hash)
{
    const std::string *branchesBuffer = reinterpret_cast<const std::string *>(branches);

    std::vector<std::string> _branches(branchesBuffer, branchesBuffer + branchesLength);

    std::string _hash = Core::Cryptography::tree_hash_from_branch(_branches, leaf, path);

    hash = strdup(_hash.c_str());
}

inline int generateRingSignatures(
    const char *prefixHash,
    const char *keyImage,
    const char *publicKeys,
    uint64_t publicKeysLength,
    const char *transactionSecretKey,
    const uint64_t realOutput,
    char *&signatures)
{
    const std::string *publicKeysBuffer = reinterpret_cast<const std::string *>(publicKeys);

    std::vector<std::string> _publicKeys(publicKeysBuffer, publicKeysBuffer + publicKeysLength);

    std::vector<std::string> _signatures;

    bool success = Core::Cryptography::generateRingSignatures(
        prefixHash, keyImage, _publicKeys, transactionSecretKey, realOutput, _signatures);

    if (success)
    {
        signatures = reinterpret_cast<char *>(_signatures.data());
    }

    return success;
}

inline bool checkRingSignature(
    const char *prefixHash,
    const char *keyImage,
    const char *publicKeys,
    const uint64_t publicKeysLength,
    const char *signatures,
    const uint64_t signaturesLength)
{
    const std::string *publicKeysBuffer = reinterpret_cast<const std::string *>(publicKeys);

    std::vector<std::string> _publicKeys(publicKeysBuffer, publicKeysBuffer + publicKeysLength);

    const std::string *signaturesBuffer = reinterpret_cast<const std::string *>(signatures);

    std::vector<std::string> _signatures(signaturesBuffer, signaturesBuffer + signaturesLength);

    return Core::Cryptography::checkRingSignature(prefixHash, keyImage, _publicKeys, _signatures);
}

inline void generateViewKeysFromPrivateSpendKey(const char *privateSpendKey, char *&privateKey, char *&publicKey)
{
    std::string _privateKey;

    std::string _publicKey;

    Core::Cryptography::generateViewKeysFromPrivateSpendKey(privateSpendKey, _privateKey, _publicKey);

    privateKey = strdup(_privateKey.c_str());

    publicKey = strdup(_publicKey.c_str());
}

inline void generateKeys(char *&privateKey, char *&publicKey)
{
    std::string _privateKey;

    std::string _publicKey;

    Core::Cryptography::generateKeys(_privateKey, _publicKey);

    privateKey = strdup(_privateKey.c_str());

    publicKey = strdup(_publicKey.c_str());
}

inline int secretKeyToPublicKey(const char *privateKey, char *&publicKey)
{
    std::string _publicKey;

    bool success = Core::Cryptography::secretKeyToPublicKey(privateKey, _publicKey);

    publicKey = strdup(_publicKey.c_str());

    return success;
}

inline int generateKeyDerivation(const char *publicKey, const char *privateKey, char *&derivation)
{
    std::string _derivation;

    bool success = Core::Cryptography::generateKeyDerivation(publicKey, privateKey, _derivation);

    derivation = strdup(_derivation.c_str());

    return success;
}

inline int
    derivePublicKey(const char *derivation, const uint64_t outputIndex, const char *publicKey, char *&outPublicKey)
{
    std::string _outPublicKey;

    bool success = Core::Cryptography::derivePublicKey(derivation, outputIndex, publicKey, _outPublicKey);

    outPublicKey = strdup(_outPublicKey.c_str());

    return success;
}

inline int
    underivePublicKey(const char *derivation, const uint64_t outputIndex, const char *derivedKey, char *&publicKey)
{
    std::string _publicKey;

    bool success = Core::Cryptography::underivePublicKey(derivation, outputIndex, derivedKey, _publicKey);

    publicKey = strdup(_publicKey.c_str());

    return success;
}

inline bool generateDeterministicSubwalletKeys(
    const char *basePrivateKey,
    const uint64_t walletIndex,
    char *&privateKey,
    char *&publicKey)
{
    std::string _privateKey;

    std::string _publicKey;

    if (Core::Cryptography::generateDeterministicSubwalletKeys(basePrivateKey, walletIndex, _privateKey, _publicKey))
    {
        privateKey = strdup(_privateKey.c_str());

        publicKey = strdup(_publicKey.c_str());

        return true;
    }

    return false;
}

inline int completeRingSignatures(
    const char *transactionSecretKey,
    const uint64_t realOutput,
    const char *k,
    char *&signatures,
    const uint64_t signaturesLength)
{
    const std::string *sigsBuffer = reinterpret_cast<const std::string *>(signatures);

    std::vector<std::string> sigs(sigsBuffer, sigsBuffer + signaturesLength);

    bool success = Core::Cryptography::completeRingSignatures(transactionSecretKey, realOutput, k, sigs);

    if (success)
    {
        signatures = reinterpret_cast<char *>(sigs.data());
    }

    return success;
}

inline int prepareRingSignatures(
    const char *prefixHash,
    const char *keyImage,
    const char *publicKeys,
    const uint64_t publicKeysLength,
    const uint64_t realOutput,
    char *&signatures,
    char *&k)
{
    const std::string *keysBuffer = reinterpret_cast<const std::string *>(publicKeys);

    std::vector<std::string> keys(keysBuffer, keysBuffer + publicKeysLength);

    std::vector<std::string> sigs;

    std::string kTemp;

    bool success = Core::Cryptography::prepareRingSignatures(prefixHash, keyImage, keys, realOutput, sigs, kTemp);

    if (success)
    {
        k = strdup(kTemp.c_str());

        signatures = reinterpret_cast<char *>(sigs.data());
    }

    return success;
}

inline void restoreKeyImage(
    const char *publicEphemeral,
    const char *derivation,
    const uint64_t output_index,
    const char *partialKeyImages,
    const uint64_t partialKeyImagesLength,
    char *&keyImage)
{
    const std::string *keysBuffer = reinterpret_cast<const std::string *>(partialKeyImages);

    std::vector<std::string> keys(keysBuffer, keysBuffer + partialKeyImagesLength);

    const std::string result = Core::Cryptography::restoreKeyImage(publicEphemeral, derivation, output_index, keys);

    keyImage = strdup(result.c_str());
}

inline int restoreRingSignatures(
    const char *derivation,
    const uint64_t output_index,
    const char *partialSigningKeys,
    const uint64_t partialSigningKeysLength,
    const uint64_t realOutput,
    const char *k,
    char *&signatures,
    const uint64_t signaturesLength)
{
    const std::string *keysBuffer = reinterpret_cast<const std::string *>(partialSigningKeys);

    std::vector<std::string> keys(keysBuffer, keysBuffer + partialSigningKeysLength);

    const std::string *sigsBuffer = reinterpret_cast<const std::string *>(signatures);

    std::vector<std::string> sigs(sigsBuffer, sigsBuffer + signaturesLength);

    bool success = Core::Cryptography::restoreRingSignatures(derivation, output_index, keys, realOutput, k, sigs);

    if (success)
    {
        signatures = reinterpret_cast<char *>(sigs.data());
    }

    return success;
}

inline void calculateMultisigPrivateKeys(
    const char *ourPrivateSpendKey,
    const char *publicKeys,
    const uint64_t publicKeysLength,
    char *&multisigKeys)
{
    const std::string *keysBuffer = reinterpret_cast<const std::string *>(publicKeys);

    std::vector<std::string> keys(keysBuffer, keysBuffer + publicKeysLength);

    std::vector<std::string> multisigKeysTemp =
        Core::Cryptography::calculateMultisigPrivateKeys(ourPrivateSpendKey, keys);

    multisigKeys = reinterpret_cast<char *>(multisigKeysTemp.data());
}

inline void calculateSharedPrivateKey(const char *secretKeys, const uint64_t secretKeysLength, char *&secretKey)
{
    const std::string *keysBuffer = reinterpret_cast<const std::string *>(secretKeys);

    std::vector<std::string> keys(keysBuffer, keysBuffer + secretKeysLength);

    const std::string result = Core::Cryptography::calculateSharedPrivateKey(keys);

    secretKey = strdup(result.c_str());
}

inline void calculateSharedPublicKey(const char *publicKeys, const uint64_t publicKeysLength, char *&publicKey)
{
    const std::string *keysBuffer = reinterpret_cast<const std::string *>(publicKeys);

    std::vector<std::string> keys(keysBuffer, keysBuffer + publicKeysLength);

    const std::string result = Core::Cryptography::calculateSharedPublicKey(keys);

    publicKey = strdup(result.c_str());
}

extern "C"
{
    /* Hashing Methods */

    EXPORTDLL void _cn_fast_hash(const char *input, char *&output)
    {
        output = strdup(Core::Cryptography::cn_fast_hash(input).c_str());
    }

    EXPORTDLL void _cn_slow_hash_v0(const char *input, char *&output)
    {
        output = strdup(Core::Cryptography::cn_slow_hash_v0(input).c_str());
    }

    EXPORTDLL void _cn_slow_hash_v1(const char *input, char *&output)
    {
        output = strdup(Core::Cryptography::cn_slow_hash_v1(input).c_str());
    }

    EXPORTDLL void _cn_slow_hash_v2(const char *input, char *&output)
    {
        output = strdup(Core::Cryptography::cn_slow_hash_v2(input).c_str());
    }

    EXPORTDLL void _cn_lite_slow_hash_v0(const char *input, char *&output)
    {
        output = strdup(Core::Cryptography::cn_lite_slow_hash_v0(input).c_str());
    }

    EXPORTDLL void _cn_lite_slow_hash_v1(const char *input, char *&output)
    {
        output = strdup(Core::Cryptography::cn_lite_slow_hash_v1(input).c_str());
    }

    EXPORTDLL void _cn_lite_slow_hash_v2(const char *input, char *&output)
    {
        output = strdup(Core::Cryptography::cn_lite_slow_hash_v2(input).c_str());
    }

    EXPORTDLL void _cn_dark_slow_hash_v0(const char *input, char *&output)
    {
        output = strdup(Core::Cryptography::cn_dark_slow_hash_v0(input).c_str());
    }

    EXPORTDLL void _cn_dark_slow_hash_v1(const char *input, char *&output)
    {
        output = strdup(Core::Cryptography::cn_dark_slow_hash_v1(input).c_str());
    }

    EXPORTDLL void _cn_dark_slow_hash_v2(const char *input, char *&output)
    {
        output = strdup(Core::Cryptography::cn_dark_slow_hash_v2(input).c_str());
    }

    EXPORTDLL void _cn_dark_lite_slow_hash_v0(const char *input, char *&output)
    {
        output = strdup(Core::Cryptography::cn_dark_lite_slow_hash_v0(input).c_str());
    }

    EXPORTDLL void _cn_dark_lite_slow_hash_v1(const char *input, char *&output)
    {
        output = strdup(Core::Cryptography::cn_dark_lite_slow_hash_v1(input).c_str());
    }

    EXPORTDLL void _cn_dark_lite_slow_hash_v2(const char *input, char *&output)
    {
        output = strdup(Core::Cryptography::cn_dark_lite_slow_hash_v2(input).c_str());
    }

    EXPORTDLL void _cn_turtle_slow_hash_v0(const char *input, char *&output)
    {
        output = strdup(Core::Cryptography::cn_turtle_slow_hash_v0(input).c_str());
    }

    EXPORTDLL void _cn_turtle_slow_hash_v1(const char *input, char *&output)
    {
        output = strdup(Core::Cryptography::cn_turtle_slow_hash_v1(input).c_str());
    }

    EXPORTDLL void _cn_turtle_slow_hash_v2(const char *input, char *&output)
    {
        output = strdup(Core::Cryptography::cn_turtle_slow_hash_v2(input).c_str());
    }

    EXPORTDLL void _cn_turtle_lite_slow_hash_v0(const char *input, char *&output)
    {
        output = strdup(Core::Cryptography::cn_turtle_lite_slow_hash_v0(input).c_str());
    }

    EXPORTDLL void _cn_turtle_lite_slow_hash_v1(const char *input, char *&output)
    {
        output = strdup(Core::Cryptography::cn_turtle_lite_slow_hash_v1(input).c_str());
    }

    EXPORTDLL void _cn_turtle_lite_slow_hash_v2(const char *input, char *&output)
    {
        output = strdup(Core::Cryptography::cn_turtle_lite_slow_hash_v2(input).c_str());
    }

    EXPORTDLL void _cn_soft_shell_slow_hash_v0(const char *input, const uint32_t height, char *&output)
    {
        output = strdup(Core::Cryptography::cn_soft_shell_slow_hash_v0(input, height).c_str());
    }

    EXPORTDLL void _cn_soft_shell_slow_hash_v1(const char *input, const uint32_t height, char *&output)
    {
        output = strdup(Core::Cryptography::cn_soft_shell_slow_hash_v1(input, height).c_str());
    }

    EXPORTDLL void _cn_soft_shell_slow_hash_v2(const char *input, const uint32_t height, char *&output)
    {
        output = strdup(Core::Cryptography::cn_soft_shell_slow_hash_v2(input, height).c_str());
    }

    EXPORTDLL void _chukwa_slow_hash(const char *input, char *&output)
    {
        output = strdup(Core::Cryptography::chukwa_slow_hash(input).c_str());
    }

    EXPORTDLL uint32_t _tree_depth(const uint32_t count)
    {
        return Core::Cryptography::tree_depth(count);
    }

    EXPORTDLL void _tree_hash(const char *hashes, const uint64_t hashesLength, char *&hash)
    {
        tree_hash(hashes, hashesLength, hash);
    }

    EXPORTDLL void _tree_branch(const char *hashes, const uint64_t hashesLength, char *&branch)
    {
        tree_branch(hashes, hashesLength, branch);
    }

    EXPORTDLL void _tree_hash_from_branch(
        const char *branches,
        const uint64_t branchesLength,
        const uint64_t depth,
        const char *leaf,
        const char *path,
        char *&hash)
    {
        tree_hash_from_branch(branches, branchesLength, leaf, path, hash);
    }

    /* Crypto Methods */

    EXPORTDLL int _generateRingSignatures(
        const char *prefixHash,
        const char *keyImage,
        const char *publicKeys,
        const uint64_t publicKeysLength,
        const char *transactionSecretKey,
        const uint64_t realOutput,
        char *&signatures)
    {
        return generateRingSignatures(
            prefixHash, keyImage, publicKeys, publicKeysLength, transactionSecretKey, realOutput, signatures);
    }

    EXPORTDLL bool _checkRingSignature(
        const char *prefixHash,
        const char *keyImage,
        const char *publicKeys,
        const uint64_t publicKeysLength,
        const char *signatures,
        const uint64_t signaturesLength)
    {
        return checkRingSignature(prefixHash, keyImage, publicKeys, publicKeysLength, signatures, signaturesLength);
    }

    EXPORTDLL void _generatePrivateViewKeyFromPrivateSpendKey(const char *spendPrivateKey, char *&output)
    {
        output = strdup(Core::Cryptography::generatePrivateViewKeyFromPrivateSpendKey(spendPrivateKey).c_str());
    }

    EXPORTDLL void
        _generateViewKeysFromPrivateSpendKey(const char *spendPrivateKey, char *&privateKey, char *&publicKey)
    {
        generateViewKeysFromPrivateSpendKey(spendPrivateKey, privateKey, publicKey);
    }

    EXPORTDLL void _generateKeys(char *&privateKey, char *&publicKey)
    {
        generateKeys(privateKey, publicKey);
    }

    EXPORTDLL int _checkKey(const char *publicKey)
    {
        return Core::Cryptography::checkKey(publicKey);
    }

    EXPORTDLL int _secretKeyToPublicKey(const char *privateKey, char *&publicKey)
    {
        return secretKeyToPublicKey(privateKey, publicKey);
    }

    EXPORTDLL int _generateKeyDerivation(const char *publicKey, const char *privateKey, char *&derivation)
    {
        return generateKeyDerivation(publicKey, privateKey, derivation);
    }

    EXPORTDLL int
        _derivePublicKey(const char *derivation, uint32_t outputIndex, const char *publicKey, char *&outPublicKey)
    {
        return derivePublicKey(derivation, outputIndex, publicKey, outPublicKey);
    }

    EXPORTDLL void
        _deriveSecretKey(const char *derivation, uint32_t outputIndex, const char *privateKey, char *&outPrivateKey)
    {
        outPrivateKey = strdup(Core::Cryptography::deriveSecretKey(derivation, outputIndex, privateKey).c_str());
    }

    EXPORTDLL int
        _underivePublicKey(const char *derivation, const uint64_t outputIndex, const char *derivedKey, char *&publicKey)
    {
        return underivePublicKey(derivation, outputIndex, derivedKey, publicKey);
    }

    EXPORTDLL void
        _generateSignature(const char *prefixHash, const char *publicKey, const char *privateKey, char *&signature)
    {
        signature = strdup(Core::Cryptography::generateSignature(prefixHash, publicKey, privateKey).c_str());
    }

    EXPORTDLL int _checkSignature(const char *prefixHash, const char *publicKey, const char *signature)
    {
        return Core::Cryptography::checkSignature(prefixHash, publicKey, signature);
    }

    EXPORTDLL void _generateKeyImage(const char *publicKey, const char *privateKey, char *&keyImage)
    {
        keyImage = strdup(Core::Cryptography::generateKeyImage(publicKey, privateKey).c_str());
    }

    EXPORTDLL void _scalarmultKey(const char *keyImageA, const char *keyImageB, char *&keyImageC)
    {
        keyImageC = strdup(Core::Cryptography::scalarmultKey(keyImageA, keyImageB).c_str());
    }

    EXPORTDLL void _hashToEllipticCurve(const char *hash, char *&ec)
    {
        ec = strdup(Core::Cryptography::hashToEllipticCurve(hash).c_str());
    }

    EXPORTDLL void _scReduce32(const char *data, char *&output)
    {
        output = strdup(Core::Cryptography::scReduce32(data).c_str());
    }

    EXPORTDLL void _hashToScalar(const char *hash, char *&output)
    {
        output = strdup(Core::Cryptography::hashToScalar(hash).c_str());
    }

    EXPORTDLL int _generateDeterministicSubwalletKeys(
        const char *basePrivateKey,
        const uint64_t walletIndex,
        char *&privateKey,
        char *&publicKey)
    {
        return generateDeterministicSubwalletKeys(basePrivateKey, walletIndex, privateKey, publicKey);
    }

    EXPORTDLL void _restoreKeyImage(
        const char *publicEphemeral,
        const char *derivation,
        const uint64_t output_index,
        const char *partialKeyImages,
        const uint64_t partialKeyImagesLength,
        char *&keyImage)
    {
        restoreKeyImage(publicEphemeral, derivation, output_index, partialKeyImages, partialKeyImagesLength, keyImage);
    }

    EXPORTDLL int _restoreRingSignatures(
        const char *derivation,
        const uint64_t output_index,
        const char *partialSigningKeys,
        const uint64_t partialSigningKeysLength,
        const uint64_t realOutput,
        const char *k,
        char *&signatures,
        const uint64_t signaturesLength)
    {
        return restoreRingSignatures(
            derivation,
            output_index,
            partialSigningKeys,
            partialSigningKeysLength,
            realOutput,
            k,
            signatures,
            signaturesLength);
    }

    EXPORTDLL void
        _generatePartialSigningKey(const char *signature, const char *privateSpendKey, char *&partialSigningKey)
    {
        partialSigningKey = strdup(Core::Cryptography::generatePartialSigningKey(signature, privateSpendKey).c_str());
    }

    EXPORTDLL int _prepareRingSignatures(
        const char *prefixHash,
        const char *keyImage,
        const char *publicKeys,
        const uint64_t publicKeysLength,
        const uint64_t realOutput,
        char *&signatures,
        char *&k)
    {
        return prepareRingSignatures(prefixHash, keyImage, publicKeys, publicKeysLength, realOutput, signatures, k);
    }

    EXPORTDLL int _completeRingSignatures(
        const char *transactionSecretKey,
        const uint64_t realOutput,
        const char *k,
        char *&signatures,
        const uint64_t signaturesLength)
    {
        return completeRingSignatures(transactionSecretKey, realOutput, k, signatures, signaturesLength);
    }

    EXPORTDLL void _calculateMultisigPrivateKeys(
        const char *ourPrivateSpendKey,
        const char *publicKeys,
        const uint64_t publicKeysLength,
        char *&multisigKeys)
    {
        calculateMultisigPrivateKeys(ourPrivateSpendKey, publicKeys, publicKeysLength, multisigKeys);
    }

    EXPORTDLL void _calculateSharedPrivateKey(const char *secretKeys, const uint64_t secretKeysLength, char *&secretKey)
    {
        calculateSharedPrivateKey(secretKeys, secretKeysLength, secretKey);
    }

    EXPORTDLL void _calculateSharedPublicKey(const char *publicKeys, const uint64_t publicKeysLength, char *&publicKey)
    {
        calculateSharedPublicKey(publicKeys, publicKeysLength, publicKey);
    }
}
