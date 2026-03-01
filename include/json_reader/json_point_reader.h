#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <string>

#include "json_reader/jsor_reader.h"

namespace trajectory::json {

class PointReader : IPointReader {
 public:
  PointReader(const std::string& file_name);

  Vec3D GetPointByIndex(std::size_t i) override;

  Vec3D GetPointById(std::size_t id) override;

  std::vector<Vec3D> GetPointsAsVector() override;
 
 private:
  void BuildToIndex_();

  void ConstructPointByIndex_(Vec3D& point, std::size_t i) const;

  QJsonArray json_arr_;
  bool is_open_{false};
  QHash<std::size_t, std::size_t> id_to_index_;
  
};

}