#include <vector>
#include <string>

#include "math/vec3D.h"

namespace trajectory::json {

class IPointReader {
 public:
  virtual Vec3D GetPointByIndex(std::size_t i) const = 0;

  virtual Vec3D GetPointById(std::size_t id) const = 0;

  virtual std::vector<Vec3D> GetPointsAsVector() const = 0;

  virtual ~IPointReader() = default;
};

}