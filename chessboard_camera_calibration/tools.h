//
// Created by dayan3847 on 5/21/23.
//

#ifndef CHESSBOARD_CAMERA_CALIBRATION_TOOLS_H
#define CHESSBOARD_CAMERA_CALIBRATION_TOOLS_H

namespace my_tools {
    void getCenteredCoordinates(int count, double distance, double outCoords[]) {
        double init = (count - 1.) / 2 * distance * -1;
        for (int i = 0; i < count; ++i) {
            outCoords[i] = init + i * distance;
        }
    }
}


#endif //CHESSBOARD_CAMERA_CALIBRATION_TOOLS_H
