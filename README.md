# 🧠 Zappy

Welcome to our implementation of **Zappy**, a multiplayer network game built as part of the Epitech YEP (Year-End Project).

This repository contains the complete source code for:
- `zappy_server`: the game server (written in C)
- `zappy_gui`: the graphical client (written in C++ with SFML)
- `zappy_ai`: an autonomous AI client (written in Rust)

Our version strictly follows the official Zappy protocol and architecture, with a strong focus on modularity, clean command handling, multithreaded networking, and a responsive GUI.

## 🧩 How the Game Works

Zappy is a real-time multiplayer game where teams of AI players compete to evolve to the highest level. The game takes place on a 2D toroidal map filled with various resources.

### Objective

The first team to have **6 players at level 8** wins the game.

### Core Concepts

- **Map**: a flat, wraparound grid of tiles containing players and resources.
- **Resources**:
  - `food`, `linemate`, `deraumere`, `sibur`, `mendiane`, `phiras`, `thystame`
- **Elevation**: players level up by performing **incantations**, which require specific amounts of resources and other players of the same level on the same tile.
- **Teams**: each team starts with a set number of available slots (eggs) and must coordinate its players to evolve.

## ⏱️ Time Management

Zappy uses a unit-based time system controlled by the `-f` parameter passed to the server.

- All actions take a duration proportional to `1 / freq`, where `freq` is the time unit multiplier.

### Life

Each player starts with 1260 time units (i.e., `1260 / f` seconds). They must consume `food` to stay alive. Every food unit gives +126 time units.


## 🛰️ AI Protocol Overview

The AI client communicates with the server via TCP sockets using plain text commands.

### Initial Handshake

1. Server -> `WELCOME`
2. Client -> `team_name`
3. Server -> `client_number`
4. Server -> `map_size_x map_size_y`

### Core Commands

| Action       | Command           | Duration      | Response       |
|--------------|-------------------|---------------|----------------|
| Move forward | `Forward`         | `7 / f`       | `ok`           |
| Turn left    | `Left`            | `7 / f`       | `ok`           |
| Turn right   | `Right`           | `7 / f`       | `ok`           |
| See         | `Look`            | `7 / f`       | `[tile1, ...]` |
| Inventory   | `Inventory`       | `1 / f`       | `[food n, ...]`|
| Take item   | `Take object`     | `7 / f`       | `ok` / `ko`    |
| Drop item   | `Set object`      | `7 / f`       | `ok` / `ko`    |
| Fork (egg)  | `Fork`            | `42 / f`      | `ok`           |
| Broadcast   | `Broadcast text`  | `7 / f`       | `ok`           |
| Start level-up | `Incantation`  | `300 / f`     | `Elevation underway` / `ko` |
| Free slots  | `Connect_nbr`     | `0`           | `<number>`     |

Each command must be followed by a newline (`\n`), and the server responds in order.


## 🖼️ GUI Protocol Overview

The GUI client connects using a reserved team name:
```
GRAPHIC
```

###
 GUI receives real-time updates via these messages:

| Message        | Description                                  |
|----------------|----------------------------------------------|
| `msz X Y`      | Map size                                     |
| `bct X Y q0..q6` | Tile content at (X,Y)                     |
| `mct`          | Entire map content (multiple `bct`)          |
| `tna N`        | Team names                                   |
| `pnw #n X Y O L N` | New player connected                   |
| `ppo #n X Y O` | Player position                              |
| `plv #n L`     | Player level                                 |
| `pin #n X Y q0..q6` | Player inventory                       |
| `pex #n`       | Player expulsion                             |
| `pbc #n M`     | Broadcast message                            |
| `pic X Y L #n...` | Start of incantation                    |
| `pie X Y R`    | End of incantation (`R` = 0: fail, 1: success)|
| `pfk #n`       | Player lays egg                              |
| `enw #e #n X Y`| Egg laid by player                           |
| `ebo #e`       | Player hatched from egg                      |
| `edi #e`       | Egg died                                     |
| `pdr #n i`     | Player drops resource                        |
| `pgt #n i`     | Player takes resource                        |
| `pdi #n`       | Player dies                                  |
| `seg N`        | Game over - team `N` wins                    |
| `sgt T`        | Current time unit                            |
| `sst T`        | Time unit updated                            |
| `smg M`        | Server message                               |
| `suc`          | Unknown command                              |
| `sbp`          | Command syntax error                         |

