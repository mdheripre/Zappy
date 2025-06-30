# 🧠 Zappy Server — Technical Overview

## 🏗️ Introduction

The `zappy_server` was implemented in C, but we adopted a **modular and object-oriented architecture** to ensure clarity, scalability, and maintainability.

Even though C is not object-oriented by nature, we structured the code following common OOP patterns such as:

- **Encapsulation**: using structs with associated `.c` files for methods
- **Constructors / Destructors**: each component has `*_create()` and `*_destroy()` functions
- **Responsibility Separation**: each module handles a specific task (game loop, event dispatching, command parsing, etc.)
- **Dependency Injection**: objects pass references to each other for communication and shared state

This approach allowed us to isolate the logic of the server into independent, reusable components that are easy to test and reason about.

## 📦 Main Modules (Overview)

Each module is located in its own folder inside `server/src/` and follows a clear pattern:
- `constructor/`: contains `*_create.c` functions
- `destructor/`: contains `*_destroy.c` functions
- `methods/`: contains all logic methods
- `events/`: contains code for handling commands/events

The major modules are:
- `server_t`: main structure holding sockets and game state
- `game_t`: core gameplay logic (map, players, rules)
- `dispatcher_t`: event system
- `command_manager_t`: routing and parsing protocol commands
- `poll_manager_t`: multiplexed I/O abstraction (poll syscall)
- `config_t`: command-line argument parsing and validation
- `player_t`, `client_t`, `egg_t`: entities representing the game state

## 🧱 Core Objects & Structures

This section presents each major object used in the server implementation. Every component is represented by a dedicated `struct`, and we follow a modular, object-like design pattern in C.

### 🧩 `dispatcher_t`

**Header**: `dispatcher.h`  
The dispatcher is a centralized event manager. It stores event → callback mappings and allows modules to emit named events.

```c
struct event_handler_s {
    event_callback_t callback;
    void *ctx;
};

struct dispatcher_methods_s {
    void (*emit)(dispatcher_t *self, int index, void *data);
    bool (*register_event)(dispatcher_t *self, int index,
        event_callback_t callback, void *ctx);
};

struct dispatcher_s {
    event_handler_t handlers[MAX_EVENT_HANDLERS];
    const event_type_map_entry_t *map;
    size_t map_size;
    event_not_found_t on_not_found;
    const dispatcher_methods_t *vtable;
};
```

All registered callbacks are stored in a list. When `dispatcher_emit()` is called, the corresponding callbacks are triggered with user-defined context and data.

### 🧩 `command_manager_t`

**Header**: `command_manager.h`  
Manages protocol commands for AI and GUI clients.

```c
struct command_manager_methods_s {
    void (*register_all)(command_manager_t *self, server_t *server);
    void (*process_identify)(command_manager_t *self, server_t *server);
    void (*process_all)(command_manager_t *self, server_t *server,
        int ticks);
    void (*process_responses)(command_manager_t *self, game_t *game,
        server_t *server);
};

struct command_manager_s {
    const command_manager_methods_t *methods;
    dispatcher_t *dispatcher;
};
```

Each command is stored with its name, type (GUI or IA), and handler. Handlers are functions executed when a command is parsed from a client input.

### 🧩 `list_t`

**Header**: `list.h`  
Generic, type-agnostic linked list with destructor awareness.

```c
typedef struct list_methods_s {
    void (*destroy)(list_t *self);
    void (*clear)(list_t *self);
    void (*push_back)(list_t *self, void *data);
    void (*push_front)(list_t *self, void *data);
    void *(*pop_front)(list_t *self);
    int (*size)(const list_t *self);
    bool (*contain)(list_t *self, void *data, bool (*compare)(void *, void *));
    void (*remove)(list_t *self, void *target);
    void *(*consume)(list_t *self, bool (*match)(void *, void *), void *data);
    void *(*front)(const list_t *self);
    void *(*index)(const list_t *self, size_t index);
} list_methods_t;

struct list_s {
    list_node_t *head;
    list_node_t *tail;
    int size;
    void (*free_fn)(void *);
    const list_methods_t *methods;
};
```

Any module can create a list with its own destructor, allowing recursive cleanup when `list_destroy()` is called. This serves as our **memory safety and garbage collection backbone**.

### 🧩 `game_t`

**Header**: `game.h`  
Contains the full state of the game (map, players, resources, etc.).

```c
struct game_methods_s {
    void (*dispatch_events)(game_t *self);
    void (*update)(game_t *self, int tick);
    int (*count_team_members)(game_t *self, const char *team_name);
    void (*update_players)(game_t *self, int tick);
    void (*spawn_resources)(game_t *self);
    void (*update_incantations)(game_t *self, int tick);
    bool (*check_incantate)(game_t *self, incantation_t *inc);
    list_t *(*get_players_on_tile)(game_t *self, int x, int y, int level);
    bool (*has_finished)(game_t *self);
    char *(*get_winner)(game_t *self);
};

struct game_s {
    int width;
    int height;
    double frequency;
    unsigned long last_tick_time;
    int tick_counter_tiled;
    unsigned long tick_counter;
    bool has_finished;
    int max_players;
    int egg_id_current;

    tile_t **map;
    list_t *teams;
    list_t *players;
    list_t *eggs;
    list_t *incantations;
    list_t *event_queue;
    list_t *server_event_queue;
    dispatcher_t *dispatcher;
    const game_methods_t *methods;
};
```

The game owns all live entities and emits game events through the dispatcher. The main loop calls `game_update()` to tick this state.

### 🧩 `player_t`

**Header**: `player.h`  
Represents a player in the world.

```c
typedef struct player_methods_s {
    void (*move)(player_t *self, int map_width, int map_height,
        move_direction_t dir);
    void (*die)(player_t *self);
    void (*add_resource)(player_t *self, int resource_type, int amount);
    void (*remove_resource)(player_t *self, int resource_type, int amount);
    void (*update)(player_t *self, game_t *game, int ticks);
} player_methods_t;

struct player_s {
    int id;
    int x;
    int y;
    player_orientation_t orientation;
    client_t *client;
    int level;
    bool is_alive;
    char *team_name;
    int inventory[INVENTORY_SIZE];
    int nbr_tick;

    const player_methods_t *methods;
};
```

Each player tracks their own position, orientation, inventory, and lifecycle. They are linked to both their team and underlying network `client_t`.

### 🧩 `poll_manager_t`

**Header**: `poll_manager.h`  
Abstraction over the `poll()` syscall for multiplexed socket handling.

```c
typedef struct poll_manager_methods_s {
    bool (*resize)(poll_manager_t *, size_t);
    struct pollfd *(*get_fds)(poll_manager_t *, nfds_t *);
    void (*destroy)(poll_manager_t *);
} poll_manager_methods_t;

typedef struct poll_manager_s {
    struct pollfd *fds;
    nfds_t nfds;
    size_t capacity;
    poll_manager_methods_t methods;
} poll_manager_t;

```

This is used by `server_t` to check for incoming data from multiple clients at once.

## 🧹 Centralized Memory Management (a.k.a Garbage Collection)

Though written in C, our architecture mimics garbage collection through:

- **Encapsulated destructors**: Each module owns its resources and frees them via `*_destroy()`
- **Lists with destructors**: `list_t` ensures everything it contains is cleaned up recursively
- **Hierarchical ownership**:
  - `server_t` owns `dispatcher`, `poll_manager`, and `game_t`
  - `game_t` owns players, teams, eggs, and map
  - `client_t` links to `player_t` or egg

This layered structure means calling `server_destroy()` triggers cleanup of all child objects.




