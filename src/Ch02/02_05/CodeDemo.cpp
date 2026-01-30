// Secure Coding in C++
// Challenge 02_05
// Secure a data parsing function, by Eduardo Corpeño

#include <iostream>
#include <string>
#include <map>
#include <sstream>

std::map<std::string, std::string> parseSettings(const std::string& input){
    std::map<std::string, std::string> result;
    std::istringstream ss(input);
    std::string pair;

    while (std::getline(ss, pair, ',')){
        size_t eq = pair.find('=');

        // Unsafe: no check for missing '=', empty keys or values, 
        // duplicate keys, spaces, or non-numeric values.
        
        if (eq == std::string::npos || eq == 0 || eq == pair.length() - 1) {
            continue; // Skip invalid pairs
        }

        std::string key = pair.substr(0, eq);
        std::string value = pair.substr(eq + 1);

        if (key.find(' ') != std::string::npos || value.find(' ') != std::string::npos) {
            continue; // Skip pairs with spaces
        }

        if (value.find_first_not_of("0123456789") != std::string::npos) {
            continue; // Skip non-numeric values
        }

        if(result.find(key) != result.end()) {
            continue; // Skip duplicate keys
        }

        result[key] = value; // silently overwrites
    }
    return result;
}

int main(){
    std::string rawInput;
    std::cout << "Enter settings (key=value,key=value,...): ";
    std::getline(std::cin, rawInput);

    auto settings = parseSettings(rawInput);

    std::cout << "Parsed settings:\n";
    for (const auto& [k, v] : settings)
        std::cout << k << ": " << v << "\n";

    std::cout << std::endl;
    return 0;
}
