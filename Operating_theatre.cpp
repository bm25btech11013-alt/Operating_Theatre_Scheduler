
#include <bits/stdc++.h>
using namespace std;

const int MAX_OTS = 12;

struct Doctor {
    int id;
    string name, specialty;
};

struct Equipment {
    int id;
    string name;
    int units;
};

struct Surgery {
    int id;
    string patient, procedure;
    int doctorId;
    string date;
    int start, end;
    string priority;
    int weight;
    vector<int> equipment;
    int ot;
};

vector<Doctor> doctors = {
    {1, "Dr. Arun", "Cardiology"},
    {2, "Dr. Meera", "Cardiology"},
    {3, "Dr. Ravi", "Neurology"},
    {4, "Dr. Priya", "Neurology"},
    {5, "Dr. Kiran", "Orthopaedics"},
    {6, "Dr. Ananya", "Orthopaedics"},
    {7, "Dr. Rahul", "Neurosurgery"},
    {8, "Dr. Sneha", "Neurosurgery"},
    {9, "Dr. Vikram", "General Surgery"},
    {10, "Dr. Divya", "General Surgery"},
    {11, "Dr. Nikhil", "Urology"},
    {12, "Dr. Asha", "Gynaecology"},
    {13, "Dr. Varun", "Cardiothoracic Surgery"},
    {14, "Dr. Kavya", "Paediatric Surgery"},
    {15, "Dr. Sanjay", "Plastic Surgery"},
    {16, "Dr. Neha", "ENT"},
    {17, "Dr. Aditya", "Ophthalmology"},
    {18, "Dr. Rohan", "Urology"},
    {19, "Dr. Ishita", "Gynaecology"},
    {20, "Dr. Manish", "Cardiothoracic Surgery"}
};

vector<Equipment> equipmentList = {
    {1, "ECG Monitor", 2},
    {2, "Ventilator", 2},
    {3, "Defibrillator", 2},
    {4, "Ultrasound", 2},
    {5, "Surgical Microscope", 2},
    {6, "Laparoscope", 2},
    {7, "Anaesthesia Machine", 2},
    {8, "Infusion Pump", 2},
    {9, "Patient Monitor", 2},
    {10, "Neurosurgical Drill", 2}
};

vector<Surgery> surgeries;
vector<vector<int>> adj;
int nextId = 1001;

int getWeight(string p) {
    transform(p.begin(), p.end(), p.begin(), ::tolower);

    if (p == "emergency") return 100;
    if (p == "high") return 90;
    if (p == "medium") return 60;
    if (p == "low") return 30;

    return -1;
}

string getPriority(int w) {
    if (w == 100) return "Emergency";
    if (w == 90) return "High";
    if (w == 60) return "Medium";
    return "Low";
}

int parseTime(string t) {
    int h, m = 0;
    size_t pos = t.find(':');

    try {
        if (pos == string::npos)
            h = stoi(t);
        else {
            h = stoi(t.substr(0, pos));
            m = stoi(t.substr(pos + 1));
        }
    }
    catch (...) {
        return -1;
    }

    if (h < 0 || h > 23 || m < 0 || m > 59)
        return -1;

    return h * 60 + m;
}

string formatTime(int t) {
    stringstream ss;
    ss << setfill('0') << setw(2) << t / 60
       << ":" << setw(2) << t % 60;
    return ss.str();
}

bool validDate(string d) {
    if (d.size() != 10 || d[4] != '-' || d[7] != '-')
        return false;

    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (!isdigit(d[i])) return false;
    }

    int y = stoi(d.substr(0, 4));
    int m = stoi(d.substr(5, 2));
    int day = stoi(d.substr(8, 2));

    if (m < 1 || m > 12) return false;

    int days[] = {31, 28, 31, 30, 31, 30,
                  31, 31, 30, 31, 30, 31};

    if (y % 400 == 0 || (y % 4 == 0 && y % 100 != 0))
        days[1] = 29;

    return day >= 1 && day <= days[m - 1];
}

