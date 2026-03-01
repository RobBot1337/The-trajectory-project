#ifndef BRUTE_FORCE_H
#define BRUTE_FORCE_H

#include <execution>
#include <limits>
#include <string>
#include <vector>

#include "json_reader/jsor_reader.h"

namespace trajectory::algorithm {

class BruteForce {
 public:
  BruteForce(IPointReader& json_reader);

  void CalculatePath(const std::string& path);

  std::vector<std::size_t> GetAsIndexVector() { return best_path_indices_; }

  double GetBestDistance() const { return best_distance_; }

  void SetClosedLoop(bool closed) { closed_loop_ = closed; }

  bool IsClosedLoop() const { return closed_loop_; }

 private:
  void PrecomputeDistances_();

  double DistanceBetween_(const Vec3D& a, const Vec3D& b) const;

  IPointReader& json_reader_;
  std::vector<Vec3D> points_;
  std::vector<std::vector<double>> distance_matrix_;
  std::vector<std::size_t> best_path_indices_;
  double best_distance_;
  bool closed_loop_ = true;
};

}

#endif