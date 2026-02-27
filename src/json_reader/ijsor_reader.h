#include <vector>
#include <string>

#include "math/vec3D.h"

class IJsonPointReader {
 public:
  IJsonPointReader(const std::string& file_name);

  Vec3D GetPointByIndex(std::size_t i) const;

  Vec3D GetPointById(std::size_t id) const;

  std::vector<Vec3D> GetPointsAsVector() const;
};