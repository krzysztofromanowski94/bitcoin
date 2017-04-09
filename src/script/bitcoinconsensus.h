// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2016 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DETKCOIN_DETKCOINCONSENSUS_H
#define DETKCOIN_DETKCOINCONSENSUS_H

#include <stdint.h>

#if defined(BUILD_DETKCOIN_INTERNAL) && defined(HAVE_CONFIG_H)
#include "config/detkcoin-config.h"
  #if defined(_WIN32)
    #if defined(DLL_EXPORT)
      #if defined(HAVE_FUNC_ATTRIBUTE_DLLEXPORT)
        #define EXPORT_SYMBOL __declspec(dllexport)
      #else
        #define EXPORT_SYMBOL
      #endif
    #endif
  #elif defined(HAVE_FUNC_ATTRIBUTE_VISIBILITY)
    #define EXPORT_SYMBOL __attribute__ ((visibility ("default")))
  #endif
#elif defined(MSC_VER) && !defined(STATIC_LIBDETKCOINCONSENSUS)
  #define EXPORT_SYMBOL __declspec(dllimport)
#endif

#ifndef EXPORT_SYMBOL
  #define EXPORT_SYMBOL
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define DETKCOINCONSENSUS_API_VER 1

typedef enum detkcoinconsensus_error_t
{
    detkcoinconsensus_ERR_OK = 0,
    detkcoinconsensus_ERR_TX_INDEX,
    detkcoinconsensus_ERR_TX_SIZE_MISMATCH,
    detkcoinconsensus_ERR_TX_DESERIALIZE,
    detkcoinconsensus_ERR_AMOUNT_REQUIRED,
    detkcoinconsensus_ERR_INVALID_FLAGS,
} detkcoinconsensus_error;

/** Script verification flags */
enum
{
    detkcoinconsensus_SCRIPT_FLAGS_VERIFY_NONE                = 0,
    detkcoinconsensus_SCRIPT_FLAGS_VERIFY_P2SH                = (1U << 0), // evaluate P2SH (BIP16) subscripts
    detkcoinconsensus_SCRIPT_FLAGS_VERIFY_DERSIG              = (1U << 2), // enforce strict DER (BIP66) compliance
    detkcoinconsensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY           = (1U << 4), // enforce NULLDUMMY (BIP147)
    detkcoinconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY = (1U << 9), // enable CHECKLOCKTIMEVERIFY (BIP65)
    detkcoinconsensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY = (1U << 10), // enable CHECKSEQUENCEVERIFY (BIP112)
    detkcoinconsensus_SCRIPT_FLAGS_VERIFY_WITNESS             = (1U << 11), // enable WITNESS (BIP141)
    detkcoinconsensus_SCRIPT_FLAGS_VERIFY_ALL                 = detkcoinconsensus_SCRIPT_FLAGS_VERIFY_P2SH | detkcoinconsensus_SCRIPT_FLAGS_VERIFY_DERSIG |
                                                               detkcoinconsensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY | detkcoinconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY |
                                                               detkcoinconsensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY | detkcoinconsensus_SCRIPT_FLAGS_VERIFY_WITNESS
};

/// Returns 1 if the input nIn of the serialized transaction pointed to by
/// txTo correctly spends the scriptPubKey pointed to by scriptPubKey under
/// the additional constraints specified by flags.
/// If not NULL, err will contain an error/success code for the operation
EXPORT_SYMBOL int detkcoinconsensus_verify_script(const unsigned char *scriptPubKey, unsigned int scriptPubKeyLen,
                                                 const unsigned char *txTo        , unsigned int txToLen,
                                                 unsigned int nIn, unsigned int flags, detkcoinconsensus_error* err);

EXPORT_SYMBOL int detkcoinconsensus_verify_script_with_amount(const unsigned char *scriptPubKey, unsigned int scriptPubKeyLen, int64_t amount,
                                    const unsigned char *txTo        , unsigned int txToLen,
                                    unsigned int nIn, unsigned int flags, detkcoinconsensus_error* err);

EXPORT_SYMBOL unsigned int detkcoinconsensus_version();

#ifdef __cplusplus
} // extern "C"
#endif

#undef EXPORT_SYMBOL

#endif // DETKCOIN_DETKCOINCONSENSUS_H
