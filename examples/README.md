# Observer Library Examples Details

This document provides detailed information for each example in the Observer Library. Each folder contains all source (`.c`) and header (`.h`) files, and the examples are MISRA-C / ISO 26262 compliant, using deterministic, static memory.

---

## 1️⃣ Basic Observer Example

* **Folder:** `examples/example_basic/`

* **Purpose:** Demonstrates multiple observers reacting to a pushbutton event in a deterministic, MISRA-C compliant way.

* **Files:**

  | File                  | Description                                                                           |
  | --------------------- | ------------------------------------------------------------------------------------- |
  | `main.c`              | Entry point. Initializes modules, sets up observer subscriptions, and runs main loop. |
  | `mock_LED.c/h`        | Mock LED observer that toggles its state on pushbutton events.                        |
  | `mock_LCD.c/h`        | Mock LCD observer that prints messages to terminal on pushbutton events.              |
  | `mock_pushbutton.c/h` | Simulates pushbutton input via terminal keyboard ('c' key) and notifies observers.    |

* **Detailed Description:**
  This example demonstrates a **basic observer pattern** in C. The system consists of a mock pushbutton event source and two observers: a mock LED and a mock LCD display. Each press of the 'c' key triggers a notification event:

  1. The **pushbutton module** detects the key press and calls `notify()` only on **subscribed observers**.
  2. The **LCD observer** prints a message indicating the key press.
  3. The **LED observer** toggles its state and prints the new state.

  Deterministic **static subscription tables** are used to avoid dynamic memory allocation. Observer callbacks are independent. Terminal I/O uses POSIX calls only for simulation.

* **Build & Run:**

  ```bash
  cd examples/example_basic
  cmake -S ./ -B out -G "Unix Makefiles"   # or cmake -S ./ -B out -G "Ninja"
  cd out
  make all        # or ninja
  make run        # or ninja run
  ```

* **Expected Output:**

  ```
  [MOCK_LCD]: Key 'C' has been pressed
  [MOCK_LED]: LED IS ON
  [MOCK_LCD]: Key 'C' has been pressed
  [MOCK_LED]: LED IS OFF
  ```

* **Safety Notes:**

  * Deterministic execution using **static memory**.
  * Observer callbacks are independent.
  * Terminal I/O uses POSIX calls (non-MISRA) for simulation only.

* **Relation Diagrams for Initialization and Main Loop Phases:**

<table>
<tr>
<td><center>

<b>Initialization Phase</b>

```mermaid
flowchart TD
    A[Pushbutton Module / Publisher]
    B[LED Observer]
    C[LCD Observer]

    B -->|Subscribe to pushbutton events| A
    C -->|Subscribe to pushbutton events| A

    style A fill:#444444,stroke:#ffffff,stroke-width:2px,color:#ffffff
    style B fill:#666666,stroke:#ffffff,stroke-width:1px,color:#ffffff
    style C fill:#666666,stroke:#ffffff,stroke-width:1px,color:#ffffff
```

</center></td>
<td><center>

<b>Main Loop Phase</b>

```mermaid
flowchart TD
    D[update_mock_pushbutton]
    A[Pushbutton Module / Publisher]
    B[LED Observer]
    C[LCD Observer]

    D -->|Detect C key press| A
    A -->|Notify only subscribed observers| B
    A -->|Notify only subscribed observers| C

    style A fill:#444444,stroke:#ffffff,stroke-width:2px,color:#ffffff
    style B fill:#666666,stroke:#ffffff,stroke-width:1px,color:#ffffff
    style C fill:#666666,stroke:#ffffff,stroke-width:1px,color:#ffffff
    style D fill:#FFA500,stroke:#ffffff,stroke-width:1px,color:#000000
```

</center></td> </tr> </table>

* **Explanation of Flow:**

  1. `main.c` initializes all modules (`init_mock_modules()`) and sets subscriptions (`set_all_subscriptions()`) in the **Initialization Phase**.
  2. Main loop (`for(;;)`) continuously calls `update_mock_pushbutton()` in the **Main Loop Phase**.
  3. When the user presses C key, pushbutton module invokes `notify()` **only for subscribed observers**.
  4. LED and LCD react independently.

---

## 2️⃣ State Observer Example

* **Folder:** `examples/example_state/`

* **Purpose:** Demonstrates `observer_enter_exit` API with a mock state machine alternating between ENTER and EXIT states.

* **Files:**

  | File                     | Description                                        |
  | ------------------------ | -------------------------------------------------- |
  | `main_state_example.c`   | Entry point, initializes state machine and display |
  | `mock_state_machine.c/h` | Toggles state and notifies observers               |
  | `mock_display.c/h`       | Prints messages on state transitions               |

