//Written 03/2022 
//Hosted on https://github.com/JesseBr925 as C++ experience examples.
//This project is a simple recipe collection and storage application.  
//It then takes the input reccipes from command line, it will repeat the list of recipes entered back to you,
//and store them in a json object file containing the recipes.

//For information regarding nlohman/json.hpp reference : https://github.com/nlohmann/json 

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "nlohmann/json.hpp"
using json = nlohmann::json;

using namespace std;

class Recipe {
public:
    Recipe(string n = "", string i = "", string d = "") : name(n), ingredients(i), directions(d) {}

    void setName(string n) { name = n; }
    void setIngredients(string i) { ingredients = i; }
    void setDirections(string d) { directions = d; }

    string getName() const { return name; }
    string getIngredients() const { return ingredients; }
    string getDirections() const { return directions; }

    void displayRecipe() const {
        cout << "Name: " << name << endl;
        cout << "Ingredients: " << ingredients << endl;
        cout << "Directions: " << directions << endl;
    }

    json to_json() const {
        return {
            {"name", name},
            {"ingredients", ingredients},
            {"directions", directions}
        };
    }

private:
    string name;
    string ingredients;
    string directions;
};

void outputRecipesToFile(const vector<Recipe>& recipes) {
    json j;
    for (const auto& recipe : recipes) {
        j.push_back(recipe.to_json());
    }

    ofstream outFile("Recipes.json");
    if (outFile.is_open()) {
        outFile << j.dump(4);
        outFile.close();
        cout << "Recipe list written to file 'Recipes.json'" << endl;
    } else {
        cerr << "Unable to open file 'Recipes.json' for writing" << endl;
    }
}

int main() {
    vector<Recipe> recipes;

    // prompt user to add recipes
    while (true) {
        cout << "Enter recipe name (or 'done' to exit): ";
        string name;
        getline(cin, name);

        if (name == "done") {
            break;
        }

        cout << "Enter recipe ingredients: ";
        string ingredients;
        getline(cin, ingredients);

        cout << "Enter recipe directions: ";
        string directions;
        getline(cin, directions);

        // add recipe to vector
        Recipe recipe(name, ingredients, directions);
        recipes.push_back(recipe);
    }

    // display recipe list
    for (int i = 0; i < recipes.size(); i++) {
        cout << "Recipe " << i + 1 << endl;
        recipes[i].displayRecipe();
        cout << endl;
    }

    outputRecipesToFile(recipes);

    return 0;
}