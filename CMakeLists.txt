cmake_minimum_required (VERSION 3.16)

# Back compatibility for VERSION range
if (${CMAKE_VERSION} VERSION_LESS 3.12)
  cmake_policy (VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif ()

project (
  data
  VERSION 0.0.24
  DESCRIPTION "wrappers and high-level programming constructs in c++"
  LANGUAGES CXX
)
include(FetchContent)



FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_Declare(secp256k1
        GIT_REPOSITORY https://github.com/bitcoin-core/secp256k1
        GIT_TAG v0.5.0
)
FetchContent_Declare(cryptopp-cmake
    GIT_REPOSITORY https://github.com/abdes/cryptopp-cmake
        GIT_TAG CRYPTOPP_8_9_0
)
FetchContent_Declare(pegtl
        GIT_REPOSITORY https://github.com/taocpp/PEGTL
        GIT_TAG 3.2.7)
FetchContent_Declare(argh
        GIT_REPOSITORY https://github.com/adishavit/argh
        GIT_TAG v1.3.2)


FetchContent_MakeAvailable(cryptopp-cmake)
FetchContent_MakeAvailable(googletest)
FetchContent_MakeAvailable(json)
FetchContent_MakeAvailable(secp256k1)
FetchContent_MakeAvailable(pegtl)
FetchContent_MakeAvailable(argh)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(
        Boost 1.82 REQUIRED)

find_package (OpenSSL)
find_package(GMP)
find_package(NTL)



# Check if GTests is installed. If not, install it

option (PACKAGE_TESTS "Build the tests" ON)

add_definitions ("-DHAS_BOOST")

if (PACKAGE_TESTS)
  include (CTest)
  enable_testing ()
  add_subdirectory (test)

endif ()

# Add Library source files here
include("cmake/Symbols.cmake")

add_library (data STATIC
  src/sv/fs.cpp
  src/sv/support/cleanse.cpp
  src/sv/support/lockedpool.cpp
  src/sv/crypto/chacha20.cpp
  src/sv/crypto/hmac_sha512.cpp
  src/sv/crypto/ripemd160.cpp
  src/sv/crypto/sha1.cpp
  src/sv/crypto/sha256.cpp
  src/sv/crypto/sha512.cpp
  src/sv/utiltime.cpp
  include/rotella/aks.cpp
  include/rotella/sieve.cpp
  include/rotella/akslib.cpp
  src/data/types.cpp
  src/data/string.cpp
  src/data/tools.cpp
  src/data/encoding/hex.cpp
  src/data/encoding/ascii.cpp
  src/data/encoding/utf8.cpp
  src/data/encoding/base64.cpp
  src/data/encoding/base58.cpp
  src/data/encoding/integer.cpp
  src/data/net/URL.cpp
  src/data/net/HTTP.cpp
  src/data/net/REST.cpp
  src/data/net/JSON.cpp
  src/data/net/TCP.cpp
  src/data/net/websocket.cpp
  src/data/net/HTTP_client.cpp
  #src/data/io/run.cpp
  src/data/tools/channel.cpp
  src/data/crypto/random.cpp
  src/data/crypto/secret_share.cpp
  src/data/math/number/gmp/mpq.cpp
  src/data/math/number/gmp/N.cpp
  src/data/math/number/gmp/aks.cpp
  src/data/math/number/gmp/sqrt.cpp
  src/data/crypto/AES.cpp
  src/data/tools/circular_queue.cpp
  src/data/tools/rate_limiter.cpp
  src/data/log/log.cpp
)

target_include_directories (data PUBLIC include)

target_link_libraries (
  data
        Boost::headers
        OpenSSL::SSL
  cryptopp::cryptopp
  nlohmann_json::nlohmann_json
  ntl
        gmp
  secp256k1
  pegtl
  argh
  # PkgConfig::LIBSECP256K1
)

get_target_property (OUT data LINK_LIBRARIES)
message (STATUS ${OUT})

# Set C++ version
target_compile_features (data PUBLIC cxx_std_20)
set_target_properties (data PROPERTIES CXX_EXTENSIONS ON)
#target_compile_options (data PUBLIC "-fconcepts")

install (DIRECTORY include/ DESTINATION include)
install (TARGETS data)
