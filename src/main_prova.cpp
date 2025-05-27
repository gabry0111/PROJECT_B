#include "enum_objects.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include <iostream>
#include <stdexcept>

/*
namespace MapSize {
    constexpr std::size_t width = 16;  // Number of tiles in the X direction
    constexpr std::size_t height = 16; // Number of tiles in the Y direction
}

class TileMap : public sf::Drawable, public sf::Transformable {
public:
    bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles,
              unsigned int width, unsigned int height) {
        // Load the tileset texture
        if (!m_tileset.loadFromFile(tileset)) {
            return false;
        }

        // Resize the vertex array to fit the level size
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(width * height * 4); // 4 vertices per tile (quad)

        // Populate the vertex array
        for (unsigned int i = 0; i < width; ++i) {
            for (unsigned int j = 0; j < height; ++j) {
                // Get the current tile number
                int tileNumber = tiles[i + j * width];

                // Find its position in the tileset texture
                int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
                int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

                // Get a pointer to the quad's 4 vertices
                sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

                // Define the 4 corners of the quad
                quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
                quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
                quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
                quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

                // Define the 4 texture coordinates
                quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
                quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
                quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            }
        }

        return true;
    }

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        // Apply transform
        states.transform *= getTransform();

        // Apply the tileset texture
        states.texture = &m_tileset;

        // Draw the vertex array
        target.draw(m_vertices, states);
    }

    sf::VertexArray m_vertices{};
    sf::Texture m_tileset{};
};
*/

/* PARTE 2
// Map the textures based on the integer values
const std::array<sf::Texture&, (+Baba_Is_Us::Type::ICON_NOUN_TYPE - 1)>& getTextureArray(){
    std::array<sf::Texture*, (+Baba_Is_Us::Type::ICON_NOUN_TYPE - 1)> texarr {};
    for (sf::Texture* iter : texarr) {
        if (! iter.loadFromFile("")) throw std::runtime_error("Error loading textures in getTextureArray()");
    }

}
FINE PARTE 2*/
void createGridFromImage(const std::string& imageFilePath) { 
    //importa l'immagine dal file
    sf::Texture texture; 
    if (!texture.loadFromFile(imageFilePath)) { 
        std::cerr << "Error loading image: " << imageFilePath << '\n'; 
        return; 
    } 
    
    const size_t TILE_SIZE = 16; 
    
    // l'immagine può essere divisa in 16*16?
    sf::Vector2u imageSize = texture.getSize(); 
    if (imageSize.x < TILE_SIZE * 16 || imageSize.y < TILE_SIZE * 16) { 
        std::cerr << "Image is too small to fit a 16x16 grid of " << TILE_SIZE << "x" << TILE_SIZE << " tiles." << '\n'; 
        return; 
    } 

    sf::RenderWindow window(sf::VideoMode(512, 512), "16x16 Image Grid"); 
    

    sf::Sprite sprite(texture); 

    // Main Loop 
    while (window.isOpen()) { 
        sf::Event event; 
        while (window.pollEvent(event)) { 
            if (event.type == sf::Event::Closed) window.close(); 
        } 
        window.clear(); 

        //Disegniamo
        for (size_t row = 0; row < 16; ++row) { 
            for (size_t col = 0; col < 16; ++col) { 
                sprite.setTextureRect(sf::IntRect(col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE)); 
                sprite.setPosition(col * TILE_SIZE, row * TILE_SIZE); 
                window.draw(sprite); 
            } 
        } 
        window.display(); 
    } 
} 


int main() {
    try{
        std::string baba_babaisyou_v0 = "~/progetto/PROJECT_B/ToBeMoved/Images/Levels/baba-babaisyou-v0.png";
        createGridFromImage(baba_babaisyou_v0);
        return 0;
/*
    // Set up the window
    sf::RenderWindow window(sf::VideoMode({512, 512}), "Game Map"); //la finestra sarà quadrata, con 16*16 griglie da 32 pixel di lato per ognuna
    window.setVerticalSyncEnabled(true); // mi dà problemi "Setting vertical sync not supported" anche se lo metto
   
    // One-dimensional array representing the map (this could be your game level)
    const int level[] {
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };
    static_assert(std::size(level) == MapSize::width * MapSize::height);

    TileMap map;
    if (!map.load("/home/diegoarcari/labs/progetto/PROJECT_B/ToBeMoved/Images/Levels/baba-babaisyou-v0.png", sf::Vector2u(32, 32), level, 16, 16))
        throw std::runtime_error("Error loading map from [namelevel].png");

    // PARTE 2
    // Load textures (tiles)
    sf::Texture texture0, texture1, texture2, texture3;
    if (!texture0.loadFromFile("grass.png") || // Replace with actual paths to your images
        !texture1.loadFromFile("water.png") || 
        !texture2.loadFromFile("sand.png") || 
        !texture3.loadFromFile("rock.png")) {
        std::cerr << "Error loading textures!" << std::endl;
        return -1;
    }

    
    // lambda per creare l'array di texture
    const std::array<sf::Texture&, (+Baba_Is_Us::Type::ICON_NOUN_TYPE - 1)>& texarr{
        [](){std::array<sf::Texture&, (+Baba_Is_Us::Type::ICON_NOUN_TYPE - 1)> texarr {};
            for (sf::Texture& iter : texarr) {
            if (!iter.loadFromFile("")) throw std::runtime_error("Error loading textures in getTextureArray()");
            }
        }
    };
    
    std::vector<sf::Sprite> mapSprites{};
    mapSprites.reserve(256);
    for (int i = 0; i < (MapSize::width * MapSize::height); ++i) {
        sf::Sprite sprite;
        sprite.setTexture(texarr[map[i]]); // per ogni indice dell'array mappa assegna una sprite

        int x = (i % MapSize::width) * 32; // se ogni tile quadrata è 32 pixel di lato
        int y = (i / MapSize::width) * 32;

        sprite.setPosition(x, y); //in ogni cella la posizione è in alto a sx
        mapSprites.push_back(sprite);
    }
    FINE PARTE 2*/
/*
    // Main game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Clear the screen
        window.clear();

        // Draw all the sprites (map tiles)
        window.draw(map);

        // Display the rendered frame
        window.display();
    }

    return 0;
*/
    } 
    catch(const std::runtime_error& e) {std::cerr << e.what();}
}