int doctorIndex(int id) {
    for (int i = 0; i < doctors.size(); i++)
        if (doctors[i].id == id) return i;

    return -1;
}

int equipmentIndex(int id) {
    for (int i = 0; i < equipmentList.size(); i++)
        if (equipmentList[i].id == id) return i;

    return -1;
}

bool overlaps(Surgery a, Surgery b) {
    return a.date == b.date &&
           a.start < b.end && b.start < a.end;
}

bool doctorAvailable(int id, string date, int start, int end) {
    for (auto s : surgeries) {
        if (s.doctorId == id && s.date == date &&
            start < s.end && s.start < end)
            return false;
    }

    return true;
}

vector<string> getSpecialties() {
    vector<string> specialties;

    for (auto d : doctors) {
        if (find(specialties.begin(), specialties.end(),
                 d.specialty) == specialties.end())
            specialties.push_back(d.specialty);
    }

    return specialties;
}

void showSpecialties() {
    vector<string> specialties = getSpecialties();

    cout << "\nAVAILABLE SPECIALISATIONS\n";

    for (int i = 0; i < specialties.size(); i++)
        cout << i + 1 << ". " << specialties[i] << "\n";
}

string getSpecialty(int key) {
    vector<string> specialties = getSpecialties();

    if (key < 1 || key > specialties.size())
        return "";

    return specialties[key - 1];
}

int assignDoctor(string specialty, string date,
                 int start, int end) {
    vector<int> available;

    for (auto d : doctors) {
        if (d.specialty == specialty &&
            doctorAvailable(d.id, date, start, end))
            available.push_back(d.id);
    }

    if (available.empty()) return -1;

    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<int> dist(
        0, available.size() - 1
    );

    return available[dist(gen)];
}

int equipmentRemaining(int id, string date,
                       int start, int end) {
    int index = equipmentIndex(id);

    if (index == -1) return 0;

    int units = equipmentList[index].units;
    int maxUsed = 0;

    vector<int> times = {start};

    for (auto s : surgeries) {
        if (s.date == date && s.start < end && s.end > start &&
            find(s.equipment.begin(), s.equipment.end(), id)
            != s.equipment.end()) {

            if (s.start > start)
                times.push_back(s.start);
        }
    }

    for (int t : times) {
        int used = 0;

        for (auto s : surgeries) {
            if (s.date == date && s.start <= t && t < s.end &&
                find(s.equipment.begin(), s.equipment.end(), id)
                != s.equipment.end()) {
                used++;
            }
        }

        maxUsed = max(maxUsed, used);
    }

    return units - maxUsed;
}

bool equipmentAvailable(int id, string date,
                        int start, int end) {
    return equipmentRemaining(id, date, start, end) > 0;
}

void generateGraph() {
    int n = surgeries.size();
    adj.assign(n, {});

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (overlaps(surgeries[i], surgeries[j])) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }
}

bool allocateTheatres() {
    generateGraph();

    int n = surgeries.size();
    vector<int> color(n, -1);
    vector<int> order(n);

    iota(order.begin(), order.end(), 0);

    sort(order.begin(), order.end(), [](int a, int b) {
        if (surgeries[a].date != surgeries[b].date)
            return surgeries[a].date < surgeries[b].date;

        return surgeries[a].start < surgeries[b].start;
    });

    for (int u : order) {
        vector<bool> used(MAX_OTS, false);

        for (int v : adj[u]) {
            if (color[v] != -1)
                used[color[v]] = true;
        }

        int c;

        for (c = 0; c < MAX_OTS; c++) {
            if (!used[c]) break;
        }

        if (c == MAX_OTS) return false;

        color[u] = c;
        surgeries[u].ot = c + 1;
    }

    return true;
}

void showEquipment(string date, int start, int end) {
    cout << "\nAVAILABLE EQUIPMENT\n";

    for (auto e : equipmentList) {
        int remaining = equipmentRemaining(
            e.id, date, start, end
        );

        cout << e.id << ". " << e.name
             << " (Available: " << remaining
             << "/" << e.units << ")\n";
    }
}

