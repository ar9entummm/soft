#ifndef MAIN_H
#define MAIN_H

#include <string>
#include <functional>

class Option{
private:
  std::string name;
  int index;
  std::function<void(int index)> callback;
public:
    Option(int ind, std::string nm, std::function<void(int index)> cb);

    void ex_callback(int index);

    std::string get_name() const;

    int get_index() const;
};

void writeOptions(const std::vector<Option>& options, int index);

#endif
