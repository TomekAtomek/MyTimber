#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

typedef struct mysprite
{
  Sprite sprite;
  bool isActive;
  float moveSpeed;
  
} MySprite;

int main()
{
  uint8_t c = 'c';
  VideoMode vm(1920,1080);
  RenderWindow window(vm,"MyTimer", Style::Fullscreen);
  
  Texture textureBackGround;
  
  textureBackGround.loadFromFile("graphics/background.png");
  
  Sprite spriteBackGround;
  
  spriteBackGround.setTexture(textureBackGround);
  
  spriteBackGround.setPosition(0,0);
  
  Texture textureTree;
  
  textureTree.loadFromFile("graphics/tree.png");
  
  Sprite spriteTree;
  
  spriteTree.setTexture(textureTree);
  
  spriteTree.setPosition(810,0);
  
  Texture textureBee;
  
  textureBee.loadFromFile("graphics/bee.png");
  
  Sprite spriteBee;
  
  spriteBee.setTexture(textureBee);
  
  spriteBee.setPosition(0,800);
  
  bool beeActive = false;
  
  float beeSpeed = 0.0f;
  
  
  Texture textureCloud;
  
  textureCloud.loadFromFile("graphics/cloud.png");
  
  std::vector<MySprite> clouds;
  
  for(int i = 0; i < 3; ++i)
  {
    Sprite spriteCloud;
    spriteCloud.setTexture(textureCloud);
    spriteCloud.setPosition(0,250 * i);
    MySprite mySprite;
    mySprite.sprite = spriteCloud;
    mySprite.isActive = false;
    mySprite.moveSpeed = 0.0f;
    clouds.push_back(mySprite);
  }
  
  
  while(window.isOpen())
  {
    if(Keyboard::isKeyPressed(Keyboard::Escape))
    {
      window.close();
    }
    
    window.clear();
    
    window.draw(spriteBackGround);
    
    window.draw(spriteTree);
    
    window.draw(spriteBee);
    
    for (int i = 0; i < 3; ++i)
    {
      window.draw(clouds[i].sprite);
    }
    
    window.display();
  }
  
  std::cout << "MyTimber" << std::endl;
  return 0;
}