#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>

// 游戏常量
const int CELL_SIZE = 30;
const int GRID_WIDTH = 20;
const int GRID_HEIGHT = 15;
const int WINDOW_WIDTH = CELL_SIZE * GRID_WIDTH;
const int WINDOW_HEIGHT = CELL_SIZE * GRID_HEIGHT;

// 方向枚举
enum Direction { UP, DOWN, LEFT, RIGHT };

// 位置结构体
struct Position {
    int x, y;
    
    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }
};

// 贪吃蛇类
class Snake {
public:
    std::vector<Position> body;
    Direction direction;
    bool growing;
    
    Snake() {
        body.push_back({GRID_WIDTH / 2, GRID_HEIGHT / 2});
        body.push_back({GRID_WIDTH / 2 - 1, GRID_HEIGHT / 2});
        body.push_back({GRID_WIDTH / 2 - 2, GRID_HEIGHT / 2});
        direction = RIGHT;
        growing = false;
    }
    
    void move() {
        Position newHead = body[0];
        
        switch (direction) {
            case UP:    newHead.y--; break;
            case DOWN:  newHead.y++; break;
            case LEFT:  newHead.x--; break;
            case RIGHT: newHead.x++; break;
        }
        
        body.insert(body.begin(), newHead);
        
        if (!growing) {
            body.pop_back();
        } else {
            growing = false;
        }
    }
    
    void grow() {
        growing = true;
    }
    
    bool checkSelfCollision() {
        Position head = body[0];
        for (size_t i = 1; i < body.size(); i++) {
            if (body[i] == head) {
                return true;
            }
        }
        return false;
    }
    
    bool checkWallCollision() {
        Position head = body[0];
        return head.x < 0 || head.x >= GRID_WIDTH || 
               head.y < 0 || head.y >= GRID_HEIGHT;
    }
};

// 食物类
class Food {
public:
    Position position;
    
    void spawn(const Snake& snake) {
        bool validPosition = false;
        
        while (!validPosition) {
            position.x = rand() % GRID_WIDTH;
            position.y = rand() % GRID_HEIGHT;
            
            validPosition = true;
            for (size_t i = 0; i < snake.body.size(); i++) {
                if (snake.body[i] == position) {
                    validPosition = false;
                    break;
                }
            }
        }
    }
};

// 游戏类
class Game {
private:
    sf::RenderWindow window;
    Snake snake;
    Food food;
    int score;
    float moveTimer;
    float moveDelay;
    bool gameOver;
    
public:
    Game() : window(sf::VideoMode(sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT)), "Snake Game") {
        window.setFramerateLimit(60);
        srand(static_cast<unsigned int>(time(0)));
        
        score = 0;
        moveTimer = 0;
        moveDelay = 0.15f;
        gameOver = false;
        
        food.spawn(snake);
    }
    
    void run() {
        sf::Clock clock;
        
        while (window.isOpen()) {
            float deltaTime = clock.restart().asSeconds();
            
            handleInput();
            
            if (!gameOver) {
                update(deltaTime);
            }
            
            render();
        }
    }
    
