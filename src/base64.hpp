#pragma once
#include <stdexcept>
#include <string>

namespace {
    char encode(int c) {
        constexpr char TABLE[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
        return TABLE[c];
    }

    unsigned char decode(char c) {
        if      (c == '=')             return 0;
        else if (c >= 'A' && c <= 'Z') return c - 'A';
        else if (c >= 'a' && c <= 'z') return c - 'a' + 26;
        else if (c >= '0' && c <= '9') return c - '0' + 52;
        else if (c == '+')             return 62;
        else if (c == '/')             return 63;
        else throw std::runtime_error(std::string("Invalid Base64 character: ") + c);
    }
} // namespace

inline std::string base64_encode(const std::string& raw) {
    std::string encoded;

    for (size_t i = 0; i < raw.size(); i += 3) {
        unsigned char a = raw[i];
        unsigned char b = i + 1 < raw.size() ? raw[i + 1] : 0;
        unsigned char c = i + 2 < raw.size() ? raw[i + 2] : 0;

        int s1 = (a >> 2) & 0b00111111;                             // 6 from a
        int s2 = ((a & 0b00000011) << 4) | ((b >> 4) & 0b00001111); // 2 from a + 4 from b
        int s3 = ((b & 0b00001111) << 2) | ((c >> 6) & 0b00000011); // 4 from b + 2 from c
        int s4 = c & 0b00111111;                                    // 6 from c

        encoded += encode(s1);
        encoded += encode(s2);
        encoded += i + 1 < raw.size() ? encode(s3) : '=';
        encoded += i + 2 < raw.size() ? encode(s4) : '=';
    }

    return encoded;
}

inline std::string base64_decode(const std::string& encoded) {
    if (encoded.size() % 4 != 0) throw std::runtime_error("Invalid base64 length");

    std::string decoded;

    for (size_t i = 0; i < encoded.size(); i += 4) {
        unsigned char a = decode(encoded[i]);
        unsigned char b = decode(encoded[i + 1]);
        unsigned char c = decode(encoded[i + 2]);
        unsigned char d = decode(encoded[i + 3]);

        int c1 = (a << 2) | ((b >> 4) & 0b00000011);                // 6 from a + 2 from b
        int c2 = ((b & 0b00001111) << 4) | ((c >> 2) & 0b00001111); // 4 from b + 4 from c
        int c3 = ((c & 0b00000011) << 6) | (d & 0b00111111);        // 2 from c + 6 from d

        decoded += (char) c1;
        if (encoded[i + 2] != '=') decoded += (char) c2;
        if (encoded[i + 3] != '=') decoded += (char) c3;
    }

    return decoded;
}
