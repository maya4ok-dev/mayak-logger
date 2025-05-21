# 📓 MayakLogger

**MayakLogger** is a lightweight, **header-only** logging library for C++ by [Maya4ok](https://github.com/maya4ok-dev). Minimal dependencies, maximum usefulness. Colored output, log levels, support for `__FILE__` and `__LINE__`, and most importantly — **thread-safe**. Perfect for everything from pet projects to serious tools.

---

## ⚡ Features

* ✅ Header-only — just drop the `.hpp` in your project and go
* 🌈 Colored console output (ANSI escape codes)
* 🧵 Thread-safe using `std::mutex`
* 🧭 Log levels support: TRACE → FATAL
* 📍 Optional file and line info for debugging
* 💬 Convenient `MAYAK_LOG_XXX()` macros

---

## 🚀 Quick Start

```cpp
#include "mayak_logger.hpp"

int main() {
    MAYAK_LOG_INFO("Let's go!");
    MAYAK_LOG_WARN("Something's off...");
    MAYAK_LOG_ERROR("We messed up.");
    return 0;
}
```

---

## 🔧 Configuration

```cpp
// Set minimum log level (default is INFO)
mayak::logger::setLogLevel(mayak::logger::DEBUG);

// Enable/disable file and line info output
mayak::logger::setAdditionalInfo(true);
```

---

## 🧪 Log Levels

| Level | Macro                  | Terminal Color |
| ----- | ---------------------- | -------------- |
| TRACE | `MAYAK_LOG_TRACE(msg)` | Gray           |
| DEBUG | `MAYAK_LOG_DEBUG(msg)` | Cyan           |
| INFO  | `MAYAK_LOG_INFO(msg)`  | White          |
| WARN  | `MAYAK_LOG_WARN(msg)`  | Yellow         |
| ERROR | `MAYAK_LOG_ERROR(msg)` | Red            |
| FATAL | `MAYAK_LOG_FATAL(msg)` | Red background |

---

## 🛡️ Thread Safety

All output is protected by `std::mutex`, so it’s safe to log from multiple threads simultaneously.

---

## 📂 Structure

Everything lives in the `mayak::logger` namespace. Use macros like `MAYAK_LOG_INFO()` for easy logging.

---

## 📜 License

MIT — do whatever you want, but please keep a link to the original if you don’t mind.

---

## ❤️ Made with love

This logger is part of the MayakUI ecosystem but feel free to use it anywhere.
Write clean, log happy.
Made by Maya4ok — for the people.