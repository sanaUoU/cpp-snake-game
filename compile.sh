#!/bin/bash

echo "🐍 编译贪吃蛇游戏 (SFML 3.0.2)..."

g++ -std=c++20 main.cpp -o SnakeGame \
    -I/usr/local/include \
    -L/usr/local/lib \
    -lsfml-graphics -lsfml-window -lsfml-system

if [ $? -eq 0 ]; then
    echo "✅ 编译成功！"
    echo "🎮 运行游戏: ./SnakeGame"
    echo ""
    echo "游戏操作："
    echo "  ⬆️  方向键/WASD - 控制方向"
    echo "  🔄 空格键 - 游戏结束后重新开始"
else
    echo "❌ 编译失败！"
    exit 1
fi
