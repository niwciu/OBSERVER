# Observer Library Examples Details

This document provides detailed information for each example in the Observer Library. Each folder contains all source (`.c`) and header (`.h`) files, and the examples are MISRA-C / ISO 26262 compliant, using deterministic, static memory.

---

## 1️⃣ Basic Observer Example

* **Folder:** `examples/example_basic/`

* **Purpose:** Demonstrates multiple observers reacting to a pushbutton event (mock LED and LCD).

* **Files:**

  * `main.c` - Entry point, initializes modules, runs main loop
  * `mock_LED.c/h` - Toggles LED state on pushbutton event
  * `mock_LCD.c/h` - Prints message on pushbutton event
  * `mock_pushbutton.c/h` - Simulates pushbutton input using terminal

* **Detailed Description:**
  This example shows a simple observer pattern implementation in C. When the user presses the 'c' key in the terminal, the mock pushbutton module detects it and notifies all registered observers. The LCD observer prints a message to the terminal, and the LED observer toggles its state, also printing its state change. The system uses static subscription tables to maintain determinism and MISRA-C compliance.

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
  [MOCK_LED]: LED IS OFF
  ```

* **Safety Notes:**

  * Deterministic, static memory only
  * Observers independent
  * Terminal I/O uses POSIX calls (non-MISRA)

---

## 2️⃣ State Observer Example

* **Folder:** `examples/example_state/`

* **Purpose:** Demonstrates `observer_enter_exit` API with a mock state machine alternating between ENTER and EXIT states.

* **Files:**

  * `main_state_example.c` - Entry point, initializes state machine and display
  * `mock_state_machine.c/h` - Toggles state and notifies observers
  * `mock_display.c/h` - Prints messages on state transitions

* **Detailed Description:**
  This example demonstrates a state-change observer. The mock state machine toggles between `ENTER` and `EXIT` states at a fixed interval (1 second). Each time the state changes, all observers subscribed to state events are notified. The display observer prints a message indicating whether the state was entered or exited. This demonstrates deterministic state notifications, static memory usage, and safe separation of observer responsibilities.

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
  [DISPLAY] State entered
  [DISPLAY] State exited
  [DISPLAY] State entered
  ```

* **Safety Notes:**

  * Deterministic toggling between states
  * Observers use static subscription tables
  * Observer notification is thread-safe if externally protected

---

## 3️⃣ Observer with u8 Notify arg Example

* **Folder:** `examples/example_u8_arg/`

* **Purpose:** Demonstrates `observer_u8` API with periodic mock sensor updates.

* **Files:**

  * `main_sensor_example.c` - Entry point, initializes sensor and logger
  * `mock_sensor.c/h` - Generates periodic sensor values and notifies observers
  * `mock_logger.c/h` - Logs sensor value to stdout

* **Detailed Description:**
  This example shows the observer pattern with `uint8_t` arguments. The mock sensor generates incrementing sensor values at a fixed interval (0.5 seconds). Each new sensor value is sent to all subscribed observers using the `observer_u8` API. The logger observer prints the sensor value to the terminal. The design ensures deterministic updates, static memory usage, and safe observer execution.

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
  [LOGGER] Sensor value = 1
  [LOGGER] Sensor value = 2
  [LOGGER] Sensor value = 3
  ```

* **Safety Notes:**

  * Static memory only
  * Deterministic updates
  * Observer callbacks independent
