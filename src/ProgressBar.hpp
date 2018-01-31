#ifndef __PROGRESSBAR_HPP__
#define __PROGRESSBAR_HPP__

#include <vector>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

class ProgressBar : public sf::Drawable, public sf::Transformable {
public:
    ProgressBar(const float percentage = 0.0f, const sf::Vector2f size = { 64.f, 8.f });

    void setPercentage(float percentage);
    float getPercentage() const;
    void setSize(sf::Vector2f size);
    sf::Vector2f getSize() const;
    void setColor(sf::Color color);
    sf::Color getColor() const;
    void setShowBackgroundAndFrame(bool showBackgroundAndFrame);
    void setBackgroundColor(sf::Color backgroundColor);
    void setFrameColor(sf::Color frameColor);
    void setTexture(const sf::Texture& texture, bool resetRect = false);

    sf::FloatRect getLocalBounds() const;
    sf::FloatRect getGlobalBounds() const;

    sf::Vector2f getAnchorProgressTop() const;
    sf::Vector2f getAnchorProgressCenter() const;
    sf::Vector2f getAnchorProgressBottom() const;
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void updateGraphics();

    float m_percent;
    sf::Color m_color;
    sf::Vector2f m_size;
    std::vector<sf::Vertex> m_bar;
    const sf::Texture* m_texture;
    sf::IntRect m_textureRectangle;
    bool m_showBackground;
    sf::RectangleShape m_backgroundAndFrame;
    const sf::Texture* m_backgroundTexture;
    sf::IntRect m_backgroundTextureRectangle;
};

#endif /* __PROGRESSBAR_HPP__ */
