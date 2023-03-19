#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;

// Data structure to store email
struct Email {
  string sender;
  string subject;
  string body;
};

// Function to detect spam emails
bool isSpam(Email email, unordered_set<string> spamKeywords, unordered_map<string, int> spamSenders) {
  // Convert email to lowercase for case-insensitive matching
  transform(email.subject.begin(), email.subject.end(), email.subject.begin(), ::tolower);
  transform(email.body.begin(), email.body.end(), email.body.begin(), ::tolower);

  // Check if email subject or body contain any spam keywords
  for (const auto& keyword : spamKeywords) {
    if (email.subject.find(keyword) != string::npos || email.body.find(keyword) != string::npos) {
      return true;
    }
  }

  // Check if email is from a known spam sender
  if (spamSenders.find(email.sender) != spamSenders.end()) {
    return true;
  }

  return false;
}

int main() {
  // Initialize set of spam keywords
  unordered_set<string> spamKeywords = {"discount", "viagra", "free", "medicine", "earn money"};

  // Initialize map of spam senders and their spam email count
  unordered_map<string, int> spamSenders = {{"spam@spammer.com", 10}, {"spam@gmail.com", 5}};

  // Read emails from user
  vector<Email> emails;
  while (true) {
    cout << "Enter email sender (leave blank to stop): ";
    string sender;
    getline(cin, sender);
    if (sender.empty()) {
      break;
    }

    cout << "Enter email subject: ";
    string subject;
    getline(cin, subject);

    cout << "Enter email body: ";
    string body;
    getline(cin, body);

    emails.emplace_back(Email{sender, subject, body});
  }

  // Check which emails are spam
  for (const auto& email : emails) {
    if (isSpam(email, spamKeywords, spamSenders)) {
      cout << "SPAM: " << email.subject << endl;
    } else {
      cout << "NOT SPAM: " << email.subject << endl;
    }
  }

  return 0;
}
