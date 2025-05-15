#include <string>
#include <string_view>
#include <vector>
#include <algorithm>
#include <iostream>

using  Vect_strv = std::vector<std::string_view>;

Vect_strv alphaOrder (Vect_strv strv) { //move semantics: 
    std::sort(strv.begin(), strv.end());
    return strv;
}

int main() {
    Vect_strv ordered_string{alphaOrder({"Baba",
        "Wall",
        "Lava",
        "Rock", //lanciabile se ha aggettivo launchable, Player deve "calpestarla" per poterla lanciare
        "Door", //apribile automaticamente azionando ingranaggio/leva
        "Lever", //?trasportabile?
        "Gear", //fisso
        "Flag",
    })};
    for(auto element : ordered_string) std::cout<< element << '\n';
}