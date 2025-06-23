# ⚡ PowerShell Suite Installer

Welcome to the **PowerShell Suite Installer**! This tool automates the setup of a modern PowerShell environment on Windows, including fonts, modules, and terminal configuration.

---

## ✨ Features

- 🚀 **Automated PowerShell & Suite Installation**
- 🧩 **Module Management** (Terminal-Icons)
- 🔤 **Lilex Nerd Font Installation**
- 🖥️ **Windows Terminal Configuration**
- 🛡️ **Robust Error Handling & Cleanup**

---

## 🛠️ Usage

1. **Run the Installer**
   - Double-click the executable or run from terminal:
     ```sh
     PowerShellInstaller.exe
     ```
2. **Follow On-Screen Prompts**
   - The installer will:
     - Download and install PowerShell
     - Set up your PowerShell profile
     - Install the Lilex font
     - Move and configure Terminal-Icons
     - Update Windows Terminal settings

---

## 📋 Requirements

- Windows 11
- Internet connection
- Administrator privileges (for font and terminal settings)

---

## 🐞 Troubleshooting

- ⚠️ If you see warnings about missing folders or failed downloads, check your internet connection and permissions.
- 🔄 Re-run the installer if any step fails.
- 🧹 The installer cleans up temporary files automatically.

---

## 📂 Project Structure

```
PowerShell_Installer/
├── PowerShellInstaller.exe
├── main.c
├── lib/
│   ├── helpers.c
│   ├── downloader.c
│   ├── fileio.c
│   └── headers/
│       ├── fileio.h
│       ├── downloader.h
│       └── const.h
└── ...
```

---

## 🙏 Credits

- [PowerShell](https://github.com/PowerShell/PowerShell)
- [Nerd Fonts (Lilex)](https://github.com/ryanoasis/nerd-fonts)
- [Terminal-Icons](https://github.com/devblackops/Terminal-Icons)

---

> Made with ❤️ for Windows Power Users!
