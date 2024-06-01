#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

#define MAX_DEPARTMENTS 100
#define INF 99999 // Updated INF value to ensure correct initialization

// Structure to represent a department
typedef struct Department
{
    int beds;
    int equipment;
    int numPatients; // Number of patients in the department
} Department;

// Structure to represent a patient
typedef struct Patient
{
    char name[50];
    int department; // Department number where patient is allocated
} Patient;

// Function prototypes
void addEdge(int graph[][MAX_DEPARTMENTS], int u, int v, int weight);
void dijkstra(int graph[][MAX_DEPARTMENTS], int src, int numVertices, Department departments[], int dist[]);
void manageResources(int numVertices, Department departments[]);
void allocateResources(int numVertices, Department departments[], int from, int to, int dist[]);
int findNearestDepartment(int numVertices, Department departments[], int centralDepartment, int dist[]);
void displayPatientAllocations(Patient patients[], int numPatients);
void departPatient(Patient patients[], Department departments[], int *numPatients);
void showDepartmentResources(Department departments[], int numDepartments);

int main()
{
    int numDepartments;
    printf("Enter the number of departments: ");
    scanf("%d", &numDepartments);

    Department departments[MAX_DEPARTMENTS];

    // Initialize the adjacency matrix
    int graph[MAX_DEPARTMENTS][MAX_DEPARTMENTS];
    for (int i = 0; i < MAX_DEPARTMENTS; i++)
    {
        for (int j = 0; j < MAX_DEPARTMENTS; j++)
        {
            graph[i][j] = INF;
        }
    }

    // Adding departments and their resources
    for (int i = 0; i < numDepartments; i++)
    {
        printf("Enter the number of beds in department %d: ", i + 1);
        scanf("%d", &departments[i].beds);
        printf("Enter the number of equipment in department %d: ", i + 1);
        scanf("%d", &departments[i].equipment);
        departments[i].numPatients = 0; // Initialize the number of patients to 0
    }

    // Adding edges between departments
    int numEdges;
    printf("Enter the number of edges: ");
    scanf("%d", &numEdges);

    for (int i = 0; i < numEdges; i++)
    {
        int u, v, weight;
        printf("Enter edge (department1 department2 distance): ");
        scanf("%d %d %d", &u, &v, &weight);
        addEdge(graph, u - 1, v - 1, weight); // Adjusting index to start from 0
    }

    // Initially, allocate resources using Dijkstra's algorithm from a central department
    int src;
    printf("Enter the central department: ");
    scanf("%d", &src);
    src--; // Adjusting index to start from 0

    int dist[MAX_DEPARTMENTS];
    dijkstra(graph, src, numDepartments, departments, dist);

    int option;
    Patient patients[MAX_DEPARTMENTS];
    int numPatients = 0;

    do
    {
        printf("\nOptions:\n");
        printf("1. Allocate resources equally\n");
        printf("2. Allocate resources based on Dijkstra's shortest path\n");
        printf("3. Patient Entry\n");
        printf("4. Display Patient Allocations\n");
        printf("5. Depart a Patient\n");
        printf("6. Show current resources of each department and total resources and patients in each department\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            manageResources(numDepartments, departments);
            break;
        case 2:
            int from, to;
            printf("Enter source department and destination department for resource allocation: ");
            scanf("%d %d", &from, &to);
            from--; // Adjusting index to start from 0
            to--;   // Adjusting index to start from 0
            allocateResources(numDepartments, departments, from, to, dist);
            break;
        case 3:
            // Patient entry
            printf("\nPatient Entry:\n");
            printf("Enter patient name: ");
            scanf("%s", patients[numPatients].name);

            // Find nearest department
            int nearestDepartment = findNearestDepartment(numDepartments, departments, src, dist);
            if (nearestDepartment != -1)
            {
                printf("Allocating patient %s to department %d\n", patients[numPatients].name, nearestDepartment + 1); // Adjusting index to start from 1
                departments[nearestDepartment].beds--;                                                                 // Decrease available beds in the department
                departments[nearestDepartment].equipment--;                                                            // Decrease available equipment in the department
                departments[nearestDepartment].numPatients++;                                                          // Increment number of patients in the department
                patients[numPatients].department = nearestDepartment + 1;                                              // Store allocated department number
                numPatients++;
            }
            else
            {
                printf("No suitable department found for patient %s\n", patients[numPatients].name);
            }
            break;
        case 4:
            // Display patient allocations
            displayPatientAllocations(patients, numPatients);
            break;
        case 5:
            // Depart a patient
            departPatient(patients, departments, &numPatients);
            break;
        case 6:
            // Show current resources of each department and total resources and patients in each department
            showDepartmentResources(departments, numDepartments);
            break;
        case 7:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid option. Please try again.\n");
        }
    } while (option != 7);

    return 0;
}

