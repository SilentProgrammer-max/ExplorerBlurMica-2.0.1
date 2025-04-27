#pragma once
// Exclude rarely used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <string>
#include <atomic>
#include <functional>
#include <stdexcept>
#include <array>
#include <memory>
#include <mutex>

#include <dwmapi.h>
#include <CommCtrl.h>
#include <shlwapi.h>
#include <Uxtheme.h>
#pragma comment(lib, "dwmapi.lib")
#pragma comment(lib, "Comctl32.lib")
#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "uxtheme.lib")
