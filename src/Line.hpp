#ifndef __LINE_HPP__
#define __LINE_HPP__

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <vector>

class Line : public sf::Drawable, public sf::Transformable {
public:
    sf::FloatRect getLocalBounds() const;
    sf::FloatRect getGlobalBounds() const;

    void appendText(sf::Text text);
protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
    void updateTextAndGeometry(sf::Text &text) const;

    std::vector<sf::Text> m_texts;
    mutable sf::FloatRect m_bounds;
};

#endif /* __LINE_HPP__ */
