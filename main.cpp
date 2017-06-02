#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
  
  VideoMode vm(1920,1080);
  RenderWindow window(vm,"MyTimer", Style::Fullscreen);
  
  Texture textureBackGround;
  
  textureBackGround.loadFromFile("graphics/background.png");
  
  Sprite spriteBackGround;
  
  spriteBackGround.setTexture(textureBackGround);
  
  spriteBackGround.setPosition(0,0);
  
  while(window.isOpen())
  {
    if(Keyboard::isKeyPressed(Keyboard::Escape))
    {
      window.close();
    }
    
    window.clear();
    
    window.draw(spriteBackGround);
    
    window.display();
  }
  
  std::cout << "MyTimber" << std::endl;
  return 0;
}