* **Detailed Description:**
  This example demonstrates a state-change observer. The mock state machine toggles between `ENTER` and `EXIT` states at a fixed interval (1 second). Each time the state changes, all observers subscribed to state events are notified. The display observer prints a message indicating whether the state was entered or exited. Deterministic notifications, static memory usage, and safe observer execution are ensured.

* **Build & Run:**

  ```bash
  cd examples/example_state
  cmake -S ./ -B out -G "Unix Makefiles"   # or cmake -S ./ -B out -G "Ninja"
  cd out
  make all        # or ninja
  make run        # or ninja run
  ```

* **Expected Output:**

  ```
  [DISPLAY]: State ENTER
  [DISPLAY]: State EXIT
  [DISPLAY]: State ENTER
  ```

* **Safety Notes:**

  * Deterministic toggling between states
  * Observers use static subscription tables
  * Observer notification is thread-safe if externally protected

* **Relation Diagrams for Initialization and Main Loop Phases:**

<table>
<tr>
<td><center>

<b>Initialization Phase</b>

```mermaid
flowchart TD
    A[State Machine / Publisher]
    B[Display Observer]

    B -->|Subscribe to state events| A

    style A fill:#444444,stroke:#ffffff,stroke-width:2px,color:#ffffff
    style B fill:#666666,stroke:#ffffff,stroke-width:1px,color:#ffffff
```

</center></td>
<td><center>

<b>Main Loop Phase</b>

```mermaid
flowchart TD
    D[update_mock_state_machine]
    A[State Machine / Publisher]
    B[Display Observer]

    D -->|Toggle state| A
    A -->|Notify subscribed observers| B

    style A fill:#444444,stroke:#ffffff,stroke-width:2px,color:#ffffff
    style B fill:#666666,stroke:#ffffff,stroke-width:1px,color:#ffffff
    style D fill:#FFA500,stroke:#ffffff,stroke-width:1px,color:#000000
```

</center></td> </tr> </table>

---

## 3️⃣ Observer with u8 Notify Arg Example

* **Folder:** `examples/example_u8_arg/`

* **Purpose:** Demonstrates `observer_u8` API with periodic mock sensor updates.

* **Files:**

  | File                    | Description                                             |
  | ----------------------- | ------------------------------------------------------- |
  | `main_sensor_example.c` | Entry point, initializes sensor and logger              |
  | `mock_sensor.c/h`       | Generates periodic sensor values and notifies observers |
  | `mock_logger.c/h`       | Logs sensor value to stdout                             |

* **Detailed Description:**
  This example shows the observer pattern with `uint8_t` arguments. The mock sensor generates incrementing sensor values at a fixed interval (0.5 seconds). Each new sensor value is sent to all subscribed observers using the `observer_u8` API. The logger observer prints the sensor value to the terminal. Deterministic updates, static memory usage, and safe observer execution are ensured.

* **Build & Run:**

  ```bash
  cd examples/example_u8_arg
  cmake -S ./ -B out -G "Unix Makefiles"   # or cmake -S ./ -B out -G "Ninja"
  cd out
  make all        # or ninja
  make run        # or ninja run
  ```

* **Expected Output:**

  ```
  [LOGGER]: Sensor value = 1
  [LOGGER]: Sensor value = 2
  [LOGGER]: Sensor value = 3
  ```

* **Safety Notes:**

  * Static memory only
  * Deterministic updates
  * Observer callbacks independent

* **Relation Diagrams for Initialization and Main Loop Phases:**

<table>
<tr>
<td><center>

<b>Initialization Phase</b>

```mermaid
flowchart TD
    A[Mock Sensor / Publisher]
    B[Logger Observer]

    B -->|Subscribe to sensor updates| A

    style A fill:#444444,stroke:#ffffff,stroke-width:2px,color:#ffffff
    style B fill:#666666,stroke:#ffffff,stroke-width:1px,color:#ffffff
```

</center></td>
<td><center>

<b>Main Loop Phase</b>

```mermaid
flowchart TD
    D[update_mock_sensor]
    A[Mock Sensor / Publisher]
    B[Logger Observer]

    D -->|Increment sensor value| A
    A -->|Notify subscribed observers| B

    style A fill:#444444,stroke:#ffffff,stroke-width:2px,color:#ffffff
    style B fill:#666666,stroke:#ffffff,stroke-width:1px,color:#ffffff
    style D fill:#FFA500,stroke:#ffffff,stroke-width:1px,color:#000000
```

</center></td> </tr> </table>

```}
```
