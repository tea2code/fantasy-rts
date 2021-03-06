#ifndef FRTS_LIBRARYLOADER_H
#define FRTS_LIBRARYLOADER_H

#include <boost/format.hpp>
#include <boost/predef.h>

#include <stdexcept>
#include <string>

#if BOOST_OS_WINDOWS
    #define WIN32_LEAN_AND_MEAN
    #define VC_EXTRALEAN
    #include <windows.h>
#else
    #pragma GCC system_header
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

#if BOOST_OS_WINDOWS
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
        Function* getFunctionPointer(HandleType library, const std::string& name) const;

        /**
         * @brief Load the library.
         * @param path Path to the library. Must end with slash.
         * @param name Name of the library file without extension.
         * @return The library handle.
         */
        HandleType load(const std::string& path, const std::string& name) const;

        /**
         * @brief Unload the library.
         * @param library The library.
         */
        void unload(HandleType library) const;
    };
}

#if BOOST_OS_WINDOWS

template<typename Function>
Function* frts::LibraryLoader::getFunctionPointer(HandleType library, const std::string& name) const
{
    FARPROC functionAddress = ::GetProcAddress(library, name.c_str());
    if(functionAddress == nullptr)
    {
        auto msg = boost::format(R"(LibraryLoader: Could not find exported function "%1%".)") % name;
        throw std::runtime_error(msg.str());
    }
    return reinterpret_cast<Function *>(functionAddress);
}

#else

template<typename Function>
Function* frts::LibraryLoader::getFunctionPointer(HandleType library, const std::string& name) const
{
    ::dlerror(); // clear error value

    void *functionAddress = ::dlsym(library, name.c_str());

    const char *error = ::dlerror(); // check for error
    if(error != nullptr)
    {
        auto msg = boost::format(R"(LibraryLoader: Could not find exported function "%1%".)") % name;
        throw std::runtime_error(msg.str());
    }

    return reinterpret_cast<Function *>(functionAddress);
}

#endif

#endif // FRTS_LIBRARYLOADER_H
