#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

struct Car {
  string id;
  string brand;
  string model;
  string year;
  string price;

  string to_string() const {
    return id + "|" + brand + "|" + model + "|" + year + "|" + price;
  }

  static Car from_string(const string &data) {
    Car car;
    stringstream ss(data);
    getline(ss, car.id, '|');
    getline(ss, car.brand, '|');
    getline(ss, car.model, '|');
    getline(ss, car.year, '|');
    getline(ss, car.price, '|');
    return car;
  }
};

void loadDatabase(const string &filename, Car *&cars, int &count) {
  ifstream file(filename);
  if (!file.is_open()) {
    cerr << "Unable to open file: " << filename << endl;
    return;
  }

  count = 0;
  string line;
  while (getline(file, line)) {
    count++;
  }
  file.clear();
  file.seekg(0, ios::beg);

  cars = new Car[count];
  int index = 0;
  while (getline(file, line)) {
    cars[index++] = Car::from_string(line);
  }

  file.close();
}

void saveDatabase(const string &filename, Car *cars, int count) {
  ofstream file(filename);
  if (!file.is_open()) {
    cerr << "Unable to open file: " << filename << endl;
    return;
  }

  for (int i = 0; i < count; ++i) {
    file << cars[i].to_string() << endl;
  }

  file.close();
}

void addCar(Car *&cars, int &count) {
  Car *newCars = new Car[count + 1];

  for (int i = 0; i < count; ++i) {
    newCars[i] = cars[i];
  }

  cout << "Enter car ID: ";
  cin >> newCars[count].id;
  cout << "Enter car brand: ";
  cin.ignore();
  getline(cin, newCars[count].brand);
  cout << "Enter car model: ";
  getline(cin, newCars[count].model);
  cout << "Enter car year: ";
  getline(cin, newCars[count].year);
  cout << "Enter car price: ";
  getline(cin, newCars[count].price);

  delete[] cars;
  cars = newCars;
  ++count;
}

void editCar(Car *cars, int count) {
  string id;
  cout << "Enter car ID to edit: ";
  cin >> id;

  for (int i = 0; i < count; ++i) {
    if (cars[i].id == id) {
      cout << "Enter new car brand: ";
      cin.ignore();
      getline(cin, cars[i].brand);
      cout << "Enter new car model: ";
      getline(cin, cars[i].model);
      cout << "Enter new car year: ";
      getline(cin, cars[i].year);
      cout << "Enter new car price: ";
      getline(cin, cars[i].price);
      return;
    }
  }

  cout << "Car ID not found." << endl;
}

void deleteCar(Car *&cars, int &count) {
  string id;
  cout << "Enter car ID to delete: ";
  cin >> id;

  int index = -1;
  for (int i = 0; i < count; ++i) {
    if (cars[i].id == id) {
      index = i;
      break;
    }
  }

  if (index == -1) {
    cout << "Car ID not found." << endl;
    return;
  }

  Car *newCars = new Car[count - 1];
  for (int i = 0, j = 0; i < count; ++i) {
    if (i != index) {
      newCars[j++] = cars[i];
    }
  }

  delete[] cars;
  cars = newCars;
  --count;
}

void searchCar(const Car *cars, int count) {
  string id;
  cout << "Enter car ID to search: ";
  cin >> id;

  for (int i = 0; i < count; ++i) {
    if (cars[i].id == id) {
      cout << "ID: " << cars[i].id << endl;
      cout << "Brand: " << cars[i].brand << endl;
      cout << "Model: " << cars[i].model << endl;
      cout << "Year: " << cars[i].year << endl;
      cout << "Price: " << cars[i].price << endl;
      return;
    }
  }

  cout << "Car ID not found." << endl;
}

void printCars(const Car *cars, int count) {
  for (int i = 0; i < count; ++i) {
    cout << "ID: " << cars[i].id << endl;
    cout << "Brand: " << cars[i].brand << endl;
    cout << "Model: " << cars[i].model << endl;
    cout << "Year: " << cars[i].year << endl;
    cout << "Price: " << cars[i].price << endl;
    cout << "---------------------" << endl;
  }
}

int main() {
  Car *cars = nullptr;
  int count = 0;
  const string filename = "car_database.txt";
  loadDatabase(filename, cars, count);

  while (true) {
    cout << "1. Add car" << endl;
    cout << "2. Edit car" << endl;
    cout << "3. Delete car" << endl;
    cout << "4. Search car" << endl;
    cout << "5. Print all cars" << endl;
    cout << "6. Exit" << endl;
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;

    switch (choice) {
    case 1:
      addCar(cars, count);
      saveDatabase(filename, cars, count);
      break;
    case 2:
      editCar(cars, count);
      saveDatabase(filename, cars, count);
      break;
    case 3:
      deleteCar(cars, count);
      saveDatabase(filename, cars, count);
      break;
    case 4:
      searchCar(cars, count);
      break;
    case 5:
      printCars(cars, count);
      break;
    case 6:
      delete[] cars;
      return 0;
    default:
      cout << "Invalid choice, try again." << endl;
    }
  }

  return 0;
}
