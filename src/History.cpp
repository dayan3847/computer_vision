//
// Created by dayan3847 on 3/21/23.
//

#include "History.h"


map<int, ImageStats> History::imageStatsMap = map<int, ImageStats>();

History::History(Mat &mask, vector<int> &labels) {
    this->mask = mask.clone();
    this->labels = vector<int>(labels);
}
