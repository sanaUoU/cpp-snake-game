#!/bin/bash

# 🎮 一键运行脚本

clear
echo "══════════════════════════════════════════════════════════"
echo "          🐍 贪吃蛇游戏 - 快速启动 🎮"
echo "══════════════════════════════════════════════════════════"
echo ""

# 检查是否已经编译
if [ ! -f "SnakeGame" ]; then
    echo "📦 首次运行，正在编译游戏..."
    g++ -std=c++20 main.cpp -o SnakeGame \
        -I/usr/local/include \
        -L/usr/local/lib \
        -lsfml-graphics -lsfml-window -lsfml-system
    
    if [ $? -ne 0 ]; then
        echo ""
        echo "❌ 编译失败！"
        echo ""
        echo "可能的原因："
        echo "  1. 未安装 SFML: brew install sfml"
        echo "  2. 未安装 Xcode Command Line Tools"
        echo ""
        exit 1
    fi
    
    echo "✅ 编译成功！"
fi

echo ""
echo "🎮 启动游戏..."
echo ""

# 运行游戏
./SnakeGame

echo ""
echo "👋 游戏已关闭"
echo ""
