#ifndef __FACE_CONVERTER_H__
#define __FACE_CONVERTER_H__

#include <iconv.h>

#include <string>

enum face { face_utf8 = 0, face_gb2312, face_big5, face_gbk };

class Convertor {
public:
  static std::string face_to_string(face f);

  Convertor(face in_face, face out_face);
  ~Convertor();
  std::string convert(std::string const& src);

private:
  iconv_t _iconv = nullptr;
};

#endif