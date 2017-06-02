#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
  
  VideoMode vm(1920,1080);
  RenderWindow window(vm,"MyTimer", Style::Fullscreen);
  
  while(window.isOpen())
  {
    if(Keyboard::isKeyPressed(Keyboard::Escape))
    {
      window.close();
    }
    
    window.clear();
    
    window.display();
  }
  
  std::cout << "MyTimber" << std::endl;
  return 0;
}