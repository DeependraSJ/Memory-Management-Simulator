# Memory Management Simulator

## How to Run
1. **Windows:** Double-click `build.bat`, then run `st.exe`.
2. **Linux/Mac:** Run `g++ -std=c++17 -Iinclude src/main.cpp src/memoryManage.cpp src/physicalMemory.cpp src/statistics.cpp src/cache/cache_level.cpp src/virtual_memory/virtual_memory_manager.cpp -o st`, then `./st`.

## Features
- First Fit, Best Fit, Worst Fit Allocators
- Virtual Memory & Paging (FIFO Replacement Policy)
- L1/L2 Cache Simulation
