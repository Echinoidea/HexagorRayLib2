#pragma once

#include <iostream>
#include <hex.cpp>
#include <vector>
#include <raylib.h>
#include <math.h>
#include <constants.cpp>

using namespace constants;

/// @brief A Board is comprised of a 2D array of Hexes with a width of N.
class Board {
 public:

  Hex hexBoard[N][N];

  Board() {}

  Board(int maxMountains, int maxVillages) {
    fillBoard();
    addFeatures(maxMountains, maxVillages);
  }

  /// @brief Overloaded verion of the private function updateColor to allow one Hex to be excluded.
  /// @param exclude The Hex to exclude during iteration.
  void updateColor(Hex exclude) {
    Hex currentHex;

    for (int q = 0; q < N; q++) {
      for (int r = 0; r < N; r++) {
        currentHex = hexBoard[r][q];
        
        if (!currentHex.isEqual(exclude)) {
          currentHex.color = currentHex.getColor();
        }
      }
    }
  }

  Hex getHexFromPixel2(Board* board, Vector2 offset) {
    Vector2 mousePosition = GetMousePosition();

    float horizontalOffset = (sin(PI/3) * HEX_RADIUS);
    int verticalOffset = 75;

    std::vector<Vector2> circles;

    for (int r = 0; r < N; r++) {
      for (int q = 0; q < N; q++) {
        circles.push_back((Vector2) {
          .x = offset.x + (horizontalOffset * r) + (float)(q) * (horizontalOffset * 2),//(cos(PI/6) * 100),
          .y = offset.y + (float)(r) * verticalOffset
        });
      }
    }

    // std::cout << "Click position: " << mousePosition.x << ", " << mousePosition.y << std::endl;

    Vector2 closestCircle;

    // Calculate distance from mousePosition to each Hex. Find least distance. If distance < HEX_RADIUS, then it is clicking that circle

    float closestDistance = INT_MAX;
    float distance;

    std::vector<Vector2> closeCircles;

    for (unsigned i = 0; i < circles.size(); i++) {
      distance = calcDistance(mousePosition, circles.at(i));
      //std::cout << "Distance between click and (" << circles.at(i).x << ", " << circles.at(i).y << "): " << distance << std::endl;
      if (distance < closestDistance) {
        closestDistance = distance;
        if (closestDistance <= HEX_RADIUS) {
          closestCircle = circles.at(i);
        }
      }
    }
    /*
    .x = offset.x + (horizontalOffset * hex.r) + (float)(hex.q) * (horizontalOffset * 2), //(cos(PI/6) * 100),
    .y = offset.y + (float)(hex.r) * verticalOffset
    */

   

    // Use the formulas from main "hexToDrawPosition" to solve for r and q rather than x and y

    float r = ((closestCircle.y / verticalOffset) - (offset.y / verticalOffset));
    float q = ((closestCircle.x / (2 * horizontalOffset)) - (offset.x / (2 * horizontalOffset)) - (r / 2));

    return board->hexBoard[(int)round(r)][(int)round(q)];
  }

  Vector2 getHexFromPixel(Vector2 point, Vector2 offset) {
    Vector2 mousePosition = GetMousePosition();

    float horizontalOffset = (sin(PI/3) * HEX_RADIUS);
    int verticalOffset = HEX_RADIUS + (HEX_RADIUS / 2);

    std::vector<Vector2> circles;

    for (int r = 0; r < N; r++) {
      for (int q = 0; q < N; q++) {
        circles.push_back((Vector2) {
          .x = offset.x + (horizontalOffset * r) + (float)(q) * (horizontalOffset * 2),//(cos(PI/6) * 100),
          .y = offset.y + (float)(r) * verticalOffset
        });
      }
    }

    // std::cout << "Click position: " << mousePosition.x << ", " << mousePosition.y << std::endl;

    Vector2 closestCircle;

    // Calculate distance from mousePosition to each Hex. Find least distance. If distance < HEX_RADIUS, then it is clicking that circle

    float closestDistance = INT_MAX;
    float distance;

    std::vector<Vector2> closeCircles;

    for (unsigned i = 0; i < circles.size(); i++) {
      distance = calcDistance(mousePosition, circles.at(i));
      //std::cout << "Distance between click and (" << circles.at(i).x << ", " << circles.at(i).y << "): " << distance << std::endl;
      if (distance < closestDistance) {
        closestDistance = distance;
        if (closestDistance <= HEX_RADIUS) {
          closestCircle = circles.at(i);
        }
      }
    }
    
    // std::cout << "Closest circle: " << (int)round(closestCircle.x) << ", " << (int)round(closestCircle.y) << std::endl;

    /*
    .x = offset.x + (horizontalOffset * hex.r) + (float)(hex.q) * (horizontalOffset * 2), //(cos(PI/6) * 100),
    .y = offset.y + (float)(hex.r) * verticalOffset
    */

    // Use the formulas from main "hexToDrawPosition" to solve for r and q rather than x and y

    float r = ((closestCircle.y / verticalOffset) - (offset.y / verticalOffset));
    float q = ((closestCircle.x / (2 * horizontalOffset)) - (offset.x / (2 * horizontalOffset)) - (r / 2));

    //printf("NEW : %d, %d\n", q, r);

    return (Vector2) {q, r};
  }

