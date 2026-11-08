#include "machine.h"
#include "Programs.h"
#include <iomanip>
#include <iostream>
using namespace std;

void printScreen(const Machine& m){
     cout << "Screen output: "<< endl;
     vector<int> out = m.getScreen().getOutput();
     if (out.empty()){
        cout << "  (empty)" << endl;
     }
     else{
        for (int v : out){
            cout << " 0x" << hex << uppercase << setw(2) << setfill('0') << v << dec << endl;
        }
     }
     cout << "Last value: 0x" << hex << uppercase << setw(2) << setfill('0') << m.getScreen().getLastValue()<< dec << endl;
}

void ViewMenu(){
    cout << "===== Vole Machine =====" << endl;
    cout << "1. Load program1: sum 1 to 5" << endl;
    cout << "2. Load program2: multiply 6 x 3" << endl;
    cout << "3. Load program3: load 0x0A and display" << endl;
    cout << "4. Load program4: Add 3+5" << endl;
    cout << "5. Load program5: OR 1 | 5" << endl;
    cout << "6. Load program6: AND 3 & 1" << endl;
    cout << "7. Load program7: XOR 6 ^ 3" << endl;
    cout << "8. Load program8: Load 0x0F and display" << endl;
    cout << "9. Load program9: Add 1+3" << endl;
    cout << "10. Load program10: Add 5+10" << endl;
    cout << "11. Load all programs: " << endl;
    cout << "12. Run (execute until HALT)" << endl;
    cout << "13. Step (execute one instruction)" << endl;
    cout << "14. Reset machine" << endl;
    cout << "15. Show screen output" << endl;
    cout << "16. Show registers" << endl;
    cout << "17. Show memory " << endl;
    cout << "18. Exit" << endl;
}

int getChoice() {
  int choice;
  while (true) {
    cin >> choice;
    if (!cin.fail()) {
      cin.ignore(10000, '\n');
      return choice;
    }
    cin.clear();
    cin.ignore(10000, '\n');
    cout << "Invalid input. Please enter a number between 1 and 18." << endl;
  }
}

int main() {
   Machine machine;
   int choice;
   bool hasProgram = false;

   do{
      ViewMenu();
      choice = getChoice();

      if (choice == 18){
        cout << "Exiting the program." << endl;
        break;
      }

      switch (choice){
      case 1:
          machine.reset();
          machine.loadProgram(Programs::program1());
          hasProgram = true;
          break;
      case 2:
          machine.reset();
          machine.loadProgram(Programs::program2());
          hasProgram = true;
          break;
      case 3:
          machine.reset();
          machine.loadProgram(Programs::program3());
          hasProgram = true;
          break;
      case 4:
          machine.reset();
          machine.loadProgram(Programs::program4());
          hasProgram = true;
          break;
      case 5:
          machine.reset();
          machine.loadProgram(Programs::program5());
          hasProgram = true;
          break;
      case 6:
          machine.reset();
          machine.loadProgram(Programs::program6());
          hasProgram = true;
          break;
      case 7:
          machine.reset();
          machine.loadProgram(Programs::program7());
          hasProgram = true;
          break;
      case 8:
          machine.reset();
          machine.loadProgram(Programs::program8());
          hasProgram = true;
          break;
      case 9:
          machine.reset();
          machine.loadProgram(Programs::program9());
          hasProgram = true;
          break;
      case 10:
          machine.reset();
          machine.loadProgram(Programs::program10());
          hasProgram = true;
          break;
      case 11:
          machine.reset();
          static int addr ;
          addr = 0;
          for (const auto& p : Programs::allPrograms()){
              machine.loadProgram(p , addr);
              addr += static_cast<int>(p.size()) * 2;
          }
          hasProgram = true;
          break;
      case 12:
          if(!hasProgram){
             cout << "No program loaded. Please choose 1 to 10 first." << endl;
             break;
          }
          machine.run();
          printScreen(machine);
          break;
      case 13:
          if(!hasProgram){
             cout << "No program loaded. Please choose 1 to 10 first." << endl;
             break;
          }
          machine.step();
          cout << "Executed one instruction. Use 15-17 to inspect."<< endl;
          break;
      case 14:
          machine.reset();
          cout << "Machine reset."<< endl;
          break;
      case 15:
          printScreen(machine);
          break;
      case 16:
          cout << machine.getRegisters().dump()<<endl;
          break;
      case 17:
          cout << machine.getMemory().dump() << endl;
          break;
      default:
          cout << "Invalid choice. Please try again." << endl;
      }
   }while(choice != 18);

   return 0;
}