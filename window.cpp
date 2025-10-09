#include "window.hpp"
#include <iostream>

#include <SFML/Window/Cursor.hpp>

using namespace pfui;

Window::Window(const std::initializer_list<GUIElement*>& children)
{
  init(children.begin(), children.end());
}

Window::Window(GUIElement* const * childrenBegin, GUIElement* const * childrenEnd)
{
  init(childrenBegin, childrenEnd);
}
    
void Window::setOpen(bool open)
{
  if (open) close = 1.0f;
  else close = 0.99f;
}

bool Window::isOpen()
{
  return close == 1.0f;
}

void Window::setMaximize(bool maximize)
{
  if (maximize && this->maximize == 0.0f) this->maximize = 0.01f;
  else if (!maximize && this->maximize == 1.0f) this->maximize = -1.0f;
}

bool Window::isMaximized()
{
  return maximize > 0.0f;
}

void Window::setMinimize(bool minimize)
{
  if (minimize && this->minimize == 1.0f) this->minimize = 0.99f;
  else if (!minimize && this->minimize == 0.0f) this->minimize = -0.01f;
}

bool Window::isMinimized()
{
  return minimize < 1.0f && minimize >= 0.0f;
}

GUIElement* Window::addChild(GUIElement* child, uint8_t index)
{
  if (index == uint8_t(-1))
  {
    index = children.second;
  }

  if (children.second == 32 || index > children.second)
  {
    return nullptr;
  }

  std::move_backward(&children.first[index], &children.first[children.second++], &children.first[index+1]);
  children.first[index].reset(child);
  return children.first[index].get();
}

bool Window::removeChild(uint8_t index)
{
  if (index == uint8_t(-1))
  {
    index = children.second-1;
  }

  if (index >= children.second)
  {
    return false;
  }

  children.first[index].reset();
  std::move(&children.first[index+1], &children.first[children.second--], &children.first[index]);
  return true;
}

GUIElement* Window::operator[](uint8_t index)
{
  if (index < children.second)
  {
    return children.first[index].get();
  }
  return nullptr;
}

uint8_t Window::childCount()
{
  return children.second;
}

Rect Window::getGlobalBounds() const
{
  return Rect{titlebar.getGlobalBounds().position, body.getGlobalBounds().size+glm::vec2(0.0f, titlebar.getGlobalBounds().size.y)};
}

GUIElement::ElementType Window::getType() const
{
  return ElementType::Window;
}

