#include "Graph.h"

Graph::Graph(){
}

template <typename T>
T Graph::applyLookup(T& in){
  const double sample = static_cast<double>(in);

  // Not enough nodes yet: pass the sample through unchanged.
  if(nNodes <= 1)
    return in;

  if(sample < segments[0].getXMin())
    return static_cast<T>(segments[0].applyLookup(sample));
  if(sample > segments[nNodes-1].getXMax())
    return static_cast<T>(segments[nNodes-1].applyLookup(sample));

  for(int i = 0; i < nNodes; ++i){
    const auto& seg = segments[i];
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

void Graph::applySegments(){

}
