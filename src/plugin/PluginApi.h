#ifndef PLUGINAPI_H
#define PLUGINAPI_H

#if defined(__GNUC__)

    // Prevent problems with visibility in GCC.
    // See http://gcc.gnu.org/wiki/Visibility
    #define PLUGIN_API __attribute__ ((visibility ("default")))

#elif defined(_MSC_VER)

    // Building the library.
    #define PLUGIN_API __declspec(dllexport)

#else

    #error Unknown compiler, please implement shared library macros.

#endif

#if defined(PLUGIN_API)

    #include "PluginPtr.h"

    #define REGISTER_PLUGIN(pluginClass) extern "C" PLUGIN_API frts::PluginPtr getPlugin()\
    {\
        return frts::PluginPtr(new pluginClass());\
    }\

    extern "C" PLUGIN_API int getVersion()
    {
      return 1; // Also update in plugin manager.
    }

#endif

#endif // PLUGINAPI_H