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
         * @param deltaTime The delta time of a frame.
         */
        MainDataImpl(const std::string& pluginPath, Frame::time deltaTima);

        Frame::time getDeltaTime() const override;
        std::string getName() const override;
        std::string getPluginPath() const override;
        std::string getTypeName() const override;
        int getTypeVersion() const override;
        int getVersion() const override;

    private:
        Frame::time deltaTime;
        std::string pluginPath;
    };

    /**
     * @brief Create new MainData.
     * @param pluginPath Relative path to plugin directory.
     * @param deltaTime The delta time of a frame.
     * @return The MainData.
     */
    inline MainDataPtr makeMainData(const std::string& pluginPath, Frame::time deltaTime)
    {
        return std::make_shared<MainDataImpl>(pluginPath, deltaTime);
    }
}

#endif // MAINDATAIMPL_H
