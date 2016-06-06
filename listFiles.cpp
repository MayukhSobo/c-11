#include <iostream>
// #include <thread>
#include <dirent.h>
#include <string>
#include <utility>

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

// class Worker {

// };

class Master {
    private:
        std::string path;
    public:
        bool create_file(std::string& fileName);
        std::string delete_file(std::string& fileName);
        void present_display(){
            std::cout << "--------------  Press 1 to add a file --------------- " << std::endl;
            std::cout << "--------------  Press 2 to delete a file  --------------- " << std::endl;
            int choice;
            std::string fileName;
            std::cin >> choice;
            std::cout << "Enter the fileName:: ";
            std::cin >> fileName;
            if (choice == 1)
                create_file(fileName);
            else if (choice == 2)
                delete_file(fileName);
        }
        explicit Master(std::string p) : path(p) {}
};



std::pair<int, int> list_files(const std::string& path, const std::string& ext) {
   DIR* pdir;
   struct dirent* entry;
   static int totalFiles;
   static int allowedFiles;
   auto display = [] (std::string str, std::string ext) {
        return (str.size() >= ext.size()) and (str.compare(str.size() - ext.size(), ext.size(), ext) == 0);
   };

   if (pdir = opendir(path.c_str())) {
    while(entry = readdir(pdir)) {
        std::string each(entry->d_name);
        totalFiles++;
        if (each.compare(".") and each.compare("..") and display(each, ext)){
            allowedFiles++;
            std::cout << each << std::endl;
        }
    }
    closedir(pdir);
   }
   return std::make_pair(totalFiles, allowedFiles);
}

int main(){
    // const char* c = "Hello";
    // std::cout << c << std::endl;
    const std::string p("C:/Users/g514549/Desktop/cli");
    const std::string e("py");
    auto counts = list_files(p, e);
    std::cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
    std::cout << "Total Files: " << counts.first << std::endl;
    std::cout << "Files Displayed: " << counts.second << std::endl;
    std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
    return 0;
}
