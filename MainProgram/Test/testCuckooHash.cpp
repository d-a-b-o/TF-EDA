#include "../Model/CuckooHashTable.h"
#include <iostream>

int main() {
  // Create an instance of CuckooHashTable
  CuckooHashTable hashTable;

  // Insert some test data
  for (int i = 0; i < 100; i++) {
    Data temp = Data(i, i);
    hashTable.insert(temp);
    cout << "Insercion " << i << "." << endl;
  }

  // Print the current state of the hash table
  std::cout << "Hash table after inserting 5 elements:" << std::endl;
  hashTable.print();

  // Test searching for existing keys
  std::cout << "\nSearching for keys:" << std::endl;
  for (u_int32_t key = 1; key <= 100; key++) {
    Data result = hashTable.search(key);
    if (result.key != 0) {
      std::cout << "Key " << key << " found with data: " << result.data
                << std::endl;
    } else {
      std::cout << "Key " << key << " not found." << std::endl;
    }
  }

  // Test searching for a non-existing key
  std::cout << "\nSearching for a non-existing key (10):" << std::endl;
  Data result = hashTable.search(10);
  if (result.key != 0) {
    std::cout << "Key 10 found with data: " << result.data << std::endl;
  } else {
    std::cout << "Key 10 not found." << std::endl;
  }

  return 0;
}
