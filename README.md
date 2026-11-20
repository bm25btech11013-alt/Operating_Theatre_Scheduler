# Operation Theatre Scheduling System

## About the Project

In a hospital, scheduling surgeries can get complicated when multiple patients need to undergo surgery on the same day. A doctor might already be occupied, an operating theatre might be in use, or the required medical equipment might not be available.

We wanted to work on this problem and build a simple system that could handle these scheduling requirements.

Our project, **Operation Theatre Scheduling System**, is developed using C++. It allows us to add patients and their surgery details, assign doctors based on their specialization and availability, select the required equipment and allocate operating theatres without overlapping schedules.

We have also included different scheduling algorithms to see how Greedy and Dynamic Programming approaches work when the priority and number of surgeries are considered.

## Features

The system currently supports the following operations:

- Adding patients along with their surgery details, date, time, duration and priority.
- Assigning doctors automatically based on their specialization and availability.
- Checking whether the required medical equipment is available during the selected time slot.
- Allocating operating theatres based on surgery timings.
- Viewing patient details using their unique patient ID.
- Checking the schedule of individual doctors.
- Displaying the final schedule of all operating theatres.
- Checking the status of a surgery (To be done, Ongoing or Completed).
- Viewing a conflict graph that shows which surgeries overlap.
- Comparing different scheduling algorithms based on the number and priority of surgeries.

## Data Structures Used

While working on this project, we used different data structures depending on what we needed to store or manage.

### 1. Structures (struct)

We used structures to store information about doctors, equipment and surgeries.

For example, the Doctor structure stores the doctor's ID, name and specialization. Similarly, the Surgery structure contains details such as patient name, procedure, date, timings, priority, assigned doctor, selected equipment and OT number.

This helped us keep related information together instead of managing each detail separately.

### 2. Vectors

We used vectors to store the lists of doctors, equipment and scheduled surgeries.

Since new surgeries can be added at any time, we needed a data structure that could grow as more records were added. Vectors also made it easier to go through the records, search for information and sort the schedules.

### 3. Graphs (Adjacency List)

One of the main problems in surgery scheduling is identifying overlapping surgeries.

To handle this, we represented each surgery as a vertex in a graph. Whenever two surgeries overlap in time, we connect them with an edge.

We used an adjacency list to store these connections. This gives us a way to identify which surgeries have conflicts with each other.

### 4. Graph Coloring

After creating the conflict graph, we used graph coloring to assign operating theatres.

The idea is that two connected vertices cannot have the same colour. In our project, each colour represents an operating theatre.

So, if two surgeries overlap, they are assigned different theatres. We use a greedy coloring approach and currently support up to 12 operating theatres.

### 5. Maps

We used a map to group surgeries according to their dates.

This was especially useful during algorithm analysis because we wanted to compare scheduling results separately for each date rather than mixing surgeries from different days.

### 6. Sorting

Sorting is used in different parts of the project.

For displaying schedules, we arrange surgeries according to their dates and starting times.

For the Greedy and Dynamic Programming algorithms, we sort surgeries according to their finishing times. This is necessary for the scheduling approaches we have implemented.

## Algorithms Used

Apart from the data structures, we implemented three main algorithmic approaches.

### 1. Graph Coloring

We use graph coloring for allocating operating theatres.

First, we create a graph where each vertex represents a surgery and an edge represents a timing conflict. We then process the surgeries in chronological order and assign the first available colour that is not being used by an already-colored neighbouring vertex.

Each colour corresponds to an operating theatre. This ensures that overlapping surgeries are not assigned to the same theatre.

### 2. Greedy Algorithm – Activity Selection

Here, our aim is to find the maximum number of surgeries that can be performed without overlapping in a single operating theatre.

We first sort the surgeries according to their finishing times. Then we select a surgery if it starts after or exactly when the previously selected surgery finishes.

The idea is to select surgeries that finish earlier so that more surgeries can fit into the available time.

### 3. Dynamic Programming – Weighted Interval Scheduling

We also wanted to consider the priority of surgeries instead of only looking at how many surgeries could be performed.

For this, we implemented Weighted Interval Scheduling using Dynamic Programming.

We assigned different weights to the priority levels:

- Emergency – 100
- High – 90
- Medium – 60
- Low – 30

The algorithm finds a combination of non-overlapping surgeries that gives the maximum total priority weight.

This gives us an interesting comparison between the two approaches: one tries to schedule the maximum number of surgeries, while the other tries to maximize the total priority weight.

Both results are displayed separately for each date.

## Technologies Used

- C++
- Data Structures and Algorithms
- VS Code
- G++ Compiler

## How to Run

The project is a menu-driven C++ application. After running it, the user can choose from different options to add surgeries, view patient details, check doctor schedules, display the final OT schedule or view the conflict graph.

## Future Improvements

There are still a few things that could be added to make the system more useful:

- Connecting a database so that patient and surgery details are saved even after the program is closed.
- Adding a graphical interface instead of using only the console.
- Providing options to modify or cancel an already scheduled surgery.
- Handling unexpected delays and changes in surgery timings.
- Considering more hospital-related constraints while allocating resources.

## Project Information

**Project:** Operation Theatre Scheduling System

**Language:** C++

**Course:** Data Structures and Algorithms

**Domain:** Healthcare Management
