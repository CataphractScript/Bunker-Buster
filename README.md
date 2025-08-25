# Bunker-Buster

## 📌 Project Overview

**Bunker-Buster** is a final project for the "Algorithms Design and Analysis" course, implemented in C++. The main goal of this project is to develop missile routing algorithms to maximize damage in simulated war scenarios. This project is also referred to as **“Sangar Shekan.”**

## 🧠 Objective and Applications

The project simulates a war scenario where strategic missiles must be optimally launched at various targets (such as bunkers and military installations) to inflict maximum damage. The algorithms can be used for military analysis, strategic planning, and simulation purposes.

## ⚙️ Key Features

* Implementation of optimized pathfinding algorithms for missiles
* Simulation of war scenarios with multiple targets
* Analysis and evaluation of algorithm performance under different conditions
* Use of advanced data structures to enhance computational efficiency

## 🛠️ Project Structure

The repository is organized as follows:

* `src/`: Contains source code
* `include/`: Contains header files
* `docs/`: Project documentation
* `LICENSE`: License file

## 📥 How to Run

Clone the repository:

```bash
git clone https://github.com/M-M-Soleimani/Bunker-Buster.git
```

Navigate into the project directory:

```bash
cd Bunker-Buster
```

Compile and run the project:

```bash
g++ -o bunker_buster src/*.cpp
./bunker_buster
```

## 🧩 Algorithms and Project Logic

The project includes four main scenarios, each using different algorithms for missile pathfinding and targeting:

### 1️⃣ Scenario 1: Launching D-Class Missiles

* **Algorithm:** Step-by-step search selecting the nearest city to the target
* **Logic:**

  * Launch all D-class missiles from friendly cities.
  * For each missile, the path toward the nearest enemy city is calculated.
  * If a city along the path has a spy, the missile may be detected.
  * The missile proceeds until it hits the target or cannot find a valid path.
* **Note:** This scenario is a **Greedy Search**, always selecting the next step closest to the target.

### 2️⃣ Scenario 2: Launching A-Class Missiles

* **Algorithm:** Constrained path search considering range and spy detection
* **Logic:**

  * Possible paths are evaluated to minimize distance to enemy cities while avoiding spies.
  * If the number of spies along the path exceeds a limit, the missile is canceled or destroyed.
* **Note:** A combination of **Greedy Search with constraints**.

### 3️⃣ Scenario 3: Launching B1, B2, C, and C1 Missiles

* **Algorithm:** Range-based pathfinding with stealth considerations
* **Logic:**

  * Missiles of types **B1, B2, C, and C1** are assigned to friendly bases capable of reaching enemy targets.
  * The path from base to target considers:

    * Missile range
    * Presence of spies along the path
    * Enemy defenses at the target city
  * Each time a missile passes through a city with a spy, its **stealth** value decreases.

    * If stealth drops to zero, the missile is **detected** and may be destroyed by enemy defenses.
  * Only missiles that successfully reach the target without being destroyed inflict damage.
* **Note:** This scenario combines **Greedy path selection** with **stealth-aware decision-making** to maximize successful hits while avoiding detection.

### 4️⃣ Scenario 4: Launching A, B, and C Missiles at the Nearest Target

* **Algorithm:** Nearest-Neighbor search based on missile range
* **Logic:**

  * For each base, the nearest enemy city within missile range is selected.
  * Paths and spy detection are considered to maximize the chance of successful hits.
* **Note:** **Nearest-Neighbor Search with range and detection constraints**.

### ⚡ Summary of Algorithms

* The project uses a combination of **Greedy Search**, **Constraint-based Search**, and **Stealth-aware Pathfinding**.
* Decisions are based on **distance, missile range, presence of spies, and enemy defenses**.
* The project allows simulation and analysis of various missile attack strategies.

## 📄 License

This project is licensed under the MIT License. See the `LICENSE` file for details.
