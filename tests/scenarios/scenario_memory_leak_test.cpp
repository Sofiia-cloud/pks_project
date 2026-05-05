/**
 * Сценарий 3: Проверка на утечки памяти (минимальный)
 */

#include <iostream>
#include <vector>

class TestClass {
public:
    TestClass() { std::cout << "Создан объект\n"; }
    ~TestClass() { std::cout << "Уничтожен объект\n"; }
};

int main() {
    std::cout << "=== Сценарий 3: Проверка создания/уничтожения объектов ===\n\n";
    
    {
        std::vector<TestClass> objects;
        objects.push_back(TestClass());
        objects.push_back(TestClass());
        std::cout << "Объекты в векторе: " << objects.size() << std::endl;
    }
    
    std::cout << "\nВектор вышел из области видимости\n";
    std::cout << "Если вы видите сообщения об уничтожении — утечек нет\n";
    
    return 0;
}