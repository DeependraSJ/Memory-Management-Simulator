#include <iostream>
#include <string>
#include <sstream>
#include "virtual_memory_manager.h"
#include "memoryManage.h"
#include "allocator.h"
#include "allocator/worst_fit.cpp"
#include "allocator/first_fit.cpp"
#include "allocator/best_fit.cpp"
#include "cachelevel.h"
using namespace std;

class first_fit_allocator;
class best_fit_allocator;
class worst_fit_allocator;

int main(){
    memoryManager* memo = nullptr;
    first_fit_allocator first_fit;
    best_fit_allocator best_fit;
    worst_fit_allocator worst_fit;
    string line;
    
    cout << "memory simulator has run, input commands (init/malloc/set/free/exit/dump/stats)\n";

    cache_level L1("L1", 1024, 32, 2); 
    cache_level L2("L2", 4096, 64, 8); 
    virtual_memory_manager vM(65536, 16384, 512); 
    vM.attach_caches(&L1, &L2);

    while (true) {
        cout << "> ";
        getline(cin, line);
        stringstream take(line);
        string command;
        take >> command;

        if (command == "exit") break;
        else if (command == "set") {
            string word, type;
            take >> word >> type;
            if (memo == nullptr) {
                cout << "memory not initialized!\n\n";
                continue;
            }
            
            if (type == "first_fit") {
                memo->set_allocator(&first_fit);
                cout << "allocator set to first_fit\n\n";
            } 
            else if (type == "best_fit") {
                memo->set_allocator(&best_fit);
                cout << "allocator set to best_fit\n\n";
            } 
            else if (type == "worst_fit") {
                memo->set_allocator(&worst_fit);
                cout << "allocator set to worst_fit\n\n";
            } 
            else {
                cout << "unknown allocator!\n\n";
            }
        }
        else if (command == "init") {
            size_t size;
            take >> size;
            if (memo != nullptr) {
                delete memo;
            }
            memo = new memoryManager(size);
            cout << "memory initialized with size " << size << " units\n\n";
        }
        else if (command == "free") {
            int id;
            take >> id;
            if (memo == nullptr) {
                cout << "memory not initialized!\n\n";
                continue;
            }
            
            memo->free_block(id);
        }
        else if (command == "malloc") {
            size_t size;
            take >> size;

            if (memo == nullptr) {
                cout << "memory not initialized!\n\n";
                continue;
            }

            int id = memo->malloc_block(size);
            if (id == -1) {
                cout << "allocation failed!\n\n";
            } else {
                cout << "allocated block id=" << id << "\n\n";
            }
        }
        else if (command == "dump") {
            if (memo == nullptr) {
                cout << "memory not initialized!\n\n";
                continue;
            }
            memo->dump_memory();
        }
        else if (command == "access") {
            size_t addr;
            take >> addr;
            vM.access(addr);
        }
        else if (command == "stats") {
            vM.print_stats();
            L1.print_stats();
            L2.print_stats();
            if (memo == nullptr) {
                cout << "memory not initialized!\n\n";
                continue;
            }
            memo->print_stats();
        }
        else {
            cout << "unknown command!\n\n";
        }
    }
    delete memo;
    cout << "exited\n\n";
    return 0;
}
