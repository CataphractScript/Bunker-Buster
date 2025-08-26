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
# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Define the project name and language
project(BunkerBuster LANGUAGES CXX)

# Set the C++ standard (C++17 in this case)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Collect all source files from src/ and main.cpp
file(GLOB_RECURSE SOURCES
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/main.cpp"
)

# Create the executable target
add_executable(${PROJECT_NAME} ${SOURCES})

# Include directory scoped to the target
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Set compiler warnings
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /permissive-)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

# Optional: Debug/Release output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_BINARY_DIR}/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_BINARY_DIR}/Release)

```
Or 
Then:
```bash
mkdir build && cd build
cmake ..
cmake --build . --config Release
```

### Run
```bash
cd Release
./BunkerBuster.exe
```

The program loads a predefined scenario (in `src/data/graph_data.cpp`) and prints computed paths to stdout. Example output:
```
1   3   5
2   4   6
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