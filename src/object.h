#pragma once
#include "dialogue.h"
#include "character.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "utils/structs.h"

class Object {
  public:
    
    Object();
    Object(int width, int height, bool collidable);
    ~Object();
    // may want to have a texture sheet as an argument in the constructor,
    // to do once we have a functioning texture manager

    int GetWidth();
    int GetHeight();
    int GetObjId();
    bool IsCollidable();
    Position GetPosition();

    // Returns a copy of the object.
    Object Copy();

    // Allows the player to interact with the object
    void InteractButton();

    // Check if the player is colliding with the object
    bool InteractCollision(Character character);

    void Render();

  protected:
    std::string textureId_; // string to link to texture map
    int width_, height_; // dimension in squares
    bool collidable_;
    Position position_; // possibly the up-left position of the object,
                        // subject to changes
    int obj_id;

};

// Object signalling map changes.
class Portal : public Object {
  public:
    Portal(int width, int height, int map_id);

  private:
    int map_id_;
};
