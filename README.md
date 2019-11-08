# FastReader

[![Version][]]() [![Tests][]]() [![License][]]()

[Version]:		   https://img.shields.io/badge/Version-v1.0-blue
[Tests]:		   https://img.shields.io/badge/Tests-passed-brightgreen
[License]:		   https://img.shields.io/badge/License-GNU%20GPL%20v.3-blue
[code guidelines]: https://docs.microsoft.com/en-gb/windows/win32/stg/coding-style-conventions

FastReader is a C++ library for Windows that provides fast file reading.

### Usage

```cpp
//
// Usage is very simple:
//

CFileHandler file( szFileName );  // szFileName is a LPCWSTR string

// Now just iterate over each line:
for(const auto& line : file )
{
	// ...
}

// You don't need to close file
```

### Test results

```
[----------] 2 tests from Timing
[ RUN      ] Timing.CFileHandler

CFileHandler: 56700 ns.

[       OK ] Timing.CFileHandler (1 ms)
[ RUN      ] Timing.fstream

std::ifstream: 241000 ns.

[       OK ] Timing.fstream (3 ms)
[----------] 2 tests from Timing (11 ms total)
```

### Contributing

First of all, thanks for taking time for contributing :)

> ⚠ **Attention\!** If you don't follow [code guidelines][], your pull-request will be declined anyway. 
Carefully read PEP conventions. It is highly required to make our code cleaner and more understandable.

The only way you can contribute is:
- fork this repo to your GitHub
- make some changes and improvements
- make pull request to this main repo

> 👉 **Note**: All the pull-requests will be strictly checked and reviewed before being accepted or declined. All external 
pull-requests have the same scrutiny for quality, coding standards, performance, globalization, accessibility, and 
compatibility as those of me.