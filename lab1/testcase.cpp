#include "graph.hpp"


int main(){
    graph::Edge edge1(1);
    graph::Edge edge2(2);
    graph::Edge edge3(3);
    graph::Edge edge4(4);
    graph::Edge edge5(5);
    graph::Edge edge6(6);
    graph::Edge edge7(7);
    graph::Edge edge8(8);
    graph::Edge edge9(9);
    graph::Edge edge10(10);
    graph::Edge edge11(11);
    graph::Edge edge12(12);
    graph::Edge edge13(13);
    graph::Edge edge14(14);
    graph::Edge edge15(15);

    edge1.Connect(&edge2);
    edge2.Connect(&edge5);
    edge1.Connect(&edge3);
    edge3.Connect(&edge6);
    edge6.Connect(&edge9);
    edge3.Connect(&edge7);
    edge3.Connect(&edge4);
    edge4.Connect(&edge10);
    edge4.Connect(&edge13);
    edge4.Connect(&edge14);
    edge14.Connect(&edge15);
    edge4.Connect(&edge8);
    edge8.Connect(&edge11);
    edge8.Connect(&edge12);

    std::cout << " --- Debug log ------ " << std::endl;
    std::stack<graph::Edge*> stack;
    edge1.DeepSearch(11, &stack);
    std::cout << " --- Looking ended -- " << std::endl << std::endl;
    std::cout << "result of looking: ";
    while (!stack.empty())
    {
        std::cout << stack.top()->index;
        stack.pop();
        if (!stack.empty()){
            std::cout << " -> ";
        }
    }
    std::cout << std::endl;
    
 

}