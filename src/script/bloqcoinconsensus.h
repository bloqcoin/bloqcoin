// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2022 The Bloqcoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BLOQCOIN_BLOQCOINCONSENSUS_H
#define BLOQCOIN_BLOQCOINCONSENSUS_H

#if defined(BUILD_BLOQCOIN_INTERNAL) && defined(HAVE_CONFIG_H)
#include "config/bloqcoin-config.h"
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
#elif defined(MSC_VER) && !defined(STATIC_LIBBLOQCOINCONSENSUS)
  #define EXPORT_SYMBOL __declspec(dllimport)
#endif

#ifndef EXPORT_SYMBOL
  #define EXPORT_SYMBOL
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define BLOQCOINCONSENSUS_API_VER 0

typedef enum bloqcoinconsensus_error_t
{
    bloqcoinconsensus_ERR_OK = 0,
    bloqcoinconsensus_ERR_TX_INDEX,
    bloqcoinconsensus_ERR_TX_SIZE_MISMATCH,
    bloqcoinconsensus_ERR_TX_DESERIALIZE,
} bloqcoinconsensus_error;

/** Script verification flags */
enum
{
    bloqcoinconsensus_SCRIPT_FLAGS_VERIFY_NONE                = 0,
    bloqcoinconsensus_SCRIPT_FLAGS_VERIFY_P2SH                = (1U << 0), // evaluate P2SH (BIP16) subscripts
    bloqcoinconsensus_SCRIPT_FLAGS_VERIFY_DERSIG              = (1U << 2), // enforce strict DER (BIP66) compliance
    bloqcoinconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY = (1U << 9), // enable CHECKLOCKTIMEVERIFY (BIP65)
};

/// Returns 1 if the input nIn of the serialized transaction pointed to by
/// txTo correctly spends the scriptPubKey pointed to by scriptPubKey under
/// the additional constraints specified by flags.
/// If not NULL, err will contain an error/success code for the operation
EXPORT_SYMBOL int bloqcoinconsensus_verify_script(const unsigned char *scriptPubKey, unsigned int scriptPubKeyLen,
                                    const unsigned char *txTo        , unsigned int txToLen,
                                    unsigned int nIn, unsigned int flags, bloqcoinconsensus_error* err);

EXPORT_SYMBOL unsigned int bloqcoinconsensus_version();

#ifdef __cplusplus
} // extern "C"
#endif

#undef EXPORT_SYMBOL

#endif // BLOQCOIN_BLOQCOINCONSENSUS_H
