#pragma region include
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <vector>
#include <array>

#include "../headers/Settings.h"
#include "../headers/TileMap.h"
#include "../headers/Spell.h"
#include "../headers/Player.h"
#include "../headers/Settings.h" 
#include "../headers/Utils.h"
#include "../headers/Collider.h"
#include "../headers/Obstacle.h"
#include "../headers/DevConsole.h"
#include "../headers/Npc.h"
#include "../headers/RenderLayer.h"
#include "../headers/UiInterface.h"
#include "../headers/Animation.h"
#include "../headers/Explosion.h"
#include "../headers/Pathfinder.h"
#pragma endregion

int main() {
    Settings settings = Settings();
    settings.keyMap.left  = sf::Keyboard::Key::A;
    settings.keyMap.right = sf::Keyboard::D;
    settings.keyMap.up    = sf::Keyboard::Key::W;
    settings.keyMap.down  = sf::Keyboard::Key::S;

    settings.keyMap.openConsole = sf::Keyboard::Key::F1;

    settings.keyMap.spell1 = sf::Keyboard::Key::Num1;
    settings.keyMap.spell2 = sf::Keyboard::Key::Num2;
    settings.keyMap.spell3 = sf::Keyboard::Key::Num3;
    settings.keyMap.spell4 = sf::Keyboard::Key::Num4;
    settings.keyMap.spell5 = sf::Keyboard::Key::Num5;
    settings.keyMap.spell6 = sf::Keyboard::Key::Num6;
    settings.keyMap.spell7 = sf::Keyboard::Key::Num7;
    settings.keyMap.spell8 = sf::Keyboard::Key::Num8;
    settings.keyMap.spell9 = sf::Keyboard::Key::Num9;

    settings.keyMap.useSpell = sf::Keyboard::Key::Space;
    settings.showNavData = true;


    const sf::Color bgColor(51, 51, 51);
    sf::Font font;
    sf::Vector2i mousePos;
    sf::Vector2i mousePosRelative;
    font.loadFromFile("font.ttf");

    // Initialization of important stuff

    sf::RenderWindow window(sf::VideoMode(settings.WINDOW_WIDTH, settings.WINDOW_HEIGHT), "SFML Dungeon Crawler", sf::Style::Close | sf::Style::Titlebar);
    window.setFramerateLimit(1000);

    sf::View viewport(sf::Vector2f((float) settings.WINDOW_WIDTH / 2.0f, (float) settings.WINDOW_HEIGHT / 2.0f), sf::Vector2f(settings.WINDOW_WIDTH, settings.WINDOW_HEIGHT));
    window.setView(viewport);
    window.setKeyRepeatEnabled(false);


    // Vector with all obstacles - kind of like a sprite group
    std::vector<Obstacle> obstacles;
    std::vector<CellDoor> cellDoors;

    std::vector<Explosion> explosions;

    Spell::explosions = &explosions;
    Projectile::explosions = &explosions;

    sf::Clock clock;
    
    // This stores and draws the background image of the map
    TileMap map = TileMap("./resources/tmap3", obstacles, cellDoors);
    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(map.mapTexture);
    backgroundSprite.setPosition(sf::Vector2f(0.0f, 0.0f));
    sf::Vector2f lowerBound(settings.WINDOW_WIDTH / 2.0f, settings.WINDOW_HEIGHT / 2.0f);
    sf::Vector2f upperBound(map.mapTexture.getSize().x - (settings.WINDOW_WIDTH / 2.0f),
                            map.mapTexture.getSize().y - (settings.WINDOW_HEIGHT / 2.0f));
    sf::Sprite foreGround;
    foreGround.setTexture(map.foreGroundTexture);
    foreGround.setPosition(sf::Vector2f(0.0f, 0.0f));
    
    // Player setup
    bool isRunning = true;
    Player player = Player(sf::RectangleShape(sf::Vector2f(28.f, 28.f)), &settings);
    player.setPos(sf::Vector2f(settings.WINDOW_WIDTH / 2, settings.WINDOW_HEIGHT / 2));
    sf::Event event;
    Collider playerCol = player.getCollider();
    //Spell initialization
    Fireball fireball = Fireball(player);
    MagicMissile magicMissile = MagicMissile(player);
    Explode explode = Explode(player);
    SprintSpell sprint = SprintSpell(player);
    FlashHeal flashHeal = FlashHeal(player);
    Firebolt firebolt = Firebolt(player);
    //Adding spells to player

    player.addSpell(&firebolt);
    player.addSpell(&fireball);
    player.addSpell(&explode);
    player.addSpell(&magicMissile);
    player.addSpell(&sprint);
    player.addSpell(&flashHeal);

    // Enemies
    EnemyFactory enemyFactory(player);
    enemyFactory.spawnEnemy("slime", sf::Vector2f(300.0f, 300.0f));

    // Dev Console
    UiGrid interfaceGrid;
    DevConsole console = DevConsole(settings, enemyFactory, &interfaceGrid, &player);

    // Spell
    Spell *currspell;

    // Test render layer
    RenderLayer layer1;
    layer1.add(&(player.uiCastBar));
    
    // Spellbar setup
    //SpellBarIcon icon1 = SpellBarIcon(1);
    //SpellBarIcon icon2 = SpellBarIcon(2);
    //spellIcons.push_back(icon1);
    //spellIcons.push_back(icon2);
    //SpellBar mainSpellBar = SpellBar();
    //mainSpellBar.setSize(sf::Vector2f(80, 30));
    //mainSpellBar.setSpellIcons(spellIcons);
    //mainSpellBar.changeSelection(1);
    std::vector<SpellBarIcon> spellIcons;
    //for (int i = 0; i < 2; i++) {
        //spellIcons.push_back(SpellBarIcon(i + 1));
    //}
    SpellBar mainSpellBar = SpellBar(9);
    mainSpellBar.setPosition(sf::Vector2f(settings.WINDOW_WIDTH / 2 - (mainSpellBar.getSize().x / 2), settings.WINDOW_HEIGHT - 40));
    //mainSpellBar.setPosition(sf::Vector2f(settings.WINDOW_WIDTH / 2 - 1400, settings.WINDOW_HEIGHT - 100));
    layer1.add(&mainSpellBar);
    player.spellBar = &mainSpellBar;

    PlayerHpBar playerHpBar;
    playerHpBar.setMaxStat(player.getMaxHp());

    // Player interface layer 1
    RenderLayer playerInterfaces;
    playerInterfaces.add(&(player.uiCastBar));
    player.uiCastBar.setPosition(sf::Vector2f(settings.WINDOW_WIDTH / 2, settings.WINDOW_HEIGHT - 72));
    PlayerLevelIcon levelIcon;
    levelIcon.update(player.getLevel());
    playerInterfaces.add(&levelIcon);
    player.setLevelIcon(&levelIcon);
    levelIcon.setPosition(sf::Vector2f(10, 18));
    playerInterfaces.add(&playerHpBar);
    playerHpBar.setPosition(sf::Vector2f(110, 31));

    PlayerStaminaBar staminaBar;
    staminaBar.setPosition(sf::Vector2f(110, 75));
    staminaBar.setMaxStat(100);
    staminaBar.update(100);
    playerInterfaces.add(&staminaBar);
    
    PlayerManaBar playerManaBar;
    playerManaBar.setPosition(sf::Vector2f(110, 53));
    playerManaBar.setMaxStat(100);
    playerInterfaces.add(&playerManaBar);
    playerInterfaces.add(&mainSpellBar);

    player.setHpBar(&playerHpBar);
    player.setManaBar(&playerManaBar);
    
    // Jakob wat is dis?
    std::vector<std::string> statusText;

    RenderLayer debugLayer;
    debugLayer.add(&interfaceGrid);

    PauseMenu pauseMenu(&settings);

    Pathfinder testBrain;
    testBrain.generateGraph(map.getNavData(), 2);
    testBrain.generateGraphTexture();
    testBrain.setStartNode(40, 40);
    testBrain.setEndNode(126, 104);
    std::cout << "starting" << std::endl;
    testBrain.findPath();
    std::cout << "finished" << std::endl;
    testBrain.generatePathTexture();


    // Main Game Loop
    clock.restart();
    float dt = 0;
    // Frame rate display
    bool showFPS = false;
    std::array<float, 10> deltaTimes;
    int frameCount = 0;
    sf::IntRect viewPortRect = map.getViewportRect(viewport.getCenter());
    while (isRunning) {
        sf::Time l = clock.restart();
        dt = l.asMilliseconds();
        //std::cout << l.asMicroseconds() << std::endl;
        if (showFPS) {
            deltaTimes[frameCount] = dt;
            frameCount++;
            if (frameCount > deltaTimes.size()) {
                frameCount = 0;
            }
            float sum = 0;
            for (int i = 0; i < deltaTimes.size(); i++) {
                sum += deltaTimes[i];
            }
            if (frameCount % 10 == 0) {
                std::cout << 1000.0f / (sum / 10.0f) << std::endl;
                //for (int i = 0; i < deltaTimes.size(); i++) {
                    //std::cout << deltaTimes[i] << " ";
                //}
                //std::cout << std::endl;
            }
        }
        // Event Loop
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                isRunning = false;
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    // Paragraph
                    case 54:
                    // F1 as backup for devconsole
                    case 85:
                        isRunning = console.open(window, player);
                        clock.restart();
                        break;
                    // Only for testing
                    case sf::Keyboard::Key::B:
                        enemyFactory.hurtEnemy(0, 1);
                        break;
                    case sf::Keyboard::Key::Escape:
                        isRunning = !pauseMenu.open(window, clock, viewport);
                    default:
                        break;
                }
            }
        }   

        mousePos = sf::Mouse::getPosition(window);

        mousePos.y -= std::min(0, (int)(settings.WINDOW_HEIGHT  / 2 - player.getPos().y));
        mousePos.x -= std::min(0, (int)(settings.WINDOW_WIDTH / 2 - player.getPos().x));
        mousePos.y += std::min(0, (int)((map.getSize().y * settings.TILESIZE - settings.WINDOW_HEIGHT / 2) - player.getPos().y));
        mousePos.x += std::min(0, (int)((map.getSize().x * settings.TILESIZE - settings.WINDOW_WIDTH / 2) - player.getPos().x));
        player.setMousePos(sf::Vector2f(mousePos.x, mousePos.y));

        player.setMouseAngle(getAngle(player.getPos(),
                             sf::Vector2f(mousePos.x,
                             mousePos.y)));

        for (int i = 0; i < player.getProjectiles().size(); i++) {
            player.getProjectiles()[i].update(dt, sf::Vector2f(mousePos.x, mousePos.y));
        }
        player.update(dt);

        for (int i = 0; i < player.getSpells().size(); i++) {
            (*player.getSpells()[i]).update(dt);
            
        }
      
        viewport.setCenter(clampVec(player.getPos(), lowerBound, upperBound));
        window.setView(viewport);
        map.update(dt);
        viewPortRect = map.getViewportRect(viewport.getCenter());
        backgroundSprite.setTextureRect(viewPortRect);
        backgroundSprite.setPosition(sf::Vector2f(viewPortRect.left, viewPortRect.top));
        sf::IntRect kek = backgroundSprite.getTextureRect();
        sf::Vector2f direction;

        // Collision detection
        if (settings.playerColliding) {
            for (Obstacle &obstacle : obstacles) {
                if (obstacle.getCollider().checkCollision(&playerCol, direction, 1.0f)) {
                    player.onCollision(direction);
                }
            }
        }
        
        enemyFactory.update(dt);
        enemyFactory.wallCollide(obstacles);
        enemyFactory.spellCollide(player.getProjectiles());
        enemyFactory.playerCollide(player);
        enemyFactory.explosionCollide(explosions);
        // Moving the ui layer to ensure that it follows the screen
        playerInterfaces.setPosition(viewport.getCenter() - sf::Vector2f((float) settings.WINDOW_WIDTH / 2, (float) settings.WINDOW_HEIGHT / 2));
        debugLayer.setPosition(viewport.getCenter() - sf::Vector2f((float) settings.WINDOW_WIDTH / 2, (float) settings.WINDOW_HEIGHT / 2));
        // Collision with cell linkers
        for (CellDoor &door : cellDoors) {
            if (door.getCollider().isColliding(&playerCol)) {
                // Loading new map
                std::string newPath = door.getLinkedMap();
                sf::Vector2f linkedPos = door.getLinkedPos();
                map = TileMap(newPath, obstacles, cellDoors);
                // Updating texture and texutre clamping
                backgroundSprite.setTexture(map.mapTexture);
                backgroundSprite.setPosition(sf::Vector2f(0.0f, 0.0f));
                sf::Vector2f lowerBound(settings.WINDOW_WIDTH / 2.0f, settings.WINDOW_HEIGHT / 2.0f);
                sf::Vector2f upperBound(map.mapTexture.getSize().x - (settings.WINDOW_WIDTH / 2.0f),
                                        map.mapTexture.getSize().y - (settings.WINDOW_HEIGHT / 2.0f));
                sf::Sprite foreGround;
                foreGround.setTexture(map.foreGroundTexture);
                foreGround.setPosition(sf::Vector2f(0.0f, 0.0f));
                player.setPos(linkedPos);
                player.setVel(sf::Vector2f(0, 0));
                player.clearProjectiles();
                // In future the enemyFactory should also be reset and spawn new enemies
            }
        }
        
        for (int i = 0; i < explosions.size(); i++) {
            explosions[i].update(dt);
            if (explosions[i].kill) {
                explosions.erase(explosions.begin() + i);
            }
        }


        // Drawing
        window.clear(bgColor);

        // Landscape background
        window.draw(backgroundSprite);

        for (int i = 0; i < player.getProjectiles().size(); i++) {
            player.getProjectiles()[i].draw(window);
        }

        for (int i = 0; i < explosions.size(); i++) {
            explosions[i].draw(window);
        }

        player.draw(window);
        window.draw(foreGround);
        enemyFactory.draw(window);
        map.drawAnimatedTerrain(window);
        if (settings.showNavData) {
            std::vector<std::vector<bool>> navData = map.getNavData();
            sf::RectangleShape debugNavRect;
            debugNavRect.setSize(sf::Vector2f(32.0, 32.0));
            debugNavRect.setFillColor(sf::Color(255, 0, 0, 100));
            for (int y = 0; y < navData.size(); y++) {
                for (int x = 0; x < navData[0].size(); x++) {
                    if (!navData[y][x]) {
                        debugNavRect.setPosition(sf::Vector2f(x * 32, y * 32));
                        window.draw(debugNavRect);
                    }
                }
            }
        }
        window.draw(playerInterfaces);
        window.draw(debugLayer);
        testBrain.draw(window);
        window.display();
    }

    return 0;
}

