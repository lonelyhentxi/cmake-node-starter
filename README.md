# CMake Node Starter

![repo-size](https://img.shields.io/github/repo-size/lonelyhentai/cmake-node-starter) ![license](https://img.shields.io/github/license/lonelyhentai/cmake-node-starter)

Starter for node addons development with bare `cmake` instead of `node-gyp` or `cmake-js`.

**❗️ RISK: Now at very early development stage**

## Pre-Settings

Please ensure you have installed:

- node
- npm
- node-gyp (only used to download nodejs source code)
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

## Usage & Example

Briefly, Edit `CMakeLists.txt` and build it, you can find `*.node` file in your cmake output directory. 
Then, you can use it in node scripts.

For example, We want to create a addon name `example`:

### Edit `CMakeLists.txt` to change target name

We should replace `ADDON_NAME` variable value to `'example'`.

```
# CMakeLists.txt
# ...
set(ADDON_NAME "example")
# ...
```

### Add function for this addon and register

At `src/example.hpp`, introduce `N-API` headers and write your addon interface:

```cpp
#include "napi.h"

class Example: public Napi::ObjectWrap<Example> {
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    explicit Example(const Napi::CallbackInfo &info);

private:
    static Napi::FunctionReference constructor;
    double _value;
    Napi::Value GetValue(const Napi::CallbackInfo &info);
    Napi::Value SetValue(const Napi::CallbackInfo &info);
};
```

Then implement them in `src/example.cpp`. Your must register your module:

```cpp
#include "example.hpp"

/** write your implements here **/

// register function
Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Example::Init(env, exports);
    return exports;
}

// edit here to fit our addon name 'example'
NODE_API_MODULE(example , Init);
```

### Build addon

CMake configure and generate command format:

**Attention: if you use `clion`, `vscode` or `visual studio` and want to auto build by these tools, you should edit their cmake build directory setting by yourself.**

```bash
/path/to/cmake -DCMAKE_BUILD_TYPE=<Debug|Release> -G <Generator-Tools> -B/dir/to/build -S/dir/to/source
```

For example:

```bash
cmake -DCMAKE_BUILD_TYPE=Debug -G "Ninja" -B./build -S.
```

Use CMake build, Or choose your platform's make tools to build, such as `msbuild` in windows, `make` in linux. Cmake build command format:

```bash
/path/to/cmake --build /dir/to/build --config <Debug|Release> --target <all|some-target> -- -j <build-threads>
```

For example:

```bash
cmake --build ./build --config Debug --target all -- -j 10
```

Now, you can find `example.node` at `./build`.

### Binding modules

Test its functions in `index.js`

```javascript
const { Example } = require('bindings')('example.node');
const assert = require('assert');

const example = new Example(11);
assert.equal(example.GetValue(), 11);

example.SetValue(19);
assert.equal(example.GetValue(), 19);
```

### (Optional) Add type hints

Write types in `example.d.ts`:

```typescript
// example.d.ts
declare module 'example' {
    export class Example {
        constructor(value: Number);
        SetValue(value: Number);
        GetValue();
    }
}
```

And add type info in `index.js`:

```javascript
/// <reference path="./example.d.ts" />
const { Example } = require('bindings')('example.node');
// ...
```

# Authors

- [lonelyhentai](https://github.com/lonelyhentai)

# License

[MIT](./LICENSE) © Zhou Yeheng