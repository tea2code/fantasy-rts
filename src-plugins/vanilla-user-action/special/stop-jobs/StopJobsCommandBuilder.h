#ifndef FRTS_STOPJOBSCOMMANDBUILDER_H
#define FRTS_STOPJOBSCOMMANDBUILDER_H

#include <main/UserActionCommandBuilder.h>


namespace frts
{
    class StopJobsCommandBuilder : public UserActionCommandBuilder
    {
    public:
        /**
         * @param commandType The command type.
         */
        StopJobsCommandBuilder(const IdPtr& commandType);
        ~StopJobsCommandBuilder();

        CommandPtr build(const SharedManagerPtr& shared) override;
        void setSettings(const ConfigNodePtr& node) override;

    private:
        IdPtr commandType;
        ConfigNodePtr node;
    };

    /**
     * @brief Create new stop jobs command builder.
     * @param commandType The command type.
     * @return The command builder.
     */
    inline UserActionCommandBuilderPtr makeStopJobsCommandBuilder(const IdPtr& commandType)
    {
        assert(commandType != nullptr);

        return std::make_shared<StopJobsCommandBuilder>(commandType);
    }
}

#endif // FRTS_STOPJOBSCOMMANDBUILDER_H
