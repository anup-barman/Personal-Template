import sys
import os
import subprocess
import re
from time import time

def benchmark(func):
    """
    Decorator to measure execution time of a function.
    """
    def timer(*args, **kwargs):
        start = time()
        result = func(*args, **kwargs)
        stop = time()
        print(f'Time taken: {stop - start:.3f}s')
        return result
    return timer

SECTION = ['section', 'subsection', 'subsubsection', 'paragraph']
TEXT = ''

MINTED_OPTS = """
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
    mathescape=false
    samepage=false,
    showspaces=false,
    showtabs =false,
    texcl=false
"""

COMMENT_TYPES = [
    ('/**', '*/'),
    ("'''", "'''"),
    ('"""', '"""'),
]

def find_start_comment(source, start=None):
    first = (-1, -1, None)
    for s, e in COMMENT_TYPES:
        i = source.find(s, start)
        if i != -1 and (i < first[0] or first[0] == -1):
            first = (i, i + len(s), e)
    return first

def parse_include(line):
    line = line.strip()
    if line.startswith("#include"):
        return line[8:].strip()
    return None

def escape(input_str):
    input_str = input_str.replace('<', r'\ensuremath{<}')
    input_str = input_str.replace('>', r'\ensuremath{>}')
    return input_str

def pathescape(input_str):
    input_str = input_str.replace('\\', r'\\')
    input_str = input_str.replace('_', r'\_')
    input_str = escape(input_str)
    return input_str

def codeescape(input_str):
    input_str = input_str.replace('_', r'\_')
    input_str = input_str.replace('\n', '\\\\\n')
    input_str = input_str.replace('{', r'\{')
    input_str = input_str.replace('}', r'\}')
    input_str = input_str.replace('^', r'\ensuremath{\hat{\;}}')
    input_str = escape(input_str)
    return input_str

def ordoescape(input_str, esc=True):
    if esc:
        input_str = escape(input_str)
    start = input_str.find("O(")
    if start >= 0:
        bracketcount = 1
        end = start + 1
        while end + 1 < len(input_str) and bracketcount > 0:
            end = end + 1
            if input_str[end] == '(':
                bracketcount += 1
            elif input_str[end] == ')':
                bracketcount -= 1
        if bracketcount == 0:
            return r"%s\bigo{%s}%s" % (
                input_str[:start], 
                input_str[start+2:end], 
                ordoescape(input_str[end+1:], False)
            )
    return input_str

def clean_folder_name(folder_name):
    """Remove numerical prefix from folder name for display"""
    return re.sub(r'^\d+\.\s*', '', folder_name)

def processwithcomments(caption):
    code = ''
    try:
        with open(caption, 'r') as instream:
            lines = instream.readlines()
    except IOError:
        print(r"error{%s: Could not read source.}" % caption)
        return ''

    knowncommands = ['Author', 'Date', 'Description', 'Source', 'Time', 'Memory', 'License', 'Status', 'Usage', 'Details']
    commands = {}
    error = ""
    warning = ""
    
    nlines = []
    for line in lines:
        if 'exclude-line' in line:
            continue
        if 'include-line' in line:
            line = line.replace('// ', '', 1)
        
        had_comment = "///" in line
        # Remove /// comments
        line = line.split("///")[0].rstrip()
        
        # Remove '#pragma once' lines
        if line == "#pragma once":
            continue
        if had_comment and not line:
            continue
            
        nlines.append(line)

    source = '\n'.join(nlines)
    nsource = ''
    start, start2, end_str = find_start_comment(source)
    end = 0
    
    while start >= 0 and not error:
        nsource = nsource.rstrip() + source[end:start]
        end = source.find(end_str, start2)
        if end < start:
            error = "Invalid %s %s comments." % (source[start:start2], end_str)
            break
        comment = source[start2:end].strip()
        end += len(end_str)
        start, start2, end_str = find_start_comment(source, end)

        commentlines = comment.split('\n')
        command = None
        value = ""
        for cline in commentlines:
            allow_command = False
            cline = cline.strip()
            if cline.startswith('*'):
                cline = cline[1:].strip()
                allow_command = True
            ind = cline.find(':')
            if allow_command and ind != -1 and ' ' not in cline[:ind] and cline[0].isalpha() and cline[0].isupper():
                if command:
                    if command not in knowncommands:
                        error += "Unknown command: " + command + ". "
                    commands[command] = value.lstrip()
                command = cline[:ind]
                value = cline[ind+1:].strip()
            else:
                value = value + '\n' + cline
        if command:
            if command not in knowncommands:
                error += "Unknown command: " + command + ". "
            commands[command] = value.lstrip()

    if end >= 0:
        nsource = nsource.rstrip() + source[end:]
    nsource = nsource.strip()

    # Produce output
    out = []
    if warning:
        print(r"warning{%s: %s}" % (caption, warning))
    if error:
        print(r"error{%s: %s}" % (caption, error))
    else:
        if commands.get("Description"):
            out.append(r"\printdescription{%s}" % escape(commands["Description"]))
        if commands.get("Usage"):
            out.append(r"\printusage{%s}" % codeescape(commands["Usage"]))
        if commands.get("Time"):
            out.append(r"\printtime{%s}" % ordoescape(commands["Time"]))
        if commands.get("Memory"):
            out.append(r"\printmemory{%s}" % ordoescape(commands["Memory"]))
        
        out.append('\\begin{minted}[' + MINTED_OPTS + ']{C++}\n')
        out.append(nsource)
        out.append('\\end{minted}\n')

    code = '\n'.join(out) + '\n'
    return code

