# Playlist Management

## Overview
This project implements a playlist management system in C++ using a doubly linked list data structure. Developed as part of a Data Structures course at the University of Piraeus, it allows users to manage songs with attributes like title, singer name, album title, and likes. The system features a menu-driven interface with eight options for song insertion, navigation, random playback, movement, sorting, and printing.

## Technologies
- **Language**: C++
- **Standard Library**: `<iostream>`, `<string>`, `<cstdlib>`, `<ctime>`, `<algorithm>` (for `shuffle`)

## Features
- **Song Class**: Stores song details (title, singer name, surname, album title, likes) with `next` and `prev` pointers.
- **Playlist Class**: Manages a doubly linked list with the following methods:
  - `insertSong`: Adds a new song to the playlist.
  - `nextSong`: Plays the next song, handling empty list or end-of-list cases.
  - `prevSong`: Plays the previous song, with similar edge case handling.
  - `playAllRandom`: Shuffles and plays all songs in random order using `std::shuffle`.
  - `moveSong`: Moves a song to a new position, with checks for invalid positions.
  - `sortPlaylist`: Sorts the playlist based on user-selected criteria (e.g., likes).
  - `printPlaylist`: Displays all songs in the current order.
- **Menu Interface**: Offers 8 options in a loop, exiting only with option 8.

## Installation
1. Clone the repository:
   ```
   git clone https://github.com/OzzYBcc/playlist-management.git
   ```
2. Navigate to the project directory:
   ```
   cd playlist-management
   ```
3. Compile the code with a C++ compiler (e.g., g++):
   ```
   g++ -o playlist main.cpp
   ```
4. Run the executable:
   ```
   ./playlist
   ```

## Usage
- **Sample Menu Output**:
  ```
  Menu:
  1. Insert new song into playlist
  2. Play next song in playlist
  3. Play previous song in playlist
  4. Play all songs in playlist in random order
  5. Move song to another position in playlist
  6. Sort playlist
  7. Print playlist to screen
  8. Exit
  Enter your choice: 
  ```
- **Sample Code Snippet (insertSong Method)**:
  ```cpp
  void insertSong(const Song& newSong) {
      Song* newSongPtr = new Song(newSong);
      if (head == nullptr) {
          head = newSongPtr;
          tail = newSongPtr;
      } else {
          tail->next = newSongPtr;
          newSongPtr->prev = tail;
          tail = newSongPtr;
      }
  }
  ```
- Enter song details (title, singer name, etc.) for option 1, or select options 2-7 to interact with the playlist.

## Contributing
Contributions are welcome! Enhance features (e.g., add file I/O or additional sort criteria) by forking the repository and submitting a pull request.

## License
MIT License