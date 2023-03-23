#ifndef COLIB_CONFIG_HPP
#define COLIB_CONFIG_HPP

#include <SFML/Config.hpp>

#define COLIB_MAJOR_VERSION 1
#define COLIB_MINOR_VERSION 0
#define COLIB_PATCH_VERSION 0
#define COLIB_DEVELOPMENT_TAG "a"
#define COLIB_VERSION_STRING "v1.0.0-b"

#define COLIB_API_EXPORT SFML_API_EXPORT
#define COLIB_API_IMPORT SFML_API_IMPORT

namespace co
{

    using i8t = sf::Int8;
    using i16t = sf::Int16;
    using i32t = sf::Int32;
    using i64t = sf::Int64;

    using u8t = sf::Uint8;
    using u16t = sf::Uint16;
    using u32t = sf::Uint32;
    using u64t = sf::Uint64;

    using f32t = float;
    using f64t = double;
    using f128t = long double;

    using c8t = char;
    using c16t = char16_t;
    using c32t = char32_t;

    using s8t = const char *;
    using s16t = const char16_t *;
    using s32t = const char32_t *;

    using szt = std::size_t;

    template <typename T>
    using ptrt = T *;

    template <typename T>
    using reft = T &;

    template <typename R, typename... As>
    using funt = R (*)(As...);

}

#endif // COLIB_CONFIG_HPP