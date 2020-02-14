#include <string>
#include <iostream>
#include <vector>

std::vector<int> find_all(std::string text, std::string term) {
    std::vector<int> all_pos;
    
    int pos = -1;
    do {
        pos = text.find(term, pos + 1);
        if (pos != std::string::npos) {
            all_pos.push_back(pos);
        }
    } while (pos != std::string::npos);
    
    return all_pos;
}

int main() {
    std::string line, term;
    
    std::getline(std::cin, line);
    std::cin >> term;
    
    auto pos = find_all(line, term);
    for (auto it = pos.begin(); it != pos.end(); it++) {
        std::cout << "Encontrado em " << *it << "\n";
    }
    
    return 0;
}

