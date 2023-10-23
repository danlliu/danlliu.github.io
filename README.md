# danlliu.github.io

The third iteration of my personal website!

## License

Copyright 2023 Daniel Liu

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

## Infrastructure

### Main Page

`index.html` is rendered from Jinja templates and static data.

**Front-End:**
- HTML
- Tailwind CSS
- JavaScript

**Rendering / Templating:**
- The data for the website is stored in the [`src/data`](src/data) directory.
- HTML templates are stored in the [`src/templates`](src/templates) directory.
- These files are interpreted by [`templates.py`](src/templates.py) to generate
  the rendered HTML files in `build`.
- To generate the CSS file, `npx tailwindcss` is used to generate the required
  CSS tags.
- JavaScript files are copied from [`src/js`](src/js) to the `build/script`
  directory.

### "Super Secret" Terminal Mode

The fun begins! Terminal mode is an easter egg I wanted to add that ended up
becoming the majority of this project.

The HTML for terminal mode is rendered in a similar fashion, although there's
no template data at all. I reuse the same infrastructure for simplicity.

All of the logic behind terminal mode is written in C++, and compiled to
WebAssembly using Emscripten. Terminal mode also uses some JavaScript to act
as a bridge between Wasm and the DOM (in [`terminal_mode_interface.js`](src/js/terminal_mode_interface.js)).

**`wash`: the WebAssembly SHell:**

Terminal mode relies on a completely emulated filesystem, which contains the
contents of my website, but in textual format. The interface between these files
and the terminal is a shell called `wash`. `wash` implements a subset of shell
commands (shown below), allowing the user to move around the file system, read
files, and even create new files and write to them!

The code for the filesystem is in [`filesystem.hpp`](src/cpp/filesystem.hpp) and
[`filesystem.cpp`](src/cpp/filesystem.cpp). The code for `wash` is in
[`wash.hpp`](src/cpp/wash.hpp) and [`wash.cpp`](src/cpp/wash.cpp). `wash` also
utilizes [`args.hpp`](src/cpp/args.hpp) for argument parsing, thanks to @brenfwd
for writing that!

**Terminal Emulation:**

For terminal mode, we need a terminal! The terminal emulator code is in
[`terminal_emulator.hpp`](src/cpp/terminal_emulator.hpp) and 
[`terminal_emulator.cpp`](src/cpp/terminal_emulator.cpp). This implements an
ANSI escape code-compatible terminal, including 256 color support!

### Makefile

The [`Makefile`](./Makefile) chains together all of the necessary build steps.
To build the website, run

```console
$ make
```

To spin up a server using Python's `http.server`, run

```console
$ make server
```
