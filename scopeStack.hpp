#ifndef SCOPESTACK_HPP
#define SCOPESTACK_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include <optional>
#include <iostream>
#include "node.hpp"

// Original one in symbolTable.hpp, this one uses the original SymbolTable in the org code
class ScopeStack {

public:
    // Enter a new scope, note we use directly unordered_map
    std::vector<unordered_map<string,Type*>> scopes = {
    std::unordered_map<std::string, Type*>{}
};;
    int current_scope_level = 0; // To track depth of current scope
    
    void enterScope(unordered_map<string,Type*> symbolTable) {
        scopes.push_back(symbolTable);
        ++current_scope_level;
        // std::cout << "Entered scope " << current_scope_level <<std::endl;

    }

    // Exit the current scope by removing the last LocalSymbolTable from the vector
    void exitScope() {
        if (!scopes.empty()) {
            scopes.pop_back();
            --current_scope_level;
            // std::cout << "Exited scope " << current_scope_level <<std::endl;

        }
    }

    // Insert a new symbol into the current (last) scope
    bool insert(const std::string& name, Type *type) {
        if (!scopes.empty()) {

            // back accesses last element
            return scopes.back()[name] == type;
        }
        return false;
    }

    // Lookup a symbol, starting from the most recent scope and moving outward
    Type* lookup(const std::string& name) {
        // Iterate from the last element back to the first
        for (size_t i = 0; i < scopes.size(); ++i) {
            auto& scopeTable = scopes[i];
            Type* result = scopeTable[name];
            if (result != nullptr) return result;
        }
       
        return nullptr; // Not found in any scope
    }

    std::unordered_map<std::string, Type*>* lookupTable(const std::string& name) {
    
    for (size_t i = 0; i < scopes.size(); ++i) {
        auto& scopeTable = scopes[i];
        if (scopeTable.count(name) > 0) {
            return &scopeTable;  // Return the address of the map containing the symbol
        }
    }
        return nullptr;  // Symbol not found in any scope
    }

    void printScopes() {
        // std::cout << "=== Current Scope Stack ===" << std::endl;
            std::cout << "Scope Level " << current_scope_level << ":" << std::endl;

    }

};


extern ScopeStack scopeStack;

#endif // SCOPESTACK_HPP
