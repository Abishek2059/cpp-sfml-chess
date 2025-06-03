# ♟️ Chess in SFML

A graphical chessboard built entirely in C++ using SFML 3.0. This project showcases object-oriented design and event-based graphics programming with interactive mouse support for selecting chessboard squares. All pieces are displayed in their correct initial positions.

---
<p align="center">
  <img src="https://github.com/Abishek2059/cpp-sfml-chess/blob/main/Screenshot%202025-05-31%20035016.png?raw=true" alt="Screenshot 1" width="45%"/>
  &nbsp;
  <img src="https://github.com/Abishek2059/cpp-sfml-chess/blob/main/Screenshot%202025-06-03%20052641.png?raw=true" alt="Screenshot 2" width="45%"/>
</p>




## 💻 Tech Stack

- **Language:** C++17  
- **Graphics Library:** SFML 3.0  
- **Build System:** CMake ≥ 3.16  
- **Compiler:** MinGW-w64 (GCC 14.2.0, UCRT)  
- **Editor:** Visual Studio Code (✅ recommended with IntelliSense)

🪟 **Platform:** Built and tested for **Windows OS**  


---

## 🚀 Current Stage

- ✅ **Board**: Grid drawn with alternating square colors  
- ✅ **Piece Setup**: All 12 chess pieces placed at standard initial positions  
- ✅ **Input**: Mouse input highlights clicked squares  
- ✅ **Movement**: Piece movement with basic rules validation  
- ✅ **Game Logic**: Check, checkmate, stalemate detection  
- ❌ **Advanced Rules**:
  - Castling  
  - En passant capture  
  - Draw by 50-move rule  
  - Draw by insufficient material  


---


## ⚙️ How to Build and Run (Windows Only)

> 🧰 **Requirements:**
> 
> - **C++17 compiler:** MinGW-w64 (GCC 14.2.0, UCRT recommended)  
> - **SFML 3.0:** [Download from official site](https://www.sfml-dev.org/download.php)  
> - **CMake ≥ 3.16**  
> - ✅ *Optional but recommended:* [Visual Studio Code](https://code.visualstudio.com/) with the [CMake Tools Extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools)  
> 
> 🔧 Ensure the following paths are correctly set in your CMakeLists.txt and environment:  
> 
> - `SFML_DIR = C:/SFML-3.0`  
> - `GCC DLLs = C:/winlibs-x86_64-posix-seh-gcc-14.2.0-.../mingw64/bin`



### 🛠️ Step 1: Install SFML

1. Download the **SFML 3.0 - GCC 14.2.0 (UCRT) 64-bit** version.
2. Extract it to a known location like:

```
C:/SFML-3.0
```

3. Make sure your `CMakeLists.txt` includes:

```cmake
include_directories("C:/SFML-3.0/include")
link_directories("C:/SFML-3.0/lib")
```



### 📥 Step 2: Clone and Build

```bash
git clone https://github.com/Abishek2059/cpp-sfml-chess.git
cd cpp-sfml-chess
mkdir build
cd build
cmake ..
cmake --build .
```



### ▶️ Step 3: Run the Executable

```bash
./Chess.exe
```

---

### 💡 Notes

- If `libstdc++-6.dll` or `sfml-graphics-3.dll` is missing, ensure your **MinGW/bin** and **SFML/bin** are in your system `PATH`.
- To rebuild cleanly, delete the `build/` directory and repeat the steps above.
- The `assets/` folder (images + fonts) is required at runtime; don’t move it unless you update the code path.



---

## 📁 Folder Structure

Chess/  
├── assets/  
│   ├── white_king.png  
│   ├── black_queen.png  
│   ├── arial.ttf  
│   └── ... (other chess piece images like white_queen.png, black_pawn.png, etc.)  
│  
├── header/  
│   ├── board.h  
│   ├── pieces.h  
│   └── piece.h  
│  
├── src/  
│   ├── main.cpp  
│   ├── board.cpp  
│   ├── pieces.cpp  
│   └── game.cpp  
│  
├── build/  
├── CMakeLists.txt  
└── README.md  


## 📄 Folder Descriptions

- `assets/` – Contains PNG images for chess pieces (e.g., `white_king.png`, `black_queen.png`) and the font file (`arial.ttf`) used to display text.
- `header/` – Header files defining class interfaces and game logic, such as `board.h`, `pieces.h`, and `piece.h`.
- `src/` – C++ source files implementing the chess logic, graphics rendering, and event handling.
- `build/` – Auto-generated directory where CMake stores compiled binaries and intermediate files (usually excluded from version control).
- `CMakeLists.txt` – Build configuration file used by CMake to generate build scripts.
- `README.md` – Project overview, setup instructions, and documentation.

---






## 🔄 Pull Requests

Pull requests will be welcome **after all fundamental logic are implemented**.  
Stay tuned for an update in this section!


## 📄 License & Asset Credits

The chess piece images used in this project are sourced from public domain assets and are licensed under the [CC0 1.0 Public Domain Dedication](https://creativecommons.org/publicdomain/zero/1.0/).

🛠️ This project is currently **under active development**.  
It will be released under the **MIT License** upon completion.

👨‍💻 Developed by **Dadhiram (Abishek) Bhattarai**


