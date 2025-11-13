### Required Packages

This project requires Python, Pygments and a TeX distribution. Platform-specific installation notes follow.

- Python 3
  - Debian/Ubuntu:
    ```bash
    sudo apt-get update
    sudo apt-get install python3 python3-pip
    ```
  - Fedora:
    ```bash
    sudo dnf install python3 python3-pip
    ```
  - Arch Linux:
    ```bash
    sudo pacman -S python python-pip
    ```
  - macOS (Homebrew):
    ```bash
    brew install python
    ```
  - Windows:
    - Use the official installer from python.org or Chocolatey:
      ```powershell
      choco install python
      ```
    - Using WSL is recommended for a Linux-like environment.

- pygments (syntax highlighter)
  ```bash
  pip3 install pygments
  ```
  On Windows use `pip install pygments` if `pip3` is not available.

- TeX distribution (for building PDFs)
  - Debian/Ubuntu:
    ```bash
    sudo apt-get install texlive-full
    ```
  - Fedora:
    ```bash
    sudo dnf install texlive-scheme-full
    ```
    or install TeX Live via the official installer.
  - Arch Linux:
    ```bash
    sudo pacman -S texlive-most
    ```
  - macOS:
    - Install MacTeX (recommended):
      ```bash
      brew install --cask mactex
      ```
    - Or install BasicTeX / MacTeX from tug.org.
  - Windows:
    - Install MiKTeX (recommended) or TeX Live. With Chocolatey:
      ```powershell
      choco install miktex
      ```

Notes:
- Ensure `python`/`python3` and `pdflatex` are on your PATH after installation.
- Installing the full TeX distribution can be large; install smaller schemes if disk space is limited.

### How To Use

Put your code files in the `code` folder. You can create subfolders (e.g. Graph, String, Math) for different categories.

Open a terminal and run:

- Linux / macOS / WSL:
  ```bash
  python3 main.py
  ```
- Windows (native):
  ```powershell
  python main.py
  ```

### Customization

To customize output edit `template/template.tex`.

- Change team information: edit lines ~3–9.
- Change font size: edit line 1 or adjust `scaled=..` (around line 20) for flexible scaling.

### Attribution

This project was taken from hamza-28's GitHub: https://github.com/hamza-28
