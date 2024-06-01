# HospitAI: Intelligent Resource and Patient Management System for Hospitals

## Project Overview

**HospitAI** is an intelligent system designed to efficiently manage hospital resources and patient allocations. Using advanced algorithms like Dijkstra's shortest path algorithm, the system ensures optimal use of hospital beds, equipment, and other resources, providing a streamlined approach to patient management.

## Features

1. **Resource Allocation**:
   - Equitable distribution of beds and equipment across departments.
   - Dynamic allocation based on shortest path calculations.

2. **Patient Management**:
   - Automatic patient allocation to departments with available resources.
   - Patient entry, departure, and reassignment functionalities.

3. **Resource Monitoring**:
   - Real-time display of available resources and patient count in each department.
   - Detailed overview of total resources across the hospital.

4. **User-Friendly Interface**:
   - Intuitive menu-driven console application.
   - Easy-to-follow prompts for managing resources and patient information.

## Getting Started

### Prerequisites

- A C compiler (e.g., GCC)
- Basic knowledge of C programming and terminal/command-line usage

### Installation

1. **Clone the repository**:
   ```sh
   git clone https://github.com/yourusername/HospitAI.git
   cd HospitAI
   ```

2. **Compile the program**:
   ```sh
   gcc -o hospitAI main.c
   ```

3. **Run the program**:
   ```sh
   ./hospitAI
   ```

## Usage

Upon running the program, you will be prompted to enter the number of departments and their respective resources (beds and equipment). You can then define the connections between departments and manage resources through a series of options:

1. **Allocate Resources Equally**: Distribute beds and equipment evenly among all departments.
2. **Allocate Resources Based on Dijkstra's Algorithm**: Allocate resources dynamically based on shortest paths.
3. **Patient Entry**: Enter new patient information and allocate them to the nearest department with available resources.
4. **Display Patient Allocations**: View current patient allocations across departments.
5. **Depart a Patient**: Remove a patient from the system, freeing up resources.
6. **Show Department Resources**: Display current resources and patient count for each department.
7. **Exit**: Exit the program.

## Example

```sh
Enter the number of departments: 3
Enter the number of beds in department 1: 10
Enter the number of equipment in department 1: 5
Enter the number of beds in department 2: 8
Enter the number of equipment in department 2: 3
Enter the number of beds in department 3: 6
Enter the number of equipment in department 3: 4
Enter the number of edges: 2
Enter edge (department1 department2 distance): 1 2 7
Enter edge (department1 department3 distance): 2 3 10
Enter the central department: 1

Options:
1. Allocate resources equally
2. Allocate resources based on Dijkstra's shortest path
3. Patient Entry
4. Display Patient Allocations
5. Depart a Patient
6. Show current resources of each department and total resources and patients in each department
7. Exit
Enter your choice:
```

## Contributing

Contributions are welcome! Please follow these steps:

1. Fork the repository.
2. Create your feature branch (`git checkout -b feature/AmazingFeature`).
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`).
4. Push to the branch (`git push origin feature/AmazingFeature`).
5. Open a Pull Request.

