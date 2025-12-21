"""
ACM-ICPC Notebook Generator

This script automates the creation of a PDF notebook for competitive programming.
It traverses a source code directory, extracts metadata from comments, applies
syntax highlighting, and compiles a LaTeX document.

Dependencies:
    - Python 3.8+
    - Pygments
    - LaTeX distribution (TeX Live, MiKTeX, etc.)
"""

import sys
import os
import subprocess
import re
from time import time

# LaTeX section hierarchy
LATEX_SECTION_LEVELS = ['section', 'subsection', 'subsubsection', 'paragraph']

# Global buffer to store the generated LaTeX content
LATEX_CONTENT = ''

# Configuration for the 'minted' package (syntax highlighting)
MINTED_OPTIONS = """
    breaklines = true,
    breakanywhere = true,
    frame=lines,    
    fontfamily=tt,
    linenos=false,
    numberblanklines=true,
    numbersep=2pt,
    gobble=0,
    framerule=1pt,
    framesep=1mm,
    funcnamehighlighting=true,
    tabsize=2,
    obeytabs=false,
    mathescape=false,
    samepage=false,
    showspaces=false,
    showtabs =false,
    texcl=false
"""

# Supported comment styles for metadata extraction
COMMENT_TYPES = [
    ('/**', '*/'),  # C++/Java multiline
    ("'''", "'''"), # Python multiline
    ('"""', '"""'), # Python multiline
]

def benchmark(func):
    """
    Decorator to measure and print the execution time of a function.
    
    Args:
        func (callable): The function to benchmark.
        
    Returns:
        callable: The wrapped function.
    """
    def timer(*args, **kwargs):
        start = time()
        result = func(*args, **kwargs)
        stop = time()
        print(f'Time taken: {stop - start:.3f}s')
        return result
    return timer

def find_comment_block_start(source_code, start_index=None):
    """
    Finds the first occurrence of a comment block start marker.

    Args:
        source_code (str): The source code string to search.
        start_index (int, optional): The index to start searching from.

    Returns:
        tuple: (start_pos, content_start_pos, end_marker_string)
               Returns (-1, -1, None) if not found.
    """
    first_match = (-1, -1, None)
    for start_marker, end_marker in COMMENT_TYPES:
        index = source_code.find(start_marker, start_index)
        if index != -1 and (index < first_match[0] or first_match[0] == -1):
            first_match = (index, index + len(start_marker), end_marker)
    return first_match

def escape_latex_special_chars(text):
    """
    Escapes LaTeX special characters < and >.

    Args:
        text (str): Input text.

    Returns:
        str: Escaped text.
    """
    text = text.replace('<', r'\ensuremath{<}')
    text = text.replace('>', r'\ensuremath{>}')
    return text

def escape_latex_path(path_str):
    """
    Escapes characters in file paths for LaTeX.

    Args:
        path_str (str): The file path.

    Returns:
        str: Escaped path string.
    """
    path_str = path_str.replace('\\', r'\\')
    path_str = path_str.replace('_', r'\_')
    path_str = escape_latex_special_chars(path_str)
    return path_str

def escape_latex_code_block(code_str):
    """
    Escapes characters within code blocks for LaTeX rendering.

    Args:
        code_str (str): Code content.

    Returns:
        str: Escaped code content.
    """
    code_str = code_str.replace('_', r'\_')
    code_str = code_str.replace('\n', '\\\\\n')
    code_str = code_str.replace('{', r'\{')
    code_str = code_str.replace('}', r'\}')
    code_str = code_str.replace('^', r'\ensuremath{\hat{\;}}')
    code_str = escape_latex_special_chars(code_str)
    return code_str

def format_complexity(complexity_str, escape_text=True):
    """
    Formats Big O notation for LaTeX (e.g., O(N) -> \bigo{N}).

    Args:
        complexity_str (str): The time/memory complexity string.
        escape_text (bool): Whether to escape the text initially.

    Returns:
        str: LaTeX formatted string.
    """
    if escape_text:
        complexity_str = escape_latex_special_chars(complexity_str)
    
    start_index = complexity_str.find("O(")
    if start_index >= 0:
        bracket_count = 1
        end_index = start_index + 1
        while end_index + 1 < len(complexity_str) and bracket_count > 0:
            end_index += 1
            if complexity_str[end_index] == '(':
                bracket_count += 1
            elif complexity_str[end_index] == ')':
                bracket_count -= 1
        
        if bracket_count == 0:
            # Recursively format the rest of the string
            formatted_inner = complexity_str[start_index + 2 : end_index]
            formatted_outer = format_complexity(complexity_str[end_index + 1:], False)
            return r"%s\bigo{%s}%s" % (
                complexity_str[:start_index], 
                formatted_inner, 
                formatted_outer
            )
    return complexity_str

