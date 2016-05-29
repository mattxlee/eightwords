#include "face_converter.h"

std::string Convertor::face_to_string(face f)
{
    switch (f)
    {
    case face_utf8:
        return "utf-8";
    case face_gb2312:
        return "gb2312";
    case face_big5:
        return "big5";
    case face_gbk:
        return "gbk";
    }
}

Convertor::Convertor(face in_face, face out_face)
{
    _iconv = iconv_open(face_to_string(out_face).c_str(), face_to_string(in_face).c_str());
}

Convertor::~Convertor()
{
    iconv_close(_iconv);
    _iconv = NULL;
}

std::string Convertor::convert(const std::string &src)
{
    int arg = 1;
    iconvctl(_iconv, ICONV_SET_DISCARD_ILSEQ, &arg);
    const char *sz_src = src.c_str();
    size_t len_src = src.size() + 1;
    if (src.empty())
    {
        throw std::runtime_error("转换输入的字符串是空的");
    }
    size_t len_dst = len_src * 3;
    char *sz_dst2 = new char[len_dst];
    memset(sz_dst2, 0, len_dst);
    char *sz_dst = sz_dst2;
    auto err = iconv(_iconv, const_cast<char **>(&sz_src), &len_src, &sz_dst, &len_dst);
    if (err == -1)
    {
        delete[] sz_dst2;
        throw std::runtime_error("iconv转换函数返回值异常");
    }
    std::string dst = sz_dst2;
    delete[] sz_dst2;
    return dst;
}
