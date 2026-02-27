#include "json_reader.h"

JsonPointReader::JsonPointParser(const std::string& file_name) {
  QFile file(file_name.c_str());
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    is_open_ = false;
    return;
  }

  QByteArray json_data = file.readAll();
  file.close();

  QJsonParseError parser_error;
  QJsonDocument document = QJsonDocument::fromJson(json_data, &parser_error);

  if (parser_error.error != QJsonParseError::NoError || !document.isArray()) {
    is_open_ = false;
  } else {
    json_arr_ = document.array();
    BuildToIndex_();
  }
}

Vec3D JsonPointReader::GetPointByIndex(std::size_t i) const {
  Vec3D point;
  if (i < json_arr_.size()) {
    ConstructPointByIndex_(point, i);
  }
  return point;
}

Vec3D JsonPointReader::GetPointById(std::size_t id) const {
  Vec3D point;
  if (id_to_index_.contains(id)) {
    ConstructPointByIndex_(point, id_to_index_[id]);
  }
  return point;
}

std::vector<Vec3D> JsonPointReader::GetPointsAsVector() const {
  std::vector<Vec3D> result(json_arr_.size());
  for (std::size_t i{0}; i != json_arr_.size(); ++i) {
    result.push_back(GetPointByIndex(i));
  }
  return result;
}

void JsonPointReader::BuildToIndex_() {
  for (std::size_t i{0}; i != json_arr_.size(); ++i) {
    QJsonObject obj = json_arr_[i].toObject();
    std::size_t id = obj["id"].toInt(-1);

    if (id == -1) throw std::runtime_error("bad id");

    if (id_to_index_.contains(id))
      throw std::runtime_error("two points with equal ids");

    id_to_index_[id] = i;
  }
}

void JsonPointReader::ConstructPointByIndex_(Vec3D& point, std::size_t i) const {
  QJsonObject obj = json_arr_[i].toObject();
  point.x = obj["x"].toInt(0);
  point.y = obj["y"].toInt(0);
  point.z = obj["z"].toInt(0);
}
