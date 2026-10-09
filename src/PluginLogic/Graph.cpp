#include "Graph.h"

Graph::Graph(){
}

template <typename T>
T Graph::applyLookup(T& in){
  const double sample = static_cast<double>(in);

  // Not enough segments yet: pass the sample through unchanged.
  if(segments.size() < 1)
    return in;

  if(sample < segments[0].getXMin())
    return static_cast<T>(segments[0].applyLookup(sample));
  if(sample > segments[segments.size()-1].getXMax())
    return static_cast<T>(segments[segments.size()-1].applyLookup(sample));

  for(const auto& seg: segments){
    if(seg.contains(sample)){
      return static_cast<T>(seg.applyLookup(sample));
    }
  }

  //should never get here
  return sample;
}

// Explicit instantiations: the definition lives in this TU, so every type used
// by callers must be listed here.
template float Graph::applyLookup(float&);
template double Graph::applyLookup(double&);

void Graph::applySegments(const std::vector<point>& points){
  //points must be sorted on x in the UI thread
  segments.clear();
  for(int i = 1; i < points.size(); i++){
    Segment s(points[i-1].first, points[i-1].second, points[i].first, points[i].second);
    segments.push_back(s);
  }
}