void selectEquipment(Surgery &s) {
    showEquipment(s.date, s.start, s.end);

    cout << "\nEnter equipment IDs separated by commas (0 to finish): ";

    string line;
    getline(cin, line);

    stringstream ss(line);
    string token;

    while (getline(ss, token, ',')) {
        size_t first = token.find_first_not_of(" \t");

        if (first == string::npos) continue;

        size_t last = token.find_last_not_of(" \t");
        token = token.substr(first, last - first + 1);

        int id;

        try {
            size_t pos;
            id = stoi(token, &pos);

            if (pos != token.size()) {
                cout << "Invalid equipment number: "
                     << token << "\n";
                continue;
            }
        }
        catch (...) {
            cout << "Invalid equipment number: "
                 << token << "\n";
            continue;
        }

        if (id == 0) break;

        int index = equipmentIndex(id);

        if (index == -1) {
            cout << "Invalid equipment number.\n";
            continue;
        }

        if (find(s.equipment.begin(), s.equipment.end(), id)
            != s.equipment.end()) {
            cout << equipmentList[index].name
                 << " is already selected.\n";
            continue;
        }

        int remaining = equipmentRemaining(
            id, s.date, s.start, s.end
        );

        if (remaining <= 0) {
            cout << "ERROR: " << equipmentList[index].name
                 << " is not available for this time slot.\n";
            continue;
        }

        s.equipment.push_back(id);

        cout << equipmentList[index].name
             << " selected successfully. Remaining units: "
             << remaining - 1 << "\n";
    }
}

void addPatient() {
    Surgery s;
    s.id = nextId++;

    cout << "\nPatient name: ";
    getline(cin, s.patient);

    if (s.patient.empty()) {
        cout << "Invalid patient name.\n";
        nextId--;
        return;
    }

    cout << "Surgery name: ";
    getline(cin, s.procedure);

    cout << "Surgery date (YYYY-MM-DD): ";
    getline(cin, s.date);

    if (!validDate(s.date)) {
        cout << "Invalid date.\n";
        nextId--;
        return;
    }

    string time;

    cout << "Start time (HH:MM): ";
    getline(cin, time);

    s.start = parseTime(time);

    if (s.start == -1) {
        cout << "Invalid time.\n";
        nextId--;
        return;
    }

    int duration;

    cout << "Duration in minutes: ";
    cin >> duration;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (duration <= 0 || s.start + duration > 1440) {
        cout << "Invalid duration.\n";
        nextId--;
        return;
    }

    s.end = s.start + duration;

    cout << "Priority (Emergency / High / Medium / Low): ";
    getline(cin, s.priority);

    s.weight = getWeight(s.priority);

    if (s.weight == -1) {
        cout << "Invalid priority.\n";
        nextId--;
        return;
    }

    s.priority = getPriority(s.weight);

    showSpecialties();

    int key;

    cout << "\nSelect specialisation: ";
    cin >> key;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string specialty = getSpecialty(key);

    if (specialty == "") {
        cout << "Invalid specialisation.\n";
        nextId--;
        return;
    }

    s.doctorId = assignDoctor(
        specialty, s.date, s.start, s.end
    );

    if (s.doctorId == -1) {
        cout << "No doctor available in "
             << specialty << ".\n";
        nextId--;
        return;
    }

    cout << "\nDoctor assigned: "
         << doctors[doctorIndex(s.doctorId)].name << "\n";

    selectEquipment(s);

    surgeries.push_back(s);

    if (!allocateTheatres()) {
        surgeries.pop_back();
        allocateTheatres();

        cout << "No operating theatre is available.\n";
        nextId--;
        return;
    }

    Surgery added = surgeries.back();

    cout << "\nSURGERY SCHEDULED SUCCESSFULLY\n";
    cout << "Patient ID: " << added.id << "\n";
    cout << "Doctor: "
         << doctors[doctorIndex(added.doctorId)].name << "\n";
    cout << "OT: " << added.ot << "\n";
    cout << "Date: " << added.date << "\n";
    cout << "Time: " << formatTime(added.start)
         << " - " << formatTime(added.end) << "\n";
    cout << "Priority: " << added.priority << "\n";
}

