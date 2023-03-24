#include "graph.hpp"

graph::Edge::Edge(int index){
    this->index = index;
}

bool graph::Edge::IsThis(Edge* edgePtr){
    return (*edgePtr).index == this->index;
}

bool graph::Edge::IsConnectedWith(Edge* edgePtr){
    for(Edge* checkEdgePtr : this->connectedEdges){
        if ((*checkEdgePtr).index == this->index){
            return true;
        }
    }
    return false;
}

bool graph::Edge::Connect(Edge* edgePtr){
    if (this->IsThis(edgePtr)){
        return false;
    }
    if (this->IsConnectedWith(edgePtr)){
        return false;
    }
    this->connectedEdges.push_back(edgePtr);
    (*edgePtr).connectedEdges.push_back(this);
    return true;
}

void graph::Edge::DeepSearch(int index, std::stack<graph::Edge*>* stackPtr){
    std::cout << "DeepSearch log: " << "edge " << this->index << " is looking for edge " << index << std::endl;
    if (this->index == index){
        (*stackPtr).push(this);
        std::cout << "DeepSearch log: " << "edge was found" << std::endl;
        return;
    }
    for (graph::Edge* edgePtr : this->connectedEdges){
        std::cout << "DeepSearch log: " << "edge " << this->index << " looking for edge " << index << " in edge " << (*edgePtr).index << std::endl;
        (*edgePtr).DeepSearch(index, this->index, stackPtr);
        if (!(*stackPtr).empty()){
            std::cout << "DeepSearch log: " << "edge " << this->index << " connected with edge " << (*edgePtr).index << std::endl; 
            std::cout << "DeepSearch log: return from DeepSearch" << std::endl;
            (*stackPtr).push(this);
            return;
        }
    }
}

void graph::Edge::DeepSearch(int index, int indexFrom, std::stack<graph::Edge*>* stackPtr){
    if (this->index == index){
        std::cout << "DeepSearch log: " << "edge " << index << " was found" << std::endl;
        (*stackPtr).push(this);
        return;
    }
    for (graph::Edge* edgePtr : this->connectedEdges){
        if ((*edgePtr).index != indexFrom){
            std::cout << "DeepSearch log: " << "edge " << this->index << " looking for edge " << index << " in edge " << (*edgePtr).index << std::endl;
            (*edgePtr).DeepSearch(index, this->index, stackPtr);
            if (!(*stackPtr).empty()){
                (*stackPtr).push(this);
                std::cout << "DeepSearch log: " << "edge " << this->index << " connected with edge " << (*edgePtr).index << std::endl; 
                return;
            }
        }
    }
    std::cout << "DeepSearch log: edge " << index << " not connected with edge " << this->index << std::endl;
}


    
