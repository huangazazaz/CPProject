#ifndef SCOPESTACK_HPP
#define SCOPESTACK_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include <optional>
#include <iostream>

// Define SymbolInfo to store information about variables or functions.
struct SymbolInfo {
    std::string type; // e.g., "int", "float", "function", etc.
    int scope_level;  // Depth of scope, can be useful for debugging

    SymbolInfo(std::string type = "", int scope_level = 0) 
        : type(type), scope_level(scope_level) {}
};

class LocalSymbolTable {
public:
    std::unordered_map<std::string, SymbolInfo> table;

    bool insert(const std::string& name, const SymbolInfo& info) {
        if (table.find(name) == table.end()) {
            table[name] = info;
            return true;
        }
        return false; // Insertion failed, already present
    }

    SymbolInfo* lookup(const std::string& name) {
        auto it = table.find(name);
        if (it != table.end()) {
            return &it->second; // Return pointer to SymbolInfo if found
        }
        return nullptr; // Not found in this local scope
    }

    void print() const {
        for (const auto& [name, info] : table) {
            std::cout << "  Symbol: " << name 
                      << ", Type: " << info.type 
                      << ", Scope Level: " << info.scope_level << std::endl;
        }
    }
};

class ScopeStack {
    std::vector<LocalSymbolTable> scopes;
    int current_scope_level = 0; // To track depth of current scope

public:
    // Enter a new scope by adding a new LocalSymbolTable to the vector
    void enterScope() {
        scopes.push_back(LocalSymbolTable());
        ++current_scope_level;
        printf("After entering scope %d",current_scope_level);
    }

    // Exit the current scope by removing the last LocalSymbolTable from the vector
    void exitScope() {
        if (!scopes.empty()) {
            scopes.pop_back();
            --current_scope_level;
        }
    }

    // Insert a new symbol into the current (last) scope
    bool insert(const std::string& name, const SymbolInfo& info) {
        if (!scopes.empty()) {
            return scopes.back().insert(name, info);
        }
        return false;
    }

    // Lookup a symbol, starting from the most recent scope and moving outward
    SymbolInfo* lookup(const std::string& name) {
        // Iterate from the last element back to the first
        for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
            SymbolInfo* result = it->lookup(name);
            if (result != nullptr) return result;
        }
        return nullptr; // Not found in any scope
    }

    void print() const {
        std::cout << "Scope Stack Content (from outermost to innermost):" << std::endl;
        int level = 1;
        for (const auto& scope : scopes) {
            std::cout << "Scope Level " << level++ << ":" << std::endl;
            scope.print();
        }
    }
};

extern ScopeStack scopeStack;

#endif // SCOPESTACK_HPP
