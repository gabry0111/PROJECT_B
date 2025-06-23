#ifndef MAP_HPP
#define MAP_HPP
#include "enum_objects.hpp"
#include "objects.hpp"
#include <SFML/Graphics.hpp>
#include <array>
#include <string_view>
#include <fstream>

using Position = std::pair<std::size_t, std::size_t>;

namespace MapSize {
    constexpr int width = 16;  // Number of tiles in the X direction = n° of columns
    constexpr int height = 16; // Number of tiles in the Y direction = n° of rows
    constexpr int depth = 2;   // Number of layers in the map
    constexpr int n_tiles = width * height; // Total number of tiles

    constexpr int TILE_SIZE = 32;
    constexpr int FRAMES_PER_ANIMATION = 3;
    constexpr int FRAME_TIME_MS = 150;
    
}
using MapGrid2D = std::array<std::array<int, MapSize::height>, MapSize::width>;

namespace Baba_Is_Us {

// va implementato un modo per cui il compilatore prenda il file dalla BUILD
    // così da semplificare l'azione che prende il percorso (di tipo std::string)
    inline std::array<std::string, 32> tilePaths { 
        "../../assets/png_PROGETTO/gifs/VOID_spritesheet.png",                  //0
        "../../assets/png_PROGETTO/gifs/BABA_move_up_spritesheet.png",          //1
        "../../assets/png_PROGETTO/gifs/BABA_move_down_spritesheet.png",        //2
        "../../assets/png_PROGETTO/gifs/BABA_move_right_spritesheet.png",       //3
        "../../assets/png_PROGETTO/gifs/BABA_move_left_spritesheet.png",        //4
        "../../assets/png_PROGETTO/gifs/BABA_spritesheet_up.png",               //5
        "../../assets/png_PROGETTO/gifs/BABA_spritesheet_down.png",             //6
        "../../assets/png_PROGETTO/gifs/BABA_spritesheet_right.png",            //7
        "../../assets/png_PROGETTO/gifs/BABA_spritesheet_left.png",             //8
        "../../assets/png_PROGETTO/gifs/DOOR_spritesheet.png",                  //9
        "../../assets/png_PROGETTO/gifs/FLAG_spritesheet.png",                  //10
        "../../assets/png_PROGETTO/gifs/GEAR_spritesheet.png",                  //11
        "../../assets/png_PROGETTO/gifs/KEY_spritesheet.png",                   //12
        "../../assets/png_PROGETTO/gifs/LAVA_spritesheet.png",                  //13
        "../../assets/png_PROGETTO/gifs/LEVER_LEFT_spritesheet.png",            //14
        "../../assets/png_PROGETTO/gifs/LEVER_RIGHT_spritesheet.png",           //15
        "../../assets/png_PROGETTO/gifs/PENDULUM_spritesheet.png",              //16
        "../../assets/png_PROGETTO/gifs/ROCK_spritesheet.png",                  //17
        "../../assets/png_PROGETTO/gifs/WALL_spritesheet.png",                  //18
        "../../assets/png_PROGETTO/text/BABA_text_spritesheet.png",             //19
        "../../assets/png_PROGETTO/text/DEFEAT_text_spritesheet.png",           //20
        "../../assets/png_PROGETTO/text/FLAG_text_spritesheet.png",             //21
        "../../assets/png_PROGETTO/text/HOT_text_spritesheet.png",              //22
        "../../assets/png_PROGETTO/text/IS_text_spritesheet.png",               //23
        "../../assets/png_PROGETTO/text/LAVA_text_spritesheet.png",             //24
        "../../assets/png_PROGETTO/text/MELT_text_spritesheet.png",             //25
        "../../assets/png_PROGETTO/text/PUSH_text_spritesheet.png",             //26
        "../../assets/png_PROGETTO/text/ROCK_text_spritesheet.png",             //27
        "../../assets/png_PROGETTO/text/STOP_text_spritesheet.png",             //28
        "../../assets/png_PROGETTO/text/WALL_text_spritesheet.png",             //29
        "../../assets/png_PROGETTO/text/WIN_text_spritesheet.png",              //30
        "../../assets/png_PROGETTO/text/YOU_text_spritesheet.png"               //31
    };

    
    inline std::size_t findLastNoun(const std::vector<Type>& types) {
        std::size_t last {};
        for (std::size_t i{}; i < types.size(); ++i) {
            if (+types[i] > +Type::Void && +types[i] < +Type::ICON_NOUN_TYPE) { 
                last = i;
            }
        }
        std::cerr << "findLastNoun(): " << last << ", type = " << types[last] << '\n';
        return last; 
    }

