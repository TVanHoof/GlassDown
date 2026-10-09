#include <gtest/gtest.h>

#include "Graph.h"

#include <type_traits>
#include <utility>

namespace {

constexpr double kTolerance = 1e-9;

using point = std::pair<double, double>;

// applyLookup takes T&, so the sample is copied into a mutable local first.
// Graph itself is non-const because applyLookup is not a const member; that is
// a wart in the API, not something these tests should paper over by hiding it.
double lookup(Graph& graph, double x) {
  return graph.applyLookup(x);
}

} // namespace

TEST(GraphTests, EmptyGraphPassesSampleThroughUnchanged) {
  Graph graph;

  // No segments set yet: audio must pass through untouched.
  for(const double x : { -1.0, 0.0, 0.5, 1.0 })
    EXPECT_NEAR(lookup(graph, x), x, kTolerance) << "at x = " << x;
}

TEST(GraphTests, SinglePointProducesNoSegmentsAndPassesThrough) {
  Graph graph;
  graph.applySegments({ point{ 0.0, 0.0 } });

  // One point cannot describe a segment, so the graph stays empty.
  EXPECT_NEAR(lookup(graph, 0.5), 0.5, kTolerance);
}

TEST(GraphTests, IdentitySegmentMapsInputToOutput) {
  Graph graph;
  graph.applySegments({ point{ -1.0, -1.0 }, point{ 1.0, 1.0 } });

  for(const double x : { -1.0, -0.5, 0.0, 0.5, 1.0 })
    EXPECT_NEAR(lookup(graph, x), x, kTolerance) << "at x = " << x;
}

TEST(GraphTests, SingleSegmentAppliesGainOfTwo) {
  Graph graph;
  graph.applySegments({ point{ 0.0, 0.0 }, point{ 0.5, 1.0 } });

  // This is the case that proves a single segment actually does work: the
  // expected output differs from the input, so a passthrough bug fails here.
  for(const double x : { 0.0, 0.125, 0.25, 0.5 })
    EXPECT_NEAR(lookup(graph, x), 2.0 * x, kTolerance) << "at x = " << x;
}

TEST(GraphTests, SingleSegmentCanInvertSignal) {
  Graph graph;
  graph.applySegments({ point{ -1.0, 1.0 }, point{ 1.0, -1.0 } });

  // Negative gain: an inverted signal cannot be produced by a passthrough, so
  // this catches a guard that returns early for a one-segment graph.
  for(const double x : { -1.0, -0.25, 0.0, 0.25, 1.0 })
    EXPECT_NEAR(lookup(graph, x), -x, kTolerance) << "at x = " << x;
}

TEST(GraphTests, SampleBelowRangeIsMappedByTheFirstSegment) {
  Graph graph;
  graph.applySegments({ point{ 0.0, 0.0 }, point{ 0.5, 1.0 } });

  // Out of range below: extrapolated along the first segment's line (y = 2x).
  EXPECT_NEAR(lookup(graph, -0.25), -0.5, kTolerance);
}

TEST(GraphTests, SampleAboveRangeIsMappedByTheLastSegment) {
  Graph graph;
  graph.applySegments({ point{ 0.0, 0.0 }, point{ 0.5, 1.0 } });

  // Out of range above: extrapolated along the last (only) segment, y = 2x.
  EXPECT_NEAR(lookup(graph, 2.0), 4.0, kTolerance);
}

TEST(GraphTests, TwoSegmentsApplyEachSlopeOnItsOwnRange) {
  // Gain of 2 on [0, 0.5], then a fall from 1 to 0 on [0.5, 1].
  Graph graph;
  graph.applySegments({ point{ 0.0, 0.0 }, point{ 0.5, 1.0 }, point{ 1.0, 0.0 } });

  EXPECT_NEAR(lookup(graph, 0.0),  0.0, kTolerance);
  EXPECT_NEAR(lookup(graph, 0.25), 0.5, kTolerance);
  EXPECT_NEAR(lookup(graph, 0.5),  1.0, kTolerance);
  EXPECT_NEAR(lookup(graph, 0.75), 0.5, kTolerance);
  EXPECT_NEAR(lookup(graph, 1.0),  0.0, kTolerance);
}

TEST(GraphTests, MultipleSegmentsJoinWithoutADiscontinuity) {
  // Rising by 1 per unit across two segments: the join point must land on the
  // same value whether it is resolved through the first or the second segment.
  Graph graph;
  graph.applySegments({ point{ 0.0, 0.0 }, point{ 1.0, 1.0 }, point{ 2.0, 2.0 } });

  EXPECT_NEAR(lookup(graph, 1.0), 1.0, kTolerance);
  EXPECT_NEAR(lookup(graph, 0.999), 0.999, kTolerance);
  EXPECT_NEAR(lookup(graph, 1.001), 1.001, kTolerance);
}

TEST(GraphTests, ReplacingSegmentsDiscardsThePreviousCurve) {
  Graph graph;
  graph.applySegments({ point{ 0.0, 0.0 }, point{ 0.5, 1.0 } });
  EXPECT_NEAR(lookup(graph, 0.25), 0.5, kTolerance);

  // Re-applying must clear the old segments, not append to them.
  graph.applySegments({ point{ -1.0, 1.0 }, point{ 1.0, -1.0 } });
  EXPECT_NEAR(lookup(graph, 0.25), -0.25, kTolerance);
}

TEST(GraphTests, FloatSamplesAreProcessedTheSameWay) {
  Graph graph;
  graph.applySegments({ point{ 0.0, 0.0 }, point{ 0.5, 1.0 } });

  float x = 0.25f;
  const auto result = graph.applyLookup(x);

  EXPECT_NEAR(result, 0.5f, kTolerance);

  // applyLookup is templated on the sample type and must hand back the same
  // type it was given, so a float in yields a float out (not a double).
  static_assert(std::is_same_v<decltype(graph.applyLookup(x)), float>,
                "applyLookup must preserve the sample type");
}