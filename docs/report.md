# 📑 Final Project Report — Bunker-Buster

## 🔍 Abstract
This project, **Bunker-Buster**, models a strategic missile strike scenario where friendly bases launch different classes of missiles toward enemy cities. The environment is modeled as a weighted graph with constraints such as missile range, stealth degradation, uncontrolled distance, spies, and enemy defenses.  

We design and analyze multiple algorithmic strategies (greedy, constraint-based, stealth-aware, nearest-neighbor). Each algorithm is formally described, implemented in C++17, and experimentally evaluated. The results show trade-offs between efficiency, survivability, and inflicted damage. Scenario 3 (stealth-aware routing) achieves the best balance between realism and effectiveness.

---

## 📝 1. Introduction
Real-world problems often combine **optimization, graph traversal, and uncertainty**. This project represents such a problem: given limited missile resources, how can we maximize enemy damage under stealth and defense constraints?  

The aim is to:
- Explore different algorithmic paradigms,
- Compare their performance and limitations,
- Provide a modular implementation for experimentation.

---

## 🎯 2. Problem Definition

We model the battlefield as a **weighted graph**:

- **Vertices (V):** Cities (either friendly or enemy).
- **Edges (E):** Distances between cities, weight = distance.
- **Missiles (M):** Each missile type has attributes:
  - `range` (max distance),
  - `uncontrolled_range`,
  - `damage`,
  - `stealth`.
- **Spies:** Certain cities reduce stealth of missiles that pass through.
- **Defenses:** Enemy cities may intercept detected missiles.

### Mathematical Model

We model the battlefield as a weighted graph:

- Let **G = (V, E)** be the graph,  
  where **V** = set of cities, and **E** = set of connections (edges).  
- Each missile **m ∈ M** has:
  - Range **r_m** (maximum travel distance),
  - Stealth **s_m**,
  - Damage **d_m**.

---

#### Path Validity
A path from base **v₀** to enemy **v_k** is valid if:

$$
\sum_{i=0}^{k-1} dist(v_i, v_{i+1}) \leq r_m
$$

*(The total traveled distance must be within the missile’s range).*

and

$$
s_m - spies(P) > 0
$$

*(The remaining stealth after passing spy cities must stay positive).*

---

#### Objective
We want to **maximize the total inflicted damage**:

$$
\text{Maximize} \quad \sum_{m \in M} d_m
$$

*(i.e., maximize the sum of all missile damages that successfully reach their targets).*

---

## 🧩 3. Algorithmic Scenarios

### 3.1 Scenario 1 — D-Class Missiles (Greedy)
- **Idea:** Each missile picks the nearest enemy target iteratively.  
- **Pseudo-code:**
```python
function D_Class_Attack(base):
    while missiles available:
        target = nearest_enemy_city(base)
        if path_has_spy(target):
            missile_destroyed
        else:
            inflict_damage(target)
````

* **Complexity:** `O(n log n)` (finding nearest city with priority queue).

---

### 3.2 Scenario 2 — A-Class Missiles (Constraint-based)

* **Idea:** Evaluate paths; abort if too many spies are present.
* **Pseudo-code:**

```python
function A_Class_Attack(base):
    for each enemy in range:
        path = shortest_path(base, enemy)
        if spy_count(path) <= threshold:
            launch missile
```

* **Complexity:** `O(n²)` (shortest paths + spy evaluation).

---

### 3.3 Scenario 3 — B1, B2, C, C1 Missiles (Stealth-aware)

* **Idea:** Assign missiles with range + stealth degradation.
* **Pseudo-code:**

```python
function Stealth_Attack(base):
    for missile in missiles:
        target = enemy_in_range(missile)
        path = choose_path(base, target)
        for city in path:
            if city.has_spy:
                missile.stealth -= 1
        if missile.stealth <= 0:
            destroyed
        else:
            damage(target)
```

* **Complexity:** `O(n²)` per missile (checking spies & ranges).

---

### 3.4 Scenario 4 — Nearest Target Strategy (A/B/C)

* **Idea:** Simple nearest neighbor but with stealth check.
* **Pseudo-code:**

```python
function Nearest_Target(base):
    target = nearest_enemy_within_range(base)
    if path_safe(base, target):
        launch
```

* **Complexity:** `O(n log n)`.

---

## ⚙️ 4. Implementation

### 4.1 Language & Tools

* **C++17** (object-oriented design for performance and modularity).

### 4.2 Project Structure

```plaintext
Bunker-Buster/
│── src/        # Implementation
│── include/    # Header files
│── docs/       # Documentation
│── LICENSE
```

### 4.3 Main Components

* **Graph:** Cities & distances.
* **City:** Properties (type, spies, defenses).
* **Missile:** Encapsulates missile attributes.
* **Simulator:** Executes each scenario.

---

## 🔬 5. Case Study

---

## 📊 6. Complexity & Performance

| Scenario | Time Complexity   | Space Complexity |
| -------- | ----------------- | ---------------- |
| D-Class  | O(n log n)        | O(n)             |
| A-Class  | O(n²)             | O(n)             |
| Stealth  | O(n²) per missile | O(n)             |
| Nearest  | O(n log n)        | O(n)             |

---

## 💡 7. Evaluation Metrics

* **Success Rate (% of missiles hitting target).**
* **Average Damage Inflicted (sum of damage / missiles launched).**
* **Detection Probability (missiles intercepted by spies/defenses).**
* **Computation Time.**

These metrics allow fair comparison between scenarios.

---

## 🔎 8. Discussion & Limitations

* Greedy algorithms are **fast** but often fail in stealth-heavy environments.
* Constraint-based methods improve **safety** but reduce flexibility.
* Stealth-aware algorithms are **realistic** but computationally heavier.
* Our simulation simplifies reality:

  * Spies always detect (no probabilities).
  * Defenses always succeed if stealth=0.
  * No coordinated multi-missile attacks yet.

---

## 🚀 9. Conclusion & Future Work

This project showed the trade-offs between different algorithmic strategies in a constrained graph-based simulation.

**Future improvements:**

* Implement **A\*** or **Dijkstra** for optimal routing.
* Add **probabilistic detection & interception**.
* Design **coordinated multi-missile strategies** with scheduling algorithms.
* Visualize results with a GUI for educational use.

---

## 📚 10. References
- Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C. (2009). *Introduction to Algorithms* (3rd ed.). MIT Press.  
- Grimaldi, R. P. (2004). *Discrete and Combinatorial Mathematics: An Applied Introduction* (5th ed.). Pearson.  
- ChatGPT (2025). *Assistance in report writing and algorithmic explanation*. OpenAI.  


---

## ⚖️ 11. License

This project is licensed under the **MIT License**. See the `LICENSE` file for details.