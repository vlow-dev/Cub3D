# Cub3D 🎮
A Wolfenstein-3D–style raycasting engine built with **C** and **MiniLibX (X11)**.  

---

## ✨ Features
- Raycasting renderer (DDA algorithm)  
- Textured walls & floor/ceiling colors  
- Keyboard input (movement + rotation)  
- Collision detection with walls  
- `.cub` map parser (config + map layout)  

---

## 🚀 Bonus & Optimizations
- 🧩 **Sprites** — fully implemented with correct depth sorting & rendering  
- 🧭 **Minimap** — real-time player position + walls overview  
- 🖱️ **Mouse controls** — smooth camera rotation using the mouse  
- 🚪 **Doors** — interactable doors that open/close  
- 🎨 **Multiple textures** — extended support for floor & ceiling rendering  
- 🌀 **Animated sprites** (where supported)  
- ⏱️ **Delta time implementation** — ensures frame-independent player movement & rotation, smoother gameplay across different machines  

---

## 🧭 Controls
- **W / S** — Move forward / backward  
- **A / D** — Strafe left / right  
- **← / →** — Rotate view left / right  
- **Mouse** — Rotate view smoothly  
- **ESC** — Quit game  

---

## 🛠️ Build & Run (Linux)

### 1) Install dependencies
```bash
sudo apt update
sudo apt install -y build-essential libx11-dev libxext-dev libbsd-dev
