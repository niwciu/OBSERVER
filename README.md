![observer\_header](https://github.com)

# 🧩 Observer Library (MISRA-C / Safety-Critical)

A **deterministic**, **zero-dynamic-memory**, and **MISRA-C:2012 compliant** implementation of the **Observer Pattern** written in pure C — designed for **embedded**, **real-time**, and **safety-critical** applications (ISO 26262 / IEC 61508 / DO-178C).

---

![GitHub License](https://img.shields.io/github/license/niwciu/OBSERVER_LIB)
![GitHub top language](https://img.shields.io/github/languages/top/niwciu/OBSERVER_LIB)
![GitHub Release](https://img.shields.io/github/v/release/niwciu/OBSERVER_LIB)
![GitHub branch check runs](https://img.shields.io/github/check-runs/niwciu/OBSERVER_LIB/main)
![CI Pipeline](https://github.com/niwciu/OBSERVER_LIB/actions/workflows/CI_Pipeline.yml/badge.svg)
![MISRA](https://img.shields.io/badge/MISRA-C%3A2012-blue)

<b><a href='https://niwciu.github.io/OBSERVER_LIB/reports/gcovr.html'>Library GCOVR Report</a></b> <b><a href='https://niwciu.github.io/OBSERVER_LIB/reports/code_complexity_report.html'>Library Code Complexity Report</a></b>

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
│
├── .github/
│   └── workflows/
│       ├── CI_Pipeline.yml             # Continuous integration workflow
│       └── Deploy.yml                  # GitHub Pages deployment
├── doc/
├── examples/
│   ├── example_basic/                  # Simple callback example
│   ├── example_state/                  # State-change observer example
│   └── example_u8_arg/                 # Observer with uint8_t argument
│
├── hw/
├── lib/
│   └── observer/                
│        ├── observer.c                 # Core implementation (MISRA-C compliant)
│        ├── observer.h                 # Public API header
│        └── observer_public_types.h    # Public enums and callback type definitions
│
├── test/
│   ├── observer/                       # library Unit tests (Unity)
│   ├── unity/                          # Unit test framework
│   └── reports/                        # Coverage and complexity reports
│
└── LICENSE                             # Library License
└── README.md                           # Library documentation
```

---

## ⚙️ API Reference

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

---

## 🧠 Example 1: Basic Observer

```c
#include "observer.h"
#include <stdio.h>

#define MAX_OBSERVERS 4U

static observer_cb_t system_event_list[MAX_OBSERVERS] = { NULL };

static void on_system_ready(void)
{
    printf("System is ready!\n");
}

int main(void)
{
    (void)subscribe(system_event_list, on_system_ready, MAX_OBSERVERS);
    notify(system_event_list, MAX_OBSERVERS);
    return 0;
}
```

**Output:**

```
System is ready!
```

---

## 🧩 Example 2: Observer with `event_state_e` Argument

```c
#include "observer.h"
#include <stdio.h>

#define MAX_OBSERVERS 4U

static observer_cb_arg_t state_observers[MAX_OBSERVERS] = { NULL };

static void on_state_change(event_state_e state)
{
    if (state == EVENT_STATE_ENTER)
    {
        printf("Entering state\n");
    }
    else
    {
        printf("Exiting state\n");
    }
}

int main(void)
{
    (void)subscribe_enter_exit(state_observers, on_state_change, MAX_OBSERVERS);
    notify_enter_exit(state_observers, MAX_OBSERVERS, EVENT_STATE_ENTER);
    notify_enter_exit(state_observers, MAX_OBSERVERS, EVENT_STATE_EXIT);
    return 0;
}
```

**Output:**

```
Entering state
Exiting state
```

---

## 🔢 Example 3: Observer with `uint8_t` Argument

```c
#include "observer.h"
#include <stdio.h>

#define MAX_OBSERVERS 4U
static observer_cb_u8_arg_t sensor_observers[MAX_OBSERVERS] = { NULL };

static void on_sensor_update(uint8_t value)
{
    printf("Sensor value: %u\n", value);
}

int main(void)
{
    (void)subscribe_u8(sensor_observers, on_sensor_update, MAX_OBSERVERS);
    notify_u8(sensor_observers, MAX_OBSERVERS, 42U);
    notify_u8(sensor_observers, MAX_OBSERVERS, 99U);
    return 0;
}
```

**Output:**

```
Sensor value: 42
Sensor value: 99
```

---

## 🧪 Running Unit Tests

```bash
cd test/observer
cmake -S ./ -B out -G "Unix Makefiles"
cd out
make run
```

Generates:

* `gcovr.html` → Code coverage report
* `code_complexity_report.html` → Cyclomatic complexity

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

Licensed under the MIT License — see `LICENSE` file for details.

© 2025 [niwciu](mailto:niwciu@gmail.com)

<br>
<div align="center">

---

![myEmbeddedWayBanerWhiteSmaller](https://github.com/user-attachments/assets/f4825882-e285-4e02-a75c-68fc86ff5716)

---

</div>
