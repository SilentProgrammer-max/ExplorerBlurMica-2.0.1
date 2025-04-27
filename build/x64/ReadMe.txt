
### v2.0.1 – 2024-02-12
- Compatible with Windows 11 Preview Canary 23H2 26040 and 24H2 26052  
- Optimized compatibility with StartAllBack  
- Fixed a white bar appearing on the title bar when first opening after reboot (Mica effect)  
- Added **MicaAlt** effect (`effect=4`); normal Mica remains `effect=2`  
- Restored **showLine** option (use `showLine=true` to hide the split line between TreeView and DUI)  
- Updated and optimized registration & uninstall scripts  
> Special thanks to OnCloud125252  

### v2.0.0 – 2024-01-01
- Fully refactored and rewritten from scratch for stability & performance (#34)  
- **New setting**: `clearWinUIBg` – removes WinUI/XAML toolbar backgrounds on Windows 11  
- **Removed**: `[smallBorder]`, `[showLine]`, `[darkRibbon]` options  
- Fixed Windows 10 Ribbon rendering (dropped `darkRibbon`)  
- Added support for WinUI toolbar in Windows 11 23H2/Dev/Canary (#39, #59, #62, #65, #67)  
- Fixed major Control Panel rendering issues (#22, #38, #54, #56, #66, #70, #71, #77)  
- Fixed Preview Panel text rendering & WinUI support (#41)  
- Fixed address-bar dropdown scrollbar color with `clearBarBg` (#53)  
- Fixed Windows 10 new search box rendering  
- Switched from BHO to FolderExtension COM loading (#58, #63, #79)  
- Improved compatibility with StartAllBack & others (#25, #28, #55, #73, #75)  
- Unified TreeView/DUI split-line styling, removed `showLine`  
- Fixed Acrylic blur boundary on Windows 10 (dropped `smallBorder`)  
- Performance & stability tweaks (2024-01-03)  
> **Note:** From this version on, only header files (`*.h`) are shipped to prevent license misuse.

### v1.0.7 – 2023-08-11
- **New settings**:  
  - `clearAddress`: clear the address-bar background (disable “Classic search box” in StartAllBack)  
  - `clearBarBg`: clear scroll-bar background (program-drawn scrollbars may differ in style)  
  - `effect=3`: pure Blur/Clear effect (#42)  
- Config split: `[blend]` → `[light]` & `[dark]` (#32)  
- Fixed multi-tab **showLine** loss of effect  
- Fixed missing window effects on DPI change/monitor switch (#46)  
- Fixed File Explorer Properties & file dialog rendering (#35)  
- Various rendering optimizations

### v1.0.6 – 2023-05-01
- `showLine`: toggle separator between TreeView & preview panel  
- `darkRibbon`: enable dark Ribbon in Windows 10 Light mode  
- Fixed Acrylic blur overflow on Windows 10 (default `smallBorder=false`)

### v1.0.5 – 2023-04-29
- Fixed StartAllBack navigation-bar compatibility (#17)  
- Fixed Control Panel & Shell-page rendering issues  
- General code optimizations

### v1.0.4 – 2023-01-12
- Fixed specific background-render errors (#10)  
- Fixed Control Panel command module & nav-bar rendering (#9)  
- Fixed Microsoft IME text-color bug (#8)

### v1.0.3 – 2022-11-21
- Fixed Windows 10 Dark mode address-bar opacity (#7)  
- Fixed reversed Blur/Acrylic config IDs

### v1.0.2 – 2022-10-22
- Added Windows 22H2 multi-tab support (#5)  
- Fixed Windows 11 left white bar & dark-mode address-bar opacity  
- Stability enhancements & Acrylic support (default `effect=2`)

### v1.0.1 – 2022-08-27
- Fixed opaque Ribbon bar on English-language Windows 10
