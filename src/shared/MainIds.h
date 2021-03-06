#ifndef FRTS_MAINIDS_H
#define FRTS_MAINIDS_H

#include <string>


namespace frts
{
    /**
     * @brief Simple collection of ID strings.
     */
    class MainIds
    {
    public:
        static std::string mainData()
        {
            return "frts::MainData";
        }
    };
}

#endif // FRTS_MAINIDS_H