def gen(level):
    global TEXT

    folders = [x for x in os.listdir(".") if os.path.isdir(x) and x != ".git"]
    files = [x for x in os.listdir(".") if os.path.isfile(x) and x != ".gitignore"]
  
    # Sort folders with numerical prefix support
    def sort_key(name):
        match = re.match(r'^(\d+)', name)
        if match:
            return (int(match.group(1)), name)
        return (float('inf'), name)
  
    folders.sort(key=sort_key)
    files.sort()

    parent = os.getcwd()
    for folder in folders:
        display_name = clean_folder_name(folder)
        TEXT += '\\' + SECTION[level] + '{' + display_name + '}\n'
        child = os.path.join(parent, folder)
        os.chdir(child)
        gen(level + 1)
        os.chdir(parent)

    for file in files:
        name, ext = os.path.splitext(file)
        if ext not in ['.cpp', '.py', '.java', '.tex', '.h']:
            continue
        name = re.sub('_', '\\_', name)

        TEXT += '\\' + SECTION[level] + '{' + name + '}\n'
        if ext == '.tex':
            TEXT += '\\input{' + '\"' + os.getcwd() + '/' + file + '\"' + '}\n'
        else:
            source = processwithcomments(file)
            TEXT += source

@benchmark
def main():
    global TEXT

    main_dir = os.getcwd()
    code_dir = os.path.join(main_dir, 'code')
    template_dir = os.path.join(main_dir, 'template')

    if not os.path.exists(code_dir):
        print("Error!\nFolder 'code' not found!")
        sys.exit(1)

    os.chdir(code_dir)
    gen(0)

    if not os.path.exists(template_dir):
        print("Error!\nFolder 'template' not found!")
        sys.exit(1)

    os.chdir(template_dir)
    
    TEXT += '\\end{multicols}\n'
    TEXT += '\\end{document}'

    with open('template.tex', 'r') as f:
        template_content = f.read()
    
    full_content = template_content + TEXT
    
    with open('notebook.tex', 'w') as f:
        f.write(full_content)
        
    print("Generating Notebook...")
    print("This may take a while. Please wait...")
    
    # Run pdflatex multiple times to resolve references/indexes
    for i in range(2): # reduced from 4, usually 2-3 is enough
        subprocess.run('pdflatex -interaction=nonstopmode --shell-escape notebook.tex', shell=True, stdout=subprocess.PIPE)
    
    # Clean up
    if os.path.exists('_minted-notebook'):
        subprocess.run('rm -r _minted-notebook', shell=True)
    
    if os.path.exists('notebook.pdf'):
        subprocess.run(f'mv notebook.pdf "{main_dir}"', shell=True)
        
    subprocess.run('rm notebook.*', shell=True)
    print('Done!')

if __name__ == "__main__":
    main()
