#include <unordered_map>
#include <queue>
#include <mutex>

// Represents a process that can be scheduled
struct Process {
  int priority; // Higher priority processes are scheduled before lower priority processes
  int elapsed_time; // How much time has this process already been scheduled for
  int burst_time; // How much time does this process need to complete
  int time_slice; // The time slice allocated to this process for each scheduling period
  int waiting_time; // The total time this process has spent waiting to be scheduled
};

// A scheduler that uses priority-based round-robin scheduling
class Scheduler {
 public:
  // Adds a new process to the queue
  void AddProcess(const Process& p) {
    std::lock_guard<std::mutex> lock(mutex_);
    process_map_[p.id] = p;
    queue_.push(p.id);
  }

  // Removes a process from the queue
  void RemoveProcess(int id) {
    std::lock_guard<std::mutex> lock(mutex_);
    process_map_.erase(id);
  }

  // Returns the next process to be scheduled
  Process GetNextProcess() {
    std::lock_guard<std::mutex> lock(mutex_);

    // Keep track of the next process to be scheduled
    int next_id = -1;

    // Iterate through the queue and find the next process to be scheduled
    for (int id : queue_) {
      Process p = process_map_[id];
      if (next_id == -1 || p.priority > process_map_[next_id].priority) {
        next_id = id;
      }
    }

    // Remove the process from the queue
    queue_.erase(next_id);

    // Return the next process to be scheduled
    return process_map_[next_id];
  }

 private:
  std::mutex mutex_;
  std::unordered_map<int, Process> process_map_;
  std::queue<int> queue_;
};

// The global scheduler instance
Scheduler scheduler;

// This function represents the kernel's main scheduling loop
void ScheduleProcesses() {
  while (true) {
    // Get the next process to be scheduled
    Process p = scheduler.GetNextProcess();

    // Schedule the process for its allocated time slice
    Schedule(p, p.time_slice);

    // Update the process's elapsed time and waiting time
    p.elapsed_time += p.time_slice;
    p.waiting_time += p.time_slice;

    // If the process has not yet completed, add it back to the queue
    if (p.elapsed_time < p.burst_time) {
      scheduler.AddProcess(p);
    }
  }
}
// Changes the priority of a process
void ChangePriority(int id, int new_priority) {
  std::lock_guard<std::mutex> lock(mutex_);
  Process p = process_map_[id];
  p.priority = new_priority;
  process_map_[id] = p;
}

// Returns the current average waiting time for all processes
double GetAverageWaitingTime() {
  std::lock_guard<std::mutex> lock(mutex_);
  int total_waiting_time = 0;
  int num_processes = 0;
  for (const auto& kv : process_map_) {
    total_waiting_time += kv.second.waiting_time;
    num_processes++;
  }
  return static_cast<double>(total_waiting_time) / num_processes;
}

// Returns the current utilization rate of the CPU
double GetCPUUtilization() {
  std::lock_guard<std::mutex> lock(mutex_);
  int total_elapsed_time = 0;
  int num_processes = 0;
  for (const auto& kv : process_map_) {
    total_elapsed_time += kv.second.elapsed_time;
    num_processes++;
  }
  return static_cast<double>(total_elapsed_time) / (num_processes * time_slice);
}
// Suspends a process until it is resumed
void SuspendProcess(int id) {
  std::lock_guard<std::mutex> lock(mutex_);
  Process p = process_map_[id];
  p.suspended = true;
  process_map_[id] = p;
}

// Resumes a suspended process
void ResumeProcess(int id) {
  std::lock_guard<std::mutex> lock(mutex_);
  Process p = process_map_[id];
  p.suspended = false;
  process_map_[id] = p;
  queue_.push(id);
}

// Returns the current status (suspended or not) of a process
bool GetProcessStatus(int id) {
  std::lock_guard<std::mutex> lock(mutex_);
  Process p = process_map_[id];
  return p.suspended;
}

// Returns the current priority of a process
int GetProcessPriority(int id) {
  std::lock_guard<std::mutex> lock(mutex_);
  Process p = process_map_[id];
  return p.priority;
}

