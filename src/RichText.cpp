#include "RichText.hpp"

RichText::RichText(const sf::Font &font)
        : m_font(&font),
          m_color(sf::Color::White),
          m_style(sf::Text::Regular),
          m_characterSize(30) {

}

RichText &RichText::operator<<(sf::Text::Style style) {
    m_style = style;
    return *this;
}

RichText &RichText::operator<<(const sf::Color &color) {
    m_color = color;
    return *this;
}

RichText &RichText::operator<<(const sf::String &str) {
    if (str.isEmpty()) {
        return *this;
    }

    std::vector<sf::String> subStrings = explode(str, '\n');

    // Append first substring using the last line
    auto it = subStrings.begin();
    if(it != subStrings.end()) {
        if(m_lines.empty()) {
            m_lines.resize(1);
        }

        // Remove last line's height
        Line &line = m_lines.back();
        m_bounds.height -= line.getGlobalBounds().height;

        // Append Text
        line.appendText(createText(*it));

        // Update bounds
        m_bounds.height += line.getGlobalBounds().height;
        m_bounds.width = std::max(m_bounds.width, line.getGlobalBounds().width);
    }

    while(++it != subStrings.end()) {
        Line line;
        line.setPosition(0.0f, m_bounds.height);
        line.appendText(createText(*it));
        m_lines.push_back(std::move(line));

        // Update bounds
        m_bounds.height += line.getGlobalBounds().height;
        m_bounds.width = std::max(m_bounds.width, line.getGlobalBounds().width);
    }

    return *this;
}

sf::FloatRect RichText::getLocalBounds() const {
    return m_bounds;
}

sf::FloatRect RichText::getGlobalBounds() const {
    return getTransform().transformRect(getLocalBounds());
}

void RichText::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();

    for (const Line &line : m_lines) {
        target.draw(line, states);
    }
}

std::vector<sf::String> RichText::explode(const sf::String &str, sf::Uint32 delimiter) {
    if (str.isEmpty()) {
        return std::vector<sf::String>();
    }

    // For each character in the string
    std::vector<sf::String> result;
    sf::String buffer;

    for (sf::Uint32 character : str) {
        // If we've hit the delimiter character
        if (character == delimiter) {
            // Add them to the result vector
            result.push_back(buffer);
            buffer.clear();
        }
        else {
            // Accumulate the next character into the sequence
            buffer += character;
        }
    }

    // Add to the result if buffer still has contents or if the last character is a delimiter
    if (!buffer.isEmpty() || str[str.getSize() - 1] == delimiter) {
        result.push_back(buffer);
    }

    return result;
}

sf::Text RichText::createText(const sf::String &str) const {
    sf::Text text;
    text.setString(str);
    text.setFillColor(m_color);
    text.setStyle(m_style);
    text.setCharacterSize(m_characterSize);

    if(m_color == sf::Color::Black) {
        text.setOutlineColor(sf::Color::White);
        text.setOutlineThickness(2.0f);
    }

    if(m_font)
        text.setFont(*m_font);

    return text;
}

void RichText::setCharacterSize(unsigned size) {
    m_characterSize = size;
}