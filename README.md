![observer\_header](https://github.com/user-attachments/assets/4c9970c9-6374-44e9-a40a-0a5bfc5a0b43)

# 🧩 Observer Library (MISRA-C / Safety-Critical)

A **deterministic**, **zero-dynamic-memory**, and **MISRA-C:2012 compliant** implementation of the **Observer Pattern** written in pure C — designed for **embedded**, **real-time**, and **safety-critical** applications (ISO 26262 / IEC 61508 / DO-178C).

---

![GitHub License](https://img.shields.io/github/license/niwciu/OBSERVER)
![GitHub top language](https://img.shields.io/github/languages/top/niwciu/OBSERVER)
![GitHub Release](https://img.shields.io/github/v/release/niwciu/OBSERVER)
![GitHub branch check runs](https://img.shields.io/github/check-runs/niwciu/OBSERVER/main)
![CI Pipeline](https://github.com/niwciu/OBSERVER/actions/workflows/CI_Pipeline.yml/badge.svg)
![MISRA](https://img.shields.io/badge/MISRA-C%3A2012-blue)

<b><a href='https://niwciu.github.io/OBSERVER/reports/gcovr.html'>Library GCOVR Report</a></b> <br>
<b><a href='https://niwciu.github.io/OBSERVER/reports/code_complexity_report.html'>Library Code Complexity Report</a></b><br>
<b><a href='https://niwciu.github.io/OBSERVER/doxygen/observer_lib_doc/html/index.html'>Library Code Complexity Report</a></b>

---

## 🚀 Key Features

* ✅ **MISRA-C:2012** compliant (checked via *Cppcheck* and *PC-lint*)
* ✅ **Zero dynamic memory** – uses only static tables
* ✅ **Deterministic execution** – bounded by compile-time table size
* ✅ **Thread-safe when externally synchronized**
* ✅ **ASIL / DAL / SIL ready** — structured for safety-certified projects
* ✅ **Defensive argument validation** in all public APIs
* ✅ **100 % unit-test coverage** (Unity + gcovr)

---

## 📁 Directory Layout

```
/observer_lib/
├── examples/
│   ├── basic_observer/                # Basic no-arg callback
│   ├── state_observer/                # Uses event_state_e argument
│   └── observer_u8/                   # Uses uint8_t argument
├── hw/
├── lib/
│   └── observer/
│        ├── observer.c                # Core implementation
│        ├── observer.h                # Public API
│        └── observer_public_types.h   # Enums & callback typedefs
├── test/
│   ├── observer/                      # Unit tests (Unity)
│   ├── unity/                         # Test framework
│   └── reports/                       # Coverage & complexity outputs
├── LICENSE
└── README.md
```

> All examples are **deterministic**, **static**, and self-contained.

---
## 🧩 Observer Library Examples

This folder contains practical examples demonstrating how to integrate the **Observer library** into embedded-style applications using **static memory tables**.
| Example         | Description                                                            | Folder                                     |
| --------------- | ---------------------------------------------------------------------- | ------------------------------------------ |
| Basic Observer  | Simple callback example using pushbutton, LED and LCD mocks            | [basic_observer_example](https://github.com/niwciu/OBSERVER/tree/main/examples/basic_observer)   |
| State Observer  | Observer with `event_state_e` argument demonstrating ENTER/EXIT states | [state_observer_example](https://github.com/niwciu/OBSERVER/tree/main/examples/state_observer)   |
| Sensor Observer | Observer with `uint8_t` argument demonstrating periodic sensor updates | [observer_notify_u8_arg_example](https://github.com/niwciu/OBSERVER/tree/main/examples/observer_u8) |

> Each folder contains a complete `src/` with all C/H files and a common `README.md` with detailed instructions, expected output, and safety notes.  
> For full information on building, running, and understanding the examples, see the [Examples Details README](examples/README.md).

---

## ⚙️ Public API Reference

### 1️⃣ Callbacks Without Arguments

#### `subscribe()`

```c
subscr_status_e subscribe(observer_cb_t *subscription_table,
                          observer_cb_t cb_2_register,
                          uint8_t subscription_table_size);
```

Registers a callback function.
Returns one of:

* `OBSERVER_OK` — callback registered or already present
* `OBSERVER_INVALID_ARGUMENT_ERROR` — invalid pointer or zero size
* `OBSERVER_TABLE_FULL_ERROR` — no free slot available

---

#### `unsubscribe()`

```c
subscr_status_e unsubscribe(observer_cb_t *subscription_table,
                            observer_cb_t cb_2_register,
                            uint8_t subscription_table_size);
```

Removes a callback and compacts the table.
Returns:

* `OBSERVER_OK`
* `OBSERVER_TABLE_EMPTY_ERROR`
* `OBSERVER_INVALID_ARGUMENT_ERROR`

---

#### `notify()`

```c
subscr_status_e notify(observer_cb_t *subscription_table,
                       uint8_t subscription_table_size);
```

Invokes all registered callbacks sequentially.
Returns:

* `OBSERVER_OK` — at least one callback executed
* `OBSERVER_TABLE_EMPTY_ERROR` — no callbacks registered
* `OBSERVER_INVALID_ARGUMENT_ERROR`

---

### 2️⃣ Callbacks with `event_state_e` Argument

#### `subscribe_state_change()`

```c
subscr_status_e subscribe_state_change(observer_cb_state_t *subscription_table,
                                       observer_cb_state_t cb_2_register,
                                       uint8_t subscription_table_size);
```

#### `unsubscribe_state_change()`

```c
subscr_status_e unsubscribe_state_change(observer_cb_state_t *subscription_table,
                                         observer_cb_state_t cb_2_register,
                                         uint8_t subscription_table_size);
```

#### `notify_state_change()`

```c
subscr_status_e notify_state_change(observer_cb_state_t *subscription_table,
                                    uint8_t subscription_table_size,
                                    event_state_e state);
```

---

### 3️⃣ Callbacks with `uint8_t` Argument

#### `subscribe_u8()`

```c
subscr_status_e subscribe_u8(observer_cb_u8_arg_t *subscription_table,
                             observer_cb_u8_arg_t cb_2_register,
                             uint8_t subscription_table_size);
```

#### `unsubscribe_u8()`

```c
subscr_status_e unsubscribe_u8(observer_cb_u8_arg_t *subscription_table,
                               observer_cb_u8_arg_t cb_2_register,
                               uint8_t subscription_table_size);
```

#### `notify_u8()`

```c
subscr_status_e notify_u8(observer_cb_u8_arg_t *subscription_table,
                          uint8_t subscription_table_size,
                          uint8_t data);
```

---

### 🧩 Return Codes (`subscr_status_e`)

| Code                              | Meaning                         |
| --------------------------------- | ------------------------------- |
| `OBSERVER_OK`                     | Operation successful            |
| `OBSERVER_INVALID_ARGUMENT_ERROR` | Invalid pointer or table size   |
| `OBSERVER_TABLE_FULL_ERROR`       | No free slot available          |
| `OBSERVER_TABLE_EMPTY_ERROR`      | Table contains no valid entries |

---

## ⚙️ Running Library Targets

To build and run any of the predefined targets, follow this sequence of commands from the main project library location:

```bash
# Navigate to the observer test folder
cd test/observer

# Configure the build with CMake
# Use "Unix Makefiles" or "Ninja" generator
cmake -S ./ -B out -G "Unix Makefiles"
# cmake -S ./ -B out -G "Ninja"

# Enter the output folder
cd out

# Build the library targets
make all        # or use: ninja


```
>This sequence ensures the library and example targets are properly compiled and ready for execution.

After building the library, you can run any of the predefined targets, such as:


### 🧪 Run Unit Tests

```bash
make run
```

---

### 🔍 Run Static Analysis

```bash
make cppcheck
```

---

### 📈 Run Cyclomatic Complexity check

```bash
make ccm
```

---

### 📊 Run Code Coverage check

```bash
make ccc
```

### 📈 Generate Cyclomatic Complexity report

```bash
make ccm
```

---

### 📊 Genearte Code Coverage report

```bash
make ccc
```

### ✨Format lib src with predefined library rules

```bash
make format
```

---

### ✨ Format lib test code with predefined library rules

```bash
make format_test
```

---

## 🧰 Safety and Compliance Summary

* ✅ **Static memory only** — no heap or dynamic allocation
* ✅ **Deterministic** — execution bounded by table size
* ✅ **Input validation** — every function checks arguments
* ✅ **Thread safety** — achieved externally if needed
* ✅ **MISRA-C:2012** compliant and statically analyzed
* ✅ **Portable** across GCC, IAR, ARMCC, GHS, etc.

---

## ⚠️ Safety-Critical Compliance Matrix

| ID   | Requirement                  |   Status  |
| ---- | ---------------------------- | :-------: |
| SC-1 | No dynamic memory usage      |     ✅     |
| SC-2 | Deterministic control flow   |     ✅     |
| SC-3 | Input validation on all APIs |     ✅     |
| SC-4 | MISRA-C:2012 compliance      |     ✅     |
| SC-5 | Unit test coverage ≥ 90 %    | ✅ (100 %) |
| SC-6 | Thread safety documented     |     ✅     |
| SC-7 | Static analysis clean        |     ✅     |

---


## 🧩 Integration Examples

The library includes **ready-to-run integration examples** located in the [`examples/`](examples/) directory. These examples demonstrate:

* How to integrate the **Observer library** in an application.
* Realistic usage patterns with **mocked embedded hardware modules** (e.g., pushbuttons, LEDs, sensors).
* Deterministic behavior using **static observer tables**.

> 💡 Each example contains **block diagrams** and **commented code** explaining the module interactions, subscription flow, and event notifications.

For detailed guidance and diagrams, see the [`examples/README.md`](examples/README.md) file.


---

### 🧠 Notes

* **Publisher** owns the static subscription table.  
* **Subscribers** register their callbacks using the publisher’s API.  
* All operations are **deterministic** — no dynamic allocation or recursion.  
* Fully compliant with **MISRA-C** and **safety-critical** software design principles.  

> ✅ Clean modular separation and static memory usage make this design ideal for real-time and safety-critical embedded systems.

---

### 🧩 Practical Examples in `/examples/`

For more realistic use cases — including **mocked hardware modules** such as pushbuttons, LEDs, and sensors — check the [`examples/`](examples/) directory.  

These examples illustrate:  

* Publisher/Subscriber interaction using **hardware abstraction layer (HAL) mocks**.  
* Deterministic execution under **embedded-like constraints**.  
* Clear modular separation, suitable for **unit testing** and **safety certification**.

> 💡 Each example is fully self-contained and demonstrates **real embedded-like execution flow** using the same static Observer core.  

---

## 📜 License

Released under the **MIT License** — see [`LICENSE`](LICENSE).
© 2025 [niwciu](mailto:niwciu@gmail.com)

</br>

---

<div align="center">

![myEmbeddedWayBannerWhiteSmaller](https://github.com/user-attachments/assets/f4825882-e285-4e02-a75c-68fc86ff5716)

</div>

---