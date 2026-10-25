#pragma once

// Asio is isolated in its own translation unit: <asio.hpp> pulls in <windows.h> on MinGW,
// which conflicts with "import std;" (conflicting language linkage of _mm_* intrinsics).
void runAsioSmokeTest();
