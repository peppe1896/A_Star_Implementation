#include "Game.h"

int main()
{

    Game* game = new Game();

    game->run();

}

/*
#include "A_Star.h"

void breadth_first_search(SimpleGraph graph, char start) {
    std::queue<char> frontier;
    frontier.push(start);

    std::unordered_set<char> visited;
    visited.insert(start);

    while (!frontier.empty()) {
        char current = frontier.front();
        frontier.pop();

        std::cout << "Visiting " << current << '\n';
        for (char next : graph.neighbors(current)) {
            if (visited.find(next) == visited.end()) {
                frontier.push(next);
                visited.insert(next);
                //std::cout << "BOH" << std::endl;
            }
        }
    }
}


int main() {
    breadth_first_search(example_graph, 'A');

    //a_star_search(example_graph, 'A', 'E');
}

 */