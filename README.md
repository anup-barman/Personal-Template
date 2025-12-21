# ACM-ICPC Notebook Generator

![Python](https://img.shields.io/badge/python-3.8%2B-blue)
![License](https://img.shields.io/badge/license-MIT-green)
![Status](https://img.shields.io/badge/status-active-success)

A Python script to generate a PDF notebook for Competitive Programming (ACM-ICPC, IOI, etc.) from your source code. It features syntax highlighting, automatic index generation, and supports LaTeX customization.

## Features
- **Syntax Highlighting**: Uses `pygments` (via LaTeX `minted` package).
- **Automatic Indexing**: Generates a Table of Contents based on your directory structure.
- **Customizable**: Edit the LaTeX template to match your team's needs.
- **Complexity Support**: Automatically format Time and Memory complexity from comments.

## Prerequisites

### Python
- Python 3.8 or higher
- `pip`

### LaTeX
A full TeX distribution is required to compile the PDF.
- **Ubuntu/Debian**: `sudo apt install texlive-full`
- **macOS**: `brew install --cask mactex`
- **Windows**: Install [MiKTeX](https://miktex.org/download) or [TeX Live](https://www.tug.org/texlive/).

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/Personal-Template.git
   cd Personal-Template
   ```

2. Install Python dependencies:
   ```bash
   pip install -r requirements.txt
   ```

## Usage

1. **Organize your code**: Place your source files in the `code/` directory. You can create subdirectories (e.g., `Graph`, `DP`) to organize them.
   - Files are sorted alphabetically.
   - Folders can be prefixed with numbers (e.g., `1. Graph`) to control order.

2. **Generate the Notebook**:
   ```bash
   python3 main.py
   ```
   The script will generate `notebook.pdf` in the root directory.

## Code formatting features

Special comments in your code are parsed to add metadata to the notebook:

```cpp
/**
 * Author: Your Name
 * Date: 2023-11-15
 * Description: Short description of the algorithm.
 * Time: O(V+E)
 * Status: Tested
 */
```

## Customization

- **Team Info**: Edit `template/template.tex` to change the team name and university.
- **Formatting**: Adjust the `minted` options in `main.py` if you want to change syntax highlighting styles.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments
- Based on [hamza-28's template](https://github.com/hamza-28).