    inline Type iconToAll(Type type) {
        switch(type){
            case Type::Icon_Void:   return Type::Void;
            case Type::Icon_Baba:   return Type::Baba;
            case Type::Icon_Defeat: return Type::Defeat;
            case Type::Icon_Flag:   return Type::Flag;
            case Type::Icon_Hot:    return Type::Hot;
            case Type::Icon_Is:     return Type::Is;
            case Type::Icon_Lava:   return Type::Lava;
            case Type::Icon_Melt:   return Type::Melt;
            case Type::Icon_Push:   return Type::Push;
            case Type::Icon_Rock:   return Type::Rock;
            case Type::Icon_Stop:   return Type::Stop;
            case Type::Icon_Wall:   return Type::Wall;
            case Type::Icon_Win:    return Type::Win;
            case Type::Icon_You:    return Type::You;
            default: throw(std::runtime_error("iconToAll(): scimpanzini bananini"));
        }
    }

    class Map{
    private :
        // N.B: [0][1][2] accedi a depth = 0; x (width) = 1; y (height) = 2
        std::array<MapGrid2D, MapSize::depth> m_grid; 
        // N.B: [1][2] accedi a x (width) = 1; y (height) = 2
        std::array<std::array<Objects, MapSize::height>, MapSize::width> m_objects;

    public:
        bool isOutOfBoundary(std::size_t x, std::size_t y) const;

        std::vector<sf::Texture> textures{};
        std::vector<int> frameCounts{};
        int nth_frame{};
        std::vector<sf::Sprite> tileSprites{};

        Map() = default;
        // alloca lo spazio di m_objects per (MapSize::width * MapSize::height) elementi
        Map(std::string_view);
        
        void spriteOverlay();
        // inizializza ogni Objects di m_objects al tipo della corrispondente cella di new_map_grid
        // da chiamare appena creata un'istanza di Map
        const std::array<MapGrid2D, MapSize::depth>& getm_grid() const;
        std::array<MapGrid2D, MapSize::depth>& accessm_grid() ;
        const std::array<std::array<Objects, MapSize::height>, MapSize::width>& getm_objects() const;
        std::array<std::array<Objects, MapSize::height>, MapSize::width>& accessm_objects() ;
        void setTextures();
        void setSprites();
        void redraw(sf::Clock &);
        const std::vector<sf::Sprite>& getTileSprites() const;
        sf::Sprite& accessWhichSpriteIsInPosition(Position&);
        // resetta la mappa (se PlayState::Invalid o se cambia livello)
        // N.B: ogni oggetto può avere proprietà che devono essere tolte richiamando poi la funzione apposita che controlla le regole nella mappa
        void Reset(const std::array<std::array<int,MapSize::width>,MapSize::height>& ); // può diventare constexpr
        
        // aggiungi un oggetto (constexpr)
        void addObject(Position position, Type type);

        // rimuovi un oggetto (constexpr)
        void resetObject(Position position);

        // Quale oggetto c'è in quella posizione?
        Objects& At(std::size_t x, std::size_t y);
        const Objects& At(std::size_t x, std::size_t y) const; // NON può diventare constexpr (m_objects è vector)

        // restituisce le posizioni di uno specifico tipo (TRANNE I BLOCCHI)
        const std::vector<Position> getPositions(Type) const; // non conviene diventare constexpr (dovrebbe essere template di array)
    };

    std::size_t indexToBeDrawn(const std::size_t i);


}
#endif