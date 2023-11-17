#include <iostream>
#include <string>
#include <functional>
#include <map>
#include <vector>

// Event types
enum class EventType {
    Click,
    Hover,
    KeyPress
};

// Generic Event class
class Event {
    EventType type;
public:
    explicit Event(EventType type) : type(type) {}
    virtual ~Event() = default;
    EventType getType() const { return type; }
};

// Specific event classes
class ClickEvent : public Event {
public:
    ClickEvent() : Event(EventType::Click) {}
};

class HoverEvent : public Event {
public:
    HoverEvent() : Event(EventType::Hover) {}
};

class KeyPressEvent : public Event {
    char key;
public:
    explicit KeyPressEvent(char key) : Event(EventType::KeyPress), key(key) {}
    char getKey() const { return key; }
};

// Listener interface
class EventListener {
public:
    virtual void onEvent(const Event& event) = 0;
};

// Event Manager
class EventManager {
    std::map<EventType, std::vector<std::function<void(const Event&)>>> listeners;
public:
    void subscribe(EventType eventType, std::function<void(const Event&)> listener) {
        listeners[eventType].push_back(listener);
    }

    void emit(const Event& event) {
        auto& eventListeners = listeners[event.getType()];
        for (auto& listener : eventListeners) {
            listener(event);
        }
    }
};

// Example listener
class Button : public EventListener {
    std::string label;

public:
    explicit Button(std::string label) : label(std::move(label)) {}

    void onEvent(const Event& event) override {
        if (event.getType() == EventType::Click) {
            std::cout << "Button " << label << " clicked." << std::endl;
        }
    }
};

int main() {
    EventManager eventManager;

    Button button1("Play");
    Button button2("Stop");

    eventManager.subscribe(EventType::Click, [&](const Event& event) { button1.onEvent(event); });
    eventManager.subscribe(EventType::Click, [&](const Event& event) { button2.onEvent(event); });

    // Simulate a click event
    ClickEvent click;
    eventManager.emit(click);

    return 0;
}
