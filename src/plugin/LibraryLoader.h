#ifndef LIBRARYLOADER_H
#define LIBRARYLOADER_H

#include <string>

#if defined(WIN32) || defined(_WIN32)
    #define WIN32_LEAN_AND_MEAN
    #define VC_EXTRALEAN
    #include <windows.h>
#else
    #include <dlfcn.h>
#endif

namespace frts
{
    /**
     * @brief Wrapps low level loading of libraries on Windows and Linux. Based
     * on http://blog.nuclex-games.com/tutorials/cxx/plugin-architecture/
     * @throws Every method may throw runtime errors if something goes wrong.
     */
    class LibraryLoader
    {
    public:
        LibraryLoader();

#if defined(WIN32) || defined(_WIN32)
        using HandleType = HMODULE;
#else
        using HandleType = void *;
#endif

        /**
         * @brief Get pointer to a function in given library.
         * @param library The library.
         * @param name Name of the function.
         * @return Pointer to the function.
         */
        template<typename Function>
        Function* getFunctionPointer(HandleType library, const std::string& name);

        /**
         * @brief Load the library.
         * @param path Path to the library. Must end with slash.
         * @param name Name of the library file without extension.
         * @return The library handle.
         */
        HandleType load(const std::string& path, const std::string& name);

        /**
         * @brief Unload the library.
         * @param library The library.
         */
        void unload(HandleType library);
    };
}

#endif // LIBRARYLOADER_H
