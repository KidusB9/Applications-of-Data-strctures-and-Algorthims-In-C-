// program that uses a linked list to implement an image viewer with previous and next buttons:
#include <iostream>
#include <string>
#include <memory>
#include <vector>

using namespace std;

// Data structure to store image
struct Image {
  string fileName;
  string imageData;
};

// Node in linked list
struct Node {
  Image image;
  shared_ptr<Node> next;
  shared_ptr<Node> prev;
};

// Linked list to store images
class ImageList {
 private:
  shared_ptr<Node> head;
  shared_ptr<Node> tail;

 public:
  ImageList() : head(nullptr), tail(nullptr) {}

  // Add image to the end of the list
  void addImage(Image image) {
    auto newNode = make_shared<Node>(Node{image, nullptr, tail});
    if (tail) {
      tail->next = newNode;
    }
    tail = newNode;
    if (!head) {
      head = newNode;
    }
  }

  // Get current image
  Image getCurrentImage() {
    return tail->image;
  }

  // Move to previous image
  void prevImage() {
    if (tail->prev) {
      tail = tail->prev;
    }
  }

  // Move to next image
  void nextImage() {
    if (tail->next) {
      tail = tail->next;
    }
  }
};

int main() {
  ImageList imageList;

  // Read in images from user
  while (true) {
    cout << "Enter image file name (leave blank to stop): ";
    string fileName;
    getline(cin, fileName);
    if (fileName.empty()) {
      break;
    }

    cout << "Enter image data: ";
    string imageData;
    getline(cin, imageData);

    imageList.addImage(Image{fileName, imageData});
  }

  // Display current image and allow user to navigate through images
  while (true) {
    cout << "Current image: " << imageList.getCurrentImage().fileName << endl;
    cout << "Enter 'n' for next image, 'p' for previous image, or 'q' to quit: ";
    char input;
    cin >> input;
    if (input == 'n') {
      imageList.nextImage();
    } else if (input == 'p') {
      imageList.prevImage();
    } else if (input == 'q') {
      break;
    }
  }

  return 0;
}



