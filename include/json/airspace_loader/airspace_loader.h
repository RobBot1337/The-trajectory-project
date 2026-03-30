#ifndef AIRSPACE_LOADER_H
#define AIRSPACE_LOADER_H

#include <string>
#include <tuple>

#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QSet>

#include "math/vec3D.h"
#include <air_space/air_space_data.h>

class AirspaceLoader {
 public:
  AirspaceLoader() = default;

  static AirSpace LoadFrom(const std::string& path);

 private:
  static AirSpace _ConstructAirspace(QJsonArray& arr);
};

#endif