// Function to add an edge between two departments
void addEdge(int graph[][MAX_DEPARTMENTS], int u, int v, int weight)
{
    graph[u][v] = weight;
    graph[v][u] = weight; // Assuming the graph is undirected
}

// Dijkstra's algorithm to find the shortest path
void dijkstra(int graph[][MAX_DEPARTMENTS], int src, int numVertices, Department departments[], int dist[])
{
    int visited[numVertices];

    // Initialize distance array and visited array
    for (int i = 0; i < numVertices; i++)
    {
        dist[i] = INF;
        visited[i] = 0;
    }

    dist[src] = 0; // Distance from source to itself is 0

    // Find shortest path for all vertices
    for (int count = 0; count < numVertices - 1; count++)
    {
        int minDist = INF, minIndex;

        // Pick the minimum distance vertex from the set of vertices not yet processed
        for (int v = 0; v < numVertices; v++)
        {
            if (!visited[v] && dist[v] <= minDist)
            {
                minDist = dist[v];
                minIndex = v;
            }
        }

        visited[minIndex] = 1; // Mark the picked vertex as processed

        // Update dist value of the adjacent vertices of the picked vertex
        for (int v = 0; v < numVertices; v++)
        {
            if (!visited[v] && graph[minIndex][v] && dist[minIndex] != INF &&
                dist[minIndex] + graph[minIndex][v] < dist[v])
            {
                dist[v] = dist[minIndex] + graph[minIndex][v];
            }
        }
    }

    // Print the shortest distance from source to all other departments
    printf("Shortest distances from department %d to all other departments:\n", src + 1); // Adjusting index to start from 1
    for (int i = 0; i < numVertices; i++)
    {
        printf("Department %d: %d\n", i + 1, dist[i]); // Adjusting index to start from 1
    }
}

// Function to find the nearest department from a central department
int findNearestDepartment(int numVertices, Department departments[], int centralDepartment, int dist[])
{
    int minDistance = INF;
    int nearestDepartment = -1;

    for (int i = 0; i < numVertices; i++)
    {
        if (departments[i].beds > 0 && departments[i].equipment > 0 && dist[i] < minDistance)
        {
            minDistance = dist[i];
            nearestDepartment = i;
        }
    }

    return nearestDepartment;
}

// Function to manage resources based on distances
void manageResources(int numVertices, Department departments[])
{
    // Calculate total resources available
    int totalBeds = 0, totalEquipment = 0;
    for (int i = 0; i < numVertices; i++)
    {
        totalBeds += departments[i].beds;
        totalEquipment += departments[i].equipment;
    }

    // Calculate average resources
    int averageBeds = totalBeds / numVertices;
    int averageEquipment = totalEquipment / numVertices;

    // Allocate equal resources to each department
    for (int i = 0; i < numVertices; i++)
    {
        departments[i].beds = averageBeds;
        departments[i].equipment = averageEquipment;
    }

    // Print the adjusted resources
    printf("\nAdjusted resources based on equal allocation:\n");
    for (int i = 0; i < numVertices; i++)
    {
        printf("Department %d - Beds: %d, Equipment: %d\n", i + 1, departments[i].beds, departments[i].equipment); // Adjusting index to start from 1
    }

    // Print total resources available
    printf("\nTotal resources available across all departments:\n");
    printf("Total Beds: %d, Total Equipment: %d\n", totalBeds, totalEquipment);
}

