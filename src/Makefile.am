DIST_SUBDIRS = secp256k1 univalue

AM_LDFLAGS = $(PTHREAD_CFLAGS) $(LIBTOOL_LDFLAGS) $(HARDENED_LDFLAGS)
AM_CXXFLAGS = $(HARDENED_CXXFLAGS)
AM_CPPFLAGS = $(HARDENED_CPPFLAGS)

if EMBEDDED_LEVELDB
LEVELDB_CPPFLAGS += -I$(srcdir)/leveldb/include
LEVELDB_CPPFLAGS += -I$(srcdir)/leveldb/helpers/memenv
LIBLEVELDB += $(builddir)/leveldb/libleveldb.a
LIBMEMENV  += $(builddir)/leveldb/libmemenv.a

# NOTE: This dependency is not strictly necessary, but without it make may try to build both in parallel, which breaks the LevelDB build system in a race
$(LIBLEVELDB): $(LIBMEMENV)

$(LIBLEVELDB) $(LIBMEMENV):
	@echo "Building LevelDB ..." && $(MAKE) -C $(@D) $(@F) CXX="$(CXX)" \
	  CC="$(CC)" PLATFORM=$(TARGET_OS) AR="$(AR)" $(LEVELDB_TARGET_FLAGS) \
          OPT="$(AM_CXXFLAGS) $(PIE_FLAGS) $(CXXFLAGS) $(AM_CPPFLAGS) $(CPPFLAGS) -D__STDC_LIMIT_MACROS"
endif

BLOQCOIN_CONFIG_INCLUDES=-I$(builddir)/config
BLOQCOIN_INCLUDES=-I$(builddir) -I$(builddir)/obj $(BOOST_CPPFLAGS) $(LEVELDB_CPPFLAGS) $(CRYPTO_CFLAGS) $(SSL_CFLAGS)

BLOQCOIN_INCLUDES += -I$(srcdir)/secp256k1/include
BLOQCOIN_INCLUDES += -I$(srcdir)/univalue/include

LIBBLOQCOIN_SERVER=libbloqcoin_server.a
LIBBLOQCOIN_WALLET=libbloqcoin_wallet.a
LIBBLOQCOIN_COMMON=libbloqcoin_common.a
LIBBLOQCOIN_CLI=libbloqcoin_cli.a
LIBBLOQCOIN_UTIL=libbloqcoin_util.a
LIBBLOQCOIN_CRYPTO=crypto/libbloqcoin_crypto.a
LIBBLOQCOINQT=qt/libbloqcoinqt.a
LIBSECP256K1=secp256k1/libsecp256k1.la
LIBUNIVALUE=univalue/libunivalue.la

