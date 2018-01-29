#include <string>
#include <mutex>
#include <cstring>
#include <cstdlib>
#include <boost/algorithm/string.hpp>

enum OperateStatus {
    SUCCESS = 0,
    FAIL,
};

enum ColumnDataType {
    INT = 0,
    INT_ARRAY,
    FLOAT,
    FLOAT_ARRAY,
    C_STYLE_STRING,
    C_STYLE_STRING_ARRAY = 5,
    USR_DEFINED,
};

template<typename T>
class AbstractStringConventor {
  public:
    AbstractStringConventor() {}
    virtual ~AbstractStringConventor() {}

    virtual OperateStatus convert(const std::string& src, T& dst) = 0;
};

class StringIntConventor : public AbstractStringConventor<int> {
  public:
    StringIntConventor() {}
    virtual ~StringIntConventor() {}

    OperateStatus convert(const std::string& src, int& dst) {
        int tmp_value = 0;
        try {
            tmp_value = std::stoi(src);
        } catch (std::invalid_argument) {
            return FAIL;
        } catch (std::out_of_range) {
            return FAIL;
        }

        dst = tmp_value;
        return SUCCESS;
    }
};

class StringFloatConventor : public AbstractStringConventor<float> {
  public:
    StringFloatConventor() {}
    virtual ~StringFloatConventor() {}

    OperateStatus convert(const std::string& src, float& dst) {
        float tmp_value = 0.0f;
        try {
            tmp_value = std::stof(src);
        } catch (std::invalid_argument) {
            return FAIL;
        } catch (std::out_of_range) {
            return FAIL;
        }

        dst = tmp_value;
        return SUCCESS;
    }
};

class StringCStyleStringConventor : public AbstractStringConventor<char *> {
  public:
    StringCStyleStringConventor() {}
    virtual ~StringCStyleStringConventor() {}

    OperateStatus convert(const std::string& src, char* &dst) {
        int str_len = src.size();
        memcpy(dst, src.c_str(), str_len);
        dst[str_len] = '\0';
        return SUCCESS;
    }
};

template<typename T>
class BaseParser {
  public:
    BaseParser(const std::string& item_to_parse,
               std::shared_ptr<AbstractStringConventor<T> > conventor)
            : _item_to_parse(item_to_parse),
              _conventor(conventor) {}
    virtual ~BaseParser() {}

    const std::string get_item_to_parse() {
        std::lock_guard<std::mutex> lock(_mutex);
        return _item_to_parse;
    }

    OperateStatus set_item_to_parse(const std::string& item_to_parse) {
        std::lock_guard<std::mutex> lock(_mutex);
        _item_to_parse = item_to_parse;
        return SUCCESS;
    }

    std::shared_ptr<AbstractStringConventor<T> > get_conventor() {
        std::lock_guard<std::mutex> lock(_mutex);
        return _conventor;
    }

    OperateStatus set_conventor(std::shared_ptr<AbstractStringConventor<T> > conventor) {
        std::lock_guard<std::mutex> lock(_mutex);
        _conventor = conventor;   
    }

    virtual OperateStatus parse(T& value) {
        std::lock_guard<std::mutex> lock(_mutex);
        if (_conventor == nullptr) {
            return FAIL;
        }
        return _conventor->convert(_item_to_parse, value);
    }

  protected:
    std::mutex _mutex;
    std::string _item_to_parse;
    std::shared_ptr<AbstractStringConventor<T> > _conventor;
};

class IntParser : public BaseParser<int> {
  public:
    IntParser(const std::string& item_to_parse,
              std::shared_ptr<AbstractStringConventor<int> > conventor)
            : BaseParser(item_to_parse, conventor) {}
    virtual ~IntParser() {}
};

class FloatParser : public BaseParser<float> {
  public:
    FloatParser(const std::string& item_to_parse,
                std::shared_ptr<AbstractStringConventor<float> > conventor)
            : BaseParser(item_to_parse, conventor) {}
    virtual ~FloatParser() {}
};

class CStyleStringParser : public BaseParser<char *> {
  public:
    CStyleStringParser(const std::string& item_to_parse,
                       std::shared_ptr<AbstractStringConventor<char *> > conventor)
            : BaseParser(item_to_parse, conventor) {}
    virtual ~CStyleStringParser() {}
};

class StringSpliter {
  public:
    StringSpliter(const std::string& delimeter = ",")
            : _delimeter(delimeter) {}
    virtual ~StringSpliter() {}

    OperateStatus set_delimeter(const std::string& delimeter) {
        _delimeter = delimeter;
        return SUCCESS;
    }

    const std::string get_delimeter() {
        return _delimeter;
    }

    OperateStatus split_string_to_array(const std::string& src_str,
                                        std::vector<std::string>& dst_array) {
        boost::split(dst_array, src_str, boost::is_any_of(_delimeter));
        return SUCCESS;
    }

  private:
    std::string _delimeter;
}

template<typename T>
class StringBuildInTypeArrayConventor : public AbstractStringConventor<std::vector<T> > {
  public:
    StringBuildInTypeArrayConventor() {
        _conventor = std::make_shared<AbstractStringConventor<T> >();
        _spliter = std::make_shared<StringSpliter>();
    }
    virtual ~StringBuildInTypeArrayConventor() {}

    OperateStatus convert(const std::string& src, vector<T>& dst) {
        // find index of ':'
        std::string::size_typ colon_idx = src.find(':');
        if (colon_idx == std::string::npos) {
            return FAIL;
        }

        // calculate num of array items
        std::string size_str = src.substr(0, colon_idx);
        int size = 0;
        try {
            size = std::stoi(size_str);
        } catch (std::invalid_argument) {
            return FAIL;
        } catch (std::out_of_range) {
            return FAIL;
        }

        // split array string to vector
        std::string arr_str = src.substr(colon_idx+1);
        std::vector<std::string> arr_vec;
        if (_spliter->split_string_to_array(arr_str, arr_vec) != SUCCESS) {
            return FAIL;
        }

        if (arr_vec.size() != size) {
            return FAIL;
        }

        T tmp_value = 0;
        for (auto& item : arr_vec) {
            if (_conventor->convert(item, tmp_value) != SUCCESS) {
                return FAIL;
            }
            dst.push_back(tmp_value);
        }

        return SUCCESS;    
    }

  private:
    std::shared_ptr<AbstractStringConventor<T> > _conventor;
    std::shared_ptr<StringSpliter> _spliter;
}

class IntArrayParser : public BaseParser<std::vector<int> > {
  public:
    IntArrayParser(const std::string& item_to_parse,
                   std::shared_ptr<AbstractStringConventor<std::vector<int>>> conventor)
            : BaseParser(item_to_parse, conventor) {}
    virtual ~IntArrayParser() {}
};

class FloatArrayParser : public BaseParser<std::vector<float> > {
  public:
    FloatArrayParser(const std::string& item_to_parse,
                     std::shared_ptr<AbstractStringConventor<std::vector<float>>> conventor)
            : BaseParser(item_to_parse, conventor) {}
    virtual ~FloatArrayParser() {}
};

class CStyleStringArrayParser : public BaseParser<std::vector<char *> > {
  public:
    CStyleStringArrayParser(const std::string& item_to_parse,
                            std::shared_ptr<AbstractStringConventor<std::vector<char *>>> conventor)
            : BaseParser(item_to_parse, conventor) {}
    virtual ~CStyleStringArrayParser() {}
};

int main(int argc, char *argv[]) {

    return 0;
}