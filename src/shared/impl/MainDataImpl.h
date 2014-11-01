#ifndef MAINDATAIMPL_H
#define MAINDATAIMPL_H

#include <shared/MainData.h>

#include <string>
#include <memory>


namespace frts
{
    class MainDataImpl : public MainData
    {
    public:
        /**
         * @param pluginPath Relative path to plugin directory.
         */
        MainDataImpl(const std::string& pluginPath);

        std::string getName() const override;
        std::string getPluginPath() const override;

    private:
        std::string pluginPath;
    };

    /**
     * @brief Create new MainData.
     * @param pluginPath Relative path to plugin directory.
     * @return The MainData.
     */
    inline MainDataPtr makeMainData(const std::string& pluginPath)
    {
        return std::make_shared<MainDataImpl>(pluginPath);
    }
}

#endif // MAINDATAIMPL_H
