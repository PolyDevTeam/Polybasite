#include "ProgressBar.hpp"

ProgressBar::ProgressBar(const float percentage, const sf::Vector2f size)
        : m_percent(percentage),
          m_size(size),
          m_color(sf::Color::White),
          m_bar(4),
          m_texture(nullptr),
          m_textureRectangle(),
          m_showBackground(false),
          m_backgroundAndFrame(size),
          m_backgroundTexture(nullptr),
          m_backgroundTextureRectangle() {
    m_backgroundAndFrame.setFillColor(sf::Color::Black);
    m_backgroundAndFrame.setOutlineColor(sf::Color::White);
    m_backgroundAndFrame.setOutlineThickness(1.f);
}

void ProgressBar::setPercentage(float percentage) {
    m_percent = percentage;
    updateGraphics();
}

float ProgressBar::getPercentage() const {
    return m_percent;
}

void ProgressBar::setSize(sf::Vector2f size) {
    m_size = size;
    updateGraphics();
}

sf::Vector2f ProgressBar::getSize() const {
    return m_size;
}

void ProgressBar::setColor(sf::Color color) {
    m_color = color;
    updateGraphics();
}

sf::Color ProgressBar::getColor() const {
    return m_color;
}

void ProgressBar::setShowBackgroundAndFrame(bool showBackgroundAndFrame) {
    m_showBackground = showBackgroundAndFrame;
}

void ProgressBar::setBackgroundColor(const sf::Color backgroundColor) {
    m_backgroundAndFrame.setFillColor(backgroundColor);
}

void ProgressBar::setFrameColor(const sf::Color frameColor) {
    m_backgroundAndFrame.setOutlineColor(frameColor);
}

void ProgressBar::setTexture(const sf::Texture &texture, const bool resetRect) {
    m_texture = &texture;

    if (resetRect) {
        m_textureRectangle.width = m_texture->getSize().x;
        m_textureRectangle.height = m_texture->getSize().y;
    }

    updateGraphics();
}


sf::FloatRect ProgressBar::getLocalBounds() const {
    if (m_showBackground && m_backgroundAndFrame.getOutlineThickness() > 0.f) {
        const float outlineThickness{m_backgroundAndFrame.getOutlineThickness()};
        return {{0.f - outlineThickness, 0.f - outlineThickness},
                {m_size.x + outlineThickness * 2, m_size.y + outlineThickness * 2}};
    } else
        return {{0.f, 0.f}, m_size};
}

sf::FloatRect ProgressBar::getGlobalBounds() const {
    return getTransform().transformRect(getLocalBounds());
}

sf::Vector2f ProgressBar::getAnchorProgressTop() const {
    return getTransform().transformPoint({ m_size.x * (m_percent / 100.0f), 0.f });
}

sf::Vector2f ProgressBar::getAnchorProgressCenter() const {
    return getTransform().transformPoint({ m_size.x * (m_percent / 100.0f), m_size.y / 2.f });
}

sf::Vector2f ProgressBar::getAnchorProgressBottom() const {
    return getTransform().transformPoint({ m_size.x * (m_percent / 100.0f), m_size.y });
}

void ProgressBar::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();

    if (m_showBackground) {
        target.draw(m_backgroundAndFrame, states);
    }

    states.texture = m_texture;
    target.draw(&m_bar.front(), 4, sf::PrimitiveType::Quads, states);
}

void ProgressBar::updateGraphics() {
    m_backgroundAndFrame.setSize(m_size);
    m_backgroundAndFrame.setTexture(m_backgroundTexture);
    m_backgroundAndFrame.setTextureRect(m_backgroundTextureRectangle);

    const float width{m_size.x * (m_percent / 100.0f)};
    m_bar[0].position = {0.f, 0.f};
    m_bar[1].position = {width, 0.f};
    m_bar[2].position = {width, m_size.y};
    m_bar[3].position = {0.f, m_size.y};

    sf::FloatRect textureRect{m_textureRectangle};
    textureRect.width = textureRect.width * (m_percent / 100.0f);
    m_bar[0].texCoords = {textureRect.left, textureRect.top};
    m_bar[1].texCoords = {textureRect.left + textureRect.width, textureRect.top};
    m_bar[2].texCoords = {textureRect.left + textureRect.width, textureRect.top + textureRect.height};
    m_bar[3].texCoords = {textureRect.left, textureRect.top + textureRect.height};

    for (sf::Vertex &vertex : m_bar) {
        vertex.color = m_color;
    }
}