private:
    void handleInput() {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (!gameOver) {
                    if (keyPressed->code == sf::Keyboard::Key::Up || keyPressed->code == sf::Keyboard::Key::W) {
                        if (snake.direction != DOWN) snake.direction = UP;
                    }
                    else if (keyPressed->code == sf::Keyboard::Key::Down || keyPressed->code == sf::Keyboard::Key::S) {
                        if (snake.direction != UP) snake.direction = DOWN;
                    }
                    else if (keyPressed->code == sf::Keyboard::Key::Left || keyPressed->code == sf::Keyboard::Key::A) {
                        if (snake.direction != RIGHT) snake.direction = LEFT;
                    }
                    else if (keyPressed->code == sf::Keyboard::Key::Right || keyPressed->code == sf::Keyboard::Key::D) {
                        if (snake.direction != LEFT) snake.direction = RIGHT;
                    }
                } else {
                    if (keyPressed->code == sf::Keyboard::Key::Space) {
                        reset();
                    }
                }
            }
        }
    }
    
    void update(float deltaTime) {
        moveTimer += deltaTime;
        
        if (moveTimer >= moveDelay) {
            moveTimer = 0;
            
            snake.move();
            
            if (snake.checkWallCollision() || snake.checkSelfCollision()) {
                gameOver = true;
                return;
            }
            
            if (snake.body[0] == food.position) {
                snake.grow();
                food.spawn(snake);
                score += 10;
                
                if (moveDelay > 0.05f) {
                    moveDelay -= 0.005f;
                }
            }
        }
    }
    
    void render() {
        window.clear(sf::Color(20, 20, 20));
        
        // 绘制网格
        for (int i = 0; i <= GRID_WIDTH; i++) {
            sf::RectangleShape line(sf::Vector2f(1.f, static_cast<float>(WINDOW_HEIGHT)));
            line.setPosition(sf::Vector2f(static_cast<float>(i * CELL_SIZE), 0.f));
            line.setFillColor(sf::Color(40, 40, 40));
            window.draw(line);
        }
        for (int i = 0; i <= GRID_HEIGHT; i++) {
            sf::RectangleShape line(sf::Vector2f(static_cast<float>(WINDOW_WIDTH), 1.f));
            line.setPosition(sf::Vector2f(0.f, static_cast<float>(i * CELL_SIZE)));
            line.setFillColor(sf::Color(40, 40, 40));
            window.draw(line);
        }
        
        // 绘制食物
        sf::RectangleShape foodShape(sf::Vector2f(CELL_SIZE - 2.f, CELL_SIZE - 2.f));
        foodShape.setPosition(sf::Vector2f(
            static_cast<float>(food.position.x * CELL_SIZE + 1), 
            static_cast<float>(food.position.y * CELL_SIZE + 1)
        ));
        foodShape.setFillColor(sf::Color::Red);
        window.draw(foodShape);
        
        // 绘制蛇
        for (size_t i = 0; i < snake.body.size(); i++) {
            sf::RectangleShape segment(sf::Vector2f(CELL_SIZE - 2.f, CELL_SIZE - 2.f));
            segment.setPosition(sf::Vector2f(
                static_cast<float>(snake.body[i].x * CELL_SIZE + 1), 
                static_cast<float>(snake.body[i].y * CELL_SIZE + 1)
            ));
            
            if (i == 0) {
                segment.setFillColor(sf::Color(0, 255, 0));
            } else {
                segment.setFillColor(sf::Color(0, 200, 0));
            }
            
            window.draw(segment);
        }
        
        // 绘制分数
        sf::RectangleShape scoreBg(sf::Vector2f(150.f, 30.f));
        scoreBg.setPosition(sf::Vector2f(10.f, 10.f));
        scoreBg.setFillColor(sf::Color(50, 50, 50, 180));
        window.draw(scoreBg);
        
        for (int i = 0; i < score / 10 && i < 10; i++) {
            sf::CircleShape dot(5.f);
            dot.setPosition(sf::Vector2f(20.f + i * 12.f, 20.f));
            dot.setFillColor(sf::Color::Yellow);
            window.draw(dot);
        }
        
        // 游戏结束
        if (gameOver) {
            sf::RectangleShape overlay(sf::Vector2f(
                static_cast<float>(WINDOW_WIDTH), 
                static_cast<float>(WINDOW_HEIGHT)
            ));
            overlay.setFillColor(sf::Color(0, 0, 0, 150));
            window.draw(overlay);
            
            sf::RectangleShape textBg(sf::Vector2f(300.f, 100.f));
            textBg.setPosition(sf::Vector2f(
                WINDOW_WIDTH / 2.f - 150.f, 
                WINDOW_HEIGHT / 2.f - 50.f
            ));
            textBg.setFillColor(sf::Color(200, 50, 50));
            window.draw(textBg);
            
            sf::RectangleShape restartBg(sf::Vector2f(280.f, 40.f));
            restartBg.setPosition(sf::Vector2f(
                WINDOW_WIDTH / 2.f - 140.f, 
                WINDOW_HEIGHT / 2.f + 80.f
            ));
            restartBg.setFillColor(sf::Color(50, 50, 200));
            window.draw(restartBg);
        }
        
        window.display();
    }
    
    void reset() {
        snake = Snake();
        food.spawn(snake);
        score = 0;
        moveTimer = 0;
        moveDelay = 0.15f;
        gameOver = false;
    }
};

int main() {
    Game game;
    game.run();
    return 0;
}
