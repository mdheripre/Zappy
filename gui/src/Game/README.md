# Zappy GUI Client

This README describes exclusively the Zappy graphical client (GUI). It covers installation, configuration, keyboard commands, and mouse interactions.

---

## Table of Contents

1. [Overview](#overview)  
2. [Prerequisites](#prerequisites)  
3. [Installation](#installation)  
4. [Configuration](#configuration)  
5. [Running the Client](#running-the-client)  
6. [Keyboard Controls](#keyboard-controls)  
7. [Mouse Interactions](#mouse-interactions)  
8. [License](#license)

---

## Overview

The GUI client displays the Zappy world state in real time: map tiles, players (Trantorians), resources, and events. It communicates with the server using the Zappy GUI protocol, sending and receiving messages to update the view.

---

## Prerequisites

- **C++17** or newer  
- **SFML 2.5** (Graphics, Window, Audio)  
- **CMake** ≥ 3.10  
- **Networking library** (e.g., Boost.Asio)

Refer to the official SFML documentation:  
https://www.sfml-dev.org/documentation/2.5.1/

---

## Installation

Clone the repository and build the GUI client:

```bash
git clone https://github.com/<your-org>/zappy.git
cd zappy/gui-client
```

Create a build directory and compile:

```bash
mkdir build && cd build
cmake ..
make
```

The executable will be generated at `build/bin/zappy_gui`.

## Running the Client

Use the following invocation from the project root:

"bash  
./zappy_gui -p <port> -h <machine>  
"

This will start the GUI client, connecting to the specified server host (`-h`) and port (`-p`).

---

## Keyboard Controls

| Key            | Action                                                                   |
|---------------:|:-------------------------------------------------------------------------|
| **Arrow Keys** | Pan the view by ±20 pixels in the corresponding direction.               |
| **W**          | Zoom in (×1.1).                                                          |
| **S**          | Zoom out (×0.9).                                                         |
| **R**          | Reset zoom to initial level.                                             |
| **P**          | Advance simulation by one time unit.                                     |
| **M**          | Rewind simulation by one time unit.                                      |
| **A**          | Toggle broadcast message visibility.                                     |
| **Z**          | Toggle team visibility.                                                  |
| **E**          | Toggle event visibility (e.g., death, birth).                            |
| **Y**          | Toggle player (Trantorian) visibility.                                   |
| **T**          | Toggle display of the current time unit.                                 |
| **Q**          | Pause/resume background music.                                           |

### Key Mapping in Code

The following key-to-action mappings are implemented in `GuiClient.cpp`:

## Mouse Interactions

- **Left-click on a Trantorian**: Display detailed information in the side panel (ID, team, level, inventory, position, etc.).

---