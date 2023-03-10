#ifndef COLIB_SYSTEM_EXPORT_HPP
#define COLIB_SYSTEM_EXPORT_HPP

#include <CoLib/Config.hpp>

#ifdef COLIB_SYSTEM_EXPORTS
#define COLIB_SYSTEM_API COLIB_API_EXPORT
#else
#define COLIB_SYSTEM_API COLIB_API_IMPORT
#endif

#endif // COLIB_SYSTEM_EXPORT_HPP