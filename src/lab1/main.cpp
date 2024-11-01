//Лазарев Фёдор николаевич 3372


#include "application.h"
#include "Windows.h"
#undef max

int main() {
    SetConsoleOutputCP(CP_UTF8);
    srand(time(NULL));
    application app;
    app.interactionMenu();
    return 0;
}