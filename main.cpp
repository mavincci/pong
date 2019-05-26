#include <graph.h>
#include <game.h>
#include <iterator>
#include <iostream>

int main(){
    // mickey::graph grp(600, 600, "Mick si Magician", 50, 10);

    mickey::game gm;

    gm.main_loop();

    // std::copy(gm.state.begin(), gm.state.end(), std::ostream_iterator<std::uint16_t>(std::cout, " "));

    getch();
}