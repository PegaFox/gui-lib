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
  glm::vec2 projectedPos(transform * glm::vec3(pos, 1.0f));
  glm::vec2 projectedSize(transform * glm::vec3(size, 0.0f));

  float projectedHeight = (transform * glm::vec3(0.0f, this->textHeight, 0.0f)).y;

  if (projectedSize.x == 0.0f || projectedSize.y == 0.0f || this->text.empty() || this->getTextBounds == nullptr)
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
    paragraphStr = this->shiftTextByScroll(paragraphStr);
  }

  paragraphStr = this->wrapText(
    paragraphStr,
    projectedPos,
    projectedSize,
    projectedHeight);

  Rect bounds = getTextBounds(
    this->font,
    paragraphStr.c_str(),
    projectedPos,
    projectedHeight);

  projectedPos -= bounds.size*0.5f;

  if (this->drawText != nullptr)
  {
    this->drawText(this->font, paragraphStr.c_str(), projectedPos, projectedHeight, this->color);
  }

  if (scrollable && bounds.contains(mPos))
  {
    drawStart = glm::clamp((float)drawStart-scrollValue, 0.0f, (float)originalStr.size());
    scrollValue = 0.0f;
  }
}

Rect Paragraph::getTextLocalBounds(
  const std::string& text,
  const glm::vec2 globalPos,
  const float globalHeight,
  const glm::mat3& invTransform) const
{
  Rect bounds = this->getTextBounds(this->font, text.c_str(), globalPos, globalHeight);

  bounds.position = invTransform * glm::vec3(bounds.position, 1.0f);
  bounds.size = invTransform * glm::vec3(bounds.size, 0.0f);

  return bounds;
}

std::string& Paragraph::shiftTextByScroll(std::string& text) const
{
  std::size_t pos = 0;
  for (uint32_t l = 0; l < drawStart; l++)
  {
    pos = text.find('\n', pos)+1;
  }
  text.erase(0, pos);

  return text;
}

std::string& Paragraph::wrapText(
  std::string& text,
  const glm::vec2 projectedPos,
  const glm::vec2 projectedSize,
  const float projectedHeight) const
{
  std::string newText;

  glm::mat3 invTransform = glm::inverse(transform);

  // Because I've had to deal with way too many infinite loop bugs
  uint32_t iterLimit = 0;
  const uint32_t maxIter = this->text.size();

  Rect bounds;
  switch (wrapMode)
  {
    case WrapMode::None:
      for (std::size_t pos = text.size(); pos > 0; pos--)
      {
        newText = text.substr(0, pos);

        bounds = this->getTextLocalBounds(this->text, projectedPos, projectedHeight, invTransform);

        if (bounds.position.x+bounds.size.x <= 2.0f)
        {
          break;
        }
      }

      if (bounds.position.y+bounds.size.y > 2.0f)
      {
        //newText.setString("");
      }
      break;
    case WrapMode::LetterWrap:
      iterLimit = 0;
      for (std::size_t pos = 0; pos < text.size()-1 && iterLimit < maxIter; iterLimit++)
      {
        for (std::size_t i = text.size(); i > pos; i--)
        {
          newText = text.substr(pos, i-pos);
          if (newText[0] == '\n')
          {
            pos = -1;
            break;
          }

          bounds = this->getTextLocalBounds(this->text, projectedPos, projectedHeight, invTransform);

          if (i == pos)
          {
            pos = -1;
            break;
          }

          if (bounds.position.x+bounds.size.x <= 2.0f)
          {
            if (text[i] == ' ')
            {
              text.erase(i, 1);
            }
            text.insert(i, "\n");
            pos = i;
            break;
          }
        }
      }
      newText = text;

      iterLimit = 0;
      for (std::size_t i = text.size(); i != -1 && iterLimit < maxIter; i = text.rfind('\n', i-1), iterLimit++)
      {
        newText = text.substr(0, i);

        bounds = this->getTextLocalBounds(this->text, projectedPos, projectedHeight, invTransform);

        if (bounds.position.y+bounds.size.y <= 2.0f)
        {
          text.erase(i);
          break;
        }
      }

      if (bounds.position.x+bounds.size.x > 2.0f || bounds.position.y+bounds.size.y > 2.0f)
      {
        text = "";
      }
      break;
    case WrapMode::WordWrap:
      iterLimit = 0;
      for (std::size_t pos = 0; pos < text.size()-1 && iterLimit < maxIter; iterLimit++)
      {
        for (std::size_t i = text.size(); i > pos; i = text.rfind(' ', i-1))
        {
          if (i == -1)
          {
            pos = -1;
            //wrapMode = WrapMode::LetterWrap;
            break;
          }

          newText = text.substr(pos, i-pos);

          bounds = this->getTextLocalBounds(this->text, projectedPos, projectedHeight, invTransform);

          if (bounds.position.x+bounds.size.x <= 2.0f)
          {
            text[i] = '\n';
            pos = i;
            break;
          }
        }
      }
      newText = text;

      iterLimit = 0;
      for (std::size_t i = text.size(); i > 0 && iterLimit < maxIter; i = text.rfind('\n', i-1), iterLimit++)
      {
        newText = text.substr(0, i);

        bounds = this->getTextLocalBounds(this->text, projectedPos, projectedHeight, invTransform);

        if (bounds.position.y+bounds.size.y <= 2.0f)
        {
          text.erase(i);
          break;
        }
      }

      if (bounds.position.x+bounds.size.x > 2.0f || bounds.position.y+bounds.size.y > 2.0f)
      {
        newText = "";
      }
      break;
  }

  //text = newText;

  return text;
}
