#include "window.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

using namespace pfui;

Window::Window(const std::initializer_list<GUIElement*>& children)
{
  type = ElementType::Window;

  body.shape.setPrimitiveType(sf::TriangleFan);
  body.shape.append(sf::Vertex(sf::Vector2f(-0.5f, -0.5f), sf::Color(150, 50, 0)));
  body.shape.append(sf::Vertex(sf::Vector2f(-0.5f, 0.5f), sf::Color(150, 50, 0)));
  body.shape.append(sf::Vertex(sf::Vector2f(0.5f, 0.5f), sf::Color(150, 50, 0)));
  body.shape.append(sf::Vertex(sf::Vector2f(0.5f, -0.5f), sf::Color(150, 50, 0)));

  titlebar.shape.setPrimitiveType(sf::TriangleFan);
  titlebar.shape.append(sf::Vertex(sf::Vector2f(-0.5f, -0.5f), sf::Color(150, 150, 100)));
  titlebar.shape.append(sf::Vertex(sf::Vector2f(-0.5f, 0.5f), sf::Color(150, 150, 100)));
  titlebar.shape.append(sf::Vertex(sf::Vector2f(0.5f, 0.5f), sf::Color(150, 150, 100)));
  titlebar.shape.append(sf::Vertex(sf::Vector2f(0.5f, -0.5f), sf::Color(150, 150, 100)));
  titlebar.size.y = 0.07f;

  closeSpr.shape.setPrimitiveType(sf::Lines);
  closeSpr.shape.append(sf::Vertex(sf::Vector2f(-0.5f, -0.5f), sf::Color(100, 50, 0)));
  closeSpr.shape.append(sf::Vertex(sf::Vector2f(0.5f, 0.5f), sf::Color(100, 50, 0)));
  closeSpr.shape.append(sf::Vertex(sf::Vector2f(-0.5f, 0.5f), sf::Color(100, 50, 0)));
  closeSpr.shape.append(sf::Vertex(sf::Vector2f(0.5f, -0.5f), sf::Color(100, 50, 0)));
  closeSpr.size = glm::vec2(0.05f);

  maximizeSpr.shape.setPrimitiveType(sf::LineStrip);
  maximizeSpr.shape.append(sf::Vertex(sf::Vector2f(-0.5f, -0.5f), sf::Color(100, 50, 0)));
  maximizeSpr.shape.append(sf::Vertex(sf::Vector2f(-0.5f, 0.5f), sf::Color(100, 50, 0)));
  maximizeSpr.shape.append(sf::Vertex(sf::Vector2f(0.5f, 0.5f), sf::Color(100, 50, 0)));
  maximizeSpr.shape.append(sf::Vertex(sf::Vector2f(0.5f, -0.5f), sf::Color(100, 50, 0)));
  maximizeSpr.shape.append(sf::Vertex(sf::Vector2f(-0.5f, -0.5f), sf::Color(100, 50, 0)));
  maximizeSpr.size = glm::vec2(0.05f);

  minimizeSpr.shape.setPrimitiveType(sf::LineStrip);
  minimizeSpr.shape.append(sf::Vertex(sf::Vector2f(-0.5f, 0.5f), sf::Color(100, 50, 0)));
  minimizeSpr.shape.append(sf::Vertex(sf::Vector2f(0.5f, 0.5f), sf::Color(100, 50, 0)));
  minimizeSpr.size = glm::vec2(0.05f);

  for (GUIElement* child: children)
  {
    this->children.first[this->children.second++] = std::unique_ptr<GUIElement>(child);
  }
}

void Window::setOpen(bool open)
{
  if (open) close = -1;
  else close = 255;
}

bool Window::isOpen()
{
  return close == -1;
}

void Window::setMaximize(bool maximize)
{
  this->maximize = (SCREEN->getSize().y * ((maximize<<1)-1)) / 2.0f;
}

bool Window::isMaximized()
{
  return maximize > -1;
}

void Window::setMinimize(bool minimize)
{
  float pixHeight = SCREEN->getSize().y*size.y;
  this->minimize = pixHeight * ((minimize<<1)-1);
}

bool Window::isMinimized()
{
  return minimize > -1;
}

GUIElement* Window::addChild(GUIElement* child)
{
  if (children.second == 32)
  {
    return nullptr;
  }

  children.first[children.second++].reset(child);
  return children.first[children.second-1].get();
}