def format_section_title(folder_name):
    """
    Removes numerical prefixes from folder names for cleaner titles.
    Example: "1. Graph" -> "Graph"

    Args:
        folder_name (str): Original directory name.

    Returns:
        str: Formatted display name.
    """
    return re.sub(r'^\d+\.\s*', '', folder_name)

def parse_file_and_generate_latex(file_path):
    """
    Reads a source file, extracts metadata from comments, and generates the LaTeX block.

    Args:
        file_path (str): Path to the source file.

    Returns:
        str: Generated LaTeX content for the file.
    """
    try:
        with open(file_path, 'r') as file_handle:
            lines = file_handle.readlines()
    except IOError:
        print(r"error{%s: Could not read source.}" % file_path)
        return ''

    known_commands = ['Author', 'Date', 'Description', 'Source', 'Time', 'Memory', 'License', 'Status', 'Usage', 'Details']
    metadata = {}
    error_msg = ""
    warning_msg = ""
    
    # Filter lines (remove special directives and processed comments)
    filtered_lines = []
    for line in lines:
        if 'exclude-line' in line:
            continue
        if 'include-line' in line:
            line = line.replace('// ', '', 1)
        
        has_triple_slash = "///" in line
        # Remove trailing single-line comments used for directives
        line = line.split("///")[0].rstrip()
        
        # Skip include guards
        if line == "#pragma once":
            continue
        # Skip empty lines that only contained a directive
        if has_triple_slash and not line:
            continue
            
        filtered_lines.append(line)

    source_content = '\n'.join(filtered_lines)
    processed_source = ''
    
    # Extract metadata blocks (e.g., /** Author: ... */)
    start_idx, content_start_idx, end_marker = find_comment_block_start(source_content)
    last_end_idx = 0
    
    while start_idx >= 0 and not error_msg:
        # Append code before the comment block
        processed_source = processed_source.rstrip() + source_content[last_end_idx:start_idx]
        
        end_idx = source_content.find(end_marker, content_start_idx)
        if end_idx < start_idx:
            error_msg = "Invalid %s %s comments." % (source_content[start_idx:content_start_idx], end_marker)
            break
            
        comment_content = source_content[content_start_idx:end_idx].strip()
        last_end_idx = end_idx + len(end_marker)
        
        # Find next comment block
        start_idx, content_start_idx, end_marker = find_comment_block_start(source_content, last_end_idx)

        # Parse commands within the comment
        comment_lines = comment_content.split('\n')
        current_command = None
        command_value = ""
        
        for line in comment_lines:
            line = line.strip()
            # Handle block comments starting with *
            if line.startswith('*'):
                line = line[1:].strip()
                
            separator_idx = line.find(':')
            is_valid_command = (
                separator_idx != -1 and 
                ' ' not in line[:separator_idx] and 
                line[0].isalpha() and 
                line[0].isupper()
            )
            
            if is_valid_command:
                if current_command:
                    if current_command not in known_commands:
                        error_msg += f"Unknown command: {current_command}. "
                    metadata[current_command] = command_value.lstrip()
                current_command = line[:separator_idx]
                command_value = line[separator_idx+1:].strip()
            else:
                command_value = command_value + '\n' + line
                
        if current_command:
            if current_command not in known_commands:
                error_msg += f"Unknown command: {current_command}. "
            metadata[current_command] = command_value.lstrip()

    # Append remaining code
    if last_end_idx >= 0:
        processed_source = processed_source.rstrip() + source_content[last_end_idx:]
    processed_source = processed_source.strip()

    # Generate LaTeX Output
    output_lines = []
    if warning_msg:
        print(r"warning{%s: %s}" % (file_path, warning_msg))
    if error_msg:
        print(r"error{%s: %s}" % (file_path, error_msg))
    else:
        # Add metadata sections if present
        if metadata.get("Description"):
            output_lines.append(r"\printdescription{%s}" % escape_latex_special_chars(metadata["Description"]))
        if metadata.get("Usage"):
            output_lines.append(r"\printusage{%s}" % escape_latex_code_block(metadata["Usage"]))
        if metadata.get("Time"):
            output_lines.append(r"\printtime{%s}" % format_complexity(metadata["Time"]))
        if metadata.get("Memory"):
            output_lines.append(r"\printmemory{%s}" % format_complexity(metadata["Memory"]))
        
        # Add code block
        output_lines.append('\\begin{minted}[' + MINTED_OPTIONS + ']{C++}\n')
        output_lines.append(processed_source)
        output_lines.append('\\end{minted}\n')

    return '\n'.join(output_lines) + '\n'

