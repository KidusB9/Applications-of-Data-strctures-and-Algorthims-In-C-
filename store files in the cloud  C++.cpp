#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <functional>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

const int BUFFER_SIZE = 4096;

// used Structure func to store progress information for the file upload
struct UploadProgress {
    size_t bytes_uploaded;
    size_t file_size;
    bool interrupted;
};

//  this code uses Global variables to check  progress information and synchronization
mutex progress_mutex;
condition_variable progress_cv;
UploadProgress progress;

// Function to upload the file to the cloud storage service
void UploadFile(ifstream& file, size_t file_size) {
    // Set the position in the file to the next chunk to be uploaded
    file.seekg(progress.bytes_uploaded);

    // used Loop until the entire file has been uploaded
    while (progress.bytes_uploaded < file_size) {
        // Read a chunk of the file into the buffer
        file.read(buffer, BUFFER_SIZE);
        size_t bytes_read = file.gcount();

        // Upload the chunk to the cloud storage service
        // (code for uploading the chunk goes here)

        // Update the progress information
        {
            lock_guard<mutex> lock(progress_mutex);
            progress.bytes_uploaded += bytes_read;
        }
        progress_cv.notify_all();
    }
}


// Function to show the progress of the file upload
void DisplayProgress() {
    while (true) {
        unique_lock<mutex> lock(progress_mutex);
        if (progress.bytes_uploaded == progress.file_size || progress.interrupted) {
            break;
        }
        lock.unlock();
        cout << "." << flush;
        this_thread::sleep_for(chrono::seconds(1));
    }
}


       
int main(int argc, char** argv)
{
    if (argc < 3)
    {
        cout << "uses  cloud_storage file_to_upload cloud_storage_service" << endl;
        return 1;
    }

    string file_path = argv[1];
    string service = argv[2];

    // this code opens  the file for reading in binary mode
    ifstream file(file_path, ios::binary);
    if (!file.is_open())
    {
        cerr << "Error opening file: " << file_path << endl;
        return 1;
    }

    // Calculate the file size
    file.seekg(0, ios::end);
    size_t file_size = file.tellg();
    file.seekg(0, ios::beg);

    //  to Read the file into a buffer
    char buffer[BUFFER_SIZE];
    file.read(buffer, file_size);

    // Hash the file contents using the SHA-256 algorithm
    unsigned char hash[32];
    SHA256(reinterpret_cast<unsigned char*>(buffer), file_size, hash);

    // to  Convert the hash to a hexadecimal string
    string hash_string;
    hash_string.resize(64);
    const char* hex_digits = "0123456789abcdef";
    for (int i = 0; i < 32; i++)
    {
        hash_string[2 * i] = hex_digits[hash[i] >> 4];
        hash_string[2 * i + 1] = hex_digits[hash[i] & 0x0F];
    }

    // Check for a file containing progress information
    string progress_file_name = file_path + ".progress";
    ifstream progress_file(progress_file_name, ios::binary);
    if (progress_file.is_open()) {
        // Read the progress information from the file
        progress_file.read(reinterpret_cast<char*>(&progress), sizeof(UploadProgress));

       
        file.seekg(progress.bytes_uploaded);
    } else {
        // Initialize the progress information
        progress.bytes_uploaded = 0;
        progress.file_size = file_size;
        progress.interrupted = false;
    }

    // Connect to the cloud storage service
    // (code for connecting to the service goes here)

    // Start a thread to display the progress of the file upload
    thread progress_thread(DisplayProgress);

    // Upload the file to the cloud storage service
  UploadFile(file, file_size);


    // Wait for the progress display thread to finish
    progress_thread.join();

    // If the upload was interrupted, write the progress information to a file
    if (progress.interrupted) {
        ofstream progress_file(progress_file_name, ios::binary);
        progress_file.write(reinterpret_cast<char*>(&progress), sizeof(UploadProgress));
        progress_file.close();
        cout << endl << "File upload interrupted. Progress information saved to " << progress_file_name << end
