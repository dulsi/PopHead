#pragma once

#include "Audio/Music/musicPlayer.hpp"
#include "Audio/Sound/soundPlayer.hpp"
#include "gameData.hpp"
#include "Renderer/renderer.hpp"
#include "Scenes/sceneManager.hpp"
#include "Map/map.hpp"
#include "Input/input.hpp"
#include "Resources/resourceHolder.hpp"
#include "Physics/physicsEngine.hpp"
#include "Terminal/terminal.hpp"
#include "EfficiencyRegister/efficiencyRegister.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>

namespace ph {

class Game
{
public:
	Game();

	void run();
	inline auto getGameData() const -> const GameData & { return *(mGameData); };
	Terminal* getTerminal() { return mTerminal.get(); }

private:
	void input();
	void update(sf::Time delta);
	void draw();

	std::unique_ptr< GameData >           mGameData;
	sf::RenderWindow                      mRenderWindow;
	std::unique_ptr< SoundPlayer >        mSoundPlayer;
	std::unique_ptr< MusicPlayer >        mMusicPlayer;
	std::unique_ptr< TextureHolder >      mTextures;
	std::unique_ptr< FontHolder >         mFonts;
	std::unique_ptr< ShaderHolder >       mShaders;
	std::unique_ptr< SceneManager >       mSceneMachine;
	std::unique_ptr< Map >                mMap;
	std::unique_ptr< Input >              mInput;
	std::unique_ptr< Renderer >           mRenderer;
	std::unique_ptr< PhysicsEngine >      mPhysicsEngine;
	std::unique_ptr< Terminal >           mTerminal;
	std::unique_ptr< EfficiencyRegister > mEfficiencyRegister;
	std::unique_ptr< GUI >                mGui;
};

}
