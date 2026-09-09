# mayak-logger
An extremely flexible C++ logging framework.

## Features

* **Separated core and frontend** - the core contains no sinks, formatting or IO logic.
    You can build your own logger implementation on top of it.
* **Fully modular** - sinks, formatters and even loggers are independent and can be compiled out.
* **Clean understandable syntax** - simple to use and extend, see example below.

## Philosophy

There are many logging libraries, but most of them are either inflexible or very hard to extend.

For example, in spdlog logging levels can only be renamed - you can't actually add new ones.
Also, spdlog doesn't allow registering custom types and passing them directly.

Mayak Logger is designed to solve all of these problems and make logging simpler and more extensible.

## Example

```cpp
// 1. Include the main header.
#include <mayak/logger.hpp>

// 2. Make aliases for types to simplify the code so you don't have to type long namespaces.
using Level = mayak::logger::core::Level;
using mayak::logger::core::flush;

int main() {
    // 3. Create a logger
    mayak::logger::core::Logger ml;

    // 4. Add a sink
    ml.addSink<mayak::logger::ConsoleSink>();

    // Set a log level if needed
    // Default level is INFO with priority 40
    // Level debug("DEBUG", 10);
    // ml.setLevel(debug);

    // 5. Done! Now log messages using DSL
    ml << "Hello, Project Mayak!" << flush;
    ml << "Number: " << (123 + 456) << flush;

    return 0;
}
```
