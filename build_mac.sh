#!/bin/bash

echo "🍎 开始打包 Mac 版本..."
echo ""

# 检查 SFML
if ! brew list sfml &> /dev/null; then
    echo "❌ 未安装 SFML，运行: brew install sfml"
    exit 1
fi

# 编译游戏
echo "📦 编译游戏..."
g++ -std=c++20 main.cpp -o SnakeGame \
    -I/usr/local/include \
    -L/usr/local/lib \
    -lsfml-graphics -lsfml-window -lsfml-system

if [ $? -ne 0 ]; then
    echo "❌ 编译失败"
    exit 1
fi

# 清理旧的 .app
rm -rf SnakeGame.app

# 创建 .app 结构
echo "🏗️  创建应用包结构..."
mkdir -p SnakeGame.app/Contents/MacOS
mkdir -p SnakeGame.app/Contents/Resources
mkdir -p SnakeGame.app/Contents/Frameworks

# 移动可执行文件
mv SnakeGame SnakeGame.app/Contents/MacOS/

# 检测 SFML 路径 (支持 Intel 和 Apple Silicon Mac)
if [ -d "/opt/homebrew/lib" ]; then
    SFML_PATH="/opt/homebrew/lib"
elif [ -d "/usr/local/lib" ]; then
    SFML_PATH="/usr/local/lib"
else
    echo "❌ 找不到 SFML 库"
    exit 1
fi

echo "📚 复制 SFML 库 (从 $SFML_PATH)..."
cp $SFML_PATH/libsfml-graphics.3.dylib SnakeGame.app/Contents/Frameworks/
cp $SFML_PATH/libsfml-window.3.dylib SnakeGame.app/Contents/Frameworks/
cp $SFML_PATH/libsfml-system.3.dylib SnakeGame.app/Contents/Frameworks/

# 创建 Info.plist
echo "📝 创建配置文件..."
cat > SnakeGame.app/Contents/Info.plist << 'EOF'
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
    <key>CFBundleExecutable</key>
    <string>SnakeGame</string>
    <key>CFBundleName</key>
    <string>Snake Game</string>
    <key>CFBundleIdentifier</key>
    <string>com.yourname.snakegame</string>
    <key>CFBundleVersion</key>
    <string>1.0</string>
    <key>CFBundlePackageType</key>
    <string>APPL</string>
    <key>CFBundleShortVersionString</key>
    <string>1.0</string>
</dict>
</plist>
EOF

# 修复库路径
echo "🔧 修复库依赖..."
install_name_tool -change @rpath/libsfml-graphics.3.dylib @executable_path/../Frameworks/libsfml-graphics.3.dylib SnakeGame.app/Contents/MacOS/SnakeGame
install_name_tool -change @rpath/libsfml-window.3.dylib @executable_path/../Frameworks/libsfml-window.3.dylib SnakeGame.app/Contents/MacOS/SnakeGame
install_name_tool -change @rpath/libsfml-system.3.dylib @executable_path/../Frameworks/libsfml-system.3.dylib SnakeGame.app/Contents/MacOS/SnakeGame

# 创建发布文件夹
mkdir -p releases/mac

# 压缩 .app
echo "📦 创建分发包..."
zip -r releases/mac/SnakeGame-Mac.zip SnakeGame.app

# 计算大小
SIZE=$(du -sh SnakeGame.app | cut -f1)

echo ""
echo "✅ Mac 版本打包完成！"
echo ""
echo "📁 输出："
echo "   - SnakeGame.app (双击运行)"
echo "   - releases/mac/SnakeGame-Mac.zip (分发用)"
echo ""
echo "📊 大小: $SIZE"
echo ""
echo "🎮 测试: open SnakeGame.app"
echo ""
