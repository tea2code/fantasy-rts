#ifndef FRTS_MAINDATA_H
#define FRTS_MAINDATA_H

#include "DataValue.h"
#include "Frame.h"

#include <string>
#include <memory>


namespace frts
{
    class MainData;

    /**
     * @brief Pointer to MainData.
     */
    using MainDataPtr = std::shared_ptr<MainData>;

    /**
     * @brief This data value stores some data related to the main program.
     */
    class MainData : public DataValue
    {
    public:
        virtual ~MainData() {}

        /**
         * @brief The time a frame normally should have.
         * @return The delta time.
         */
        virtual Frame::time getDeltaTime() const = 0;

        /**
         * @brief Get the relative (from execution directory)
         *        path to the plugin directory. Ends with a slash.
         * @return The plugin path.
         */
        virtual std::string getPluginPath() const = 0;
    };
}

#endif // FRTS_MAINDATA_H
