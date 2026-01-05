# CP-Arsenal Personal Template

A script to generate a competitive programming personal template PDF from your code library.

### Required Packages

* python3

  ```bash
  sudo apt-get install python3
  ```

* pygments

  ```bash
  sudo apt-get install python3-pip
  pip3 install pygments
  ```

* texlive-full

  ```bash
  sudo apt-get install texlive-full
  ```

### Directory Structure

* **CodeLibrary/**: Put your `.cpp`, `.py`, `.java` codes here. You can organize them into subfolders (e.g., Graph, String, Math).
* **Template/**: Contains the LaTeX template and assets.
  * **Assets/**: Place your logos and icons here.

### How To Use

Open a terminal and run:

```bash
python3 main.py
```

This will generate `notebook.pdf` in the root directory.

### Customization

To customize the template, edit the `Template/template.tex` file.

* **Colors**: Change definitions of `CfCyan` or `CfGreen`.
* **Personal Details**: Update `\Name` and `\templateTitle`.
* **Icons**: Replace files in `Template/Assets/` (`codeforces-icon.jpg`, `atcoder-icon.png`, `codechef-icon.jpg`, `logo.pdf`).
* **Font Size**: Edit line 1 or change `scaled=..` in line 20.
