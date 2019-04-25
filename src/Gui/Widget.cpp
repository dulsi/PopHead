#include "Widget.hpp"
namespace PopHead {

namespace GUI {
	Widget::Widget()
	{


	}
	void Widget::draw()
	{
		if (misActive)
		{
			mWindow->draw(mSprite);
			for (const auto& k : mWidgetList)
			{
				k.second->draw();
			}
		}
	}

	void Widget::setAlpha(unsigned int alpha) 
	{
	}

	void Widget::update(sf::Time delta)
	{
		if (misActive)
		{
			for (const auto& k : mWidgetList)
			{
				k.second->update(delta);
			}
		}
	}

	void Widget::addWidget(const std::string& name, Widget* ptr) 
	{
		mWidgetList.insert({name,std::unique_ptr<Widget>(ptr) });
		(mWidgetList.end()--)->second->setGameData(mGameData);
		(mWidgetList.end()--)->second->setRoot(this);
	}

	void Widget::hide() 
	{
		misActive = false;
	}

	void Widget::show()
	{
		misActive = true;
	}

	bool Widget::setContentPath(const std::string& path)
	{
		if (!mTexture.loadFromFile(path))
			return false;
		mSprite.setTexture(mTexture);
		return true;
	}

	void Widget::setPosition(const sf::Vector2f& pos) 
	{
		mSprite.setPosition(pos);
	}

	void Widget::setScale(const sf::Vector2f& scale)
	{
		mSprite.setPosition(scale);
	}

	void Widget::setVirtualSize(const sf::Vector2f& size) 
	{
	}

	void Widget::addBehavior(behaviorType type, const std::function<void(Widget*)>& func) 
	{
	}
	Widget* Widget::getWidget(const std::string& name)
	{
		return nullptr;
	}
	void Widget::transform(const sf::Vector2f pos, const sf::Vector2f size) 
	{
	}
	void Widget::setGameData(Base::GameData* GameData)
	{
		mGameData = GameData;
		mWindow = dynamic_cast<sf::RenderWindow*>(&GameData->getRenderer().getWindow());
	}
	bool Widget::isActive()
	{
		return misActive;
	}
	void Widget::setRoot(Widget* ptr)
	{
		mRoot = ptr;
	}
}}