void Window::draw()
{
  if (close == 0.0f) return;

  if (transform == glm::mat3(0.0f))
  {
    transform = normalizationTransform(glm::vec2(2.0f));
  }

  //if (width.value < 0.0f) width.value = 0.0f;
  //if (height.value < 0.0f) height.value = 0.0f;
  //if (titlebarHeight.value < 0.0f) titlebarHeight.value = 0.0f;

  /*float pos[2] = {
    x.normalized ? windowWidth*x.value : x.value,
    y.normalized ? windowHeight*y.value : y.value
  };*/
  /*float size[2] = {
    width.normalized ? windowWidth*width.value : width.value,
    height.normalized ? windowHeight*height.value : height.value
  };*/
  /*float halfSize[2] = {
    size[0]/2.0f, size[1]/2.0f
  };
  float titlebarSize = titlebarHeight.normalized ? windowHeight*titlebarHeight.value : titlebarHeight.value;*/

  /*if (minimize > -1) {
    halfSize[1] = minimize/2.0f;
  }
  if (minimize < -1) {
    halfSize[1] = (minimize+size[1])/2.0f;
  }
  if (maximize > -1) {
    pos[0] = windowWidth/2.0f;
    pos[1] = (windowHeight/2.0f)+titlebarSize/2.0f;
    halfSize[0] = -(maximize-windowWidth/2.0f);
    halfSize[1] = -(maximize-windowHeight/2.0f)-titlebarSize/2.0f;
  }
  if (maximize < -1) {
    pos[0] = windowWidth/2.0f;
    pos[1] = (windowHeight/2.0f)+titlebarSize/2.0f;
    halfSize[0] = size[0]/2.0f-maximize;
    halfSize[1] = size[1]/2.0f-maximize-titlebarSize/2.0f;
  }*/

  // background
  /*result.push_back(Element{
    std::vector<std::array<float, 2>>{
      {pos[0]-halfSize[0], pos[1]-halfSize[1]},
      {pos[0]+halfSize[0], pos[1]-halfSize[1]},
      {pos[0]+halfSize[0], pos[1]+halfSize[1]},
      {pos[0]-halfSize[0], pos[1]+halfSize[1]}
    },
    {char(79), char(41), char(35), close < 0 ? char(255) : char(close)},
    triangleFan
  });*/
  //body.pos = pos;
  //body.size = size;

  glm::vec2 modifiedPos = glm::mix(pos, glm::vec2(0.0f, hasTitlebar * titlebar.size.y*0.5f), glm::abs(maximize));
  modifiedPos.y -= (1.0f - glm::abs(minimize))*size.y*0.5f;

  glm::vec2 modifiedSize = glm::mix(size, glm::vec2(2.0f, 2.0f - hasTitlebar * titlebar.size.y), glm::abs(maximize)) * close;
  modifiedSize.y *= glm::abs(minimize);

  glm::mat3 windowTransform = transform * glm::mat3(glm::vec3(modifiedSize.x*0.5f, 0, 0), glm::vec3(0, modifiedSize.y*0.5f, 0), glm::vec3(modifiedPos.x, modifiedPos.y, 1));

  body.transform = windowTransform;
  body.draw();

  /*
  size.x,      0, pos.x
       0, size.y, pos.y
       0,      0,     1
  */

  if (hasTitlebar)
  {
    titlebar.pos = glm::vec2(modifiedPos.x, modifiedPos.y - modifiedSize.y*0.5f - titlebar.size.y*0.5f);
    titlebar.size.x = modifiedSize.x;
    titlebar.draw();

    if (close == 1.0f)
    {
      float buttonOffset = titlebar.size.y*0.5f;

      if (closeButton)
      {
        closeSpr.pos = glm::vec2(titlebar.pos.x+(titlebar.size.x*0.5f-buttonOffset), titlebar.pos.y);
        closeSpr.draw();
        buttonOffset += titlebar.size.y;
      }
      if (maximizeButton)
      {
        maximizeSpr.pos = glm::vec2(titlebar.pos.x+(titlebar.size.x*0.5f-buttonOffset), titlebar.pos.y);
        maximizeSpr.draw();
        buttonOffset += titlebar.size.y;
      }
      if (minimizeButton)
      {
        minimizeSpr.pos = glm::vec2(titlebar.pos.x+(titlebar.size.x*0.5f-buttonOffset), titlebar.pos.y);
        minimizeSpr.draw();
      }
    }
  }

  // contents
  /*float corner[2] = {
    pos[0] - halfSize[0],
    pos[1] - halfSize[1]
  };
  for (unsigned int widget = 0; widget < contents.size(); widget++) {
    std::vector<Element> drawData = contents[widget]->update(halfSize[0]*2.0f, halfSize[1]*2.0f);
    for (unsigned int element = 0; element < drawData.size(); element++) {
      for (unsigned int vertex = 0; vertex < drawData[element].vertices.size(); vertex++)
        drawData[element].vertices[vertex] = {
          corner[0] + drawData[element].vertices[vertex][0],
          corner[1] + drawData[element].vertices[vertex][1]
        };
      drawData[element].color[3] = close < 0 ? drawData[element].color[3] : char(close);
    }
    result.insert(result.end(), drawData.begin(), drawData.end());
  }*/

  for (uint8_t c = 0; c < children.second; c++)
  {
    children.first[c]->transform = windowTransform;
    children.first[c]->draw();
  }

  bool cursorChanged = false;

  if (hasTitlebar && held == nullptr)
  {
    if (closeButton && closeSpr.getGlobalBounds().contains(mPos))
    {
      /*if (dynamic_cast<sf::RenderWindow*>(this->SCREEN))
      {
        sf::Cursor newCursor(sf::Cursor::Type::Hand);
        dynamic_cast<sf::RenderWindow*>(this->SCREEN)->setMouseCursor(newCursor);
        cursorChanged = true;
      }*/

      if (this->mPressed.states.left)
      {
        setOpen(false);
        maximize = -1;
      }
    }
    if (maximizeButton && maximizeSpr.getGlobalBounds().contains(mPos))
    {
      /*jif (dynamic_cast<sf::RenderWindow*>(this->SCREEN))
      {
        sf::Cursor newCursor(sf::Cursor::Type::Hand);
        dynamic_cast<sf::RenderWindow*>(this->SCREEN)->setMouseCursor(newCursor);
        cursorChanged = true;
      }*/

      if (this->mPressed.states.left)
      {
        setMinimize(false);
        setMaximize(!isMaximized());
      }
    }

    Rect minimizeBounds = minimizeSpr.getGlobalBounds();
    minimizeBounds.size.y = minimizeBounds.size.x;
    minimizeBounds.position.y -= minimizeBounds.size.y;
    if (minimizeButton && minimizeBounds.contains(mPos))
    {
      /*if (dynamic_cast<sf::RenderWindow*>(this->SCREEN))
      {
        sf::Cursor newCursor(sf::Cursor::Type::Hand);
        dynamic_cast<sf::RenderWindow*>(this->SCREEN)->setMouseCursor(newCursor);
        cursorChanged = true;
      }*/

      if (this->mPressed.states.left)
      {
        setMaximize(false);
        setMinimize(!isMinimized());
      }
    }
  }

  if (resizeable && minimize == 1.0f && held == nullptr)
  {
    const float resizeWidth = 0.02f; // the area around the edges of the window where clicking and dragging will resize it
    Rect bounds = body.getGlobalBounds();
    float mouseLeftDis = glm::abs(mPos.x - bounds.position.x);
    float mouseRightDis = glm::abs(mPos.x - (bounds.position.x + bounds.size.x));
    float mouseTopDis = glm::abs(mPos.y - bounds.position.y);
    float mouseBottomDis = glm::abs(mPos.y - (bounds.position.y + bounds.size.y));
    if (mouseLeftDis < resizeWidth && mPos.y > bounds.position.y && mPos.y < bounds.position.y+bounds.size.y) // if left edge is grabbed
    {
      /*if (dynamic_cast<sf::RenderWindow*>(this->SCREEN))
      {
        sf::Cursor newCursor(sf::Cursor::Type::SizeLeft);
        dynamic_cast<sf::RenderWindow*>(this->SCREEN)->setMouseCursor(newCursor);
        cursorChanged = true;
      }*/

      if (this->mPressed.states.left)
      {
        held.reset(this, HeldDeleter());
        resizeDirs.flags.left = true;
        resizeDirs.flags.right = false;
        resizeDirs.flags.top = false;
        resizeDirs.flags.bottom = false;
      }
    } else if (mouseRightDis < resizeWidth && mPos.y > bounds.position.y && mPos.y < bounds.position.y+bounds.size.y) // if right edge is grabbed
    {
      /*if (dynamic_cast<sf::RenderWindow*>(this->SCREEN))
      {
        sf::Cursor newCursor(sf::Cursor::Type::SizeRight);
        dynamic_cast<sf::RenderWindow*>(this->SCREEN)->setMouseCursor(newCursor);
        cursorChanged = true;
      }*/

      if (this->mPressed.states.left)
      {
        held.reset(this, HeldDeleter());
        resizeDirs.flags.left = false;
        resizeDirs.flags.right = true;
        resizeDirs.flags.top = false;
        resizeDirs.flags.bottom = false;
      }
    } else if (mPos.x > bounds.position.x && mPos.x < bounds.position.x+bounds.size.x && mouseTopDis < resizeWidth) // if top edge is grabbed
    {
      /*if (dynamic_cast<sf::RenderWindow*>(this->SCREEN))
      {
        sf::Cursor newCursor(sf::Cursor::Type::SizeTop);
        dynamic_cast<sf::RenderWindow*>(this->SCREEN)->setMouseCursor(newCursor);
        cursorChanged = true;
      }*/
  
      if (this->mPressed.states.left)
      {
        held.reset(this, HeldDeleter());
        resizeDirs.flags.left = false;
        resizeDirs.flags.right = false;
        resizeDirs.flags.top = true;
        resizeDirs.flags.bottom = false;
      }
    } else if (mPos.x > bounds.position.x && mPos.x < bounds.position.x+bounds.size.x && mouseBottomDis < resizeWidth) // if bottom edge is grabbed
    {
      /*if (dynamic_cast<sf::RenderWindow*>(this->SCREEN))
      {
        sf::Cursor newCursor(sf::Cursor::Type::SizeBottom);
        dynamic_cast<sf::RenderWindow*>(this->SCREEN)->setMouseCursor(newCursor);
        cursorChanged = true;
      }*/

      if (this->mPressed.states.left)
      {
        held.reset(this, HeldDeleter());
        resizeDirs.flags.left = false;
        resizeDirs.flags.right = false;
        resizeDirs.flags.top = false;
        resizeDirs.flags.bottom = true;
      }
    }
  }

  //std::cout << titlebar.getGlobalBounds().position.x << ", " << titlebar.getGlobalBounds().position.y << ", " << titlebar.getGlobalBounds().size.x << ", " << titlebar.getGlobalBounds().size.y << " | " << mPos.x << ", " << mPos.y << "\n";
  //std::cout << isDraggable << ", " << (held == nullptr) << ", " << sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) << ", " << hasTitlebar << ", " << titlebar.getGlobalBounds().contains(mPos) << ", " << body.getGlobalBounds().contains(mPos) << "\n";

  if (isDraggable && held == nullptr && this->mPressed.states.left && ((hasTitlebar && titlebar.getGlobalBounds().contains(mPos)) || (!hasTitlebar && body.getGlobalBounds().contains(mPos))))
  {
    held.reset(this, HeldDeleter());
    resizeDirs.value = 0;

    /*if (dynamic_cast<sf::RenderWindow*>(this->SCREEN))
    {
      sf::Cursor newCursor(sf::Cursor::Type::SizeAll);
      dynamic_cast<sf::RenderWindow*>(this->SCREEN)->setMouseCursor(newCursor);
      cursorChanged = true;
    }*/
  } else if (held.get() == this)
  {
    if (!this->mPressed.states.left)
    {
      held = nullptr;
    } else
    {
      cursorChanged = true;
    }
  }

  /*if (cursorChanged == false && dynamic_cast<sf::RenderWindow*>(this->SCREEN))
  {
    sf::Cursor newCursor(sf::Cursor::Type::Arrow);
    dynamic_cast<sf::RenderWindow*>(this->SCREEN)->setMouseCursor(newCursor);
  }*/

  //keep window on-screen
  /*if (windowBind) {
    if (pos[0] - halfSize[0] < 0)
      x.value -= x.normalized ? (pos[0] - halfSize[0]) / windowWidth : pos[0] - halfSize[0];
    if (pos[0] + halfSize[0] > windowWidth)
      x.value -= x.normalized ? (pos[0] + halfSize[0] - windowWidth) / windowWidth : pos[0] + halfSize[0] - windowWidth;
    if (pos[1] - halfSize[1] - titlebarSize < 0)
      y.value -= y.normalized ? (pos[1] - halfSize[1] - titlebarSize) / windowHeight : pos[1] - halfSize[1] - titlebarSize;
    if (pos[1] + halfSize[1] > windowHeight)
      y.value -= y.normalized ? (pos[1] + halfSize[1] - windowHeight) / windowHeight : pos[1] + halfSize[1] - windowHeight;
  }*/

  if (close != 1.0f)
  {
    close *= 0.65f;
    if (close < 0.01f)
    {
      close = 0.0f;
    }
  }

  if (maximize > 0.0f)
  {
    maximize = (maximize-1.0f)*0.8f + 1.0f;
    if (maximize > 0.99f)
    {
      maximize = 1.0f;
    }
  } else if (maximize < 0.0f)
  {
    maximize *= 0.8f;
    if (maximize > -0.01f)
    {
      maximize = 0.0f;
    }
  }

  if (minimize > 0.0f && minimize < 1.0f)
  {
    minimize *= 0.8f;
    if (minimize < 0.01f)
    {
      minimize = 0.0f;
    }
  } else if (minimize < 0.0f)
  {
    minimize = (minimize+1.0f)*0.8f - 1.0f;
    if (minimize < -0.99f)
    {
      minimize = 1.0f;
    }
  }
}

