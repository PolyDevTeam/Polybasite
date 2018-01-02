#include "Line.hpp"

sf::FloatRect Line::getLocalBounds() const {
    return m_bounds;
}

sf::FloatRect Line::getGlobalBounds() const {
    return getTransform().transformRect(getLocalBounds());
}

void Line::appendText(sf::Text text) {
    // Set text offset
    updateTextAndGeometry(text);

    m_texts.push_back(std::move(text));
}

void Line::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();

    for(const sf::Text &text : m_texts) {
        target.draw(text, states);
    }
}

void Line::updateTextAndGeometry(sf::Text &text) const {
    // Set text offset
    text.setPosition(m_bounds.width, 0.0f);

    // Update bounds
    int lineSpacing = text.getFont()->getLineSpacing(text.getCharacterSize());
    m_bounds.height = std::max(m_bounds.height, static_cast<float>(lineSpacing));
    m_bounds.width += text.getGlobalBounds().width;
}