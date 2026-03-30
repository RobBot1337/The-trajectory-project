#ifndef AIR_SPACE_DATA_H
#define AIR_SPACE_DATA_H

#include <QVector>
#include <QHash>
#include <QSet>

#include <math/vec3D.h>

struct Point {
  Vec3D vec;
  std::size_t id {0};
};

struct AirCorridor {
  std::size_t id1{0};
  std::size_t id2{0};

  bool operator==(const AirCorridor& other) const {
    return (id1 == other.id1 && id2 == other.id2) ||
           (id1 == other.id2 && id2 == other.id1);
  }
};

struct Pvo {
  std::size_t id{0};
  Vec3D position{0, 0};
  unsigned int radius{0};
};

struct HighReliefZone {
  QVector<Vec3D> vertices;
};

struct AirSpace {
  QVector<Point> points;
  QSet<AirCorridor> air_corridors;
  QVector<Pvo> pvo_list;
  QVector<HighReliefZone> high_relief_zones;
};

inline uint qHash(const AirCorridor& corridor, uint seed = 0) {
    return ::qHash(corridor.id1, seed) ^ ::qHash(corridor.id2, seed);
}

#endif