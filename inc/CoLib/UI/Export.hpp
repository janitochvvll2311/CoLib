#ifndef COLIB_UI_EXPORT_HPP
#define COLIB_UI_EXPORT_HPP

#include <CoLib/Config.hpp>

#ifdef COLIB_UI_EXPORTS
#define COLIB_UI_API COLIB_API_EXPORT
#else
#define COLIB_UI_API COLIB_API_IMPORT
#endif

#endif // COLIB_UI_EXPORT_HPP