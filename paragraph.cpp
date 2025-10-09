#include "paragraph.hpp"

using namespace pfui;

Rect Paragraph::getGlobalBounds() const
{
  return Rect{glm::vec2(0.0f), glm::vec2(0.0f)};
}

GUIElement::ElementType Paragraph::getType() const
{
  return ElementType::Paragraph;
}

void Paragraph::draw()
{
  if (transform == glm::mat3(0.0f))
  {
    transform = normalizationTransform(glm::vec2(2.0f));
  }
  glm::mat3 invTransform = glm::inverse(transform);

  glm::vec2 projectedPos(transform * glm::vec3(pos, 1.0f));
  glm::vec2 projectedSize(transform * glm::vec3(size, 0.0f));

  float projectedHeight = (transform * glm::vec3(0.0f, this->textHeight, 0.0f)).y;

  if (projectedSize.x == 0.0f || projectedSize.y == 0.0f || this->getTextBounds == nullptr)
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

  //text.setCharacterSize(transform[1].y*2.0f);
  //text.setScale(sf::Vector2f(projectedSize.x/(transform[1].y*2.0f), projectedSize.y/(transform[1].y*2.0f)));

  const std::string originalStr = this->text;
  std::string paragraphStr = originalStr;

  if (scrollable)
  {
    std::size_t pos = 0;
    for (uint32_t l = 0; l < drawStart; l++)
    {
      pos = paragraphStr.find('\n', pos)+1;
    }
    paragraphStr.erase(0, pos);
  }

  Rect bounds;
  switch (wrapMode)
  {
    case WrapMode::None:
      for (std::size_t pos = paragraphStr.size(); pos > 0; pos--)
      {
        text = paragraphStr.substr(0, pos);

        bounds = this->getTextBounds(this->font, this->text, projectedPos, this->textHeight);

        bounds.position = invTransform * glm::vec3(bounds.position, 1.0f);
        bounds.size = invTransform * glm::vec3(bounds.size, 0.0f);

        if (bounds.position.x+bounds.size.x <= 1.0f)
        {
          break;
        }
      }

      if (bounds.position.y+bounds.size.y > 1.0f)
      {
        //text.setString("");
      }
      break;
    case WrapMode::LetterWrap:
      for (std::size_t pos = 0; pos < paragraphStr.size()-1;)
      {
        for (std::size_t i = paragraphStr.size(); i >= pos; i--)
        {
          text = paragraphStr.substr(pos, i-pos);
          if (text[0] == '\n')
          {
            pos = -1;
            break;
          }

          bounds = this->getTextBounds(this->font, this->text, projectedPos, this->textHeight);

          bounds.position = invTransform * glm::vec3(bounds.position, 0.0f);
          bounds.size = invTransform * glm::vec3(bounds.size, 0.0f);

          if (i == pos)
          {
            pos = -1;
            break;
          }

          if (bounds.position.x+bounds.size.x <= 1.0f)
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
      text = paragraphStr;

      for (std::size_t i = paragraphStr.size(); i != -1; i = paragraphStr.rfind('\n', i-1))
      {
        text = paragraphStr.substr(0, i);

        bounds = this->getTextBounds(this->font, this->text, projectedPos, this->textHeight);

        bounds.position = invTransform * glm::vec3(bounds.position, 0.0f);
        bounds.size = invTransform * glm::vec3(bounds.size, 0.0f);

        if (bounds.position.y+bounds.size.y <= 1.0f)
        {
          paragraphStr.erase(i);
          break;
        }
      }

      if (bounds.position.x+bounds.size.x > 1.0f || bounds.position.y+bounds.size.y > 1.0f)
      {
        text = "";
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

          text = paragraphStr.substr(pos, i-pos);

          bounds = this->getTextBounds(this->font, this->text, projectedPos, projectedHeight);

          bounds.position = invTransform * glm::vec3(bounds.position, 1.0f);
          bounds.size = invTransform * glm::vec3(bounds.size, 0.0f);

          if (bounds.position.x+bounds.size.x <= 1.0f)
          {
            paragraphStr[i] = '\n';
            pos = i;
            break;
          }
        }
      }
      text = paragraphStr;

      for (std::size_t i = paragraphStr.size(); i > 0; i = paragraphStr.rfind('\n', i-1))
      {
        text = paragraphStr.substr(0, i);

        bounds = this->getTextBounds(this->font, this->text, projectedPos, projectedHeight);

        bounds.position = invTransform * glm::vec3(bounds.position, 1.0f);
        bounds.size = invTransform * glm::vec3(bounds.size, 0.0f);

        if (bounds.position.y+bounds.size.y <= 1.0f)
        {
          paragraphStr.erase(i);
          break;
        }
      }

      if (bounds.position.x+bounds.size.x > 1.0f || bounds.position.y+bounds.size.y > 1.0f)
      {
        text = "";
      }
      break;
  }

  if (this->drawText != nullptr)
  {
    this->drawText(this->font, this->text, projectedPos, projectedHeight, this->color);
  }

  if (scrollable && this->getTextBounds(this->font, this->text, projectedPos, this->textHeight).contains(mPos))
  {
    drawStart = glm::clamp((float)drawStart-scrollValue, 0.0f, (float)originalStr.size());
    scrollValue = 0.0f;
  }

  text = originalStr;
}
