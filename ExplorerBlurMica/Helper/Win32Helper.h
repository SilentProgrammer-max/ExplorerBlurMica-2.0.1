/**
 * FileName: Win32Helper.h
 *
 * Copyright (C) 2022-2024 Ayesha
 *
 * This file is part of MToolBox and ExplorerBlurMica.
 * ExplorerBlurMica is free software: you can redistribute it and/or modify it under the terms of the
 * GNU Lesser General Public License as published by the Free Software Foundation, either version 3
 * of the License, or any later version.
 *
 * ExplorerBlurMica is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License along with this program.
 * If not, see <https://www.gnu.org/licenses/lgpl-3.0.html>.
 */
#pragma once

#include "VersionHelper.h"
#include <inspectable.h>

// This header is used to include COM-related headers.
// It can be placed in the precompiled header.
#include <shellapi.h>
#include <shellscalingapi.h>
#include <shlwapi.h>
#include <shlobj.h>
#include <shcore.h>
#include <unknwn.h>
#include <comdef.h>
#include <wincodec.h>
#include <uianimation.h>
#include <oleacc.h>
#include <taskschd.h>
#include <comutil.h>
#include <pathcch.h>
#include <oleidl.h>
#include <exdisp.h>
#include <exdispid.h>
#include <mshtml.h>
#include <mshtmdid.h>
#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "shcore.lib")
#pragma comment(lib, "oleacc.lib")
#pragma comment(lib, "taskschd.lib")
#pragma comment(lib, "comsuppw.lib")
#pragma comment(lib, "pathcch.lib")

EXTERN_C IMAGE_DOS_HEADER __ImageBase;

namespace RAIIHelper
{
    template <typename TLambda>
    class lambda_call
    {
    public:
        lambda_call(const lambda_call&) = delete;
        lambda_call& operator=(const lambda_call&) = delete;
        lambda_call& operator=(lambda_call&& other) = delete;

        explicit lambda_call(TLambda&& lambda) noexcept
            : m_lambda(std::move(lambda))
        {
            static_assert(std::is_same<decltype(lambda()), void>::value,
                "The lambda for scope_exit must not return a value.");
            static_assert(!std::is_lvalue_reference<TLambda>::value && !std::is_rvalue_reference<TLambda>::value,
                "scope_exit can only be used directly with a lambda function.");
        }

        lambda_call(lambda_call&& other) noexcept
            : m_lambda(std::move(other.m_lambda)), m_call(other.m_call)
        {
            other.m_call = false;
        }

        ~lambda_call() noexcept
        {
            reset();
        }

        // Ensure the scope_exit lambda will not be called
        void release() noexcept
        {
            m_call = false;
        }

        // Immediately execute the scope_exit lambda if it hasn't run yet;
        // ensure it is not called again
        void reset() noexcept
        {
            if (m_call)
            {
                m_call = false;
                m_lambda();
            }
        }

        // Return true if the scope_exit lambda is still pending execution
        [[nodiscard]] explicit operator bool() const noexcept
        {
            return m_call;
        }

    protected:
        TLambda m_lambda;
        bool m_call = true;
    };

    /**
     * Creates an object that executes the given lambda on destruction.
     * Use auto to capture the returned object.
     * Call reset() to execute the lambda early or release() to prevent execution.
     * Exceptions thrown inside the lambda will trigger fast fail.
     * Think of this as a C++ equivalent to finally.
     */
    template <typename TLambda>
    [[nodiscard]] inline auto scope_exit(TLambda&& lambda) noexcept
    {
        return lambda_call<TLambda>(std::forward<TLambda>(lambda));
    }
}

namespace MBox
{
    extern const HMODULE g_user32Module;
    extern const HMODULE g_comctl32Module;

    extern UINT MTBM_ATTACH;
    extern UINT MTBM_DETACH;
    extern const HINSTANCE this_inst;

    namespace Utils
    {
        inline PKUSER_SHARED_DATA get_kernel_shared_info()
        {
            return reinterpret_cast<PKUSER_SHARED_DATA>(0x7FFE0000);
        }

        extern std::string_view get_file_name_ansi(std::string_view path);
        extern HWND GetChildByClass(HWND hwnd, std::wstring_view className);
        extern HWND GetParentByClass(HWND hwnd, std::wstring_view className);
        extern HRESULT get_module_name(HMODULE moduleHandle, LPWSTR moduleName, DWORD size);
        extern HRESULT GetThemeClass(HTHEME hTheme, LPCWSTR pszClassIdList, int cchClass);
        extern HRESULT get_runtime_class_name(::IInspectable* inspectable, LPWSTR className, DWORD size);
        extern void RefreshExplorerTheme();
    }

