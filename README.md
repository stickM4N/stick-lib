```
███████╗████████╗██╗ ██████╗██╗  ██╗      ██╗     ██╗██████╗
██╔════╝╚══██╔══╝██║██╔════╝██║ ██╔╝██╗██╗██║     ██║██╔══██╗
███████╗   ██║   ██║██║     █████╔╝ ╚═╝╚═╝██║     ██║██████╔╝
╚════██║   ██║   ██║██║     ██╔═██╗ ██╗██╗██║     ██║██╔══██╗
███████║   ██║   ██║╚██████╗██║  ██╗╚═╝╚═╝███████╗██║██████╔╝
╚══════╝   ╚═╝   ╚═╝ ╚═════╝╚═╝  ╚═╝      ╚══════╝╚═╝╚═════╝    by stickM4N
```

stick::lib
==========

Full and cross-platform implementation of many libraries without any dependencies.

The main goal of this library is to mimic std:: library and implement all missing features.

It is implemented in the most simple and efficient way possible, what makes it good for educational purposes.

Requirements
-------------

- [CMake](https://cmake.org)
- [Doxygen](https://www.doxygen.nl) (Optional)

Installation
------------

- Acquire sources by any of these methods:

```bash
# Using git...
mkdir "<source_directory>"
cd "<source_directory>"

git clone https://github.com/stickM4N/stick-lib .
```

```bash
mkdir "<source_directory>"
cd "<source_directory>"

# Using wget, curl, etc. Or maybe download it from a browser...
wget https://github.com/stickM4N/stick-lib/archive/refs/heads/main.zip

# Or unpack using a similar method or some software...
unzip main.zip
cd "stick-lib-main"
```

- Build:

```bash
mkdir "<build_dir>"
cd "<build_dir>"

cmake ..
cmake --build .
```

- Install:

```bash
# Might need superuser privileges...
cmake --install .
```

Documentation
-------------

Documentation for latest version can be found [here](https://stickm4n.github.io/index.html).

Author
------

Made by Julio C. Galindo ([stickM4N](https://github.com/stickM4N)). I can be contacted by telegram
[stickM4N](https://t.me/stickM4N) or by [e-mail](mailto:jcgalindo.jcgh@gmail.com). Feel free to do it...

Contributing
------------

I openly listen to any suggestion. Feel free to open issues and/or pull requests to implement new features and/or fix
bugs.

License
-------

This project is licensed under the terms of the GNU General Public License v3.0
([GNU GPLv3](https://choosealicense.com/licenses/gpl-3.0)).
