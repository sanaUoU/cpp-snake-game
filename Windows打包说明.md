# 🪟 Windows 打包说明

## ⚠️ 重要提示

你现在在 **Mac** 上，无法直接编译 Windows 版本。

需要在 **Windows 电脑**上执行以下步骤。

---

## 📋 Windows 电脑准备清单

### 第一步：安装 C++ 编译器

**推荐方式：MSYS2**

1. 访问：https://www.msys2.org/
2. 下载并安装
3. 打开 "MSYS2 MSYS" 终端
4. 运行以下命令：

```bash
pacman -Syu
pacman -S mingw-w64-x86_64-gcc
pacman -S mingw-w64-x86_64-sfml
```

5. 添加到系统 PATH：
   - 路径：`C:\msys64\mingw64\bin`
   - 系统属性 → 高级 → 环境变量 → Path → 新增

---

### 第二步：传输项目文件

**方式A：U盘**
- 将整个 `SnakeGame` 文件夹拷贝到 U盘
- 在 Windows 上复制到任意位置

**方式B：网盘**
- 上传 `SnakeGame` 文件夹到 iCloud/OneDrive
- 在 Windows 上下载

**方式C：GitHub（推荐）**
```bash
# 在 Mac 上
cd ~/Downloads/Documentation/SnakeGame
git init
git add .
git commit -m "Initial commit"
git remote add origin YOUR_REPO_URL
git push -u origin main

# 在 Windows 上
git clone YOUR_REPO_URL
```

---

### 第三步：在 Windows 上打包

1. 打开 Windows 资源管理器
2. 找到项目文件夹
3. **双击运行 `build_windows.bat`**
4. 等待编译完成

---

## 📦 输出结果

编译成功后会生成：

```
releases/
└── windows/
    ├── SnakeGame.exe          ← 游戏主程序
    ├── sfml-graphics-3.dll    ← SFML 图形库
    ├── sfml-window-3.dll      ← SFML 窗口库
    ├── sfml-system-3.dll      ← SFML 系统库
    ├── openal32.dll           ← 音频库（可选）
    └── README.txt             ← 说明文件
```

---

## 🎁 分发给 Windows 用户

1. 将 `releases/windows/` 整个文件夹打包成 zip
2. 命名为 `SnakeGame-Windows.zip`
3. 发给用户

**用户使用方法：**
1. 解压 zip 文件
2. 双击 `SnakeGame.exe`
3. 开始游戏！

---

## ⚡ 快速测试

在 Windows 上编译完成后：

```cmd
cd releases\windows
SnakeGame.exe
```

游戏窗口应该立即弹出！

---

## 🐛 Windows 常见问题

### 找不到 g++ 命令

**解决：**
- 确保安装了 MSYS2
- 检查 PATH 环境变量包含 `C:\msys64\mingw64\bin`
- 重启终端/命令提示符

### 找不到 SFML

**解决：**
```bash
# 在 MSYS2 终端中
pacman -S mingw-w64-x86_64-sfml
```

### 双击 exe 没反应

**解决：**
- 检查所有 .dll 文件是否在同一文件夹
- 尝试从命令行运行看错误信息
- 确保是 64 位 Windows

### 提示缺少 DLL

**解决：**
- 重新运行 `build_windows.bat`
- 手动从 `C:\msys64\mingw64\bin\` 复制缺失的 DLL

---

## 💻 如果没有 Windows 电脑怎么办？

### 选项1：虚拟机
- 安装 VirtualBox 或 Parallels
- 安装 Windows 10/11
- 在虚拟机中编译

### 选项2：朋友的电脑
- 让有 Windows 的朋友帮忙编译
- 发送项目文件夹 + 这份说明

### 选项3：云服务
- 使用 GitHub Actions（免费）
- 自动编译 Windows 版本

### 选项4：只发布 Mac 版本
- 先发布 Mac 版本
- 等有 Windows 电脑再补充

---

## 🎯 总结

**在 Mac 上（现在）：**
```bash
./build_all.sh  # 生成 Mac 版本
```

**在 Windows 上（之后）：**
```cmd
build_windows.bat  # 生成 Windows 版本
```

**两个版本都完成后：**
- Mac: `releases/mac/SnakeGame-Mac.zip`
- Windows: 打包 `releases/windows/` 为 zip

---

需要帮忙设置 GitHub Actions 自动编译吗？
