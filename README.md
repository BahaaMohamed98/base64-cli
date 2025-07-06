# 🧬 base64-cli

A minimal and efficient Base64 encoder/decoder written in C++.  
Supports file input/output, piped stdin, and argument input.

> 🔧 No dependencies. Cross-platform. Fast. Ideal for quick scripts or lightweight CLI usage.

## ✨ Features

- 📝 Encode or decode Base64
- 📂 Input from file, argument, or `stdin`
- 📤 Output to file or `stdout`
- 🚫 Graceful error handling
- 🧪 Useful for piping, scripting, and quick testing

## 📋 Examples

### 🔤 Encode a string

```bash
./base64 "hello"
# → aGVsbG8=
```

### 📝 Encode a file

```bash
./base64 -i hello.txt
```

### 🧪 Pipe input via stdin

```bash
echo -n "hello" | ./base64
```

### 🔓 Decode from file to binary output

```bash
./base64 -d -i encoded.txt -o image.png
```

### ❔ Show help

```bash
./base64 --help
```

## 🛠️ Build

### Using CMake

```bash
cmake -B build
cd build
cmake --build .
./base64 "hello"
```

### Or manually

```bash
g++ -std=c++17 -O2 -o base64 ./src/main.cpp
```

## 📦 Usage

```bash
base64 [options] [input...]
```

### Options

| Option           | Description            |
| ---------------- | ---------------------- |
| `-e`, `--encode` | Encode input (default) |
| `-d`, `--decode` | Decode input           |
| `-i <path>`      | Read input from file   |
| `-o <path>`      | Write output to file   |
| `-h`, `--help`   | Show help message      |

## 🔐 License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

