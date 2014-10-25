#ifndef FRTS_MAINDATA_H
#define FRTS_MAINDATA_H

#include "DataValue.h"

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
         * @brief Get the relative (from execution directory)
         *        path to the plugin directory. Ends with a slash.
         * @return The plugin path.
         */
        virtual std::string getPluginPath() const = 0;

        /**
         * @brief The default identifier for this data value.
         * @return The id string.
         */
        static std::string identifier()
        {
            return "frts.maindata";
        }
    };
}

#endif // FRTS_MAINDATA_H
