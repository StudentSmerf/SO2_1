#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <string>

using namespace std;

void philosopher(int id, std::mutex* forks, int num_philosophers) {
    cout << "DP6" << endl;
    while (true) {
        cout << "DP7" << endl;
        unique_lock<std::mutex> left_fork(forks[id]);  
        cout << "DP8" << endl;
        this_thread::sleep_for(chrono::milliseconds(10)); 
        cout << "DP9" << endl;
        unique_lock<std::mutex> right_fork(forks[(id + 1) % num_philosophers]); 
        cout << "DP10" << endl;
        cout << "Philosopher " << id << " is eating." << endl;
        this_thread::sleep_for(chrono::milliseconds(100)); 
        cout << "DP11" << endl;
        cout << "Philosopher " << id << " finished eating." << endl;
    }
}

int main(int argc, char* argv[]) {
    
    cout << "Dining Philosophers Problem" << endl;
    int num_philosophers = 5;
    try {
        num_philosophers = stoi(argv[1]);
    } catch (const std::exception& e) {
        cerr << "Invalid number of philosophers: " << e.what() << endl;
        return 1;
    }
    //check if num_philosophers is set corectly
    cout << "Number of philosophers: " << num_philosophers << endl;

    if (num_philosophers < 2) {  
        cerr << "Number of philosophers can't be less than 2!" << endl;
        return 1;
    }
    cout << "DP1" << endl;
    std::mutex* forks = new std::mutex[num_philosophers];  
    cout << "DP2" << endl;
    thread* threads = new thread[num_philosophers];  
    cout << "DP3" << endl;
    for (int i = 0; i < num_philosophers; ++i) {
        threads[i] = thread(philosopher, i, forks, num_philosophers);
    }
    cout << "DP4" << endl;
    for (int i = 0; i < num_philosophers; ++i) {
        threads[i].join();
    }
    cout << "DP5" << endl;

    delete[] forks;
    delete[] threads;
    cout << "Finish" << endl;
    return 0;
}
