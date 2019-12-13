# CMake Node Starter

Starter for node addons development with bare `cmake` instead of `node-gyp` or `cmake-js`.

❗️ **RISK: Now at very early development stage**

## Pre-Settings

Please ensure you have installed:

- node
- npm
- node-gyp (globally)
- cmake
- c++ build toolchains
    - nmake + msvc (windows)
    - make + gcc (*nix)

Other recommended:

- vcpkg
- ninja

Then install

```bash
npm install
# or yarn
yarn install
```

## Usage

edit `CMakeLists.txt` and build it, you can find `*.node` file in your cmake output directory.