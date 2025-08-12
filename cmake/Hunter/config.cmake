hunter_config(CURL VERSION ${HUNTER_CURL_VERSION} CMAKE_ARGS HTTP_ONLY=ON CMAKE_USE_OPENSSL=ON CMAKE_USE_LIBSSH2=OFF CURL_CA_PATH=none)

# Boost configuration - Use 1.83.0 for compatibility with GCC 13 and Hunter v0.25.2
# Note: Ubuntu 24 ships with Boost 1.83, matching this version
# If you need to use system Boost, comment out hunter_add_package(Boost) in CMakeLists.txt
hunter_config(Boost VERSION 1.83.0)

#hunter_config(
#    ethash VERSION 1.0.0
#    URL https://github.com/RavenCommunity/cpp-kawpow/archive/1.1.0.tar.gz
#    SHA1 fff78f555a43900b6726c131305a71be769ef769
#)

hunter_config(
    intx VERSION 0.5.1
    URL https://github.com/chfast/intx/archive/v0.5.1.tar.gz
    SHA1 743c46a82750143bd302a4394b7008a2112fc97b
)
