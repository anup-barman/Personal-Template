import sys
import os
import subprocess
import re
import pygments
from time import time

def benchmark(func):
  def timer():
    start = time()
    func()
    stop = time()
    print('Time taken : %.3fs' %(stop - start))
    return
  return timer

section = ['section', 'subsection', 'subsubsection', 'paragraph']
text = ''

minted_opts = """
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
    samepage=false, %with this setting you can force the list to appear on the same page
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

def escape(input):
    input = input.replace('<', r'\ensuremath{<}')
    input = input.replace('>', r'\ensuremath{>}')
    return input

def pathescape(input):
    input = input.replace('\\', r'\\')
    input = input.replace('_', r'\_')
    input = escape(input)
    return input

def codeescape(input):
    input = input.replace('_', r'\_')
    input = input.replace('\n', '\\\\\n')
    input = input.replace('{', r'\{')
    input = input.replace('}', r'\}')
    input = input.replace('^', r'\ensuremath{\hat{\;}}')
    input = escape(input)
    return input

def ordoescape(input, esc=True):
    if esc:
        input = escape(input)
    start = input.find("O(")
    if start >= 0:
        bracketcount = 1
        end = start+1
        while end+1<len(input) and bracketcount>0:
            end = end + 1
            if input[end] == '(':
                bracketcount = bracketcount + 1
            elif input[end] == ')':
                bracketcount = bracketcount - 1
        if bracketcount == 0:
            return r"%s\bigo{%s}%s" % (input[:start], input[start+2:end], ordoescape(input[end+1:], False))
    return input

def processwithcomments(caption):
  code = ''
  instream = open(caption)
  knowncommands = ['Author', 'Date', 'Description', 'Source', 'Time', 'Memory', 'License', 'Status', 'Usage', 'Details']
  # requiredcommands = ['Author', 'Description']
  requiredcommands = []
  includelist = []
  error = ""
  warning = ""
  # Read lines from source file
  try:
    lines = instream.readlines()
  except:
    error = "Could not read source."
  nlines = list()
  for line in lines:
    if 'exclude-line' in line:
      continue
    if 'include-line' in line:
      line = line.replace('// ', '', 1)
    had_comment = "///" in line
    keep_include = 'keep-include' in line
    # Remove /// comments
    line = line.split("///")[0].rstrip()
    # Remove '#pragma once' lines
    if line == "#pragma once":
      continue
    if had_comment and not line:
      continue
    # Check includes
    # include = parse_include(line)
    # if include is not None and not keep_include:
    #   includelist.append(include)
    #   continue
    nlines.append(line)
  # Remove and process multiline comments
  source = '\n'.join(nlines)
  nsource = ''
  start, start2, end_str = find_start_comment(source)
  end = 0
  commands = {}
  while start >= 0 and not error:
    nsource = nsource.rstrip() + source[end:start]
    end = source.find(end_str, start2)
    if end<start:
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
            error = error + "Unknown command: " + command + ". "
          commands[command] = value.lstrip()
        command = cline[:ind]
        value = cline[ind+1:].strip()
      else:
        value = value + '\n' + cline
    if command:
      if command not in knowncommands:
        error = error + "Unknown command: " + command + ". "
      commands[command] = value.lstrip()
  for rcommand in sorted(set(requiredcommands) - set(commands)):
    error = error + "Missing command: " + rcommand + ". "
  if end>=0:
    nsource = nsource.rstrip() + source[end:]
  nsource = nsource.strip()

  # Produce output
  out = []
  if warning:
    print(r"warning{%s: %s}" % (caption, warning))
  if error:
    print(r"error{%s: %s}" % (caption, error))
  else:
    # addref(caption, outstream)
    if commands.get("Description"):
        out.append(r"\printdescription{%s}" % escape(commands["Description"]))
    if commands.get("Usage"):
        out.append(r"\printusage{%s}" % codeescape(commands["Usage"]))
    if commands.get("Time"):
        out.append(r"\printtime{%s}" % ordoescape(commands["Time"]))
    if commands.get("Memory"):
        out.append(r"\printmemory{%s}" % ordoescape(commands["Memory"]))
    # if includelist:
    #     out.append(r"\leftcaption{%s}" % pathescape(", ".join(includelist)))
    # if nsource:
        # out.append(r"\rightcaption{%s%d lines}" % (hsh, len(nsource.split("\n"))))
    # langstr = ", language="+listingslang
    # out.append(r"\begin{lstlisting}[caption={%s}%s]" % (pathescape(caption), langstr))
    out.append('\\begin{minted}[' + minted_opts + ']{C++}\n')
    out.append(nsource)
    out.append('\\end{minted}\n')
    # out.append(r"\end{lstlisting}")

  for line in out:
    code = code + line + '\n'
 
  return code

def gen(level):
  global text

  folders = [x for x in os.listdir(".") if os.path.isdir(x) and x != ".git"]
  files = [x for x in os.listdir(".") if os.path.isfile(x) and x != ".gitignore"]
  
  folders.sort()
  files.sort()

  parent = os.getcwd()
  for folder in folders:
    text = text + '\\' + section[level] + '{' + folder + '}\n'
    child = parent + "/" + folder
    os.chdir(child)
    gen(level + 1)
    os.chdir(parent)

  for file in files:
    name, ext = os.path.splitext(file)
    if ext not in ['.cpp', '.py', '.java', '.tex', '.h']:
      continue
    name = re.sub('_','\\_', name)

    text = text + '\\' + section[level] + '{' + name + '}\n'
    if ext == '.tex':
      text = text + '\\input{' + '\"' + os.getcwd() + '/' + file + '\"' + '}\n'
    else:
      source = processwithcomments(file)
      text = text + source

@benchmark
def main():
  global text

  main_dir = os.getcwd()

  try:
    os.chdir('code')
  except:
    print("Error!\nFolder \'code\' not found!")
    sys.exit()

  gen(0)

  try:
    os.chdir(main_dir + '/template')
  except:
    print("Error!\nFolder \'template\' not found!")
    sys.exit()

  text = text + '\\end{multicols}\n'
  text = text + '\\end{document}'

  file = open('template.tex', 'r')
  text = file.read() + text
  file.close()
  file = open('notebook.tex', 'w')
  file.write(text)
  file.close()
  print("Generating Notebook...")
  print("This may take a while. Please wait...")
  for i in range(4):
    subprocess.run('pdflatex -interaction=nonstopmode --shell-escape notebook.tex', shell=True, stdout=subprocess.PIPE)
  os.system('rm -r _minted-notebook')
  os.system('mv notebook.pdf ' + '\"' + main_dir + '\"')
  os.system('rm notebook.*')
  print('Done!')

main()
