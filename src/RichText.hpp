#ifndef __RICHTEXT_HPP__
#define __RICHTEXT_HPP__

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>

#include <vector>

#include "Line.hpp"

class RichText : public sf::Drawable, public sf::Transformable {
public:
    RichText();
    RichText(const sf::Font &font);

    RichText& operator<<(const sf::Color &color);
    RichText& operator<<(sf::Text::Style style);
    RichText& operator<<(const sf::String &str);

    sf::FloatRect getLocalBounds() const;
    sf::FloatRect getGlobalBounds() const;

    void setCharacterSize (unsigned size);
protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
    std::vector<sf::String> explode(const sf::String &str, sf::Uint32 delimiter);
    sf::Text createText(const sf::String &string) const;

    const sf::Font* m_font;
    sf::Color m_color;
    sf::Text::Style m_style;
    unsigned int m_characterSize;
    sf::FloatRect m_bounds;
    std::vector<Line> m_lines;
};

#endif /* __RICHTEXT_HPP__ */
