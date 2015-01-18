#ifndef FRTS_PLUGINAPI_H
#define FRTS_PLUGINAPI_H

#include <boost/predef.h>


#if BOOST_COMP_GNUC

    // Prevent problems with visibility in GCC.
    // See http://gcc.gnu.org/wiki/Visibility
    #define PLUGIN_API __attribute__ ((visibility ("default")))

#elif BOOST_COMP_MSVC

    // Building the library.
    #define PLUGIN_API __declspec(dllexport)

#else

    #error Unknown compiler, please implement shared library macros.

#endif

#if defined(PLUGIN_API)

    #include "PluginPtr.h"

    #define REGISTER_PLUGIN(pluginClass)\
    namespace\
    {\
        extern "C" PLUGIN_API frts::PluginPtr getPlugin()\
        {\
            return frts::PluginPtr(new pluginClass());\
        }\
    }

    namespace
    {
        extern "C" PLUGIN_API int getVersion()
        {
          return 1; // Also update in PluginManager.cpp.
        }
    }

#endif

#endif // FRTS_PLUGINAPI_H
