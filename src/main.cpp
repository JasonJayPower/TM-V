#include "App/App.hpp"

#include<iostream>

//#include "Testing/Test.hpp"
//
//struct Position {
//    int x;
//    int y;
//};
//
//struct Health {
//    int health;
//};
//
//int main() {
//    RegisterMap m;
//
//    auto e = m.create();
//    m.insert<Position>(e, { 10, 10 });
//    m.insert<Health>(e, { 50 });
//
//
//    auto e1 = m.create();
//    m.insert<Health>(e1, { 50 });
//
//    auto e2 = m.create();
//    m.insert<Health>(e2, { 50 });
//    m.insert<Position>(e2, { 10, 10 });
//
//
//    auto view = m.view<Position, Health>();
//
//
//    std::cout << m.get<Position>(e).x << std::endl;
//    std::cout << m.get<Health>(e).health << std::endl;
//    //App app;
//    //app.setup();
//    //app.run();
//
//    return 0;
//}


int main() {

    App app;
    app.setup();
    app.run();

    return 0;
}
