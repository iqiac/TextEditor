// Core Components
// 1. Text Buffer: A data structure to hold the text being edited.
// 2. Cursor: A component to keep track of the current position in the text buffer.
// 3. Command Handling: A mechanism to interpret user inputs as commands.
// 4. Screen Rendering: A component to display the text buffer and cursor in the terminal.

#include "CursorManager.h"
#include "ScreenRenderer.h"
#include "TextBuffer.h"

#include <chrono>
#include <fstream>
#include <functional>
#include <iostream>
#include <ncurses.h>
#include <string>
#include <thread>

int main(int argc, char* argv[]) {
  // Get filepath as argument
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <filepath>\n";
    return 1;
  }

  // Open file
  std::string   filepath{argv[1]};
  std::ifstream file(filepath);
  if (!file.is_open()) {
    std::cerr << "Failed to open file: " << filepath << "\n";
    return 1;
  }

  // Store file content into appropriate format
  std::vector<std::string> lines;
  std::string              line;
  while (std::getline(file, line)) {
    lines.push_back(line);
  }
  file.close();

  // Setup ncurses
  initscr();                              // Init ncurses
  curs_set(1);                            // Turn on cursor blinking
  start_color();                          // Enable color support
  init_pair(1, COLOR_WHITE, COLOR_BLACK); // Initialize color pairs

  // Initialize the components
  TextBuffer     textBuffer{};
  CursorManager  cursorManager{textBuffer};
  ScreenRenderer screenRenderer{};
  UpdateFunction screenRendererUpdate = std::bind(&ScreenRenderer::Update, &screenRenderer, std::placeholders::_1);
  textBuffer.Attach(screenRenderer.GetObserverName(), screenRendererUpdate);
  cursorManager.Attach(screenRenderer.GetObserverName(), screenRendererUpdate);

  // Run TextEditor
  bool running{true};
  while (running) {
    char input;
    std::cin >> input;
    if (input == 'q') {
      running = false;
    }
    // Sleep for short duration to prevent high CPU usage
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  // Clean up and close ncurses
  endwin();

  return 0;
}
