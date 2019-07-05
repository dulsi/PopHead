#include "States/state.hpp"

#include "World/Entity/entityType.hpp"

namespace ph {

State::State(GameData* const gameData)
	:mRoot(EntityType::none, gameData, "root")
	,mGameData(gameData)
	,mSceneParser(gameData, mRoot, "scene.xml")
	,mHide(false)
	,mPause(false)
{
}

}