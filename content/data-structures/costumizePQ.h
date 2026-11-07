struct Task {
    int id;
    int priority;
    int execution_time;
};

// rule: priority bigger, then execution_time smaller
struct CompareTask {
    bool operator()(const Task& a, const Task& b) const {
        if (a.priority != b.priority) {
            return a.priority < b.priority;
        }
        return a.execution_time > b.execution_time;
    }
};

int main() {
    priority_queue<Task, vector<Task>, CompareTask> pq;

    pq.push({1, 5, 100});
    pq.push({2, 10, 50});
    pq.push({3, 5, 30});

    while (!pq.empty()) {
        auto t = pq.top();
        pq.pop();
        cout << "Task ID: " << t.id << "\n";
    }
    // output result: Task 2 -> Task 3 -> Task 1
}