$(LIBSECP256K1): $(wildcard secp256k1/src/*) $(wildcard secp256k1/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)
  
$(LIBUNIVALUE): $(wildcard univalue/lib/*) $(wildcard univalue/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)

# Make is not made aware of per-object dependencies to avoid limiting building parallelization
# But to build the less dependent modules first, we manually select their order here:
EXTRA_LIBRARIES = \
  crypto/libbloqcoin_crypto.a \
  libbloqcoin_util.a \
  libbloqcoin_common.a \
  libbloqcoin_server.a \
  libbloqcoin_cli.a
if ENABLE_WALLET
BLOQCOIN_INCLUDES += $(BDB_CPPFLAGS)
EXTRA_LIBRARIES += libbloqcoin_wallet.a
endif
if ENABLE_ZMQ
EXTRA_LIBRARIES += libbloqcoin_zmq.a
endif

if BUILD_BLOQCOIN_LIBS
lib_LTLIBRARIES = libbloqcoinconsensus.la
LIBBLOQCOIN_CONSENSUS=libbloqcoinconsensus.la
else
LIBBLOQCOIN_CONSENSUS=
endif

bin_PROGRAMS =
TESTS =
BENCHMARKS =

if BUILD_BLOQCOIND
  bin_PROGRAMS += bloqcoind
endif

if BUILD_BLOQCOIN_UTILS
  bin_PROGRAMS += bloqcoin-cli bloqcoin-tx
endif

.PHONY: FORCE check-symbols check-security
# bloqcoin core #
BLOQCOIN_CORE_H = \
  addrman.h \
  alert.h \
  amount.h \
  arith_uint256.h \
  base58.h \
  bloom.h \
  chain.h \
  chainparams.h \
  chainparamsbase.h \
  chainparamsseeds.h \
  checkpoints.h \
  checkqueue.h \
  clientversion.h \
  coincontrol.h \
  coins.h \
  compat.h \
  compat/byteswap.h \
  compat/endian.h \
  compat/sanity.h \
  compressor.h \
  consensus/consensus.h \
  consensus/merkle.h \
  consensus/params.h \
  consensus/validation.h \
  core_io.h \
  core_memusage.h \
  hash.h \
  httprpc.h \
  httpserver.h \
  init.h \
  key.h \
  keystore.h \
  dbwrapper.h \
  limitedmap.h \
  main.h \
  memusage.h \
  merkleblock.h \
  miner.h \
  net.h \
  netbase.h \
  noui.h \
  policy/fees.h \
  policy/policy.h \
  policy/rbf.h \
  pow.h \
  prevector.h \
  primitives/block.h \
  primitives/transaction.h \
  protocol.h \
  pubkey.h \
  random.h \
  reverselock.h \
  rpcclient.h \
  rpcprotocol.h \
  rpcserver.h \
  scheduler.h \
  script/interpreter.h \
  script/script.h \
  script/script_error.h \
  script/sigcache.h \
  script/sign.h \
  script/standard.h \
  serialize.h \
  streams.h \
  support/allocators/secure.h \
  support/allocators/zeroafterfree.h \
  support/cleanse.h \
  support/pagelocker.h \
  sync.h \
  threadsafety.h \
  timedata.h \
  tinyformat.h \
  torcontrol.h \
  txdb.h \
  txmempool.h \
  ui_interface.h \
  uint256.h \
  undo.h \
  util.h \
  utilmoneystr.h \
  utilstrencodings.h \
  utiltime.h \
  validationinterface.h \
  version.h \
  versionbits.h \
  wallet/crypter.h \
  wallet/db.h \
  wallet/wallet.h \
  wallet/wallet_ismine.h \
  wallet/walletdb.h \
  zmq/zmqabstractnotifier.h \
  zmq/zmqconfig.h\
  zmq/zmqnotificationinterface.h \
  zmq/zmqpublishnotifier.h


obj/build.h: FORCE
	@$(MKDIR_P) $(builddir)/obj
	@$(top_srcdir)/share/genbuild.sh $(abs_top_builddir)/src/obj/build.h \
	  $(abs_top_srcdir)
libbloqcoin_util_a-clientversion.$(OBJEXT): obj/build.h

# server: shared between bloqcoind and bloqcoin-qt
libbloqcoin_server_a_CPPFLAGS = $(AM_CPPFLAGS) $(BLOQCOIN_INCLUDES) $(MINIUPNPC_CPPFLAGS) $(EVENT_CFLAGS) $(EVENT_PTHREADS_CFLAGS)
libbloqcoin_server_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libbloqcoin_server_a_SOURCES = \
  addrman.cpp \
  alert.cpp \
  bloom.cpp \
  chain.cpp \
  checkpoints.cpp \
  httprpc.cpp \
  httpserver.cpp \
  init.cpp \
  dbwrapper.cpp \
  main.cpp \
  merkleblock.cpp \
  miner.cpp \
  net.cpp \
  noui.cpp \
  policy/fees.cpp \
  policy/policy.cpp \
  pow.cpp \
  rest.cpp \
  rpcblockchain.cpp \
  rpcmining.cpp \
  rpcmisc.cpp \
  rpcnet.cpp \
  rpcrawtransaction.cpp \
  rpcserver.cpp \
  script/sigcache.cpp \
  timedata.cpp \
  torcontrol.cpp \
  txdb.cpp \
  txmempool.cpp \
  validationinterface.cpp \
  versionbits.cpp \
  $(BLOQCOIN_CORE_H)

if ENABLE_ZMQ
LIBBLOQCOIN_ZMQ=libbloqcoin_zmq.a

libbloqcoin_zmq_a_CPPFLAGS = $(BLOQCOIN_INCLUDES) $(ZMQ_CFLAGS)
libbloqcoin_zmq_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libbloqcoin_zmq_a_SOURCES = \
  zmq/zmqabstractnotifier.cpp \
  zmq/zmqnotificationinterface.cpp \
  zmq/zmqpublishnotifier.cpp
endif


# wallet: shared between bloqcoind and bloqcoin-qt, but only linked
# when wallet enabled
libbloqcoin_wallet_a_CPPFLAGS = $(AM_CPPFLAGS) $(BLOQCOIN_INCLUDES)
libbloqcoin_wallet_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libbloqcoin_wallet_a_SOURCES = \
  wallet/crypter.cpp \
  wallet/db.cpp \
  wallet/rpcdump.cpp \
  wallet/rpcwallet.cpp \
  wallet/wallet.cpp \
  wallet/wallet_ismine.cpp \
  wallet/walletdb.cpp \
  policy/rbf.cpp \
  $(BLOQCOIN_CORE_H)

# crypto primitives library
crypto_libbloqcoin_crypto_a_CPPFLAGS = $(AM_CPPFLAGS) $(BLOQCOIN_CONFIG_INCLUDES)
crypto_libbloqcoin_crypto_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
crypto_libbloqcoin_crypto_a_SOURCES = \
  crypto/common.h \
  crypto/hmac_sha256.cpp \
  crypto/hmac_sha256.h \
  crypto/hmac_sha512.cpp \
  crypto/hmac_sha512.h \
  crypto/ripemd160.cpp \
  crypto/ripemd160.h \
  crypto/sha1.cpp \
  crypto/sha1.h \
  crypto/sha256.cpp \
  crypto/sha256.h \
  crypto/sha512.cpp \
  crypto/sha512.h

# common: shared between bloqcoind, and bloqcoin-qt and non-server tools
libbloqcoin_common_a_CPPFLAGS = $(AM_CPPFLAGS) $(BLOQCOIN_INCLUDES)
libbloqcoin_common_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libbloqcoin_common_a_SOURCES = \
  amount.cpp \
  arith_uint256.cpp \
  base58.cpp \
  chainparams.cpp \
  coins.cpp \
  compressor.cpp \
  consensus/merkle.cpp \
  core_read.cpp \
  core_write.cpp \
  hash.cpp \
  key.cpp \
  keystore.cpp \
  netbase.cpp \
  primitives/block.cpp \
  primitives/transaction.cpp \
  protocol.cpp \
  pubkey.cpp \
  scheduler.cpp \
  script/interpreter.cpp \
  script/script.cpp \
  script/script_error.cpp \
  script/sign.cpp \
  script/standard.cpp \
  $(BLOQCOIN_CORE_H)

# util: shared between all executables.
# This library *must* be included to make sure that the glibc
# backward-compatibility objects and their sanity checks are linked.
libbloqcoin_util_a_CPPFLAGS = $(AM_CPPFLAGS) $(BLOQCOIN_INCLUDES)
libbloqcoin_util_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libbloqcoin_util_a_SOURCES = \
  support/pagelocker.cpp \
  chainparamsbase.cpp \
  clientversion.cpp \
  compat/glibc_sanity.cpp \
  compat/glibcxx_sanity.cpp \
  compat/strnlen.cpp \
  random.cpp \
  rpcprotocol.cpp \
  support/cleanse.cpp \
  sync.cpp \
  uint256.cpp \
  util.cpp \
  utilmoneystr.cpp \
  utilstrencodings.cpp \
  utiltime.cpp \
  $(BLOQCOIN_CORE_H)

if GLIBC_BACK_COMPAT
libbloqcoin_util_a_SOURCES += compat/glibc_compat.cpp
endif

# cli: shared between bloqcoin-cli and bloqcoin-qt
libbloqcoin_cli_a_CPPFLAGS = $(AM_CPPFLAGS) $(BLOQCOIN_INCLUDES)
libbloqcoin_cli_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libbloqcoin_cli_a_SOURCES = \
  rpcclient.cpp \
  $(BLOQCOIN_CORE_H)

nodist_libbloqcoin_util_a_SOURCES = $(srcdir)/obj/build.h
#

# bloqcoind binary #
bloqcoind_SOURCES = bloqcoind.cpp
bloqcoind_CPPFLAGS = $(AM_CPPFLAGS) $(BLOQCOIN_INCLUDES)
bloqcoind_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
bloqcoind_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
bloqcoind_SOURCES += bloqcoind-res.rc
endif

bloqcoind_LDADD = \
  $(LIBBLOQCOIN_SERVER) \
  $(LIBBLOQCOIN_COMMON) \
  $(LIBUNIVALUE) \
  $(LIBBLOQCOIN_UTIL) \
  $(LIBBLOQCOIN_CRYPTO) \
  $(LIBLEVELDB) \
  $(LIBMEMENV) \
  $(LIBSECP256K1)

if ENABLE_ZMQ
bloqcoind_LDADD += $(LIBBLOQCOIN_ZMQ) $(ZMQ_LIBS)
endif

if ENABLE_WALLET
bloqcoind_LDADD += libbloqcoin_wallet.a
endif

bloqcoind_LDADD += $(BOOST_LIBS) $(BDB_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS) $(MINIUPNPC_LIBS) $(EVENT_PTHREADS_LIBS) $(EVENT_LIBS)

# bloqcoin-cli binary #
bloqcoin_cli_SOURCES = bloqcoin-cli.cpp
bloqcoin_cli_CPPFLAGS = $(AM_CPPFLAGS) $(BLOQCOIN_INCLUDES) $(EVENT_CFLAGS)
bloqcoin_cli_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
bloqcoin_cli_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
bloqcoin_cli_SOURCES += bloqcoin-cli-res.rc
endif

bloqcoin_cli_LDADD = \
  $(LIBBLOQCOIN_CLI) \
  $(LIBUNIVALUE) \
  $(LIBBLOQCOIN_UTIL)

bloqcoin_cli_LDADD += $(BOOST_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS) $(EVENT_LIBS)
#

# bloqcoin-tx binary #
bloqcoin_tx_SOURCES = bloqcoin-tx.cpp
bloqcoin_tx_CPPFLAGS = $(AM_CPPFLAGS) $(BLOQCOIN_INCLUDES)
bloqcoin_tx_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
bloqcoin_tx_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
bloqcoin_tx_SOURCES += bloqcoin-tx-res.rc
endif

bloqcoin_tx_LDADD = \
  $(LIBUNIVALUE) \
  $(LIBBLOQCOIN_COMMON) \
  $(LIBBLOQCOIN_UTIL) \
  $(LIBBLOQCOIN_CRYPTO) \
  $(LIBSECP256K1)

bloqcoin_tx_LDADD += $(BOOST_LIBS) $(CRYPTO_LIBS)
#

# bloqcoinconsensus library #
if BUILD_BLOQCOIN_LIBS
include_HEADERS = script/bloqcoinconsensus.h
libbloqcoinconsensus_la_SOURCES = \
  crypto/hmac_sha512.cpp \
  crypto/ripemd160.cpp \
  crypto/sha1.cpp \
  crypto/sha256.cpp \
  crypto/sha512.cpp \
  hash.cpp \
  primitives/transaction.cpp \
  pubkey.cpp \
  script/bloqcoinconsensus.cpp \
  script/interpreter.cpp \
  script/script.cpp \
  uint256.cpp \
  utilstrencodings.cpp

if GLIBC_BACK_COMPAT
  libbloqcoinconsensus_la_SOURCES += compat/glibc_compat.cpp
endif

libbloqcoinconsensus_la_LDFLAGS = $(AM_LDFLAGS) -no-undefined $(RELDFLAGS)
libbloqcoinconsensus_la_LIBADD = $(LIBSECP256K1)
libbloqcoinconsensus_la_CPPFLAGS = $(AM_CPPFLAGS) -I$(builddir)/obj -I$(srcdir)/secp256k1/include -DBUILD_BLOQCOIN_INTERNAL
libbloqcoinconsensus_la_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)

endif
#

CLEANFILES = leveldb/libleveldb.a leveldb/libmemenv.a
CLEANFILES += *.gcda *.gcno
CLEANFILES += compat/*.gcda compat/*.gcno
CLEANFILES += consensus/*.gcda consensus/*.gcno
CLEANFILES += crypto/*.gcda crypto/*.gcno
CLEANFILES += policy/*.gcda policy/*.gcno
CLEANFILES += primitives/*.gcda primitives/*.gcno
CLEANFILES += script/*.gcda script/*.gcno
CLEANFILES += support/*.gcda support/*.gcno
CLEANFILES += univalue/*.gcda univalue/*.gcno
CLEANFILES += wallet/*.gcda wallet/*.gcno
CLEANFILES += wallet/test/*.gcda wallet/test/*.gcno
CLEANFILES += zmq/*.gcda zmq/*.gcno

DISTCLEANFILES = obj/build.h

EXTRA_DIST = leveldb

clean-local:
	-$(MAKE) -C leveldb clean
	-$(MAKE) -C secp256k1 clean
	-$(MAKE) -C univalue clean
	-rm -f leveldb/*/*.gcda leveldb/*/*.gcno leveldb/helpers/memenv/*.gcda leveldb/helpers/memenv/*.gcno
	-rm -f config.h

.rc.o:
	@test -f $(WINDRES)
	$(AM_V_GEN) $(WINDRES) -DWINDRES_PREPROC -i $< -o $@

.mm.o:
	$(AM_V_CXX) $(OBJCXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) \
	  $(CPPFLAGS) $(AM_CXXFLAGS) $(QT_INCLUDES) $(AM_CXXFLAGS) $(PIE_FLAGS) $(CXXFLAGS) -c -o $@ $<

check-symbols: $(bin_PROGRAMS)
if GLIBC_BACK_COMPAT
	@echo "Checking glibc back compat..."
	$(AM_V_at) READELF=$(READELF) CPPFILT=$(CPPFILT) $(top_srcdir)/contrib/devtools/symbol-check.py < $(bin_PROGRAMS)
endif

check-security: $(bin_PROGRAMS)
if HARDEN
	@echo "Checking binary security..."
	$(AM_V_at) READELF=$(READELF) OBJDUMP=$(OBJDUMP) $(top_srcdir)/contrib/devtools/security-check.py < $(bin_PROGRAMS)
endif

%.pb.cc %.pb.h: %.proto
	@test -f $(PROTOC)
	$(AM_V_GEN) $(PROTOC) --cpp_out=$(@D) --proto_path=$(abspath $(<D) $<)

if ENABLE_TESTS
include Makefile.test.include
endif

if ENABLE_BENCH
include Makefile.bench.include
endif

if ENABLE_QT
include Makefile.qt.include
endif

if ENABLE_QT_TESTS
include Makefile.qttest.include
endif
