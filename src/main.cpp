#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>
#include "base64.hpp"

int help(int exitCode = EXIT_FAILURE) {
    std::cout << "usage: base64 [options] [input...]\n"
                 "Options:\n"
                 "  -e, --encode          Encode input (default)\n"
                 "  -d, --decode          Decode input\n"
                 "  -i, --input  <path>   Read input from file\n"
                 "  -o, --output <path>   Write output to file\n"
                 "  -h, --help            Show this help message\n";
    return exitCode;
}

std::string read_file(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) throw std::runtime_error("Failed to read file: " + path);
    return {std::istreambuf_iterator<char>(file), {}};
}

void write_file(const std::string& path, const std::string& data) {
    std::ofstream file(path, std::ios::binary);
    if (!file.is_open()) throw std::runtime_error("Failed to write file: " + path);
    file << data;
}

int run(int argc, char** argv) {
    std::vector<std::string> args{argv + 1, argv + argc};

    std::string inPath;
    std::string outPath;
    std::string input;
    bool isEncoding = true;

    for (auto it = args.begin(); it != args.end(); ++it) {
        if (*it == "-e" || *it == "--encode") {
            isEncoding = true;
        } else if (*it == "-d" || *it == "--decode") {
            isEncoding = false;
        } else if (*it == "-i" || *it == "--input") {
            if (std::next(it) == args.end()) {
                std::cerr << "Missing path after " << *it << "\n";
                return help();
            }
            inPath = *std::next(it);
        } else if (*it == "-o" || *it == "--output") {
            if (std::next(it) == args.end()) {
                std::cerr << "Missing path after " << *it << "\n";
                return help();
            }
            outPath = *std::next(it);
        } else if (*it == "-h" || *it == "--help") {
            return help(EXIT_SUCCESS);
        } else if (*it->begin() == '-') {
            std::cerr << "Unknown option: " << *it << '\n';
            return help();
        } else {
            input += *it;
        }
    }

    if (!inPath.empty()) input = read_file(inPath);

    // accept stdin
    if (input.empty()) {
        input.assign(std::istreambuf_iterator<char>(std::cin), {});
    }

    std::string result = isEncoding ? base64_encode(input) : base64_decode(input);

    if (outPath.empty())
        std::cout << result << '\n';
    else
        write_file(outPath, result);

    return EXIT_SUCCESS;
}

int main(int argc, char* argv[]) {
    try {
        return run(argc, argv);
    } catch (const std::exception& e) {
        std::cerr << "error: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
}
