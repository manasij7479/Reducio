#include <vector>
#include <unordered_map>
#include <functional>
namespace reducio {
  template 
  <
    typename Key,
    typename Val,
    typename IKey,
    typename IVal,
    typename RKey,
    typename RVal
  >
  class MapReduce {
  public:
    typedef std::vector<std::pair<IKey, IVal>> MapResult;
    typedef std::vector<std::pair<Key, Val>> InputList;
    typedef std::function<MapResult(Key, Val)> Mapper;
    
    typedef std::unordered_map<RKey, RVal> ResultTable;
    typedef std::vector<IVal> ReduceList;
    typedef std::function<std::pair<RKey, RVal>(IKey, ReduceList)> Reducer;

    MapReduce(Mapper mapper, Reducer reducer) : M(mapper), R(reducer) {}

    ResultTable operator()(const InputList& input) {
      
      std::unordered_map<IKey, ReduceList> tempStorage;

      for (auto&& pair : input) {
        for (auto&& mapresult : M(pair.first, pair.second)) {
          tempStorage[mapresult.first].push_back(mapresult.second);
        }
      }
      ResultTable result;
      for (auto&& pair : tempStorage) {
      	result.insert(R(pair.first, pair.second));
      }
      return result;
    }
  private:
    Mapper M;
    Reducer R;
  };
}