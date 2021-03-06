#include "object.h"
#include "game.h"
#include "utils/texture_manager.h"

Object::Object() {} // TODO
Object::~Object() {}

Object::Object(int width, int height, bool collidable) {
    // Initializing all the attributes. We set x = y = 0 for the moment,
    // subject to change depending on whether or not we want it
    // as an argument in the constructor
    SetHitbox(0, 0);
    hitbox_.w = width;
    hitbox_.h = height;
    collidable_ = collidable;
    position_ = {0, 0};
}

Object::Object(std::string texture_id, int width, int height, bool collidable, int x, int y ) {
    SetHitbox(width, height);
    textureId_ = texture_id;
    hitbox_.w = width;
    hitbox_.h = height;
    collidable_ = collidable;
    position_ = {x, y};
}

int Object::GetWidth() {
    return hitbox_.w;
}

int Object::GetHeight() {
    return hitbox_.h;
}

int Object::GetObjId() {
    return obj_id;
}

bool Object::IsCollidable() {
    return collidable_;
}

Position Object::GetPosition() {
    return position_;
}

SDL_Rect Object::GetHitbox() {
    hitbox_.x = position_.x;
    hitbox_.y = position_.y;
    return hitbox_;
}

void Object::SetHitbox(int width, int height) {
    hitbox_.x = position_.x;
    hitbox_.y = position_.y;
    hitbox_.h = height;
    hitbox_.w = width;
}

Object Object::Copy() {
    Object new_object(hitbox_.w, hitbox_.h, collidable_);
    return new_object;
}

bool Object::CheckCollision(Character character) {
    // Checks if the object is collidable and if the character is currently colliding with it.SS
    if (!collidable_) return false;

    SDL_Rect character_hitbox_ = character.GetHitbox();
    bool intersection = SDL_HasIntersection(&hitbox_, &character_hitbox_);
    return intersection;
}

bool Object::CheckCollision(SDL_Rect hitbox) {
    // Checks if the object is collidable and if the character is currently colliding with it.SS
    if (!collidable_) return false;

    bool intersection = SDL_HasIntersection(&hitbox_, &hitbox);
    return intersection;
}

void Object::Render() {
    TextureManager::Instance()->DrawFrame(textureId_, {32, 0, 32, 32},
                                          {position_.x, position_.y, 32, 32},
                                          Game::renderer_);

}

// Used as placedholders 
void Object::Action1() {}
void Object::Action2() {}

Portal::Portal(int width, int height, int map_id) {
    hitbox_.w = width;
    hitbox_.h = height;
    map_id_ = map_id;
    collidable_ = false;
}

Switch::Switch(int width, int height, bool collidable, int x, int y, 
int offset, int interact_width, int interact_height) {
    SetHitbox(width, height);
    hitbox_.w = width;
    hitbox_.h = height;
    collidable_ = collidable;
    position_ = {x, y};

    SetField(offset, width, height);
}

SDL_Rect Switch::GetField() {
   return interact_field_;
}

void Switch::SetField(int offset, int height, int width) {
    interact_field_.x = offset;
    interact_field_.y = offset;
    interact_field_.h = height;
    interact_field_.w = width;
}

void Switch::KeyInteraction(Character character) {
    SDL_Rect character_hitbox_ = character.GetHitbox();
    bool intersection = SDL_HasIntersection(&interact_field_, &character_hitbox_);
    const Uint8* event_array = SDL_GetKeyboardState(nullptr);
    if (event_array[SDL_SCANCODE_E] && intersection) {
        Action2();
    }
}

void Switch::KeyInteraction(SDL_Rect hitbox) {
    bool intersection = SDL_HasIntersection(&interact_field_, &hitbox);
    const Uint8* event_array = SDL_GetKeyboardState(nullptr);
    if (event_array[SDL_SCANCODE_E] && intersection) {
        Action2();
    }
}