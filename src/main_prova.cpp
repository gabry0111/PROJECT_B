#include "enum_objects.hpp"
#include "objects.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include <iostream>
#include <stdexcept>
#include "map.hpp"
#include "game.hpp"
using namespace Baba_Is_Us;


namespace MapSize {
    constexpr int width = 16;  // Number of tiles in the X direction
    constexpr int height = 16; // Number of tiles in the Y direction
}
/*
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
// Map the m_textures based on the integer values
const std::array<sf::Texture&, (+Baba_Is_Us::Type::ICON_NOUN_TYPE - 1)>& getTextureArray(){
    std::array<sf::Texture*, (+Baba_Is_Us::Type::ICON_NOUN_TYPE - 1)> texarr {};
    for (sf::Texture* iter : texarr) {
        if (! iter.loadFromFile("")) throw std::runtime_error("Error loading m_textures in getTextureArray()");
    }

}
FINE PARTE 2*/

/* ------------------------------ createGrid metodo texture ---------------------------------- */
/*
void createGridFromImage(const std::string& imageFilePath) { 
    //importa l'immagine dal file
    sf::Texture texture; 
    if (!texture.loadFromFile(imageFilePath)) { 
        std::cerr << "Error loading image: " << imageFilePath << '\n'; 
        return; 
    } 
    
    const int TILE_SIZE = 16; 
    
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
        for (int row = 0; row < 16; ++row) { 
            for (int col = 0; col < 16; ++col) { 
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
        std::string baba_babaisyou_v0 = "~/progetto/PROJECT_B/ToBeMoved/Images/Levels/tileset.png";
        createGridFromImage(baba_babaisyou_v0);
        return 0;
    } 
    catch(const std::runtime_error& e) {std::cerr << e.what();}
}
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
    // Load m_textures (tiles)
    sf::Texture texture0, texture1, texture2, texture3;
    if (!texture0.loadFromFile("grass.png") || // Replace with actual paths to your images
        !texture1.loadFromFile("water.png") || 
        !texture2.loadFromFile("sand.png") || 
        !texture3.loadFromFile("rock.png")) {
        std::cerr << "Error loading m_textures!" << std::endl;
        return -1;
    }

    
    // lambda per creare l'array di texture
    const std::array<sf::Texture&, (+Baba_Is_Us::Type::ICON_NOUN_TYPE - 1)>& texarr{
        [](){std::array<sf::Texture&, (+Baba_Is_Us::Type::ICON_NOUN_TYPE - 1)> texarr {};
            for (sf::Texture& iter : texarr) {
            if (!iter.loadFromFile("")) throw std::runtime_error("Error loading m_textures in getTextureArray()");
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
    FINE PARTE 2




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
 
                                ////////////////////////
                                /* ------ main -------*/
