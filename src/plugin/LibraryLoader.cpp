#include "LibraryLoader.h"

#include <boost/format.hpp>

#include <stdexcept>

frts::LibraryLoader::LibraryLoader()
{
}

#if defined(WIN32) || defined(_WIN32)

template<typename Function>
Function* frts::LibraryLoader::getFunctionPointer(HandleType library, const std::string& name)
{
    FARPROC functionAddress = ::GetProcAddress(library, name.c_str());
    if(functionAddress == NULL)
    {
        auto msg = boost::format(R"(Could not find exported function "%1%".)") % name;
        throw std::runtime_error(msg.str());
    }
    return reinterpret_cast<Function *>(functionAddress);
}

frts::LibraryLoader::HandleType frts::LibraryLoader::load(const std::string& path,
                                                          const std::string& name)
{
    const std::string pathWithExtension = path + name + ".dll";

    HandleType moduleHandle = ::LoadLibraryA(pathWithExtension.c_str());
    if(moduleHandle == NULL)
    {
        auto msg = boost::format(R"(Could not load DLL "%1%".)") % pathWithExtension;
        throw std::runtime_error(msg.str());
    }
    return moduleHandle;
}

void frts::LibraryLoader::unload(HandleType library)
{
    BOOL result = ::FreeLibrary(library);
    if(result == FALSE)
    {
        throw std::runtime_error("Could not unload DLL.");
    }
}

#else

template<typename Function>
Function* frts::LibraryLoader::getFunctionPointer(HandleType library, const std::string& name)
{
    ::dlerror(); // clear error value

    void *functionAddress = ::dlsym(library, name.c_str());

    const char *error = ::dlerror(); // check for error
    if(error != NULL)
    {
        auto msg = boost::format(R"(Could not find exported function "%1%".)") % name;
        throw std::runtime_error(msg.str());
    }

    return reinterpret_cast<Function *>(functionAddress);
}

frts::LibraryLoader::HandleType frts::LibraryLoader::load(const std::string& path, const std::string& name)
{
    const std::string pathWithExtension = std::string("./lib") + path + name + ".so";

    void* sharedObject = ::dlopen(pathWithExtension.c_str(), RTLD_NOW);
    if(sharedObject == NULL)
    {
        auto msg = boost::format(R"(Could not load shared library "%1%".)") % pathWithExtension;
        throw std::runtime_error(msg.str());
    }
    return sharedObject;
}

void frts::LibraryLoader::unload(HandleType library)
{
    int result = ::dlclose(library);
    if(result != 0)
    {
        throw std::runtime_error("Could not unload shared object.");
    }
}

#endif
