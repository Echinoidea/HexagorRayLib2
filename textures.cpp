#pragma once
#include <iostream>
#include <vector>
#include <raylib.h>
#include <hex.cpp>
#include <constants.cpp>

using namespace constants;

namespace textures {
  std::vector<Image> sources; 
  std::vector<Texture> textures;


  void LoadImages() {
    // TODO: Load all images from \assets and load into map. Then, reference textures by name with key

    sources[0] = LoadImage(".\\assets\\mountains.png");
    sources[1] = LoadImage(".\\assets\\village.png");

    int resizeFactor = 4;

    ImageResize(&sources[0], HEX_RADIUS - (HEX_RADIUS / resizeFactor), HEX_RADIUS - (HEX_RADIUS / resizeFactor));
    ImageResize(&sources[1], HEX_RADIUS - (HEX_RADIUS / resizeFactor), HEX_RADIUS - (HEX_RADIUS / resizeFactor));

    textures[0] = LoadTexture(NULL);
    textures[1] = LoadTextureFromImage(sources[0]);
    textures[2] = LoadTextureFromImage(sources[1]);
  }

  Texture2D getTexture(Hex hex) {
    Texture2D tx;

    if (hex.featureState == HFS_MOUNTAIN) {
      tx = textures[1];
    }
    else if (hex.featureState == HFS_VILLAGE) {
      tx = textures[2];
    }
    else {
      tx = textures[0];
    }
    
    return tx;
  }
}