/*
class Map : public sf::Drawable, public sf::Transformable {
    private: 
    std::size_t m_width{MapSize::width};
    std::size_t m_height{MapSize::height};
    // std::vector<Objects> m_initial_objects {}; // se resetti il livello
    std::vector<Objects> m_current_objects {}; // cambio di livello: verificare quali oggetti cambiano invece di distruggere e ricreare tutto

    protected :
    void draw(sf::RenderTarget&, sf::RenderStates) const;

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;

    public :
    Map() = default;
    Map(std::size_t width, std::size_t height);
    bool load(const std::array<int,256>& level);
};


Map::Map(std::size_t width, std::size_t height)
    : m_width(width), m_height(height)
{
    //m_initial_objects.reserve(m_width * m_height);
    m_current_objects.reserve(m_width * m_height);

    for (std::size_t i = 0; i < m_width * m_height; ++i)
    {
        //m_initial_objects.emplace_back(
            //std::vector<Type>{ Type::Void });
        m_current_objects.emplace_back(
            std::vector<Type>{Type::Void});
    }
}
bool Map::load(const std::array<int, 256>& level) {
    std::size_t iter {};
    for(std::size_t iter : level) {
        //m_initial_objects.emplace_back(static_cast<Type>(iter))
        m_current_objects.emplace_back(static_cast<Type>(iter));
    }
}
void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const{
        // apply the transform
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = &m_tileset;

        // draw the vertex array
        target.draw(m_vertices, states);
    }
*/
/* ALTRO METODO
class TextureManager {
private :
    std::vector<sf::Texture&> m_textures; // conserva tutte le texturesheet (animazioni) e singole texture (statiche) qui
    std::vector<int> m_frame_count_per_anim;    // =1 se statica; >1 se animazione
    
public:
    TextureManager() = default;
    TextureManager(std::vector<sf::Texture&> text_arr, std::vector<int> count) : m_textures{text_arr}, m_frame_count_per_anim{count} {};

// da un const std::string& (array?) aggiorna se la texture è una spritesheet (cioè sarà un'animazione) e 
    int loadTile(const std::string& level1D) {
        sf::Texture texture;
        if(!texture.loadFromFile(level1D)) {
            std::cerr << "Failed to load texture: " << level1D << "\n";
            return -1;
        }
        constexpr std::size_t frameSize = 32; // assumiamo ogni sprite sia 32 pixels
        const int frames {texture.getSize().x / frameSize};
        m_textures.emplace_back(texture);
        m_frame_count_per_anim.emplace_back(frames > 1 ? frames : 1);
        return static_cast<int>(m_textures.size() - 1);
    }

    std::optional<sf::Texture> getTexture(int ID) {
        if (ID < 0 || ID >= static_cast<int>(m_textures.size())) return ;
        return m_textures[ID];
    }
};

    void loadMapFrom1DArray(
    const std::array<int, (MapSize::height * MapSize::width)>& level,
    TextureManager& textureManager,
    std::vector<sf::Sprite>& outSprites
    )
{
    outSprites.clear();
    for (size_t i = 0; i < level.size(); ++i) {
        int textID = level[i];
        std::optional<sf::Texture> texture = textureManager.getTexture(textID);
        if (!texture) {
            std::cerr << "Texture ID " << textID << " not found.\n";
            continue;
        }
        sf::Sprite sprite;
        sprite.setTexture(*texture);

        int x = (i % MapSize::height) * MapSize::width;
        int y = (i / MapSize::height) * MapSize::width;
        sprite.setPosition(static_cast<float>(x), static_cast<float>(y));
        outSprites.push_back(sprite);
    }
}


int main() {
    sf::RenderWindow window(sf::VideoMode(640, 480), "SFML Texture Manager");

    TextureManager tm;

    // Load textures in order, so their IDs correspond to indices:
    // 0 -> grass.png
    // 1 -> water.png
    tm.loadTile("assets/grass.png");  // ID 0
    tm.loadTile("assets/water.png");  // ID 1

    // Example fire animation loading (not used in map here)
    tm.loadTile({
        "/home/diegoarcari/labs/progetto/PROJECT_B/png_PROGETTO/BABA_spritesheet.png"
    });

    // Now use 0s and 1s directly in the mapLayout
    std::array<int, 256> mapLayout{
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
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };

    std::vector<sf::Sprite> sprites;
    loadMapFrom1DArray(mapLayout, tm, sprites);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        window.clear();
        for (const auto& sprite : sprites) {
            window.draw(sprite);
        }
        window.display();
    }

    return 0;

}
 FINE ALTRO METODO */

/* METODO CONCRETE_TILE_MAP
int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode({512, 512}), "Tilemap");

    // define the level with an array of tile indices
    std::array<int, 256> level = {
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
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    // create the tilemap from the level definition

    class ConcreteTileMap : public TileMap {
    public:
        using TileMap::TileMap;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
            // Implement the draw method or call the base implementation if available
            TileMap::draw(target, states);
        }
    };
    ConcreteTileMap map;

    

    if (!map.load(level))
        return -1;
    Game game;

    
    std::vector<sf::Texture> texarr(9);
    //loadTexture();
    for(auto iii : level) {switch(iii) {
        case 1 : {texarr[iii].loadFromFile("/home/diegoarcari/labs/progetto/PROJECT_B/png_PROGETTO/BABA_spritesheet.png"); break;}
        case 2 : {texarr[iii].loadFromFile("png_PROGETTO/FLAG_spritesheet.png"); break;}
        case 3 : {texarr[iii].loadFromFile("png_PROGETTO/LAVA_spritesheet.png"); break;}
        case 4 : {texarr[iii].loadFromFile("png_PROGETTO/ROCK_spritesheet.png"); break;}
        case 5 : {texarr[iii].loadFromFile("png_PROGETTO/WALL_spritesheet.png"); break;}
        default : {break;}
    }
    }

    
    std::vector<sf::Sprite> mapSprites{};
    mapSprites.reserve(256);
    for (int i = 0; i < (MapSize::width * MapSize::height); ++i) {
        sf::Sprite sprite;
        sprite.setTexture(texarr[level[i]]); // per ogni indice dell'array mappa assegna una sprite

        int x = (i % MapSize::width) * 32; // se ogni tile quadrata è 32 pixel di lato
        int y = (i / MapSize::width) * 32;

        sprite.setPosition(x, y); //in ogni cella la posizione è in alto a sx
        mapSprites.push_back(sprite);
    }
    //FINE PARTE 2





    // run the main loop
    while (window.isOpen())
    {
        // handle events
        game.update(window);
        game.render(window, map);

    }
    return 0;
}
    */

                        ///////////////////////
                        // ----- METODO SPRITES ----- //