// Function to allocate resources based on Dijkstra's shortest path
void allocateResources(int numVertices, Department departments[], int from, int to, int dist[])
{
    // Print the shortest path from source to destination
    printf("Shortest path from department %d to department %d:\n", from + 1, to + 1); // Adjusting index to start from 1
    int current = to;
    while (current != from)
    {
        printf("%d <- ", current + 1); // Adjusting index to start from 1
        current = dist[current];       // Move to the previous node in the shortest path
    }
    printf("%d\n", from + 1); // Adjusting index to start from 1

    // Assuming from and to departments are valid
    // Allocate beds and equipment from 'from' department to 'to' department
    departments[to].beds += departments[from].beds;
    departments[to].equipment += departments[from].equipment;

    // Deduct allocated resources from 'from' department
    departments[from].beds = 0;
    departments[from].equipment = 0;

    printf("\nResources allocated from department %d to department %d\n", from + 1, to + 1); // Adjusting index to start from 1

    // Print updated resources
    printf("\nUpdated resources:\n");
    for (int i = 0; i < numVertices; i++)
    {
        printf("Department %d - Beds: %d, Equipment: %d\n", i + 1, departments[i].beds, departments[i].equipment); // Adjusting index to start from 1
    }
}

// Function to display department numbers where each patient is allocated
void displayPatientAllocations(Patient patients[], int numPatients)
{
    printf("\nPatient Allocations:\n");
    for (int i = 0; i < numPatients; i++)
    {
        printf("Patient %s is allocated to department %d\n", patients[i].name, patients[i].department);
    }
}

// Function to depart a patient from a department
void departPatient(Patient patients[], Department departments[], int *numPatients)
{
    printf("\nDepart a Patient:\n");

    // Print the list of patients along with their index
    printf("Index\tPatient Name\n");
    for (int i = 0; i < *numPatients; i++)
    {
        printf("%d\t%s\n", i + 1, patients[i].name); // Adjusting index to start from 1
    }

    printf("Enter the index of the patient to depart (1-%d): ", *numPatients);
    int index;
    scanf("%d", &index);

    if (index >= 1 && index <= *numPatients)
    {
        index--;                                         // Adjusting index to access array element
        int department = patients[index].department - 1; // Adjusting department index to access array element
        departments[department].beds++;                  // Increase available beds in the department
        departments[department].equipment++;             // Increase available equipment in the department
        departments[department].numPatients--;           // Decrement number of patients in the department

        printf("Patient %s departed successfully.\n", patients[index].name);

        // Move the last patient to the position of the departed patient
        patients[index] = patients[*numPatients - 1];

        // Decrement the number of patients
        (*numPatients)--;
    }
    else
    {
        printf("Invalid index.\n");
    }
}

// Function to show current resources of each department and total resources and patients in each department
void showDepartmentResources(Department departments[], int numDepartments)
{
    printf("\nCurrent Resources of Each Department:\n");
    for (int i = 0; i < numDepartments; i++)
    {
        printf("Department %d - Beds: %d, Equipment: %d, Patients: %d\n",
               i + 1, departments[i].beds, departments[i].equipment, departments[i].numPatients); // Adjusting index to start from 1
    }

    int totalBeds = 0, totalEquipment = 0, totalPatients = 0;
    for (int i = 0; i < numDepartments; i++)
    {
        totalBeds += departments[i].beds;
        totalEquipment += departments[i].equipment;
        totalPatients += departments[i].numPatients;
    }

    printf("\nTotal Resources and Patients Across All Departments:\n");
    printf("Total Beds: %d, Total Equipment: %d, Total Patients: %d\n", totalBeds, totalEquipment, totalPatients);
}
final code
