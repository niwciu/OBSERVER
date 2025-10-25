![observer\_header](https://github.com/user-attachments/assets/4c9970c9-6374-44e9-a40a-0a5bfc5a0b43)

# 🧩 Observer Library (MISRA-C / Safety-Critical)

A **deterministic**, **zero-dynamic-memory**, and **MISRA-C:2012 compliant** implementation of the **Observer Pattern** written in pure C — designed for **embedded**, **real-time**, and **safety-critical** applications (ISO 26262 / IEC 61508 / DO-178C).

---

![GitHub License](https://img.shields.io/github/license/niwciu/OBSERVER_LIB)
![GitHub top language](https://img.shields.io/github/languages/top/niwciu/OBSERVER_LIB)
![GitHub Release](https://img.shields.io/github/v/release/niwciu/OBSERVER_LIB)
![GitHub branch check runs](https://img.shields.io/github/check-runs/niwciu/OBSERVER_LIB/main)
![CI Pipeline](https://github.com/niwciu/OBSERVER_LIB/actions/workflows/CI_Pipeline.yml/badge.svg)
![MISRA](https://img.shields.io/badge/MISRA-C%3A2012-blue)

<b><a href='https://niwciu.github.io/OBSERVER_LIB/reports/gcovr.html'>Library GCOVR Report</a></b> <br>
<b><a href='https://niwciu.github.io/OBSERVER_LIB/reports/code_complexity_report.html'>Library Code Complexity Report</a></b>

---

## 🚀 Features

* ✅ Fully **MISRA-C:2012** compliant (verified with Cppcheck & PC-lint)
* ✅ **No dynamic memory allocation** (uses static tables only)
* ✅ **Deterministic and bounded execution time**
* ✅ **Safety-critical ready** (ASIL / DAL / SIL compliant design principles)
* ✅ **Clean error handling** and defensive argument checking
* ✅ **Thread-safe if protected by caller** (no internal synchronization)
* ✅ **100% unit test coverage** verified with Unity and gcovr

---

## 📁 File Structure

```
/observer_lib/
├── examples/
│   ├── basic_observer/                 # Simple callback example
│   ├── state_observer/                 # State-change observer example
│   └── observeer_u8/                   # Observer with uint8_t notify argument example
├── hw/
├── lib/
│   └── observer/                
│        ├── observer.c                 # Core implementation (MISRA-C compliant)
│        ├── observer.h                 # Public API header
│        └── observer_public_types.h    # Public enums and callback type definitions
├── test/
│   ├── observer/                       # library Unit tests (Unity)
│   ├── unity/                          # Unit test framework
│   └── reports/                        # Coverage and complexity reports
└── LICENSE                             # Library License
└── README.md                           # Library documentation
```

> Each example is self-contained with static memory and deterministic execution.

---

## 📚 Examples Overview

| Example         | Description                                                            | Folder                                     |
| --------------- | ---------------------------------------------------------------------- | ------------------------------------------ |
| Basic Observer  | Simple callback example using pushbutton, LED and LCD mocks            | [basic_observer_example](examples/basic_observer/)   |
| State Observer  | Observer with `event_state_e` argument demonstrating ENTER/EXIT states | [state_observer_example](examples/state_observer/)   |
| Sensor Observer | Observer with `uint8_t` argument demonstrating periodic sensor updates | [observer_notify_u8_arg_example](examples/observer_u8/) |

> Each folder contains a complete `src/` with all C/H files and a common `README.md` with detailed instructions, expected output, and safety notes.  
> For full information on building, running, and understanding the examples, see the [Examples Details README](examples/README.md).



---

## ⚙️ API Reference

Observer pattern provides deterministic subscription/notification functions:

### `subscribe`

```c
subscr_status_e subscribe(observer_cb_t *subscription_table,
                          observer_cb_t cb_2_register,
                          uint8_t subscription_table_size);
```

Registers a callback (no arguments).

Returns one of:

* `CALLBACK_SUBSCR_OK` – successfully registered
* `CALLBACK_ERROR_INVALID_ARGUMENT` – invalid parameters (NULL or size = 0)
* `CALLBACK_ERROR_TABLE_FULL` – no free slot available

---

### `unsubscribe`

```c
void unsubscribe(observer_cb_t *subscription_table,
                 observer_cb_t cb_2_register,
                 uint8_t subscription_table_size);
```

Removes a callback from the table and shifts remaining entries.

---

### `notify`

```c
void notify(observer_cb_t *subscription_table,
            uint8_t subscription_table_size);
```

Invokes all registered callbacks in order.

---

### Extended Variants

Each API has equivalents for callbacks with arguments:

* `subscribe_enter_exit(...)` / `unsubscribe_enter_exit(...)` / `notify_enter_exit(...)` — for `event_state_e` arguments.
* `subscribe_u8(...)` / `unsubscribe_u8(...)` / `notify_u8(...)` — for `uint8_t` arguments.

> All APIs are **MISRA-C compliant**, deterministic, and use **static memory tables only**.

---

## ✅ Running Unit Tests

```bash
cd test/observer
cmake -S ./ -B out -G "Unix Makefiles"
cd out
make run
```
---

## 🛠️ Run Cppcheck

```bash
cd test/observer
cmake -S ./ -B out -G "Unix Makefiles"
cd out
make cppcheck
```
---

## 📈 Run Cyclomatic Complexity (CCM/Lizard)

```bash
cd test/observer
cmake -S ./ -B out -G "Unix Makefiles"
cd out
make ccm
```
---

## 📝 Generate CCM HTML Report

```bash
cd test/observer
cmake -S ./ -B out -G "Unix Makefiles"
cd out
make ccmr
```
---

## 📊 Run Code Coverage (gcovr)

```bash
cd test/observer
cmake -S ./ -B out -G "Unix Makefiles"
cd out
make ccc
```
---

## 📝 Generate Code Coverage HTML

```bash
cd test/observer
cmake -S ./ -B out -G "Unix Makefiles"
cd out
make ccmr
```
---

## 🧰 Safety / Compliance Notes

* **Zero dynamic allocation** — static tables only
* **Deterministic** — all loops bounded by table size
* **MISRA-C:2012 compliant** — verified by static analysis tools
* **Portable** — compatible with any embedded target (GCC, IAR, GHS, ARMCC)
* **Thread-safe if protected by caller**

---

## ⚠️ Safety-Critical Compliance Checklist

| Requirement | Description                                | Status   |
| ----------- | ------------------------------------------ | -------- |
| SC-1        | No dynamic memory                          | ✅        |
| SC-2        | Deterministic control flow                 | ✅        |
| SC-3        | Input validation on all public functions   | ✅        |
| SC-4        | MISRA-C:2012 compliance verified           | ✅        |
| SC-5        | Full unit test coverage (≥ 90%)            | ✅ (100%) |
| SC-6        | Thread safety documented                   | ✅        |
| SC-7        | Static analysis clean (Cppcheck / PC-lint) | ✅        |

---

## 🧩 Integration

Add `observer.c`, `observer.h`, and `observer_public_types.h` to your project and include:

```c
#include "observer.h"
```

Provide static arrays to hold callback pointers, e.g.:

```c
static observer_cb_t my_table[4U] = { NULL };
```

---

## 📜 License

MIT License — see `LICENSE` file.

© 2025 [niwciu](mailto:niwciu@gmail.com)

<br>
<div align="center">

---

![myEmbeddedWayBanerWhiteSmaller](https://github.com/user-attachments/assets/f4825882-e285-4e02-a75c-68fc86ff5716)

---

</div>
