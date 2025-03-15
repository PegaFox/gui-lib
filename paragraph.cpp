#include "paragraph.hpp"

using namespace pfui;

Paragraph::Paragraph()
{
  type = ElementType::Paragraph;

  text.setString("Hello, World!");
}

void Paragraph::draw(sf::RenderTarget& SCREEN, glm::mat3 transform)
{
  if (transform == glm::mat3(0.0f))
  {
    transform = normalizationTransform(SCREEN);
  }
  glm::mat3 invTransform = glm::inverse(transform);

  glm::vec2 projectedPos(transform * glm::vec3(pos, 1.0f));
  glm::vec2 projectedSize(transform * glm::vec3(size, 0.0f));

  if (projectedSize.x == 0.0f || projectedSize.y == 0.0f)
  {
    return;
  }

  /*float pos[2] = {
    x.normalized ? windowWidth*x.value : x.value,
    y.normalized ? windowHeight*y.value : y.value
  };
  float size = fontSize.normalized ? (float)windowHeight*fontSize.value : fontSize.value;
  std::string outText(dialogue);
  
  if ((windowWidth - pos[0]) / size < 1.0f || size < 1.0f)
    return std::vector<Element>{};

  for (unsigned int newl = (windowWidth - pos[0]) / size; newl < dialogue.size(); newl += (windowWidth - pos[0]) / size) {
    unsigned int linePos = newl;
    if (wordAlign) {
      linePos = dialogue.substr(0UL, newl).find_last_of(' ');
      if (linePos >= dialogue.size()) {
        outText = dialogue.substr(0UL, newl);
        break;
      }
    }
    outText.replace(linePos, 1, "\n");
    newl = linePos;
  }*/

  text.setCharacterSize(transform[1].y*2.0f);
  text.setFont(font);
  text.setPosition(sf::Vector2f(projectedPos.x, projectedPos.y));
  text.setScale(sf::Vector2f(projectedSize.x/(transform[1].y*2.0f), projectedSize.y/(transform[1].y*2.0f)));

  const std::string originalStr = text.getString();
  std::string paragraphStr = originalStr;

  sf::FloatRect bounds;
  glm::vec2 boundsPos;
  glm::vec2 boundsSize;
  switch (wrapMode)
  {
    case WrapMode::None:
      for (std::size_t pos = paragraphStr.size(); pos > 0; pos--)
      {
        text.setString(paragraphStr.substr(0, pos));

        bounds = text.getGlobalBounds();

        boundsPos = glm::vec2(bounds.position.x, bounds.position.y);
        boundsSize = glm::vec2(bounds.size.x, bounds.size.y);

        boundsPos = invTransform * glm::vec3(boundsPos, 1.0f);
        boundsSize = invTransform * glm::vec3(boundsSize, 0.0f);

        if (boundsPos.x+boundsSize.x <= 1.0f)
        {
          break;
        }
      }

      if (boundsPos.y+boundsSize.y > 1.0f)
      {
        text.setString("");
      }
      break;
    case WrapMode::LetterWrap:
      for (std::size_t pos = 0; pos < paragraphStr.size()-1;)
      {
        for (std::size_t i = paragraphStr.size(); i >= pos; i--)
        {
          text.setString(paragraphStr.substr(pos, i-pos));
          if (text.getString()[0] == '\n')
          {
            pos = -1;
            break;
          }

          bounds = text.getGlobalBounds();

          boundsPos = glm::vec2(bounds.position.x, bounds.position.y);
          boundsSize = glm::vec2(bounds.size.x, bounds.size.y);

          boundsPos = invTransform * glm::vec3(boundsPos, 1.0f);
          boundsSize = invTransform * glm::vec3(boundsSize, 0.0f);

          if (i == pos)
          {
            pos = -1;
            break;
          }

          if (boundsPos.x+boundsSize.x <= 1.0f)
          {
            if (paragraphStr[i] == ' ')
            {
              paragraphStr.erase(i, 1);
            }
            paragraphStr.insert(i, "\n");
            pos = i;
            break;
          }
        }
      }
      text.setString(paragraphStr);

      for (std::size_t i = paragraphStr.size(); i != -1; i = paragraphStr.rfind('\n', i-1))
      {
        text.setString(paragraphStr.substr(0, i));

        bounds = text.getGlobalBounds();

        boundsPos = glm::vec2(bounds.position.x, bounds.position.y);
        boundsSize = glm::vec2(bounds.size.x, bounds.size.y);

        boundsPos = invTransform * glm::vec3(boundsPos, 1.0f);
        boundsSize = invTransform * glm::vec3(boundsSize, 0.0f);

        if (boundsPos.y+boundsSize.y <= 1.0f)
        {
          paragraphStr.erase(i);
          break;
        }
      }

      if (boundsPos.x+boundsSize.x > 1.0f || boundsPos.y+boundsSize.y > 1.0f)
      {
        text.setString("");
      }
      break;
    case WrapMode::WordWrap:
      for (std::size_t pos = 0; pos < paragraphStr.size()-1;)
      {
        for (std::size_t i = paragraphStr.size(); i > pos; i = paragraphStr.rfind(' ', i-1))
        {
          if (i == -1)
          {
            pos = -1;
            wrapMode = WrapMode::LetterWrap;
            break;
          }

          text.setString(paragraphStr.substr(pos, i-pos));

          bounds = text.getGlobalBounds();

          boundsPos = glm::vec2(bounds.position.x, bounds.position.y);
          boundsSize = glm::vec2(bounds.size.x, bounds.size.y);

          boundsPos = invTransform * glm::vec3(boundsPos, 1.0f);
          boundsSize = invTransform * glm::vec3(boundsSize, 0.0f);

          if (boundsPos.x+boundsSize.x <= 1.0f)
          {
            paragraphStr[i] = '\n';
            pos = i;
            break;
          }
        }
      }
      text.setString(paragraphStr);

      for (std::size_t i = paragraphStr.size(); i > 0; i = paragraphStr.rfind('\n', i-1))
      {
        text.setString(paragraphStr.substr(0, i));

        bounds = text.getGlobalBounds();

        boundsPos = glm::vec2(bounds.position.x, bounds.position.y);
        boundsSize = glm::vec2(bounds.size.x, bounds.size.y);

        boundsPos = invTransform * glm::vec3(boundsPos, 1.0f);
        boundsSize = invTransform * glm::vec3(boundsSize, 0.0f);

        if (boundsPos.y+boundsSize.y <= 1.0f)
        {
          paragraphStr.erase(i);
          break;
        }
      }

      if (boundsPos.x+boundsSize.x > 1.0f || boundsPos.y+boundsSize.y > 1.0f)
      {
        text.setString("");
      }
      break;
  }

  SCREEN.draw(text);

  text.setString(originalStr);
}

sf::Font Paragraph::font;