void Window::init(GUIElement* const * childrenBegin, GUIElement* const * childrenEnd)
{
  this->body.color = defaultBackgroundColor;
  this->body.vertices.emplace_back(-0.5f, -0.5f);
  this->body.vertices.emplace_back(0.5f, 0.5f);

  this->titlebar.color = defaultBorderColor;
  this->titlebar.vertices.emplace_back(-0.5f, -0.5f);
  this->titlebar.vertices.emplace_back(0.5f, 0.5f);
  this->titlebar.size.y = 0.07f;

  this->closeSpr.color = defaultObjectColor;
  this->closeSpr.vertices.insert(closeSpr.vertices.end(), {
    glm::vec2(-0.5f, -0.5f),
    glm::vec2(0.5f, 0.5f),
    glm::vec2(-0.5f, 0.5f),
    glm::vec2(0.5f, -0.5f),
  });
  this->closeSpr.size = glm::vec2(0.05f);

  this->maximizeSpr.color = defaultObjectColor;
  this->maximizeSpr.vertices.insert(maximizeSpr.vertices.end(), {
    glm::vec2(-0.5f, -0.5f),
    glm::vec2(-0.5f, 0.5f),
    glm::vec2(0.5f, 0.5f),
    glm::vec2(0.5f, -0.5f),
    glm::vec2(-0.5f, -0.5f),
  });
  maximizeSpr.size = glm::vec2(0.05f);

  this->minimizeSpr.color = defaultObjectColor;
  this->minimizeSpr.vertices.insert(minimizeSpr.vertices.end(), {
    glm::vec2(-0.5f, 0.5f),
    glm::vec2(0.5f, 0.5f),
  });
  minimizeSpr.size = glm::vec2(0.05f);

  for (GUIElement* const * child = childrenBegin; child != childrenEnd; child++)
  {
    this->children.first[this->children.second++] = std::unique_ptr<GUIElement>(*child);
  }
}