    template <typename T, bool ignoreNullptr, const void* defaultValue,
              typename get_name_fn_t, get_name_fn_t get_name_fn,
              size_t buffer_size = MAX_PATH + 1>
    class obj_name
    {
    public:
        obj_name(const obj_name&) = delete;
        obj_name& operator=(const obj_name&) = delete;
        obj_name& operator=(obj_name&& other) = delete;

        bool operator==(std::wstring str) const { return !_wcsicmp(m_name, str.c_str()); }
        bool operator==(std::wstring_view str) const { return !_wcsicmp(m_name, str.data()); }
        bool operator==(LPCWSTR str) const { return !_wcsicmp(m_name, str); }

        T operator=(T obj)
        {
            get_name_fn(obj, m_name, buffer_size - 1);
            return obj;
        }

        obj_name()
        {
            if constexpr (ignoreNullptr || defaultValue != nullptr)
            {
                if constexpr (std::is_same<T, std::wstring_view>::value && defaultValue == nullptr)
                    obj_name::operator=(T(L""));
                else
                    obj_name::operator=(T(defaultValue));
            }
        }

        obj_name(T obj) { obj_name::operator=(obj); }

        ~obj_name() = default;

        [[nodiscard]] const wchar_t* c_str() const noexcept { return m_name; }
        [[nodiscard]] std::wstring_view get() const noexcept { return m_name; }
        [[nodiscard]] std::wstring make_wstring() const { return std::wstring(m_name); }

        void* operator new(size_t) = delete;
        void operator delete(void*) = delete;

    private:
        WCHAR m_name[buffer_size] = {};
    };

    template <typename T, bool ignoreNullptr, const void* defaultValue,
              typename get_name_fn_t, get_name_fn_t get_name_fn,
              size_t buffer_size = MAX_PATH + 1>
    class obj_name_ansi
    {
    public:
        obj_name_ansi(const obj_name_ansi&) = delete;
        obj_name_ansi& operator=(const obj_name_ansi&) = delete;
        obj_name_ansi& operator=(obj_name_ansi&& other) = delete;

        bool operator==(std::string str) const { return !_stricmp(m_name, str.c_str()); }
        bool operator==(std::string_view str) const { return !_stricmp(m_name, str.data()); }
        bool operator==(LPCSTR str) const { return !_stricmp(m_name, str); }

        T operator=(T obj)
        {
            get_name_fn(obj, m_name, buffer_size - 1);
            return obj;
        }

        obj_name_ansi()
        {
            if constexpr (ignoreNullptr || defaultValue != nullptr)
            {
                if constexpr (std::is_same<T, std::string_view>::value && defaultValue == nullptr)
                    obj_name_ansi::operator=(T(""));
                else
                    obj_name_ansi::operator=(T(defaultValue));
            }
        }

        obj_name_ansi(T obj) { obj_name_ansi::operator=(obj); }

        ~obj_name_ansi() = default;

        [[nodiscard]] const char* c_str() const noexcept { return m_name; }
        [[nodiscard]] std::string_view get() const noexcept { return m_name; }
        [[nodiscard]] std::string make_string() const { return std::string(m_name); }

        void* operator new(size_t) = delete;
        void operator delete(void*) = delete;

    private:
        CHAR m_name[buffer_size] = {};
    };

    using atom_name = obj_name<ATOM, false, nullptr, decltype(GetAtomNameW), GetAtomNameW>;
    using window_class = obj_name<HWND, false, nullptr, decltype(GetClassNameW), GetClassNameW>;
    using hmodule_file_name = obj_name<HMODULE, true, nullptr, decltype(GetModuleFileNameW), GetModuleFileNameW>;
    using hmodule_file_name_ansi = obj_name_ansi<HMODULE, true, nullptr, decltype(GetModuleFileNameA), GetModuleFileNameA>;
    using hmodule_name = obj_name<HMODULE, true, nullptr, decltype(Utils::get_module_name), Utils::get_module_name>;
    using htheme_class_name = obj_name<HTHEME, false, nullptr, decltype(Utils::GetThemeClass), Utils::GetThemeClass>;
    using runtime_class_name = obj_name<::IInspectable*, false, nullptr, decltype(Utils::get_runtime_class_name), Utils::get_runtime_class_name>;

    namespace os
    {
        const ULONG buildNumber = Utils::get_kernel_shared_info()->NtBuildNumber;
    }
}