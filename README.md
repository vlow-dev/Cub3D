# Cub3D 🎮
A Wolfenstein-3D–style raycasting engine built with **C** and **MiniLibX (X11)**. Renders a 3D scene from a 2D map, with textured walls and basic player movement.

> 42KL educational project. Linux build with `minilibx-linux`.

---

## ✨ Features
- Raycasting renderer (DDA)
- Textured walls & floor/ceiling colors
- Keyboard input (movement + rotation)
- Basic collision detection
- `.cub` map parser (resolution, colors, textures, layout)
- Minimal HUD/info overlay (optional)

---

## 🧭 Controls
- **W / S** — Move forward / backward  
- **A / D** — Strafe left / right  
- **← / →** — Rotate left / right  
- **ESC** — Quit

---

## 🛠️ Build & Run (Linux)

### 1) Dependencies
- **C toolchain:** `gcc`, `make`
- **X11 libs:** `libx11`, `libxext`
- **Others:** `libbsd` (depending on your MLX build)

Ubuntu/Debian:
```bash
sudo apt update
sudo apt install -y build-essential libx11-dev libxext-dev libbsd-dev
