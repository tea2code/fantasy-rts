#ifndef FRTS_FILE_H
#define FRTS_FILE_H

#include <fstream>


namespace frts
{
    /**
     * @brief Check if a file exists.
     * @see http://stackoverflow.com/a/17195806/1931663
     * @param filePath The file path.
     * @return True if the file exists else false.
     */
    inline bool fileExists(const std::string& filePath)
    {
        std::ifstream file(filePath);
        return file.good();
    }
}

#endif // FRTS_FILE_H
