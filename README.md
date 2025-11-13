# 🐍 贪吃蛇游戏 (跨平台版)

专门为 SFML 3.0 优化的贪吃蛇游戏，支持 Mac 和 Windows。

---

## 🚀 快速开始

### 🍎 Mac 用户（你现在的系统）

**一键打包运行：**
```bash
cd ~/Downloads/Documentation/SnakeGame
chmod +x build_all.sh
./build_all.sh
open SnakeGame.app
```

### 🪟 Windows 用户

查看 → [Windows打包说明.md](Windows打包说明.md)

---

## 📦 打包方式

### 方法1：一键打包（推荐）

```bash
./build_all.sh
```

生成：
- ✅ Mac 版本：`SnakeGame.app` + `SnakeGame-Mac.zip`
- 📋 Windows 版本：提供详细说明

### 方法2：单独打包

**只打包 Mac：**
```bash
./build_mac.sh
```

**只打包 Windows（需在 Windows 上）：**
```cmd
build_windows.bat
```

---

## 🎮 游戏操作

| 按键 | 功能 |
|------|------|
| ⬆️⬇️⬅️➡️ | 控制蛇移动 |
| W A S D | 也可以用 WASD |
| 空格键 | 游戏结束后重新开始 |

---

## ✨ 游戏特性

- ✅ 流畅 60 FPS
- ✅ 吃食物会加速
- ✅ 碰撞检测完善
- ✅ 分数实时显示
- ✅ 游戏结束可重新开始
- ✅ 完全跨平台

---

## 📊 项目结构

```
SnakeGame/
├── main.cpp                    # 游戏源代码（跨平台）
├── compile.sh                  # Mac 简单编译
├── build_mac.sh               # Mac 打包脚本
├── build_windows.bat          # Windows 打包脚本
├── build_all.sh               # 一键打包所有平台
├── README.md                  # 本文件
├── 跨平台打包指南.md          # 详细指南
├── Windows打包说明.md         # Windows 专用说明
├── .vscode/
│   └── tasks.json             # Cursor 配置
└── releases/                  # 打包输出
    ├── mac/
    │   ├── SnakeGame.app
    │   └── SnakeGame-Mac.zip
    └── windows/
        ├── SnakeGame.exe
        └── *.dll
```

---

## 🔧 开发环境

### Mac
- macOS 10.15+
- Homebrew
- SFML 3.0: `brew install sfml`
- Xcode Command Line Tools

### Windows
- Windows 10/11
- MSYS2 + MinGW
- SFML 3.0
- 详见：[Windows打包说明.md](Windows打包说明.md)

---

## 📝 技术细节

- **语言**: C++20
- **图形库**: SFML 3.0
- **跨平台**: 同一份代码支持 Mac/Windows
- **代码行数**: ~270 行
- **窗口大小**: 600x450
- **网格**: 20x15

---

## 🎯 游戏规则

1. 控制绿色的蛇吃红色的食物
2. 每吃一个食物 +10 分，蛇身变长
3. 速度会越来越快
4. 撞墙或撞到自己 = Game Over
5. 按空格重新开始

---

## 🎁 分发指南

### 给 Mac 用户
发送：`releases/mac/SnakeGame-Mac.zip`

用户操作：
1. 解压
2. 双击 `SnakeGame.app`
3. 如果提示安全警告，右键 → 打开

### 给 Windows 用户
发送：`releases/windows/` 整个文件夹（压缩成 zip）

用户操作：
1. 解压所有文件
2. 双击 `SnakeGame.exe`

---

## 🐛 问题排查

### Mac

**编译失败？**
```bash
brew reinstall sfml
xcode-select --install
```

**"无法打开，因为无法验证开发者"？**
- 右键点击 → 打开 → 仍要打开

### Windows

**缺少 DLL？**
- 确保所有 .dll 文件和 .exe 在同一文件夹

**编译失败？**
- 检查是否安装 MSYS2
- 检查 PATH 环境变量

详见：[跨平台打包指南.md](跨平台打包指南.md)

---

## 📚 文档索引

- 📖 [跨平台打包指南.md](跨平台打包指南.md) - 完整的跨平台教程
- 🪟 [Windows打包说明.md](Windows打包说明.md) - Windows 专用指南
- ⚡ [如何运行.md](如何运行.md) - 快速开始

---

## 🎓 学习价值

这个项目适合学习：
- ✅ C++ 面向对象编程
- ✅ 游戏循环原理
- ✅ 碰撞检测算法
- ✅ SFML 图形库
- ✅ 跨平台开发
- ✅ 软件打包发布

---

## 📦 文件大小

| 平台 | 开发版 | 发布版 |
|------|--------|--------|
| Mac | 500 KB | 8 MB (.app) |
| Mac 压缩 | - | 3 MB (.zip) |
| Windows | 500 KB | 6 MB (含DLL) |

---

## 🚀 快速命令

```bash
# 编译测试（不打包）
./compile.sh

# 打包 Mac 版本
./build_mac.sh

# 一键打包所有
./build_all.sh

# 运行 Mac 版本
open SnakeGame.app

# 查看打包结果
open releases
```

---

## 💡 下一步

想要添加更多功能？可以尝试：
- 🎵 添加音效
- 🏆 添加排行榜
- 🎨 更多皮肤主题
- 🌟 特殊道具
- 👥 多人模式

---

**祝你玩得开心！🎮**

能得多少分？试试看！😎
