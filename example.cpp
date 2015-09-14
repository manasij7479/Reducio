#include "Reducio.h"
#include <iostream>
#include <string>
int main() {
  reducio::MapReduce 
    <
      std::string, std::vector<std::string>,
      std::string, int, 
      std::string, int
    > 
  mr
  (
  	[](std::string a, std::vector<std::string> b) {
  	  std::vector<std::pair<std::string, int>> result;
  	  for (auto s : b)
        result.push_back({s,1});
      return result;
  	},
  	[](std::string a, std::vector<int> v) {
  	  return std::make_pair(a, v.size());
  	}
  );

  auto result = mr({{"a", {"a", "b"}},{"b", {"b", "c"}}});
  for (auto p : result) {
  	std::cout << p.first << '\t' << p.second << std::endl;
  }
}