int main() {
    constexpr int TILE_SIZE = 32;
    constexpr int FRAME_TIME_MS = 150;

    std::array<int, 256> level = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    std::vector<std::string> tilePaths {
    "/home/Dprogetto/PROJECT_B/png_PROGETTO/BABA_spritesheet.png"
    };

    sf::RenderWindow window(sf::VideoMode({512, 512}), "Oui");

    std::vector<sf::Texture> textures{};
    std::vector<int> frameCounts{};
    std::vector<int> current_frame_per_tile_ID{}; // tengo traccia di un unico frame per ogni object, quindi ogni istanza di ciascun oggetto si aggiornerà insieme

    
    // load textures e tieni conto, per ogni indice, della quantità di frame
    for (std::size_t i{}; i < tilePaths.size(); ++i) {
        sf::Texture texture;
        if (!texture.loadFromFile(tilePaths[i])) {
            std::cerr << "Failed to load " << tilePaths[i] << "\n";
            return -1;
        }

        int width = static_cast<int>(texture.getSize().x);
        int frames = std::max(1, width / TILE_SIZE);
        textures.emplace_back(texture);
        frameCounts.emplace_back(frames);
        current_frame_per_tile_ID.push_back(0); // ogni tile ID partirà dal frame n° 0
    }
    // converti le tileID in sprite
    std::vector<sf::Sprite> tileSprites;

    for (std::size_t i = 0; i < level.size(); ++i) {
        int tileID {level[i]}; //ID = elemento di level
        if (tileID < 0 || tileID >= static_cast<int>(textures.size())) continue;

        sf::Sprite sprite;
        sprite.setTexture(textures[static_cast<std::size_t>(tileID)]);
        sprite.setTextureRect({0, 0, TILE_SIZE, TILE_SIZE});

        int x = (static_cast<int> (i) % MapSize::width) * TILE_SIZE;
        int y = (static_cast<int> (i) / MapSize::height) * TILE_SIZE;
        
        sprite.setPosition(static_cast<float>(x), static_cast<float>(y));

        tileSprites.emplace_back(sprite); // alla fine avrà level.size() elementi, ognuno con una sprite
    }

    // Animation loop
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        if (clock.getElapsedTime().asMilliseconds() >= FRAME_TIME_MS) {
            for (std::size_t i{}; i < frameCounts.size(); ++i) {
                if (frameCounts[i] > 1) { // se in i c'è un'animazione
                    current_frame_per_tile_ID[i] = (current_frame_per_tile_ID[i] + 1) % frameCounts[i]; //frameCounts[i] sarà sempre 3 se è animazione, quindi prova a calcolare
                
                }
            }
            clock.restart();
        }
        for (std::size_t i{}; i < tileSprites.size(); ++i) {
            int tileID = level[i];
            int frame = current_frame_per_tile_ID[static_cast<size_t>(tileID)];
            tileSprites[i].setTextureRect({frame * TILE_SIZE, 0,TILE_SIZE, TILE_SIZE});
            // se vogliamo ruotare l'oggetto, aggiungere funzioni qui. (con switch per comandi WASD?)
        }

        window.clear();
        for (const auto& sprite : tileSprites)
            window.draw(sprite);
        window.display();
    }

    return 0;
}
