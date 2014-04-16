#ifndef FRTS_SHAREDPTR_H
#define FRTS_SHAREDPTR_H

namespace frts
{
    class DataValue;

    /**
     * @brief Pointer to DataValue.
     */
    using DataValuePtr = std::shared_ptr<DataValue>;

    class Frame;

    /**
     * @brief Pointer to a frame.
     */
    using FramePtr = std::shared_ptr<Frame>;

    class Id;

    /**
     * @brief Pointer to Id.
     */
    using IdPtr = std::shared_ptr<Id>;

    class SharedManager;

    /**
     * @brief Pointer to SharedManager.
     */
    using SharedManagerPtr = std::shared_ptr<SharedManager>;
}

#endif // FRTS_SHAREDPTR_H
