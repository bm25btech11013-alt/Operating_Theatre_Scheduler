

## About the Project

Scheduling surgeries in a hospital involves more than just deciding a date and time. Doctors, operating theatres and medical equipment all need to be available at the same time. When multiple surgeries are planned for the same day, managing these resources without conflicts becomes a challenge.

We developed this project using C++ and concepts from Data Structures and Algorithms to handle this problem.

The system allows users to register patients and their surgeries, assign doctors based on specialization and availability, select the required medical equipment and allocate operating theatres. It also identifies overlapping surgeries and ensures that they are assigned to different operating theatres.

Another part of the project focuses on comparing different scheduling approaches using Greedy Algorithms and Dynamic Programming, taking both the number and priority of surgeries into consideration.

## Features

- **Patient and Surgery Registration:** Add patient details along with the surgery name, date, starting time, duration and priority.
- **Automatic Doctor Allocation:** Assign doctors based on their specialization and check their availability before assigning them.
- **Equipment Management:** Select the required medical equipment and check whether sufficient units are available during the selected time slot.
- **Operating Theatre Allocation:** Automatically assign operating theatres while avoiding conflicts between overlapping surgeries.
- **Patient Details:** Retrieve patient and surgery information using a unique patient ID.
- **Doctor Schedule:** View all surgeries assigned to a particular doctor in chronological order.
- **Final OT Schedule:** Display all scheduled surgeries separately for each operating theatre.
- **Surgery Status:** Display whether a surgery is yet to be performed, ongoing or completed.
- **Conflict Graph:** Display connections between surgeries that overlap in time.
- **Algorithm Analysis:** Compare Greedy and Dynamic Programming approaches for scheduling surgeries.

## Data Structures Used

An important part of this project was deciding which data structures would be suitable for handling different types of information and scheduling requirements.

### 1. Structures (struct)

We used structures to keep related information together.

- **Doctor:** Stores the doctor's ID, name and specialization.
- **Equipment:** Stores the equipment ID, name and number of available units.
- **Surgery:** Stores patient details, surgery timings, assigned doctor, priority, selected equipment and operating theatre.

This makes it easier to organize and access information related to each entity.

### 2. Vectors

Vectors are used to maintain the lists of doctors, medical equipment and scheduled surgeries.

We chose vectors because the number of records can change as new surgeries are added. They also make it easy to traverse records, search for information and sort schedules.

### 3. Graphs (Adjacency List)

Graphs are used to represent conflicts between surgeries.

Each surgery is treated as a vertex. If two surgeries overlap in time, an edge is created between them. We use an adjacency list to store these connections.

This helps identify which surgeries cannot be assigned to the same operating theatre.

### 4. Graph Coloring

Graph coloring is used for operating theatre allocation.

Since overlapping surgeries are connected by an edge, they must be assigned different colours. Each colour represents an operating theatre.

This helps allocate theatres while avoiding conflicts between surgeries that take place at overlapping times.

### 5. Maps

We use a map to group surgeries according to their dates.

This is useful during algorithm analysis because scheduling calculations can be performed separately for each date instead of considering all surgeries together.

### 6. Sorting

Sorting is used at different stages of the project.

- Surgeries are arranged by date and starting time when displaying doctor schedules and the final OT schedule.
- For Activity Selection and Weighted Interval Scheduling, surgeries are sorted according to their finishing times.

This helps process surgeries in the required order for scheduling and analysis.

## Algorithms Used

### 1. Graph Coloring

We use a graph coloring approach to allocate operating theatres.

First, a conflict graph is created in which vertices represent surgeries and edges represent overlapping time slots.

The surgeries are processed in chronological order. Each surgery is assigned the first available colour that is not used by its already-colored neighbouring vertices.

Each colour corresponds to an operating theatre. The system currently supports a maximum of 12 operating theatres.

### 2. Greedy Algorithm – Activity Selection

This algorithm is used to find the maximum number of surgeries that can be performed without overlapping in a single operating theatre.

Surgeries are sorted according to their finishing times. The algorithm selects a surgery if its starting time is greater than or equal to the finishing time of the previously selected surgery.

The main idea is to select surgeries that finish earlier so that more surgeries can fit into the available time.

### 3. Dynamic Programming – Weighted Interval Scheduling

Unlike Activity Selection, this approach also considers the priority of surgeries.

Each priority is assigned a weight:

| Priority | Weight |
|---|---:|
| Emergency | 100 |
| High | 90 |
| Medium | 60 |
| Low | 30 |

The algorithm finds a combination of non-overlapping surgeries that gives the maximum total priority weight.

This allows us to compare two different scheduling objectives:
- Maximizing the number of surgeries.
- Maximizing the total priority weight of selected surgeries.

Both Greedy and Dynamic Programming results are displayed separately for each date.

## Technologies Used

- **Programming Language:** C++
- **Concepts:** Data Structures and Algorithms
- **Compiler:** G++
- **IDE:** Visual Studio Code

## How to Run

The project can be compiled and executed using any C++ compiler that supports C++11 or later.

The application uses a menu-driven interface through which users can add surgeries, view patient details, check doctor schedules, display the final OT schedule and view the conflict graph.

## Main Menu

The system provides the following options:

1. Add Patient / Surgery
2. Access Patient Details
3. Access Doctor's Schedule
4. Display Final OT Schedule
5. Display Conflict Graph
6. Exit

## Future Scope

There are several improvements that can be made to the project:

- Adding a database to store patient and surgery records permanently.
- Developing a graphical interface to make the system easier to use.
- Allowing users to modify or cancel scheduled surgeries.
- Handling unexpected delays and changes in surgery timings.
- Improving the scheduling process by considering additional hospital constraints.

## Project Details

**Project Name:** Operation Theatre Scheduling System

**Programming Language:** C++

**Domain:** Healthcare Management

**Course:** Data Structures and Algorithms# Operating_Theatre_Scheduler
