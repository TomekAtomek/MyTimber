#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
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
  
  Clock clock;
  
  RectangleShape timeBar;
  
  float timeBarStartWidth = 400;
  float timeBarHeight = 80;
  
  timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
  
  timeBar.setFillColor(Color::Red);
  
  timeBar.setPosition(1920 / 2 - timeBarStartWidth / 2, 80);
  
  Time gameTimeTotal;
  
  float timeRemaining = 6.0f;
  
  float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;
  
  
  bool paused = false;
  
  int score = 0;
  
  sf::Text messageText;
  sf::Text scoreText;
  
  Font font;
  
  font.loadFromFile("fonts/KOMIKAP_.ttf");
  
  messageText.setFont(font);
  scoreText.setFont(font);
  
  messageText.setString("Press Enter to Start!");
  scoreText.setString("Score = 0");
  
  messageText.setCharacterSize(75);
  scoreText.setCharacterSize(100);
  
  messageText.setFillColor(Color::White);
  scoreText.setFillColor(Color::White);
  
  FloatRect textRect = messageText.getLocalBounds();
  
  messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
  
  scoreText.setPosition(20,20);
  messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
  
  while(window.isOpen())
  {
    
    
    if(!paused)
    {
      Time deltaTime = clock.restart();
      
      timeRemaining -= deltaTime.asSeconds();
      
      timeBar.setSize(Vector2f( timeBarWidthPerSecond * timeRemaining, timeBarHeight));
      
      
      if(timeRemaining <= 0.0f)
      {
	paused = true;
	
	messageText.setString("Out of Time!");
	
	FloatRect textRect = messageText.getLocalBounds();
  
	messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	
	messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
      }
      
      for(int i = 0; i < 3; ++i)
      {
	if( !(clouds[i].isActive) )
	{
	  clouds[i].isActive = true;
	  
	  //how fast the cloud is
	  srand((int)time(0) * 10 + (10 * i));
	  clouds[i].moveSpeed = (rand() % 200);
	  
	  if(clouds[i].moveSpeed == 0)
	  {
	    std::cout << "Cloud " << i << " speed is zero" << std::endl;
	  }
	  
	  //how high the cloud is
	  srand((int)time(0) * 10 * (i+1));
	  int subs = (i == 0) ? 0 : 150;
	  float height = (rand() % (150 + i * 150)) - subs;
	  clouds[i].sprite.setPosition(-200, height);
	  
	}
	else
	{
	  //Sprite tmp = clouds[i].sprite;
	  clouds[i].sprite.setPosition( clouds[i].sprite.getPosition().x + (clouds[i].moveSpeed * deltaTime.asSeconds()), clouds[i].sprite.getPosition().y );
	  if(clouds[i].sprite.getPosition().x > 1920)
	  {
	    clouds[i].isActive = false;
	  }
	  
	}
      }
      
      if(!beeActive)
      {
	beeActive = true;
	
	// how fast the bee is
	srand((int)time(0));
	beeSpeed = (rand() % 200) + 200;
	
	// how high the bee is
	srand((int)time(0) * 10);
	float height = (rand() % 500) + 500;
	
	spriteBee.setPosition(2000, height);
	
	
      }
      else //move the bee
      {
	spriteBee.setPosition(spriteBee.getPosition().x - 
	(beeSpeed * deltaTime.asSeconds()),spriteBee.getPosition().y);
	
	if(spriteBee.getPosition().x < -100)
	{
	  beeActive = false;
	}
	
      }
      std::stringstream ss;
      
      ss << "Score = " << score;
      
      scoreText.setString(ss.str());
      
    }// !paused
    
    if(Keyboard::isKeyPressed(Keyboard::Escape))
    {
      window.close();
    }
    
    if(Keyboard::isKeyPressed(Keyboard::P))
    {
      paused = true;
    }
    
    if(Keyboard::isKeyPressed(Keyboard::Return))
    {
      paused = false;
      score = 0;
      timeRemaining = 5;
    }
    
    window.clear();
    
    window.draw(spriteBackGround);
    
    window.draw(spriteTree);
    
    window.draw(spriteBee);
    
    for (int i = 0; i < 3; ++i)
    {
      window.draw(clouds[i].sprite);
    }
    
    if(paused)
    {
      window.draw(messageText);
    }
    
    window.draw(scoreText);
    
    window.draw(timeBar);
    
    window.display();
  }
  
  std::cout << "MyTimber" << std::endl;
  return 0;
}