#include "window.h"

int main() {
    std::unique_ptr<Window> window = std::make_unique<Start_Window>();

    while (window) {
        std::unique_ptr<Window> new_window = window->handle_events();
        window.swap(new_window);
    }
    return 0;
}