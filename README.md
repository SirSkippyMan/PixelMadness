
# PIXEL MADNESS!!!   
A colourful, interactive pixel grid animation built with **SDL2**.   

Move your mouse, click, and tweak settings to create mesmerizing wave-based colour patterns in real time.   

**WARNING:** This program contains bright flashing colours that may trigger seizures in sensitive individuals. Viewer discretion is advised.

---
## Features
- Dynamic pixel grid rendering
- HSV-based smooth colour transitions
- Mouse-controlled animation direction and interaction
- Adjustable speed and colour frequency
- Multiple animation modes:   
	- Radial
	- Horizontal
	- Vertical
	- Diagonal
	- Spiral
	- Rings
- Optional debug mode for logging internal behaviour   
---
## System requirements   
- C compiler (e.g. `gcc`)
- SDL2 library

### Install SDL2   
#### Linux (Debian/Ubuntu)   
```bash
sudo apt-get install libsdl2-dev
````
#### macOS (Homebrew)   
```bash
brew install sdl2
````
#### Windows   
Download SDL2 from the [official site.](https://www.libsdl.org/)

---
## Compilation   
Compile using:   
```bash
make
````
---
## Running the program   
```bash
./pixelMadness
````
### Enable Debug Mode   
```bash
./pixelMadness debug
````
Debug mode prints internal state changes like speed, mode switches, and frequency adjustments.   

---
## Controls   
### Mouse   
- **Move mouse** → Changes animation origin and pattern
- **Left click (hold)** → Animate forward
- **Right click (hold)** → Animate backward   

### Keyboard   
#### Animation Modes
| Key | Mode       |
| --- | ---------- |
| 1   | Radial     |
| 2   | Horizontal |
| 3   | Vertical   |
| 4   | Diagonal   |
| 5   | Spiral     |
| 6   | Rings      |
#### Parameters

| Key     | Action                   |
| ------- | ------------------------ |
| ↑ Arrow | Increase color frequency |
| ↓ Arrow | Decrease color frequency |
| → Arrow | Increase animation speed |
| ← Arrow | Decrease animation speed |

---
## How it works   
- The screen is divided into a grid of square "pixels."
- Each pixel's colour is calculated using:
	- Distance from the mouse
	- Selected animation mode
	- A shifting hue offset
- Colours are generated in **HSV space** and converted to RGB.
- Animation occurs by continuously shifting hue values over time.
---
## Author   
**Josh Nygaard**   
joshdn03@gmail.com   
[LinkedIn](https://www.linkedin.com/in/josh-nygaard/)   
Version 1.0   

---
## License   
This project is open source and may be freely modified and distributed.
