#include "brute_force.h"

#include <execution>
#include <limits>
#include <string>
#include <vector>

#include "json_reader/ijsor_reader.h"

BruteForceAlgorithm::BruteForceAlgorithm(IJsonPointReader& json_reader)
    : json_reader_{json_reader},
      points_{json_reader.GetPointsAsVector()},
      best_path_indices_{},
      best_distance_{std::numeric_limits<double>::max()} {
  PrecomputeDistances_();
}

void BruteForceAlgorithm::CalculatePath(const std::string& path) {
  std::vector<std::size_t> indices(points_.size());
  for (std::size_t i = 0; i != points_.size(); ++i) {
    indices[i] = i;
  }

  best_distance_ = std::numeric_limits<double>::max();

  do {
    double current_distance = 0.0;

    for (std::size_t i = 0; i + 1 != indices.size(); ++i) {
      current_distance += distance_matrix_[indices[i]][indices[i + 1]];
    }

    if (indices.size() > 2) {
      current_distance += distance_matrix_[indices.back()][indices.front()];
    }

    if (current_distance < best_distance_) {
      best_distance_ = current_distance;
      best_path_indices_ = indices;
    }

  } while (std::next_permutation(indices.begin() + 1, indices.end()));

  if (IsClosedLoop()) {
    best_path_indices_.push_back(best_path_indices_.front());
  }
}

void BruteForceAlgorithm::PrecomputeDistances_() {
  size_t n = points_.size();
  distance_matrix_.resize(n, std::vector<double>(n, 0.0));

  for (size_t i = 0; i != n; ++i) {
    for (size_t j = i + 1; j != n; ++j) {
      double dist = DistanceBetween_(points_[i], points_[j]);
      distance_matrix_[i][j] = dist;
      distance_matrix_[j][i] = dist;
    }
  }
}

double BruteForceAlgorithm::DistanceBetween_(const Vec3D& a,
                                             const Vec3D& b) const {
  double dx = a.x - b.x;
  double dy = a.y - b.y;
  double dz = a.z - b.z;
  return std::sqrt(dx * dx + dy * dy + dz * dz);
}