#include <iostream>
// #include <thread>
#include <dirent.h>
#include <string>
#include <utility>
#include <vector>
#include <fstream>

// class ThreadGuard {
//     private:
//         std::thread& t;
//     public:
//         explicit ThreadGuard(std::thread& t_) : t(t_) {}

//         ~ThreadGuard() {
//             if (t.joinable()){
//                 t.join();
//             }
//         }
// };

class Worker {

};

class Master {
    private:
        std::string path;
    public:
        bool create_file(std::string& fileName);
        bool delete_file(std::string& fileName) {}
        void present_display(){
            bool run = true;
            while (run) {
                std::cout << "--------------  Press 1 to add a file --------------- " << std::endl;
                std::cout << "--------------  Press 2 to delete a file  --------------- " << std::endl;
                int choice;
                std::string fileName;
                std::cout << "Enter your choice:: ";
                std::cin >> choice;
                std::cout << "Enter the fileName:: ";
                std::cin >> fileName;
                if (choice == 1)
                    run = create_file(fileName);
                else if (choice == 2)
                    run = delete_file(fileName);

            }
        }
        explicit Master(std::string p) : path(p) {}
};

bool Master::create_file(std::string& fileName) {
    DIR* pdir;
    struct dirent* entry;
    if (pdir = opendir(path.c_str())) {
    while(entry = readdir(pdir)) {
        std::string each(entry->d_name);

        if (not each.compare(fileName)){  // if file is already present
            std::cout << "File is already present" << std::endl;
            return false;
        }
    }
    fileName = path + "/" + fileName;
    std::ofstream out(fileName);
    out.close();
    closedir(pdir);
    return true;
   }
}

//////////////////////////////   Thread Program ///////////////////////////////////////
// std::vector<std::string> files;


// std::pair<int, int> list_files(const std::string& path, const std::string& ext) {
//    DIR* pdir;
//    struct dirent* entry;
//    static int totalFiles;
//    static int allowedFiles;
//    auto display = [] (std::string str, std::string ext) {
//         return (str.size() >= ext.size()) and (str.compare(str.size() - ext.size(), ext.size(), ext) == 0);
//    };

//    if (pdir = opendir(path.c_str())) {
//     while(entry = readdir(pdir)) {
//         std::string each(entry->d_name);
//         totalFiles++;
//         if (each.compare(".") and each.compare("..") and display(each, ext)){
//             allowedFiles++;
//             // std::cout << each << std::endl;
//             files.push_back(each);
//         }
//     }
//     closedir(pdir);
//    }
//    return std::make_pair(totalFiles, allowedFiles);
// }

// void print(auto c) {
//     static int af;
//     if (af != c.second) {
//         af = c.second;
//         for (auto each : files)
//             std::cout << each << std::endl;
//         std::cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
//         std::cout << "Total Files: " << c.first << std::endl;
//         std::cout << "Files Displayed: " << c.second << std::endl;
//         std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
//     }
// }


int main(){
    // const char* c = "Hello";
    // std::cout << c << std::endl;
    const std::string p("C:/Users/g514549/Desktop/cli");
    // const std::string e("py");
    // auto counts = list_files(p, e);
    // while(true)
    //     print(counts);
    Master m {p};
    m.present_display();
    return 0;
}
