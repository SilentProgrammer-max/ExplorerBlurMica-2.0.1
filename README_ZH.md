# ExplorerBlurMica

Add Blur, Acrylic or Mica background effects to Windows File Explorer on Windows 10 and 11.

[![License](https://img.shields.io/github/license/Maplespe/ExplorerBlurMica.svg)](https://www.gnu.org/licenses/lgpl-3.0.en.html)  
[![Downloads](https://img.shields.io/github/downloads/Maplespe/ExplorerBlurMica/total.svg)](https://github.com/Maplespe/ExplorerBlurMica/releases)  
[![Latest Release](https://img.shields.io/github/release/Maplespe/ExplorerBlurMica.svg)](https://github.com/Maplespe/ExplorerBlurMica/releases/latest)  
![Language: C++](https://img.shields.io/badge/language-c++-F34B7D.svg)  
![Last Commit](https://img.shields.io/github/last-commit/Maplespe/ExplorerBlurMica.svg)  

---

## Features

- Selectable **Blur**, **Acrylic** or **Mica** effects  
- Customizable tint color (RGBA)  
- Automatic light/dark mode adaptation  

_For a global blur/Acrylic/Mica effect on all windows, see [DWMBlurGlass](https://github.com/Maplespe/DWMBlurGlass)._

---

## Compatibility

Compatible with StartAllBack, OldNewExplorer and other window-styling utilities.  
Supports third-party themes.

---

## Table of Contents

- [ExplorerBlurMica](#explorerblurmica)
  - [Features](#features)
  - [Compatibility](#compatibility)
  - [Table of Contents](#table-of-contents)
  - [Preview](#preview)
    - [Dark More](#dark-more)
    - [Win11 Dark Preview](#win11-dark-preview)
    - [details](#details)
    - [Usage](#usage)
    - [Configuration](#configuration)
    - [Dependencies](#dependencies)

---

## Preview

<details><summary><strong>Windows 11 Preview</strong></summary>

**WinUI 3 (23H2 / 24H2 Canary)**  
```ini
[config]
effect=1
clearBarBg=true
clearAddress=true
clearWinUIBg=true

[light]
r=255
g=255
b=255
a=200
```
### Dark More
```
[config]
effect=2
clearBarBg=true
clearAddress=true
clearWinUIBg=true
```
### Win11 Dark Preview
</details> <details><summary><strong>Windows 10</strong></summary>
```
[config]
effect=1
clearBarBg=true
clearAddress=true
clearWinUIBg=false
[light]
r=222
g=222
b=222
a=200
```


### details
</details>
### Usage
Install

1.  Download the latest ZIP from the Releases page.

2. Extract into a folder (e.g. C:\Program Files\ExplorerBlurMica).

3.  Run as Administrator and execute:

```
register.cmd
```
pr
``` regsvr32 "C:\Program Files\ExplorerBlurMica\ExplorerBlurMica.dll"
```
4. Open or refresh File Explorer; the effect will apply automatically.

Uninstall
1. Run as Administrator and execute:
```
uninstall.cmd
```
or
```
regsvr32 /u "C:\Program Files\ExplorerBlurMica\ExplorerBlurMica.dll"
```
2. Delete remaining files if desired.

Tip: If Explorer crashes, hold ESC while launching Explorer to bypass the effect, then run the uninstall script.

### Configuration
Edit config.ini in the same folder as ExplorerBlurMica.dll:
```
[config]
# Effect: 0=Blur, 1=Acrylic, 2=Mica, 3=Blur(Clear), 4=MicaAlt
effect=1

# Remove address bar background
clearAddress=true

# Remove scrollbar background (program-drawn scrollbars may differ in style)
clearBarBg=true

# Remove WinUI/XAML toolbar background in File Explorer
clearWinUIBg=true

# Show separator line between TreeView and preview panel
showLine=true

[light]
# RGBA tint in Light mode
r=220
g=220
b=220
a=160

[dark]
# RGBA tint in Dark mode
r=0
g=0
b=0
a=120
```
Save and reopen File Explorer to apply changes.

### Dependencies
- MinHook for API hooking

License
This project is licensed under the GNU LGPL v3.0.
See COPYING.LESSER for full license text.
