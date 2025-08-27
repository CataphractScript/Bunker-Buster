# 🚀 Bunker-Buster — Final README

## 📖 What is this?
**Bunker-Buster** is a small **C++17** graph-based simulation project. It models a network of cities (friendly / neutral / enemy) with missiles and simulates scenarios to compute paths and damage. The design is modular: headers live under `include/` and implementation under `src/` so it's straightforward to extend.

---

## 🗂️ Project layout (actual)

```
Bunker-Buster/
  docs/
    project-document.pdf
    report.md
  include/
    data/
      graph_data.hpp
      missile_data.hpp
    domain/
      city.hpp
      missile.hpp
    graph/
      graph.hpp
    sim/
      simulator.hpp
  src/
    data/
      graph_data.cpp
      missile_data.cpp      
    domain/
      city.cpp
      missile.cpp
    graph/
      graph.cpp
    sim/
      simulator.cpp
  CMakeLists.txt
  LICENSE
  main.cpp
  README.md
  
```
### Source files (for build)

- `main.cpp`
- `src/data/graph_data.cpp`
- `src/data/missile_data.cpp`
- `src/domain/city.cpp`
- `src/domain/missile.cpp`
- `src/graph/graph.cpp`
- `src/sim/simulator.cpp`

### Header files (API)

- `include/data/graph_data.hpp`
- `include/data/missile_data.hpp`
- `include/domain/city.hpp`
- `include/domain/missile.hpp`
- `include/graph/graph.hpp`
- `include/sim/simulator.hpp`

---

## ⚙️ Build & Run (recommended)

### Option A — Quick g++ build (single command)
From the project root (the folder that contains `main.cpp` and `src/`):

```bash
g++ -std=c++17 -Iinclude main.cpp main.cpp src/data/graph_data.cpp src/data/missile_data.cpp src/domain/city.cpp src/domain/missile.cpp src/graph/graph.cpp src/sim/simulator.cpp -o bunker-buster
```

> If your shell supports globs you can also run:
> ```bash
> g++ -std=c++17 -Iinclude main.cpp src/**/*.cpp -o bunker-buster
> ```

### Option B — Using a simple CMakeLists.txt (recommended for larger development)
Use `CMakeLists.txt` at project root:

```cmake
cmake_minimum_required(VERSION 3.15)

project(BunkerBuster VERSION 1.0 LANGUAGES CXX)

# Use at least C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler warnings
if(MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Wconversion)
endif()

# Source files
set(SRC_FILES
    ${CMAKE_SOURCE_DIR}/main.cpp
    ${CMAKE_SOURCE_DIR}/src/sim/simulator.cpp
    ${CMAKE_SOURCE_DIR}/src/graph/graph.cpp
    ${CMAKE_SOURCE_DIR}/src/data/graph_data.cpp
    ${CMAKE_SOURCE_DIR}/src/data/missile_data.cpp
    ${CMAKE_SOURCE_DIR}/src/domain/missile.cpp
    ${CMAKE_SOURCE_DIR}/src/domain/city.cpp
)

add_executable(BunkerBuster ${SRC_FILES})

# Include directories (project-local headers)
target_include_directories(BunkerBuster PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

# If you prefer a different binary name, change the target name above or set this
set_target_properties(BunkerBuster PROPERTIES OUTPUT_NAME "bunker_buster")

# Installation (optional)
install(TARGETS BunkerBuster RUNTIME DESTINATION bin)
```
Or 
Then:
```bash
mkdir build && cd build
cmake -G "MinGW Makefiles" ..
mingw32-make
```

### Run
```bash
./bunker_buster.exe
```

The program loads a predefined scenario (in `src/data/graph_data.cpp`) and prints computed paths to stdout. Example output:
```
Total damage: 1130
{IRN, Friendly, (500, 700)}
{SYR, Neutral, (280, 680)}
{JOR, Neutral, (300, 520)}
{ISR, Enemy, (220, 460)}
```

---

## 🧭 Available Scenarios / API (developer-facing)

The `Simulator` class (headers in `include/sim/simulator.hpp`) exposes:
- `Simulator()` — constructor
- `void set_graph(const Graph& g)` — set the graph to simulate
- `void run(int scenario_num)` — run a scenario by number (used by `main.cpp`)
- `std::vector<std::vector<int>> get_paths() const` — get computed paths after `run()`
- `scenario_1()`, `scenario_2()`, `scenario_3(...)`, `scenario_4(...)` — internal scenario helpers you can call/extend

Helper functions to build graphs are provided in `include/data/graph_data.hpp` (e.g. `load_graph_for_scenario2()`), which returns a `Graph` populated with `City` nodes (friendly/neutral/enemy).

**Tip:** To add a new scenario:
1. Add a `scenario_N()` method in `src/sim/simulator.cpp` and declare it in the header.
2. Call it from `run(int scenario_num)`.
3. Optionally add a new `load_graph_for_scenarioN()` in `src/data/graph_data.cpp` to create a graph tailored to that scenario.

---

## 🧩 Design notes & important files
- `include/` — public headers (graph, domain, sim, data interfaces)
- `src/` — implementation (`graph.cpp`, `simulator.cpp`, `domain/*.cpp`, `data/*.cpp`)
- `main.cpp` — example entrypoint that uses `Simulator` and `load_graph_for_scenario2()`
- `src/data/graph_data.cpp` — contains the scenario used by default (country/city setup)

---

## 🛠️ Common pitfalls & troubleshooting
- **Missing include path**: Use `-Iinclude` (or configure your IDE to add the `include/` directory) otherwise headers won't be found.
- **Order of files**: When compiling manually, include all `.cpp` files or compile into object files and link.
- **C++ standard**: Use `-std=c++17` (some code uses C++17 features).
- **Undefined references**: If you forget to compile/link one of the `src/*.cpp` files you'll get undefined symbol errors — include them all.

---

## 🤝 Contributing
Contributions, bug reports and feature ideas are welcome. Please:
1. Fork the repo
2. Add tests or examples for new scenarios
3. Open a PR with a clear description

Add a small `ISSUE_TEMPLATE.md`/`CONTRIBUTING.md` if this becomes a public project.

---

## 🧾 License
This project is licensed under the **MIT License** — see the [LICENSE](LICENSE) file for details.


---

## ✍️ Authors
- Mohammad Matin Soleimani 
- Parsa Dowlatabadi