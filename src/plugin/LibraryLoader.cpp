#include "LibraryLoader.h"

frts::LibraryLoader::LibraryLoader()
{
}

#if defined(WIN32) || defined(_WIN32)

frts::LibraryLoader::HandleType frts::LibraryLoader::load(const std::string& path,
                                                          const std::string& name) const
{
    const std::string pathWithExtension = path + name + ".dll";

    HandleType moduleHandle = ::LoadLibraryA(pathWithExtension.c_str());
    if(moduleHandle == nullptr)
    {
        auto msg = boost::format(R"(LibraryLoader: Could not load DLL "%1%".)") % pathWithExtension;
        throw std::runtime_error(msg.str());
    }
    return moduleHandle;
}

void frts::LibraryLoader::unload(HandleType library) const
{
    BOOL result = ::FreeLibrary(library);
    if(result == FALSE)
    {
        throw std::runtime_error("LibraryLoader: Could not unload DLL.");
    }
}

#else

frts::LibraryLoader::HandleType frts::LibraryLoader::load(const std::string& path,
                                                          const std::string& name) const
{
    const std::string pathWithExtension = std::string("./") + path + "lib" + name + ".so";

    void* sharedObject = ::dlopen(pathWithExtension.c_str(), RTLD_NOW);
    if(sharedObject == nullptr)
    {
        auto msg = boost::format(R"(LibraryLoader: Could not load shared library "%1%".)") % pathWithExtension;
        throw std::runtime_error(msg.str());
    }
    return sharedObject;
}

void frts::LibraryLoader::unload(HandleType library) const
{
    int result = ::dlclose(library);
    if(result != 0)
    {
        throw std::runtime_error("LibraryLoader: Could not unload shared object.");
    }
}

#endif
