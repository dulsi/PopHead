#include "TextWidget.hpp"

namespace PopHead {
	namespace GUI {


	TextWidget::TextWidget()
		:mTextPosition{ 0,0 }
	{
	}


	void TextWidget::setString(const std::string& text)
	{
		mText.setString(text);
	}

	void TextWidget::setColor(const sf::Color& color)
	{
		mText.setFillColor(color);
	}

	void TextWidget::setTextPosition(const sf::Vector2f& pos)
	{
		auto localPosition = getGlobalPosition();
		auto size = getSize();

		mText.setPosition(pos.x * size.x + localPosition.x , pos.y * size.y + localPosition.y);
	}

	void TextWidget::setAlpha(unsigned int alpha)
	{
		mText.setFillColor(sf::Color(255, 255, 255, alpha));
		Widget::setAlpha(alpha);
	}

	void TextWidget::setTextOrigin(const sf::Vector2f& origin)
	{
		mText.setOrigin(origin);
	}

	void TextWidget::setTextAlpha(unsigned int alpha)
	{
		mText.setFillColor(sf::Color(255, 255, 255, alpha));
	}

	void TextWidget::scaleText(const sf::Vector2f& scale)
	{
		mText.scale(scale);
	}

	void TextWidget::setPosition(const sf::Vector2f& pos)
	{
		Widget::setPosition(pos);
		mText.setPosition(Widget::getGlobalPosition());
	}

	void TextWidget::move(const sf::Vector2f& delta)
	{
		Widget::move(delta);
		mText.move(delta);
	}

	void TextWidget::setCharacterSize(unsigned int size)
	{
		mText.setCharacterSize(size);
	}

	void TextWidget::setFontPath(const std::string& path)
	{
		mText.setFont(mGameData->getFonts().get(path));
	}

	void TextWidget::draw()
	{
		if (misActive)
		{
			Widget::draw();
			mWindow->draw(mText);
		}
	}

}}

