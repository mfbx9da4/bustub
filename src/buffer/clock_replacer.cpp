//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// clock_replacer.cpp
//
// Identification: src/buffer/clock_replacer.cpp
//
// Copyright (c) 2015-2019, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//
#include "buffer/clock_replacer.h"

#include <iostream>
#include <string>

namespace bustub {

ClockReplacer::ClockReplacer(size_t num_pages) {
  frames = {};
  frames.reserve(num_pages);
  clock_hand = 0;
  size = 0;
  frame_table = {};
}

ClockReplacer::~ClockReplacer() = default;

bool ClockReplacer::Victim(frame_id_t *frame_id) {
  for (int i = 0; i < 2; i++) {
    for (const auto &n : frame_table) {
      if (n.first >= clock_hand) {
        clock_hand = n.first;
        if (n.second) {
          frame_table[n.first] = false;
        } else {
          *frame_id = n.first;
          frame_table.erase(n.first);
          size--;
          return false;
        }
      }
    }
    for (const auto &n : frame_table) {
      if (n.first < clock_hand) {
        clock_hand = n.first;
        if (n.second) {
          frame_table[n.first] = false;
        } else {
          *frame_id = n.first;
          frame_table.erase(n.first);
          size--;
          return false;
        }
      }
    }
  }
  return false;
}

void ClockReplacer::Pin(frame_id_t frame_id) {
  if (frame_table.count(frame_id) > 0) {
    frame_table.erase(frame_id);
    frames[frame_id] = false;
    size--;
  }
}

void ClockReplacer::Unpin(frame_id_t frame_id) {
  if (!frame_table[frame_id]) {
    frame_table[frame_id] = true;
    frames[frame_id] = true;
    size++;
  }
}

size_t ClockReplacer::Size() { return size; }

}  // namespace bustub
