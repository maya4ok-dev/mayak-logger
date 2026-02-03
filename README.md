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

For now, default sinks aren't implemented. They'll append in future versions.

```cpp
// 1. Include the main header.
#include <mayak/logger.hpp>
#include <iostream>
#include <string>

// 2. Make aliases for types to simplify the code so you don't have to type long namespaces.
using Level = mayak::logger::core::Level;
using Sink = mayak::logger::core::Sink;
using flush = mayak::logger::core::flush;

// 3. Define a sink, it'll send messages to the output.
struct ConsoleSink : Sink {
    // This method sends the message into the IO buffer.
    void log(const std::string& msg) override {
        std::cout << msg;
    }
    // This method forces IO to show the buffered message.
    void flush() override {
        std::cout << std::endl;
    }
};

int main() {
    // 4. Create a logger
    mayak::logger::core::Logger ml;

    // 5. Add a sink
    ml.addSink<ConsoleSink>();

    // Set a log level if needed
    // Default level is INFO with priotiry 40
    // Level debug("DEBUG", 10);
    // ml.setLevel(debug);

    // 6. Done! Now log messages using DSL
    ml << "Hello, Project Mayak!" << flush;
    ml << "Another message" << flush;

    return 0;
}
```
