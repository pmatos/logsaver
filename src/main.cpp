#include <iostream>
#include <string>
#include <regex>
#include <cassert>

int main(void) {

    size_t repcnt = 0; // repetitions counter
    std::string lastline;
    std::string lastlogline; // just the description part of lastline
    for(std::string line; std::getline(std::cin, line); ) {
        // regex for log file lines
        // example:
        // Aug 12 17:47:10 andromeda kernel: [drm:amdgpu_ih_process [amdgpu]] amdgpu_ih_process: rptr 51536, wptr 51552
        std::regex re("([[:alnum:]]{3} \\d{2} \\d{2}:\\d{2}:\\d{2}) [[:graph:]]+ [[:graph:]]+: (.+)");

        std::smatch sm;
        if (!std::regex_match(line, sm, re)) {
            std::cerr << "Failed to match line: " << line << std::endl;
            return 1;
        }
        assert(sm.size() == 3);

        if (lastlogline == sm[2]) {
            repcnt++;
            continue;
        }

        std::cout << lastline << std::endl;
        if (repcnt > 0) {
            std::cout << sm[1] << ": (repeated " << repcnt << " times)" << std::endl; 
        }
        
        repcnt = 0;
        lastline = line;
        lastlogline = sm[2];
    }

    std::cout << lastline << std::endl;
    
    return 0;
}