def generate_content_from_directory(depth_level):
    """
    Recursively scans directory content to build the LaTeX structure.

    Args:
        depth_level (int): Current nesting depth (0 = section, 1 = subsection, etc.).
    """
    global LATEX_CONTENT

    # List subdirectories and files
    items = os.listdir(".")
    folders = [x for x in items if os.path.isdir(x) and x != ".git"]
    files = [x for x in items if os.path.isfile(x) and x != ".gitignore"]
  
    # Sort folders with optional numerical prefix (e.g., "1. Graph" comes before "2. Math")
    def sort_key(name):
        match = re.match(r'^(\d+)', name)
        if match:
            return (int(match.group(1)), name)
        return (float('inf'), name)
  
    folders.sort(key=sort_key)
    files.sort()

    current_dir = os.getcwd()
    
    # Process Folders (Recursion)
    for folder in folders:
        display_name = format_section_title(folder)
        LATEX_CONTENT += '\\' + LATEX_SECTION_LEVELS[depth_level] + '{' + display_name + '}\n'
        
        child_path = os.path.join(current_dir, folder)
        os.chdir(child_path)
        generate_content_from_directory(depth_level + 1)
        os.chdir(current_dir)

    # Process Files
    for file_name in files:
        name_root, extension = os.path.splitext(file_name)
        if extension not in ['.cpp', '.py', '.java', '.tex', '.h']:
            continue
            
        display_name = re.sub('_', '\\_', name_root)
        LATEX_CONTENT += '\\' + LATEX_SECTION_LEVELS[depth_level] + '{' + display_name + '}\n'
        
        if extension == '.tex':
            # Directly input existing tex files
            tex_path = os.path.join(os.getcwd(), file_name)
            LATEX_CONTENT += f'\\input{{"{tex_path}"}}\n'
        else:
            # Parse code files and wrap in LaTeX
            latex_block = parse_file_and_generate_latex(file_name)
            LATEX_CONTENT += latex_block

@benchmark
def main():
    """
    Main entry point. Orchestrates the notebook generation process.
    """
    global LATEX_CONTENT

    base_dir = os.getcwd()
    code_dir = os.path.join(base_dir, 'code')
    template_dir = os.path.join(base_dir, 'template')

    # Validate directory structure
    if not os.path.exists(code_dir):
        print("Error: Folder 'code' not found!")
        sys.exit(1)

    print("Scanning 'code' directory...")
    os.chdir(code_dir)
    generate_content_from_directory(0)

    if not os.path.exists(template_dir):
        print("Error: Folder 'template' not found!")
        sys.exit(1)

    # Prepare for compilation
    os.chdir(template_dir)
    LATEX_CONTENT += '\\end{multicols}\n'
    LATEX_CONTENT += '\\end{document}'

    # Read base template
    try:
        with open('template.tex', 'r') as f:
            template_base = f.read()
    except IOError:
        print("Error: Could not read 'template/template.tex'.")
        sys.exit(1)
    
    full_document = template_base + LATEX_CONTENT
    
    with open('notebook.tex', 'w') as f:
        f.write(full_document)
        
    print("Generating PDF Notebook...")
    print("Running pdflatex (this may take a few moments)...")
    
    # Run pdflatex multiple times to resolve cross-references and indices
    build_success = True
    for i in range(2):
        result = subprocess.run(
            'pdflatex -interaction=nonstopmode --shell-escape notebook.tex', 
            shell=True, 
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE
        )
        if result.returncode != 0:
            print(f"Warning: pdflatex run {i+1} completed with errors.")
            # We don't exit here because sometimes latex has warnings that are treated as errors but output is fine
    
    # Cleanup artifacts
    if os.path.exists('_minted-notebook'):
        subprocess.run('rm -r _minted-notebook', shell=True)
    
    if os.path.exists('notebook.pdf'):
        subprocess.run(f'mv notebook.pdf "{base_dir}"', shell=True)
        print("Done! 'notebook.pdf' generated successfully.")
    else:
        print("Error: 'notebook.pdf' was not generated. Check LaTeX logs.")

    # Cleanup temporary files
    subprocess.run('rm notebook.*', shell=True)

if __name__ == "__main__":
    main()