  Vector2 hexToPixel(Hex hex, Vector2 offset) {
    float horizontalOffset = (sin(PI/3) * HEX_RADIUS);
    int verticalOffset = 75;

    return (Vector2) {
      .x = offset.x + (horizontalOffset * hex.r) + (float)(hex.q) * (horizontalOffset * 2),//(cos(PI/6) * 100),
      .y = offset.y + (float)(hex.r) * verticalOffset
    };
  }

  

 private:

  int mountainCount = 0;  // Number of mountains currently on the board.
  int villageCount = 0;   // Number of villages currently on the board.

  /// @brief Populate the array with Hexes.
  void fillBoard() {
    for (int r = 0; r < N; r++) {
      for (int q = 0; q < N; q++) {
        int s = (q * -1) - r;

        hexBoard[r][q] = Hex(q, r, s);
      }
    }
  }

  /// @brief Add mountains and villages randomly around the board.
  /// @param maxMountains Number of mountains to add to the map.
  /// @param maxVillages Number of villages to add to the map.
  void addFeatures(int maxMountains, int maxVillages) {
    int randR = 0;
    int randQ = 0;
    int whichFeature = 0;  // 0 for mountain, 1 for village

    Hex currentHex;

    for (int i = 0; i < N * N; i++) {
      randR = GetRandomValue(0, N - 1);
      randQ = GetRandomValue(0, N - 1);

      whichFeature = GetRandomValue(0, 1);

      currentHex = hexBoard[randR][randQ];

      if (currentHex.featureState != HFS_EMPTY) {
        continue;
      }

      if (whichFeature == 0 && mountainCount < maxMountains) {
        currentHex.featureState = HFS_MOUNTAIN;
        mountainCount++;
      }
      else if (whichFeature == 1 && villageCount < maxVillages) {
        currentHex.featureState = HFS_VILLAGE;
        villageCount++;
      }
    }

    /*for (int i = 0; i < N * N; i++) {
      int mOrV = GetRandomValue(0, 1);
      int rq = GetRandomValue(0, N);
      int rr = GetRandomValue(0, N); 
      
      if (mOrV == 0 && mountainCount < mountainCount_ && hexBoard[rr][rq].featureState == HFS_EMPTY) {
        hexBoard[rr][rq].featureState = HFS_MOUNTAIN;
        mountainCount++;
        //hexBoard[rr][rq].color = hexBoard[rr][rq].getColor();
        printf("Created new mountain at %d, %d\n", rr, rq);
      }

      if (mOrV == 1 && villageCount < villageCount_ && hexBoard[rr][rq].featureState == HFS_EMPTY) {
        hexBoard[rr][rq].featureState = HFS_VILLAGE;
        villageCount++;
        //hexBoard[rr][rq].color = COLOR_HFS_VILLAGE;
        printf("Created new village at %d, %d\n", rr, rq);
      }
    }*/
  }

  /// @brief Iterate across the entire board and update each Hex's color to the appropriate one.
  void updateColor() {
    Hex currentHex;

    for (int q = 0; q < N; q++) {
      for (int r = 0; r < N; r++) {
        currentHex = hexBoard[r][q];
        
        currentHex.color = currentHex.getColor();
      }
    }
  }

  // /// @brief Iterate across the entire board and update each Hex's texture to the appropriate one.
  // void updateTextures() {
  //   Hex& currentHex;

  //   for (int q = 0; q < N; q++) {
  //     for (int r = 0; r < N; r++) {
  //       currentHex = hexBoard[r][q];

        
  //     }
  //   }
  // }


  float calcDistance(Vector2 a, Vector2 b) {
    return sqrt(pow((b.x - a.x), 2) + pow((b.y - a.y), 2));
  }
};