string getStatus(Surgery s) {
    time_t now = time(nullptr);
    tm *current = localtime(&now);

    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", current);

    string today = buffer;
    int nowTime = current->tm_hour * 60 + current->tm_min;

    if (today < s.date) return "To be done";
    if (today > s.date) return "Completed";
    if (nowTime < s.start) return "To be done";
    if (nowTime < s.end) return "Ongoing";

    return "Completed";
}

void showPatientDetails() {
    int id;

    cout << "\nEnter Patient ID: ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (auto s : surgeries) {
        if (s.id == id) {
            int d = doctorIndex(s.doctorId);

            cout << "\nPATIENT DETAILS\n";
            cout << "ID: " << s.id << "\n";
            cout << "Name: " << s.patient << "\n";
            cout << "Surgery: " << s.procedure << "\n";
            cout << "Doctor: " << doctors[d].name << "\n";
            cout << "Specialisation: " << doctors[d].specialty << "\n";
            cout << "Date: " << s.date << "\n";
            cout << "Time: " << formatTime(s.start)
                 << " - " << formatTime(s.end) << "\n";
            cout << "Priority: " << s.priority << "\n";
            cout << "OT: " << s.ot << "\n";
            cout << "Status: " << getStatus(s) << "\n";

            cout << "Equipment: ";

            if (s.equipment.empty())
                cout << "None";

            for (int i = 0; i < s.equipment.size(); i++) {
                cout << equipmentList[
                    equipmentIndex(s.equipment[i])
                ].name;

                if (i + 1 < s.equipment.size())
                    cout << ", ";
            }

            cout << "\n";
            return;
        }
    }

    cout << "Patient not found.\n";
}

void showDoctorSchedule() {
    cout << "\nDOCTORS\n";

    for (auto d : doctors)
        cout << d.id << ". " << d.name
             << " - " << d.specialty << "\n";

    int id;

    cout << "\nEnter Doctor ID: ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int index = doctorIndex(id);

    if (index == -1) {
        cout << "Invalid doctor ID.\n";
        return;
    }

    vector<Surgery> schedule;

    for (auto s : surgeries) {
        if (s.doctorId == id)
            schedule.push_back(s);
    }

    sort(schedule.begin(), schedule.end(), [](Surgery a, Surgery b) {
        if (a.date != b.date) return a.date < b.date;
        return a.start < b.start;
    });

    cout << "\nSCHEDULE OF " << doctors[index].name << "\n";

    if (schedule.empty()) {
        cout << "No surgeries scheduled.\n";
        return;
    }

    for (auto s : schedule) {
        cout << "\nPatient: " << s.patient
             << " (ID: " << s.id << ")\n";
        cout << "Surgery: " << s.procedure << "\n";
        cout << "Date: " << s.date << "\n";
        cout << "Time: " << formatTime(s.start)
             << " - " << formatTime(s.end) << "\n";
        cout << "OT: " << s.ot << "\n";
        cout << "Priority: " << s.priority << "\n";
        cout << "Status: " << getStatus(s) << "\n";
    }
}

pair<int, int> weightedDP(vector<Surgery> v) {
    sort(v.begin(), v.end(), [](Surgery a, Surgery b) {
        if (a.end != b.end) return a.end < b.end;
        return a.start < b.start;
    });

    int n = v.size();
    vector<int> dp(n + 1, 0);
    vector<int> prev(n, -1);

    for (int i = 0; i < n; i++) {
        for (int j = i - 1; j >= 0; j--) {
            if (v[j].end <= v[i].start) {
                prev[i] = j;
                break;
            }
        }

        int take = v[i].weight + dp[prev[i] + 1];
        dp[i + 1] = max(dp[i], take);
    }

    int count = 0;

    for (int i = n - 1; i >= 0;) {
        int take = v[i].weight + dp[prev[i] + 1];

        if (take > dp[i]) {
            count++;
            i = prev[i];
        }
        else {
            i--;
        }
    }

    return {dp[n], count};
}