The GUI must implement a stateful listener loop and render the game based on these updates.

## 🧱 Project Components

### 🧠 `server/` — The Game Server

The `zappy_server` is the core of the game. It handles:

- player and team management
- resource generation and map state
- the execution of all AI commands
- event scheduling and game progression
- communication with both GUI and AI clients via TCP

It implements the full protocol, command queueing, and time-based execution system.

📄 For a deep dive into its architecture, see [`server/TECHNICAL.md`](server/TECHNICAL.md)


### 🖼️ `gui/` — The Graphical Client

A REMPLIR CHARLES

### 🤖 `ai/` — The Rust AI Client

Our AI system employs a hierarchical structure where one AI instance assumes the role of the Alpha AI. This design facilitates coordinated actions and efficient resource management across the team.

#### The Alpha AI

The Alpha AI is central to our strategy. Its primary responsibilities include:
- Communication Hub: It communicates crucial information to other AI clients, especially when a new AI connects to the game [Query].
- Team Expansion: The Alpha AI is responsible for initiating player reproduction by using the fork command, leading to the production of an egg and adding a new slot for the team. Once an egg is laid, the Alpha AI can resume other activities. This operation authorizes a new client to connect to the team.

#### Communication and Security

Communication between AI clients is facilitated through the server via the Broadcast command. All players can hear broadcasts and perceive the direction from which the sound originates, but they do not know the sender. To ensure the integrity of messages exchanged within the team, our AI system incorporates a unique ID mechanism to detect and filter out fake messages. This is crucial for maintaining trust and coordination among team members.

#### Strategic Approach

Our AI employs a multi-phase strategy focused on efficient resource collection, continuous team expansion, and synchronized elevation rituals.

// Initial Phase: Resource Gathering and Expansion

- Alpha's Role: Initially, the Alpha AI prioritizes collecting essential resources while simultaneously using the fork command to create new AI instances.

- New AI's Role: Once new AI players connect and hatch from eggs, their primary focus is also on collecting resources and food to ensure their survival.

// Late Game: Coordinated Elevation

- Elevation Prerequisite Check: Once the collective inventory of the AI team indicates they have sufficient food and resources (stones) to reach the maximum elevation level (level 8) according to the ritual requirements, the Alpha AI initiates the final phase.

- Gathering and Incantation: The Alpha AI will instruct other AIs to gather on a specific tile to perform the elevation ritual. Once all the AIs are gathered, they start the ritual.

## 🚀 How to Launch the Project

### 1. Dependencies

```
cargo
make
c
c++
```

### 2. Build everything

From the root of the project:

```
make
```

This will generate the following executables at the root:

- `./zappy_server`
- `./zappy_gui`
- `./zappy_ai`

### 1. Available commands

#### 🔌 Server — `./zappy_server`

Run the game server.

```
USAGE: ./zappy_server -p <port> -x <width> -y <height> -n <team1> <team2> ... -c <clients/team> -f <freq> [-d]

Options:
  -p <port>         Port number to listen on
  -x <width>        Width of the world map
  -y <height>       Height of the world map
  -n <teams...>     List of team names (at least one)
  -c <slots>        Number of authorized clients per team
  -f <freq>         Time unit frequency (actions = duration / freq)
  -d                (optional) Enable debug logs on the server
```

Example:

```
./zappy_server -p 4242 -x 20 -y 20 -n alpha beta -c 4 -f 100 -d
```

#### 🖼️ GUI — `./zappy_gui`

Run the graphical interface (2D rendering via SFML).

```
USAGE: ./zappy_gui -p <port> -h <machine>

Options:
  -p <port>         Port to connect to
  -h <machine>      IP address or hostname of the server
```

Example:

```
./zappy_gui -p 4242 -h localhost
```

#### 🤖 AI — `./zappy_ai`

Run an autonomous Rust AI client.

```
USAGE: ./zappy_ai -p <port> -n <team_name> -h <machine>

Options:
  -p <port>         Port to connect to
  -n <team_name>    Name of the team to join
  -h <machine>      IP address or hostname of the server
```

Example:

```
./zappy_ai -p 4242 -n alpha -h 127.0.0.1
```


