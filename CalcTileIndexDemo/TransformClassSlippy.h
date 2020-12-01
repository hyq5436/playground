#pragma once
/*
 * Created by CntChen 2016.04.30
 * 参考资料：http://wiki.openstreetmap.org/wiki/Slippy_map_tilenames
 * 适用地图：高德，Google Map，OSM
 */
#define  _USE_MATH_DEFINES
#include<cmath>
#include<tuple>

class TransformClassNormal {
public:
  TransformClassNormal(int levelRange_max, int levelRange_min) {
    this->levelMax = levelRange_max;
    this->levelMin = levelRange_min;
  }

  /*
   * 分辨率，表示水平方向上一个像素点代表的真实距离(m)
   */
  double getResolution(double latitude, int level){
    double resolution = 6378137.0 * 2 * M_PI * cos(latitude) / 256 / this->_getMapSize(level);
    return resolution;
  }

  int lngToTileX(double longitude, int level) {
    double x = (longitude + 180.0) / 360.0;
    int tileX = floor(x * this->_getMapSize(level));
    return tileX;
  }

  int latToTileY(double latitude, int level) {
    double lat_rad = latitude * M_PI / 180;
    double y = (1 - log(tan(lat_rad) + 1 / cos(lat_rad)) / M_PI)/2;
    int tileY = floor(y * this->_getMapSize(level));

    // 代替性算法,使用了一些三角变化，其实完全等价
    //let sinLatitude = Math.sin(latitude * Math.PI / 180);
    //let y = 0.5 - Math.log((1 + sinLatitude) / (1 - sinLatitude)) / (4 * Math.PI);
    //let tileY = Math.floor(y * this._getMapSize(level));

    return tileY;
  }

  /*
   * 从经纬度获取某一级别瓦片坐标编号
   */
  std::tuple<int, int> lnglatToTile(double longitude, double latitude, int level) {
    int tileX = this->lngToTileX(longitude, level);
    int tileY = this->latToTileY(latitude, level);

    return std::tuple<int, int>(tileX, tileY);
  }

  int lngToPixelX(double longitude, int level) {
    double x = (longitude + 180.0) / 360.0;
    int pixelX = (int)floor(x * this->_getMapSize(level) * 256) % 256;

    return pixelX;
  }

  int latToPixelY(double latitude, int level) {
    double sinLatitude = sin(latitude * M_PI / 180);
    double y = 0.5 - log((1 + sinLatitude) / (1 - sinLatitude)) / (4 * M_PI);
    int pixelY = (int)floor(y * this->_getMapSize(level) * 256) % 256;

    return pixelY;
  }

  /*
   * 从经纬度获取点在某一级别瓦片中的像素坐标
   */
  std::tuple<int, int> lnglatToPixel(double longitude, double latitude, int level) {
    int pixelX = this->lngToPixelX(longitude, level);
    int pixelY = this->latToPixelY(latitude, level);

    return std::tuple<int, int>{pixelX, pixelY};
  }

  double pixelXTolng(int pixelX, int tileX, int level) {
    double pixelXToTileAddition = pixelX / 256.0;
    double lngitude = (tileX + pixelXToTileAddition) / this->_getMapSize(level) * 360 - 180;

    return lngitude;
  }

  double pixelYToLat(int pixelY, int tileY, int level) {
    double pixelYToTileAddition = pixelY / 256.0;
    double latitude = atan(sinh(M_PI * (1 - 2 * (tileY + pixelYToTileAddition) / this->_getMapSize(level)))) * 180.0 / M_PI;

    return latitude;
  }

  /*
   * 从某一瓦片的某一像素点到经纬度
   */
  std::tuple<double, double> pixelToLnglat(int pixelX, int pixelY, int tileX, int tileY, int level) {
    double lng = this->pixelXTolng(pixelX, tileX, level);
    double lat = this->pixelYToLat(pixelY, tileY, level);

    return std::tuple<double, double>(lng, lat);
  }

private:
  /*
   * 某一瓦片等级下瓦片地图X轴(Y轴)上的瓦片数目
   */
  double _getMapSize(int level) {
    return 1 << level;
  }

private:
    int levelMax;
    int levelMin;
};