int activitySelection(vector<Surgery> v) {
    sort(v.begin(), v.end(), [](Surgery a, Surgery b) {
        if (a.end != b.end) return a.end < b.end;
        return a.start < b.start;
    });

    int count = 0;
    int lastEnd = -1;

    for (auto s : v) {
        if (s.start >= lastEnd) {
            count++;
            lastEnd = s.end;
        }
    }

    return count;
}

void showAlgorithmAnalysis() {
    map<string, vector<Surgery>> dates;

    for (auto s : surgeries)
        dates[s.date].push_back(s);

    cout << "\nSCHEDULING ALGORITHM ANALYSIS\n";
    cout << "(Alternative single-OT schedules)\n";

    for (auto entry : dates) {
        auto result = weightedDP(entry.second);

        cout << "\nDate: " << entry.first << "\n";
        cout << "DP maximum priority weight: "
             << result.first << "\n";
        cout << "DP surgeries selected: "
             << result.second << "\n";
        cout << "Greedy maximum compatible surgeries: "
             << activitySelection(entry.second) << "\n";
    }
}

void showFinalSchedule() {
    if (surgeries.empty()) {
        cout << "\nNo surgeries scheduled.\n";
        return;
    }

    allocateTheatres();

    cout << "\n========== FINAL OT SCHEDULE ==========\n";

    for (int ot = 1; ot <= MAX_OTS; ot++) {
        vector<Surgery> schedule;

        for (auto s : surgeries) {
            if (s.ot == ot)
                schedule.push_back(s);
        }

        sort(schedule.begin(), schedule.end(), [](Surgery a, Surgery b) {
            if (a.date != b.date) return a.date < b.date;
            return a.start < b.start;
        });

        cout << "\n========== OT " << ot << " ==========\n";

        if (schedule.empty()) {
            cout << "No surgeries assigned.\n";
            continue;
        }

        for (auto s : schedule) {
            cout << "\nPatient ID: " << s.id << "\n";
            cout << "Patient: " << s.patient << "\n";
            cout << "Surgery: " << s.procedure << "\n";
            cout << "Doctor: "
                 << doctors[doctorIndex(s.doctorId)].name << "\n";
            cout << "Date: " << s.date << "\n";
            cout << "Time: " << formatTime(s.start)
                 << " - " << formatTime(s.end) << "\n";
            cout << "Priority: " << s.priority << "\n";
            cout << "Status: " << getStatus(s) << "\n";
        }
    }
}

void showGraph() {
    generateGraph();

    cout << "\nSURGERY CONFLICT GRAPH\n";
    cout << "Vertices represent surgeries.\n";
    cout << "Edges represent overlapping surgeries.\n\n";

    for (int i = 0; i < adj.size(); i++) {
        cout << "Patient " << surgeries[i].id << " -> ";

        if (adj[i].empty()) {
            cout << "No conflicts";
        }
        else {
            for (int v : adj[i])
                cout << surgeries[v].id << " ";
        }

        cout << "\n";
    }
}

int main() {
    int choice;

    do {
        cout << "\n========== OPERATION THEATRE SCHEDULER ==========\n";
        cout << "1. Add Patient / Surgery\n";
        cout << "2. Access Patient Details\n";
        cout << "3. Access Doctor's Schedule\n";
        cout << "4. Display Final OT Schedule\n";
        cout << "5. Display Conflict Graph\n";
        cout << "6. Exit\n";

        cout << "\nEnter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                addPatient();
                break;

            case 2:
                showPatientDetails();
                break;

            case 3:
                showDoctorSchedule();
                break;

            case 4:
                showFinalSchedule();
                break;

            case 5:
                if (surgeries.empty())
                    cout << "No surgeries to display.\n";
                else
                    showGraph();
                break;

            case 6:
                cout << "Exiting Scheduler.\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 6);

    return 0;
}
