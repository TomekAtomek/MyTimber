#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

typedef struct mysprite
{
  Sprite sprite;
  bool isActive;
  float moveSpeed;
  
} MySprite;

void updateBranches( int seed );

const int NUM_BRANCHES = 6;

Sprite branches[NUM_BRANCHES];

enum class side {LEFT, RIGHT, NONE};

side branchPositions[NUM_BRANCHES];

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
  
  
  bool paused = true;
  
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
  
  Texture textureBranch;
  
  textureBranch.loadFromFile("graphics/branch.png");
  
  for(int i = 0; i < NUM_BRANCHES; ++i)
  {
    branches[i].setTexture(textureBranch);
    branches[i].setPosition(-2000,-2000);
    branches[i].setOrigin(220,20);
  }
  
  
  Texture texturePlayer;
  texturePlayer.loadFromFile("graphics/player.png");
  Sprite spritePlayer;
  spritePlayer.setTexture(texturePlayer);
  spritePlayer.setPosition(580,720);
  
  side playerSide = side::LEFT;
  
  Texture textureRIP;
  textureRIP.loadFromFile("graphics/rip.png");
  Sprite spriteRIP;
  spriteRIP.setTexture(textureRIP);
  spriteRIP.setPosition(600,860);
  
  Texture textureAxe;
  textureAxe.loadFromFile("graphics/axe.png");
  Sprite spriteAxe;
  spriteAxe.setTexture(textureAxe);
  spriteAxe.setPosition(700,830);
  
  const float AXE_POSITION_LEFT = 700;
  const float AXE_POSITION_RIGHT = 1075;
  
  Texture textureLog;
  textureLog.loadFromFile("graphics/log.png");
  Sprite spriteLog;
  spriteLog.setTexture(textureLog);
  spriteLog.setPosition(810,720);
  
  bool logActive = false;
  float logSpeedX = 1000;
  float logSpeedY = -1500;
  
  bool acceptInput = false;
  
  
  SoundBuffer chopBuffer;
  chopBuffer.loadFromFile("sound/chop.wav");
  Sound chop;
  chop.setBuffer(chopBuffer);
  
  SoundBuffer deathBuffer;
  deathBuffer.loadFromFile("sound/death.wav");
  Sound death;
  death.setBuffer(deathBuffer);
  
  SoundBuffer ootBuffer;
  ootBuffer.loadFromFile("sound/out_of_time.wav");
  Sound outOfTime;
  outOfTime.setBuffer(ootBuffer);
  
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
	
	outOfTime.play();
	
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
          
      for(int i = 0; i < NUM_BRANCHES; ++i)
      {
	float height = i * 150;
	
	if (branchPositions[i] == side::LEFT)
	{
	  branches[i].setPosition(610, height);
	  branches[i].setRotation(180);
	}
	else if (branchPositions[i] == side::RIGHT)
	{
	  branches[i].setPosition(1330, height);
	  branches[i].setRotation(0);
	}
	else
	{
	  //hide the branch
	  branches[i].setPosition(3000, height);
	}
      }
      
      if(logActive)
      {
	spriteLog.setPosition(spriteLog.getPosition().x + (logSpeedX * deltaTime.asSeconds()), spriteLog.getPosition().y + (logSpeedY * deltaTime.asSeconds()));
	if(spriteLog.getPosition().x < -100 || spriteLog.getPosition().x > 2000)
	{
	  logActive = false;
	  spriteLog.setPosition(810, 720);
	}
      }
      
      if(branchPositions[5] == playerSide)
      {
	paused = true;
	acceptInput =false;
	
	spriteRIP.setPosition(525, 760);
	
	spritePlayer.setPosition(2000, 660);
	
	messageText.setString("SQUISHED!!");
	
	FloatRect textRect = messageText.getLocalBounds();
	
	messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	
	messageText.setPosition(1920 / 2.0f , 1080 / 2.0f);
	
	death.play();
	
      }
      
      
    }// !paused
    
    Event event;
    
    while(window.pollEvent(event))
    {
      if(event.type == Event::KeyReleased && !paused)
      {
	acceptInput = true;
	
	spriteAxe.setPosition(2000, spriteAxe.getPosition().y);
      }
    }
    
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
      
      for (int i = 1; i < NUM_BRANCHES; ++i)
      {
	branchPositions[i] = side::NONE;
      }
      
      spriteRIP.setPosition(675, 2000);
      
      spritePlayer.setPosition(580, 720);
      
      acceptInput= true;
      
    }
    
    if(acceptInput)
    {
      if(Keyboard::isKeyPressed(Keyboard::Right))
      {
	playerSide = side::RIGHT;
	
	++score;
	
	timeRemaining += (2 / score) + .15;
	
	spriteAxe.setPosition(AXE_POSITION_RIGHT, spriteAxe.getPosition().y);
	
	spritePlayer.setPosition(1200, 720);
	
	updateBranches(score);
	
	spriteLog.setPosition(810, 720);
	
	logSpeedX = -5000;
	logActive = true;
	
	acceptInput = false;
	
	chop.play();
      }
      
      if(Keyboard::isKeyPressed(Keyboard::Left))
      {
	playerSide = side::LEFT;
	
	++score;
	
	timeRemaining += (2 / score) + .15;
	
	spriteAxe.setPosition(AXE_POSITION_LEFT, spriteAxe.getPosition().y);
	
	spritePlayer.setPosition(580, 720);
	
	updateBranches(score);
	
	spriteLog.setPosition(810, 720);
	logSpeedX = 5000;
	logActive = true;
	
	acceptInput = false;
	
	chop.play();
	
      }
    }
    
    window.clear();
    
    window.draw(spriteBackGround);
    
    window.draw(spriteTree);
    
    
    for (int i = 0; i < NUM_BRANCHES; ++i)
    {
      window.draw(branches[i]);
    }
    
    window.draw(spritePlayer);
    
    window.draw(spriteAxe);
    
    window.draw(spriteLog);
    
    window.draw(spriteRIP);
    
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

void updateBranches( int seed )
{
  //move branches up
  for (int i = NUM_BRANCHES - 1; i > 0; --i)
  {
    branchPositions[i] = branchPositions[i-1];
  }
  
  srand((int)time(0) + seed);
  int r = (rand() % 5);
  
  switch(r)
  {
    case 0:
      branchPositions[0] = side::LEFT;
      break;
    case 1:
      branchPositions[0] = side::RIGHT;
      break;
    default:
      branchPositions[0] = side::NONE;
      break;
  }
  
}