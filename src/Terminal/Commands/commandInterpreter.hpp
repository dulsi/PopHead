#ifndef POPHEAD_TERMINAL_COMMANDS_COMMANDINTERPRETER_H_
#define POPHEAD_TERMINAL_COMMANDS_COMMANDINTERPRETER_H_

#include <string>

namespace PopHead {
	namespace Base { class GameData; }
namespace Terminal {

class CommandInterpreter
{
public:
	void setGameData(Base::GameData* gameData) { mGameData = gameData; }

	void handleCommand(const std::string&);
private:
	bool commandHasAnArgument();
	bool commandContains(const char);

	void handleCommandWithOneArgument();
	std::string getCommandWithoutArguments();
	int getArgumentPositionInCommand();
	void executeLog();
	
	void handleCommandWithoutArguments();

private:
	std::string mCommand;
	Base::GameData* mGameData;
};

}}

#endif // !POPHEAD_TERMINAL_COMMANDS_COMMANDINTERPRETER_H_
