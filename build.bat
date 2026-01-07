@echo off
echo Building Memory Simulator...

g++ -std=c++17 -Iinclude src/main.cpp src/memoryManage.cpp src/physicalMemory.cpp src/statistics.cpp src/allocator/first_fit.cpp src/allocator/best_fit.cpp src/allocator/worst_fit.cpp src/cache/cache_level.cpp src/virtual_memory/virtual_memory_manager.cpp -o st.exe

if %errorlevel% neq 0 (
    echo [ERROR] Build Failed! Check your code.
    pause
) else (
    echo [SUCCESS] Build Complete! Run st.exe to start.
)