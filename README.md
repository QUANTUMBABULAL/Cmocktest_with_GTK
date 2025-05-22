# Question Paper Generator (GTK+3, C)

A modern, interactive desktop application for generating and taking C programming quizzes and question papers. Built with GTK+3 and C.

## Features

- **Generate Question Papers:** Create question papers with MCQs, descriptive, or mixed questions.
- **Quiz Mode:** Take quizzes filtered by difficulty and type.
- **Professional UI:** Stylish, responsive interface with dark mode and accent colors.
- **CSV Data:** Easily add or edit questions in `data/questions.csv`.

## Project Structure

```
CMakeLists.txt
build/                  # Build output directory
data/
  questions.csv         # All questions (MCQ & descriptive) in CSV format
src/
  main.c                # Main application logic
  file_utils.c/h        # File loading utilities
  generator.c/h         # Question paper generation logic
  quiz.c/h              # Quiz mode logic
  style.c/h             # UI styling (CSS, fonts, colors)
  question.h            # Question struct definition
```

## Requirements
->you will need these to run the gui
- GCC (MinGW-w64 on Windows recommended)
- GTK+3 development libraries
- CMake 3.10+

## Building

1. **Install dependencies:**
   - On Windows (MSYS2):  
     ```
     pacman -S mingw-w64-x86_64-gtk3 mingw-w64-x86_64-toolchain cmake
     ```
   - On Linux:  
     ```
     sudo apt install build-essential libgtk-3-dev cmake
     ```

2. **Build the project:**
   ```sh
   mkdir build
   cd build
   cmake ..
   make
   ```

3. **Run the app:**
   ```sh
   ./QuestionGeneratorApp.exe   # On Windows
   ./QuestionGeneratorApp       # On Linux
   ```

### Usage

- **Select Difficulty:** Choose from Easy, Medium, or Hard.
- **Select Question Type:** MCQ, Descriptive, Both, or Take Quiz.
- **Quiz Mode:** Answer questions interactively and see your score.
- **Generate Paper:** View and copy a formatted question paper.

### Customizing Questions

Edit [`data/questions.csv`](data/questions.csv) to add, remove, or modify questions.  
- MCQ rows must include options and correct answer.
- Descriptive rows can leave options/answer columns empty.

### Credits

- Built with [GTK+3](https://www.gtk.org/) and C.
- Developed by CHINMAI A S 
- CSE(AIML) -PES Uni


*Enjoy generating and taking C programming quizzes!*