bool Window::removeChild()
{
  if (children.second == 0)
  {
    return false;
  }

  children.first[--children.second].reset();
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

uint8_t Window::childNum()
{
  return children.second;
}

void Window::draw(sf::RenderTarget& SCREEN, glm::mat3 transform)
{
  this->SCREEN = &SCREEN;

  if (close == 0) return;

  if (transform == glm::mat3(0.0f))
  {
    transform = normalizationTransform(SCREEN);
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

  glm::mat3 windowTransform = transform * glm::mat3(glm::vec3(size.x*0.5f, 0, 0), glm::vec3(0, size.y*0.5f, 0), glm::vec3(pos.x, pos.y, 1));

  body.draw(SCREEN, windowTransform);

  /*
  size.x,      0, pos.x
       0, size.y, pos.y
       0,      0,     1
  */

  if (hasTitlebar)
  {
    titlebar.pos = glm::vec2(pos.x, pos.y - size.y*0.5f - titlebar.size.y*0.5f);
    titlebar.size.x = size.x;
    titlebar.draw(SCREEN);
  }

  float buttonOffset = titlebar.size.y*0.5f;

  if (closeButton)
  {
    closeSpr.pos = glm::vec2(titlebar.pos.x+(titlebar.size.x*0.5f-buttonOffset), titlebar.pos.y);
    closeSpr.draw(SCREEN);
    buttonOffset += titlebar.size.y;
  }
  if (maximizeButton)
  {
    maximizeSpr.pos = glm::vec2(titlebar.pos.x+(titlebar.size.x*0.5f-buttonOffset), titlebar.pos.y);
    maximizeSpr.draw(SCREEN);
    buttonOffset += titlebar.size.y;
  }
  if (minimizeButton)
  {
    minimizeSpr.pos = glm::vec2(titlebar.pos.x+(titlebar.size.x*0.5f-buttonOffset), titlebar.pos.y);
    minimizeSpr.draw(SCREEN);
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
    children.first[c]->draw(SCREEN, windowTransform);
  }

  bool cursorChanged = false;

  if (held == nullptr)
  {
    if (closeButton && closeSpr.getGlobalBounds().contains(sf::Vector2f(mPos.x, mPos.y)))
    {
      if (dynamic_cast<sf::RenderWindow*>(this->SCREEN))
      {
        sf::Cursor newCursor;
        newCursor.loadFromSystem(sf::Cursor::Hand);
        dynamic_cast<sf::RenderWindow*>(this->SCREEN)->setMouseCursor(newCursor);
        cursorChanged = true;
      }

      if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
      {
        close = 255;
        maximize = -1;

        closeButton = false;
        maximizeButton = false;
        minimizeButton = false;
      }
    }
    if (maximizeButton && maximizeSpr.getGlobalBounds().contains(sf::Vector2f(mPos.x, mPos.y)))
    {
      if (dynamic_cast<sf::RenderWindow*>(this->SCREEN))
      {
        sf::Cursor newCursor;
        newCursor.loadFromSystem(sf::Cursor::Hand);
        dynamic_cast<sf::RenderWindow*>(this->SCREEN)->setMouseCursor(newCursor);
        cursorChanged = true;
      }

      if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
      {
        if (maximize == -1) setMaximize(true);
        if (maximize == 0) setMaximize(false);
      }
    }

    sf::FloatRect minimizeBounds = minimizeSpr.getGlobalBounds();
    minimizeBounds.height = minimizeBounds.width;
    minimizeBounds.top -= minimizeBounds.height;
    if (minimizeButton && minimizeBounds.contains(sf::Vector2f(mPos.x, mPos.y)))
    {
      if (dynamic_cast<sf::RenderWindow*>(this->SCREEN))
      {
        sf::Cursor newCursor;
        newCursor.loadFromSystem(sf::Cursor::Hand);
        dynamic_cast<sf::RenderWindow*>(this->SCREEN)->setMouseCursor(newCursor);
        cursorChanged = true;
      }

      if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
      {
        if (minimize == 0) minimize = -size.y;
        if (minimize == -1) minimize = size.y;
      }
    }
  }

  if (resizeable && held == nullptr)
  {
    const float resizeWidth = 2.0f;
    sf::FloatRect bounds = body.getGlobalBounds();
    float mouseLeftDis = glm::abs(mPos.x - bounds.left);
    float mouseRightDis = glm::abs(mPos.x - (bounds.left + bounds.width));
    float mouseTopDis = glm::abs(mPos.y - bounds.top);
    float mouseBottomDis = glm::abs(mPos.y - (bounds.top + bounds.height));
    if (mouseLeftDis < resizeWidth && mPos.y > bounds.top && mPos.y < bounds.top+bounds.height) // if left edge is grabbed
    {
      if (dynamic_cast<sf::RenderWindow*>(this->SCREEN))
      {
        sf::Cursor newCursor;
        newCursor.loadFromSystem(sf::Cursor::SizeLeft);
        dynamic_cast<sf::RenderWindow*>(this->SCREEN)->setMouseCursor(newCursor);
        cursorChanged = true;
      }

      if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
      {
        held.reset(this, HeldDeleter());
        resizeDirs.flags.left = true;
        resizeDirs.flags.right = false;
        resizeDirs.flags.top = false;
        resizeDirs.flags.bottom = false;
      }
    } else if (mouseRightDis < resizeWidth && mPos.y > bounds.top && mPos.y < bounds.top+bounds.height) // if right edge is grabbed
    {
      if (dynamic_cast<sf::RenderWindow*>(this->SCREEN))
      {
        sf::Cursor newCursor;
        newCursor.loadFromSystem(sf::Cursor::SizeRight);
        dynamic_cast<sf::RenderWindow*>(this->SCREEN)->setMouseCursor(newCursor);
        cursorChanged = true;
      }

      if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
      {
        held.reset(this, HeldDeleter());
        resizeDirs.flags.left = false;
        resizeDirs.flags.right = true;
        resizeDirs.flags.top = false;
        resizeDirs.flags.bottom = false;
      }
    } else if (mPos.x > bounds.left && mPos.x < bounds.left+bounds.width && mouseTopDis < resizeWidth) // if top edge is grabbed
    {
      if (dynamic_cast<sf::RenderWindow*>(this->SCREEN))
      {
        sf::Cursor newCursor;
        newCursor.loadFromSystem(sf::Cursor::SizeTop);
        dynamic_cast<sf::RenderWindow*>(this->SCREEN)->setMouseCursor(newCursor);
        cursorChanged = true;
      }
  
      if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
      {
        held.reset(this, HeldDeleter());
        resizeDirs.flags.left = false;
        resizeDirs.flags.right = false;
        resizeDirs.flags.top = true;
        resizeDirs.flags.bottom = false;
      }
    } else if (mPos.x > bounds.left && mPos.x < bounds.left+bounds.width && mouseBottomDis < resizeWidth) // if bottom edge is grabbed
    {
      if (dynamic_cast<sf::RenderWindow*>(this->SCREEN))
      {
        sf::Cursor newCursor;
        newCursor.loadFromSystem(sf::Cursor::SizeBottom);
        dynamic_cast<sf::RenderWindow*>(this->SCREEN)->setMouseCursor(newCursor);
        cursorChanged = true;
      }

      if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
      {
        held.reset(this, HeldDeleter());
        resizeDirs.flags.left = false;
        resizeDirs.flags.right = false;
        resizeDirs.flags.top = false;
        resizeDirs.flags.bottom = true;
      }
    }
  }

  if (isDraggable && held == nullptr && sf::Mouse::isButtonPressed(sf::Mouse::Left) && ((hasTitlebar && titlebar.getGlobalBounds().contains(sf::Vector2f(mPos.x, mPos.y))) || (!hasTitlebar && body.getGlobalBounds().contains(sf::Vector2f(mPos.x, mPos.y)))))
  {
    held.reset(this, HeldDeleter());
    resizeDirs.value = 0;

    if (dynamic_cast<sf::RenderWindow*>(this->SCREEN))
    {
      sf::Cursor newCursor;
      newCursor.loadFromSystem(sf::Cursor::SizeAll);
      dynamic_cast<sf::RenderWindow*>(this->SCREEN)->setMouseCursor(newCursor);
      cursorChanged = true;
    }
  } else if (held.get() == this)
  {
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
      held = nullptr;
    } else
    {
      cursorChanged = true;
    }
  }

  if (cursorChanged == false && dynamic_cast<sf::RenderWindow*>(this->SCREEN))
  {
    sf::Cursor newCursor;
    newCursor.loadFromSystem(sf::Cursor::Arrow);
    dynamic_cast<sf::RenderWindow*>(this->SCREEN)->setMouseCursor(newCursor);
  }

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

  if (close > 0) {
    close--;
    size.x *= 0.5;
    size.y *= 0.5;
  }
  if (maximize != -1) {
    maximize *= 0.7f;
  }
  if (minimize != -1.0f) {
    minimize *= 0.8f;
  }
}
