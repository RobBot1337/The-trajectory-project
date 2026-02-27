#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <string>

#include "ijsor_reader.h"
// #include "vec3D.h"

class JsonPointReader : IJsonPointReader {
 private:
  void BuildToIndex_();

  void ConstructPointByIndex_(Vec3D& point, std::size_t i) const;

  QJsonArray json_arr_;
  bool is_open_{false};
  QHash<std::size_t, std::size_t> id_to_index_;
};