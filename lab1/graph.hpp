#include <stack>
#include <list>
#include <iostream>

namespace graph{
    class Edge
    {
        public:
            int index;
            std::list<Edge*> connectedEdges;

            Edge(int index);
            
            bool Connect(Edge* edgePtr);
            void DeepSearch(int index, std::stack<Edge*>* stackPtr);
        private:
            bool IsConnectedWith(Edge* edgePtr);
            bool IsThis(Edge* edgePtr);
            void DeepSearch(int index, int indexFrom, std::stack<Edge*>* stackPtr);
    };
}